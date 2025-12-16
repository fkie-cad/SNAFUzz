
int hacky_display_input_handling(struct context *context){
    
    if(events_processed == events_initiated) return 0;
    
    ticket_spinlock_lock(&globals.vmbus.message_lock);
    
    if(events_processed == events_initiated){
        ticket_spinlock_unlock(&globals.vmbus.message_lock);
        return 0;
    }
    
    int success = 0;
    
    //
    // Check for pending keyboard/mouse updates.
    //
    
    struct hacky_event event = event_buffer[events_processed % array_count(event_buffer)];
    events_processed++;
    
    switch(event.kind){
        
        case HACKY_EVENT_key_event:{
            if(!globals.vmbus.keyboard) break;
            
            u16 keycode = event.keycode;
            
            if(PRINT_INPUT_EVENTS || PRINT_HOOK_EVENTS) print("[input] Send key%s \n", ((keycode >> 8) & 2) ? "down" : "up");
            
            struct keystroke{
                struct vmbus_packet_description description;
                u32 type;
                u16 make_code;
                u16 __padding;
                u32 information;
                u32 __padding2;
            } keystroke = {
                .description = {
                    .PacketType = 6,
                    .PacketDataOffsetDiv8 = offset_in_type(struct keystroke, type) / 8,
                    .PacketLengthDiv8 = sizeof(keystroke) / 8,
                },
                
                .type = /*SYNTH_KBD_EVENT*/3,
                .make_code = (u8)keycode,
                .information = (keycode >> 8),
            }; 
            
            vmbus_send_packet(context, globals.vmbus.keyboard, &keystroke.description);
            success = 1;
            
        }break;
        
        case HACKY_EVENT_mouse_move:
        case HACKY_EVENT_mouse_event:{
            if(!globals.vmbus.mouse) break;
            
            if(PRINT_INPUT_EVENTS || PRINT_HOOK_EVENTS) print("[input] Send mouse event {.x = 0x%x .y = 0x%x, .z = 0x%x, .button = 0x%x}\n", 
                    event.mouse_x, event.mouse_y, event.wheel, event.button);
            
            struct mouse_event{
                struct vmbus_packet_description description;
                struct pipe_msg{
                    u32 type;
                    u32 size;
                } pipe_msg;
                struct hid_msg{
                    u32 type;
                    u32 size;
                } hid_msg;
                
                //
                // Absolutely positioned hid mouse according to this random commit of a random project: 
                //     https://github.com/hathach/tinyusb/pull/1363/files/8c79b8924eabf441f40a8ce3cab8828688575b6d
                //
                
                u8 button;
                
                // These are unaligned -.-
                u8 mouse_x_low;
                u8 mouse_x_high;
                u8 mouse_y_low;
                u8 mouse_y_high;
                
                u8 wheel_low;
                u8 wheel_high;
                // u8 pan; // Not sure what this is :)
                
                u8 unused;
            } mouse_event = {
                .description = {
                    .PacketType = 6,
                    .PacketDataOffsetDiv8 = offset_in_type(struct mouse_event, pipe_msg) / 8,
                    .PacketLengthDiv8 = sizeof(mouse_event) / 8,
                },
                .pipe_msg = {
                    .type = /*PIPE_MESSAGE_DATA*/1,
                    .size = sizeof(mouse_event) - sizeof(mouse_event.description) - sizeof(mouse_event.pipe_msg),
                },
                
                .hid_msg = {
                    .type = /*SYNTH_HID_INPUT_REPORT*/4,
                    .size = 7,
                },
                
                .button = event.button,
                .mouse_x_low  = (u8)(event.mouse_x >> 0),
                .mouse_x_high = (u8)(event.mouse_x >> 8),
                .mouse_y_low  = (u8)(event.mouse_y >> 0),
                .mouse_y_high = (u8)(event.mouse_y >> 8),
                .wheel_low  = (u8)(event.wheel >> 0),
                .wheel_high = (u8)(event.wheel >> 8),
            };
            
            vmbus_send_packet(context, globals.vmbus.mouse, &mouse_event.description);
            success = 1;
        }break;
    }
    
    ticket_spinlock_unlock(&globals.vmbus.message_lock);
    return success;
}

