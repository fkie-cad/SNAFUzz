// 
// The VMBUS is the system used by Hyper-V to implement synthetic devices.
// Once set up, each device has associated ring-buffers, used to exchange 
// packets between the guest and host. When the host sends a message to 
// the guest, it 
//     1) Writes the message to the ring buffer
//     2) Set the flag corresponding to the Device in the 
//        "Synthetic interrupt event flags page"
//     3) and causes a synthetic interrupt on the VMBUS_SINT (2).
// Conversely, when the guest wants to send an interrupt to the host, it
//     1) Writes the message to the ring buffer
//     2) Either causes a VMEXIT by using a VMCALL which specifies
//        the connection if for the VMBUS
//     3) Or writes to a "Monitor Page", which was set up during negotiations,
//        causing a VMEXIT for accessing unmapped physical memory.
// 
// We support the following devices:
//    
//    1) SCSI Disk Device
//    2) Absolutely positioned HID Mouse
//    3) PS/2 Keyboard
//    4) VMBUS specific SynthVid Screen
// 
// After hardcoding the negotiation packets, we respond to SCSI
// requests from the Disk Device including reads and writes and
// in Snapshot Mode, we send Mouse / Keyboard packets when they
// change. All other packets are pulled from the ring-buffer
// and ignored.
// 
//                                           - Pascal Beyer 28.02.2024
// 


// 
// VMBUS Packets:
// 
// Each vmbus bus packet starts out with a 'vmbus_packet_description'.
// The size of the packet is 'vmbus_packet->PacketLengthDiv8 * 8' and is 
// immediately followed by a 'u64' being the offset of the start of the packet 
// (so you can iterate the packets in reverse order as well).
// 
// Depending on the packet type (see 'vmbus_packet_types') there might be additional 
// data immediately after the 'vmbus_packet_description' but before the _data_ of the
// packet, located at (u8 *)vmbus_packet + vmbus_packet->PacketDataOffsetDiv8 * 8.
// 

struct vmbus_packet_description{
    u16 PacketType;
    u16 PacketDataOffsetDiv8;
    u16 PacketLengthDiv8;
    u16 PacketFlags;
    u64 PacketIdentifier;
};

static char *vmbus_packet_types[] = {
    [0x0] = "VM_PKT_INVALID",
    [0x1] = "VM_PKT_SYNCH",
    [0x2] = "VM_PKT_ADD_XFER_PAGESET",
    [0x3] = "VM_PKT_RM_XFER_PAGESET",
    [0x4] = "VM_PKT_ESTABLISH_GPADL",
    [0x5] = "VM_PKT_TEARDOWN_GPADL",
    [0x6] = "VM_PKT_DATA_INBAND",
    [0x7] = "VM_PKT_DATA_USING_XFER_PAGES",
    [0x8] = "VM_PKT_DATA_USING_GPADL",
    [0x9] = "VM_PKT_DATA_USING_GPA_DIRECT",
    [0xa] = "VM_PKT_CANCEL_REQUEST",
    [0xb] = "VM_PKT_COMP",
    [0xc] = "VM_PKT_DATA_USING_ADDITIONAL_PKT",
    [0xd] = "VM_PKT_ADDITIONAL_DATA",
};

struct hv_message{
    u32 message_type;
    u8  payload_size;
    u8  message_flags;
    u16 reserved;
    
    u64 sender_identifier;
    
    u8 payload[];
};

void sint_post_message(struct context *context, u32 synthetic_interrupt_number, u32 message_type, void *payload, u8 payload_size){
    
    struct registers *registers = &context->registers;
    
    if(!(registers->hv_x64_msr_simp & 1)) return;
    
    u8 *message_page = get_physical_memory_for_write(context, registers->hv_x64_msr_simp & ~0xfff);
    
    struct hv_message *message = (void *)(message_page + 0x100 * synthetic_interrupt_number);
    
    if(message->message_type == /*HvMessageTypeNone*/0){
        message->message_type  = message_type;
        message->message_flags = 0;
        message->payload_size  = payload_size;
        memcpy(message->payload, payload, payload_size);
        
        u64 synthetic_interrupt_configuration = registers->hv_x64_msr_sint[synthetic_interrupt_number];
        
        pend_interrupt(context, registers, synthetic_interrupt_configuration & 0xff);
    }else{
        message->message_flags |= /*MessagePending*/1;
        
        message = (void *)push_data(&context->permanent_arena, u8, sizeof(*message) + payload_size); // @cleanup: Use malloc?
        message->message_type  = message_type;
        message->message_flags = 0;
        message->payload_size  = payload_size;
        memcpy(message->payload, payload, payload_size);
        
        context->vmbus.pending_messages[context->vmbus.pending_message_reserved++ % array_count(context->vmbus.pending_messages)] = message;
    }
}

// @cleanup: For now this assumes that there is only one packet to read.
struct vmbus_packet_description *vmbus_read_packet(struct memory_arena *arena, struct context *context, struct vmbus_channel *channel){
    
    // if(PRINT_VMBUS_EVENTS) print("["__FUNCTION__"] DeviceKind %x\n", channel->device_kind);
    
    u8 *header = get_physical_memory_for_write(context, channel->read_buffer.header);
    
    u32 write_index = *(u32 *)(header + 0);
    u32 read_index  = *(u32 *)(header + 4);
    
    u64 channel_size = channel->read_buffer.amount_of_pages * 0x1000;
    
    crash_assert((write_index & 7) == 0, null);
    crash_assert((read_index  & 7) == 0, null);
    if(read_index == write_index) return null;
    
    u64 size_to_read = (read_index <= write_index) ? (write_index - read_index) : ((channel_size - read_index) + write_index);
    if(size_to_read == 0) return null;
    
    u8 *packet_buffer = push_data(arena, u8, size_to_read);
    
    for(u32 offset = 0; offset < size_to_read;){
        
        u32 read_at = (read_index + offset) % channel_size;
        
        // 
        // Figure out the page and offset.
        // 
        u32 page_to_read   = read_at & ~0xfff;
        u32 offset_to_read = read_at &  0xfff;
        
        // 
        // Translate the page to physical memory.
        // 
        u64 physical_address = channel->read_buffer.pages[page_to_read / 0x1000] * 0x1000;
        u8 *physical_memory  = get_physical_memory_for_read(context, physical_address);
        
        int is_last_page = ((size_to_read - offset) + offset_to_read) < 0x1000;
        
        // 
        // The end is either the 'write_index' if we are on the last page, or the start of the next page.
        // 
        u32 end = is_last_page ? write_index : (page_to_read + 0x1000);
        u32 size = end - read_at;
        
        memcpy(packet_buffer + offset, physical_memory + offset_to_read, size);
        
        offset += size;
    }
    
    *(u32 *)(header + 4) = write_index;
    
    struct vmbus_packet_description *vmbus_packet = (void *)packet_buffer;
    
    u64 packet_data_offset = vmbus_packet->PacketDataOffsetDiv8 << 3;
    u64 packet_length      = (vmbus_packet->PacketLengthDiv8 << 3) + 8; // plus 8 for the trailing u64.
    
    crash_assert(packet_length <= size_to_read, null);
    crash_assert(packet_data_offset <= packet_length, null);
    
    return vmbus_packet;
}

void vmbus_send_packet(struct context *context, struct vmbus_channel *channel, struct vmbus_packet_description *packet){
    
    // if(PRINT_VMBUS_EVENTS) print("["__FUNCTION__"] DeviceKind %x\n", channel->device_kind);
    
    u32 packet_size = (packet->PacketLengthDiv8 << 3);
    
    u8 *header = get_physical_memory_for_write(context, channel->send_buffer.header);
    
    u32 write_index = *(u32 *)(header + 0);
    u32 read_index  = *(u32 *)(header + 4);
    u64 channel_size = channel->send_buffer.amount_of_pages * 0x1000;
    
    crash_assert((write_index & 7) == 0);
    crash_assert((read_index  & 7) == 0);
    
    u64 size_used = (read_index <= write_index) ? (write_index - read_index) : ((channel_size - read_index) + write_index);
    u64 size_left = channel_size - size_used;
    crash_assert(packet_size <= size_left); 
    
    // 
    // @cleanup: This is really ugly!
    // 
    u8 *packet_data = push_data(&context->scratch_arena, u8, packet_size + 8);
    memcpy(packet_data, packet, packet_size);
    *(u64 *)(packet_data + packet_size) = write_index;
    packet_size += 8;
    
    u32 packet_end = (write_index + packet_size) % channel_size;
    
    for(u32 offset = 0; offset < packet_size; ){
        
        u32 write_at = (write_index + offset) % channel_size;
        
        // 
        // Figure out the page and offset.
        // 
        u32 page_to_write   = write_at & ~0xfff;
        u32 offset_to_write = write_at &  0xfff;
        
        // 
        // Translate the page to physical memory.
        // 
        u64 physical_address = channel->send_buffer.pages[page_to_write / 0x1000] * 0x1000;
        u8 *physical_memory  = get_physical_memory_for_write(context, physical_address);
        
        int is_last_page = ((packet_size - offset) + offset_to_write) < 0x1000;
        
        // 
        // The end is either the 'read_index' if we are on the last page, or the start of the next page.
        // 
        u32 end = is_last_page ? packet_end : (page_to_write + 0x1000);
        u32 size = end - write_at;
        
        memcpy(physical_memory + offset_to_write, packet_data + offset, size);
        
        offset += size;
    }
    
    *(u32 *)(header + 0) = packet_end;
    
    u8 *siefp = get_physical_memory_for_write(context, context->registers.hv_x64_msr_siefp & ~0xfff);
    u64 flag  = 1ull << channel->channel_id;
    *(u32 *)(siefp + /*VMBUS_SINT*/2 * 0x100) |= flag;
    
    if(!context->vmbus.send_packet_skip_interrupt){
        sint_post_message(context, /*VMBUS_SINT*/2, /*HV_MESSAGE_NONE*/0, null, 0);
    }
}

struct vmbus_pipe_header{
    u32 type;
    u32 size;
};

void vmbus_pipe_send_packet(struct context *context, struct vmbus_channel *channel, void *data, smm size){
    
    u8 buffer[0x100];
    
    struct {
        struct vmbus_packet_description description;
        struct vmbus_pipe_header pipe_header;
        u8 packet[];
    } *packet = (void *)buffer;
    
    u32 aligned_size = (u32)((size + 7) & ~7);
    
    crash_assert(size + sizeof(*packet) < sizeof(buffer));
    
    packet->description = (struct vmbus_packet_description){
        .PacketType = /*VMBUS_PACKET_DATA_INBAND*/6,
        .PacketDataOffsetDiv8 = sizeof(struct vmbus_packet_description)/8,
        .PacketLengthDiv8 = (u16)((sizeof(*packet) + aligned_size)/8),
        .PacketFlags = 0,
        .PacketIdentifier = 0, 
    };
    
    packet->pipe_header.type = 1;
    packet->pipe_header.size = (u32)size;
    
    memcpy(packet->packet, data, size);
    if(aligned_size - size){
        memset(packet->packet + size, 0, aligned_size - size);
    }
    
    vmbus_send_packet(context, channel, &packet->description);
}

#define HV_SCSI_GUID   {0xba6163d9, 0x04a1, 0x4d29, {0xb6, 0x05, 0x72, 0xe2, 0xff, 0xb1, 0xdc, 0x7f}}
#define HV_MOUSE_GUID  {0xcfa8b69e, 0x5b4a, 0x4cc0, {0xb9, 0x8b, 0x8b, 0xa1, 0xa1, 0xf3, 0xf9, 0x5a}}
#define HV_KBD_GUID    {0xf912ad6d, 0x2b17, 0x48ea, {0xbd, 0x65, 0xf9, 0x27, 0xa6, 0x1c, 0x76, 0x84}}
#define HV_SYNVID_GUID {0xda0a7802, 0xe377, 0x4aac, {0x8e, 0x77, 0x05, 0x58, 0xeb, 0x10, 0x73, 0xf8}}

enum vmbus_device_kind vmbus_interface_type_id_to_device_type(struct guid device_guid){
    enum vmbus_device_kind vmbus_device_kind = VMBUS_DEVICE_unknown;
    
    if(memcmp(&device_guid, &(struct guid)HV_SCSI_GUID, 16) == 0){
        vmbus_device_kind = VMBUS_DEVICE_scsi;
    }else if(memcmp(&device_guid, &(struct guid)HV_MOUSE_GUID, 16) == 0){
        vmbus_device_kind = VMBUS_DEVICE_mouse;
    }else if(memcmp(&device_guid, &(struct guid)HV_KBD_GUID, 16) == 0){
        vmbus_device_kind = VMBUS_DEVICE_keyboard;
    }else if(memcmp(&device_guid, &(struct guid)HV_SYNVID_GUID, 16) == 0){
        vmbus_device_kind = VMBUS_DEVICE_framebuffer;
    }
    
    return vmbus_device_kind;
}

void vmbus_handle_end_of_message(struct context *context){

    if(context->vmbus.pending_message_send < context->vmbus.pending_message_reserved){
        struct hv_message *pending_message = context->vmbus.pending_messages[context->vmbus.pending_message_send++ % array_count(context->vmbus.pending_messages)];
        
        u32 synthetic_interrupt_number = /*VMBUS_SINT*/2; // @cleanup: Where should this come from?
        
        u8 *message_page = get_physical_memory_for_write(context, context->registers.hv_x64_msr_simp & ~0xfff);
        struct hv_message *message = (void *)(message_page + 0x100 * synthetic_interrupt_number);
        
        memcpy(message, pending_message, sizeof(*pending_message) + pending_message->payload_size);
        
        if(context->vmbus.pending_message_send < context->vmbus.pending_message_reserved){
            message->message_flags |= /*MessagePending*/1;
        }
        
        u64 synthetic_interrupt_configuration = context->registers.hv_x64_msr_sint[synthetic_interrupt_number];
        pend_interrupt(context, &context->registers, synthetic_interrupt_configuration & 0xff);
    }
}

void vmbus_channel_initialize_ringbuffers(struct vmbus_channel *channel, struct gpadl *gpadl){
    u64 read_ring_buffer_pages = channel->read_ring_buffer_pages;
    
    struct vmbus_ring_buffer *read_buffer = &channel->read_buffer;
    struct vmbus_ring_buffer *send_buffer = &channel->send_buffer;
    
    read_buffer->header = gpadl->pages[0] * 0x1000;
    read_buffer->amount_of_pages = (read_ring_buffer_pages - 1);
    read_buffer->pages = &gpadl->pages[1];
    
    send_buffer->header = gpadl->pages[read_ring_buffer_pages] * 0x1000;
    send_buffer->amount_of_pages = gpadl->amount_of_pages - (read_ring_buffer_pages + 1);
    send_buffer->pages = &gpadl->pages[read_ring_buffer_pages + 1];
}

void vmbus_handle_message(struct context *context, u32 connection_id, void *payload, u32 payload_size){
    
    (void)payload_size; // @cleanup:
    
    struct{
        u32 message_type;
        u32 padding;
        
        union{
            struct{
                u32 vmbus_version_requested;
                u32 target_vcpu;
                u64 interrupt_page;
                u64 monitor_page1;
                u64 monitor_page2;
            } initiate_contact;
            
            struct {
                u32 channel_id;
                u32 gpadl_id;
                u16 range_buflen;
                u16 rangecount;
                
                // Followed by the range buffers.
                u8 range_lists[];
                
            } gpadl_header; // @note: GPADL = guest physical address descriptor list
            
            struct {
                u32 channel_id;
                u32 open_id;
                u32 ring_buffer_gpadl_id;
                u32 target_vp;
                u32 read_ring_buffer_pages;
                u8 user_data[120];
            } open_channel;
            
            struct{
                u32 child_id;
                u32 gpadl_id;
            } teardown;
            
            struct{
                u32 child_relid;
            } close_channel;
        };
    } *message = payload;
    
    if(PRINT_VMBUS_EVENTS) print("["__FUNCTION__"] Message %x\n", message->message_type);
    
    switch(message->message_type){
        
        case /*VMBUS_MSG_INITIATE_CONTACT*/0xe:{
            
            context->vmbus.monitor_page1 = message->initiate_contact.monitor_page1;
            context->vmbus.monitor_page2 = message->initiate_contact.monitor_page2;
            
            struct{
                u64 message_type;
                u32 version_supported; // @note: Technically this is 2 u8 and then u16 reserved.
                u32 message_connection_id;
            } version_response_message = {
                .message_type = /*VMBUS_MSG_VERSION_RESPONSE*/0xf,
                .version_supported = message->initiate_contact.vmbus_version_requested == 0x50002,
                .message_connection_id = connection_id,
            };
            
            if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("[" __FUNCTION__ "] Received VMBUS_MSG_INITIATE_CONTACT with version 0x%x sending supported %d\n", message->initiate_contact.vmbus_version_requested, version_response_message.version_supported);
            
            sint_post_message(context, /*VMBUS_SINT*/2, /*HV_MESSAGE_VMBUS*/1, &version_response_message, sizeof(version_response_message));
        }break;
        
        case /*VMBUS_MSG_REQUESTOFFERS*/3:{
            // no contents.
            
            if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("[" __FUNCTION__ "] Received VMBUS_MSG_REQUESTOFFERS\n");
            
            
            static struct {
                u8  monitor_id;
                u8  monitor_allocated;
                u16 channel_flags;
                u32 connection_id;
                struct guid interface_type_guid;
                struct guid interface_instance_guid;
            } vmbus_channels[] = { // @WARNING: order needs to match 'vmbus_device_kind'.
                {
                    .monitor_id  = 0xff,
                    .monitor_allocated = 0,
                    .connection_id = 0x2001,
                    .interface_type_guid = HV_SCSI_GUID,
                    .interface_instance_guid = {0xfec9c10e, 0x93fb, 0x4005, {0xbb, 0x8c, 0x22, 0x40, 0x24, 0x0f, 0xaf, 0xb7}},
                },
                
                {
                    .monitor_id  = 0xff,
                    .monitor_allocated = 0,
                    .channel_flags = /*NAMED_PIPE_MODE*/0x10,
                    .connection_id = 0x2002,
                    .interface_type_guid = HV_MOUSE_GUID,
                    .interface_instance_guid = {0x58f75a6d, 0xd949, 0x4320, {0x99, 0xe1, 0xa2, 0xa2, 0x57, 0x6d, 0x58, 0x1c}},
                },
                
                {
                    .monitor_id  = 0xff,
                    .monitor_allocated = 0,
                    .channel_flags = 0,
                    .connection_id = 0x2003,
                    .interface_type_guid = HV_KBD_GUID,
                    .interface_instance_guid = {0xd34b2567, 0xb9b6, 0x42b9, {0x87, 0x78, 0x0a, 0x4e, 0xc0, 0xb9, 0x55, 0xbf}},
                },
                
                {
                    .monitor_id  = 0xff,
                    .monitor_allocated = 0,
                    .channel_flags = /*NAMED_PIPE_MODE*/0x10,
                    .connection_id = 0x2004,
                    .interface_type_guid = HV_SYNVID_GUID,
                    .interface_instance_guid = {0x5620e0c7, 0x8062, 0x4dce, {0xae, 0xb7, 0x52, 0x0c, 0x7e, 0xf7, 0x61, 0x71}},
                },
            };
            
            for(u32 at = 0; at < array_count(vmbus_channels); at++){
                
                struct{
                    u64 message_type;
                    
                    struct guid interface_type_guid;
                    struct guid interface_instance_guid;
                    u64 reserved1;
                    u64 reserved2;
                    
                    u16 channel_flags;
                    u16 mmio_megabytes;
                    
                    u32 pipe_mode;
                    u8 user_bytes[116];
                    
                    u16 sub_channel_index;
                    u16 reserved3;
                    
                    u32 channel_id;
                    u8  monitor_id;
                    
                    u8 monitor_allocated;
                    u16 is_dedicated_interrupt;
                    
                    u32 connection_id;
                } offer_channel_message = {
                    .message_type = /*VMBUS_MSG_OFFERCHANNEL*/1,
                    
                    .interface_type_guid     = vmbus_channels[at].interface_type_guid,
                    .interface_instance_guid = vmbus_channels[at].interface_instance_guid,
                    .channel_id             = at + 1,
                    .channel_flags           = vmbus_channels[at].channel_flags,
                    .monitor_id              = vmbus_channels[at].monitor_id,
                    .monitor_allocated       = vmbus_channels[at].monitor_allocated,
                    .is_dedicated_interrupt  = 1,
                    .connection_id           = vmbus_channels[at].connection_id,
                };
                
                if(vmbus_channels[at].interface_type_guid.Data1 == 0xda0a7802){
                    offer_channel_message.mmio_megabytes = 8;
                }
                
                if(offer_channel_message.channel_flags & /*NAMED_PIPE_MODE*/0x10){
                    offer_channel_message.pipe_mode = 4;
                }
                
                sint_post_message(context, /*VMBUS_SINT*/2, /*HV_MESSAGE_VMBUS*/1, &offer_channel_message, sizeof(offer_channel_message) - /*padding*/4);
                
                struct vmbus_channel *channel = push_struct(&context->permanent_arena, struct vmbus_channel);
                channel->device_kind = at + 1;
                channel->channel_id  = offer_channel_message.channel_id;
                channel->monitor_id  = offer_channel_message.monitor_id;
                channel->connection_id = offer_channel_message.connection_id;
                
                channel->next = context->vmbus.channels;
                context->vmbus.channels = channel;
                
                if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("["__FUNCTION__"] DeviceKind %s (%x)\n", vmbus_device_kind_string[channel->device_kind], channel->device_kind);
            }
            
            u64 message_type = /*VMBUS_MSG_ALLOFFERS_DELIVERED*/4;
            
            if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("["__FUNCTION__"] VMBUS_MSG_ALLOFFERS_DELIVERED\n");
            
            sint_post_message(context, /*VMBUS_SINT*/2, /*HV_MESSAGE_VMBUS*/1, &message_type, sizeof(message_type));
        }break;
        
        case /*VMBUS_MSG_CREATE_GPADL*/8:{
            
            if(message->gpadl_header.rangecount != 1){
                set_crash_information(context, CRASH_internal_error, (u64)"VMBUS_MSG_CREATE_GPADL with range count != 1 (currently unsupported).");
                return;
            }
            
            // @cleanup: Checks for size and stuff.
            
            struct {
                u32 byte_count;
                u32 byte_offset;
                u64 pfn_array[];
            } *gpa_range = (void *)message->gpadl_header.range_lists;
            
            if(gpa_range->byte_offset || (gpa_range->byte_count & 0xfff)){
                set_crash_information(context, CRASH_internal_error, (u64)"VMBUS_MSG_CREATE_GPADL with non page aligned range information (currently unsupported).");
                return;
            }
            
            u32 number_of_pages = gpa_range->byte_count/0x1000;
            
            crash_assert(!globals.fuzzing);
            struct gpadl *gpadl = (void *)push_data(&context->permanent_arena, u8, sizeof(struct gpadl) + number_of_pages * sizeof(u64));
            gpadl->amount_of_pages = number_of_pages;
            gpadl->gpadl_id        = message->gpadl_header.gpadl_id;
            gpadl->channel_id      = message->gpadl_header.channel_id;
            gpadl->next            = context->vmbus.gpadls;
            
            context->vmbus.gpadls = gpadl;
            
            if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("[" __FUNCTION__ "] Received VMBUS_MSG_CREATE_GPADL id: %d channel: %d\n", message->gpadl_header.gpadl_id, message->gpadl_header.channel_id);
            
            for(u32 page_index = 0; page_index < number_of_pages; page_index++){
                gpadl->pages[page_index] = gpa_range->pfn_array[page_index];
                if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("[" __FUNCTION__ "]     [%d] 0x%p\n", page_index, gpa_range->pfn_array[page_index]);
            }
            
            struct{
                u32 message_type;
                u32 reserved;
                u32 channel_id;
                u32 gpadl_id;
                u32 status;
            } gpadl_created = {
                .message_type = /*VMBUS_MSG_GPADL_CREATED*/10,
                .channel_id = message->gpadl_header.channel_id,
                .gpadl_id = message->gpadl_header.gpadl_id,
            };
            
            sint_post_message(context, /*VMBUS_SINT*/2, /*HV_MESSAGE_VMBUS*/1, &gpadl_created, sizeof(gpadl_created));
            
            if(gpadl->next && gpadl->next->next == null && context->use_hypervisor){
                // :vmbus_tsc_frequency_hack
                // 
                // We are the first gpadl, patch in the _correct_ value for the tsc frequency.
                // The guest should now have initialized the vmbus.
                
                if(context->registers.hv_x64_msr_reference_tsc_page & 1){
                    u64 physical_address = context->registers.hv_x64_msr_reference_tsc_page & ~0xfff;
                    u8 *tsc_page = get_physical_memory_for_write(context, physical_address);
                    
                    u64 old_time = calculate_time_reference_counter(context, &context->registers);
                    
                    u64 tsc_frequency = calculate_tsc_frequency();
                    
                    u64 remainder;
                    u64 scale = _udiv128(/*high*/10000000, /*low*/0, tsc_frequency, &remainder); // @cleanup: Make sure this does not crash?
                    
                    if(PRINT_TIMER_EVENTS) print("Reversing tsc hack now tsc frequency at 0x%llx tsc scale 0x%llx\n", tsc_frequency, scale);
                    
                    *(u64 *)(tsc_page + 0) += 1;
                    *(u64 *)(tsc_page + 8)  = scale;
                    
                    u64 new_time = calculate_time_reference_counter(context, &context->registers);
                    
                    *(u64 *)(tsc_page + 16) = old_time - new_time;
                }
            }
        }break;
        
        case /*VMBUS_MSG_OPEN_CHANNEL*/5:{
            
            if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("[" __FUNCTION__ "] Received VMBUS_MSG_OPEN_CHANNEL open id: %d channel id: %d gpadl id: %d read pages: %d\n", message->open_channel.open_id, message->open_channel.channel_id, message->open_channel.ring_buffer_gpadl_id, message->open_channel.read_ring_buffer_pages);
            
            struct vmbus_channel *channel = context->vmbus.channels;
            for(; channel; channel = channel->next){
                if(message->open_channel.channel_id == channel->channel_id) break;
            }
            crash_assert(channel);
            
            struct gpadl *gpadl = context->vmbus.gpadls;
            for(; gpadl; gpadl = gpadl->next){
                if(gpadl->gpadl_id == message->open_channel.ring_buffer_gpadl_id && gpadl->channel_id == message->open_channel.channel_id) break;
            }
            crash_assert(gpadl);
            
            u32 read_ring_buffer_pages = message->open_channel.read_ring_buffer_pages;
            
            channel->gpadl_id = gpadl->gpadl_id;
            channel->read_ring_buffer_pages = read_ring_buffer_pages;
            
            vmbus_channel_initialize_ringbuffers(channel, gpadl);
            
            u8 *send_buffer_header = get_physical_memory_for_write(context, channel->send_buffer.header);
            
            // :feat_pending_send_sz
            // "feat_pending_send_sz" - We (claim we) will send an interrupt if the ring-buffer goes from being full 
            //                          to being able to handle a message of size 'pending_send_sz'. 
            //                          Another member of the ringbuffer we don't do anything with.
            *(u8 *)(send_buffer_header + 0x40) = 1; 
            
            struct{
                u32 message_type;
                u32 reserved;
                
                u32 channel_id;
                u32 open_id;
                u32 status;
            } open_channel_result = {
                .message_type = /*VMBUS_MSG_OPENCHANNEL_RESULT*/6,
                .channel_id = message->open_channel.channel_id,
                .open_id = message->open_channel.open_id,
            };
            
            sint_post_message(context, /*VMBUS_SINT*/2, /*HV_MESSAGE_VMBUS*/1, &open_channel_result, sizeof(open_channel_result));
            
            if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("     >>> %s\n", vmbus_device_kind_string[channel->device_kind]);
            if(channel->device_kind == VMBUS_DEVICE_mouse)    context->vmbus.mouse = channel;
            if(channel->device_kind == VMBUS_DEVICE_keyboard) context->vmbus.keyboard = channel;
        }break;
        
        case /*CLOSECHANNEL*/7:{
            if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("     close channel %u\n",  message->close_channel.child_relid);
        }break;
        
        case /*GPADL_TEARDOWN*/11:{
            if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("     teardown gpadl %u %u\n", message->teardown.child_id, message->teardown.gpadl_id);
            
            struct{
                u32 message_type;
                u32 reserved;
                
                u32 gpadl_id;
            } message_gpadl_torndown = {
                .message_type = /*VMBUSS_MSG_GPADL_TORNDOWN*/12,
                .gpadl_id = message->teardown.gpadl_id,
            };
            
            sint_post_message(context, /*VMBUS_SINT*/2, /*HV_MESSAGE_VMBUS*/1, &message_gpadl_torndown, sizeof(message_gpadl_torndown));
        }break;
        
        default:{
            set_crash_information(context, CRASH_internal_error, (u64)"Unimplemented post HV_MESSAGE_VMBUS (1) message type.");
        }break;
    }
}

void vmbus_handle_event(struct context *context, u32 connection_id){
    
    context->scratch_arena.current = context->scratch_arena.base; // Reset the `scratch_arena`.
    
    // 
    // Find the packet inside the ringbuffer.
    // 
    struct vmbus_channel *channel = context->vmbus.channels;
    for(; channel; channel = channel->next){
        if(channel->connection_id == connection_id) break;
    }
    crash_assert(channel);
    
    struct vmbus_packet_description *vmbus_packet = vmbus_read_packet(&context->scratch_arena, context, channel);
    if(!vmbus_packet) return; // @cleanup: This happened for some weird channel which did not have a 'gpadl_id'?
    
    u64 packet_data_offset = vmbus_packet->PacketDataOffsetDiv8 << 3;
    u64 packet_length      = (vmbus_packet->PacketLengthDiv8 << 3) + 8;
    (void)packet_length;
    
    if(PRINT_VMBUS_EVENTS) print("["__FUNCTION__"] DeviceKind %x\n", channel->device_kind);
    
    switch(channel->device_kind){
        case VMBUS_DEVICE_unknown:{
            
        }break;
        
        case VMBUS_DEVICE_scsi:{
            
            // 
            // Handle the packet.
            // 
            struct{
                u32 operation;
                u32 flags;
                u32 status;
                
                union{
                    struct{
                        u8 minor; // @note: for some reason they have the version as a u16. Maybe this order is wrong for big endian machines?
                        u8 major;
                        u16 revision;
                    } version;
                    
                    struct{
                        u32 reserved;
                        u16 max_channel_cnt;
                        u16 reserved2;
                        u32 _flags;
                        u32 max_transfer_bytes;
                    } properties;
                    
                    struct vmscsi_request{
                        u16 Length;
                        u8  srb_status;
                        u8  scsi_status;
                        
                        u8  port_number;
                        u8  path_id;
                        u8  target_id;
                        u8  lun;
                        
                        u8  cdb_length;
                        u8  sense_info_length;
                        u8  data_in;
                        u8  reserved;
                        
                        u32 data_transfer_length;
                        
                        union{
                            u8 cdb[0x10];
                            u8 sense_buffer[0x14];
                        };
                        
                        struct{
                            u16 reserve;
                            u8 queue_tag;
                            u8 queue_action;
                            u32 srb_flags;
                            u32 time_out_value;
                            u32 queue_sort_ey;
                        } win8_extension;
                        
                    } vmscsi_request;
                    
                    u8 data[0x34];
                };
            } *vstor_packet = (void *)((u8 *)vmbus_packet + packet_data_offset);
            
            u32 operation = vstor_packet->operation;
            u32 packet_type = vmbus_packet->PacketType;
            
            vmbus_packet->PacketType = /*VMBUS_PACKET_COMP*/0xb;
            vmbus_packet->PacketFlags = 0;
            vstor_packet->operation = 1;
            vstor_packet->flags = 1;
            
            switch(operation){
                case /*VSTOR_OPERATION_BEGIN_INITIALIZATION*/7:
                case /*VSTOR_OPERATION_END_INITIALIZATION*/8:
                case /*VSTOR_OPERATION_QUERY_PROTOCOL_VERSION*/9:{
                    // @note: I have no idea why this packet exists.
                    //        We will just reply "sure".
                    
                    if(operation == 9){
                        vstor_packet->status = (vstor_packet->version.minor == 2 && vstor_packet->version.major == 6) ? 0 : 0xc0000059;
                        if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("["__FUNCTION__"] VSTOR_OPERATION_QUERY_PROTOCOL_VERSION %d.%d -> status = 0x%x\n", vstor_packet->version.major, vstor_packet->version.minor, vstor_packet->status);
                    }else{
                        if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("["__FUNCTION__"] VSTOR_OPERATION_%s_INITIALIZATION\n", operation == 7 ? "BEGIN" : "END");
                    }
                    
                    vmbus_send_packet(context, channel, vmbus_packet);
                }break;
                
                case /*VSTOR_OPERATION_QUERY_PROPERTIES*/10:{
                    
                    if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("["__FUNCTION__"] VSTOR_OPERATION_QUERY_PROPERTIES\n");
                    
                    vstor_packet->properties.max_transfer_bytes = 0x800000;
                    
                    vmbus_send_packet(context, channel, vmbus_packet);
                }break;
                
                case /*VSTOR_OPERATION_EXECUTE_SRB*/3:{
                    struct vmscsi_request *vm_scsi_command = &vstor_packet->vmscsi_request;
                    
                    vm_scsi_command->srb_status = /*SRB_STATUS_SUCCESS*/1;
                    
                    
                    if(PRINT_VMBUS_EVENTS){
                        print("\n");
                        print("   VSTOR_OPERATION_EXECUTE_SRB {flags 0x%x%s, status 0x%x}\n", vstor_packet->flags, (vstor_packet->flags & 1) ? " (REQUEST_COMPLETION_FLAG)" : "" , vstor_packet->status);
                        print("{\n");
                        print("    port                    %d\n",      vm_scsi_command->port_number);
                        print("    path_id                 %d\n",      vm_scsi_command->path_id);
                        print("    target_id               %d\n",      vm_scsi_command->target_id);
                        print("    lun                     %d\n",      vm_scsi_command->lun);        // Logical unit number
                        print("    cdb_length            0x%x\n",      vm_scsi_command->cdb_length); // Command description block
                        print("    sense_info_length     0x%x\n",      vm_scsi_command->sense_info_length);
                        print("    data_in               0x%x (%s)\n", vm_scsi_command->data_in, vm_scsi_command->data_in <= 2 ? (vm_scsi_command->data_in == 0 ? "WRITE_TYPE" : (vm_scsi_command->data_in == 1 ? "READ_TYPE" : "UNKNOWN_TYPE")) : "????");
                        print("    data_transfer_length  0x%x\n",      vm_scsi_command->data_transfer_length);
                        print("}\n");
                        
                        if(vm_scsi_command->cdb_length > 0){
                            u8 *cdb = vm_scsi_command->cdb;
                            
                            // https://www.seagate.com/files/staticfiles/support/docs/manual/Interface%20manuals/100293068j.pdf
                            
                            static char *scsi_command_strings[] = {
                                [0x00] = "TEST UNIT READY",
                                [0x01] = "REWIND",
                                [0x03] = "REQUEST SENSE",
                                [0x04] = "FORMAT",
                                [0x05] = "READ BLOCK LIMITS",
                                [0x07] = "REASSIGN BLOCKS",
                                // [0x07] = "INITIALIZE ELEMENT STATUS",
                                [0x08] = "READ(6)",
                                [0x0A] = "WRITE(6)",
                                [0x0B] = "SEEK(6)",
                                [0x0F] = "READ REVERSE(6)",
                                [0x10] = "WRITE FILEMARKS(6)",
                                [0x11] = "SPACE(6)",
                                [0x12] = "INQUIRY",
                                [0x13] = "VERIFY(6)",
                                [0x14] = "RECOVER BUFFERED DATA",
                                [0x15] = "MODE SELECT(6)",
                                [0x16] = "RESERVE(6)",
                                [0x17] = "RELEASE(6)",
                                [0x18] = "COPY",
                                [0x19] = "ERASE (6)",
                                [0x1A] = "MODE SENSE (6)",
                                [0x1B] = "START STOP UNIT",
                                // [0x1B] = "LOAD UNLOAD",
                                [0x1C] = "RECEIVE DIAGNOSTIC RESULTS",
                                [0x1D] = "SEND DIAGNOSTIC",
                                [0x1E] = "PREVENT ALLOW MEDIUM REMOVAL",
                                [0x23] = "READ FORMAT CAPACITIES",
                                [0x25] = "READ CAPACITY(10)",
                                [0x28] = "READ(10)",
                                [0x29] = "READ GENERATION",
                                [0x2A] = "WRITE(10)",
                                [0x2B] = "SEEK(10)",
                                // [0x2B] = "LOCATE(10)",
                                [0x2C] = "ERASE(10)",
                                [0x2D] = "READ UPDATED BLOCK",
                                [0x2E] = "WRITE AND VERIFY(10)",
                                [0x2F] = "VERIFY(10)",
                                [0x33] = "SET LIMITS(10)",
                                // [0x34] = "PRE-FETCH(10)",
                                [0x34] = "READ POSITION",
                                [0x35] = "SYNCHRONIZE CACHE(10)",
                                [0x36] = "LOCK UNLOCK CACHE(10)",
                                // [0x37] = "READ DEFECT DATA(10)",
                                [0x37] = "INITIALIZE ELEMENT STATUS WITH RANGE",
                                [0x38] = "MEDIUM SCAN",
                                [0x39] = "COMPARE",
                                [0x3A] = "COPY AND VERIFY",
                                [0x3B] = "WRITE BUFFER",
                                [0x3C] = "READ BUFFER",
                                [0x3D] = "UPDATE BLOCK",
                                [0x3E] = "READ LONG(10)",
                                [0x3F] = "WRITE LONG(10)",
                                [0x40] = "CHANGE DEFINITION",
                                [0x41] = "WRITE SAME(10)",
                                [0x42] = "UNMAP",
                                [0x43] = "READ TOC/PMA/ATIP",
                                [0x44] = "REPORT DENSITY SUPPORT",
                                [0x45] = "PLAY AUDIO(10)",
                                [0x46] = "GET CONFIGURATION",
                                [0x47] = "PLAY AUDIO MSF",
                                [0x48] = "SANITIZE",
                                [0x4A] = "GET EVENT STATUS NOTIFICATION",
                                [0x4B] = "PAUSE/RESUME",
                                [0x4C] = "LOG SELECT",
                                [0x4D] = "LOG SENSE",
                                [0x50] = "XDWRITE(10)",
                                // [0x51] = "XPWRITE(10)",
                                [0x51] = "READ DISC INFORMATION",
                                [0x52] = "XDREAD(10)",
                                [0x53] = "XDWRITEREAD(10)",
                                [0x54] = "SEND OPC INFORMATION",
                                [0x55] = "MODE SELECT(10)",
                                [0x56] = "RESERVE(10)",
                                [0x57] = "RELEASE(10)",
                                [0x58] = "REPAIR TRACK",
                                [0x5A] = "MODE SENSE(10)",
                                [0x5B] = "CLOSE TRACK/SESSION",
                                [0x5C] = "READ BUFFER CAPACITY",
                                [0x5D] = "SEND CUE SHEET",
                                [0x5E] = "PERSISTENT RESERVE IN",
                                [0x5F] = "PERSISTENT RESERVE OUT",
                                [0x7E] = "extended CDB",
                                [0x7F] = "variable length CDB",
                                [0x80] = "XDWRITE EXTENDED(16)",
                                // [0x80] = "WRITE FILEMARKS(16)",
                                [0x81] = "READ REVERSE(16)",
                                [0x83] = "Third-party Copy OUT commands",
                                [0x84] = "Third-party Copy IN commands",
                                [0x85] = "ATA PASS-THROUGH(16)",
                                [0x86] = "ACCESS CONTROL IN",
                                [0x87] = "ACCESS CONTROL OUT",
                                [0x88] = "READ(16)",
                                [0x89] = "COMPARE AND WRITE",
                                [0x8A] = "WRITE(16)",
                                [0x8B] = "ORWRITE",
                                [0x8C] = "READ ATTRIBUTE",
                                [0x8D] = "WRITE ATTRIBUTE",
                                [0x8E] = "WRITE AND VERIFY(16)",
                                [0x8F] = "VERIFY(16)",
                                [0x90] = "PRE-FETCH(16)",
                                [0x91] = "SYNCHRONIZE CACHE(16)",
                                // [0x91] = "SPACE(16)",
                                [0x92] = "LOCK UNLOCK CACHE(16)",
                                // [0x92] = "LOCATE(16)",
                                [0x93] = "WRITE SAME(16)",
                                // [0x93] = "ERASE(16)",
                                [0x9D] = "SERVICE ACTION BIDIRECTIONAL",
                                [0x9E] = "SERVICE ACTION IN(16)",
                                [0x9F] = "SERVICE ACTION OUT(16)",
                                [0xA0] = "REPORT LUNS",
                                [0xA1] = "ATA PASS-THROUGH(12)",
                                [0xA2] = "SECURITY PROTOCOL IN",
                                [0xA3] = "MAINTENANCE IN",
                                // [0xA4] = "MAINTENANCE OUT",
                                [0xA4] = "REPORT KEY",
                                [0xA5] = "MOVE MEDIUM",
                                // [0xA5] = "PLAY AUDIO 12",
                                [0xA6] = "EXCHANGE MEDIUM",
                                [0xA7] = "MOVE MEDIUM ATTACHED",
                                [0xA8] = "READ(12)",
                                [0xA9] = "SERVICE ACTION OUT(12)",
                                [0xAA] = "WRITE(12)",
                                [0xAB] = "SERVICE ACTION IN(12)",
                                [0xAC] = "ERASE(12)",
                                [0xAD] = "READ DVD STRUCTURE",
                                [0xAE] = "WRITE AND VERIFY(12)",
                                [0xAF] = "VERIFY(12)",
                                [0xB0] = "SEARCH DATA HIGH(12)",
                                [0xB1] = "SEARCH DATA EQUAL(12)",
                                [0xB2] = "SEARCH DATA LOW(12)",
                                [0xB3] = "SET LIMITS(12)",
                                [0xB4] = "READ ELEMENT STATUS ATTACHED",
                                [0xB5] = "SECURITY PROTOCOL OUT",
                                [0xB6] = "SEND VOLUME TAG",
                                [0xB7] = "READ DEFECT DATA(12)",
                                [0xB8] = "READ ELEMENT STATUS",
                                [0xB9] = "READ CD MSF",
                                [0xBA] = "REDUNDANCY GROUP (IN)",
                                [0xBB] = "REDUNDANCY GROUP (OUT)",
                                [0xBC] = "SPARE (IN)",
                                [0xBD] = "SPARE (OUT)",
                                [0xBE] = "VOLUME SET (IN)",
                                [0xBF] = "VOLUME SET (OUT)",
                            };
                            
                            char *command_name_string = (cdb[0] < array_count(scsi_command_strings) && scsi_command_strings[cdb[0]])  ? scsi_command_strings[cdb[0]] : "???";
                            
                            print("cdb[0] = 0x%x (%s)\n", cdb[0], command_name_string);
                            if(cdb[0] == /*WRITE(16)*/0x8a || cdb[0] == /*READ(16)*/0x88){
                                print("{Flags %x, LogicaBlockAddress %llx, Transfer Length %lx, Group %x, Control %x}\n",
                                        cdb[1], byteswap_u64(*(u64 *)(cdb + 2)), byteswap_u32(*(u32 *)(cdb + 10)), cdb[14], cdb[15]);
                            }
                        }
                    }
                    
                    
                    
                    if(vm_scsi_command->cdb_length > 0){
                        //
                        // We have a 'Command Description Block' the first byte is a SCSI command code, check 
                        //     https://www.seagate.com/files/staticfiles/support/docs/manual/Interface%20manuals/100293068j.pdf
                        // for a description of all commands.
                        //
                        u8 *cdb = vm_scsi_command->cdb;
                        
                        switch(cdb[0]){
                            
                            case 0x00:{ // TEST_UNIT_READY
                                
                            }break;
                            
                            case 0x35:{ // SYNCHRONIZE CACHE(10)
                                // u8  Flags = cdb[1];
                                // u32 LogicalBlockAddress = *(u32 *)(cdb +  2);
                                // u32 NumberOfBlocks = *(u16 *)(cdb + 7);
                                
                                // @note: I don't think this is ever relevant for us.
                            }break;
                            
                            case 0x42:{ // UNMAP
                                // Invoked by trim ioctl, not sure I think this does not do much?
                            }break;
                            
                            case 0x4d:{ // LOG SENSE
                                // @cleanup: Do we need to implement this?
                            }break;
                            
                            case 0x28:  // READ(10)
                            case 0x88:{ // READ(16)
                                
                                // u8  Flags = cdb[1];
                                u64 LogicalBlockAddress = 0;
                                u32 TransferLengthInBlocks = 0; 
                                
                                // u32 GroupNumber = cdb[14];
                                // u32 Control = cdb[15];
                                
                                if(cdb[0] == 0x88){
                                    LogicalBlockAddress = byteswap_u64(*(u64 *)(cdb +  2));
                                    TransferLengthInBlocks = byteswap_u32(*(u32 *)(cdb + 10));
                                }else if(cdb[0] == 0x28){
                                    LogicalBlockAddress = byteswap_u32(*(u32 *)(cdb +  2));
                                    TransferLengthInBlocks = byteswap_u16(*(u16 *)(cdb + 7));
                                }else{
                                    crash_assert(0);
                                }
                                
                                if(!globals.disk_info.mapped_address){
                                    set_crash_information(context, CRASH_internal_error, (u64)"Disk Access!");
                                    return;
                                }
                                
                                u64 TransferLengthInBytes  = (u64)TransferLengthInBlocks * globals.disk_info.sector_size_in_bytes;
                                
                                //
                                // Reading Sectors [LogicalBlockAddress, LogicalBlockAddress + TransferLengthInBlocks)
                                // into a temporary memory buffer.
                                //
                                u8 *temp = disk_read_sectors(&context->scratch_arena, TransferLengthInBlocks, LogicalBlockAddress);
                                
                                if(context != globals.main_thread_context){
                                    // First apply the writes which were applied prior to fuzzing.
                                    disk_apply_temporary_writes(globals.main_thread_context, temp, LogicalBlockAddress, TransferLengthInBlocks);
                                }
                                
                                disk_apply_temporary_writes(context, temp, LogicalBlockAddress, TransferLengthInBlocks);
                                
                                crash_assert(packet_type == /*VM_PKT_DATA_USING_GPA_DIRECT*/9);
                                struct{
                                    u32 reserved;
                                    u32 rangecount;
                                    
                                    u8 ranges[];
                                } *gpa_descriptor = (void *)(vmbus_packet + 1);
                                
                                u32 RangeOffset = 0;
                                u32 TransferAt  = 0; 
                                for(u32 RangeIndex = 0; (RangeIndex < gpa_descriptor->rangecount) && (TransferAt < TransferLengthInBytes); RangeIndex++){
                                    
                                    struct {
                                        u32 Length;
                                        u32 Offset;
                                        u64 PageFrameNumbers[1];
                                    } *Range = (void *)(gpa_descriptor->ranges + RangeOffset);
                                    
                                    u32 RangeLength = Range->Length;
                                    
                                    u32 NumberOfPagesToWrite = (Range->Offset + RangeLength + (0x1000 - 1))/0x1000;
                                    
                                    for(u32 PageIndex = 0; (PageIndex < NumberOfPagesToWrite) && (TransferAt < TransferLengthInBytes); PageIndex++){
                                        u32 Offset = (PageIndex == 0) ? Range->Offset : 0;
                                        u32 Length = (PageIndex == (NumberOfPagesToWrite - 1)) ? RangeLength : 0x1000 - Offset;
                                        u64 PageFrameNumber = Range->PageFrameNumbers[PageIndex];
                                        
                                        crash_assert(Offset + Length <= 0x1000);
                                        u32 ReadLength = (u32)((TransferLengthInBytes > Length) ? Length : TransferLengthInBytes);
                                        
                                        u64 PhysicalAddress = (PageFrameNumber << 12) + Offset;
                                        u8 *PhysicalMemory = get_physical_memory_for_write(context, PhysicalAddress);
                                        
                                        memcpy(PhysicalMemory, temp + TransferAt, ReadLength);
                                        
                                        if(PRINT_DISK_EVENTS) print("[Disk] Read 0x%x into %p from %p\n", ReadLength, PhysicalAddress, LogicalBlockAddress * globals.disk_info.sector_size_in_bytes + TransferAt);
                                        
                                        TransferAt  += ReadLength;
                                        RangeLength -= ReadLength;
                                    }
                                    
                                    RangeOffset += 2 * sizeof(u32) + NumberOfPagesToWrite * sizeof(u64);
                                }
                                
                            }break;
                            
                            case 0x2a:
                            case 0x8a:{ // WRITE(16)
                                // u8  Flags = cdb[1];
                                u64 LogicalBlockAddress    = 0;
                                u32 TransferLengthInBlocks = 0;
                                // u32 GroupNumber = cdb[14];
                                // u32 Control = cdb[15];
                                
                                if(cdb[0] == 0x8a){
                                    LogicalBlockAddress = byteswap_u64(*(u64 *)(cdb +  2));
                                    TransferLengthInBlocks = byteswap_u32(*(u32 *)(cdb + 10));
                                }else if(cdb[0] == 0x2a){
                                    LogicalBlockAddress = byteswap_u32(*(u32 *)(cdb +  2));
                                    TransferLengthInBlocks = byteswap_u16(*(u16 *)(cdb + 7));
                                }else{
                                    crash_assert(0);
                                }
                                
                                crash_assert(packet_type == /*VM_PKT_DATA_USING_GPA_DIRECT*/9);
                                
                                u64 TransferLengthInBytes = TransferLengthInBlocks * globals.disk_info.sector_size_in_bytes;
                                u8 *Buffer = push_data(&context->scratch_arena, u8, TransferLengthInBytes); // @note: Gets copied in `disk_register_temporary_write`.
                                
                                struct{
                                    u32 reserved;
                                    u32 rangecount;
                                    
                                    u8 ranges[];
                                } *gpa_descriptor = (void *)(vmbus_packet + 1);
                                
                                u32 RangeOffset = 0;
                                u32 TransferAt  = 0; 
                                for(u32 RangeIndex = 0; (RangeIndex < gpa_descriptor->rangecount) && (TransferAt < TransferLengthInBytes); RangeIndex++){
                                    
                                    struct {
                                        u32 Length;
                                        u32 Offset;
                                        u64 PageFrameNumbers[1];
                                    } *Range = (void *)(gpa_descriptor->ranges + RangeOffset);
                                    
                                    u32 RangeLength = Range->Length;
                                    
                                    u32 NumberOfPagesToRead = (Range->Offset + RangeLength + (0x1000 - 1))/0x1000;
                                    
                                    for(u32 PageIndex = 0; (PageIndex < NumberOfPagesToRead) && (TransferAt < TransferLengthInBytes); PageIndex++){
                                        u32 Offset = (PageIndex == 0) ? Range->Offset : 0;
                                        u32 Length = (PageIndex == (NumberOfPagesToRead - 1)) ? RangeLength : 0x1000 - Offset;
                                        u64 PageFrameNumber = Range->PageFrameNumbers[PageIndex];
                                        
                                        crash_assert(Offset + Length <= 0x1000);
                                        u32 ReadLength = (u32)((TransferLengthInBytes > Length) ? Length : TransferLengthInBytes);
                                        
                                        u64 PhysicalAddress = (PageFrameNumber << 12) + Offset;
                                        u8 *PhysicalMemory = get_physical_memory_for_read(context, PhysicalAddress);
                                        
                                        memcpy(Buffer + TransferAt, PhysicalMemory, ReadLength);
                                        
                                        if(PRINT_DISK_EVENTS) print("[Disk] Wrote 0x%x bytes from %p to %p\n", ReadLength, PhysicalAddress, LogicalBlockAddress * globals.disk_info.sector_size_in_bytes + TransferAt);
                                        
                                        TransferAt  += ReadLength;
                                        RangeLength -= ReadLength;
                                    }
                                    
                                    RangeOffset += 2 * sizeof(u32) + NumberOfPagesToRead * sizeof(u64);
                                }
                                
                                disk_register_temporary_write(context, Buffer, LogicalBlockAddress, TransferLengthInBlocks);
                            }break;
                            
                            case 0x25:{ // READ CAPACITY (10)
                                
                                crash_assert(packet_type == /*VM_PKT_DATA_USING_GPA_DIRECT*/9);
                                struct{
                                    u32 reserved;
                                    u32 rangecount;
                                    
                                    // first range, we only need one.
                                    u32 Length;
                                    u32 Offset;
                                    u64 PageFrameNumber;
                                } *gpa_descriptor = (void *)(vmbus_packet + 1);
                                
                                u64 physical_address = (gpa_descriptor->PageFrameNumber * 0x1000) + gpa_descriptor->Offset;
                                
                                crash_assert(physical_address < context->physical_memory_size);
                                
                                u64 lba = (globals.disk_info.virtual_size / 0x200) - 1;
                                if(lba > 0xffffffff) lba = 0xffffffff;
                                
                                guest_write_physical(u32, physical_address + 0, byteswap_u32((u32)lba));
                                guest_write_physical(u32, physical_address + 4, byteswap_u32(0x200));
                            }break;
                            
                            case 0xa0:{ // REPORT LUNS
                                // u8 select_report = cdb[2];
                                u32 allocation_length = byteswap_u32(*(u32 *)(cdb + 6));
                                // u8 control = cdb[11];
                                
                                crash_assert(packet_type == /*VM_PKT_DATA_USING_GPA_DIRECT*/9);
                                struct{
                                    u32 reserved;
                                    u32 rangecount;
                                    
                                    // first range, we only need one.
                                    u32 Length;
                                    u32 Offset;
                                    u64 PageFrameNumber;
                                } *gpa_descriptor = (void *)(vmbus_packet + 1);
                                
                                u64 physical_address = (gpa_descriptor->PageFrameNumber * 0x1000) + gpa_descriptor->Offset;
                                
                                crash_assert(physical_address < context->physical_memory_size);
                                
                                crash_assert(allocation_length >= 0x10);
                                
                                if(vm_scsi_command->target_id == 0 && vm_scsi_command->path_id == 0){
                                    // 
                                    // @note: We only have one LUN (the vhdx). 
                                    // 
                                    
                                    guest_write_physical(u32, physical_address + 0, byteswap_u32(0x8));  // LUN LIST LENGTH (in bytes)
                                    guest_write_physical(u32, physical_address + 4, 0); // Reserved
                                    guest_write_physical(u64, physical_address + 4, 0); // LUN 0.
                                }else{
                                    guest_write_physical(u32, physical_address + 0, byteswap_u32(0));  // LUN LIST LENGTH (in bytes)
                                    guest_write_physical(u32, physical_address + 4, 0); // Reserved
                                    guest_write_physical(u64, physical_address + 4, 0); // LUN 0.
                                }
                            }break;
                            
                            case 0x12:{ // INQUERY
                                
                                u8 enable_vital_product_data = (cdb[1] & 1);
                                u8 page_code = cdb[2];
                                u16 allocation_length = byteswap_u16(*(u16 *)(cdb + 3));
                                
                                crash_assert(packet_type == /*VM_PKT_DATA_USING_GPA_DIRECT*/9);
                                struct{
                                    u32 reserved;
                                    u32 rangecount;
                                    
                                    // first range, we only need one.
                                    u32 Length;
                                    u32 Offset;
                                    u64 PageFrameNumber;
                                } *gpa_descriptor = (void *)(vmbus_packet + 1);
                                
                                u64 physical_address = (gpa_descriptor->PageFrameNumber * 0x1000) + gpa_descriptor->Offset;
                                
                                crash_assert(physical_address < context->physical_memory_size);
                                
                                u8 *buffer = push_data(&context->scratch_arena, u8, allocation_length);
                                
                                if(!enable_vital_product_data){
                                    
                                    crash_assert(allocation_length >= 0x24);
                                    
                                    buffer[2] = 5; // Version
                                    buffer[3] = 2; // Response data format
                                    buffer[4] = 0x1f; // additional length
                                    buffer[7] = 2; // cmdque
                                    memcpy(buffer + 8, "Msft    Virtual Disk    1.0 ", 0x1c);
                                    
                                }else{
                                    switch(page_code){
                                        case 0:{
                                            crash_assert(allocation_length >= 9);
                                            
                                            // supported vital product data pages
                                            buffer[0] = 0;
                                            buffer[1] = 0;
                                            buffer[2] = 0;
                                            buffer[3] = 5; // number of pages
                                            
                                            buffer[4]  = 0x00; // page 00 - supported vital product pages
                                            buffer[5]  = 0x83; // page 83 - Device Identification
                                            // buffer[6]  = 0x8f; // page 8f - ???
                                            buffer[6]  = 0xb0; // page b0 - Block Limits
                                            buffer[7]  = 0xb1; // page b1 - Block device characteristics
                                            buffer[8]  = 0xb2; // page b2 - Logical Block Provisioning
                                            // buffer[10] = 0xce; // page ce - 
                                            // buffer[11] = 0xcf; // page cf
                                        }break;
                                        
                                        case 0x83:{
                                            crash_assert(allocation_length >= 0x34);
                                            
                                            buffer[0] = 0;
                                            buffer[1] = 0x83;
                                            *(u16 *)(buffer + 2) = byteswap_u16(0x30); // length
                                            
                                            buffer[4] = 1; // binary values
                                            buffer[5] = 1; // Vendor ID
                                            buffer[6] = 0; // Reserved 
                                            buffer[7] = 0x18; // Size
                                            memcpy(buffer + 8, "MSFT    ", 8);
                                            
                                            // @cleanup: what exactly is this ?
                                            static u8 vendor_guid[] = { 0x5f, 0x2e, 0x81, 0xa7, 0xf7, 0x19, 0xde, 0x4c, 0x81, 0x29, 0x08, 0xe5, 0xfc, 0x86, 0x21, 0x2c};
                                            memcpy(buffer+ 16, vendor_guid, 16);
                                            
                                            
                                            buffer[0x20] = 1; // binary values
                                            buffer[0x21] = 3; // Name_Identifier (?)
                                            buffer[0x22] = 0; // reserved
                                            buffer[0x23] = 0x10; // size
                                            static u8 name_identifier[] = {0x60, 0x02, 0x24, 0x80, 0x5f, 0x2e, 0x81, 0xa7, 0xf7, 0x19, 0x08, 0xe5, 0xfc, 0x86, 0x21, 0x2c};
                                            memcpy(buffer + 0x24, name_identifier, 16);
                                            
                                            // @note: the last 6 bytes of the two identifiers match... ?
                                        }break;
                                        
                                        case 0xb0:{
                                            crash_assert(allocation_length >= 64);
                                            
                                            buffer[0] = 0;
                                            buffer[1] = 0xb0;
                                            *(u16 *)(buffer + 2) = byteswap_u16(0x3c);  // length
                                            
                                            buffer[4] = 0; // reserved
                                            buffer[5] = 1; // maximum compare and write length (?)
                                            *(u16 *)(buffer + 6) = 0; // Optimal Transfer length granularity
                                            *(u32 *)(buffer + 8) = 0; // Maximum Transfer length
                                            *(u32 *)(buffer + 12) = 0; // Optimal Transfer length
                                            *(u32 *)(buffer + 16) = 0; // Maximum Prefetch length
                                            *(u32 *)(buffer + 20) = 0xffffffff; // Maximum Unmap LBA count
                                            *(u32 *)(buffer + 24) = byteswap_u32(0x1000); // Maximum Unmap block descriptor count length
                                            *(u32 *)(buffer + 28) = byteswap_u32(0x100000); // Optimal Unmap granularity
                                            *(u32 *)(buffer + 32) = byteswap_u32(0x80000000); // Maximum Unmap block descriptor count length
                                            *(u64 *)(buffer + 36) = byteswap_u64(0x4000); // Maximum write same length
                                            *(u32 *)(buffer + 44) = 0; // Maximum atomic transfer length
                                            *(u32 *)(buffer + 48) = 0; // Atomic alignment
                                            *(u32 *)(buffer + 52) = 0; 
                                            *(u32 *)(buffer + 56) = 0; 
                                            *(u32 *)(buffer + 60) = 0; 
                                        }break;
                                        
                                        case 0xb1:{
                                            crash_assert(allocation_length >= 0x40);
                                            
                                            buffer[0] = 0;
                                            buffer[1] = 0xb1;
                                            *(u16 *)(buffer + 2) = byteswap_u16(0x3c);  // length
                                            
                                            memset(buffer + 4, 0, 0x3c);
                                        }break;
                                        
                                        case 0xb2:{
                                            crash_assert(allocation_length >= 8);
                                            
                                            buffer[0] = 0;
                                            buffer[1] = 0xb2;
                                            *(u16 *)(buffer + 2) = byteswap_u16(4); // length
                                            
                                            buffer[4] = 1; // threshold exponent 
                                            buffer[5] = 0; // 0x80; // supports UNMAP command ... do we actually want this?
                                            buffer[6] = 2; // thin provisioned
                                            buffer[7] = 0;
                                        }break;
                                        
                                        default:{
                                            set_crash_information(context, CRASH_internal_error, (u64)"Unhandled vital data page (SCSI).");
                                        }break;
                                    }
                                }
                                
                                write_physical_memory(context, physical_address, buffer, allocation_length);
                            }break;
                            
                            case 0x1a:{ // MODE SENSE (6)
                                u8 page_code = cdb[2];
                                u8 subpage_code = cdb[3];
                                u8 allocation_length = cdb[4];
                                
                                crash_assert(packet_type == /*VM_PKT_DATA_USING_GPA_DIRECT*/9);
                                struct{
                                    u32 reserved;
                                    u32 rangecount;
                                    
                                    // first range, we only need one.
                                    u32 Length;
                                    u32 Offset;
                                    u64 PageFrameNumber;
                                } *gpa_descriptor = (void *)(vmbus_packet + 1);
                                
                                u64 physical_address = (gpa_descriptor->PageFrameNumber * 0x1000) + gpa_descriptor->Offset;
                                
                                crash_assert(physical_address < context->physical_memory_size);
                                
                                u8 *buffer = push_data(&context->scratch_arena, u8, allocation_length);
                                
                                if(page_code == /*MODE_PAGE_CONTROL*/0xa && subpage_code == 0){
                                    vstor_packet->status = 0xc0000001;
                                    vm_scsi_command->srb_status = 0;
                                }else if(page_code == 0x1c && subpage_code == 0){
                                    vstor_packet->status = 0xc0000001;
                                    vm_scsi_command->srb_status = 0;
                                }else if(page_code == /*MODE_PAGE_CACHING*/0x8 && subpage_code == 0){
                                    crash_assert(allocation_length >= 0x10);
                                    
                                    buffer[0] = 0xf;
                                    buffer[1] = 0;
                                    buffer[2] = 0;
                                    buffer[3] = 0;
                                    buffer[4] = 8;   // caching page
                                    buffer[5] = 0xa; // page length
                                    buffer[6] = 4;   // Write cache enable
                                    buffer[7] = 0; // retension priority
                                    *(u64 *)(buffer + 8) = 0; // bunch of stuff.
                                    
                                }else if(page_code == /*MODE_SENSE_CHANGEABLE_VALUES | MODE_PAGE_CACHING*/0x48 && subpage_code == 0){
                                    crash_assert(allocation_length >= 0x10);
                                    
                                    buffer[0] = 0xf;
                                    buffer[1] = 0;
                                    buffer[2] = 0;
                                    buffer[3] = 0;
                                    buffer[4] = 8;   // caching page
                                    buffer[5] = 0xa; // page length
                                    buffer[6] = 0;   // Write cache enable
                                    buffer[7] = 0; // retension priority
                                    *(u64 *)(buffer + 8) = 0; // bunch of stuff.
                                }else if(page_code == /*MODE_SENSE_RETURN_ALL*/0x3f){
                                    crash_assert(allocation_length >= 0x10);
                                    
                                    buffer[0] = 0xf;
                                    buffer[1] = 0;
                                    buffer[2] = 0;
                                    buffer[3] = 0;
                                    buffer[4] = 8;   // caching page
                                    buffer[5] = 0xa; // page length
                                    buffer[6] = 4;   // Write cache enable
                                    buffer[7] = 0; // retension priority
                                    *(u64 *)(buffer + 8) = 0; // bunch of stuff.
                                }else{
                                    set_crash_information(context, CRASH_internal_error, (u64)"Unhandled mode sense.");
                                }
                                
                                write_physical_memory(context, physical_address, buffer, allocation_length);
                            }break;
                            
                            case 0x9e:{ // SERVICE ACTION IN (16)
                                
                                u8 service_action = cdb[1];
                                // u64 starting_logical_block_address = byteswap_u64(*(u64 *)(cdb + 2));
                                u32 allocation_length = byteswap_u32(*(u32 *)(cdb + 10));
                                
                                crash_assert(packet_type == /*VM_PKT_DATA_USING_GPA_DIRECT*/9);
                                struct{
                                    u32 reserved;
                                    u32 rangecount;
                                    
                                    // first range, we only need one.
                                    u32 Length;
                                    u32 Offset;
                                    u64 PageFrameNumber;
                                } *gpa_descriptor = (void *)(vmbus_packet + 1);
                                
                                u64 physical_address = (gpa_descriptor->PageFrameNumber * 0x1000) + gpa_descriptor->Offset;
                                
                                crash_assert(physical_address < context->physical_memory_size);
                                
                                u8 *buffer = push_data(&context->scratch_arena, u8, allocation_length);
                                
                                switch(service_action){
                                    case 0x10:{ // READ CAPACITY (16)
                                        crash_assert(allocation_length >= 0xc);
                                        
                                        u64 lba = (globals.disk_info.virtual_size / 0x200) - 1;
                                        
                                        *(u64 *)(buffer + 0) = byteswap_u64(lba); // LBA 
                                        *(u32 *)(buffer + 8) = byteswap_u32(0x200);
                                        if(allocation_length > 0xc){
                                            buffer[12] = 0;
                                            buffer[13] = 3;
                                            buffer[14] = 0x80;
                                            buffer[15] = 0;
                                            memset(buffer + 16, 0, 16);
                                        }
                                    }break;
                                    
                                    default:{
                                        set_crash_information(context, CRASH_internal_error, (u64)"Unhandled service action.");
                                    }break;
                                }
                                
                                write_physical_memory(context, physical_address, buffer, allocation_length);
                            }break;
                            
                            default:{
                                set_crash_information(context, CRASH_internal_error, (u64)"Unhandled 'Command Description Block' (SCSI command).");
                                return;
                            }break;
                        }
                    }
                    
                    vmbus_send_packet(context, channel, vmbus_packet);
                }break;
                
                default:{
                    set_crash_information(context, CRASH_internal_error, (u64)"Unhandled vstor packet operation.");
                }break;
            }
        }break;
        
        case VMBUS_DEVICE_mouse:{
            
            struct vmbus_pipe_header *pipe_header = (void *)((u8 *)vmbus_packet + packet_data_offset);
            crash_assert(pipe_header->type == 1);
            
            struct synthhid_message_header{
                u32 type;
                u32 size;
            } *synthhid_header = (void *)(pipe_header + 1);
            
            switch(synthhid_header->type){
                case /*SYNTH_HID_PROTOCOL_REQUEST*/0:{
                    struct synthhid_version{
                        u16 minor_version;
                        u16 major_version;
                    } *version = (void *)(synthhid_header + 1);
                    
                    if(version->major_version != 2 || version->minor_version != 0){
                        set_crash_information(context, CRASH_internal_error, (u64)"Unhandled mouse version.");
                        break;
                    }
                    
                    struct synthhid_version_response{
                        struct synthhid_message_header synthhid_header;
                        struct synthhid_version version;
                        u8 accepted;
                    } version_response = {
                        .synthhid_header = {
                            .type = /*SYNTH_HID_PROTOCOL_RESPONSE*/1,
                            .size = 5,
                        },
                        .version = *version,
                        .accepted = 1,
                    };
                    
                    // 
                    // @note: hack to prevent the double interrupt sending.
                    // 
                    context->vmbus.send_packet_skip_interrupt = 1;
                    vmbus_pipe_send_packet(context, channel, &version_response, 0xd);
                    context->vmbus.send_packet_skip_interrupt = 0;
                    
                    struct synthhid_initial_device_info{
                        struct synthhid_message_header synthhid_header;
                        struct {
                            u32 size;
                            u16 vendor;
                            u16 product;
                            u16 version;
                            u16 reserved[11];
                        } device_info;
                        struct {
                            u8  length;
                            u8  descriptor_type;
                            u16 hid_specification;
                            u8  county_code;
                            u8  number_of_descriptors;
                            
                            u8 descriptors[0x46];
                        } hid_descriptor;
                    } device_info = {
                        .synthhid_header = {
                            .type = 2,
                            .size = 0x6c,
                        },
                        .device_info = {
                            .size = 0x20,
                            .vendor = 0x45e,
                            .product = 0x621,
                            .version = 1,
                        },
                        .hid_descriptor = {
                            .length = 9,// sizeof(hid_descriptor) + sizeof(hid_class_descriptor)
                            .descriptor_type = 0x21,
                            .hid_specification = 0x101,
                            .county_code = 0,
                            .number_of_descriptors = 1,
                            
                            .descriptors = {
                                0x22, // type
                                0x43, 0x00, // length
                                
                                // According to 'https://eleccelerator.com/usbdescreqparser/':
                                
                                0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
                                0x09, 0x02,        // Usage (Mouse)
                                0xA1, 0x01,        // Collection (Application)
                                0x09, 0x01,        //   Usage (Pointer)
                                0xA1, 0x00,        //   Collection (Physical)
                                0x05, 0x09,        //     Usage Page (Button)
                                0x19, 0x01,        //     Usage Minimum (0x01)
                                0x29, 0x05,        //     Usage Maximum (0x05)
                                0x15, 0x00,        //     Logical Minimum (0)
                                0x25, 0x01,        //     Logical Maximum (1)
                                0x95, 0x05,        //     Report Count (5)
                                0x75, 0x01,        //     Report Size (1)
                                0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
                                0x95, 0x01,        //     Report Count (1)
                                0x75, 0x03,        //     Report Size (3)
                                0x81, 0x01,        //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
                                0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
                                0x09, 0x30,        //     Usage (X)
                                0x09, 0x31,        //     Usage (Y)
                                0x15, 0x00,        //     Logical Minimum (0)
                                0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
                                0x75, 0x10,        //     Report Size (16)
                                0x95, 0x02,        //     Report Count (2)
                                0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
                                0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
                                0x09, 0x38,        //     Usage (Wheel)
                                0x16, 0x01, 0x80,  //     Logical Minimum (-32767)
                                0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
                                0x75, 0x10,        //     Report Size (16)
                                0x95, 0x01,        //     Report Count (1)
                                0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
                                0xC0,              //   End Collection
                                0xC0,              // End Collection
                            },
                        },
                    };
                    
                    vmbus_pipe_send_packet(context, channel, &device_info, sizeof(device_info));
                }break;
                
                case /*SYNTH_HID_INITIAL_DEVICE_INFO_ACK*/3:{
                    // I think this is fine.
                }break;
                
                default:{
                    set_crash_information(context, CRASH_internal_error, (u64)"Unhandled mouse.");
                }break;
            }
        }break;
        
        case VMBUS_DEVICE_keyboard:{
            u32 keyboard_message_type = *(u32 *)((u8 *)vmbus_packet + packet_data_offset);
            
            u8 *data = (u8 *)vmbus_packet + packet_data_offset + sizeof(u32);
            
            switch(keyboard_message_type){
                case /*SYNTH_KBD_PROTOCOL_REQUEST*/1:{
                    
                    struct{
                        u16 minor;
                        u16 major;
                    } *version = (void *)data;
                    
                    if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("["__FUNCTION__"] SYNTH_KBD_PROTOCOL_REQUEST %d %d\n", version->major, version->minor);
                    
                    if(version->major != 1 || version->minor != 0){
                        set_crash_information(context, CRASH_internal_error, (u64)"Unhandled keyboard protocol version.");
                    }
                    
                    struct{
                        struct vmbus_packet_description description;
                        u32 kind;
                        u32 status;
                    } response = {
                        .description = {
                            .PacketType = /*VMBUS_PACKET_DATA_INBAND*/6,
                            .PacketDataOffsetDiv8 = sizeof(struct vmbus_packet_description)/8,
                            .PacketLengthDiv8 = sizeof(response)/8,
                            .PacketFlags = 0,
                            .PacketIdentifier = vmbus_packet->PacketIdentifier,
                        },
                        .kind = /*SYNTH_KBD_PROTOCOL_RESPONSE*/2,
                        .status = /*PROTOCOL_ACCEPTED*/1,
                    };
                    
                    vmbus_send_packet(context, channel, &response.description);
                }break;
                
                case /*SYNTH_KBD_LED_INDICATORS*/4:{
                    // wtf?
                }break;
                
                default:{
                    set_crash_information(context, CRASH_internal_error, (u64)"Unhandled keyboard.");
                }break;
            }
        }break;
        
        case VMBUS_DEVICE_framebuffer:{
            
            struct vmbus_pipe_header *pipe_header = (void *)((u8 *)vmbus_packet + packet_data_offset);
            crash_assert(pipe_header->type == 1);
            
            struct synthvid_header{
                u32 type;
                u32 size;
            } *header = (void *)(pipe_header + 1);
            
            switch(header->type){
                case /*SYNTHVID_VERSION_REQUEST*/1:{
                    struct synthvid_version{
                        u16 minor_version;
                        u16 major_version;
                    } *version = (void *)(header + 1);
                    
                    
                    if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("["__FUNCTION__"] SYNTHVID_VERSION_REQUEST %d %d\n", version->major_version, version->minor_version);
                    
                    
                    (void)version; // @cleanup: make sure 3,2 is supported ?
                    
                    struct{
                        struct synthvid_header header;
                        
                        u16 minor_version;
                        u16 major_version;
                        u8 is_accepted;
                        u8 max_video_outputs;
                    } version_response = {
                        
                        .header = {
                            .type = 2,
                            .size = 0xe,
                        },
                        
                        .minor_version = 3, // version->minor_version,
                        .major_version = 2, // version->major_version,
                        .is_accepted = 2, // ? (why 2 not 1?)
                        .max_video_outputs = 1,
                    };
                    
                    vmbus_pipe_send_packet(context, channel, &version_response, sizeof(version_response));
                }break;
                
                case /*SYNTHVID_VRAM_LOCATION*/3:{
                    
                    u8 *data = (void *)(header + 1);
                    u64 user_context = *(u64 *)(data + 0);
                    u8 is_vram_gpa_specified = data[8];
                    // u64 vram_gpa = *(u64 *)(data + 9);
                    
                    if(PRINT_VMBUS_EVENTS || PRINT_VMBUS_INITIALIZATION_EVENTS) print("["__FUNCTION__"] SYNTHVID_VRAM_LOCATION\n");
                    
                    crash_assert(is_vram_gpa_specified);
                    
                    struct{
                        struct synthvid_header header;
                        u64 user_context;
                    } vram_ack = {
                        .header = {
                            .type = /*SYNTHVID_VRAM_LOCATION_ACK*/4,
                            .size = sizeof(struct synthvid_header) + 8,
                        },
                        .user_context = user_context,
                    };
                    vmbus_pipe_send_packet(context, channel, &vram_ack, sizeof(vram_ack));
                }break;
                
                case /*SYNTHVID_SITUATION_UPDATE*/5:{
                    u8 *data = (void *)(header + 1);
                    u64 user_context = *(u64 *)(data + 0);
                    // u8  video_output_count = data[8];
                    // u8  active = data[9];
                    // u32 vram_offset = *(u32 *)(data + 10);
                    // u8  depth_bits = data[14];
                    // u32 width_pixels = *(u32 *)(data + 15);
                    // u32 height_pixels = *(u32 *)(data + 19);
                    // u32 pitch_bytes = *(u32 *)(data + 23);
                    
                    struct{
                        struct synthvid_header header;
                        u64 user_context;
                    } vram_ack = {
                        .header = {
                            .type = /*SYNTHVID_SITUATION_UPDATE_ACK*/6,
                            .size = sizeof(struct synthvid_header) + 8,
                        },
                        .user_context = user_context,
                    };
                    vmbus_pipe_send_packet(context, channel, &vram_ack, sizeof(vram_ack));
                }break;
                
                case /*SYNTHVID_POINTER_POSITION*/7:{
                    // do nothing for now.
                }break;
                
                case /*SYNTHVID_POINTER_SHAPE*/8:{
                    // do nothing for now.
                }break;
                
                case /*SYNTHVID_DIRT*/10:{
                    // do nothing for now.
                }break;
                
                default:{
                    set_crash_information(context, CRASH_internal_error, (u64)"Unhandled Framebuffer.");
                }break;
            }
        }break;
        
        default:{
            set_crash_information(context, CRASH_internal_error, (u64)"Unhandled HvCallSignalEvent connection id.");
        }break;
    }
}
