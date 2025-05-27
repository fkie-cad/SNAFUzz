
//
// Auto-generated from the Intel 64 and IA-32 Architectures Software Developer's Manual.
//

static u8 instruction_has_no_modrm[0x400] = {
    [0x4] = 1, [0x5] = 1, [0xc] = 1, [0xd] = 1, 
    [0x14] = 1, [0x15] = 1, [0x1c] = 1, [0x1d] = 1, 
    [0x24] = 1, [0x25] = 1, [0x2c] = 1, [0x2d] = 1, 
    [0x34] = 1, [0x35] = 1, [0x3c] = 1, [0x3d] = 1, 
    [0x50] = 1, [0x51] = 1, [0x52] = 1, [0x53] = 1, 
    [0x54] = 1, [0x55] = 1, [0x56] = 1, [0x57] = 1, 
    [0x58] = 1, [0x59] = 1, [0x5a] = 1, [0x5b] = 1, 
    [0x5c] = 1, [0x5d] = 1, [0x5e] = 1, [0x5f] = 1, 
    [0x68] = 1, [0x6a] = 1, [0x6c] = 1, [0x6d] = 1, 
    [0x6e] = 1, [0x6f] = 1, [0x70] = 1, [0x71] = 1, 
    [0x72] = 1, [0x73] = 1, [0x74] = 1, [0x75] = 1, 
    [0x76] = 1, [0x77] = 1, [0x78] = 1, [0x79] = 1, 
    [0x7a] = 1, [0x7b] = 1, [0x7c] = 1, [0x7d] = 1, 
    [0x7e] = 1, [0x7f] = 1, [0x90] = 1, [0x91] = 1, 
    [0x92] = 1, [0x93] = 1, [0x94] = 1, [0x95] = 1, 
    [0x96] = 1, [0x97] = 1, [0x98] = 1, [0x99] = 1, 
    [0x9b] = 1, [0x9c] = 1, [0x9d] = 1, [0x9e] = 1, 
    [0x9f] = 1, [0xa0] = 1, [0xa1] = 1, [0xa2] = 1, 
    [0xa3] = 1, [0xa4] = 1, [0xa5] = 1, [0xa6] = 1, 
    [0xa7] = 1, [0xa8] = 1, [0xa9] = 1, [0xaa] = 1, 
    [0xab] = 1, [0xac] = 1, [0xad] = 1, [0xae] = 1, 
    [0xaf] = 1, [0xb0] = 1, [0xb1] = 1, [0xb2] = 1, 
    [0xb3] = 1, [0xb4] = 1, [0xb5] = 1, [0xb6] = 1, 
    [0xb7] = 1, [0xb8] = 1, [0xb9] = 1, [0xba] = 1, 
    [0xbb] = 1, [0xbc] = 1, [0xbd] = 1, [0xbe] = 1, 
    [0xbf] = 1, [0xc2] = 1, [0xc3] = 1, [0xc8] = 1, 
    [0xc9] = 1, [0xca] = 1, [0xcb] = 1, [0xcc] = 1, 
    [0xcd] = 1, [0xcf] = 1, [0xd7] = 1, [0xe0] = 1, 
    [0xe1] = 1, [0xe2] = 1, [0xe3] = 1, [0xe4] = 1, 
    [0xe5] = 1, [0xe6] = 1, [0xe7] = 1, [0xe8] = 1, 
    [0xe9] = 1, [0xeb] = 1, [0xec] = 1, [0xed] = 1, 
    [0xee] = 1, [0xef] = 1, [0xf0] = 1, [0xf1] = 1, 
    [0xf4] = 1, [0xf5] = 1, [0xf8] = 1, [0xf9] = 1, 
    [0xfa] = 1, [0xfb] = 1, [0xfc] = 1, [0xfd] = 1, 
    [0x105] = 1, [0x106] = 1, [0x107] = 1, [0x108] = 1, 
    [0x109] = 1, [0x10b] = 1, [0x130] = 1, [0x131] = 1, 
    [0x132] = 1, [0x133] = 1, [0x134] = 1, [0x135] = 1, 
    [0x177] = 1, [0x180] = 1, [0x181] = 1, [0x182] = 1, 
    [0x183] = 1, [0x184] = 1, [0x185] = 1, [0x186] = 1, 
    [0x187] = 1, [0x188] = 1, [0x189] = 1, [0x18a] = 1, 
    [0x18b] = 1, [0x18c] = 1, [0x18d] = 1, [0x18e] = 1, 
    [0x18f] = 1, [0x1a0] = 1, [0x1a1] = 1, [0x1a2] = 1, 
    [0x1a8] = 1, [0x1a9] = 1, [0x1aa] = 1, [0x1c8] = 1, 
    [0x1c9] = 1, [0x1ca] = 1, [0x1cb] = 1, [0x1cc] = 1, 
    [0x1cd] = 1, [0x1ce] = 1, [0x1cf] = 1, 
};

enum operand_kind{
    OPERAND_none,
    OPERAND_imm8,
    OPERAND_imm16,
    OPERAND_imm32,
    OPERAND_imm64,
    OPERAND_rel8,
    OPERAND_rel16,
    OPERAND_rel32,
    OPERAND_far16,
    OPERAND_far32,
    OPERAND_far_m16,
    OPERAND_far_m32,
    OPERAND_far_m64,
    OPERAND_1,
    OPERAND_al,
    OPERAND_cl,
    OPERAND_ax,
    OPERAND_dx,
    OPERAND_eax,
    OPERAND_edx,
    OPERAND_rax,
    OPERAND_xmm0,
    OPERAND_reg8,
    OPERAND_reg16,
    OPERAND_reg32,
    OPERAND_reg64,
    OPERAND_opcode8,
    OPERAND_opcode16,
    OPERAND_opcode32,
    OPERAND_opcode64,
    OPERAND_vex_reg32,
    OPERAND_vex_reg64,
    OPERAND_vex_xmm,
    OPERAND_vex_ymm,
    OPERAND_vex_zmm,
    OPERAND_mm,
    OPERAND_xmm,
    OPERAND_ymm,
    OPERAND_zmm,
    OPERAND_regm8,
    OPERAND_regm16,
    OPERAND_regm32,
    OPERAND_regm64,
    OPERAND_regm8_zero_extended,
    OPERAND_regm16_zero_extended,
    OPERAND_mmm32,
    OPERAND_mmm64,
    OPERAND_xmmm8,
    OPERAND_xmmm16,
    OPERAND_xmmm32,
    OPERAND_xmmm64,
    OPERAND_xmmm128,
    OPERAND_ymmm256,
    OPERAND_zmmm512,
    OPERAND_mem,
    OPERAND_m8,
    OPERAND_m16,
    OPERAND_m32,
    OPERAND_m64,
    OPERAND_m128,
    OPERAND_m256,
    OPERAND_m512,
    OPERAND_moffs8,
    OPERAND_moffs16,
    OPERAND_moffs32,
    OPERAND_moffs64,
    OPERAND_segment_register,
    OPERAND_k,
    OPERAND_vex_k,
    OPERAND_km8,
    OPERAND_km16,
    OPERAND_km32,
    OPERAND_km64,
    OPERAND_bnd,
    OPERAND_bndm64,
    OPERAND_bndm128,
    OPERAND_mib,
    OPERAND_ST0,
    OPERAND_STi,
    OPERAND_cr,
    OPERAND_dr,
    OPERAND_ds,
    OPERAND_ss,
    OPERAND_cs,
    OPERAND_es,
    OPERAND_fs,
    OPERAND_gs,
    OPERAND_vm32x,
    OPERAND_vm32y,
    OPERAND_vm32z,
    OPERAND_vm64x,
    OPERAND_vm64y,
    OPERAND_vm64z,
    OPERAND_kind_count,
};

enum operand_flags{
    OPERAND_FLAG_read  = 1,
    OPERAND_FLAG_write = 2,
};

#define IMM_OP_SIZE_MAX32    0x7f // Instructions that take 'op regm, imm16/32'.
#define INSTRUCTION_IS_WEIRD 0x7e // Currently only F6, F7 and 'B8 - BF'.

static u8 instruction_immediate_size[0x400] = {
    
    [0x04] = 1, [0x05] = IMM_OP_SIZE_MAX32,
    
    [0x0c] = 1, [0x0d] = IMM_OP_SIZE_MAX32,
    
    [0x14] = 1, [0x15] = IMM_OP_SIZE_MAX32,
    
    [0x1c] = 1, [0x1d] = IMM_OP_SIZE_MAX32,
    
    [0x24] = 1, [0x25] = IMM_OP_SIZE_MAX32,
    
    [0x2c] = 1, [0x2d] = IMM_OP_SIZE_MAX32,
    
    [0x34] = 1, [0x35] = IMM_OP_SIZE_MAX32,
    
    [0x3c] = 1, [0x3d] = IMM_OP_SIZE_MAX32,
    
    [0x44] = 1, [0x45] = IMM_OP_SIZE_MAX32,
    
    [0x4c] = 1, [0x4d] = IMM_OP_SIZE_MAX32,
    
    [0x68] = IMM_OP_SIZE_MAX32,
    [0x69] = IMM_OP_SIZE_MAX32,
    [0x6a] = 1, [0x6b] = 1,     
    [0x70] = 1, [0x71] = 1, [0x72] = 1, [0x73] = 1, [0x74] = 1, [0x75] = 1, [0x76] = 1, [0x77] = 1, 
    [0x78] = 1, [0x79] = 1, [0x7a] = 1, [0x7b] = 1, [0x7c] = 1, [0x7d] = 1, [0x7e] = 1, [0x7f] = 1, 
    [0x80] = 1, [0x81] = IMM_OP_SIZE_MAX32,
    
    [0x83] = 1,     
    [0xa0] = 8, [0xa1] = 8, [0xa2] = 8, [0xa3] = 8,     
    [0xa8] = 1, [0xa9] = IMM_OP_SIZE_MAX32,
    
    [0xb0] = 1, [0xb1] = 1, [0xb2] = 1, [0xb3] = 1, [0xb4] = 1, [0xb5] = 1, [0xb6] = 1, [0xb7] = 1, 
    [0xb8] = INSTRUCTION_IS_WEIRD,
    [0xb9] = INSTRUCTION_IS_WEIRD,
    [0xba] = INSTRUCTION_IS_WEIRD,
    [0xbb] = INSTRUCTION_IS_WEIRD,
    [0xbc] = INSTRUCTION_IS_WEIRD,
    [0xbd] = INSTRUCTION_IS_WEIRD,
    [0xbe] = INSTRUCTION_IS_WEIRD,
    [0xbf] = INSTRUCTION_IS_WEIRD,
    [0xc0] = 1, [0xc1] = 1, [0xc2] = 2,     
    [0xc6] = 1, [0xc7] = IMM_OP_SIZE_MAX32,
    
    [0xcd] = 1,     
    [0xe0] = 1, [0xe1] = 1, [0xe2] = 1, [0xe3] = 1, [0xe4] = 1, [0xe5] = 1, [0xe6] = 1, [0xe7] = 1, 
    [0xe8] = 4, [0xe9] = 4,     
    [0xeb] = 1,     
    [0xf6] = INSTRUCTION_IS_WEIRD,
    [0xf7] = INSTRUCTION_IS_WEIRD,
    
    [0x170] = 1, [0x171] = 1, [0x172] = 1, [0x173] = 1,     
    [0x180] = 4, [0x181] = 4, [0x182] = 4, [0x183] = 4, [0x184] = 4, [0x185] = 4, [0x186] = 4, [0x187] = 4, 
    [0x188] = 4, [0x189] = 4, [0x18a] = 4, [0x18b] = 4, [0x18c] = 4, [0x18d] = 4, [0x18e] = 4, [0x18f] = 4, 
    
    [0x1a4] = 1,     
    [0x1ac] = 1,     
    [0x1ba] = 1,     
    [0x1c2] = 1,     
    [0x1c4] = 1, [0x1c5] = 1, [0x1c6] = 1,     
    [0x300] = 1, [0x301] = 1, [0x302] = 1, [0x303] = 1, [0x304] = 1, [0x305] = 1, [0x306] = 1,     
    [0x308] = 1, [0x309] = 1, [0x30a] = 1, [0x30b] = 1, [0x30c] = 1, [0x30d] = 1, [0x30e] = 1, [0x30f] = 1, 
    
    [0x314] = 1, [0x315] = 1, [0x316] = 1, [0x317] = 1, [0x318] = 1, [0x319] = 1, [0x31a] = 1, [0x31b] = 1, 
    
    [0x31d] = 1, [0x31e] = 1, [0x31f] = 1, [0x320] = 1, [0x321] = 1, [0x322] = 1, [0x323] = 1,     
    [0x325] = 1, [0x326] = 1, [0x327] = 1,     
    [0x330] = 1, [0x331] = 1, [0x332] = 1, [0x333] = 1,     
    [0x338] = 1, [0x339] = 1, [0x33a] = 1, [0x33b] = 1,     
    [0x33e] = 1, [0x33f] = 1, [0x340] = 1, [0x341] = 1, [0x342] = 1, [0x343] = 1, [0x344] = 1,     
    [0x346] = 1,     
    [0x350] = 1, [0x351] = 1,     
    [0x354] = 1, [0x355] = 1, [0x356] = 1, [0x357] = 1,     
    [0x360] = 1, [0x361] = 1, [0x362] = 1, [0x363] = 1,     
    [0x366] = 1, [0x367] = 1,     
    [0x370] = 1, [0x371] = 1, [0x372] = 1, [0x373] = 1,     
    [0x3cc] = 1,     
    [0x3ce] = 1, [0x3cf] = 1,     
    [0x3df] = 1,     
    [0x3f0] = 1, 
};

struct instruction_table_entry{
    struct string mnemonic;
    int extended_opcode;
    int modrm_opcode;
    u8 legacy_prefix_f2 : 1;
    u8 legacy_prefix_f3 : 1;
    u8 legacy_prefix_66 : 1;
    u8 rex_W            : 1;
    u8 regm_only        : 1;
    u8 reg_opcode       : 4;
    u8 immediate_is_fourth_register : 1;
    u8 vex_L            : 2;
    u8 amount_of_operands : 3;
    struct{
        u8 kind;
        u8 flags;
    } operands[8];
};

struct instruction_table_entry normal_instructions[] = {
    { const_string("ADD"), 0x0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 00 /r - ADD r/m8, r8
    { const_string("ADD"), 0x1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 01 /r - ADD r/m16, r16
    { const_string("ADD"), 0x1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 01 /r - ADD r/m32, r32
    { const_string("ADD"), 0x1, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 01 /r - ADD r/m64, r64
    { const_string("ADD"), 0x2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 02 /r - ADD r8, r/m8
    { const_string("ADD"), 0x3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 03 /r - ADD r16, r/m16
    { const_string("ADD"), 0x3, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 03 /r - ADD r32, r/m32
    { const_string("ADD"), 0x3, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 03 /r - ADD r64, r/m64
    { const_string("ADD"), 0x4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 04 ib - ADD al, imm8
    { const_string("ADD"), 0x5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 05 iw - ADD ax, imm16
    { const_string("ADD"), 0x5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // 05 id - ADD eax, imm32
    { const_string("ADD"), 0x5, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W 05 id - ADD rax, imm32
    { const_string("OR"), 0x8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 08 /r - OR r/m8, r8
    { const_string("OR"), 0x9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 09 /r - OR r/m16, r16
    { const_string("OR"), 0x9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 09 /r - OR r/m32, r32
    { const_string("OR"), 0x9, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 09 /r - OR r/m64, r64
    { const_string("OR"), 0xa, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 0a /r - OR r8, r/m8
    { const_string("OR"), 0xb, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0b /r - OR r16, r/m16
    { const_string("OR"), 0xb, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0b /r - OR r32, r/m32
    { const_string("OR"), 0xb, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0b /r - OR r64, r/m64
    { const_string("OR"), 0xc, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0c ib - OR al, imm8
    { const_string("OR"), 0xd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 0d iw - OR ax, imm16
    { const_string("OR"), 0xd, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // 0d id - OR eax, imm32
    { const_string("OR"), 0xd, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W 0d id - OR rax, imm32
    { const_string("ADC"), 0x10, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 10 /r - ADC r/m8, r8
    { const_string("ADC"), 0x11, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 11 /r - ADC r/m16, r16
    { const_string("ADC"), 0x11, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 11 /r - ADC r/m32, r32
    { const_string("ADC"), 0x11, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 11 /r - ADC r/m64, r64
    { const_string("ADC"), 0x12, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 12 /r - ADC r8, r/m8
    { const_string("ADC"), 0x13, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 13 /r - ADC r16, r/m16
    { const_string("ADC"), 0x13, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 13 /r - ADC r32, r/m32
    { const_string("ADC"), 0x13, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 13 /r - ADC r64, r/m64
    { const_string("ADC"), 0x14, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 14 ib - ADC al, imm8
    { const_string("ADC"), 0x15, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 15 iw - ADC ax, imm16
    { const_string("ADC"), 0x15, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // 15 id - ADC eax, imm32
    { const_string("ADC"), 0x15, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W 15 id - ADC rax, imm32
    { const_string("SBB"), 0x18, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 18 /r - SBB r/m8, r8
    { const_string("SBB"), 0x19, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 19 /r - SBB r/m16, r16
    { const_string("SBB"), 0x19, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 19 /r - SBB r/m32, r32
    { const_string("SBB"), 0x19, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 19 /r - SBB r/m64, r64
    { const_string("SBB"), 0x1a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg8, OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 1a /r - SBB r8, r/m8
    { const_string("SBB"), 0x1b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 1b /r - SBB r16, r/m16
    { const_string("SBB"), 0x1b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 1b /r - SBB r32, r/m32
    { const_string("SBB"), 0x1b, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 1b /r - SBB r64, r/m64
    { const_string("SBB"), 0x1c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 1c ib - SBB al, imm8
    { const_string("SBB"), 0x1d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 1d iw - SBB ax, imm16
    { const_string("SBB"), 0x1d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // 1d id - SBB eax, imm32
    { const_string("SBB"), 0x1d, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W 1d id - SBB rax, imm32
    { const_string("AND"), 0x20, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 20 /r - AND r/m8, r8
    { const_string("AND"), 0x21, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 21 /r - AND r/m16, r16
    { const_string("AND"), 0x21, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 21 /r - AND r/m32, r32
    { const_string("AND"), 0x21, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 21 /r - AND r/m64, r64
    { const_string("AND"), 0x22, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 22 /r - AND r8, r/m8
    { const_string("AND"), 0x23, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 23 /r - AND r16, r/m16
    { const_string("AND"), 0x23, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 23 /r - AND r32, r/m32
    { const_string("AND"), 0x23, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 23 /r - AND r64, r/m64
    { const_string("AND"), 0x24, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 24 ib - AND al, imm8
    { const_string("AND"), 0x25, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 25 iw - AND ax, imm16
    { const_string("AND"), 0x25, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // 25 id - AND eax, imm32
    { const_string("AND"), 0x25, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W 25 id - AND rax, imm32
    { const_string("SUB"), 0x28, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 28 /r - SUB r/m8, r8
    { const_string("SUB"), 0x29, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 29 /r - SUB r/m16, r16
    { const_string("SUB"), 0x29, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 29 /r - SUB r/m32, r32
    { const_string("SUB"), 0x29, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 29 /r - SUB r/m64, r64
    { const_string("SUB"), 0x2a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 2a /r - SUB r8, r/m8
    { const_string("SUB"), 0x2b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 2b /r - SUB r16, r/m16
    { const_string("SUB"), 0x2b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 2b /r - SUB r32, r/m32
    { const_string("SUB"), 0x2b, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 2b /r - SUB r64, r/m64
    { const_string("SUB"), 0x2c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 2c ib - SUB al, imm8
    { const_string("SUB"), 0x2d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 2d iw - SUB ax, imm16
    { const_string("SUB"), 0x2d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // 2d id - SUB eax, imm32
    { const_string("SUB"), 0x2d, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W 2d id - SUB rax, imm32
    { const_string("XOR"), 0x30, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 30 /r - XOR r/m8, r8
    { const_string("XOR"), 0x31, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 31 /r - XOR r/m16, r16
    { const_string("XOR"), 0x31, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 31 /r - XOR r/m32, r32
    { const_string("XOR"), 0x31, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 31 /r - XOR r/m64, r64
    { const_string("XOR"), 0x32, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 32 /r - XOR r8, r/m8
    { const_string("XOR"), 0x33, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 33 /r - XOR r16, r/m16
    { const_string("XOR"), 0x33, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 33 /r - XOR r32, r/m32
    { const_string("XOR"), 0x33, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 33 /r - XOR r64, r/m64
    { const_string("XOR"), 0x34, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 34 ib - XOR al, imm8
    { const_string("XOR"), 0x35, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 35 iw - XOR ax, imm16
    { const_string("XOR"), 0x35, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // 35 id - XOR eax, imm32
    { const_string("XOR"), 0x35, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W 35 id - XOR rax, imm32
    { const_string("CMP"), 0x38, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 38 /r - CMP r/m8, r8
    { const_string("CMP"), 0x39, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 39 /r - CMP r/m16, r16
    { const_string("CMP"), 0x39, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 39 /r - CMP r/m32, r32
    { const_string("CMP"), 0x39, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 39 /r - CMP r/m64, r64
    { const_string("CMP"), 0x3a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg8, OPERAND_FLAG_read}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 3a /r - CMP r8, r/m8
    { const_string("CMP"), 0x3b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 3b /r - CMP r16, r/m16
    { const_string("CMP"), 0x3b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 3b /r - CMP r32, r/m32
    { const_string("CMP"), 0x3b, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 3b /r - CMP r64, r/m64
    { const_string("CMP"), 0x3c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 3c ib - CMP al, imm8
    { const_string("CMP"), 0x3d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 3d iw - CMP ax, imm16
    { const_string("CMP"), 0x3d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // 3d id - CMP eax, imm32
    { const_string("CMP"), 0x3d, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W 3d id - CMP rax, imm32
    { const_string("PUSH"), 0x50, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_read}} }, // 66 50 +reg - PUSH +reg
    { const_string("PUSH"), 0x50, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read}} }, // 50 +reg - PUSH +reg
    { const_string("PUSH"), 0x51, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_read}} }, // 66 51 +reg - PUSH +reg
    { const_string("PUSH"), 0x51, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read}} }, // 51 +reg - PUSH +reg
    { const_string("PUSH"), 0x52, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_read}} }, // 66 52 +reg - PUSH +reg
    { const_string("PUSH"), 0x52, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read}} }, // 52 +reg - PUSH +reg
    { const_string("PUSH"), 0x53, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_read}} }, // 66 53 +reg - PUSH +reg
    { const_string("PUSH"), 0x53, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read}} }, // 53 +reg - PUSH +reg
    { const_string("PUSH"), 0x54, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_read}} }, // 66 54 +reg - PUSH +reg
    { const_string("PUSH"), 0x54, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read}} }, // 54 +reg - PUSH +reg
    { const_string("PUSH"), 0x55, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_read}} }, // 66 55 +reg - PUSH +reg
    { const_string("PUSH"), 0x55, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read}} }, // 55 +reg - PUSH +reg
    { const_string("PUSH"), 0x56, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_read}} }, // 66 56 +reg - PUSH +reg
    { const_string("PUSH"), 0x56, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read}} }, // 56 +reg - PUSH +reg
    { const_string("PUSH"), 0x57, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_read}} }, // 66 57 +reg - PUSH +reg
    { const_string("PUSH"), 0x57, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read}} }, // 57 +reg - PUSH +reg
    { const_string("POP"), 0x58, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_write}} }, // 66 58 +reg - POP +reg
    { const_string("POP"), 0x58, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_write}} }, // 58 +reg - POP +reg
    { const_string("POP"), 0x59, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_write}} }, // 66 59 +reg - POP +reg
    { const_string("POP"), 0x59, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_write}} }, // 59 +reg - POP +reg
    { const_string("POP"), 0x5a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_write}} }, // 66 5a +reg - POP +reg
    { const_string("POP"), 0x5a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_write}} }, // 5a +reg - POP +reg
    { const_string("POP"), 0x5b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_write}} }, // 66 5b +reg - POP +reg
    { const_string("POP"), 0x5b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_write}} }, // 5b +reg - POP +reg
    { const_string("POP"), 0x5c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_write}} }, // 66 5c +reg - POP +reg
    { const_string("POP"), 0x5c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_write}} }, // 5c +reg - POP +reg
    { const_string("POP"), 0x5d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_write}} }, // 66 5d +reg - POP +reg
    { const_string("POP"), 0x5d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_write}} }, // 5d +reg - POP +reg
    { const_string("POP"), 0x5e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_write}} }, // 66 5e +reg - POP +reg
    { const_string("POP"), 0x5e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_write}} }, // 5e +reg - POP +reg
    { const_string("POP"), 0x5f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode16, OPERAND_FLAG_write}} }, // 66 5f +reg - POP +reg
    { const_string("POP"), 0x5f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_write}} }, // 5f +reg - POP +reg
    { const_string("MOVSXD"), 0x63, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 63 /r - MOVSXD r16, r/m16
    { const_string("MOVSXD"), 0x63, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 63 /r - MOVSXD r32, r/m32
    { const_string("MOVSXD"), 0x63, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // REX.W 63 /r - MOVSXD r64, r/m32
    { const_string("PUSH"), 0x68, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_imm16, 0}} }, // 66 68 iw - PUSH imm16
    { const_string("PUSH"), 0x68, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_imm32, 0}} }, // 68 id - PUSH imm32
    { const_string("IMUL"), 0x69, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 69 iw /r - IMUL r16, r/m16, imm16
    { const_string("IMUL"), 0x69, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // 69 id /r - IMUL r32, r/m32, imm32
    { const_string("IMUL"), 0x69, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W 69 id /r - IMUL r64, r/m64, imm32
    { const_string("PUSH"), 0x6a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_imm8, 0}} }, // 6a ib - PUSH imm8
    { const_string("IMUL"), 0x6b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 6b ib /r - IMUL r16, r/m16, imm8
    { const_string("IMUL"), 0x6b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 6b ib /r - IMUL r32, r/m32, imm8
    { const_string("IMUL"), 0x6b, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // REX.W 6b ib /r - IMUL r64, r/m64, imm8
    { const_string("INSB"), 0x6c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 6c - INSB 
    { const_string("INSW"), 0x6d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 6d - INSW 
    { const_string("INSD"), 0x6d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 6d - INSD 
    { const_string("OUTSB"), 0x6e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 6e - OUTSB 
    { const_string("OUTSW"), 0x6f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 6f - OUTSW 
    { const_string("OUTSD"), 0x6f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 6f - OUTSD 
    { const_string("JO"), 0x70, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 70 ib - JO rel8
    { const_string("JNO"), 0x71, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 71 ib - JNO rel8
    { const_string("JC"), 0x72, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 72 ib - JC rel8
    { const_string("JNC"), 0x73, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 73 ib - JNC rel8
    { const_string("JZ"), 0x74, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 74 ib - JZ rel8
    { const_string("JNZ"), 0x75, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 75 ib - JNZ rel8
    { const_string("JBE"), 0x76, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 76 ib - JBE rel8
    { const_string("JNBE"), 0x77, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 77 ib - JNBE rel8
    { const_string("JS"), 0x78, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 78 ib - JS rel8
    { const_string("JNS"), 0x79, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 79 ib - JNS rel8
    { const_string("JP"), 0x7a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 7a ib - JP rel8
    { const_string("JNP"), 0x7b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 7b ib - JNP rel8
    { const_string("JL"), 0x7c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 7c ib - JL rel8
    { const_string("JNL"), 0x7d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 7d ib - JNL rel8
    { const_string("JLE"), 0x7e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 7e ib - JLE rel8
    { const_string("JNLE"), 0x7f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // 7f ib - JNLE rel8
    { const_string("ADD"), 0x80, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 80 /0 ib - ADD r/m8, imm8
    { const_string("OR"), 0x80, -1, 0, 0, 0, 0, 0, 1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 80 /1 ib - OR r/m8, imm8
    { const_string("ADC"), 0x80, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 80 /2 ib - ADC r/m8, imm8
    { const_string("SBB"), 0x80, -1, 0, 0, 0, 0, 0, 3, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 80 /3 ib - SBB r/m8, imm8
    { const_string("AND"), 0x80, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 80 /4 ib - AND r/m8, imm8
    { const_string("SUB"), 0x80, -1, 0, 0, 0, 0, 0, 5, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 80 /5 ib - SUB r/m8, imm8
    { const_string("XOR"), 0x80, -1, 0, 0, 0, 0, 0, 6, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 80 /6 ib - XOR r/m8, imm8
    { const_string("CMP"), 0x80, -1, 0, 0, 0, 0, 0, 7, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 80 /7 ib - CMP r/m8, imm8
    { const_string("ADD"), 0x81, -1, 0, 0, 1, 0, 0, 0, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 81 /0 iw - ADD r/m16, imm16
    { const_string("ADD"), 0x81, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // 81 /0 id - ADD r/m32, imm32
    { const_string("ADD"), 0x81, -1, 0, 0, 0, 1, 0, 0, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // REX.W 81 /0 id - ADD r/m64, imm32
    { const_string("OR"), 0x81, -1, 0, 0, 1, 0, 0, 1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 81 /1 iw - OR r/m16, imm16
    { const_string("OR"), 0x81, -1, 0, 0, 0, 0, 0, 1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // 81 /1 id - OR r/m32, imm32
    { const_string("OR"), 0x81, -1, 0, 0, 0, 1, 0, 1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // REX.W 81 /1 id - OR r/m64, imm32
    { const_string("ADC"), 0x81, -1, 0, 0, 1, 0, 0, 2, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 81 /2 iw - ADC r/m16, imm16
    { const_string("ADC"), 0x81, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // 81 /2 id - ADC r/m32, imm32
    { const_string("ADC"), 0x81, -1, 0, 0, 0, 1, 0, 2, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // REX.W 81 /2 id - ADC r/m64, imm32
    { const_string("SBB"), 0x81, -1, 0, 0, 1, 0, 0, 3, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 81 /3 iw - SBB r/m16, imm16
    { const_string("SBB"), 0x81, -1, 0, 0, 0, 0, 0, 3, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // 81 /3 id - SBB r/m32, imm32
    { const_string("SBB"), 0x81, -1, 0, 0, 0, 1, 0, 3, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // REX.W 81 /3 id - SBB r/m64, imm32
    { const_string("AND"), 0x81, -1, 0, 0, 1, 0, 0, 4, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 81 /4 iw - AND r/m16, imm16
    { const_string("AND"), 0x81, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // 81 /4 id - AND r/m32, imm32
    { const_string("AND"), 0x81, -1, 0, 0, 0, 1, 0, 4, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // REX.W 81 /4 id - AND r/m64, imm32
    { const_string("SUB"), 0x81, -1, 0, 0, 1, 0, 0, 5, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 81 /5 iw - SUB r/m16, imm16
    { const_string("SUB"), 0x81, -1, 0, 0, 0, 0, 0, 5, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // 81 /5 id - SUB r/m32, imm32
    { const_string("SUB"), 0x81, -1, 0, 0, 0, 1, 0, 5, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // REX.W 81 /5 id - SUB r/m64, imm32
    { const_string("XOR"), 0x81, -1, 0, 0, 1, 0, 0, 6, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 81 /6 iw - XOR r/m16, imm16
    { const_string("XOR"), 0x81, -1, 0, 0, 0, 0, 0, 6, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // 81 /6 id - XOR r/m32, imm32
    { const_string("XOR"), 0x81, -1, 0, 0, 0, 1, 0, 6, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // REX.W 81 /6 id - XOR r/m64, imm32
    { const_string("CMP"), 0x81, -1, 0, 0, 1, 0, 0, 7, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 81 /7 iw - CMP r/m16, imm16
    { const_string("CMP"), 0x81, -1, 0, 0, 0, 0, 0, 7, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // 81 /7 id - CMP r/m32, imm32
    { const_string("CMP"), 0x81, -1, 0, 0, 0, 1, 0, 7, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W 81 /7 id - CMP r/m64, imm32
    { const_string("ADD"), 0x83, -1, 0, 0, 1, 0, 0, 0, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 83 /0 ib - ADD r/m16, imm8
    { const_string("ADD"), 0x83, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 83 /0 ib - ADD r/m32, imm8
    { const_string("ADD"), 0x83, -1, 0, 0, 0, 1, 0, 0, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W 83 /0 ib - ADD r/m64, imm8
    { const_string("OR"), 0x83, -1, 0, 0, 1, 0, 0, 1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 83 /1 ib - OR r/m16, imm8
    { const_string("OR"), 0x83, -1, 0, 0, 0, 0, 0, 1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 83 /1 ib - OR r/m32, imm8
    { const_string("OR"), 0x83, -1, 0, 0, 0, 1, 0, 1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W 83 /1 ib - OR r/m64, imm8
    { const_string("ADC"), 0x83, -1, 0, 0, 1, 0, 0, 2, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 83 /2 ib - ADC r/m16, imm8
    { const_string("ADC"), 0x83, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 83 /2 ib - ADC r/m32, imm8
    { const_string("ADC"), 0x83, -1, 0, 0, 0, 1, 0, 2, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W 83 /2 ib - ADC r/m64, imm8
    { const_string("SBB"), 0x83, -1, 0, 0, 1, 0, 0, 3, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 83 /3 ib - SBB r/m16, imm8
    { const_string("SBB"), 0x83, -1, 0, 0, 0, 0, 0, 3, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 83 /3 ib - SBB r/m32, imm8
    { const_string("SBB"), 0x83, -1, 0, 0, 0, 1, 0, 3, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W 83 /3 ib - SBB r/m64, imm8
    { const_string("AND"), 0x83, -1, 0, 0, 1, 0, 0, 4, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 83 /4 ib - AND r/m16, imm8
    { const_string("AND"), 0x83, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 83 /4 ib - AND r/m32, imm8
    { const_string("AND"), 0x83, -1, 0, 0, 0, 1, 0, 4, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W 83 /4 ib - AND r/m64, imm8
    { const_string("SUB"), 0x83, -1, 0, 0, 1, 0, 0, 5, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 83 /5 ib - SUB r/m16, imm8
    { const_string("SUB"), 0x83, -1, 0, 0, 0, 0, 0, 5, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 83 /5 ib - SUB r/m32, imm8
    { const_string("SUB"), 0x83, -1, 0, 0, 0, 1, 0, 5, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W 83 /5 ib - SUB r/m64, imm8
    { const_string("XOR"), 0x83, -1, 0, 0, 1, 0, 0, 6, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 83 /6 ib - XOR r/m16, imm8
    { const_string("XOR"), 0x83, -1, 0, 0, 0, 0, 0, 6, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 83 /6 ib - XOR r/m32, imm8
    { const_string("XOR"), 0x83, -1, 0, 0, 0, 1, 0, 6, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W 83 /6 ib - XOR r/m64, imm8
    { const_string("CMP"), 0x83, -1, 0, 0, 1, 0, 0, 7, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 83 /7 ib - CMP r/m16, imm8
    { const_string("CMP"), 0x83, -1, 0, 0, 0, 0, 0, 7, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 83 /7 ib - CMP r/m32, imm8
    { const_string("CMP"), 0x83, -1, 0, 0, 0, 1, 0, 7, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // REX.W 83 /7 ib - CMP r/m64, imm8
    { const_string("TEST"), 0x84, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 84 /r - TEST r/m8, r8
    { const_string("TEST"), 0x85, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 85 /r - TEST r/m16, r16
    { const_string("TEST"), 0x85, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 85 /r - TEST r/m32, r32
    { const_string("TEST"), 0x85, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 85 /r - TEST r/m64, r64
    { const_string("XCHG"), 0x86, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 86 /r - XCHG r/m8, r8
    { const_string("XCHG"), 0x87, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 87 /r - XCHG r/m16, r16
    { const_string("XCHG"), 0x87, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 87 /r - XCHG r/m32, r32
    { const_string("XCHG"), 0x87, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 87 /r - XCHG r/m64, r64
    { const_string("MOV"), 0x88, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 88 /r - MOV r/m8, r8
    { const_string("MOV"), 0x89, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 89 /r - MOV r/m16, r16
    { const_string("MOV"), 0x89, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 89 /r - MOV r/m32, r32
    { const_string("MOV"), 0x89, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 89 /r - MOV r/m64, r64
    { const_string("MOV"), 0x8a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg8, OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 8a /r - MOV r8, r/m8
    { const_string("MOV"), 0x8b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 8b /r - MOV r16, r/m16
    { const_string("MOV"), 0x8b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 8b /r - MOV r32, r/m32
    { const_string("MOV"), 0x8b, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 8b /r - MOV r64, r/m64
    { const_string("MOV"), 0x8c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_segment_register, OPERAND_FLAG_read}} }, // 66 8c /r - MOV r/m16, Sreg
    { const_string("MOV"), 0x8c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16_zero_extended, OPERAND_FLAG_write}, {OPERAND_segment_register, OPERAND_FLAG_read}} }, // 8c /r - MOV reg/m16, Sreg
    { const_string("MOV"), 0x8c, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm16_zero_extended, OPERAND_FLAG_write}, {OPERAND_segment_register, OPERAND_FLAG_read}} }, // REX.W 8c /r - MOV reg/m16, Sreg
    { const_string("LEA"), 0x8d, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_mem, OPERAND_FLAG_read}} }, // 66 8d /r - LEA r16, mem
    { const_string("LEA"), 0x8d, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_mem, OPERAND_FLAG_read}} }, // 8d /r - LEA r32, mem
    { const_string("LEA"), 0x8d, -1, 0, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_mem, OPERAND_FLAG_read}} }, // REX.W 8d /r - LEA r64, mem
    { const_string("MOV"), 0x8e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_segment_register, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 8e /r - MOV Sreg, r/m16
    { const_string("MOV"), 0x8e, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_segment_register, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 8e /r - MOV Sreg, r/m64
    { const_string("POP"), 0x8f, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_write}} }, // 66 8f /0 - POP r/m16
    { const_string("POP"), 0x8f, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_write}} }, // 8f /0 - POP r/m64
    { const_string("PAUSE"), 0x90, -1, 0, 1, 0, 0, 0, -1, 0, 0, 0,  }, // F3 90 - PAUSE 
    { const_string("NOP"), 0x90, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 90 - NOP 
    { const_string("XCHG"), 0x91, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 91 +reg - XCHG ax, +reg
    { const_string("XCHG"), 0x91, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 91 +reg - XCHG eax, +reg
    { const_string("XCHG"), 0x91, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 91 +reg - XCHG rax, +reg
    { const_string("XCHG"), 0x92, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 92 +reg - XCHG ax, +reg
    { const_string("XCHG"), 0x92, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 92 +reg - XCHG eax, +reg
    { const_string("XCHG"), 0x92, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 92 +reg - XCHG rax, +reg
    { const_string("XCHG"), 0x93, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 93 +reg - XCHG ax, +reg
    { const_string("XCHG"), 0x93, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 93 +reg - XCHG eax, +reg
    { const_string("XCHG"), 0x93, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 93 +reg - XCHG rax, +reg
    { const_string("XCHG"), 0x94, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 94 +reg - XCHG ax, +reg
    { const_string("XCHG"), 0x94, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 94 +reg - XCHG eax, +reg
    { const_string("XCHG"), 0x94, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 94 +reg - XCHG rax, +reg
    { const_string("XCHG"), 0x95, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 95 +reg - XCHG ax, +reg
    { const_string("XCHG"), 0x95, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 95 +reg - XCHG eax, +reg
    { const_string("XCHG"), 0x95, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 95 +reg - XCHG rax, +reg
    { const_string("XCHG"), 0x96, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 96 +reg - XCHG ax, +reg
    { const_string("XCHG"), 0x96, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 96 +reg - XCHG eax, +reg
    { const_string("XCHG"), 0x96, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 96 +reg - XCHG rax, +reg
    { const_string("XCHG"), 0x97, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 97 +reg - XCHG ax, +reg
    { const_string("XCHG"), 0x97, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 97 +reg - XCHG eax, +reg
    { const_string("XCHG"), 0x97, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 97 +reg - XCHG rax, +reg
    { const_string("CBW"), 0x98, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 98 - CBW 
    { const_string("CWDE"), 0x98, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 98 - CWDE 
    { const_string("CDQE"), 0x98, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W 98 - CDQE 
    { const_string("CWD"), 0x99, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 99 - CWD 
    { const_string("CDQ"), 0x99, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 99 - CDQ 
    { const_string("CQO"), 0x99, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W 99 - CQO 
    { const_string("FWAIT"), 0x9b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 9b - FWAIT 
    { const_string("PUSHF"), 0x9c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 9c - PUSHF 
    { const_string("PUSHFQ"), 0x9c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 9c - PUSHFQ 
    { const_string("POPF"), 0x9d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 9d - POPF 
    { const_string("POPFQ"), 0x9d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 9d - POPFQ 
    { const_string("SAHF"), 0x9e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 9e - SAHF 
    { const_string("LAHF"), 0x9f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 9f - LAHF 
    { const_string("MOV"), 0xa0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_moffs8, 0}} }, // a0 - MOV al, moffs8
    { const_string("MOV"), 0xa0, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_moffs8, 0}} }, // REX.W a0 - MOV al, moffs8
    { const_string("MOV"), 0xa1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read}, {OPERAND_moffs16, 0}} }, // 66 a1 - MOV ax, moffs16
    { const_string("MOV"), 0xa1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read}, {OPERAND_moffs32, 0}} }, // a1 - MOV eax, moffs32
    { const_string("MOV"), 0xa1, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read}, {OPERAND_moffs64, 0}} }, // REX.W a1 - MOV rax, moffs64
    { const_string("MOV"), 0xa2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_moffs8, 0}, {OPERAND_al, OPERAND_FLAG_read}} }, // a2 - MOV moffs8, al
    { const_string("MOV"), 0xa2, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_moffs8, 0}, {OPERAND_al, OPERAND_FLAG_read}} }, // REX.W a2 - MOV moffs8, al
    { const_string("MOV"), 0xa3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_moffs16, 0}, {OPERAND_ax, OPERAND_FLAG_read}} }, // 66 a3 - MOV moffs16, ax
    { const_string("MOV"), 0xa3, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_moffs32, 0}, {OPERAND_eax, OPERAND_FLAG_read}} }, // a3 - MOV moffs32, eax
    { const_string("MOV"), 0xa3, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_moffs64, 0}, {OPERAND_rax, OPERAND_FLAG_read}} }, // REX.W a3 - MOV moffs64, rax
    { const_string("MOVSB"), 0xa4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // a4 - MOVSB 
    { const_string("MOVSW"), 0xa5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 a5 - MOVSW 
    { const_string("MOVSD"), 0xa5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // a5 - MOVSD 
    { const_string("MOVSQ"), 0xa5, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W a5 - MOVSQ 
    { const_string("CMPSB"), 0xa6, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // a6 - CMPSB 
    { const_string("CMPSW"), 0xa7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 a7 - CMPSW 
    { const_string("CMPSD"), 0xa7, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // a7 - CMPSD 
    { const_string("CMPSQ"), 0xa7, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W a7 - CMPSQ 
    { const_string("TEST"), 0xa8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // a8 ib - TEST al, imm8
    { const_string("TEST"), 0xa9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 a9 iw - TEST ax, imm16
    { const_string("TEST"), 0xa9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // a9 id - TEST eax, imm32
    { const_string("TEST"), 0xa9, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_rax, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W a9 id - TEST rax, imm32
    { const_string("STOSB"), 0xaa, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // aa - STOSB 
    { const_string("STOSW"), 0xab, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 ab - STOSW 
    { const_string("STOSD"), 0xab, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // ab - STOSD 
    { const_string("STOSQ"), 0xab, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W ab - STOSQ 
    { const_string("LODSB"), 0xac, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // ac - LODSB 
    { const_string("LODSW"), 0xad, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 ad - LODSW 
    { const_string("LODSD"), 0xad, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // ad - LODSD 
    { const_string("LODSQ"), 0xad, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W ad - LODSQ 
    { const_string("SCASB"), 0xae, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // ae - SCASB 
    { const_string("SCASW"), 0xaf, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 af - SCASW 
    { const_string("SCASD"), 0xaf, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // af - SCASD 
    { const_string("SCASQ"), 0xaf, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W af - SCASQ 
    { const_string("MOV"), 0xb0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // b0 +reg ib - MOV +reg, imm8
    { const_string("MOV"), 0xb1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // b1 +reg ib - MOV +reg, imm8
    { const_string("MOV"), 0xb2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // b2 +reg ib - MOV +reg, imm8
    { const_string("MOV"), 0xb3, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // b3 +reg ib - MOV +reg, imm8
    { const_string("MOV"), 0xb4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // b4 +reg ib - MOV +reg, imm8
    { const_string("MOV"), 0xb5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // b5 +reg ib - MOV +reg, imm8
    { const_string("MOV"), 0xb6, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // b6 +reg ib - MOV +reg, imm8
    { const_string("MOV"), 0xb7, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // b7 +reg ib - MOV +reg, imm8
    { const_string("MOV"), 0xb8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode16, OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 b8 +reg iw - MOV +reg, imm16
    { const_string("MOV"), 0xb8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode32, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // b8 +reg id - MOV +reg, imm32
    { const_string("MOV"), 0xb8, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_opcode64, OPERAND_FLAG_write}, {OPERAND_imm64, 0}} }, // REX.W b8 +reg - MOV +reg, imm64
    { const_string("MOV"), 0xb9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode16, OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 b9 +reg iw - MOV +reg, imm16
    { const_string("MOV"), 0xb9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode32, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // b9 +reg id - MOV +reg, imm32
    { const_string("MOV"), 0xb9, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_opcode64, OPERAND_FLAG_write}, {OPERAND_imm64, 0}} }, // REX.W b9 +reg - MOV +reg, imm64
    { const_string("MOV"), 0xba, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode16, OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 ba +reg iw - MOV +reg, imm16
    { const_string("MOV"), 0xba, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode32, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // ba +reg id - MOV +reg, imm32
    { const_string("MOV"), 0xba, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_opcode64, OPERAND_FLAG_write}, {OPERAND_imm64, 0}} }, // REX.W ba +reg - MOV +reg, imm64
    { const_string("MOV"), 0xbb, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode16, OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 bb +reg iw - MOV +reg, imm16
    { const_string("MOV"), 0xbb, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode32, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // bb +reg id - MOV +reg, imm32
    { const_string("MOV"), 0xbb, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_opcode64, OPERAND_FLAG_write}, {OPERAND_imm64, 0}} }, // REX.W bb +reg - MOV +reg, imm64
    { const_string("MOV"), 0xbc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode16, OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 bc +reg iw - MOV +reg, imm16
    { const_string("MOV"), 0xbc, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode32, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // bc +reg id - MOV +reg, imm32
    { const_string("MOV"), 0xbc, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_opcode64, OPERAND_FLAG_write}, {OPERAND_imm64, 0}} }, // REX.W bc +reg - MOV +reg, imm64
    { const_string("MOV"), 0xbd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode16, OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 bd +reg iw - MOV +reg, imm16
    { const_string("MOV"), 0xbd, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode32, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // bd +reg id - MOV +reg, imm32
    { const_string("MOV"), 0xbd, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_opcode64, OPERAND_FLAG_write}, {OPERAND_imm64, 0}} }, // REX.W bd +reg - MOV +reg, imm64
    { const_string("MOV"), 0xbe, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode16, OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 be +reg iw - MOV +reg, imm16
    { const_string("MOV"), 0xbe, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode32, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // be +reg id - MOV +reg, imm32
    { const_string("MOV"), 0xbe, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_opcode64, OPERAND_FLAG_write}, {OPERAND_imm64, 0}} }, // REX.W be +reg - MOV +reg, imm64
    { const_string("MOV"), 0xbf, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode16, OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 bf +reg iw - MOV +reg, imm16
    { const_string("MOV"), 0xbf, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_opcode32, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // bf +reg id - MOV +reg, imm32
    { const_string("MOV"), 0xbf, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_opcode64, OPERAND_FLAG_write}, {OPERAND_imm64, 0}} }, // REX.W bf +reg - MOV +reg, imm64
    { const_string("ROL"), 0xc0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c0 /0 ib - ROL r/m8, imm8
    { const_string("ROR"), 0xc0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c0 /1 ib - ROR r/m8, imm8
    { const_string("RCL"), 0xc0, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c0 /2 ib - RCL r/m8, imm8
    { const_string("RCR"), 0xc0, -1, 0, 0, 0, 0, 0, 3, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c0 /3 ib - RCR r/m8, imm8
    { const_string("SHL"), 0xc0, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c0 /4 ib - SHL r/m8, imm8
    { const_string("SHR"), 0xc0, -1, 0, 0, 0, 0, 0, 5, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c0 /5 ib - SHR r/m8, imm8
    { const_string("SAR"), 0xc0, -1, 0, 0, 0, 0, 0, 7, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c0 /7 ib - SAR r/m8, imm8
    { const_string("ROL"), 0xc1, -1, 0, 0, 1, 0, 0, 0, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 c1 /0 ib - ROL r/m16, imm8
    { const_string("ROL"), 0xc1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c1 /0 ib - ROL r/m32, imm8
    { const_string("ROL"), 0xc1, -1, 0, 0, 0, 1, 0, 0, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W c1 /0 ib - ROL r/m64, imm8
    { const_string("ROR"), 0xc1, -1, 0, 0, 1, 0, 0, 1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 c1 /1 ib - ROR r/m16, imm8
    { const_string("ROR"), 0xc1, -1, 0, 0, 0, 0, 0, 1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c1 /1 ib - ROR r/m32, imm8
    { const_string("ROR"), 0xc1, -1, 0, 0, 0, 1, 0, 1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W c1 /1 ib - ROR r/m64, imm8
    { const_string("RCL"), 0xc1, -1, 0, 0, 1, 0, 0, 2, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 c1 /2 ib - RCL r/m16, imm8
    { const_string("RCL"), 0xc1, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c1 /2 ib - RCL r/m32, imm8
    { const_string("RCL"), 0xc1, -1, 0, 0, 0, 1, 0, 2, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W c1 /2 ib - RCL r/m64, imm8
    { const_string("RCR"), 0xc1, -1, 0, 0, 1, 0, 0, 3, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 c1 /3 ib - RCR r/m16, imm8
    { const_string("RCR"), 0xc1, -1, 0, 0, 0, 0, 0, 3, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c1 /3 ib - RCR r/m32, imm8
    { const_string("RCR"), 0xc1, -1, 0, 0, 0, 1, 0, 3, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W c1 /3 ib - RCR r/m64, imm8
    { const_string("SHL"), 0xc1, -1, 0, 0, 1, 0, 0, 4, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 c1 /4 ib - SHL r/m16, imm8
    { const_string("SHL"), 0xc1, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c1 /4 ib - SHL r/m32, imm8
    { const_string("SHL"), 0xc1, -1, 0, 0, 0, 1, 0, 4, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W c1 /4 ib - SHL r/m64, imm8
    { const_string("SHR"), 0xc1, -1, 0, 0, 1, 0, 0, 5, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 c1 /5 ib - SHR r/m16, imm8
    { const_string("SHR"), 0xc1, -1, 0, 0, 0, 0, 0, 5, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c1 /5 ib - SHR r/m32, imm8
    { const_string("SHR"), 0xc1, -1, 0, 0, 0, 1, 0, 5, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W c1 /5 ib - SHR r/m64, imm8
    { const_string("SAR"), 0xc1, -1, 0, 0, 1, 0, 0, 7, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 c1 /7 ib - SAR r/m16, imm8
    { const_string("SAR"), 0xc1, -1, 0, 0, 0, 0, 0, 7, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c1 /7 ib - SAR r/m32, imm8
    { const_string("SAR"), 0xc1, -1, 0, 0, 0, 1, 0, 7, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W c1 /7 ib - SAR r/m64, imm8
    { const_string("RET"), 0xc2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_imm16, 0}} }, // c2 iw - RET imm16
    { const_string("RET"), 0xc3, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // c3 - RET 
    { const_string("MOV"), 0xc6, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // c6 /0 ib - MOV r/m8, imm8
    { const_string("XABORT"), 0xc6, 248, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_imm8, 0}} }, // c6 f8 ib - XABORT imm8
    { const_string("MOV"), 0xc7, -1, 0, 0, 1, 0, 0, 0, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_imm16, 0}} }, // 66 c7 /0 iw - MOV r/m16, imm16
    { const_string("MOV"), 0xc7, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // c7 /0 id - MOV r/m32, imm32
    { const_string("MOV"), 0xc7, -1, 0, 0, 0, 1, 0, 0, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_imm32, 0}} }, // REX.W c7 /0 id - MOV r/m64, imm32
    { const_string("XBEGIN"), 0xc7, 248, 0, 0, 1, 0, 0, -1, 0, 0, 1, {{OPERAND_rel16, 0}} }, // 66 c7 f8 - XBEGIN rel16
    { const_string("XBEGIN"), 0xc7, 248, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // c7 f8 - XBEGIN rel32
    { const_string("ENTER"), 0xc8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_imm16, 0}, {OPERAND_imm8, 0}} }, // c8 iw - ENTER imm16, imm8
    { const_string("LEAVE"), 0xc9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // c9 - LEAVE 
    { const_string("RET"), 0xca, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_imm16, 0}} }, // ca iw - RET imm16
    { const_string("RET"), 0xcb, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // cb - RET 
    { const_string("INT3"), 0xcc, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // cc - INT3 
    { const_string("INT"), 0xcd, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_imm8, 0}} }, // cd ib - INT imm8
    { const_string("IRET"), 0xcf, -1, 0, 0, 1, 0, 0, -1, 0, 0, 0,  }, // 66 cf - IRET 
    { const_string("IRETD"), 0xcf, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // cf - IRETD 
    { const_string("IRETQ"), 0xcf, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W cf - IRETQ 
    { const_string("ROL"), 0xd0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d0 /0 - ROL r/m8, 1
    { const_string("ROR"), 0xd0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d0 /1 - ROR r/m8, 1
    { const_string("RCL"), 0xd0, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d0 /2 - RCL r/m8, 1
    { const_string("RCR"), 0xd0, -1, 0, 0, 0, 0, 0, 3, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d0 /3 - RCR r/m8, 1
    { const_string("SHL"), 0xd0, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d0 /4 - SHL r/m8, 1
    { const_string("SHR"), 0xd0, -1, 0, 0, 0, 0, 0, 5, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d0 /5 - SHR r/m8, 1
    { const_string("SAR"), 0xd0, -1, 0, 0, 0, 0, 0, 7, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d0 /7 - SAR r/m8, 1
    { const_string("ROL"), 0xd1, -1, 0, 0, 1, 0, 0, 0, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // 66 d1 /0 - ROL r/m16, 1
    { const_string("ROL"), 0xd1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d1 /0 - ROL r/m32, 1
    { const_string("ROL"), 0xd1, -1, 0, 0, 0, 1, 0, 0, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // REX.W d1 /0 - ROL r/m64, 1
    { const_string("ROR"), 0xd1, -1, 0, 0, 1, 0, 0, 1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // 66 d1 /1 - ROR r/m16, 1
    { const_string("ROR"), 0xd1, -1, 0, 0, 0, 0, 0, 1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d1 /1 - ROR r/m32, 1
    { const_string("ROR"), 0xd1, -1, 0, 0, 0, 1, 0, 1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // REX.W d1 /1 - ROR r/m64, 1
    { const_string("RCL"), 0xd1, -1, 0, 0, 1, 0, 0, 2, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // 66 d1 /2 - RCL r/m16, 1
    { const_string("RCL"), 0xd1, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d1 /2 - RCL r/m32, 1
    { const_string("RCL"), 0xd1, -1, 0, 0, 0, 1, 0, 2, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // REX.W d1 /2 - RCL r/m64, 1
    { const_string("RCR"), 0xd1, -1, 0, 0, 1, 0, 0, 3, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // 66 d1 /3 - RCR r/m16, 1
    { const_string("RCR"), 0xd1, -1, 0, 0, 0, 0, 0, 3, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d1 /3 - RCR r/m32, 1
    { const_string("RCR"), 0xd1, -1, 0, 0, 0, 1, 0, 3, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // REX.W d1 /3 - RCR r/m64, 1
    { const_string("SHL"), 0xd1, -1, 0, 0, 1, 0, 0, 4, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // 66 d1 /4 - SHL r/m16, 1
    { const_string("SHL"), 0xd1, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d1 /4 - SHL r/m32, 1
    { const_string("SHL"), 0xd1, -1, 0, 0, 0, 1, 0, 4, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // REX.W d1 /4 - SHL r/m64, 1
    { const_string("SHR"), 0xd1, -1, 0, 0, 1, 0, 0, 5, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // 66 d1 /5 - SHR r/m16, 1
    { const_string("SHR"), 0xd1, -1, 0, 0, 0, 0, 0, 5, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d1 /5 - SHR r/m32, 1
    { const_string("SHR"), 0xd1, -1, 0, 0, 0, 1, 0, 5, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // REX.W d1 /5 - SHR r/m64, 1
    { const_string("SAR"), 0xd1, -1, 0, 0, 1, 0, 0, 7, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // 66 d1 /7 - SAR r/m16, 1
    { const_string("SAR"), 0xd1, -1, 0, 0, 0, 0, 0, 7, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // d1 /7 - SAR r/m32, 1
    { const_string("SAR"), 0xd1, -1, 0, 0, 0, 1, 0, 7, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_1, 0}} }, // REX.W d1 /7 - SAR r/m64, 1
    { const_string("ROL"), 0xd2, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d2 /0 - ROL r/m8, cl
    { const_string("ROR"), 0xd2, -1, 0, 0, 0, 0, 0, 1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d2 /1 - ROR r/m8, cl
    { const_string("RCL"), 0xd2, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d2 /2 - RCL r/m8, cl
    { const_string("RCR"), 0xd2, -1, 0, 0, 0, 0, 0, 3, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d2 /3 - RCR r/m8, cl
    { const_string("SHL"), 0xd2, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d2 /4 - SHL r/m8, cl
    { const_string("SHR"), 0xd2, -1, 0, 0, 0, 0, 0, 5, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d2 /5 - SHR r/m8, cl
    { const_string("SAR"), 0xd2, -1, 0, 0, 0, 0, 0, 7, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d2 /7 - SAR r/m8, cl
    { const_string("ROL"), 0xd3, -1, 0, 0, 1, 0, 0, 0, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // 66 d3 /0 - ROL r/m16, cl
    { const_string("ROL"), 0xd3, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d3 /0 - ROL r/m32, cl
    { const_string("ROL"), 0xd3, -1, 0, 0, 0, 1, 0, 0, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // REX.W d3 /0 - ROL r/m64, cl
    { const_string("ROR"), 0xd3, -1, 0, 0, 1, 0, 0, 1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // 66 d3 /1 - ROR r/m16, cl
    { const_string("ROR"), 0xd3, -1, 0, 0, 0, 0, 0, 1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d3 /1 - ROR r/m32, cl
    { const_string("ROR"), 0xd3, -1, 0, 0, 0, 1, 0, 1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // REX.W d3 /1 - ROR r/m64, cl
    { const_string("RCL"), 0xd3, -1, 0, 0, 1, 0, 0, 2, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // 66 d3 /2 - RCL r/m16, cl
    { const_string("RCL"), 0xd3, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d3 /2 - RCL r/m32, cl
    { const_string("RCL"), 0xd3, -1, 0, 0, 0, 1, 0, 2, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // REX.W d3 /2 - RCL r/m64, cl
    { const_string("RCR"), 0xd3, -1, 0, 0, 1, 0, 0, 3, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // 66 d3 /3 - RCR r/m16, cl
    { const_string("RCR"), 0xd3, -1, 0, 0, 0, 0, 0, 3, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d3 /3 - RCR r/m32, cl
    { const_string("RCR"), 0xd3, -1, 0, 0, 0, 1, 0, 3, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // REX.W d3 /3 - RCR r/m64, cl
    { const_string("SHL"), 0xd3, -1, 0, 0, 1, 0, 0, 4, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // 66 d3 /4 - SHL r/m16, cl
    { const_string("SHL"), 0xd3, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d3 /4 - SHL r/m32, cl
    { const_string("SHL"), 0xd3, -1, 0, 0, 0, 1, 0, 4, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // REX.W d3 /4 - SHL r/m64, cl
    { const_string("SHR"), 0xd3, -1, 0, 0, 1, 0, 0, 5, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // 66 d3 /5 - SHR r/m16, cl
    { const_string("SHR"), 0xd3, -1, 0, 0, 0, 0, 0, 5, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d3 /5 - SHR r/m32, cl
    { const_string("SHR"), 0xd3, -1, 0, 0, 0, 1, 0, 5, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // REX.W d3 /5 - SHR r/m64, cl
    { const_string("SAR"), 0xd3, -1, 0, 0, 1, 0, 0, 7, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // 66 d3 /7 - SAR r/m16, cl
    { const_string("SAR"), 0xd3, -1, 0, 0, 0, 0, 0, 7, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // d3 /7 - SAR r/m32, cl
    { const_string("SAR"), 0xd3, -1, 0, 0, 0, 1, 0, 7, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_cl, 0}} }, // REX.W d3 /7 - SAR r/m64, cl
    { const_string("XLATB"), 0xd7, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d7 - XLATB 
    { const_string("XLATB"), 0xd7, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W d7 - XLATB 
    { const_string("FADD"), 0xd8, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_mem, 0}} }, // d8 /0 - FADD mem
    { const_string("FMUL"), 0xd8, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_mem, 0}} }, // d8 /1 - FMUL mem
    { const_string("FCOM"), 0xd8, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_mem, 0}} }, // d8 /2 - FCOM mem
    { const_string("FCOMP"), 0xd8, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_mem, 0}} }, // d8 /3 - FCOMP mem
    { const_string("FSUB"), 0xd8, -1, 0, 0, 0, 0, 1, 4, 0, 0, 1, {{OPERAND_mem, 0}} }, // d8 /4 - FSUB mem
    { const_string("FSUBR"), 0xd8, -1, 0, 0, 0, 0, 1, 5, 0, 0, 1, {{OPERAND_mem, 0}} }, // d8 /5 - FSUBR mem
    { const_string("FDIV"), 0xd8, -1, 0, 0, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_mem, 0}} }, // d8 /6 - FDIV mem
    { const_string("FDIVR"), 0xd8, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_mem, 0}} }, // d8 /7 - FDIVR mem
    { const_string("FADD"), 0xd8, 192, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 c0 - FADD ST(0), ST(i)
    { const_string("FADD"), 0xd8, 193, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 c1 - FADD ST(0), ST(i)
    { const_string("FADD"), 0xd8, 194, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 c2 - FADD ST(0), ST(i)
    { const_string("FADD"), 0xd8, 195, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 c3 - FADD ST(0), ST(i)
    { const_string("FADD"), 0xd8, 196, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 c4 - FADD ST(0), ST(i)
    { const_string("FADD"), 0xd8, 197, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 c5 - FADD ST(0), ST(i)
    { const_string("FADD"), 0xd8, 198, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 c6 - FADD ST(0), ST(i)
    { const_string("FADD"), 0xd8, 199, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 c7 - FADD ST(0), ST(i)
    { const_string("FMUL"), 0xd8, 200, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 c8 - FMUL ST(0), ST(i)
    { const_string("FMUL"), 0xd8, 201, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 c9 - FMUL ST(0), ST(i)
    { const_string("FMUL"), 0xd8, 202, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 ca - FMUL ST(0), ST(i)
    { const_string("FMUL"), 0xd8, 203, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 cb - FMUL ST(0), ST(i)
    { const_string("FMUL"), 0xd8, 204, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 cc - FMUL ST(0), ST(i)
    { const_string("FMUL"), 0xd8, 205, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 cd - FMUL ST(0), ST(i)
    { const_string("FMUL"), 0xd8, 206, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 ce - FMUL ST(0), ST(i)
    { const_string("FMUL"), 0xd8, 207, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 cf - FMUL ST(0), ST(i)
    { const_string("FCOM"), 0xd8, 208, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 d0 - FCOM ST(i)
    { const_string("FCOM"), 0xd8, 209, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d8 d1 - FCOM 
    { const_string("FCOM"), 0xd8, 210, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 d2 - FCOM ST(i)
    { const_string("FCOM"), 0xd8, 211, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 d3 - FCOM ST(i)
    { const_string("FCOM"), 0xd8, 212, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 d4 - FCOM ST(i)
    { const_string("FCOM"), 0xd8, 213, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 d5 - FCOM ST(i)
    { const_string("FCOM"), 0xd8, 214, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 d6 - FCOM ST(i)
    { const_string("FCOM"), 0xd8, 215, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 d7 - FCOM ST(i)
    { const_string("FCOMP"), 0xd8, 216, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 d8 - FCOMP ST(i)
    { const_string("FCOMP"), 0xd8, 217, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d8 d9 - FCOMP 
    { const_string("FCOMP"), 0xd8, 218, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 da - FCOMP ST(i)
    { const_string("FCOMP"), 0xd8, 219, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 db - FCOMP ST(i)
    { const_string("FCOMP"), 0xd8, 220, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 dc - FCOMP ST(i)
    { const_string("FCOMP"), 0xd8, 221, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 dd - FCOMP ST(i)
    { const_string("FCOMP"), 0xd8, 222, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 de - FCOMP ST(i)
    { const_string("FCOMP"), 0xd8, 223, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d8 df - FCOMP ST(i)
    { const_string("FSUB"), 0xd8, 224, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 e0 - FSUB ST(0), ST(i)
    { const_string("FSUB"), 0xd8, 225, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 e1 - FSUB ST(0), ST(i)
    { const_string("FSUB"), 0xd8, 226, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 e2 - FSUB ST(0), ST(i)
    { const_string("FSUB"), 0xd8, 227, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 e3 - FSUB ST(0), ST(i)
    { const_string("FSUB"), 0xd8, 228, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 e4 - FSUB ST(0), ST(i)
    { const_string("FSUB"), 0xd8, 229, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 e5 - FSUB ST(0), ST(i)
    { const_string("FSUB"), 0xd8, 230, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 e6 - FSUB ST(0), ST(i)
    { const_string("FSUB"), 0xd8, 231, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 e7 - FSUB ST(0), ST(i)
    { const_string("FSUBR"), 0xd8, 232, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 e8 - FSUBR ST(0), ST(i)
    { const_string("FSUBR"), 0xd8, 233, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 e9 - FSUBR ST(0), ST(i)
    { const_string("FSUBR"), 0xd8, 234, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 ea - FSUBR ST(0), ST(i)
    { const_string("FSUBR"), 0xd8, 235, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 eb - FSUBR ST(0), ST(i)
    { const_string("FSUBR"), 0xd8, 236, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 ec - FSUBR ST(0), ST(i)
    { const_string("FSUBR"), 0xd8, 237, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 ed - FSUBR ST(0), ST(i)
    { const_string("FSUBR"), 0xd8, 238, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 ee - FSUBR ST(0), ST(i)
    { const_string("FSUBR"), 0xd8, 239, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 ef - FSUBR ST(0), ST(i)
    { const_string("FDIV"), 0xd8, 240, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 f0 - FDIV ST(0), ST(i)
    { const_string("FDIV"), 0xd8, 241, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 f1 - FDIV ST(0), ST(i)
    { const_string("FDIV"), 0xd8, 242, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 f2 - FDIV ST(0), ST(i)
    { const_string("FDIV"), 0xd8, 243, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 f3 - FDIV ST(0), ST(i)
    { const_string("FDIV"), 0xd8, 244, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 f4 - FDIV ST(0), ST(i)
    { const_string("FDIV"), 0xd8, 245, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 f5 - FDIV ST(0), ST(i)
    { const_string("FDIV"), 0xd8, 246, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 f6 - FDIV ST(0), ST(i)
    { const_string("FDIV"), 0xd8, 247, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 f7 - FDIV ST(0), ST(i)
    { const_string("FDIVR"), 0xd8, 248, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 f8 - FDIVR ST(0), ST(i)
    { const_string("FDIVR"), 0xd8, 249, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 f9 - FDIVR ST(0), ST(i)
    { const_string("FDIVR"), 0xd8, 250, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 fa - FDIVR ST(0), ST(i)
    { const_string("FDIVR"), 0xd8, 251, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 fb - FDIVR ST(0), ST(i)
    { const_string("FDIVR"), 0xd8, 252, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 fc - FDIVR ST(0), ST(i)
    { const_string("FDIVR"), 0xd8, 253, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 fd - FDIVR ST(0), ST(i)
    { const_string("FDIVR"), 0xd8, 254, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 fe - FDIVR ST(0), ST(i)
    { const_string("FDIVR"), 0xd8, 255, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // d8 ff - FDIVR ST(0), ST(i)
    { const_string("FLD"), 0xd9, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_mem, 0}} }, // d9 /0 - FLD mem
    { const_string("FST"), 0xd9, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_mem, 0}} }, // d9 /2 - FST mem
    { const_string("FSTP"), 0xd9, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_mem, 0}} }, // d9 /3 - FSTP mem
    { const_string("FLDENV"), 0xd9, -1, 0, 0, 0, 0, 1, 4, 0, 0, 1, {{OPERAND_mem, 0}} }, // d9 /4 - FLDENV mem
    { const_string("FLDCW"), 0xd9, -1, 0, 0, 0, 0, 1, 5, 0, 0, 1, {{OPERAND_mem, 0}} }, // d9 /5 - FLDCW mem
    { const_string("FNSTENV"), 0xd9, -1, 0, 0, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_mem, 0}} }, // d9 /6 - FNSTENV mem
    { const_string("FNSTCW"), 0xd9, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_mem, 0}} }, // d9 /7 - FNSTCW mem
    { const_string("FLD"), 0xd9, 192, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 c0 - FLD ST(i)
    { const_string("FLD"), 0xd9, 193, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 c1 - FLD ST(i)
    { const_string("FLD"), 0xd9, 194, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 c2 - FLD ST(i)
    { const_string("FLD"), 0xd9, 195, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 c3 - FLD ST(i)
    { const_string("FLD"), 0xd9, 196, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 c4 - FLD ST(i)
    { const_string("FLD"), 0xd9, 197, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 c5 - FLD ST(i)
    { const_string("FLD"), 0xd9, 198, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 c6 - FLD ST(i)
    { const_string("FLD"), 0xd9, 199, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 c7 - FLD ST(i)
    { const_string("FXCH"), 0xd9, 200, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 c8 - FXCH ST(i)
    { const_string("FXCH"), 0xd9, 201, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 c9 - FXCH 
    { const_string("FXCH"), 0xd9, 202, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 ca - FXCH ST(i)
    { const_string("FXCH"), 0xd9, 203, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 cb - FXCH ST(i)
    { const_string("FXCH"), 0xd9, 204, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 cc - FXCH ST(i)
    { const_string("FXCH"), 0xd9, 205, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 cd - FXCH ST(i)
    { const_string("FXCH"), 0xd9, 206, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 ce - FXCH ST(i)
    { const_string("FXCH"), 0xd9, 207, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // d9 cf - FXCH ST(i)
    { const_string("FNOP"), 0xd9, 208, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 d0 - FNOP 
    { const_string("FCHS"), 0xd9, 224, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 e0 - FCHS 
    { const_string("FABS"), 0xd9, 225, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 e1 - FABS 
    { const_string("FTST"), 0xd9, 228, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 e4 - FTST 
    { const_string("FXAM"), 0xd9, 229, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 e5 - FXAM 
    { const_string("FLD1"), 0xd9, 232, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 e8 - FLD1 
    { const_string("FLDL2T"), 0xd9, 233, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 e9 - FLDL2T 
    { const_string("FLDL2E"), 0xd9, 234, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 ea - FLDL2E 
    { const_string("FLDPI"), 0xd9, 235, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 eb - FLDPI 
    { const_string("FLDLG2"), 0xd9, 236, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 ec - FLDLG2 
    { const_string("FLDLN2"), 0xd9, 237, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 ed - FLDLN2 
    { const_string("FLDZ"), 0xd9, 238, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 ee - FLDZ 
    { const_string("F2XM1"), 0xd9, 240, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 f0 - F2XM1 
    { const_string("FYL2X"), 0xd9, 241, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 f1 - FYL2X 
    { const_string("FPTAN"), 0xd9, 242, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 f2 - FPTAN 
    { const_string("FPATAN"), 0xd9, 243, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 f3 - FPATAN 
    { const_string("FXTRACT"), 0xd9, 244, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 f4 - FXTRACT 
    { const_string("FPREM1"), 0xd9, 245, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 f5 - FPREM1 
    { const_string("FDECSTP"), 0xd9, 246, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 f6 - FDECSTP 
    { const_string("FINCSTP"), 0xd9, 247, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 f7 - FINCSTP 
    { const_string("FPREM"), 0xd9, 248, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 f8 - FPREM 
    { const_string("FYL2XP1"), 0xd9, 249, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 f9 - FYL2XP1 
    { const_string("FSQRT"), 0xd9, 250, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 fa - FSQRT 
    { const_string("FSINCOS"), 0xd9, 251, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 fb - FSINCOS 
    { const_string("FRNDINT"), 0xd9, 252, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 fc - FRNDINT 
    { const_string("FSCALE"), 0xd9, 253, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 fd - FSCALE 
    { const_string("FSIN"), 0xd9, 254, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 fe - FSIN 
    { const_string("FCOS"), 0xd9, 255, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // d9 ff - FCOS 
    { const_string("FIADD"), 0xda, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_mem, 0}} }, // da /0 - FIADD mem
    { const_string("FIMUL"), 0xda, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_mem, 0}} }, // da /1 - FIMUL mem
    { const_string("FICOM"), 0xda, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_mem, 0}} }, // da /2 - FICOM mem
    { const_string("FICOMP"), 0xda, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_mem, 0}} }, // da /3 - FICOMP mem
    { const_string("FISUB"), 0xda, -1, 0, 0, 0, 0, 1, 4, 0, 0, 1, {{OPERAND_mem, 0}} }, // da /4 - FISUB mem
    { const_string("FISUBR"), 0xda, -1, 0, 0, 0, 0, 1, 5, 0, 0, 1, {{OPERAND_mem, 0}} }, // da /5 - FISUBR mem
    { const_string("FIDIV"), 0xda, -1, 0, 0, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_mem, 0}} }, // da /6 - FIDIV mem
    { const_string("FIDIVR"), 0xda, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_mem, 0}} }, // da /7 - FIDIVR mem
    { const_string("FCMOVB"), 0xda, 192, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da c0 - FCMOVB ST(0), ST(i)
    { const_string("FCMOVB"), 0xda, 193, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da c1 - FCMOVB ST(0), ST(i)
    { const_string("FCMOVB"), 0xda, 194, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da c2 - FCMOVB ST(0), ST(i)
    { const_string("FCMOVB"), 0xda, 195, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da c3 - FCMOVB ST(0), ST(i)
    { const_string("FCMOVB"), 0xda, 196, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da c4 - FCMOVB ST(0), ST(i)
    { const_string("FCMOVB"), 0xda, 197, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da c5 - FCMOVB ST(0), ST(i)
    { const_string("FCMOVB"), 0xda, 198, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da c6 - FCMOVB ST(0), ST(i)
    { const_string("FCMOVB"), 0xda, 199, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da c7 - FCMOVB ST(0), ST(i)
    { const_string("FCMOVE"), 0xda, 200, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da c8 - FCMOVE ST(0), ST(i)
    { const_string("FCMOVE"), 0xda, 201, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da c9 - FCMOVE ST(0), ST(i)
    { const_string("FCMOVE"), 0xda, 202, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da ca - FCMOVE ST(0), ST(i)
    { const_string("FCMOVE"), 0xda, 203, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da cb - FCMOVE ST(0), ST(i)
    { const_string("FCMOVE"), 0xda, 204, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da cc - FCMOVE ST(0), ST(i)
    { const_string("FCMOVE"), 0xda, 205, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da cd - FCMOVE ST(0), ST(i)
    { const_string("FCMOVE"), 0xda, 206, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da ce - FCMOVE ST(0), ST(i)
    { const_string("FCMOVE"), 0xda, 207, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da cf - FCMOVE ST(0), ST(i)
    { const_string("FCMOVBE"), 0xda, 208, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da d0 - FCMOVBE ST(0), ST(i)
    { const_string("FCMOVBE"), 0xda, 209, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da d1 - FCMOVBE ST(0), ST(i)
    { const_string("FCMOVBE"), 0xda, 210, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da d2 - FCMOVBE ST(0), ST(i)
    { const_string("FCMOVBE"), 0xda, 211, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da d3 - FCMOVBE ST(0), ST(i)
    { const_string("FCMOVBE"), 0xda, 212, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da d4 - FCMOVBE ST(0), ST(i)
    { const_string("FCMOVBE"), 0xda, 213, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da d5 - FCMOVBE ST(0), ST(i)
    { const_string("FCMOVBE"), 0xda, 214, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da d6 - FCMOVBE ST(0), ST(i)
    { const_string("FCMOVBE"), 0xda, 215, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da d7 - FCMOVBE ST(0), ST(i)
    { const_string("FCMOVU"), 0xda, 216, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da d8 - FCMOVU ST(0), ST(i)
    { const_string("FCMOVU"), 0xda, 217, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da d9 - FCMOVU ST(0), ST(i)
    { const_string("FCMOVU"), 0xda, 218, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da da - FCMOVU ST(0), ST(i)
    { const_string("FCMOVU"), 0xda, 219, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da db - FCMOVU ST(0), ST(i)
    { const_string("FCMOVU"), 0xda, 220, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da dc - FCMOVU ST(0), ST(i)
    { const_string("FCMOVU"), 0xda, 221, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da dd - FCMOVU ST(0), ST(i)
    { const_string("FCMOVU"), 0xda, 222, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da de - FCMOVU ST(0), ST(i)
    { const_string("FCMOVU"), 0xda, 223, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // da df - FCMOVU ST(0), ST(i)
    { const_string("FUCOMPP"), 0xda, 233, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // da e9 - FUCOMPP 
    { const_string("FILD"), 0xdb, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_mem, 0}} }, // db /0 - FILD mem
    { const_string("FISTTP"), 0xdb, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_mem, 0}} }, // db /1 - FISTTP mem
    { const_string("FIST"), 0xdb, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_mem, 0}} }, // db /2 - FIST mem
    { const_string("FISTP"), 0xdb, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_mem, 0}} }, // db /3 - FISTP mem
    { const_string("FLD"), 0xdb, -1, 0, 0, 0, 0, 1, 5, 0, 0, 1, {{OPERAND_mem, 0}} }, // db /5 - FLD mem
    { const_string("FSTP"), 0xdb, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_mem, 0}} }, // db /7 - FSTP mem
    { const_string("FCMOVNB"), 0xdb, 192, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db c0 - FCMOVNB ST(0), ST(i)
    { const_string("FCMOVNB"), 0xdb, 193, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db c1 - FCMOVNB ST(0), ST(i)
    { const_string("FCMOVNB"), 0xdb, 194, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db c2 - FCMOVNB ST(0), ST(i)
    { const_string("FCMOVNB"), 0xdb, 195, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db c3 - FCMOVNB ST(0), ST(i)
    { const_string("FCMOVNB"), 0xdb, 196, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db c4 - FCMOVNB ST(0), ST(i)
    { const_string("FCMOVNB"), 0xdb, 197, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db c5 - FCMOVNB ST(0), ST(i)
    { const_string("FCMOVNB"), 0xdb, 198, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db c6 - FCMOVNB ST(0), ST(i)
    { const_string("FCMOVNB"), 0xdb, 199, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db c7 - FCMOVNB ST(0), ST(i)
    { const_string("FCMOVNE"), 0xdb, 200, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db c8 - FCMOVNE ST(0), ST(i)
    { const_string("FCMOVNE"), 0xdb, 201, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db c9 - FCMOVNE ST(0), ST(i)
    { const_string("FCMOVNE"), 0xdb, 202, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db ca - FCMOVNE ST(0), ST(i)
    { const_string("FCMOVNE"), 0xdb, 203, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db cb - FCMOVNE ST(0), ST(i)
    { const_string("FCMOVNE"), 0xdb, 204, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db cc - FCMOVNE ST(0), ST(i)
    { const_string("FCMOVNE"), 0xdb, 205, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db cd - FCMOVNE ST(0), ST(i)
    { const_string("FCMOVNE"), 0xdb, 206, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db ce - FCMOVNE ST(0), ST(i)
    { const_string("FCMOVNE"), 0xdb, 207, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db cf - FCMOVNE ST(0), ST(i)
    { const_string("FCMOVNBE"), 0xdb, 208, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db d0 - FCMOVNBE ST(0), ST(i)
    { const_string("FCMOVNBE"), 0xdb, 209, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db d1 - FCMOVNBE ST(0), ST(i)
    { const_string("FCMOVNBE"), 0xdb, 210, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db d2 - FCMOVNBE ST(0), ST(i)
    { const_string("FCMOVNBE"), 0xdb, 211, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db d3 - FCMOVNBE ST(0), ST(i)
    { const_string("FCMOVNBE"), 0xdb, 212, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db d4 - FCMOVNBE ST(0), ST(i)
    { const_string("FCMOVNBE"), 0xdb, 213, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db d5 - FCMOVNBE ST(0), ST(i)
    { const_string("FCMOVNBE"), 0xdb, 214, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db d6 - FCMOVNBE ST(0), ST(i)
    { const_string("FCMOVNBE"), 0xdb, 215, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db d7 - FCMOVNBE ST(0), ST(i)
    { const_string("FCMOVNU"), 0xdb, 216, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db d8 - FCMOVNU ST(0), ST(i)
    { const_string("FCMOVNU"), 0xdb, 217, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db d9 - FCMOVNU ST(0), ST(i)
    { const_string("FCMOVNU"), 0xdb, 218, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db da - FCMOVNU ST(0), ST(i)
    { const_string("FCMOVNU"), 0xdb, 219, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db db - FCMOVNU ST(0), ST(i)
    { const_string("FCMOVNU"), 0xdb, 220, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db dc - FCMOVNU ST(0), ST(i)
    { const_string("FCMOVNU"), 0xdb, 221, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db dd - FCMOVNU ST(0), ST(i)
    { const_string("FCMOVNU"), 0xdb, 222, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db de - FCMOVNU ST(0), ST(i)
    { const_string("FCMOVNU"), 0xdb, 223, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db df - FCMOVNU ST(0), ST(i)
    { const_string("FNCLEX"), 0xdb, 226, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // db e2 - FNCLEX 
    { const_string("FNINIT"), 0xdb, 227, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // db e3 - FNINIT 
    { const_string("FUCOMI"), 0xdb, 232, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db e8 - FUCOMI ST(0), ST(i)
    { const_string("FUCOMI"), 0xdb, 233, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db e9 - FUCOMI ST(0), ST(i)
    { const_string("FUCOMI"), 0xdb, 234, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db ea - FUCOMI ST(0), ST(i)
    { const_string("FUCOMI"), 0xdb, 235, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db eb - FUCOMI ST(0), ST(i)
    { const_string("FUCOMI"), 0xdb, 236, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db ec - FUCOMI ST(0), ST(i)
    { const_string("FUCOMI"), 0xdb, 237, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db ed - FUCOMI ST(0), ST(i)
    { const_string("FUCOMI"), 0xdb, 238, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db ee - FUCOMI ST(0), ST(i)
    { const_string("FUCOMI"), 0xdb, 239, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db ef - FUCOMI ST(0), ST(i)
    { const_string("FCOMI"), 0xdb, 240, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db f0 - FCOMI ST(0), ST(i)
    { const_string("FCOMI"), 0xdb, 241, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db f1 - FCOMI ST(0), ST(i)
    { const_string("FCOMI"), 0xdb, 242, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db f2 - FCOMI ST(0), ST(i)
    { const_string("FCOMI"), 0xdb, 243, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db f3 - FCOMI ST(0), ST(i)
    { const_string("FCOMI"), 0xdb, 244, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db f4 - FCOMI ST(0), ST(i)
    { const_string("FCOMI"), 0xdb, 245, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db f5 - FCOMI ST(0), ST(i)
    { const_string("FCOMI"), 0xdb, 246, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db f6 - FCOMI ST(0), ST(i)
    { const_string("FCOMI"), 0xdb, 247, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // db f7 - FCOMI ST(0), ST(i)
    { const_string("FADD"), 0xdc, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_mem, 0}} }, // dc /0 - FADD mem
    { const_string("FMUL"), 0xdc, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_mem, 0}} }, // dc /1 - FMUL mem
    { const_string("FCOM"), 0xdc, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_mem, 0}} }, // dc /2 - FCOM mem
    { const_string("FCOMP"), 0xdc, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_mem, 0}} }, // dc /3 - FCOMP mem
    { const_string("FSUB"), 0xdc, -1, 0, 0, 0, 0, 1, 4, 0, 0, 1, {{OPERAND_mem, 0}} }, // dc /4 - FSUB mem
    { const_string("FSUBR"), 0xdc, -1, 0, 0, 0, 0, 1, 5, 0, 0, 1, {{OPERAND_mem, 0}} }, // dc /5 - FSUBR mem
    { const_string("FDIV"), 0xdc, -1, 0, 0, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_mem, 0}} }, // dc /6 - FDIV mem
    { const_string("FDIVR"), 0xdc, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_mem, 0}} }, // dc /7 - FDIVR mem
    { const_string("FADD"), 0xdc, 192, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc c0 - FADD ST(i), ST(0)
    { const_string("FADD"), 0xdc, 193, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc c1 - FADD ST(i), ST(0)
    { const_string("FADD"), 0xdc, 194, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc c2 - FADD ST(i), ST(0)
    { const_string("FADD"), 0xdc, 195, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc c3 - FADD ST(i), ST(0)
    { const_string("FADD"), 0xdc, 196, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc c4 - FADD ST(i), ST(0)
    { const_string("FADD"), 0xdc, 197, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc c5 - FADD ST(i), ST(0)
    { const_string("FADD"), 0xdc, 198, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc c6 - FADD ST(i), ST(0)
    { const_string("FADD"), 0xdc, 199, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc c7 - FADD ST(i), ST(0)
    { const_string("FMUL"), 0xdc, 200, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc c8 - FMUL ST(i), ST(0)
    { const_string("FMUL"), 0xdc, 201, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc c9 - FMUL ST(i), ST(0)
    { const_string("FMUL"), 0xdc, 202, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc ca - FMUL ST(i), ST(0)
    { const_string("FMUL"), 0xdc, 203, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc cb - FMUL ST(i), ST(0)
    { const_string("FMUL"), 0xdc, 204, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc cc - FMUL ST(i), ST(0)
    { const_string("FMUL"), 0xdc, 205, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc cd - FMUL ST(i), ST(0)
    { const_string("FMUL"), 0xdc, 206, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc ce - FMUL ST(i), ST(0)
    { const_string("FMUL"), 0xdc, 207, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc cf - FMUL ST(i), ST(0)
    { const_string("FSUBR"), 0xdc, 224, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc e0 - FSUBR ST(i), ST(0)
    { const_string("FSUBR"), 0xdc, 225, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc e1 - FSUBR ST(i), ST(0)
    { const_string("FSUBR"), 0xdc, 226, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc e2 - FSUBR ST(i), ST(0)
    { const_string("FSUBR"), 0xdc, 227, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc e3 - FSUBR ST(i), ST(0)
    { const_string("FSUBR"), 0xdc, 228, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc e4 - FSUBR ST(i), ST(0)
    { const_string("FSUBR"), 0xdc, 229, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc e5 - FSUBR ST(i), ST(0)
    { const_string("FSUBR"), 0xdc, 230, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc e6 - FSUBR ST(i), ST(0)
    { const_string("FSUBR"), 0xdc, 231, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc e7 - FSUBR ST(i), ST(0)
    { const_string("FSUB"), 0xdc, 232, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc e8 - FSUB ST(i), ST(0)
    { const_string("FSUB"), 0xdc, 233, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc e9 - FSUB ST(i), ST(0)
    { const_string("FSUB"), 0xdc, 234, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc ea - FSUB ST(i), ST(0)
    { const_string("FSUB"), 0xdc, 235, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc eb - FSUB ST(i), ST(0)
    { const_string("FSUB"), 0xdc, 236, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc ec - FSUB ST(i), ST(0)
    { const_string("FSUB"), 0xdc, 237, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc ed - FSUB ST(i), ST(0)
    { const_string("FSUB"), 0xdc, 238, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc ee - FSUB ST(i), ST(0)
    { const_string("FSUB"), 0xdc, 239, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc ef - FSUB ST(i), ST(0)
    { const_string("FDIVR"), 0xdc, 240, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc f0 - FDIVR ST(i), ST(0)
    { const_string("FDIVR"), 0xdc, 241, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc f1 - FDIVR ST(i), ST(0)
    { const_string("FDIVR"), 0xdc, 242, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc f2 - FDIVR ST(i), ST(0)
    { const_string("FDIVR"), 0xdc, 243, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc f3 - FDIVR ST(i), ST(0)
    { const_string("FDIVR"), 0xdc, 244, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc f4 - FDIVR ST(i), ST(0)
    { const_string("FDIVR"), 0xdc, 245, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc f5 - FDIVR ST(i), ST(0)
    { const_string("FDIVR"), 0xdc, 246, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc f6 - FDIVR ST(i), ST(0)
    { const_string("FDIVR"), 0xdc, 247, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc f7 - FDIVR ST(i), ST(0)
    { const_string("FDIV"), 0xdc, 248, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc f8 - FDIV ST(i), ST(0)
    { const_string("FDIV"), 0xdc, 249, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc f9 - FDIV ST(i), ST(0)
    { const_string("FDIV"), 0xdc, 250, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc fa - FDIV ST(i), ST(0)
    { const_string("FDIV"), 0xdc, 251, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc fb - FDIV ST(i), ST(0)
    { const_string("FDIV"), 0xdc, 252, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc fc - FDIV ST(i), ST(0)
    { const_string("FDIV"), 0xdc, 253, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc fd - FDIV ST(i), ST(0)
    { const_string("FDIV"), 0xdc, 254, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc fe - FDIV ST(i), ST(0)
    { const_string("FDIV"), 0xdc, 255, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // dc ff - FDIV ST(i), ST(0)
    { const_string("FLD"), 0xdd, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_mem, 0}} }, // dd /0 - FLD mem
    { const_string("FISTTP"), 0xdd, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_mem, 0}} }, // dd /1 - FISTTP mem
    { const_string("FST"), 0xdd, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_mem, 0}} }, // dd /2 - FST mem
    { const_string("FSTP"), 0xdd, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_mem, 0}} }, // dd /3 - FSTP mem
    { const_string("FRSTOR"), 0xdd, -1, 0, 0, 0, 0, 1, 4, 0, 0, 1, {{OPERAND_mem, 0}} }, // dd /4 - FRSTOR mem
    { const_string("FNSAVE"), 0xdd, -1, 0, 0, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_mem, 0}} }, // dd /6 - FNSAVE mem
    { const_string("FNSTSW"), 0xdd, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_mem, 0}} }, // dd /7 - FNSTSW mem
    { const_string("FFREE"), 0xdd, 192, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd c0 - FFREE ST(i)
    { const_string("FFREE"), 0xdd, 193, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd c1 - FFREE ST(i)
    { const_string("FFREE"), 0xdd, 194, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd c2 - FFREE ST(i)
    { const_string("FFREE"), 0xdd, 195, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd c3 - FFREE ST(i)
    { const_string("FFREE"), 0xdd, 196, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd c4 - FFREE ST(i)
    { const_string("FFREE"), 0xdd, 197, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd c5 - FFREE ST(i)
    { const_string("FFREE"), 0xdd, 198, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd c6 - FFREE ST(i)
    { const_string("FFREE"), 0xdd, 199, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd c7 - FFREE ST(i)
    { const_string("FST"), 0xdd, 208, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd d0 - FST ST(i)
    { const_string("FST"), 0xdd, 209, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd d1 - FST ST(i)
    { const_string("FST"), 0xdd, 210, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd d2 - FST ST(i)
    { const_string("FST"), 0xdd, 211, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd d3 - FST ST(i)
    { const_string("FST"), 0xdd, 212, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd d4 - FST ST(i)
    { const_string("FST"), 0xdd, 213, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd d5 - FST ST(i)
    { const_string("FST"), 0xdd, 214, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd d6 - FST ST(i)
    { const_string("FST"), 0xdd, 215, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd d7 - FST ST(i)
    { const_string("FSTP"), 0xdd, 216, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd d8 - FSTP ST(i)
    { const_string("FSTP"), 0xdd, 217, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd d9 - FSTP ST(i)
    { const_string("FSTP"), 0xdd, 218, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd da - FSTP ST(i)
    { const_string("FSTP"), 0xdd, 219, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd db - FSTP ST(i)
    { const_string("FSTP"), 0xdd, 220, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd dc - FSTP ST(i)
    { const_string("FSTP"), 0xdd, 221, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd dd - FSTP ST(i)
    { const_string("FSTP"), 0xdd, 222, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd de - FSTP ST(i)
    { const_string("FSTP"), 0xdd, 223, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd df - FSTP ST(i)
    { const_string("FUCOM"), 0xdd, 224, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd e0 - FUCOM ST(i)
    { const_string("FUCOM"), 0xdd, 225, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // dd e1 - FUCOM 
    { const_string("FUCOM"), 0xdd, 226, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd e2 - FUCOM ST(i)
    { const_string("FUCOM"), 0xdd, 227, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd e3 - FUCOM ST(i)
    { const_string("FUCOM"), 0xdd, 228, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd e4 - FUCOM ST(i)
    { const_string("FUCOM"), 0xdd, 229, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd e5 - FUCOM ST(i)
    { const_string("FUCOM"), 0xdd, 230, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd e6 - FUCOM ST(i)
    { const_string("FUCOM"), 0xdd, 231, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd e7 - FUCOM ST(i)
    { const_string("FUCOMP"), 0xdd, 232, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd e8 - FUCOMP ST(i)
    { const_string("FUCOMP"), 0xdd, 233, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // dd e9 - FUCOMP 
    { const_string("FUCOMP"), 0xdd, 234, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd ea - FUCOMP ST(i)
    { const_string("FUCOMP"), 0xdd, 235, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd eb - FUCOMP ST(i)
    { const_string("FUCOMP"), 0xdd, 236, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd ec - FUCOMP ST(i)
    { const_string("FUCOMP"), 0xdd, 237, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd ed - FUCOMP ST(i)
    { const_string("FUCOMP"), 0xdd, 238, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd ee - FUCOMP ST(i)
    { const_string("FUCOMP"), 0xdd, 239, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_STi, 0}} }, // dd ef - FUCOMP ST(i)
    { const_string("FIADD"), 0xde, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_mem, 0}} }, // de /0 - FIADD mem
    { const_string("FIMUL"), 0xde, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_mem, 0}} }, // de /1 - FIMUL mem
    { const_string("FICOM"), 0xde, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_mem, 0}} }, // de /2 - FICOM mem
    { const_string("FICOMP"), 0xde, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_mem, 0}} }, // de /3 - FICOMP mem
    { const_string("FISUB"), 0xde, -1, 0, 0, 0, 0, 1, 4, 0, 0, 1, {{OPERAND_mem, 0}} }, // de /4 - FISUB mem
    { const_string("FISUBR"), 0xde, -1, 0, 0, 0, 0, 1, 5, 0, 0, 1, {{OPERAND_mem, 0}} }, // de /5 - FISUBR mem
    { const_string("FIDIV"), 0xde, -1, 0, 0, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_mem, 0}} }, // de /6 - FIDIV mem
    { const_string("FIDIVR"), 0xde, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_mem, 0}} }, // de /7 - FIDIVR mem
    { const_string("FADDP"), 0xde, 192, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de c0 - FADDP ST(i), ST(0)
    { const_string("FADDP"), 0xde, 193, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // de c1 - FADDP 
    { const_string("FADDP"), 0xde, 194, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de c2 - FADDP ST(i), ST(0)
    { const_string("FADDP"), 0xde, 195, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de c3 - FADDP ST(i), ST(0)
    { const_string("FADDP"), 0xde, 196, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de c4 - FADDP ST(i), ST(0)
    { const_string("FADDP"), 0xde, 197, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de c5 - FADDP ST(i), ST(0)
    { const_string("FADDP"), 0xde, 198, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de c6 - FADDP ST(i), ST(0)
    { const_string("FADDP"), 0xde, 199, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de c7 - FADDP ST(i), ST(0)
    { const_string("FMULP"), 0xde, 200, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de c8 - FMULP ST(i), ST(0)
    { const_string("FMULP"), 0xde, 201, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // de c9 - FMULP 
    { const_string("FMULP"), 0xde, 202, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de ca - FMULP ST(i), ST(0)
    { const_string("FMULP"), 0xde, 203, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de cb - FMULP ST(i), ST(0)
    { const_string("FMULP"), 0xde, 204, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de cc - FMULP ST(i), ST(0)
    { const_string("FMULP"), 0xde, 205, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de cd - FMULP ST(i), ST(0)
    { const_string("FMULP"), 0xde, 206, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de ce - FMULP ST(i), ST(0)
    { const_string("FMULP"), 0xde, 207, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de cf - FMULP ST(i), ST(0)
    { const_string("FCOMPP"), 0xde, 217, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // de d9 - FCOMPP 
    { const_string("FSUBRP"), 0xde, 224, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de e0 - FSUBRP ST(i), ST(0)
    { const_string("FSUBRP"), 0xde, 225, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // de e1 - FSUBRP 
    { const_string("FSUBRP"), 0xde, 226, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de e2 - FSUBRP ST(i), ST(0)
    { const_string("FSUBRP"), 0xde, 227, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de e3 - FSUBRP ST(i), ST(0)
    { const_string("FSUBRP"), 0xde, 228, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de e4 - FSUBRP ST(i), ST(0)
    { const_string("FSUBRP"), 0xde, 229, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de e5 - FSUBRP ST(i), ST(0)
    { const_string("FSUBRP"), 0xde, 230, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de e6 - FSUBRP ST(i), ST(0)
    { const_string("FSUBRP"), 0xde, 231, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de e7 - FSUBRP ST(i), ST(0)
    { const_string("FSUBP"), 0xde, 232, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de e8 - FSUBP ST(i), ST(0)
    { const_string("FSUBP"), 0xde, 233, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // de e9 - FSUBP 
    { const_string("FSUBP"), 0xde, 234, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de ea - FSUBP ST(i), ST(0)
    { const_string("FSUBP"), 0xde, 235, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de eb - FSUBP ST(i), ST(0)
    { const_string("FSUBP"), 0xde, 236, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de ec - FSUBP ST(i), ST(0)
    { const_string("FSUBP"), 0xde, 237, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de ed - FSUBP ST(i), ST(0)
    { const_string("FSUBP"), 0xde, 238, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de ee - FSUBP ST(i), ST(0)
    { const_string("FSUBP"), 0xde, 239, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de ef - FSUBP ST(i), ST(0)
    { const_string("FDIVRP"), 0xde, 240, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de f0 - FDIVRP ST(i), ST(0)
    { const_string("FDIVRP"), 0xde, 241, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // de f1 - FDIVRP 
    { const_string("FDIVRP"), 0xde, 242, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de f2 - FDIVRP ST(i), ST(0)
    { const_string("FDIVRP"), 0xde, 243, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de f3 - FDIVRP ST(i), ST(0)
    { const_string("FDIVRP"), 0xde, 244, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de f4 - FDIVRP ST(i), ST(0)
    { const_string("FDIVRP"), 0xde, 245, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de f5 - FDIVRP ST(i), ST(0)
    { const_string("FDIVRP"), 0xde, 246, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de f6 - FDIVRP ST(i), ST(0)
    { const_string("FDIVRP"), 0xde, 247, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de f7 - FDIVRP ST(i), ST(0)
    { const_string("FDIVP"), 0xde, 248, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de f8 - FDIVP ST(i), ST(0)
    { const_string("FDIVP"), 0xde, 249, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // de f9 - FDIVP 
    { const_string("FDIVP"), 0xde, 250, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de fa - FDIVP ST(i), ST(0)
    { const_string("FDIVP"), 0xde, 251, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de fb - FDIVP ST(i), ST(0)
    { const_string("FDIVP"), 0xde, 252, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de fc - FDIVP ST(i), ST(0)
    { const_string("FDIVP"), 0xde, 253, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de fd - FDIVP ST(i), ST(0)
    { const_string("FDIVP"), 0xde, 254, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de fe - FDIVP ST(i), ST(0)
    { const_string("FDIVP"), 0xde, 255, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_STi, 0}, {OPERAND_ST0, 0}} }, // de ff - FDIVP ST(i), ST(0)
    { const_string("FILD"), 0xdf, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_mem, 0}} }, // df /0 - FILD mem
    { const_string("FISTTP"), 0xdf, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_mem, 0}} }, // df /1 - FISTTP mem
    { const_string("FIST"), 0xdf, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_mem, 0}} }, // df /2 - FIST mem
    { const_string("FISTP"), 0xdf, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_mem, 0}} }, // df /3 - FISTP mem
    { const_string("FBLD"), 0xdf, -1, 0, 0, 0, 0, 1, 4, 0, 0, 1, {{OPERAND_mem, 0}} }, // df /4 - FBLD mem
    { const_string("FILD"), 0xdf, -1, 0, 0, 0, 0, 1, 5, 0, 0, 1, {{OPERAND_mem, 0}} }, // df /5 - FILD mem
    { const_string("FBSTP"), 0xdf, -1, 0, 0, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_mem, 0}} }, // df /6 - FBSTP mem
    { const_string("FISTP"), 0xdf, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_mem, 0}} }, // df /7 - FISTP mem
    { const_string("FNSTSW"), 0xdf, 224, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_ax, 0}} }, // df e0 - FNSTSW ax
    { const_string("FUCOMIP"), 0xdf, 232, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df e8 - FUCOMIP ST(0), ST(i)
    { const_string("FUCOMIP"), 0xdf, 233, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df e9 - FUCOMIP ST(0), ST(i)
    { const_string("FUCOMIP"), 0xdf, 234, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df ea - FUCOMIP ST(0), ST(i)
    { const_string("FUCOMIP"), 0xdf, 235, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df eb - FUCOMIP ST(0), ST(i)
    { const_string("FUCOMIP"), 0xdf, 236, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df ec - FUCOMIP ST(0), ST(i)
    { const_string("FUCOMIP"), 0xdf, 237, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df ed - FUCOMIP ST(0), ST(i)
    { const_string("FUCOMIP"), 0xdf, 238, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df ee - FUCOMIP ST(0), ST(i)
    { const_string("FUCOMIP"), 0xdf, 239, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df ef - FUCOMIP ST(0), ST(i)
    { const_string("FCOMIP"), 0xdf, 240, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df f0 - FCOMIP ST(0), ST(i)
    { const_string("FCOMIP"), 0xdf, 241, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df f1 - FCOMIP ST(0), ST(i)
    { const_string("FCOMIP"), 0xdf, 242, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df f2 - FCOMIP ST(0), ST(i)
    { const_string("FCOMIP"), 0xdf, 243, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df f3 - FCOMIP ST(0), ST(i)
    { const_string("FCOMIP"), 0xdf, 244, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df f4 - FCOMIP ST(0), ST(i)
    { const_string("FCOMIP"), 0xdf, 245, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df f5 - FCOMIP ST(0), ST(i)
    { const_string("FCOMIP"), 0xdf, 246, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df f6 - FCOMIP ST(0), ST(i)
    { const_string("FCOMIP"), 0xdf, 247, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_ST0, 0}, {OPERAND_STi, 0}} }, // df f7 - FCOMIP ST(0), ST(i)
    { const_string("LOOPNE"), 0xe0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // e0 ib - LOOPNE rel8
    { const_string("LOOPE"), 0xe1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // e1 ib - LOOPE rel8
    { const_string("LOOP"), 0xe2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // e2 ib - LOOP rel8
    { const_string("JRCXZ"), 0xe3, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // e3 ib - JRCXZ rel8
    { const_string("IN"), 0xe4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, 0}, {OPERAND_imm8, 0}} }, // e4 ib - IN al, imm8
    { const_string("IN"), 0xe5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, 0}, {OPERAND_imm8, 0}} }, // 66 e5 ib - IN ax, imm8
    { const_string("IN"), 0xe5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, 0}, {OPERAND_imm8, 0}} }, // e5 ib - IN eax, imm8
    { const_string("OUT"), 0xe6, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_imm8, 0}, {OPERAND_al, 0}} }, // e6 ib - OUT imm8, al
    { const_string("OUT"), 0xe7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_imm8, 0}, {OPERAND_ax, 0}} }, // 66 e7 ib - OUT imm8, ax
    { const_string("OUT"), 0xe7, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_imm8, 0}, {OPERAND_eax, 0}} }, // e7 ib - OUT imm8, eax
    { const_string("CALL"), 0xe8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // e8 id - CALL rel32
    { const_string("JMP"), 0xe9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // e9 id - JMP rel32
    { const_string("JMP"), 0xeb, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel8, 0}} }, // eb ib - JMP rel8
    { const_string("IN"), 0xec, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_al, 0}, {OPERAND_dx, 0}} }, // ec - IN al, dx
    { const_string("IN"), 0xed, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_ax, 0}, {OPERAND_dx, 0}} }, // 66 ed - IN ax, dx
    { const_string("IN"), 0xed, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_eax, 0}, {OPERAND_dx, 0}} }, // ed - IN eax, dx
    { const_string("OUT"), 0xee, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_dx, 0}, {OPERAND_al, 0}} }, // ee - OUT dx, al
    { const_string("OUT"), 0xef, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_dx, 0}, {OPERAND_ax, 0}} }, // 66 ef - OUT dx, ax
    { const_string("OUT"), 0xef, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_dx, 0}, {OPERAND_eax, 0}} }, // ef - OUT dx, eax
    { const_string("LOCK"), 0xf0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // f0 - LOCK 
    { const_string("INT1"), 0xf1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // f1 - INT1 
    { const_string("HLT"), 0xf4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // f4 - HLT 
    { const_string("CMC"), 0xf5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // f5 - CMC 
    { const_string("TEST"), 0xf6, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // f6 /0 ib - TEST r/m8, imm8
    { const_string("NOT"), 0xf6, -1, 0, 0, 0, 0, 0, 2, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // f6 /2 - NOT r/m8
    { const_string("NEG"), 0xf6, -1, 0, 0, 0, 0, 0, 3, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // f6 /3 - NEG r/m8
    { const_string("MUL"), 0xf6, -1, 0, 0, 0, 0, 0, 4, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // f6 /4 - MUL r/m8
    { const_string("IMUL"), 0xf6, -1, 0, 0, 0, 0, 0, 5, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // f6 /5 - IMUL r/m8
    { const_string("DIV"), 0xf6, -1, 0, 0, 0, 0, 0, 6, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_write}} }, // f6 /6 - DIV r/m8
    { const_string("IDIV"), 0xf6, -1, 0, 0, 0, 0, 0, 7, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // f6 /7 - IDIV r/m8
    { const_string("TEST"), 0xf7, -1, 0, 0, 1, 0, 0, 0, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read}, {OPERAND_imm16, 0}} }, // 66 f7 /0 iw - TEST r/m16, imm16
    { const_string("TEST"), 0xf7, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // f7 /0 id - TEST r/m32, imm32
    { const_string("TEST"), 0xf7, -1, 0, 0, 0, 1, 0, 0, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_imm32, 0}} }, // REX.W f7 /0 id - TEST r/m64, imm32
    { const_string("NOT"), 0xf7, -1, 0, 0, 1, 0, 0, 2, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 f7 /2 - NOT r/m16
    { const_string("NOT"), 0xf7, -1, 0, 0, 0, 0, 0, 2, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // f7 /2 - NOT r/m32
    { const_string("NOT"), 0xf7, -1, 0, 0, 0, 1, 0, 2, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W f7 /2 - NOT r/m64
    { const_string("NEG"), 0xf7, -1, 0, 0, 1, 0, 0, 3, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 f7 /3 - NEG r/m16
    { const_string("NEG"), 0xf7, -1, 0, 0, 0, 0, 0, 3, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // f7 /3 - NEG r/m32
    { const_string("NEG"), 0xf7, -1, 0, 0, 0, 1, 0, 3, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W f7 /3 - NEG r/m64
    { const_string("MUL"), 0xf7, -1, 0, 0, 1, 0, 0, 4, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 f7 /4 - MUL r/m16
    { const_string("MUL"), 0xf7, -1, 0, 0, 0, 0, 0, 4, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read}} }, // f7 /4 - MUL r/m32
    { const_string("MUL"), 0xf7, -1, 0, 0, 0, 1, 0, 4, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W f7 /4 - MUL r/m64
    { const_string("IMUL"), 0xf7, -1, 0, 0, 1, 0, 0, 5, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 f7 /5 - IMUL r/m16
    { const_string("IMUL"), 0xf7, -1, 0, 0, 0, 0, 0, 5, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // f7 /5 - IMUL r/m32
    { const_string("IMUL"), 0xf7, -1, 0, 0, 0, 1, 0, 5, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W f7 /5 - IMUL r/m64
    { const_string("DIV"), 0xf7, -1, 0, 0, 1, 0, 0, 6, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_write}} }, // 66 f7 /6 - DIV r/m16
    { const_string("DIV"), 0xf7, -1, 0, 0, 0, 0, 0, 6, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_write}} }, // f7 /6 - DIV r/m32
    { const_string("DIV"), 0xf7, -1, 0, 0, 0, 1, 0, 6, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_write}} }, // REX.W f7 /6 - DIV r/m64
    { const_string("IDIV"), 0xf7, -1, 0, 0, 1, 0, 0, 7, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 f7 /7 - IDIV r/m16
    { const_string("IDIV"), 0xf7, -1, 0, 0, 0, 0, 0, 7, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read}} }, // f7 /7 - IDIV r/m32
    { const_string("IDIV"), 0xf7, -1, 0, 0, 0, 1, 0, 7, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W f7 /7 - IDIV r/m64
    { const_string("CLC"), 0xf8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // f8 - CLC 
    { const_string("STC"), 0xf9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // f9 - STC 
    { const_string("CLI"), 0xfa, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // fa - CLI 
    { const_string("STI"), 0xfb, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // fb - STI 
    { const_string("CLD"), 0xfc, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // fc - CLD 
    { const_string("STD"), 0xfd, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // fd - STD 
    { const_string("INC"), 0xfe, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // fe /0 - INC r/m8
    { const_string("DEC"), 0xfe, -1, 0, 0, 0, 0, 0, 1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // fe /1 - DEC r/m8
    { const_string("INC"), 0xff, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 ff /0 - INC r/m16
    { const_string("INC"), 0xff, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // ff /0 - INC r/m32
    { const_string("INC"), 0xff, -1, 0, 0, 0, 1, 0, 0, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W ff /0 - INC r/m64
    { const_string("DEC"), 0xff, -1, 0, 0, 1, 0, 0, 1, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 ff /1 - DEC r/m16
    { const_string("DEC"), 0xff, -1, 0, 0, 0, 0, 0, 1, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // ff /1 - DEC r/m32
    { const_string("DEC"), 0xff, -1, 0, 0, 0, 1, 0, 1, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W ff /1 - DEC r/m64
    { const_string("CALL"), 0xff, -1, 0, 0, 0, 0, 0, 2, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read}} }, // ff /2 - CALL r/m64
    { const_string("CALL"), 0xff, -1, 0, 0, 1, 0, 0, 3, 0, 0, 1, {{OPERAND_far_m16, OPERAND_FLAG_read}} }, // 66 ff /3 - CALL m16:16
    { const_string("CALL"), 0xff, -1, 0, 0, 0, 0, 0, 3, 0, 0, 1, {{OPERAND_far_m32, OPERAND_FLAG_read}} }, // ff /3 - CALL m16:32
    { const_string("CALL"), 0xff, -1, 0, 0, 0, 1, 0, 3, 0, 0, 1, {{OPERAND_far_m64, OPERAND_FLAG_read}} }, // REX.W ff /3 - CALL m16:64
    { const_string("JMP"), 0xff, -1, 0, 0, 0, 0, 0, 4, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read}} }, // ff /4 - JMP r/m64
    { const_string("JMP"), 0xff, -1, 0, 0, 1, 0, 0, 5, 0, 0, 1, {{OPERAND_far_m16, 0}} }, // 66 ff /5 - JMP m16:16
    { const_string("JMP"), 0xff, -1, 0, 0, 0, 0, 0, 5, 0, 0, 1, {{OPERAND_far_m32, 0}} }, // ff /5 - JMP m16:32
    { const_string("JMP"), 0xff, -1, 0, 0, 0, 1, 0, 5, 0, 0, 1, {{OPERAND_far_m64, 0}} }, // REX.W ff /5 - JMP m16:64
    { const_string("PUSH"), 0xff, -1, 0, 0, 1, 0, 0, 6, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 ff /6 - PUSH r/m16
    { const_string("PUSH"), 0xff, -1, 0, 0, 0, 0, 0, 6, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read}} }, // ff /6 - PUSH r/m64
    { const_string("SLDT"), 0x100, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_write}} }, // 0F 00 /0 - SLDT r/m16
    { const_string("SLDT"), 0x100, -1, 0, 0, 0, 1, 0, 0, 0, 0, 1, {{OPERAND_regm16_zero_extended, OPERAND_FLAG_write}} }, // REX.W 0F 00 /0 - SLDT reg/m16
    { const_string("STR"), 0x100, -1, 0, 0, 0, 0, 0, 1, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_write}} }, // 0F 00 /1 - STR r/m16
    { const_string("LLDT"), 0x100, -1, 0, 0, 0, 0, 0, 2, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read}} }, // 0F 00 /2 - LLDT r/m16
    { const_string("LTR"), 0x100, -1, 0, 0, 0, 0, 0, 3, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read}} }, // 0F 00 /3 - LTR r/m16
    { const_string("VERR"), 0x100, -1, 0, 0, 0, 0, 0, 4, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read}} }, // 0F 00 /4 - VERR r/m16
    { const_string("VERW"), 0x100, -1, 0, 0, 0, 0, 0, 5, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read}} }, // 0F 00 /5 - VERW r/m16
    { const_string("SGDT"), 0x101, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // 0F 01 /0 - SGDT mem
    { const_string("SIDT"), 0x101, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // 0F 01 /1 - SIDT mem
    { const_string("LGDT"), 0x101, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_read}} }, // 0F 01 /2 - LGDT mem
    { const_string("LIDT"), 0x101, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_read}} }, // 0F 01 /3 - LIDT mem
    { const_string("SMSW"), 0x101, -1, 0, 0, 1, 0, 0, 4, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_write}} }, // 66 0F 01 /4 - SMSW r/m16
    { const_string("SMSW"), 0x101, -1, 0, 0, 0, 0, 0, 4, 0, 0, 1, {{OPERAND_regm16_zero_extended, OPERAND_FLAG_write}} }, // 0F 01 /4 - SMSW reg/m16
    { const_string("SMSW"), 0x101, -1, 0, 0, 0, 1, 0, 4, 0, 0, 1, {{OPERAND_regm16_zero_extended, OPERAND_FLAG_write}} }, // REX.W 0F 01 /4 - SMSW reg/m16
    { const_string("RSTORSSP"), 0x101, -1, 0, 1, 0, 0, 1, 5, 0, 0, 1, {{OPERAND_m64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // F3 0F 01 /5 - RSTORSSP m64
    { const_string("LMSW"), 0x101, -1, 0, 0, 0, 0, 0, 6, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read}} }, // 0F 01 /6 - LMSW r/m16
    { const_string("INVLPG"), 0x101, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_read}} }, // 0F 01 /7 - INVLPG mem
    { const_string("ENCLV"), 0x101, 192, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 c0 - ENCLV 
    { const_string("VMCALL"), 0x101, 193, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 c1 - VMCALL 
    { const_string("VMLAUNCH"), 0x101, 194, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 c2 - VMLAUNCH 
    { const_string("VMRESUME"), 0x101, 195, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 c3 - VMRESUME 
    { const_string("VMXOFF"), 0x101, 196, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 c4 - VMXOFF 
    { const_string("MONITOR"), 0x101, 200, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 c8 - MONITOR 
    { const_string("MWAIT"), 0x101, 201, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 c9 - MWAIT 
    { const_string("CLAC"), 0x101, 202, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 ca - CLAC 
    { const_string("STAC"), 0x101, 203, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 cb - STAC 
    { const_string("ENCLS"), 0x101, 207, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 cf - ENCLS 
    { const_string("XGETBV"), 0x101, 208, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 d0 - XGETBV 
    { const_string("XSETBV"), 0x101, 209, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 d1 - XSETBV 
    { const_string("VMFUNC"), 0x101, 212, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 d4 - VMFUNC 
    { const_string("XEND"), 0x101, 213, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 d5 - XEND 
    { const_string("XTEST"), 0x101, 214, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 d6 - XTEST 
    { const_string("ENCLU"), 0x101, 215, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 d7 - ENCLU 
    { const_string("SETSSBSY"), 0x101, 232, 0, 1, 0, 0, 0, -1, 0, 0, 0,  }, // F3 0F 01 e8 - SETSSBSY 
    { const_string("SAVEPREVSSP"), 0x101, 234, 0, 1, 0, 0, 0, -1, 0, 0, 0,  }, // F3 0F 01 ea - SAVEPREVSSP 
    { const_string("RDPKRU"), 0x101, 238, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 ee - RDPKRU 
    { const_string("WRPKRU"), 0x101, 239, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 ef - WRPKRU 
    { const_string("SWAPGS"), 0x101, 248, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 f8 - SWAPGS 
    { const_string("RDTSCP"), 0x101, 249, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 01 f9 - RDTSCP 
    { const_string("LAR"), 0x102, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 02 /r - LAR r16, r/m16
    { const_string("LAR"), 0x102, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm16_zero_extended, OPERAND_FLAG_read}} }, // 0F 02 /r - LAR r64, reg/m16
    { const_string("LSL"), 0x103, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 03 /r - LSL r16, r/m16
    { const_string("LSL"), 0x103, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm16_zero_extended, OPERAND_FLAG_read}} }, // 0F 03 /r - LSL r32, reg/m16
    { const_string("LSL"), 0x103, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm16_zero_extended, OPERAND_FLAG_read}} }, // REX.W 0F 03 /r - LSL r64, reg/m16
    { const_string("SYSCALL"), 0x105, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 05 - SYSCALL 
    { const_string("CLTS"), 0x106, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 06 - CLTS 
    { const_string("SYSRET"), 0x107, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 07 - SYSRET 
    { const_string("SYSRET"), 0x107, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W 0F 07 - SYSRET 
    { const_string("INVD"), 0x108, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 08 - INVD 
    { const_string("WBINVD"), 0x109, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 09 - WBINVD 
    { const_string("UD2"), 0x10b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 0b - UD2 
    { const_string("PREFETCHW"), 0x10d, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_m8, OPERAND_FLAG_read}} }, // 0F 0d /1 - PREFETCHW m8
    { const_string("MOVSS"), 0x110, -1, 0, 1, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_m32, OPERAND_FLAG_read}} }, // F3 0F 10 /r - MOVSS xmm, m32
    { const_string("MOVSS"), 0x110, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F3 0F 10 /r - MOVSS xmm, xmm/m128
    { const_string("MOVSD"), 0x110, -1, 1, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // F2 0F 10 /r - MOVSD xmm, m64
    { const_string("MOVSD"), 0x110, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F2 0F 10 /r - MOVSD xmm, xmm/m128
    { const_string("MOVUPD"), 0x110, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 10 /r - MOVUPD xmm, xmm/m128
    { const_string("MOVUPS"), 0x110, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 10 /r - MOVUPS xmm, xmm/m128
    { const_string("MOVSS"), 0x111, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // F3 0F 11 /r - MOVSS xmm/m32, xmm
    { const_string("MOVSD"), 0x111, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // F2 0F 11 /r - MOVSD xmm/m64, xmm
    { const_string("MOVUPD"), 0x111, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 66 0F 11 /r - MOVUPD xmm/m128, xmm
    { const_string("MOVUPS"), 0x111, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 0F 11 /r - MOVUPS xmm/m128, xmm
    { const_string("MOVSLDUP"), 0x112, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F3 0F 12 /r - MOVSLDUP xmm, xmm/m128
    { const_string("MOVDDUP"), 0x112, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 12 /r - MOVDDUP xmm, xmm/m64
    { const_string("MOVLPD"), 0x112, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // 66 0F 12 /r - MOVLPD xmm, m64
    { const_string("MOVLPS"), 0x112, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // 0F 12 /r - MOVLPS xmm, m64
    { const_string("MOVHLPS"), 0x112, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 12 /r - MOVHLPS xmm, xmm/m128
    { const_string("MOVLPD"), 0x113, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 66 0F 13 /r - MOVLPD m64, xmm
    { const_string("MOVLPS"), 0x113, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 0F 13 /r - MOVLPS m64, xmm
    { const_string("UNPCKLPD"), 0x114, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 14 /r - UNPCKLPD xmm, xmm/m128
    { const_string("UNPCKLPS"), 0x114, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 14 /r - UNPCKLPS xmm, xmm/m128
    { const_string("UNPCKHPD"), 0x115, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 15 /r - UNPCKHPD xmm, xmm/m128
    { const_string("UNPCKHPS"), 0x115, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 15 /r - UNPCKHPS xmm, xmm/m128
    { const_string("MOVSHDUP"), 0x116, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F3 0F 16 /r - MOVSHDUP xmm, xmm/m128
    { const_string("MOVHPD"), 0x116, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // 66 0F 16 /r - MOVHPD xmm, m64
    { const_string("MOVHPS"), 0x116, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // 0F 16 /r - MOVHPS xmm, m64
    { const_string("MOVLHPS"), 0x116, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 16 /r - MOVLHPS xmm, xmm/m128
    { const_string("MOVHPD"), 0x117, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 66 0F 17 /r - MOVHPD m64, xmm
    { const_string("MOVHPS"), 0x117, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 0F 17 /r - MOVHPS m64, xmm
    { const_string("PREFETCHNTA"), 0x118, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_m8, OPERAND_FLAG_read}} }, // 0F 18 /0 - PREFETCHNTA m8
    { const_string("PREFETCHT0"), 0x118, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_m8, OPERAND_FLAG_read}} }, // 0F 18 /1 - PREFETCHT0 m8
    { const_string("PREFETCHT1"), 0x118, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_m8, OPERAND_FLAG_read}} }, // 0F 18 /2 - PREFETCHT1 m8
    { const_string("PREFETCHT2"), 0x118, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_m8, OPERAND_FLAG_read}} }, // 0F 18 /3 - PREFETCHT2 m8
    { const_string("BNDCL"), 0x11a, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_bnd, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // F3 0F 1a /r - BNDCL bnd, r/m64
    { const_string("BNDCU"), 0x11a, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_bnd, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // F2 0F 1a /r - BNDCU bnd, r/m64
    { const_string("BNDMOV"), 0x11a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_bnd, OPERAND_FLAG_write}, {OPERAND_bndm128, OPERAND_FLAG_read}} }, // 66 0F 1a /r - BNDMOV bnd, bnd/m128
    { const_string("BNDLDX"), 0x11a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_bnd, OPERAND_FLAG_write}, {OPERAND_mib, OPERAND_FLAG_read}} }, // 0F 1a /r - BNDLDX bnd, mib
    { const_string("BNDMK"), 0x11b, -1, 0, 1, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_bnd, OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // F3 0F 1b /r - BNDMK bnd, m64
    { const_string("BNDCN"), 0x11b, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_bnd, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // F2 0F 1b /r - BNDCN bnd, r/m64
    { const_string("BNDMOV"), 0x11b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_bndm128, OPERAND_FLAG_write}, {OPERAND_bnd, OPERAND_FLAG_read}} }, // 66 0F 1b /r - BNDMOV bnd/m128, bnd
    { const_string("BNDSTX"), 0x11b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mib, OPERAND_FLAG_write}, {OPERAND_bnd, OPERAND_FLAG_read}} }, // 0F 1b /r - BNDSTX mib, bnd
    { const_string("CLDEMOTE"), 0x11c, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_m8, OPERAND_FLAG_write}} }, // 0F 1c /0 - CLDEMOTE m8
    { const_string("RDSSPD"), 0x11e, -1, 0, 1, 0, 0, 0, 1, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_write}} }, // F3 0F 1e /1 - RDSSPD r/m32
    { const_string("RDSSPQ"), 0x11e, -1, 0, 1, 0, 1, 0, 1, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_write}} }, // F3 REX.W 0F 1e /1 - RDSSPQ r/m64
    { const_string("ENDBR64"), 0x11e, 250, 0, 1, 0, 0, 0, -1, 0, 0, 0,  }, // F3 0F 1e fa - ENDBR64 
    { const_string("ENDBR32"), 0x11e, 251, 0, 1, 0, 0, 0, -1, 0, 0, 0,  }, // F3 0F 1e fb - ENDBR32 
    { const_string("NOP"), 0x11f, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 1f /0 - NOP r/m16
    { const_string("NOP"), 0x11f, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 1f /0 - NOP r/m32
    { const_string("MOV"), 0x120, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_cr, OPERAND_FLAG_read}} }, // 0F 20 /r - MOV r/m64, CR
    { const_string("MOV"), 0x120, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_cr, OPERAND_FLAG_read}} }, // 0F 20 /0 - MOV r/m64, CR
    { const_string("MOV"), 0x121, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_dr, OPERAND_FLAG_read}} }, // 0F 21 /r - MOV r/m64, DR
    { const_string("MOV"), 0x122, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_cr, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // 0F 22 /r - MOV CR, r/m64
    { const_string("MOV"), 0x122, -1, 0, 0, 0, 0, 0, 0, 0, 0, 2, {{OPERAND_cr, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // 0F 22 /0 - MOV CR, r/m64
    { const_string("MOV"), 0x123, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_dr, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // 0F 23 /r - MOV DR, r/m64
    { const_string("MOVAPD"), 0x128, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 28 /r - MOVAPD xmm, xmm/m128
    { const_string("MOVAPS"), 0x128, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 28 /r - MOVAPS xmm, xmm/m128
    { const_string("MOVAPD"), 0x129, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 66 0F 29 /r - MOVAPD xmm/m128, xmm
    { const_string("MOVAPS"), 0x129, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 0F 29 /r - MOVAPS xmm/m128, xmm
    { const_string("CVTSI2SS"), 0x12a, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // F3 0F 2a /r - CVTSI2SS xmm, r/m32
    { const_string("CVTSI2SS"), 0x12a, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // F3 REX.W 0F 2a /r - CVTSI2SS xmm, r/m64
    { const_string("CVTSI2SD"), 0x12a, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // F2 0F 2a /r - CVTSI2SD xmm, r/m32
    { const_string("CVTSI2SD"), 0x12a, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // F2 REX.W 0F 2a /r - CVTSI2SD xmm, r/m64
    { const_string("CVTPI2PD"), 0x12a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 66 0F 2a /r - CVTPI2PD xmm, mm/m64
    { const_string("CVTPI2PS"), 0x12a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 2a /r - CVTPI2PS xmm, mm/m64
    { const_string("MOVNTPD"), 0x12b, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 66 0F 2b /r - MOVNTPD m128, xmm
    { const_string("MOVNTPS"), 0x12b, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 0F 2b /r - MOVNTPS m128, xmm
    { const_string("CVTTSS2SI"), 0x12c, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 2c /r - CVTTSS2SI r32, xmm/m32
    { const_string("CVTTSS2SI"), 0x12c, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 REX.W 0F 2c /r - CVTTSS2SI r64, xmm/m32
    { const_string("CVTTSD2SI"), 0x12c, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 2c /r - CVTTSD2SI r32, xmm/m64
    { const_string("CVTTSD2SI"), 0x12c, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 REX.W 0F 2c /r - CVTTSD2SI r64, xmm/m64
    { const_string("CVTTPD2PI"), 0x12c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 2c /r - CVTTPD2PI mm, xmm/m128
    { const_string("CVTTPS2PI"), 0x12c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 0F 2c /r - CVTTPS2PI mm, xmm/m64
    { const_string("CVTSS2SI"), 0x12d, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 2d /r - CVTSS2SI r32, xmm/m32
    { const_string("CVTSS2SI"), 0x12d, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 REX.W 0F 2d /r - CVTSS2SI r64, xmm/m32
    { const_string("CVTSD2SI"), 0x12d, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 2d /r - CVTSD2SI r32, xmm/m64
    { const_string("CVTSD2SI"), 0x12d, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 REX.W 0F 2d /r - CVTSD2SI r64, xmm/m64
    { const_string("CVTPD2PI"), 0x12d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 2d /r - CVTPD2PI mm, xmm/m128
    { const_string("CVTPS2PI"), 0x12d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 0F 2d /r - CVTPS2PI mm, xmm/m64
    { const_string("UCOMISD"), 0x12e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 66 0F 2e /r - UCOMISD xmm, xmm/m64
    { const_string("UCOMISS"), 0x12e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // 0F 2e /r - UCOMISS xmm, xmm/m32
    { const_string("COMISD"), 0x12f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 66 0F 2f /r - COMISD xmm, xmm/m64
    { const_string("COMISS"), 0x12f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // 0F 2f /r - COMISS xmm, xmm/m32
    { const_string("WRMSR"), 0x130, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 30 - WRMSR 
    { const_string("RDTSC"), 0x131, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 31 - RDTSC 
    { const_string("RDMSR"), 0x132, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 32 - RDMSR 
    { const_string("RDPMC"), 0x133, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 33 - RDPMC 
    { const_string("SYSENTER"), 0x134, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 34 - SYSENTER 
    { const_string("SYSEXIT"), 0x135, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 35 - SYSEXIT 
    { const_string("SYSEXIT"), 0x135, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // REX.W 0F 35 - SYSEXIT 
    { const_string("CMOVO"), 0x140, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 40 /r - CMOVO r16, r/m16
    { const_string("CMOVO"), 0x140, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 40 /r - CMOVO r32, r/m32
    { const_string("CMOVO"), 0x140, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 40 /r - CMOVO r64, r/m64
    { const_string("CMOVNO"), 0x141, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 41 /r - CMOVNO r16, r/m16
    { const_string("CMOVNO"), 0x141, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 41 /r - CMOVNO r32, r/m32
    { const_string("CMOVNO"), 0x141, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 41 /r - CMOVNO r64, r/m64
    { const_string("CMOVC"), 0x142, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 42 /r - CMOVC r16, r/m16
    { const_string("CMOVC"), 0x142, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 42 /r - CMOVC r32, r/m32
    { const_string("CMOVC"), 0x142, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 42 /r - CMOVC r64, r/m64
    { const_string("CMOVNC"), 0x143, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 43 /r - CMOVNC r16, r/m16
    { const_string("CMOVNC"), 0x143, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 43 /r - CMOVNC r32, r/m32
    { const_string("CMOVNC"), 0x143, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 43 /r - CMOVNC r64, r/m64
    { const_string("CMOVZ"), 0x144, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 44 /r - CMOVZ r16, r/m16
    { const_string("CMOVZ"), 0x144, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 44 /r - CMOVZ r32, r/m32
    { const_string("CMOVZ"), 0x144, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 44 /r - CMOVZ r64, r/m64
    { const_string("CMOVNZ"), 0x145, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 45 /r - CMOVNZ r16, r/m16
    { const_string("CMOVNZ"), 0x145, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 45 /r - CMOVNZ r32, r/m32
    { const_string("CMOVNZ"), 0x145, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 45 /r - CMOVNZ r64, r/m64
    { const_string("CMOVBE"), 0x146, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 46 /r - CMOVBE r16, r/m16
    { const_string("CMOVBE"), 0x146, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 46 /r - CMOVBE r32, r/m32
    { const_string("CMOVBE"), 0x146, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 46 /r - CMOVBE r64, r/m64
    { const_string("CMOVNBE"), 0x147, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 47 /r - CMOVNBE r16, r/m16
    { const_string("CMOVNBE"), 0x147, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 47 /r - CMOVNBE r32, r/m32
    { const_string("CMOVNBE"), 0x147, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 47 /r - CMOVNBE r64, r/m64
    { const_string("CMOVS"), 0x148, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 48 /r - CMOVS r16, r/m16
    { const_string("CMOVS"), 0x148, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 48 /r - CMOVS r32, r/m32
    { const_string("CMOVS"), 0x148, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 48 /r - CMOVS r64, r/m64
    { const_string("CMOVNS"), 0x149, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 49 /r - CMOVNS r16, r/m16
    { const_string("CMOVNS"), 0x149, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 49 /r - CMOVNS r32, r/m32
    { const_string("CMOVNS"), 0x149, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 49 /r - CMOVNS r64, r/m64
    { const_string("CMOVP"), 0x14a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 4a /r - CMOVP r16, r/m16
    { const_string("CMOVP"), 0x14a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 4a /r - CMOVP r32, r/m32
    { const_string("CMOVP"), 0x14a, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 4a /r - CMOVP r64, r/m64
    { const_string("CMOVNP"), 0x14b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 4b /r - CMOVNP r16, r/m16
    { const_string("CMOVNP"), 0x14b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 4b /r - CMOVNP r32, r/m32
    { const_string("CMOVNP"), 0x14b, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 4b /r - CMOVNP r64, r/m64
    { const_string("CMOVL"), 0x14c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 4c /r - CMOVL r16, r/m16
    { const_string("CMOVL"), 0x14c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 4c /r - CMOVL r32, r/m32
    { const_string("CMOVL"), 0x14c, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 4c /r - CMOVL r64, r/m64
    { const_string("CMOVNL"), 0x14d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 4d /r - CMOVNL r16, r/m16
    { const_string("CMOVNL"), 0x14d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 4d /r - CMOVNL r32, r/m32
    { const_string("CMOVNL"), 0x14d, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 4d /r - CMOVNL r64, r/m64
    { const_string("CMOVLE"), 0x14e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 4e /r - CMOVLE r16, r/m16
    { const_string("CMOVLE"), 0x14e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 4e /r - CMOVLE r32, r/m32
    { const_string("CMOVLE"), 0x14e, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 4e /r - CMOVLE r64, r/m64
    { const_string("CMOVNLE"), 0x14f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F 4f /r - CMOVNLE r16, r/m16
    { const_string("CMOVNLE"), 0x14f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 4f /r - CMOVNLE r32, r/m32
    { const_string("CMOVNLE"), 0x14f, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 4f /r - CMOVNLE r64, r/m64
    { const_string("MOVMSKPD"), 0x150, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 50 /r - MOVMSKPD r64, xmm/m128
    { const_string("MOVMSKPS"), 0x150, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 50 /r - MOVMSKPS r64, xmm/m128
    { const_string("SQRTSS"), 0x151, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 51 /r - SQRTSS xmm, xmm/m32
    { const_string("SQRTSD"), 0x151, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 51 /r - SQRTSD xmm, xmm/m64
    { const_string("SQRTPD"), 0x151, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 51 /r - SQRTPD xmm, xmm/m128
    { const_string("SQRTPS"), 0x151, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 51 /r - SQRTPS xmm, xmm/m128
    { const_string("RSQRTSS"), 0x152, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 52 /r - RSQRTSS xmm, xmm/m32
    { const_string("RSQRTPS"), 0x152, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 52 /r - RSQRTPS xmm, xmm/m128
    { const_string("RCPSS"), 0x153, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 53 /r - RCPSS xmm, xmm/m32
    { const_string("RCPPS"), 0x153, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 53 /r - RCPPS xmm, xmm/m128
    { const_string("ANDPD"), 0x154, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 54 /r - ANDPD xmm, xmm/m128
    { const_string("ANDPS"), 0x154, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 54 /r - ANDPS xmm, xmm/m128
    { const_string("ANDNPD"), 0x155, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 55 /r - ANDNPD xmm, xmm/m128
    { const_string("ANDNPS"), 0x155, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 55 /r - ANDNPS xmm, xmm/m128
    { const_string("ORPD"), 0x156, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 56 /r - ORPD xmm, xmm/m128
    { const_string("ORPS"), 0x156, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 56 /r - ORPS xmm, xmm/m128
    { const_string("XORPD"), 0x157, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 57 /r - XORPD xmm, xmm/m128
    { const_string("XORPS"), 0x157, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 57 /r - XORPS xmm, xmm/m128
    { const_string("ADDSS"), 0x158, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 58 /r - ADDSS xmm, xmm/m32
    { const_string("ADDSD"), 0x158, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 58 /r - ADDSD xmm, xmm/m64
    { const_string("ADDPD"), 0x158, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 58 /r - ADDPD xmm, xmm/m128
    { const_string("ADDPS"), 0x158, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 58 /r - ADDPS xmm, xmm/m128
    { const_string("MULSS"), 0x159, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 59 /r - MULSS xmm, xmm/m32
    { const_string("MULSD"), 0x159, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 59 /r - MULSD xmm, xmm/m64
    { const_string("MULPD"), 0x159, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 59 /r - MULPD xmm, xmm/m128
    { const_string("MULPS"), 0x159, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 59 /r - MULPS xmm, xmm/m128
    { const_string("CVTSS2SD"), 0x15a, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 5a /r - CVTSS2SD xmm, xmm/m32
    { const_string("CVTSD2SS"), 0x15a, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 5a /r - CVTSD2SS xmm, xmm/m64
    { const_string("CVTPD2PS"), 0x15a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 5a /r - CVTPD2PS xmm, xmm/m128
    { const_string("CVTPS2PD"), 0x15a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 0F 5a /r - CVTPS2PD xmm, xmm/m64
    { const_string("CVTTPS2DQ"), 0x15b, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F3 0F 5b /r - CVTTPS2DQ xmm, xmm/m128
    { const_string("CVTPS2DQ"), 0x15b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 5b /r - CVTPS2DQ xmm, xmm/m128
    { const_string("CVTDQ2PS"), 0x15b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 5b /r - CVTDQ2PS xmm, xmm/m128
    { const_string("SUBSS"), 0x15c, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 5c /r - SUBSS xmm, xmm/m32
    { const_string("SUBSD"), 0x15c, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 5c /r - SUBSD xmm, xmm/m64
    { const_string("SUBPD"), 0x15c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 5c /r - SUBPD xmm, xmm/m128
    { const_string("SUBPS"), 0x15c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 5c /r - SUBPS xmm, xmm/m128
    { const_string("MINSS"), 0x15d, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 5d /r - MINSS xmm, xmm/m32
    { const_string("MINSD"), 0x15d, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 5d /r - MINSD xmm, xmm/m64
    { const_string("MINPD"), 0x15d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 5d /r - MINPD xmm, xmm/m128
    { const_string("MINPS"), 0x15d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 5d /r - MINPS xmm, xmm/m128
    { const_string("DIVSS"), 0x15e, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 5e /r - DIVSS xmm, xmm/m32
    { const_string("DIVSD"), 0x15e, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 5e /r - DIVSD xmm, xmm/m64
    { const_string("DIVPD"), 0x15e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 5e /r - DIVPD xmm, xmm/m128
    { const_string("DIVPS"), 0x15e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 5e /r - DIVPS xmm, xmm/m128
    { const_string("MAXSS"), 0x15f, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // F3 0F 5f /r - MAXSS xmm, xmm/m32
    { const_string("MAXSD"), 0x15f, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F2 0F 5f /r - MAXSD xmm, xmm/m64
    { const_string("MAXPD"), 0x15f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 5f /r - MAXPD xmm, xmm/m128
    { const_string("MAXPS"), 0x15f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 5f /r - MAXPS xmm, xmm/m128
    { const_string("PUNPCKLBW"), 0x160, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 60 /r - PUNPCKLBW xmm, xmm/m128
    { const_string("PUNPCKLBW"), 0x160, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm32, OPERAND_FLAG_read}} }, // 0F 60 /r - PUNPCKLBW mm, mm/m32
    { const_string("PUNPCKLWD"), 0x161, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 61 /r - PUNPCKLWD xmm, xmm/m128
    { const_string("PUNPCKLWD"), 0x161, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm32, OPERAND_FLAG_read}} }, // 0F 61 /r - PUNPCKLWD mm, mm/m32
    { const_string("PUNPCKLDQ"), 0x162, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 62 /r - PUNPCKLDQ xmm, xmm/m128
    { const_string("PUNPCKLDQ"), 0x162, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm32, OPERAND_FLAG_read}} }, // 0F 62 /r - PUNPCKLDQ mm, mm/m32
    { const_string("PACKSSWB"), 0x163, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 63 /r - PACKSSWB xmm, xmm/m128
    { const_string("PACKSSWB"), 0x163, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 63 /r - PACKSSWB mm, mm/m64
    { const_string("PCMPGTB"), 0x164, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 64 /r - PCMPGTB xmm, xmm/m128
    { const_string("PCMPGTB"), 0x164, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 64 /r - PCMPGTB mm, mm/m64
    { const_string("PCMPGTW"), 0x165, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 65 /r - PCMPGTW xmm, xmm/m128
    { const_string("PCMPGTW"), 0x165, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 65 /r - PCMPGTW mm, mm/m64
    { const_string("PCMPGTD"), 0x166, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 66 /r - PCMPGTD xmm, xmm/m128
    { const_string("PCMPGTD"), 0x166, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 66 /r - PCMPGTD mm, mm/m64
    { const_string("PACKUSWB"), 0x167, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 67 /r - PACKUSWB xmm, xmm/m128
    { const_string("PACKUSWB"), 0x167, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 67 /r - PACKUSWB mm, mm/m64
    { const_string("PUNPCKHBW"), 0x168, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 68 /r - PUNPCKHBW xmm, xmm/m128
    { const_string("PUNPCKHBW"), 0x168, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 68 /r - PUNPCKHBW mm, mm/m64
    { const_string("PUNPCKHWD"), 0x169, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 69 /r - PUNPCKHWD xmm, xmm/m128
    { const_string("PUNPCKHWD"), 0x169, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 69 /r - PUNPCKHWD mm, mm/m64
    { const_string("PUNPCKHDQ"), 0x16a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 6a /r - PUNPCKHDQ xmm, xmm/m128
    { const_string("PUNPCKHDQ"), 0x16a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 6a /r - PUNPCKHDQ mm, mm/m64
    { const_string("PACKSSDW"), 0x16b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 6b /r - PACKSSDW xmm, xmm/m128
    { const_string("PACKSSDW"), 0x16b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 6b /r - PACKSSDW mm, mm/m64
    { const_string("PUNPCKLQDQ"), 0x16c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 6c /r - PUNPCKLQDQ xmm, xmm/m128
    { const_string("PUNPCKHQDQ"), 0x16d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 6d /r - PUNPCKHQDQ xmm, xmm/m128
    { const_string("MOVD"), 0x16e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 66 0F 6e /r - MOVD xmm, r/m32
    { const_string("MOVQ"), 0x16e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // 66 REX.W 0F 6e /r - MOVQ xmm, r/m64
    { const_string("MOVD"), 0x16e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F 6e /r - MOVD mm, r/m32
    { const_string("MOVQ"), 0x16e, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F 6e /r - MOVQ mm, r/m64
    { const_string("MOVDQU"), 0x16f, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F3 0F 6f /r - MOVDQU xmm, xmm/m128
    { const_string("MOVDQA"), 0x16f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 6f /r - MOVDQA xmm, xmm/m128
    { const_string("MOVQ"), 0x16f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 6f /r - MOVQ mm, mm/m64
    { const_string("PSHUFHW"), 0x170, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // F3 0F 70 ib /r - PSHUFHW xmm, xmm/m128, imm8
    { const_string("PSHUFLW"), 0x170, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // F2 0F 70 ib /r - PSHUFLW xmm, xmm/m128, imm8
    { const_string("PSHUFD"), 0x170, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 70 ib /r - PSHUFD xmm, xmm/m128, imm8
    { const_string("PSHUFW"), 0x170, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0F 70 ib /r - PSHUFW mm, mm/m64, imm8
    { const_string("PSRLW"), 0x171, -1, 0, 0, 1, 0, 0, 2, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F 71 /2 ib - PSRLW xmm/m128, imm8
    { const_string("PSRLW"), 0x171, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_mmm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F 71 /2 ib - PSRLW mm/m64, imm8
    { const_string("PSRAW"), 0x171, -1, 0, 0, 1, 0, 0, 4, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F 71 /4 ib - PSRAW xmm/m128, imm8
    { const_string("PSRAW"), 0x171, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_mmm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F 71 /4 ib - PSRAW mm/m64, imm8
    { const_string("PSLLW"), 0x171, -1, 0, 0, 1, 0, 0, 6, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F 71 /6 ib - PSLLW xmm/m128, imm8
    { const_string("PSLLW"), 0x171, -1, 0, 0, 0, 0, 0, 6, 0, 0, 2, {{OPERAND_mmm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F 71 /6 ib - PSLLW mm/m64, imm8
    { const_string("PSRLD"), 0x172, -1, 0, 0, 1, 0, 0, 2, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F 72 /2 ib - PSRLD xmm/m128, imm8
    { const_string("PSRLD"), 0x172, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_mmm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F 72 /2 ib - PSRLD mm/m64, imm8
    { const_string("PSRAD"), 0x172, -1, 0, 0, 1, 0, 0, 4, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F 72 /4 ib - PSRAD xmm/m128, imm8
    { const_string("PSRAD"), 0x172, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_mmm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F 72 /4 ib - PSRAD mm/m64, imm8
    { const_string("PSLLD"), 0x172, -1, 0, 0, 1, 0, 0, 6, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F 72 /6 ib - PSLLD xmm/m128, imm8
    { const_string("PSLLD"), 0x172, -1, 0, 0, 0, 0, 0, 6, 0, 0, 2, {{OPERAND_mmm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F 72 /6 ib - PSLLD mm/m64, imm8
    { const_string("PSRLQ"), 0x173, -1, 0, 0, 1, 0, 0, 2, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F 73 /2 ib - PSRLQ xmm/m128, imm8
    { const_string("PSRLQ"), 0x173, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_mmm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F 73 /2 ib - PSRLQ mm/m64, imm8
    { const_string("PSRLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 3, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F 73 /3 ib - PSRLDQ xmm/m128, imm8
    { const_string("PSLLQ"), 0x173, -1, 0, 0, 1, 0, 0, 6, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F 73 /6 ib - PSLLQ xmm/m128, imm8
    { const_string("PSLLQ"), 0x173, -1, 0, 0, 0, 0, 0, 6, 0, 0, 2, {{OPERAND_mmm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F 73 /6 ib - PSLLQ mm/m64, imm8
    { const_string("PSLLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 7, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F 73 /7 ib - PSLLDQ xmm/m128, imm8
    { const_string("PCMPEQB"), 0x174, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 74 /r - PCMPEQB xmm, xmm/m128
    { const_string("PCMPEQB"), 0x174, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 74 /r - PCMPEQB mm, mm/m64
    { const_string("PCMPEQW"), 0x175, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 75 /r - PCMPEQW xmm, xmm/m128
    { const_string("PCMPEQW"), 0x175, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 75 /r - PCMPEQW mm, mm/m64
    { const_string("PCMPEQD"), 0x176, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 76 /r - PCMPEQD xmm, xmm/m128
    { const_string("PCMPEQD"), 0x176, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 76 /r - PCMPEQD mm, mm/m64
    { const_string("EMMS"), 0x177, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F 77 - EMMS 
    { const_string("VMREAD"), 0x178, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // 0F 78 - VMREAD r/m64, r64
    { const_string("VMWRITE"), 0x179, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // 0F 79 - VMWRITE r64, r/m64
    { const_string("HADDPS"), 0x17c, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F2 0F 7c /r - HADDPS xmm, xmm/m128
    { const_string("HADDPD"), 0x17c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 7c /r - HADDPD xmm, xmm/m128
    { const_string("HSUBPS"), 0x17d, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F2 0F 7d /r - HSUBPS xmm, xmm/m128
    { const_string("HSUBPD"), 0x17d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 7d /r - HSUBPD xmm, xmm/m128
    { const_string("MOVQ"), 0x17e, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F3 0F 7e /r - MOVQ xmm, xmm/m64
    { const_string("MOVD"), 0x17e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 66 0F 7e /r - MOVD r/m32, xmm
    { const_string("MOVQ"), 0x17e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 66 REX.W 0F 7e /r - MOVQ r/m64, xmm
    { const_string("MOVD"), 0x17e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_mm, OPERAND_FLAG_read}} }, // 0F 7e /r - MOVD r/m32, mm
    { const_string("MOVQ"), 0x17e, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_mm, OPERAND_FLAG_read}} }, // REX.W 0F 7e /r - MOVQ r/m64, mm
    { const_string("MOVDQU"), 0x17f, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // F3 0F 7f /r - MOVDQU xmm/m128, xmm
    { const_string("MOVDQA"), 0x17f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 66 0F 7f /r - MOVDQA xmm/m128, xmm
    { const_string("MOVQ"), 0x17f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mmm64, OPERAND_FLAG_write}, {OPERAND_mm, OPERAND_FLAG_read}} }, // 0F 7f /r - MOVQ mm/m64, mm
    { const_string("JO"), 0x180, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 80 id - JO rel32
    { const_string("JNO"), 0x181, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 81 id - JNO rel32
    { const_string("JC"), 0x182, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 82 id - JC rel32
    { const_string("JNC"), 0x183, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 83 id - JNC rel32
    { const_string("JZ"), 0x184, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 84 id - JZ rel32
    { const_string("JNZ"), 0x185, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 85 id - JNZ rel32
    { const_string("JBE"), 0x186, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 86 id - JBE rel32
    { const_string("JNBE"), 0x187, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 87 id - JNBE rel32
    { const_string("JS"), 0x188, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 88 id - JS rel32
    { const_string("JNS"), 0x189, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 89 id - JNS rel32
    { const_string("JP"), 0x18a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 8a id - JP rel32
    { const_string("JNP"), 0x18b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 8b id - JNP rel32
    { const_string("JL"), 0x18c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 8c id - JL rel32
    { const_string("JNL"), 0x18d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 8d id - JNL rel32
    { const_string("JLE"), 0x18e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 8e id - JLE rel32
    { const_string("JNLE"), 0x18f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_rel32, 0}} }, // 0F 8f id - JNLE rel32
    { const_string("SETO"), 0x190, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 90 - SETO r/m8
    { const_string("SETNO"), 0x191, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 91 - SETNO r/m8
    { const_string("SETC"), 0x192, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 92 - SETC r/m8
    { const_string("SETNC"), 0x193, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 93 - SETNC r/m8
    { const_string("SETZ"), 0x194, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 94 - SETZ r/m8
    { const_string("SETNZ"), 0x195, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 95 - SETNZ r/m8
    { const_string("SETBE"), 0x196, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 96 - SETBE r/m8
    { const_string("SETNBE"), 0x197, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 97 - SETNBE r/m8
    { const_string("SETS"), 0x198, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 98 - SETS r/m8
    { const_string("SETNS"), 0x199, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 99 - SETNS r/m8
    { const_string("SETP"), 0x19a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 9a - SETP r/m8
    { const_string("SETNP"), 0x19b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 9b - SETNP r/m8
    { const_string("SETL"), 0x19c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 9c - SETL r/m8
    { const_string("SETNL"), 0x19d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 9d - SETNL r/m8
    { const_string("SETLE"), 0x19e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 9e - SETLE r/m8
    { const_string("SETNLE"), 0x19f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F 9f - SETNLE r/m8
    { const_string("PUSH"), 0x1a0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_fs, 0}} }, // 0F a0 - PUSH FS
    { const_string("POP"), 0x1a1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_fs, 0}} }, // 0F a1 - POP FS
    { const_string("CPUID"), 0x1a2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F a2 - CPUID 
    { const_string("BT"), 0x1a3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 0F a3 /r - BT r/m16, r16
    { const_string("BT"), 0x1a3, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 0F a3 /r - BT r/m32, r32
    { const_string("BT"), 0x1a3, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 0F a3 /r - BT r/m64, r64
    { const_string("SHLD"), 0x1a4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F a4 ib /r - SHLD r/m16, r16, imm8
    { const_string("SHLD"), 0x1a4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0F a4 ib /r - SHLD r/m32, r32, imm8
    { const_string("SHLD"), 0x1a4, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // REX.W 0F a4 ib /r - SHLD r/m64, r64, imm8
    { const_string("SHLD"), 0x1a5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}, {OPERAND_cl, 0}} }, // 66 0F a5 /r - SHLD r/m16, r16, cl
    { const_string("SHLD"), 0x1a5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}, {OPERAND_cl, 0}} }, // 0F a5 /r - SHLD r/m32, r32, cl
    { const_string("SHLD"), 0x1a5, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}, {OPERAND_cl, 0}} }, // REX.W 0F a5 /r - SHLD r/m64, r64, cl
    { const_string("PUSH"), 0x1a8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_gs, 0}} }, // 0F a8 - PUSH GS
    { const_string("POP"), 0x1a9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_gs, 0}} }, // 0F a9 - POP GS
    { const_string("RSM"), 0x1aa, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F aa - RSM 
    { const_string("BTS"), 0x1ab, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 0F ab /r - BTS r/m16, r16
    { const_string("BTS"), 0x1ab, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 0F ab /r - BTS r/m32, r32
    { const_string("BTS"), 0x1ab, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 0F ab /r - BTS r/m64, r64
    { const_string("SHRD"), 0x1ac, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F ac ib /r - SHRD r/m16, r16, imm8
    { const_string("SHRD"), 0x1ac, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0F ac ib /r - SHRD r/m32, r32, imm8
    { const_string("SHRD"), 0x1ac, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // REX.W 0F ac ib /r - SHRD r/m64, r64, imm8
    { const_string("SHRD"), 0x1ad, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm16, OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}, {OPERAND_cl, 0}} }, // 66 0F ad /r - SHRD r/m16, r16, cl
    { const_string("SHRD"), 0x1ad, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}, {OPERAND_cl, 0}} }, // 0F ad /r - SHRD r/m32, r32, cl
    { const_string("SHRD"), 0x1ad, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}, {OPERAND_cl, 0}} }, // REX.W 0F ad /r - SHRD r/m64, r64, cl
    { const_string("RDFSBASE"), 0x1ae, -1, 0, 1, 0, 0, 0, 0, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_write}} }, // F3 0F ae /0 - RDFSBASE r/m32
    { const_string("RDFSBASE"), 0x1ae, -1, 0, 1, 0, 1, 0, 0, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_write}} }, // F3 REX.W 0F ae /0 - RDFSBASE r/m64
    { const_string("FXSAVE"), 0x1ae, -1, 0, 0, 0, 0, 1, 0, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // 0F ae /0 - FXSAVE mem
    { const_string("FXSAVE64"), 0x1ae, -1, 0, 0, 0, 1, 1, 0, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // REX.W 0F ae /0 - FXSAVE64 mem
    { const_string("RDGSBASE"), 0x1ae, -1, 0, 1, 0, 0, 0, 1, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_write}} }, // F3 0F ae /1 - RDGSBASE r/m32
    { const_string("RDGSBASE"), 0x1ae, -1, 0, 1, 0, 1, 0, 1, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_write}} }, // F3 REX.W 0F ae /1 - RDGSBASE r/m64
    { const_string("FXRSTOR"), 0x1ae, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_read}} }, // 0F ae /1 - FXRSTOR mem
    { const_string("FXRSTOR64"), 0x1ae, -1, 0, 0, 0, 1, 1, 1, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_read}} }, // REX.W 0F ae /1 - FXRSTOR64 mem
    { const_string("WRFSBASE"), 0x1ae, -1, 0, 1, 0, 0, 0, 2, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read}} }, // F3 0F ae /2 - WRFSBASE r/m32
    { const_string("WRFSBASE"), 0x1ae, -1, 0, 1, 0, 1, 0, 2, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read}} }, // F3 REX.W 0F ae /2 - WRFSBASE r/m64
    { const_string("LDMXCSR"), 0x1ae, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_m32, OPERAND_FLAG_read}} }, // 0F ae /2 - LDMXCSR m32
    { const_string("WRGSBASE"), 0x1ae, -1, 0, 1, 0, 0, 0, 3, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read}} }, // F3 0F ae /3 - WRGSBASE r/m32
    { const_string("WRGSBASE"), 0x1ae, -1, 0, 1, 0, 1, 0, 3, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read}} }, // F3 REX.W 0F ae /3 - WRGSBASE r/m64
    { const_string("STMXCSR"), 0x1ae, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_m32, OPERAND_FLAG_write}} }, // 0F ae /3 - STMXCSR m32
    { const_string("XSAVE"), 0x1ae, -1, 0, 0, 0, 0, 1, 4, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // 0F ae /4 - XSAVE mem
    { const_string("XSAVE64"), 0x1ae, -1, 0, 0, 0, 1, 1, 4, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // REX.W 0F ae /4 - XSAVE64 mem
    { const_string("INCSSPD"), 0x1ae, -1, 0, 1, 0, 0, 0, 5, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_read}} }, // F3 0F ae /5 - INCSSPD r/m32
    { const_string("INCSSPQ"), 0x1ae, -1, 0, 1, 0, 1, 0, 5, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read}} }, // F3 REX.W 0F ae /5 - INCSSPQ r/m64
    { const_string("XRSTOR"), 0x1ae, -1, 0, 0, 0, 0, 1, 5, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_read}} }, // 0F ae /5 - XRSTOR mem
    { const_string("XRSTOR64"), 0x1ae, -1, 0, 0, 0, 1, 1, 5, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_read}} }, // REX.W 0F ae /5 - XRSTOR64 mem
    { const_string("CLRSSBSY"), 0x1ae, -1, 0, 1, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_m64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // F3 0F ae /6 - CLRSSBSY m64
    { const_string("UMONITOR"), 0x1ae, -1, 0, 1, 0, 0, 0, 6, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_read}} }, // F3 0F ae /6 - UMONITOR r/m64
    { const_string("UMWAIT"), 0x1ae, -1, 1, 0, 0, 0, 0, 6, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_edx, 0}, {OPERAND_eax, 0}} }, // F2 0F ae /6 - UMWAIT r/m32, edx, eax
    { const_string("CLWB"), 0x1ae, -1, 0, 0, 1, 0, 1, 6, 0, 0, 1, {{OPERAND_m8, OPERAND_FLAG_write}} }, // 66 0F ae /6 - CLWB m8
    { const_string("TPAUSE"), 0x1ae, -1, 0, 0, 1, 0, 0, 6, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_edx, 0}, {OPERAND_eax, 0}} }, // 66 0F ae /6 - TPAUSE r/m32, edx, eax
    { const_string("XSAVEOPT"), 0x1ae, -1, 0, 0, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // 0F ae /6 - XSAVEOPT mem
    { const_string("XSAVEOPT64"), 0x1ae, -1, 0, 0, 0, 1, 1, 6, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // REX.W 0F ae /6 - XSAVEOPT64 mem
    { const_string("CLFLUSHOPT"), 0x1ae, -1, 0, 0, 1, 0, 1, 7, 0, 0, 1, {{OPERAND_m8, OPERAND_FLAG_write}} }, // 66 0F ae /7 - CLFLUSHOPT m8
    { const_string("CLFLUSH"), 0x1ae, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_m8, OPERAND_FLAG_write}} }, // 0F ae /7 - CLFLUSH m8
    { const_string("LFENCE"), 0x1ae, 232, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F ae e8 - LFENCE 
    { const_string("MFENCE"), 0x1ae, 240, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F ae f0 - MFENCE 
    { const_string("SFENCE"), 0x1ae, 248, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // 0F ae f8 - SFENCE 
    { const_string("IMUL"), 0x1af, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F af /r - IMUL r16, r/m16
    { const_string("IMUL"), 0x1af, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F af /r - IMUL r32, r/m32
    { const_string("IMUL"), 0x1af, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F af /r - IMUL r64, r/m64
    { const_string("CMPXCHG"), 0x1b0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read}} }, // 0F b0 /r - CMPXCHG r/m8, r8
    { const_string("CMPXCHG"), 0x1b1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 0F b1 /r - CMPXCHG r/m16, r16
    { const_string("CMPXCHG"), 0x1b1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 0F b1 /r - CMPXCHG r/m32, r32
    { const_string("CMPXCHG"), 0x1b1, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 0F b1 /r - CMPXCHG r/m64, r64
    { const_string("LSS"), 0x1b2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_far_m16, OPERAND_FLAG_read}} }, // 66 0F b2 /r - LSS r16, m16:16
    { const_string("LSS"), 0x1b2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_far_m32, OPERAND_FLAG_read}} }, // 0F b2 /r - LSS r32, m16:32
    { const_string("LSS"), 0x1b2, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_far_m64, OPERAND_FLAG_read}} }, // REX.W 0F b2 /r - LSS r64, m16:64
    { const_string("BTR"), 0x1b3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 0F b3 /r - BTR r/m16, r16
    { const_string("BTR"), 0x1b3, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 0F b3 /r - BTR r/m32, r32
    { const_string("BTR"), 0x1b3, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 0F b3 /r - BTR r/m64, r64
    { const_string("LFS"), 0x1b4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_far_m16, OPERAND_FLAG_read}} }, // 66 0F b4 /r - LFS r16, m16:16
    { const_string("LFS"), 0x1b4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_far_m32, OPERAND_FLAG_read}} }, // 0F b4 /r - LFS r32, m16:32
    { const_string("LFS"), 0x1b4, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_far_m64, OPERAND_FLAG_read}} }, // REX.W 0F b4 /r - LFS r64, m16:64
    { const_string("LGS"), 0x1b5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_far_m16, OPERAND_FLAG_read}} }, // 66 0F b5 /r - LGS r16, m16:16
    { const_string("LGS"), 0x1b5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_far_m32, OPERAND_FLAG_read}} }, // 0F b5 /r - LGS r32, m16:32
    { const_string("LGS"), 0x1b5, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_far_m64, OPERAND_FLAG_read}} }, // REX.W 0F b5 /r - LGS r64, m16:64
    { const_string("MOVZX"), 0x1b6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 66 0F b6 /r - MOVZX r16, r/m8
    { const_string("MOVZX"), 0x1b6, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F b6 /r - MOVZX r32, r/m8
    { const_string("MOVZX"), 0x1b6, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // REX.W 0F b6 /r - MOVZX r64, r/m8
    { const_string("MOVZX"), 0x1b7, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 0F b7 /r - MOVZX r32, r/m16
    { const_string("MOVZX"), 0x1b7, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // REX.W 0F b7 /r - MOVZX r64, r/m16
    { const_string("POPCNT"), 0x1b8, -1, 0, 1, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // F3 66 0F b8 /r - POPCNT r16, r/m16
    { const_string("POPCNT"), 0x1b8, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // F3 0F b8 /r - POPCNT r32, r/m32
    { const_string("POPCNT"), 0x1b8, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // F3 REX.W 0F b8 /r - POPCNT r64, r/m64
    { const_string("UD1"), 0x1b9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F b9 /r - UD1 r32, r/m32
    { const_string("BT"), 0x1ba, -1, 0, 0, 1, 0, 0, 4, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F ba /4 ib - BT r/m16, imm8
    { const_string("BT"), 0x1ba, -1, 0, 0, 0, 0, 0, 4, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0F ba /4 ib - BT r/m32, imm8
    { const_string("BT"), 0x1ba, -1, 0, 0, 0, 1, 0, 4, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // REX.W 0F ba /4 ib - BT r/m64, imm8
    { const_string("BTS"), 0x1ba, -1, 0, 0, 1, 0, 0, 5, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F ba /5 ib - BTS r/m16, imm8
    { const_string("BTS"), 0x1ba, -1, 0, 0, 0, 0, 0, 5, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F ba /5 ib - BTS r/m32, imm8
    { const_string("BTS"), 0x1ba, -1, 0, 0, 0, 1, 0, 5, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W 0F ba /5 ib - BTS r/m64, imm8
    { const_string("BTR"), 0x1ba, -1, 0, 0, 1, 0, 0, 6, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F ba /6 ib - BTR r/m16, imm8
    { const_string("BTR"), 0x1ba, -1, 0, 0, 0, 0, 0, 6, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F ba /6 ib - BTR r/m32, imm8
    { const_string("BTR"), 0x1ba, -1, 0, 0, 0, 1, 0, 6, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W 0F ba /6 ib - BTR r/m64, imm8
    { const_string("BTC"), 0x1ba, -1, 0, 0, 1, 0, 0, 7, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 66 0F ba /7 ib - BTC r/m16, imm8
    { const_string("BTC"), 0x1ba, -1, 0, 0, 0, 0, 0, 7, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // 0F ba /7 ib - BTC r/m32, imm8
    { const_string("BTC"), 0x1ba, -1, 0, 0, 0, 1, 0, 7, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_imm8, 0}} }, // REX.W 0F ba /7 ib - BTC r/m64, imm8
    { const_string("BTC"), 0x1bb, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 0F bb /r - BTC r/m16, r16
    { const_string("BTC"), 0x1bb, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 0F bb /r - BTC r/m32, r32
    { const_string("BTC"), 0x1bb, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 0F bb /r - BTC r/m64, r64
    { const_string("TZCNT"), 0x1bc, -1, 0, 1, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // F3 66 0F bc /r - TZCNT r16, r/m16
    { const_string("TZCNT"), 0x1bc, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // F3 0F bc /r - TZCNT r32, r/m32
    { const_string("TZCNT"), 0x1bc, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // F3 REX.W 0F bc /r - TZCNT r64, r/m64
    { const_string("BSF"), 0x1bc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F bc /r - BSF r16, r/m16
    { const_string("BSF"), 0x1bc, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F bc /r - BSF r32, r/m32
    { const_string("BSF"), 0x1bc, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F bc /r - BSF r64, r/m64
    { const_string("LZCNT"), 0x1bd, -1, 0, 1, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // F3 66 0F bd /r - LZCNT r16, r/m16
    { const_string("LZCNT"), 0x1bd, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // F3 0F bd /r - LZCNT r32, r/m32
    { const_string("LZCNT"), 0x1bd, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // F3 REX.W 0F bd /r - LZCNT r64, r/m64
    { const_string("BSR"), 0x1bd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 66 0F bd /r - BSR r16, r/m16
    { const_string("BSR"), 0x1bd, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F bd /r - BSR r32, r/m32
    { const_string("BSR"), 0x1bd, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // REX.W 0F bd /r - BSR r64, r/m64
    { const_string("MOVSX"), 0x1be, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 66 0F be /r - MOVSX r16, r/m8
    { const_string("MOVSX"), 0x1be, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // 0F be /r - MOVSX r32, r/m8
    { const_string("MOVSX"), 0x1be, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // REX.W 0F be /r - MOVSX r64, r/m8
    { const_string("MOVSX"), 0x1bf, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // 0F bf /r - MOVSX r32, r/m16
    { const_string("MOVSX"), 0x1bf, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // REX.W 0F bf /r - MOVSX r64, r/m16
    { const_string("XADD"), 0x1c0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm8, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg8, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F c0 /r - XADD r/m8, r8
    { const_string("XADD"), 0x1c1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm16, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 66 0F c1 /r - XADD r/m16, r16
    { const_string("XADD"), 0x1c1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F c1 /r - XADD r/m32, r32
    { const_string("XADD"), 0x1c1, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 0F c1 /r - XADD r/m64, r64
    { const_string("CMPSS"), 0x1c2, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // F3 0F c2 ib /r - CMPSS xmm, xmm/m32, imm8
    { const_string("CMPSD"), 0x1c2, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // F2 0F c2 ib /r - CMPSD xmm, xmm/m64, imm8
    { const_string("CMPPD"), 0x1c2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F c2 ib /r - CMPPD xmm, xmm/m128, imm8
    { const_string("CMPPS"), 0x1c2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0F c2 ib /r - CMPPS xmm, xmm/m128, imm8
    { const_string("MOVNTI"), 0x1c3, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 0F c3 /r - MOVNTI m32, r32
    { const_string("MOVNTI"), 0x1c3, -1, 0, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 0F c3 /r - MOVNTI m64, r64
    { const_string("PINSRW"), 0x1c4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm16_zero_extended, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F c4 ib /r - PINSRW xmm, reg/m16, imm8
    { const_string("PINSRW"), 0x1c4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_regm16_zero_extended, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0F c4 ib /r - PINSRW mm, reg/m16, imm8
    { const_string("PEXTRW"), 0x1c5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F c5 ib /r - PEXTRW r64, xmm/m128, imm8
    { const_string("PEXTRW"), 0x1c5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0F c5 ib /r - PEXTRW r64, mm/m64, imm8
    { const_string("SHUFPD"), 0x1c6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F c6 ib /r - SHUFPD xmm, xmm/m128, imm8
    { const_string("SHUFPS"), 0x1c6, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0F c6 ib /r - SHUFPS xmm, xmm/m128, imm8
    { const_string("CMPXCHG8B"), 0x1c7, -1, 0, 0, 0, 0, 1, 1, 0, 0, 1, {{OPERAND_m64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F c7 /1 - CMPXCHG8B m64
    { const_string("CMPXCHG16B"), 0x1c7, -1, 0, 0, 0, 1, 1, 1, 0, 0, 1, {{OPERAND_m128, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 0F c7 /1 - CMPXCHG16B m128
    { const_string("XRSTORS"), 0x1c7, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_read}} }, // 0F c7 /3 - XRSTORS mem
    { const_string("XRSTORS64"), 0x1c7, -1, 0, 0, 0, 1, 1, 3, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_read}} }, // REX.W 0F c7 /3 - XRSTORS64 mem
    { const_string("XSAVEC"), 0x1c7, -1, 0, 0, 0, 0, 1, 4, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // 0F c7 /4 - XSAVEC mem
    { const_string("XSAVEC64"), 0x1c7, -1, 0, 0, 0, 1, 1, 4, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // REX.W 0F c7 /4 - XSAVEC64 mem
    { const_string("XSAVES"), 0x1c7, -1, 0, 0, 0, 0, 1, 5, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // 0F c7 /5 - XSAVES mem
    { const_string("XSAVES64"), 0x1c7, -1, 0, 0, 0, 1, 1, 5, 0, 0, 1, {{OPERAND_mem, OPERAND_FLAG_write}} }, // REX.W 0F c7 /5 - XSAVES64 mem
    { const_string("VMXON"), 0x1c7, -1, 0, 1, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_m64, OPERAND_FLAG_read}} }, // F3 0F c7 /6 - VMXON m64
    { const_string("VMCLEAR"), 0x1c7, -1, 0, 0, 1, 0, 1, 6, 0, 0, 1, {{OPERAND_m64, OPERAND_FLAG_read}} }, // 66 0F c7 /6 - VMCLEAR m64
    { const_string("RDRAND"), 0x1c7, -1, 0, 0, 1, 0, 0, 6, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_write}} }, // 66 0F c7 /6 - RDRAND r/m16
    { const_string("VMPTRLD"), 0x1c7, -1, 0, 0, 0, 0, 1, 6, 0, 0, 1, {{OPERAND_m64, OPERAND_FLAG_read}} }, // 0F c7 /6 - VMPTRLD m64
    { const_string("RDRAND"), 0x1c7, -1, 0, 0, 0, 0, 0, 6, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_write}} }, // 0F c7 /6 - RDRAND r/m32
    { const_string("RDRAND"), 0x1c7, -1, 0, 0, 0, 1, 0, 6, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_write}} }, // REX.W 0F c7 /6 - RDRAND r/m64
    { const_string("RDPID"), 0x1c7, -1, 0, 1, 0, 0, 0, 7, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_write}} }, // F3 0F c7 /7 - RDPID r/m64
    { const_string("RDSEED"), 0x1c7, -1, 0, 0, 1, 0, 0, 7, 0, 0, 1, {{OPERAND_regm16, OPERAND_FLAG_write}} }, // 66 0F c7 /7 - RDSEED r/m16
    { const_string("VMPTRST"), 0x1c7, -1, 0, 0, 0, 0, 1, 7, 0, 0, 1, {{OPERAND_m64, OPERAND_FLAG_write}} }, // 0F c7 /7 - VMPTRST m64
    { const_string("RDSEED"), 0x1c7, -1, 0, 0, 0, 0, 0, 7, 0, 0, 1, {{OPERAND_regm32, OPERAND_FLAG_write}} }, // 0F c7 /7 - RDSEED r/m32
    { const_string("RDSEED"), 0x1c7, -1, 0, 0, 0, 1, 0, 7, 0, 0, 1, {{OPERAND_regm64, OPERAND_FLAG_write}} }, // REX.W 0F c7 /7 - RDSEED r/m64
    { const_string("BSWAP"), 0x1c8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F c8 +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1c8, -1, 0, 0, 0, 1, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 0F c8 +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1c9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F c9 +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1c9, -1, 0, 0, 0, 1, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 0F c9 +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1ca, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F ca +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1ca, -1, 0, 0, 0, 1, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 0F ca +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1cb, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F cb +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1cb, -1, 0, 0, 0, 1, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 0F cb +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1cc, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F cc +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1cc, -1, 0, 0, 0, 1, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 0F cc +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1cd, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F cd +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1cd, -1, 0, 0, 0, 1, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 0F cd +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1ce, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F ce +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1ce, -1, 0, 0, 0, 1, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 0F ce +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1cf, -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, {{OPERAND_opcode32, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // 0F cf +reg - BSWAP +reg
    { const_string("BSWAP"), 0x1cf, -1, 0, 0, 0, 1, 0, -1, 0, 0, 1, {{OPERAND_opcode64, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // REX.W 0F cf +reg - BSWAP +reg
    { const_string("ADDSUBPS"), 0x1d0, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F2 0F d0 /r - ADDSUBPS xmm, xmm/m128
    { const_string("ADDSUBPD"), 0x1d0, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F d0 /r - ADDSUBPD xmm, xmm/m128
    { const_string("PSRLW"), 0x1d1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F d1 /r - PSRLW xmm, xmm/m128
    { const_string("PSRLW"), 0x1d1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F d1 /r - PSRLW mm, mm/m64
    { const_string("PSRLD"), 0x1d2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F d2 /r - PSRLD xmm, xmm/m128
    { const_string("PSRLD"), 0x1d2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F d2 /r - PSRLD mm, mm/m64
    { const_string("PSRLQ"), 0x1d3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F d3 /r - PSRLQ xmm, xmm/m128
    { const_string("PSRLQ"), 0x1d3, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F d3 /r - PSRLQ mm, mm/m64
    { const_string("PADDQ"), 0x1d4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F d4 /r - PADDQ xmm, xmm/m128
    { const_string("PADDQ"), 0x1d4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F d4 /r - PADDQ mm, mm/m64
    { const_string("PMULLW"), 0x1d5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F d5 /r - PMULLW xmm, xmm/m128
    { const_string("PMULLW"), 0x1d5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F d5 /r - PMULLW mm, mm/m64
    { const_string("MOVQ2DQ"), 0x1d6, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // F3 0F d6 /r - MOVQ2DQ xmm, mm/m64
    { const_string("MOVDQ2Q"), 0x1d6, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F2 0F d6 /r - MOVDQ2Q mm, xmm/m128
    { const_string("MOVQ"), 0x1d6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 66 0F d6 /r - MOVQ xmm/m64, xmm
    { const_string("PMOVMSKB"), 0x1d7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 48 0F d7 /r - PMOVMSKB r32, xmm/m128
    { const_string("PMOVMSKB"), 0x1d7, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F d7 /r - PMOVMSKB r64, xmm/m128
    { const_string("PMOVMSKB"), 0x1d7, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F d7 /r - PMOVMSKB r64, mm/m64
    { const_string("PSUBUSB"), 0x1d8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F d8 /r - PSUBUSB xmm, xmm/m128
    { const_string("PSUBUSB"), 0x1d8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F d8 /r - PSUBUSB mm, mm/m64
    { const_string("PSUBUSW"), 0x1d9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F d9 /r - PSUBUSW xmm, xmm/m128
    { const_string("PSUBUSW"), 0x1d9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F d9 /r - PSUBUSW mm, mm/m64
    { const_string("PMINUB"), 0x1da, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F da /r - PMINUB xmm, xmm/m128
    { const_string("PMINUB"), 0x1da, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F da /r - PMINUB mm, mm/m64
    { const_string("PAND"), 0x1db, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F db /r - PAND xmm, xmm/m128
    { const_string("PAND"), 0x1db, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F db /r - PAND mm, mm/m64
    { const_string("PADDUSB"), 0x1dc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F dc /r - PADDUSB xmm, xmm/m128
    { const_string("PADDUSB"), 0x1dc, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F dc /r - PADDUSB mm, mm/m64
    { const_string("PADDUSW"), 0x1dd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F dd /r - PADDUSW xmm, xmm/m128
    { const_string("PADDUSW"), 0x1dd, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F dd /r - PADDUSW mm, mm/m64
    { const_string("PMAXUB"), 0x1de, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F de /r - PMAXUB xmm, xmm/m128
    { const_string("PMAXUB"), 0x1de, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F de /r - PMAXUB mm, mm/m64
    { const_string("PANDN"), 0x1df, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F df /r - PANDN xmm, xmm/m128
    { const_string("PANDN"), 0x1df, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F df /r - PANDN mm, mm/m64
    { const_string("PAVGB"), 0x1e0, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F e0 /r - PAVGB xmm, xmm/m128
    { const_string("PAVGB"), 0x1e0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F e0 /r - PAVGB mm, mm/m64
    { const_string("PSRAW"), 0x1e1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F e1 /r - PSRAW xmm, xmm/m128
    { const_string("PSRAW"), 0x1e1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F e1 /r - PSRAW mm, mm/m64
    { const_string("PSRAD"), 0x1e2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F e2 /r - PSRAD xmm, xmm/m128
    { const_string("PSRAD"), 0x1e2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F e2 /r - PSRAD mm, mm/m64
    { const_string("PAVGW"), 0x1e3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F e3 /r - PAVGW xmm, xmm/m128
    { const_string("PAVGW"), 0x1e3, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F e3 /r - PAVGW mm, mm/m64
    { const_string("PMULHUW"), 0x1e4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F e4 /r - PMULHUW xmm, xmm/m128
    { const_string("PMULHUW"), 0x1e4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F e4 /r - PMULHUW mm, mm/m64
    { const_string("PMULHW"), 0x1e5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F e5 /r - PMULHW xmm, xmm/m128
    { const_string("PMULHW"), 0x1e5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F e5 /r - PMULHW mm, mm/m64
    { const_string("CVTDQ2PD"), 0x1e6, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // F3 0F e6 /r - CVTDQ2PD xmm, xmm/m64
    { const_string("CVTPD2DQ"), 0x1e6, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // F2 0F e6 /r - CVTPD2DQ xmm, xmm/m128
    { const_string("CVTTPD2DQ"), 0x1e6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F e6 /r - CVTTPD2DQ xmm, xmm/m128
    { const_string("MOVNTDQ"), 0x1e7, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // 66 0F e7 /r - MOVNTDQ m128, xmm
    { const_string("MOVNTQ"), 0x1e7, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_mm, OPERAND_FLAG_read}} }, // 0F e7 /r - MOVNTQ m64, mm
    { const_string("PSUBSB"), 0x1e8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F e8 /r - PSUBSB xmm, xmm/m128
    { const_string("PSUBSB"), 0x1e8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F e8 /r - PSUBSB mm, mm/m64
    { const_string("PSUBSW"), 0x1e9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F e9 /r - PSUBSW xmm, xmm/m128
    { const_string("PSUBSW"), 0x1e9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F e9 /r - PSUBSW mm, mm/m64
    { const_string("PMINSW"), 0x1ea, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F ea /r - PMINSW xmm, xmm/m128
    { const_string("PMINSW"), 0x1ea, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F ea /r - PMINSW mm, mm/m64
    { const_string("POR"), 0x1eb, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F eb /r - POR xmm, xmm/m128
    { const_string("POR"), 0x1eb, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F eb /r - POR mm, mm/m64
    { const_string("PADDSB"), 0x1ec, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F ec /r - PADDSB xmm, xmm/m128
    { const_string("PADDSB"), 0x1ec, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F ec /r - PADDSB mm, mm/m64
    { const_string("PADDSW"), 0x1ed, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F ed /r - PADDSW xmm, xmm/m128
    { const_string("PADDSW"), 0x1ed, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F ed /r - PADDSW mm, mm/m64
    { const_string("PMAXSW"), 0x1ee, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F ee /r - PMAXSW xmm, xmm/m128
    { const_string("PMAXSW"), 0x1ee, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F ee /r - PMAXSW mm, mm/m64
    { const_string("PXOR"), 0x1ef, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F ef /r - PXOR xmm, xmm/m128
    { const_string("PXOR"), 0x1ef, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F ef /r - PXOR mm, mm/m64
    { const_string("LDDQU"), 0x1f0, -1, 1, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_mem, OPERAND_FLAG_read}} }, // F2 0F f0 /r - LDDQU xmm, mem
    { const_string("PSLLW"), 0x1f1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F f1 /r - PSLLW xmm, xmm/m128
    { const_string("PSLLW"), 0x1f1, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F f1 /r - PSLLW mm, mm/m64
    { const_string("PSLLD"), 0x1f2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F f2 /r - PSLLD xmm, xmm/m128
    { const_string("PSLLD"), 0x1f2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F f2 /r - PSLLD mm, mm/m64
    { const_string("PSLLQ"), 0x1f3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F f3 /r - PSLLQ xmm, xmm/m128
    { const_string("PSLLQ"), 0x1f3, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F f3 /r - PSLLQ mm, mm/m64
    { const_string("PMULUDQ"), 0x1f4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F f4 /r - PMULUDQ xmm, xmm/m128
    { const_string("PMULUDQ"), 0x1f4, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F f4 /r - PMULUDQ mm, mm/m64
    { const_string("PMADDWD"), 0x1f5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F f5 /r - PMADDWD xmm, xmm/m128
    { const_string("PMADDWD"), 0x1f5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F f5 /r - PMADDWD mm, mm/m64
    { const_string("PSADBW"), 0x1f6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F f6 /r - PSADBW xmm, xmm/m128
    { const_string("PSADBW"), 0x1f6, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F f6 /r - PSADBW mm, mm/m64
    { const_string("MASKMOVDQU"), 0x1f7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F f7 /r - MASKMOVDQU xmm, xmm/m128
    { const_string("MASKMOVQ"), 0x1f7, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F f7 /r - MASKMOVQ mm, mm/m64
    { const_string("PSUBB"), 0x1f8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F f8 /r - PSUBB xmm, xmm/m128
    { const_string("PSUBB"), 0x1f8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F f8 /r - PSUBB mm, mm/m64
    { const_string("PSUBW"), 0x1f9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F f9 /r - PSUBW xmm, xmm/m128
    { const_string("PSUBW"), 0x1f9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F f9 /r - PSUBW mm, mm/m64
    { const_string("PSUBD"), 0x1fa, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F fa /r - PSUBD xmm, xmm/m128
    { const_string("PSUBD"), 0x1fa, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F fa /r - PSUBD mm, mm/m64
    { const_string("PSUBQ"), 0x1fb, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F fb /r - PSUBQ xmm, xmm/m128
    { const_string("PSUBQ"), 0x1fb, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F fb /r - PSUBQ mm, mm/m64
    { const_string("PADDB"), 0x1fc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F fc /r - PADDB xmm, xmm/m128
    { const_string("PADDB"), 0x1fc, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F fc /r - PADDB mm, mm/m64
    { const_string("PADDW"), 0x1fd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F fd /r - PADDW xmm, xmm/m128
    { const_string("PADDW"), 0x1fd, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F fd /r - PADDW mm, mm/m64
    { const_string("PADDD"), 0x1fe, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F fe /r - PADDD xmm, xmm/m128
    { const_string("PADDD"), 0x1fe, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F fe /r - PADDD mm, mm/m64
    { const_string("UD0"), 0x1ff, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 0F ff /r - UD0 r32, r/m32
    { const_string("PSHUFB"), 0x200, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 00 /r - PSHUFB xmm, xmm/m128
    { const_string("PSHUFB"), 0x200, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 00 /r - PSHUFB mm, mm/m64
    { const_string("PHADDW"), 0x201, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 01 /r - PHADDW xmm, xmm/m128
    { const_string("PHADDW"), 0x201, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 01 /r - PHADDW mm, mm/m64
    { const_string("PHADDD"), 0x202, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 02 /r - PHADDD xmm, xmm/m128
    { const_string("PHADDD"), 0x202, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 02 /r - PHADDD mm, mm/m64
    { const_string("PHADDSW"), 0x203, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 03 /r - PHADDSW xmm, xmm/m128
    { const_string("PHADDSW"), 0x203, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 03 /r - PHADDSW mm, mm/m64
    { const_string("PMADDUBSW"), 0x204, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 04 /r - PMADDUBSW xmm, xmm/m128
    { const_string("PMADDUBSW"), 0x204, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 04 /r - PMADDUBSW mm, mm/m64
    { const_string("PHSUBW"), 0x205, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 05 /r - PHSUBW xmm, xmm/m128
    { const_string("PHSUBW"), 0x205, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 05 /r - PHSUBW mm, mm/m64
    { const_string("PHSUBD"), 0x206, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 06 /r - PHSUBD xmm, xmm/m128
    { const_string("PHSUBD"), 0x206, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 06 /r - PHSUBD mm, mm/m64
    { const_string("PHSUBSW"), 0x207, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 07 /r - PHSUBSW xmm, xmm/m128
    { const_string("PHSUBSW"), 0x207, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 07 /r - PHSUBSW mm, mm/m64
    { const_string("PSIGNB"), 0x208, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 08 /r - PSIGNB xmm, xmm/m128
    { const_string("PSIGNB"), 0x208, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 08 /r - PSIGNB mm, mm/m64
    { const_string("PSIGNW"), 0x209, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 09 /r - PSIGNW xmm, xmm/m128
    { const_string("PSIGNW"), 0x209, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 09 /r - PSIGNW mm, mm/m64
    { const_string("PSIGND"), 0x20a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 0a /r - PSIGND xmm, xmm/m128
    { const_string("PSIGND"), 0x20a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 0a /r - PSIGND mm, mm/m64
    { const_string("PMULHRSW"), 0x20b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 0b /r - PMULHRSW xmm, xmm/m128
    { const_string("PMULHRSW"), 0x20b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 0b /r - PMULHRSW mm, mm/m64
    { const_string("PBLENDVB"), 0x210, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_xmm0, OPERAND_FLAG_read}} }, // 66 0F 38 10 /r - PBLENDVB xmm, xmm/m128, xmm0
    { const_string("BLENDVPS"), 0x214, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_xmm0, OPERAND_FLAG_read}} }, // 66 0F 38 14 /r - BLENDVPS xmm, xmm/m128, xmm0
    { const_string("BLENDVPD"), 0x215, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_xmm0, OPERAND_FLAG_read}} }, // 66 0F 38 15 /r - BLENDVPD xmm, xmm/m128, xmm0
    { const_string("PTEST"), 0x217, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 17 /r - PTEST xmm, xmm/m128
    { const_string("PABSB"), 0x21c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 1c /r - PABSB xmm, xmm/m128
    { const_string("PABSB"), 0x21c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 1c /r - PABSB mm, mm/m64
    { const_string("PABSW"), 0x21d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 1d /r - PABSW xmm, xmm/m128
    { const_string("PABSW"), 0x21d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 1d /r - PABSW mm, mm/m64
    { const_string("PABSD"), 0x21e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 1e /r - PABSD xmm, xmm/m128
    { const_string("PABSD"), 0x21e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_mm, OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}} }, // 0F 38 1e /r - PABSD mm, mm/m64
    { const_string("PMOVSXBW"), 0x220, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 66 0F 38 20 /r - PMOVSXBW xmm, xmm/m64
    { const_string("PMOVSXBD"), 0x221, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // 66 0F 38 21 /r - PMOVSXBD xmm, xmm/m32
    { const_string("PMOVSXBQ"), 0x222, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 66 0F 38 22 /r - PMOVSXBQ xmm, xmm/m64
    { const_string("PMOVSXWD"), 0x223, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 66 0F 38 23 /r - PMOVSXWD xmm, xmm/m64
    { const_string("PMOVSXWQ"), 0x224, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // 66 0F 38 24 /r - PMOVSXWQ xmm, xmm/m32
    { const_string("PMOVSXDQ"), 0x225, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 66 0F 38 25 /r - PMOVSXDQ xmm, xmm/m64
    { const_string("PMULDQ"), 0x228, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 28 /r - PMULDQ xmm, xmm/m128
    { const_string("PCMPEQQ"), 0x229, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 29 /r - PCMPEQQ xmm, xmm/m128
    { const_string("MOVNTDQA"), 0x22a, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // 66 0F 38 2a /r - MOVNTDQA xmm, m128
    { const_string("PACKUSDW"), 0x22b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 2b /r - PACKUSDW xmm, xmm/m128
    { const_string("PMOVZXBW"), 0x230, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 66 0F 38 30 /r - PMOVZXBW xmm, xmm/m64
    { const_string("PMOVZXBD"), 0x231, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // 66 0F 38 31 /r - PMOVZXBD xmm, xmm/m32
    { const_string("PMOVZXBQ"), 0x232, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 66 0F 38 32 /r - PMOVZXBQ xmm, xmm/m64
    { const_string("PMOVZXWD"), 0x233, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 66 0F 38 33 /r - PMOVZXWD xmm, xmm/m64
    { const_string("PMOVZXWQ"), 0x234, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // 66 0F 38 34 /r - PMOVZXWQ xmm, xmm/m32
    { const_string("PMOVZXDQ"), 0x235, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // 66 0F 38 35 /r - PMOVZXDQ xmm, xmm/m64
    { const_string("PCMPGTQ"), 0x237, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 37 /r - PCMPGTQ xmm, xmm/m128
    { const_string("PMINSB"), 0x238, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 38 /r - PMINSB xmm, xmm/m128
    { const_string("PMINSD"), 0x239, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 39 /r - PMINSD xmm, xmm/m128
    { const_string("PMINUW"), 0x23a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 3a /r - PMINUW xmm, xmm/m128
    { const_string("PMINUD"), 0x23b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 3b /r - PMINUD xmm, xmm/m128
    { const_string("PMAXSB"), 0x23c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 3c /r - PMAXSB xmm, xmm/m128
    { const_string("PMAXSD"), 0x23d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 3d /r - PMAXSD xmm, xmm/m128
    { const_string("PMAXUW"), 0x23e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 3e /r - PMAXUW xmm, xmm/m128
    { const_string("PMAXUD"), 0x23f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 3f /r - PMAXUD xmm, xmm/m128
    { const_string("PMULLD"), 0x240, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 40 /r - PMULLD xmm, xmm/m128
    { const_string("PHMINPOSUW"), 0x241, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 41 /r - PHMINPOSUW xmm, xmm/m128
    { const_string("INVEPT"), 0x280, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read}, {OPERAND_m128, OPERAND_FLAG_read}} }, // 66 0F 38 80 - INVEPT r64, m128
    { const_string("INVVPID"), 0x281, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read}, {OPERAND_m128, OPERAND_FLAG_read}} }, // 66 0F 38 81 - INVVPID r64, m128
    { const_string("INVPCID"), 0x282, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read}, {OPERAND_m128, OPERAND_FLAG_read}} }, // 66 0F 38 82 /r - INVPCID r64, m128
    { const_string("SHA1NEXTE"), 0x2c8, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 38 c8 /r - SHA1NEXTE xmm, xmm/m128
    { const_string("SHA1MSG1"), 0x2c9, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 38 c9 /r - SHA1MSG1 xmm, xmm/m128
    { const_string("SHA1MSG2"), 0x2ca, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 38 ca /r - SHA1MSG2 xmm, xmm/m128
    { const_string("SHA256RNDS2"), 0x2cb, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_xmm0, OPERAND_FLAG_read}} }, // 0F 38 cb /r - SHA256RNDS2 xmm, xmm/m128, xmm0
    { const_string("SHA256MSG1"), 0x2cc, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 38 cc /r - SHA256MSG1 xmm, xmm/m128
    { const_string("SHA256MSG2"), 0x2cd, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 0F 38 cd /r - SHA256MSG2 xmm, xmm/m128
    { const_string("GF2P8MULB"), 0x2cf, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 cf /r - GF2P8MULB xmm, xmm/m128
    { const_string("AESIMC"), 0x2db, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 db /r - AESIMC xmm, xmm/m128
    { const_string("AESENC"), 0x2dc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 dc /r - AESENC xmm, xmm/m128
    { const_string("AESENCLAST"), 0x2dd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 dd /r - AESENCLAST xmm, xmm/m128
    { const_string("AESDEC"), 0x2de, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 de /r - AESDEC xmm, xmm/m128
    { const_string("AESDECLAST"), 0x2df, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // 66 0F 38 df /r - AESDECLAST xmm, xmm/m128
    { const_string("CRC32"), 0x2f0, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // F2 0F 38 f0 /r - CRC32 r32, r/m8
    { const_string("CRC32"), 0x2f0, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm8, OPERAND_FLAG_read}} }, // F2 REX.W 0F 38 f0 /r - CRC32 r64, r/m8
    { const_string("MOVBE"), 0x2f0, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_reg16, OPERAND_FLAG_write}, {OPERAND_m16, OPERAND_FLAG_read}} }, // 66 0F 38 f0 /r - MOVBE r16, m16
    { const_string("MOVBE"), 0x2f0, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_m32, OPERAND_FLAG_read}} }, // 0F 38 f0 /r - MOVBE r32, m32
    { const_string("MOVBE"), 0x2f0, -1, 0, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // REX.W 0F 38 f0 /r - MOVBE r64, m64
    { const_string("CRC32"), 0x2f1, -1, 1, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm16, OPERAND_FLAG_read}} }, // F2 66 0F 38 f1 /r - CRC32 r32, r/m16
    { const_string("CRC32"), 0x2f1, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // F2 0F 38 f1 /r - CRC32 r32, r/m32
    { const_string("CRC32"), 0x2f1, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // F2 REX.W 0F 38 f1 /r - CRC32 r64, r/m64
    { const_string("MOVBE"), 0x2f1, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m16, OPERAND_FLAG_write}, {OPERAND_reg16, OPERAND_FLAG_read}} }, // 66 0F 38 f1 /r - MOVBE m16, r16
    { const_string("MOVBE"), 0x2f1, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 0F 38 f1 /r - MOVBE m32, r32
    { const_string("MOVBE"), 0x2f1, -1, 0, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 0F 38 f1 /r - MOVBE m64, r64
    { const_string("WRUSSD"), 0x2f5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 66 0F 38 f5 - WRUSSD r/m32, r32
    { const_string("WRUSSQ"), 0x2f5, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // 66 REX.W 0F 38 f5 - WRUSSQ r/m64, r64
    { const_string("ADOX"), 0x2f6, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // F3 0F 38 f6 /r - ADOX r32, r/m32
    { const_string("ADOX"), 0x2f6, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // F3 REX.W 0F 38 f6 /r - ADOX r64, r/m64
    { const_string("ADCX"), 0x2f6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // 66 0F 38 f6 /r - ADCX r32, r/m32
    { const_string("ADCX"), 0x2f6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // 66 REX.W 0F 38 f6 /r - ADCX r64, r/m64
    { const_string("WRSSD"), 0x2f6, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 0F 38 f6 - WRSSD r/m32, r32
    { const_string("WRSSQ"), 0x2f6, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 0F 38 f6 - WRSSQ r/m64, r64
    { const_string("MOVDIR64B"), 0x2f8, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_m512, OPERAND_FLAG_read}} }, // 66 0F 38 f8 /r - MOVDIR64B r64, m512
    { const_string("MOVDIRI"), 0x2f9, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_read}} }, // 0F 38 f9 /r - MOVDIRI m32, r32
    { const_string("MOVDIRI"), 0x2f9, -1, 0, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_read}} }, // REX.W 0F 38 f9 /r - MOVDIRI m64, r64
    { const_string("ROUNDPS"), 0x308, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 08 ib /r - ROUNDPS xmm, xmm/m128, imm8
    { const_string("ROUNDPD"), 0x309, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 09 ib /r - ROUNDPD xmm, xmm/m128, imm8
    { const_string("ROUNDSS"), 0x30a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 0a ib /r - ROUNDSS xmm, xmm/m32, imm8
    { const_string("ROUNDSD"), 0x30b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 0b ib /r - ROUNDSD xmm, xmm/m64, imm8
    { const_string("BLENDPS"), 0x30c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 0c ib /r - BLENDPS xmm, xmm/m128, imm8
    { const_string("BLENDPD"), 0x30d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 0d ib /r - BLENDPD xmm, xmm/m128, imm8
    { const_string("PBLENDW"), 0x30e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 0e ib /r - PBLENDW xmm, xmm/m128, imm8
    { const_string("PALIGNR"), 0x30f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 0f ib /r - PALIGNR xmm, xmm/m128, imm8
    { const_string("PALIGNR"), 0x30f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_mm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_mmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0F 3A 0f ib /r - PALIGNR mm, mm/m64, imm8
    { const_string("PEXTRB"), 0x314, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm8_zero_extended, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 14 ib /r - PEXTRB reg/m8, xmm, imm8
    { const_string("PEXTRW"), 0x315, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm16_zero_extended, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 15 ib /r - PEXTRW reg/m16, xmm, imm8
    { const_string("PEXTRD"), 0x316, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 16 ib /r - PEXTRD r/m32, xmm, imm8
    { const_string("PEXTRQ"), 0x316, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 REX.W 0F 3A 16 ib /r - PEXTRQ r/m64, xmm, imm8
    { const_string("EXTRACTPS"), 0x317, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 17 ib /r - EXTRACTPS r/m32, xmm, imm8
    { const_string("PINSRB"), 0x320, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm8_zero_extended, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 20 ib /r - PINSRB xmm, reg/m8, imm8
    { const_string("INSERTPS"), 0x321, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 21 ib /r - INSERTPS xmm, xmm/m32, imm8
    { const_string("PINSRD"), 0x322, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 22 ib /r - PINSRD xmm, r/m32, imm8
    { const_string("PINSRQ"), 0x322, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 REX.W 0F 3A 22 ib /r - PINSRQ xmm, r/m64, imm8
    { const_string("DPPS"), 0x340, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 40 ib /r - DPPS xmm, xmm/m128, imm8
    { const_string("DPPD"), 0x341, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 41 ib /r - DPPD xmm, xmm/m128, imm8
    { const_string("MPSADBW"), 0x342, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 42 ib /r - MPSADBW xmm, xmm/m128, imm8
    { const_string("PCLMULQDQ"), 0x344, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 44 ib /r - PCLMULQDQ xmm, xmm/m128, imm8
    { const_string("PCMPESTRM"), 0x360, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 60 ib /r - PCMPESTRM xmm, xmm/m128, imm8
    { const_string("PCMPESTRI"), 0x361, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 61 ib /r - PCMPESTRI xmm, xmm/m128, imm8
    { const_string("PCMPISTRM"), 0x362, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 62 ib /r - PCMPISTRM xmm, xmm/m128, imm8
    { const_string("PCMPISTRI"), 0x363, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A 63 ib /r - PCMPISTRI xmm, xmm/m128, imm8
    { const_string("SHA1RNDS4"), 0x3cc, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 0F 3A cc ib /r - SHA1RNDS4 xmm, xmm/m128, imm8
    { const_string("GF2P8AFFINEQB"), 0x3ce, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A ce ib /r - GF2P8AFFINEQB xmm, xmm/m128, imm8
    { const_string("GF2P8AFFINEINVQB"), 0x3cf, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A cf ib /r - GF2P8AFFINEINVQB xmm, xmm/m128, imm8
    { const_string("AESKEYGENASSIST"), 0x3df, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // 66 0F 3A df ib /r - AESKEYGENASSIST xmm, xmm/m128, imm8
};

struct instruction_table_entry vex_instructions[] = {
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 10 /r - VMOVSS xmm, m32
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 10 /r - VMOVSS xmm, vex128, xmm/m128
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 10 /r - VMOVSS xmm, m32
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 10 /r - VMOVSS xmm, vex128, xmm/m128
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 0, 1, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 10 /r - VMOVSS xmm, m32
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 10 /r - VMOVSS xmm, vex128, xmm/m128
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 1, 1, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 10 /r - VMOVSS xmm, m32
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 10 /r - VMOVSS xmm, vex128, xmm/m128
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 10 /r - VMOVSD xmm, m64
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 10 /r - VMOVSD xmm, vex128, xmm/m128
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 10 /r - VMOVSD xmm, m64
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 10 /r - VMOVSD xmm, vex128, xmm/m128
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 0, 1, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 10 /r - VMOVSD xmm, m64
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 10 /r - VMOVSD xmm, vex128, xmm/m128
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 1, 1, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 10 /r - VMOVSD xmm, m64
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 10 /r - VMOVSD xmm, vex128, xmm/m128
    { const_string("VMOVUPD"), 0x110, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 10 /r - VMOVUPD xmm, xmm/m128
    { const_string("VMOVUPD"), 0x110, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 10 /r - VMOVUPD xmm, xmm/m128
    { const_string("VMOVUPD"), 0x110, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 10 /r - VMOVUPD ymm, ymm/m256
    { const_string("VMOVUPD"), 0x110, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 10 /r - VMOVUPD ymm, ymm/m256
    { const_string("VMOVUPS"), 0x110, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 10 /r - VMOVUPS xmm, xmm/m128
    { const_string("VMOVUPS"), 0x110, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 10 /r - VMOVUPS xmm, xmm/m128
    { const_string("VMOVUPS"), 0x110, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 10 /r - VMOVUPS ymm, ymm/m256
    { const_string("VMOVUPS"), 0x110, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 10 /r - VMOVUPS ymm, ymm/m256
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 11 /r - VMOVSS m32, xmm
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 11 /r - VMOVSS xmm/m128, vex128, xmm
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_m32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 11 /r - VMOVSS m32, xmm
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 11 /r - VMOVSS xmm/m128, vex128, xmm
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 0, 1, -1, 0, 1, 2, {{OPERAND_m32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 11 /r - VMOVSS m32, xmm
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 11 /r - VMOVSS xmm/m128, vex128, xmm
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 1, 1, -1, 0, 1, 2, {{OPERAND_m32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 11 /r - VMOVSS m32, xmm
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 11 /r - VMOVSS xmm/m128, vex128, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 11 /r - VMOVSD m64, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 11 /r - VMOVSD xmm/m128, vex128, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 11 /r - VMOVSD m64, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 11 /r - VMOVSD xmm/m128, vex128, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 0, 1, -1, 0, 1, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 11 /r - VMOVSD m64, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 11 /r - VMOVSD xmm/m128, vex128, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 1, 1, -1, 0, 1, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 11 /r - VMOVSD m64, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 11 /r - VMOVSD xmm/m128, vex128, xmm
    { const_string("VMOVUPD"), 0x111, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 11 /r - VMOVUPD xmm/m128, xmm
    { const_string("VMOVUPD"), 0x111, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 11 /r - VMOVUPD xmm/m128, xmm
    { const_string("VMOVUPD"), 0x111, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 11 /r - VMOVUPD ymm/m256, ymm
    { const_string("VMOVUPD"), 0x111, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 11 /r - VMOVUPD ymm/m256, ymm
    { const_string("VMOVUPS"), 0x111, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 11 /r - VMOVUPS xmm/m128, xmm
    { const_string("VMOVUPS"), 0x111, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 11 /r - VMOVUPS xmm/m128, xmm
    { const_string("VMOVUPS"), 0x111, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 11 /r - VMOVUPS ymm/m256, ymm
    { const_string("VMOVUPS"), 0x111, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 11 /r - VMOVUPS ymm/m256, ymm
    { const_string("VMOVSLDUP"), 0x112, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 12 /r - VMOVSLDUP xmm, xmm/m128
    { const_string("VMOVSLDUP"), 0x112, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 12 /r - VMOVSLDUP xmm, xmm/m128
    { const_string("VMOVSLDUP"), 0x112, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 12 /r - VMOVSLDUP ymm, ymm/m256
    { const_string("VMOVSLDUP"), 0x112, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 12 /r - VMOVSLDUP ymm, ymm/m256
    { const_string("VMOVDDUP"), 0x112, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 12 /r - VMOVDDUP xmm, xmm/m64
    { const_string("VMOVDDUP"), 0x112, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 12 /r - VMOVDDUP xmm, xmm/m64
    { const_string("VMOVDDUP"), 0x112, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 12 /r - VMOVDDUP ymm, ymm/m256
    { const_string("VMOVDDUP"), 0x112, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 12 /r - VMOVDDUP ymm, ymm/m256
    { const_string("VMOVLPD"), 0x112, -1, 0, 0, 1, 0, 1, -1, 0, 0, 3, {{OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 12 /r - VMOVLPD xmm/m128, vex128, m64
    { const_string("VMOVLPD"), 0x112, -1, 0, 0, 1, 1, 1, -1, 0, 0, 3, {{OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 12 /r - VMOVLPD xmm/m128, vex128, m64
    { const_string("VMOVLPS"), 0x112, -1, 0, 0, 0, 0, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 12 /r - VMOVLPS xmm, vex128, m64
    { const_string("VMOVHLPS"), 0x112, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 12 /r - VMOVHLPS xmm, vex128, xmm/m128
    { const_string("VMOVLPS"), 0x112, -1, 0, 0, 0, 1, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 12 /r - VMOVLPS xmm, vex128, m64
    { const_string("VMOVHLPS"), 0x112, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 12 /r - VMOVHLPS xmm, vex128, xmm/m128
    { const_string("VMOVLPD"), 0x113, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 13 /r - VMOVLPD m64, xmm
    { const_string("VMOVLPD"), 0x113, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 13 /r - VMOVLPD m64, xmm
    { const_string("VMOVLPS"), 0x113, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 13 /r - VMOVLPS m64, xmm
    { const_string("VMOVLPS"), 0x113, -1, 0, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 13 /r - VMOVLPS m64, xmm
    { const_string("VUNPCKLPD"), 0x114, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 14 /r - VUNPCKLPD xmm, vex128, xmm/m128
    { const_string("VUNPCKLPD"), 0x114, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 14 /r - VUNPCKLPD xmm, vex128, xmm/m128
    { const_string("VUNPCKLPD"), 0x114, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 14 /r - VUNPCKLPD ymm, vex256, ymm/m256
    { const_string("VUNPCKLPD"), 0x114, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 14 /r - VUNPCKLPD ymm, vex256, ymm/m256
    { const_string("VUNPCKLPS"), 0x114, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 14 /r - VUNPCKLPS xmm, vex128, xmm/m128
    { const_string("VUNPCKLPS"), 0x114, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 14 /r - VUNPCKLPS xmm, vex128, xmm/m128
    { const_string("VUNPCKLPS"), 0x114, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 14 /r - VUNPCKLPS ymm, vex256, ymm/m256
    { const_string("VUNPCKLPS"), 0x114, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 14 /r - VUNPCKLPS ymm, vex256, ymm/m256
    { const_string("VUNPCKHPD"), 0x115, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 15 /r - VUNPCKHPD xmm, vex128, xmm/m128
    { const_string("VUNPCKHPD"), 0x115, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 15 /r - VUNPCKHPD xmm, vex128, xmm/m128
    { const_string("VUNPCKHPD"), 0x115, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 15 /r - VUNPCKHPD ymm, vex256, ymm/m256
    { const_string("VUNPCKHPD"), 0x115, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 15 /r - VUNPCKHPD ymm, vex256, ymm/m256
    { const_string("VUNPCKHPS"), 0x115, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 15 /r - VUNPCKHPS xmm, vex128, xmm/m128
    { const_string("VUNPCKHPS"), 0x115, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 15 /r - VUNPCKHPS xmm, vex128, xmm/m128
    { const_string("VUNPCKHPS"), 0x115, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 15 /r - VUNPCKHPS ymm, vex256, ymm/m256
    { const_string("VUNPCKHPS"), 0x115, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 15 /r - VUNPCKHPS ymm, vex256, ymm/m256
    { const_string("VMOVSHDUP"), 0x116, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 16 /r - VMOVSHDUP xmm, xmm/m128
    { const_string("VMOVSHDUP"), 0x116, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 16 /r - VMOVSHDUP xmm, xmm/m128
    { const_string("VMOVSHDUP"), 0x116, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 16 /r - VMOVSHDUP ymm, ymm/m256
    { const_string("VMOVSHDUP"), 0x116, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 16 /r - VMOVSHDUP ymm, ymm/m256
    { const_string("VMOVHPD"), 0x116, -1, 0, 0, 1, 0, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 16 /r - VMOVHPD xmm, vex128, m64
    { const_string("VMOVHPD"), 0x116, -1, 0, 0, 1, 1, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 16 /r - VMOVHPD xmm, vex128, m64
    { const_string("VMOVHPS"), 0x116, -1, 0, 0, 0, 0, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 16 /r - VMOVHPS xmm, vex128, m64
    { const_string("VMOVLHPS"), 0x116, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 16 /r - VMOVLHPS xmm, vex128, xmm/m128
    { const_string("VMOVHPS"), 0x116, -1, 0, 0, 0, 1, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 16 /r - VMOVHPS xmm, vex128, m64
    { const_string("VMOVLHPS"), 0x116, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 16 /r - VMOVLHPS xmm, vex128, xmm/m128
    { const_string("VMOVHPD"), 0x117, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 17 /r - VMOVHPD m64, xmm
    { const_string("VMOVHPD"), 0x117, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 17 /r - VMOVHPD m64, xmm
    { const_string("VMOVHPS"), 0x117, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 17 /r - VMOVHPS m64, xmm
    { const_string("VMOVHPS"), 0x117, -1, 0, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 17 /r - VMOVHPS m64, xmm
    { const_string("VMOVAPD"), 0x128, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 28 /r - VMOVAPD xmm, xmm/m128
    { const_string("VMOVAPD"), 0x128, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 28 /r - VMOVAPD xmm, xmm/m128
    { const_string("VMOVAPD"), 0x128, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 28 /r - VMOVAPD ymm, ymm/m256
    { const_string("VMOVAPD"), 0x128, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 28 /r - VMOVAPD ymm, ymm/m256
    { const_string("VMOVAPS"), 0x128, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 28 /r - VMOVAPS xmm, xmm/m128
    { const_string("VMOVAPS"), 0x128, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 28 /r - VMOVAPS xmm, xmm/m128
    { const_string("VMOVAPS"), 0x128, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 28 /r - VMOVAPS ymm, ymm/m256
    { const_string("VMOVAPS"), 0x128, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 28 /r - VMOVAPS ymm, ymm/m256
    { const_string("VMOVAPD"), 0x129, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 29 /r - VMOVAPD xmm/m128, xmm
    { const_string("VMOVAPD"), 0x129, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 29 /r - VMOVAPD xmm/m128, xmm
    { const_string("VMOVAPD"), 0x129, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 29 /r - VMOVAPD ymm/m256, ymm
    { const_string("VMOVAPD"), 0x129, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 29 /r - VMOVAPD ymm/m256, ymm
    { const_string("VMOVAPS"), 0x129, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 29 /r - VMOVAPS xmm/m128, xmm
    { const_string("VMOVAPS"), 0x129, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 29 /r - VMOVAPS xmm/m128, xmm
    { const_string("VMOVAPS"), 0x129, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 29 /r - VMOVAPS ymm/m256, ymm
    { const_string("VMOVAPS"), 0x129, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 29 /r - VMOVAPS ymm/m256, ymm
    { const_string("VCVTSI2SS"), 0x12a, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 2a /r - VCVTSI2SS xmm, vex128, r/m32
    { const_string("VCVTSI2SS"), 0x12a, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 2a /r - VCVTSI2SS xmm, vex128, r/m64
    { const_string("VCVTSI2SS"), 0x12a, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 2a /r - VCVTSI2SS xmm, vex128, r/m32
    { const_string("VCVTSI2SS"), 0x12a, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 2a /r - VCVTSI2SS xmm, vex128, r/m64
    { const_string("VCVTSI2SD"), 0x12a, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 2a /r - VCVTSI2SD xmm, vex128, r/m32
    { const_string("VCVTSI2SD"), 0x12a, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 2a /r - VCVTSI2SD xmm, vex128, r/m64
    { const_string("VCVTSI2SD"), 0x12a, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 2a /r - VCVTSI2SD xmm, vex128, r/m32
    { const_string("VCVTSI2SD"), 0x12a, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 2a /r - VCVTSI2SD xmm, vex128, r/m64
    { const_string("VMOVNTPD"), 0x12b, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 2b /r - VMOVNTPD m128, xmm
    { const_string("VMOVNTPD"), 0x12b, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 2b /r - VMOVNTPD m128, xmm
    { const_string("VMOVNTPD"), 0x12b, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 2b /r - VMOVNTPD m256, ymm
    { const_string("VMOVNTPD"), 0x12b, -1, 0, 0, 1, 1, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 2b /r - VMOVNTPD m256, ymm
    { const_string("VMOVNTPS"), 0x12b, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 2b /r - VMOVNTPS m128, xmm
    { const_string("VMOVNTPS"), 0x12b, -1, 0, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 2b /r - VMOVNTPS m128, xmm
    { const_string("VMOVNTPS"), 0x12b, -1, 0, 0, 0, 0, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 2b /r - VMOVNTPS m256, ymm
    { const_string("VMOVNTPS"), 0x12b, -1, 0, 0, 0, 1, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 2b /r - VMOVNTPS m256, ymm
    { const_string("VCVTTSS2SI"), 0x12c, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 2c /r - VCVTTSS2SI r32, xmm/m32
    { const_string("VCVTTSS2SI"), 0x12c, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 2c /r - VCVTTSS2SI r64, xmm/m32
    { const_string("VCVTTSS2SI"), 0x12c, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 2c /r - VCVTTSS2SI r32, xmm/m32
    { const_string("VCVTTSS2SI"), 0x12c, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 2c /r - VCVTTSS2SI r64, xmm/m32
    { const_string("VCVTTSD2SI"), 0x12c, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 2c /r - VCVTTSD2SI r32, xmm/m64
    { const_string("VCVTTSD2SI"), 0x12c, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 2c /r - VCVTTSD2SI r64, xmm/m64
    { const_string("VCVTTSD2SI"), 0x12c, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 2c /r - VCVTTSD2SI r32, xmm/m64
    { const_string("VCVTTSD2SI"), 0x12c, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 2c /r - VCVTTSD2SI r64, xmm/m64
    { const_string("VCVTSS2SI"), 0x12d, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 2d /r - VCVTSS2SI r32, xmm/m32
    { const_string("VCVTSS2SI"), 0x12d, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 2d /r - VCVTSS2SI r64, xmm/m32
    { const_string("VCVTSS2SI"), 0x12d, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 2d /r - VCVTSS2SI r32, xmm/m32
    { const_string("VCVTSS2SI"), 0x12d, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 2d /r - VCVTSS2SI r64, xmm/m32
    { const_string("VCVTSD2SI"), 0x12d, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 2d /r - VCVTSD2SI r32, xmm/m64
    { const_string("VCVTSD2SI"), 0x12d, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 2d /r - VCVTSD2SI r64, xmm/m64
    { const_string("VCVTSD2SI"), 0x12d, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 2d /r - VCVTSD2SI r32, xmm/m64
    { const_string("VCVTSD2SI"), 0x12d, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 2d /r - VCVTSD2SI r64, xmm/m64
    { const_string("VUCOMISD"), 0x12e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 2e /r - VUCOMISD xmm, xmm/m64
    { const_string("VUCOMISD"), 0x12e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 2e /r - VUCOMISD xmm, xmm/m64
    { const_string("VUCOMISD"), 0x12e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 2e /r - VUCOMISD xmm, xmm/m64
    { const_string("VUCOMISD"), 0x12e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 2e /r - VUCOMISD xmm, xmm/m64
    { const_string("VUCOMISS"), 0x12e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 2e /r - VUCOMISS xmm, xmm/m32
    { const_string("VUCOMISS"), 0x12e, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 2e /r - VUCOMISS xmm, xmm/m32
    { const_string("VUCOMISS"), 0x12e, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 2e /r - VUCOMISS xmm, xmm/m32
    { const_string("VUCOMISS"), 0x12e, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 2e /r - VUCOMISS xmm, xmm/m32
    { const_string("VCOMISD"), 0x12f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 2f /r - VCOMISD xmm, xmm/m64
    { const_string("VCOMISD"), 0x12f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 2f /r - VCOMISD xmm, xmm/m64
    { const_string("VCOMISD"), 0x12f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 2f /r - VCOMISD xmm, xmm/m64
    { const_string("VCOMISD"), 0x12f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 2f /r - VCOMISD xmm, xmm/m64
    { const_string("VCOMISS"), 0x12f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 2f /r - VCOMISS xmm, xmm/m32
    { const_string("VCOMISS"), 0x12f, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 2f /r - VCOMISS xmm, xmm/m32
    { const_string("VCOMISS"), 0x12f, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 2f /r - VCOMISS xmm, xmm/m32
    { const_string("VCOMISS"), 0x12f, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 2f /r - VCOMISS xmm, xmm/m32
    { const_string("KANDB"), 0x141, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 41 /r - KANDB k, vex_k, k/m64
    { const_string("KANDD"), 0x141, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 41 /r - KANDD k, vex_k, k/m64
    { const_string("KANDW"), 0x141, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 41 /r - KANDW k, vex_k, k/m64
    { const_string("KANDQ"), 0x141, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 41 /r - KANDQ k, vex_k, k/m64
    { const_string("KANDNB"), 0x142, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 42 /r - KANDNB k, vex_k, k/m64
    { const_string("KANDND"), 0x142, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 42 /r - KANDND k, vex_k, k/m64
    { const_string("KANDNW"), 0x142, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 42 /r - KANDNW k, vex_k, k/m64
    { const_string("KANDNQ"), 0x142, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 42 /r - KANDNQ k, vex_k, k/m64
    { const_string("KNOTB"), 0x144, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 44 /r - KNOTB k, k/m64
    { const_string("KNOTD"), 0x144, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 44 /r - KNOTD k, k/m64
    { const_string("KNOTW"), 0x144, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 44 /r - KNOTW k, k/m64
    { const_string("KNOTQ"), 0x144, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 44 /r - KNOTQ k, k/m64
    { const_string("KORB"), 0x145, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 45 /r - KORB k, vex_k, k/m64
    { const_string("KORD"), 0x145, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 45 /r - KORD k, vex_k, k/m64
    { const_string("KORW"), 0x145, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 45 /r - KORW k, vex_k, k/m64
    { const_string("KORQ"), 0x145, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 45 /r - KORQ k, vex_k, k/m64
    { const_string("KXNORB"), 0x146, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 46 /r - KXNORB k, vex_k, k/m64
    { const_string("KXNORD"), 0x146, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 46 /r - KXNORD k, vex_k, k/m64
    { const_string("KXNORW"), 0x146, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 46 /r - KXNORW k, vex_k, k/m64
    { const_string("KXNORQ"), 0x146, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 46 /r - KXNORQ k, vex_k, k/m64
    { const_string("KXORB"), 0x147, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 47 /r - KXORB k, vex_k, k/m64
    { const_string("KXORD"), 0x147, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 47 /r - KXORD k, vex_k, k/m64
    { const_string("KXORW"), 0x147, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 47 /r - KXORW k, vex_k, k/m64
    { const_string("KXORQ"), 0x147, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 47 /r - KXORQ k, vex_k, k/m64
    { const_string("KADDB"), 0x14a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 4a /r - KADDB k, vex_k, k/m64
    { const_string("KADDD"), 0x14a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 4a /r - KADDD k, vex_k, k/m64
    { const_string("KADDW"), 0x14a, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 4a /r - KADDW k, vex_k, k/m64
    { const_string("KADDQ"), 0x14a, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 4a /r - KADDQ k, vex_k, k/m64
    { const_string("KUNPCKBW"), 0x14b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 4b /r - KUNPCKBW k, vex_k, k/m64
    { const_string("KUNPCKWD"), 0x14b, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 4b /r - KUNPCKWD k, vex_k, k/m64
    { const_string("KUNPCKDQ"), 0x14b, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 4b /r - KUNPCKDQ k, vex_k, k/m64
    { const_string("VMOVMSKPD"), 0x150, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 50 /r - VMOVMSKPD r64, xmm/m128
    { const_string("VMOVMSKPD"), 0x150, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 50 /r - VMOVMSKPD r64, xmm/m128
    { const_string("VMOVMSKPD"), 0x150, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 50 /r - VMOVMSKPD r64, ymm/m256
    { const_string("VMOVMSKPD"), 0x150, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 50 /r - VMOVMSKPD r64, ymm/m256
    { const_string("VMOVMSKPS"), 0x150, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 50 /r - VMOVMSKPS r64, xmm/m128
    { const_string("VMOVMSKPS"), 0x150, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 50 /r - VMOVMSKPS r64, xmm/m128
    { const_string("VMOVMSKPS"), 0x150, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 50 /r - VMOVMSKPS r64, ymm/m256
    { const_string("VMOVMSKPS"), 0x150, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 50 /r - VMOVMSKPS r64, ymm/m256
    { const_string("VSQRTSS"), 0x151, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 51 /r - VSQRTSS xmm, vex128, xmm/m32
    { const_string("VSQRTSS"), 0x151, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 51 /r - VSQRTSS xmm, vex128, xmm/m32
    { const_string("VSQRTSS"), 0x151, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 51 /r - VSQRTSS xmm, vex128, xmm/m32
    { const_string("VSQRTSS"), 0x151, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 51 /r - VSQRTSS xmm, vex128, xmm/m32
    { const_string("VSQRTSD"), 0x151, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 51 /r - VSQRTSD xmm, vex128, xmm/m64
    { const_string("VSQRTSD"), 0x151, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 51 /r - VSQRTSD xmm, vex128, xmm/m64
    { const_string("VSQRTSD"), 0x151, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 51 /r - VSQRTSD xmm, vex128, xmm/m64
    { const_string("VSQRTSD"), 0x151, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 51 /r - VSQRTSD xmm, vex128, xmm/m64
    { const_string("VSQRTPD"), 0x151, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 51 /r - VSQRTPD xmm, xmm/m128
    { const_string("VSQRTPD"), 0x151, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 51 /r - VSQRTPD xmm, xmm/m128
    { const_string("VSQRTPD"), 0x151, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 51 /r - VSQRTPD ymm, ymm/m256
    { const_string("VSQRTPD"), 0x151, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 51 /r - VSQRTPD ymm, ymm/m256
    { const_string("VSQRTPS"), 0x151, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 51 /r - VSQRTPS xmm, xmm/m128
    { const_string("VSQRTPS"), 0x151, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 51 /r - VSQRTPS xmm, xmm/m128
    { const_string("VSQRTPS"), 0x151, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 51 /r - VSQRTPS ymm, ymm/m256
    { const_string("VSQRTPS"), 0x151, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 51 /r - VSQRTPS ymm, ymm/m256
    { const_string("VRSQRTSS"), 0x152, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 52 /r - VRSQRTSS xmm, vex128, xmm/m32
    { const_string("VRSQRTSS"), 0x152, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 52 /r - VRSQRTSS xmm, vex128, xmm/m32
    { const_string("VRSQRTSS"), 0x152, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 52 /r - VRSQRTSS xmm, vex128, xmm/m32
    { const_string("VRSQRTSS"), 0x152, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 52 /r - VRSQRTSS xmm, vex128, xmm/m32
    { const_string("VRSQRTPS"), 0x152, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 52 /r - VRSQRTPS xmm, xmm/m128
    { const_string("VRSQRTPS"), 0x152, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 52 /r - VRSQRTPS xmm, xmm/m128
    { const_string("VRSQRTPS"), 0x152, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 52 /r - VRSQRTPS ymm, ymm/m256
    { const_string("VRSQRTPS"), 0x152, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 52 /r - VRSQRTPS ymm, ymm/m256
    { const_string("VRCPSS"), 0x153, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 53 /r - VRCPSS xmm, vex128, xmm/m32
    { const_string("VRCPSS"), 0x153, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 53 /r - VRCPSS xmm, vex128, xmm/m32
    { const_string("VRCPSS"), 0x153, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 53 /r - VRCPSS xmm, vex128, xmm/m32
    { const_string("VRCPSS"), 0x153, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 53 /r - VRCPSS xmm, vex128, xmm/m32
    { const_string("VRCPPS"), 0x153, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 53 /r - VRCPPS xmm, xmm/m128
    { const_string("VRCPPS"), 0x153, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 53 /r - VRCPPS xmm, xmm/m128
    { const_string("VRCPPS"), 0x153, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 53 /r - VRCPPS ymm, ymm/m256
    { const_string("VRCPPS"), 0x153, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 53 /r - VRCPPS ymm, ymm/m256
    { const_string("VANDPD"), 0x154, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 54 /r - VANDPD xmm, vex128, xmm/m128
    { const_string("VANDPD"), 0x154, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 54 /r - VANDPD xmm, vex128, xmm/m128
    { const_string("VANDPD"), 0x154, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 54 /r - VANDPD ymm, vex256, ymm/m256
    { const_string("VANDPD"), 0x154, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 54 /r - VANDPD ymm, vex256, ymm/m256
    { const_string("VANDPS"), 0x154, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 54 /r - VANDPS xmm, vex128, xmm/m128
    { const_string("VANDPS"), 0x154, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 54 /r - VANDPS xmm, vex128, xmm/m128
    { const_string("VANDPS"), 0x154, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 54 /r - VANDPS ymm, vex256, ymm/m256
    { const_string("VANDPS"), 0x154, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 54 /r - VANDPS ymm, vex256, ymm/m256
    { const_string("VANDNPD"), 0x155, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 55 /r - VANDNPD xmm, vex128, xmm/m128
    { const_string("VANDNPD"), 0x155, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 55 /r - VANDNPD xmm, vex128, xmm/m128
    { const_string("VANDNPD"), 0x155, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 55 /r - VANDNPD ymm, vex256, ymm/m256
    { const_string("VANDNPD"), 0x155, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 55 /r - VANDNPD ymm, vex256, ymm/m256
    { const_string("VANDNPS"), 0x155, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 55 /r - VANDNPS xmm, vex128, xmm/m128
    { const_string("VANDNPS"), 0x155, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 55 /r - VANDNPS xmm, vex128, xmm/m128
    { const_string("VANDNPS"), 0x155, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 55 /r - VANDNPS ymm, vex256, ymm/m256
    { const_string("VANDNPS"), 0x155, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 55 /r - VANDNPS ymm, vex256, ymm/m256
    { const_string("VORPD"), 0x156, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 56 /r - VORPD xmm, vex128, xmm/m128
    { const_string("VORPD"), 0x156, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 56 /r - VORPD xmm, vex128, xmm/m128
    { const_string("VORPD"), 0x156, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 56 /r - VORPD ymm, vex256, ymm/m256
    { const_string("VORPD"), 0x156, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 56 /r - VORPD ymm, vex256, ymm/m256
    { const_string("VORPS"), 0x156, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 56 /r - VORPS xmm, vex128, xmm/m128
    { const_string("VORPS"), 0x156, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 56 /r - VORPS xmm, vex128, xmm/m128
    { const_string("VORPS"), 0x156, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 56 /r - VORPS ymm, vex256, ymm/m256
    { const_string("VORPS"), 0x156, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 56 /r - VORPS ymm, vex256, ymm/m256
    { const_string("VXORPD"), 0x157, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 57 /r - VXORPD xmm, vex128, xmm/m128
    { const_string("VXORPD"), 0x157, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 57 /r - VXORPD xmm, vex128, xmm/m128
    { const_string("VXORPD"), 0x157, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 57 /r - VXORPD ymm, vex256, ymm/m256
    { const_string("VXORPD"), 0x157, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 57 /r - VXORPD ymm, vex256, ymm/m256
    { const_string("VXORPS"), 0x157, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 57 /r - VXORPS xmm, vex128, xmm/m128
    { const_string("VXORPS"), 0x157, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 57 /r - VXORPS xmm, vex128, xmm/m128
    { const_string("VXORPS"), 0x157, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 57 /r - VXORPS ymm, vex256, ymm/m256
    { const_string("VXORPS"), 0x157, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 57 /r - VXORPS ymm, vex256, ymm/m256
    { const_string("VADDSS"), 0x158, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 58 /r - VADDSS xmm, vex128, xmm/m32
    { const_string("VADDSS"), 0x158, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 58 /r - VADDSS xmm, vex128, xmm/m32
    { const_string("VADDSS"), 0x158, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 58 /r - VADDSS xmm, vex128, xmm/m32
    { const_string("VADDSS"), 0x158, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 58 /r - VADDSS xmm, vex128, xmm/m32
    { const_string("VADDSD"), 0x158, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 58 /r - VADDSD xmm, vex128, xmm/m64
    { const_string("VADDSD"), 0x158, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 58 /r - VADDSD xmm, vex128, xmm/m64
    { const_string("VADDSD"), 0x158, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 58 /r - VADDSD xmm, vex128, xmm/m64
    { const_string("VADDSD"), 0x158, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 58 /r - VADDSD xmm, vex128, xmm/m64
    { const_string("VADDPD"), 0x158, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 58 /r - VADDPD xmm, vex128, xmm/m128
    { const_string("VADDPD"), 0x158, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 58 /r - VADDPD xmm, vex128, xmm/m128
    { const_string("VADDPD"), 0x158, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 58 /r - VADDPD ymm, vex256, ymm/m256
    { const_string("VADDPD"), 0x158, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 58 /r - VADDPD ymm, vex256, ymm/m256
    { const_string("VADDPS"), 0x158, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 58 /r - VADDPS xmm, vex128, xmm/m128
    { const_string("VADDPS"), 0x158, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 58 /r - VADDPS xmm, vex128, xmm/m128
    { const_string("VADDPS"), 0x158, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 58 /r - VADDPS ymm, vex256, ymm/m256
    { const_string("VADDPS"), 0x158, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 58 /r - VADDPS ymm, vex256, ymm/m256
    { const_string("VMULSS"), 0x159, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 59 /r - VMULSS xmm, vex128, xmm/m32
    { const_string("VMULSS"), 0x159, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 59 /r - VMULSS xmm, vex128, xmm/m32
    { const_string("VMULSS"), 0x159, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 59 /r - VMULSS xmm, vex128, xmm/m32
    { const_string("VMULSS"), 0x159, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 59 /r - VMULSS xmm, vex128, xmm/m32
    { const_string("VMULSD"), 0x159, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 59 /r - VMULSD xmm, vex128, xmm/m64
    { const_string("VMULSD"), 0x159, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 59 /r - VMULSD xmm, vex128, xmm/m64
    { const_string("VMULSD"), 0x159, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 59 /r - VMULSD xmm, vex128, xmm/m64
    { const_string("VMULSD"), 0x159, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 59 /r - VMULSD xmm, vex128, xmm/m64
    { const_string("VMULPD"), 0x159, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 59 /r - VMULPD xmm, vex128, xmm/m128
    { const_string("VMULPD"), 0x159, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 59 /r - VMULPD xmm, vex128, xmm/m128
    { const_string("VMULPD"), 0x159, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 59 /r - VMULPD ymm, vex256, ymm/m256
    { const_string("VMULPD"), 0x159, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 59 /r - VMULPD ymm, vex256, ymm/m256
    { const_string("VMULPS"), 0x159, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 59 /r - VMULPS xmm, vex128, xmm/m128
    { const_string("VMULPS"), 0x159, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 59 /r - VMULPS xmm, vex128, xmm/m128
    { const_string("VMULPS"), 0x159, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 59 /r - VMULPS ymm, vex256, ymm/m256
    { const_string("VMULPS"), 0x159, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 59 /r - VMULPS ymm, vex256, ymm/m256
    { const_string("VCVTSS2SD"), 0x15a, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 5a /r - VCVTSS2SD xmm, vex128, xmm/m32
    { const_string("VCVTSS2SD"), 0x15a, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 5a /r - VCVTSS2SD xmm, vex128, xmm/m32
    { const_string("VCVTSS2SD"), 0x15a, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 5a /r - VCVTSS2SD xmm, vex128, xmm/m32
    { const_string("VCVTSS2SD"), 0x15a, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 5a /r - VCVTSS2SD xmm, vex128, xmm/m32
    { const_string("VCVTSD2SS"), 0x15a, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 5a /r - VCVTSD2SS xmm, vex128, xmm/m64
    { const_string("VCVTSD2SS"), 0x15a, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 5a /r - VCVTSD2SS xmm, vex128, xmm/m64
    { const_string("VCVTSD2SS"), 0x15a, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 5a /r - VCVTSD2SS xmm, vex128, xmm/m64
    { const_string("VCVTSD2SS"), 0x15a, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 5a /r - VCVTSD2SS xmm, vex128, xmm/m64
    { const_string("VCVTPD2PS"), 0x15a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 5a /r - VCVTPD2PS xmm, xmm/m128
    { const_string("VCVTPD2PS"), 0x15a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 5a /r - VCVTPD2PS xmm, xmm/m128
    { const_string("VCVTPD2PS"), 0x15a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 5a /r - VCVTPD2PS xmm, ymm/m256
    { const_string("VCVTPD2PS"), 0x15a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 5a /r - VCVTPD2PS xmm, ymm/m256
    { const_string("VCVTPS2PD"), 0x15a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 5a /r - VCVTPS2PD xmm, xmm/m64
    { const_string("VCVTPS2PD"), 0x15a, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 5a /r - VCVTPS2PD xmm, xmm/m64
    { const_string("VCVTPS2PD"), 0x15a, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 5a /r - VCVTPS2PD ymm, xmm/m128
    { const_string("VCVTPS2PD"), 0x15a, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 5a /r - VCVTPS2PD ymm, xmm/m128
    { const_string("VCVTTPS2DQ"), 0x15b, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 5b /r - VCVTTPS2DQ xmm, xmm/m128
    { const_string("VCVTTPS2DQ"), 0x15b, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 5b /r - VCVTTPS2DQ xmm, xmm/m128
    { const_string("VCVTTPS2DQ"), 0x15b, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 5b /r - VCVTTPS2DQ ymm, ymm/m256
    { const_string("VCVTTPS2DQ"), 0x15b, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 5b /r - VCVTTPS2DQ ymm, ymm/m256
    { const_string("VCVTPS2DQ"), 0x15b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 5b /r - VCVTPS2DQ xmm, xmm/m128
    { const_string("VCVTPS2DQ"), 0x15b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 5b /r - VCVTPS2DQ xmm, xmm/m128
    { const_string("VCVTPS2DQ"), 0x15b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 5b /r - VCVTPS2DQ ymm, ymm/m256
    { const_string("VCVTPS2DQ"), 0x15b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 5b /r - VCVTPS2DQ ymm, ymm/m256
    { const_string("VCVTDQ2PS"), 0x15b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 5b /r - VCVTDQ2PS xmm, xmm/m128
    { const_string("VCVTDQ2PS"), 0x15b, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 5b /r - VCVTDQ2PS xmm, xmm/m128
    { const_string("VCVTDQ2PS"), 0x15b, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 5b /r - VCVTDQ2PS ymm, ymm/m256
    { const_string("VCVTDQ2PS"), 0x15b, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 5b /r - VCVTDQ2PS ymm, ymm/m256
    { const_string("VSUBSS"), 0x15c, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 5c /r - VSUBSS xmm, vex128, xmm/m32
    { const_string("VSUBSS"), 0x15c, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 5c /r - VSUBSS xmm, vex128, xmm/m32
    { const_string("VSUBSS"), 0x15c, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 5c /r - VSUBSS xmm, vex128, xmm/m32
    { const_string("VSUBSS"), 0x15c, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 5c /r - VSUBSS xmm, vex128, xmm/m32
    { const_string("VSUBSD"), 0x15c, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 5c /r - VSUBSD xmm, vex128, xmm/m64
    { const_string("VSUBSD"), 0x15c, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 5c /r - VSUBSD xmm, vex128, xmm/m64
    { const_string("VSUBSD"), 0x15c, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 5c /r - VSUBSD xmm, vex128, xmm/m64
    { const_string("VSUBSD"), 0x15c, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 5c /r - VSUBSD xmm, vex128, xmm/m64
    { const_string("VSUBPD"), 0x15c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 5c /r - VSUBPD xmm, vex128, xmm/m128
    { const_string("VSUBPD"), 0x15c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 5c /r - VSUBPD xmm, vex128, xmm/m128
    { const_string("VSUBPD"), 0x15c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 5c /r - VSUBPD ymm, vex256, ymm/m256
    { const_string("VSUBPD"), 0x15c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 5c /r - VSUBPD ymm, vex256, ymm/m256
    { const_string("VSUBPS"), 0x15c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 5c /r - VSUBPS xmm, vex128, xmm/m128
    { const_string("VSUBPS"), 0x15c, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 5c /r - VSUBPS xmm, vex128, xmm/m128
    { const_string("VSUBPS"), 0x15c, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 5c /r - VSUBPS ymm, vex256, ymm/m256
    { const_string("VSUBPS"), 0x15c, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 5c /r - VSUBPS ymm, vex256, ymm/m256
    { const_string("VMINSS"), 0x15d, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 5d /r - VMINSS xmm, vex128, xmm/m32
    { const_string("VMINSS"), 0x15d, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 5d /r - VMINSS xmm, vex128, xmm/m32
    { const_string("VMINSS"), 0x15d, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 5d /r - VMINSS xmm, vex128, xmm/m32
    { const_string("VMINSS"), 0x15d, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 5d /r - VMINSS xmm, vex128, xmm/m32
    { const_string("VMINSD"), 0x15d, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 5d /r - VMINSD xmm, vex128, xmm/m64
    { const_string("VMINSD"), 0x15d, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 5d /r - VMINSD xmm, vex128, xmm/m64
    { const_string("VMINSD"), 0x15d, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 5d /r - VMINSD xmm, vex128, xmm/m64
    { const_string("VMINSD"), 0x15d, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 5d /r - VMINSD xmm, vex128, xmm/m64
    { const_string("VMINPD"), 0x15d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 5d /r - VMINPD xmm, vex128, xmm/m128
    { const_string("VMINPD"), 0x15d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 5d /r - VMINPD xmm, vex128, xmm/m128
    { const_string("VMINPD"), 0x15d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 5d /r - VMINPD ymm, vex256, ymm/m256
    { const_string("VMINPD"), 0x15d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 5d /r - VMINPD ymm, vex256, ymm/m256
    { const_string("VMINPS"), 0x15d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 5d /r - VMINPS xmm, vex128, xmm/m128
    { const_string("VMINPS"), 0x15d, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 5d /r - VMINPS xmm, vex128, xmm/m128
    { const_string("VMINPS"), 0x15d, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 5d /r - VMINPS ymm, vex256, ymm/m256
    { const_string("VMINPS"), 0x15d, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 5d /r - VMINPS ymm, vex256, ymm/m256
    { const_string("VDIVSS"), 0x15e, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 5e /r - VDIVSS xmm, vex128, xmm/m32
    { const_string("VDIVSS"), 0x15e, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 5e /r - VDIVSS xmm, vex128, xmm/m32
    { const_string("VDIVSS"), 0x15e, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 5e /r - VDIVSS xmm, vex128, xmm/m32
    { const_string("VDIVSS"), 0x15e, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 5e /r - VDIVSS xmm, vex128, xmm/m32
    { const_string("VDIVSD"), 0x15e, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 5e /r - VDIVSD xmm, vex128, xmm/m64
    { const_string("VDIVSD"), 0x15e, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 5e /r - VDIVSD xmm, vex128, xmm/m64
    { const_string("VDIVSD"), 0x15e, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 5e /r - VDIVSD xmm, vex128, xmm/m64
    { const_string("VDIVSD"), 0x15e, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 5e /r - VDIVSD xmm, vex128, xmm/m64
    { const_string("VDIVPD"), 0x15e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 5e /r - VDIVPD xmm, vex128, xmm/m128
    { const_string("VDIVPD"), 0x15e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 5e /r - VDIVPD xmm, vex128, xmm/m128
    { const_string("VDIVPD"), 0x15e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 5e /r - VDIVPD ymm, vex256, ymm/m256
    { const_string("VDIVPD"), 0x15e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 5e /r - VDIVPD ymm, vex256, ymm/m256
    { const_string("VDIVPS"), 0x15e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 5e /r - VDIVPS xmm, vex128, xmm/m128
    { const_string("VDIVPS"), 0x15e, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 5e /r - VDIVPS xmm, vex128, xmm/m128
    { const_string("VDIVPS"), 0x15e, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 5e /r - VDIVPS ymm, vex256, ymm/m256
    { const_string("VDIVPS"), 0x15e, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 5e /r - VDIVPS ymm, vex256, ymm/m256
    { const_string("VMAXSS"), 0x15f, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 5f /r - VMAXSS xmm, vex128, xmm/m32
    { const_string("VMAXSS"), 0x15f, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 5f /r - VMAXSS xmm, vex128, xmm/m32
    { const_string("VMAXSS"), 0x15f, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 5f /r - VMAXSS xmm, vex128, xmm/m32
    { const_string("VMAXSS"), 0x15f, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 5f /r - VMAXSS xmm, vex128, xmm/m32
    { const_string("VMAXSD"), 0x15f, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 5f /r - VMAXSD xmm, vex128, xmm/m64
    { const_string("VMAXSD"), 0x15f, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 5f /r - VMAXSD xmm, vex128, xmm/m64
    { const_string("VMAXSD"), 0x15f, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 5f /r - VMAXSD xmm, vex128, xmm/m64
    { const_string("VMAXSD"), 0x15f, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 5f /r - VMAXSD xmm, vex128, xmm/m64
    { const_string("VMAXPD"), 0x15f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 5f /r - VMAXPD xmm, vex128, xmm/m128
    { const_string("VMAXPD"), 0x15f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 5f /r - VMAXPD xmm, vex128, xmm/m128
    { const_string("VMAXPD"), 0x15f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 5f /r - VMAXPD ymm, vex256, ymm/m256
    { const_string("VMAXPD"), 0x15f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 5f /r - VMAXPD ymm, vex256, ymm/m256
    { const_string("VMAXPS"), 0x15f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 5f /r - VMAXPS xmm, vex128, xmm/m128
    { const_string("VMAXPS"), 0x15f, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 5f /r - VMAXPS xmm, vex128, xmm/m128
    { const_string("VMAXPS"), 0x15f, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W0 5f /r - VMAXPS ymm, vex256, ymm/m256
    { const_string("VMAXPS"), 0x15f, -1, 0, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.0F.W1 5f /r - VMAXPS ymm, vex256, ymm/m256
    { const_string("VPUNPCKLBW"), 0x160, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 60 /r - VPUNPCKLBW xmm, vex128, xmm/m128
    { const_string("VPUNPCKLBW"), 0x160, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 60 /r - VPUNPCKLBW xmm, vex128, xmm/m128
    { const_string("VPUNPCKLBW"), 0x160, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 60 /r - VPUNPCKLBW ymm, vex256, ymm/m256
    { const_string("VPUNPCKLBW"), 0x160, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 60 /r - VPUNPCKLBW ymm, vex256, ymm/m256
    { const_string("VPUNPCKLWD"), 0x161, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 61 /r - VPUNPCKLWD xmm, vex128, xmm/m128
    { const_string("VPUNPCKLWD"), 0x161, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 61 /r - VPUNPCKLWD xmm, vex128, xmm/m128
    { const_string("VPUNPCKLWD"), 0x161, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 61 /r - VPUNPCKLWD ymm, vex256, ymm/m256
    { const_string("VPUNPCKLWD"), 0x161, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 61 /r - VPUNPCKLWD ymm, vex256, ymm/m256
    { const_string("VPUNPCKLDQ"), 0x162, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 62 /r - VPUNPCKLDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKLDQ"), 0x162, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 62 /r - VPUNPCKLDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKLDQ"), 0x162, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 62 /r - VPUNPCKLDQ ymm, vex256, ymm/m256
    { const_string("VPUNPCKLDQ"), 0x162, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 62 /r - VPUNPCKLDQ ymm, vex256, ymm/m256
    { const_string("VPACKSSWB"), 0x163, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 63 /r - VPACKSSWB xmm, vex128, xmm/m128
    { const_string("VPACKSSWB"), 0x163, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 63 /r - VPACKSSWB xmm, vex128, xmm/m128
    { const_string("VPACKSSWB"), 0x163, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 63 /r - VPACKSSWB ymm, vex256, ymm/m256
    { const_string("VPACKSSWB"), 0x163, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 63 /r - VPACKSSWB ymm, vex256, ymm/m256
    { const_string("VPCMPGTB"), 0x164, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 64 /r - VPCMPGTB xmm, vex128, xmm/m128
    { const_string("VPCMPGTB"), 0x164, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 64 /r - VPCMPGTB xmm, vex128, xmm/m128
    { const_string("VPCMPGTB"), 0x164, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 64 /r - VPCMPGTB ymm, vex256, ymm/m256
    { const_string("VPCMPGTB"), 0x164, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 64 /r - VPCMPGTB ymm, vex256, ymm/m256
    { const_string("VPCMPGTW"), 0x165, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 65 /r - VPCMPGTW xmm, vex128, xmm/m128
    { const_string("VPCMPGTW"), 0x165, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 65 /r - VPCMPGTW xmm, vex128, xmm/m128
    { const_string("VPCMPGTW"), 0x165, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 65 /r - VPCMPGTW ymm, vex256, ymm/m256
    { const_string("VPCMPGTW"), 0x165, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 65 /r - VPCMPGTW ymm, vex256, ymm/m256
    { const_string("VPCMPGTD"), 0x166, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 66 /r - VPCMPGTD xmm, vex128, xmm/m128
    { const_string("VPCMPGTD"), 0x166, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 66 /r - VPCMPGTD xmm, vex128, xmm/m128
    { const_string("VPCMPGTD"), 0x166, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 66 /r - VPCMPGTD ymm, vex256, ymm/m256
    { const_string("VPCMPGTD"), 0x166, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 66 /r - VPCMPGTD ymm, vex256, ymm/m256
    { const_string("VPACKUSWB"), 0x167, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 67 /r - VPACKUSWB xmm, vex128, xmm/m128
    { const_string("VPACKUSWB"), 0x167, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 67 /r - VPACKUSWB xmm, vex128, xmm/m128
    { const_string("VPACKUSWB"), 0x167, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 67 /r - VPACKUSWB ymm, vex256, ymm/m256
    { const_string("VPACKUSWB"), 0x167, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 67 /r - VPACKUSWB ymm, vex256, ymm/m256
    { const_string("VPUNPCKHBW"), 0x168, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 68 /r - VPUNPCKHBW xmm, vex128, xmm/m128
    { const_string("VPUNPCKHBW"), 0x168, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 68 /r - VPUNPCKHBW xmm, vex128, xmm/m128
    { const_string("VPUNPCKHBW"), 0x168, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 68 /r - VPUNPCKHBW ymm, vex256, ymm/m256
    { const_string("VPUNPCKHBW"), 0x168, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 68 /r - VPUNPCKHBW ymm, vex256, ymm/m256
    { const_string("VPUNPCKHWD"), 0x169, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 69 /r - VPUNPCKHWD xmm, vex128, xmm/m128
    { const_string("VPUNPCKHWD"), 0x169, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 69 /r - VPUNPCKHWD xmm, vex128, xmm/m128
    { const_string("VPUNPCKHWD"), 0x169, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 69 /r - VPUNPCKHWD ymm, vex256, ymm/m256
    { const_string("VPUNPCKHWD"), 0x169, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 69 /r - VPUNPCKHWD ymm, vex256, ymm/m256
    { const_string("VPUNPCKHDQ"), 0x16a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 6a /r - VPUNPCKHDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKHDQ"), 0x16a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 6a /r - VPUNPCKHDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKHDQ"), 0x16a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 6a /r - VPUNPCKHDQ ymm, vex256, ymm/m256
    { const_string("VPUNPCKHDQ"), 0x16a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 6a /r - VPUNPCKHDQ ymm, vex256, ymm/m256
    { const_string("VPACKSSDW"), 0x16b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 6b /r - VPACKSSDW xmm, vex128, xmm/m128
    { const_string("VPACKSSDW"), 0x16b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 6b /r - VPACKSSDW xmm, vex128, xmm/m128
    { const_string("VPACKSSDW"), 0x16b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 6b /r - VPACKSSDW ymm, vex256, ymm/m256
    { const_string("VPACKSSDW"), 0x16b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 6b /r - VPACKSSDW ymm, vex256, ymm/m256
    { const_string("VPUNPCKLQDQ"), 0x16c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 6c /r - VPUNPCKLQDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKLQDQ"), 0x16c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 6c /r - VPUNPCKLQDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKLQDQ"), 0x16c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 6c /r - VPUNPCKLQDQ ymm, vex256, ymm/m256
    { const_string("VPUNPCKLQDQ"), 0x16c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 6c /r - VPUNPCKLQDQ ymm, vex256, ymm/m256
    { const_string("VPUNPCKHQDQ"), 0x16d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 6d /r - VPUNPCKHQDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKHQDQ"), 0x16d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 6d /r - VPUNPCKHQDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKHQDQ"), 0x16d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 6d /r - VPUNPCKHQDQ ymm, vex256, ymm/m256
    { const_string("VPUNPCKHQDQ"), 0x16d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 6d /r - VPUNPCKHQDQ ymm, vex256, ymm/m256
    { const_string("VMOVD"), 0x16e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 6e /r - VMOVD xmm, r/m32
    { const_string("VMOVQ"), 0x16e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 6e /r - VMOVQ xmm, r/m64
    { const_string("VMOVDQU"), 0x16f, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 6f /r - VMOVDQU xmm, xmm/m128
    { const_string("VMOVDQU"), 0x16f, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 6f /r - VMOVDQU xmm, xmm/m128
    { const_string("VMOVDQU"), 0x16f, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 6f /r - VMOVDQU ymm, ymm/m256
    { const_string("VMOVDQU"), 0x16f, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 6f /r - VMOVDQU ymm, ymm/m256
    { const_string("VMOVDQA"), 0x16f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 6f /r - VMOVDQA xmm, xmm/m128
    { const_string("VMOVDQA"), 0x16f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 6f /r - VMOVDQA xmm, xmm/m128
    { const_string("VMOVDQA"), 0x16f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 6f /r - VMOVDQA ymm, ymm/m256
    { const_string("VMOVDQA"), 0x16f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 6f /r - VMOVDQA ymm, ymm/m256
    { const_string("VPSHUFHW"), 0x170, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.F3.0F.W0 70 ib /r - VPSHUFHW xmm, xmm/m128, imm8
    { const_string("VPSHUFHW"), 0x170, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.F3.0F.W1 70 ib /r - VPSHUFHW xmm, xmm/m128, imm8
    { const_string("VPSHUFHW"), 0x170, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.F3.0F.W0 70 ib /r - VPSHUFHW ymm, ymm/m256, imm8
    { const_string("VPSHUFHW"), 0x170, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.F3.0F.W1 70 ib /r - VPSHUFHW ymm, ymm/m256, imm8
    { const_string("VPSHUFLW"), 0x170, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.F2.0F.W0 70 ib /r - VPSHUFLW xmm, xmm/m128, imm8
    { const_string("VPSHUFLW"), 0x170, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.F2.0F.W1 70 ib /r - VPSHUFLW xmm, xmm/m128, imm8
    { const_string("VPSHUFLW"), 0x170, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.F2.0F.W0 70 ib /r - VPSHUFLW ymm, ymm/m256, imm8
    { const_string("VPSHUFLW"), 0x170, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.F2.0F.W1 70 ib /r - VPSHUFLW ymm, ymm/m256, imm8
    { const_string("VPSHUFD"), 0x170, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 70 ib /r - VPSHUFD xmm, xmm/m128, imm8
    { const_string("VPSHUFD"), 0x170, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 70 ib /r - VPSHUFD xmm, xmm/m128, imm8
    { const_string("VPSHUFD"), 0x170, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 70 ib /r - VPSHUFD ymm, ymm/m256, imm8
    { const_string("VPSHUFD"), 0x170, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 70 ib /r - VPSHUFD ymm, ymm/m256, imm8
    { const_string("VPSRLW"), 0x171, -1, 0, 0, 1, 0, 0, 2, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 71 /2 ib - VPSRLW vex128, xmm/m128, imm8
    { const_string("VPSRLW"), 0x171, -1, 0, 0, 1, 1, 0, 2, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 71 /2 ib - VPSRLW vex128, xmm/m128, imm8
    { const_string("VPSRLW"), 0x171, -1, 0, 0, 1, 0, 0, 2, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 71 /2 ib - VPSRLW vex256, ymm/m256, imm8
    { const_string("VPSRLW"), 0x171, -1, 0, 0, 1, 1, 0, 2, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 71 /2 ib - VPSRLW vex256, ymm/m256, imm8
    { const_string("VPSRAW"), 0x171, -1, 0, 0, 1, 0, 0, 4, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 71 /4 ib - VPSRAW vex128, xmm/m128, imm8
    { const_string("VPSRAW"), 0x171, -1, 0, 0, 1, 1, 0, 4, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 71 /4 ib - VPSRAW vex128, xmm/m128, imm8
    { const_string("VPSRAW"), 0x171, -1, 0, 0, 1, 0, 0, 4, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 71 /4 ib - VPSRAW vex256, ymm/m256, imm8
    { const_string("VPSRAW"), 0x171, -1, 0, 0, 1, 1, 0, 4, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 71 /4 ib - VPSRAW vex256, ymm/m256, imm8
    { const_string("VPSLLW"), 0x171, -1, 0, 0, 1, 0, 0, 6, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 71 /6 ib - VPSLLW vex128, xmm/m128, imm8
    { const_string("VPSLLW"), 0x171, -1, 0, 0, 1, 1, 0, 6, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 71 /6 ib - VPSLLW vex128, xmm/m128, imm8
    { const_string("VPSLLW"), 0x171, -1, 0, 0, 1, 0, 0, 6, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 71 /6 ib - VPSLLW vex256, ymm/m256, imm8
    { const_string("VPSLLW"), 0x171, -1, 0, 0, 1, 1, 0, 6, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 71 /6 ib - VPSLLW vex256, ymm/m256, imm8
    { const_string("VPSRLD"), 0x172, -1, 0, 0, 1, 0, 0, 2, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 72 /2 ib - VPSRLD vex128, xmm/m128, imm8
    { const_string("VPSRLD"), 0x172, -1, 0, 0, 1, 1, 0, 2, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 72 /2 ib - VPSRLD vex128, xmm/m128, imm8
    { const_string("VPSRLD"), 0x172, -1, 0, 0, 1, 0, 0, 2, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 72 /2 ib - VPSRLD vex256, ymm/m256, imm8
    { const_string("VPSRLD"), 0x172, -1, 0, 0, 1, 1, 0, 2, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 72 /2 ib - VPSRLD vex256, ymm/m256, imm8
    { const_string("VPSRAD"), 0x172, -1, 0, 0, 1, 0, 0, 4, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 72 /4 ib - VPSRAD vex128, xmm/m128, imm8
    { const_string("VPSRAD"), 0x172, -1, 0, 0, 1, 1, 0, 4, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 72 /4 ib - VPSRAD vex128, xmm/m128, imm8
    { const_string("VPSRAD"), 0x172, -1, 0, 0, 1, 0, 0, 4, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 72 /4 ib - VPSRAD vex256, ymm/m256, imm8
    { const_string("VPSRAD"), 0x172, -1, 0, 0, 1, 1, 0, 4, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 72 /4 ib - VPSRAD vex256, ymm/m256, imm8
    { const_string("VPSLLD"), 0x172, -1, 0, 0, 1, 0, 0, 6, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 72 /6 ib - VPSLLD vex128, xmm/m128, imm8
    { const_string("VPSLLD"), 0x172, -1, 0, 0, 1, 1, 0, 6, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 72 /6 ib - VPSLLD vex128, xmm/m128, imm8
    { const_string("VPSLLD"), 0x172, -1, 0, 0, 1, 0, 0, 6, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 72 /6 ib - VPSLLD vex256, ymm/m256, imm8
    { const_string("VPSLLD"), 0x172, -1, 0, 0, 1, 1, 0, 6, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 72 /6 ib - VPSLLD vex256, ymm/m256, imm8
    { const_string("VPSRLQ"), 0x173, -1, 0, 0, 1, 0, 0, 2, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 73 /2 ib - VPSRLQ vex128, xmm/m128, imm8
    { const_string("VPSRLQ"), 0x173, -1, 0, 0, 1, 1, 0, 2, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 73 /2 ib - VPSRLQ vex128, xmm/m128, imm8
    { const_string("VPSRLQ"), 0x173, -1, 0, 0, 1, 0, 0, 2, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 73 /2 ib - VPSRLQ vex256, ymm/m256, imm8
    { const_string("VPSRLQ"), 0x173, -1, 0, 0, 1, 1, 0, 2, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 73 /2 ib - VPSRLQ vex256, ymm/m256, imm8
    { const_string("VPSRLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 3, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 73 /3 ib - VPSRLDQ vex128, xmm/m128, imm8
    { const_string("VPSRLDQ"), 0x173, -1, 0, 0, 1, 1, 0, 3, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 73 /3 ib - VPSRLDQ vex128, xmm/m128, imm8
    { const_string("VPSRLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 3, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 73 /3 ib - VPSRLDQ vex256, ymm/m256, imm8
    { const_string("VPSRLDQ"), 0x173, -1, 0, 0, 1, 1, 0, 3, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 73 /3 ib - VPSRLDQ vex256, ymm/m256, imm8
    { const_string("VPSLLQ"), 0x173, -1, 0, 0, 1, 0, 0, 6, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 73 /6 ib - VPSLLQ vex128, xmm/m128, imm8
    { const_string("VPSLLQ"), 0x173, -1, 0, 0, 1, 1, 0, 6, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 73 /6 ib - VPSLLQ vex128, xmm/m128, imm8
    { const_string("VPSLLQ"), 0x173, -1, 0, 0, 1, 0, 0, 6, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 73 /6 ib - VPSLLQ vex256, ymm/m256, imm8
    { const_string("VPSLLQ"), 0x173, -1, 0, 0, 1, 1, 0, 6, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 73 /6 ib - VPSLLQ vex256, ymm/m256, imm8
    { const_string("VPSLLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 7, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 73 /7 ib - VPSLLDQ vex128, xmm/m128, imm8
    { const_string("VPSLLDQ"), 0x173, -1, 0, 0, 1, 1, 0, 7, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 73 /7 ib - VPSLLDQ vex128, xmm/m128, imm8
    { const_string("VPSLLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 7, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 73 /7 ib - VPSLLDQ vex256, ymm/m256, imm8
    { const_string("VPSLLDQ"), 0x173, -1, 0, 0, 1, 1, 0, 7, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 73 /7 ib - VPSLLDQ vex256, ymm/m256, imm8
    { const_string("VPCMPEQB"), 0x174, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 74 /r - VPCMPEQB xmm, vex128, xmm/m128
    { const_string("VPCMPEQB"), 0x174, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 74 /r - VPCMPEQB xmm, vex128, xmm/m128
    { const_string("VPCMPEQB"), 0x174, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 74 /r - VPCMPEQB ymm, vex256, ymm/m256
    { const_string("VPCMPEQB"), 0x174, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 74 /r - VPCMPEQB ymm, vex256, ymm/m256
    { const_string("VPCMPEQW"), 0x175, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 75 /r - VPCMPEQW xmm, vex128, xmm/m128
    { const_string("VPCMPEQW"), 0x175, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 75 /r - VPCMPEQW xmm, vex128, xmm/m128
    { const_string("VPCMPEQW"), 0x175, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 75 /r - VPCMPEQW ymm, vex256, ymm/m256
    { const_string("VPCMPEQW"), 0x175, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 75 /r - VPCMPEQW ymm, vex256, ymm/m256
    { const_string("VPCMPEQD"), 0x176, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 76 /r - VPCMPEQD xmm, vex128, xmm/m128
    { const_string("VPCMPEQD"), 0x176, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 76 /r - VPCMPEQD xmm, vex128, xmm/m128
    { const_string("VPCMPEQD"), 0x176, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 76 /r - VPCMPEQD ymm, vex256, ymm/m256
    { const_string("VPCMPEQD"), 0x176, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 76 /r - VPCMPEQD ymm, vex256, ymm/m256
    { const_string("VZEROUPPER"), 0x177, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0,  }, // VEX.128.0F.W0 77 - VZEROUPPER 
    { const_string("VZEROUPPER"), 0x177, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0,  }, // VEX.128.0F.W1 77 - VZEROUPPER 
    { const_string("VZEROALL"), 0x177, -1, 0, 0, 0, 0, 0, -1, 0, 1, 0,  }, // VEX.256.0F.W0 77 - VZEROALL 
    { const_string("VZEROALL"), 0x177, -1, 0, 0, 0, 1, 0, -1, 0, 1, 0,  }, // VEX.256.0F.W1 77 - VZEROALL 
    { const_string("VHADDPS"), 0x17c, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 7c /r - VHADDPS xmm, vex128, xmm/m128
    { const_string("VHADDPS"), 0x17c, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 7c /r - VHADDPS xmm, vex128, xmm/m128
    { const_string("VHADDPS"), 0x17c, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 7c /r - VHADDPS ymm, vex256, ymm/m256
    { const_string("VHADDPS"), 0x17c, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 7c /r - VHADDPS ymm, vex256, ymm/m256
    { const_string("VHADDPD"), 0x17c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 7c /r - VHADDPD xmm, vex128, xmm/m128
    { const_string("VHADDPD"), 0x17c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 7c /r - VHADDPD xmm, vex128, xmm/m128
    { const_string("VHADDPD"), 0x17c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 7c /r - VHADDPD ymm, vex256, ymm/m256
    { const_string("VHADDPD"), 0x17c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 7c /r - VHADDPD ymm, vex256, ymm/m256
    { const_string("VHSUBPS"), 0x17d, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 7d /r - VHSUBPS xmm, vex128, xmm/m128
    { const_string("VHSUBPS"), 0x17d, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 7d /r - VHSUBPS xmm, vex128, xmm/m128
    { const_string("VHSUBPS"), 0x17d, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 7d /r - VHSUBPS ymm, vex256, ymm/m256
    { const_string("VHSUBPS"), 0x17d, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 7d /r - VHSUBPS ymm, vex256, ymm/m256
    { const_string("VHSUBPD"), 0x17d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 7d /r - VHSUBPD xmm, vex128, xmm/m128
    { const_string("VHSUBPD"), 0x17d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 7d /r - VHSUBPD xmm, vex128, xmm/m128
    { const_string("VHSUBPD"), 0x17d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 7d /r - VHSUBPD ymm, vex256, ymm/m256
    { const_string("VHSUBPD"), 0x17d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 7d /r - VHSUBPD ymm, vex256, ymm/m256
    { const_string("VMOVQ"), 0x17e, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 7e /r - VMOVQ xmm, xmm/m64
    { const_string("VMOVQ"), 0x17e, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 7e /r - VMOVQ xmm, xmm/m64
    { const_string("VMOVD"), 0x17e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 7e /r - VMOVD r/m32, xmm
    { const_string("VMOVQ"), 0x17e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 7e /r - VMOVQ r/m64, xmm
    { const_string("VMOVDQU"), 0x17f, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 7f /r - VMOVDQU xmm/m128, xmm
    { const_string("VMOVDQU"), 0x17f, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 7f /r - VMOVDQU xmm/m128, xmm
    { const_string("VMOVDQU"), 0x17f, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 7f /r - VMOVDQU ymm/m256, ymm
    { const_string("VMOVDQU"), 0x17f, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 7f /r - VMOVDQU ymm/m256, ymm
    { const_string("VMOVDQA"), 0x17f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 7f /r - VMOVDQA xmm/m128, xmm
    { const_string("VMOVDQA"), 0x17f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 7f /r - VMOVDQA xmm/m128, xmm
    { const_string("VMOVDQA"), 0x17f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 7f /r - VMOVDQA ymm/m256, ymm
    { const_string("VMOVDQA"), 0x17f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 7f /r - VMOVDQA ymm/m256, ymm
    { const_string("KMOVB"), 0x190, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km8, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 90 /r - KMOVB k, k/m8
    { const_string("KMOVD"), 0x190, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km32, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 90 /r - KMOVD k, k/m32
    { const_string("KMOVW"), 0x190, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km16, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 90 /r - KMOVW k, k/m16
    { const_string("KMOVQ"), 0x190, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 90 /r - KMOVQ k, k/m64
    { const_string("KMOVB"), 0x191, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m8, OPERAND_FLAG_write}, {OPERAND_k, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 91 /r - KMOVB m8, k
    { const_string("KMOVD"), 0x191, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_m32, OPERAND_FLAG_write}, {OPERAND_k, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 91 /r - KMOVD m32, k
    { const_string("KMOVW"), 0x191, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m16, OPERAND_FLAG_write}, {OPERAND_k, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 91 /r - KMOVW m16, k
    { const_string("KMOVQ"), 0x191, -1, 0, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_k, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 91 /r - KMOVQ m64, k
    { const_string("KMOVD"), 0x192, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 92 /r - KMOVD k, r/m32
    { const_string("KMOVQ"), 0x192, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 92 /r - KMOVQ k, r/m64
    { const_string("KMOVB"), 0x192, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 92 /r - KMOVB k, r/m32
    { const_string("KMOVW"), 0x192, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 92 /r - KMOVW k, r/m32
    { const_string("KMOVD"), 0x193, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 93 /r - KMOVD r32, k/m64
    { const_string("KMOVQ"), 0x193, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 93 /r - KMOVQ r64, k/m64
    { const_string("KMOVB"), 0x193, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 93 /r - KMOVB r32, k/m64
    { const_string("KMOVW"), 0x193, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 93 /r - KMOVW r32, k/m64
    { const_string("KORTESTB"), 0x198, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 98 /r - KORTESTB k, k/m64
    { const_string("KORTESTD"), 0x198, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 98 /r - KORTESTD k, k/m64
    { const_string("KORTESTW"), 0x198, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 98 /r - KORTESTW k, k/m64
    { const_string("KORTESTQ"), 0x198, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 98 /r - KORTESTQ k, k/m64
    { const_string("KTESTB"), 0x199, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 99 /r - KTESTB k, k/m64
    { const_string("KTESTD"), 0x199, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 99 /r - KTESTD k, k/m64
    { const_string("KTESTW"), 0x199, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 99 /r - KTESTW k, k/m64
    { const_string("KTESTQ"), 0x199, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_read}, {OPERAND_km64, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 99 /r - KTESTQ k, k/m64
    { const_string("VLDMXCSR"), 0x1ae, -1, 0, 0, 0, 0, 1, 2, 0, 0, 1, {{OPERAND_m32, OPERAND_FLAG_read}} }, // VEX.128.0F.W0 ae /2 - VLDMXCSR m32
    { const_string("VLDMXCSR"), 0x1ae, -1, 0, 0, 0, 1, 1, 2, 0, 0, 1, {{OPERAND_m32, OPERAND_FLAG_read}} }, // VEX.128.0F.W1 ae /2 - VLDMXCSR m32
    { const_string("VSTMXCSR"), 0x1ae, -1, 0, 0, 0, 0, 1, 3, 0, 0, 1, {{OPERAND_m32, OPERAND_FLAG_write}} }, // VEX.128.0F.W0 ae /3 - VSTMXCSR m32
    { const_string("VSTMXCSR"), 0x1ae, -1, 0, 0, 0, 1, 1, 3, 0, 0, 1, {{OPERAND_m32, OPERAND_FLAG_write}} }, // VEX.128.0F.W1 ae /3 - VSTMXCSR m32
    { const_string("VCMPSS"), 0x1c2, -1, 0, 1, 0, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.F3.0F.W0 c2 ib /r - VCMPSS xmm, vex128, xmm/m32, imm8
    { const_string("VCMPSS"), 0x1c2, -1, 0, 1, 0, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.F3.0F.W1 c2 ib /r - VCMPSS xmm, vex128, xmm/m32, imm8
    { const_string("VCMPSS"), 0x1c2, -1, 0, 1, 0, 0, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.F3.0F.W0 c2 ib /r - VCMPSS xmm, vex128, xmm/m32, imm8
    { const_string("VCMPSS"), 0x1c2, -1, 0, 1, 0, 1, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.F3.0F.W1 c2 ib /r - VCMPSS xmm, vex128, xmm/m32, imm8
    { const_string("VCMPSD"), 0x1c2, -1, 1, 0, 0, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.F2.0F.W0 c2 ib /r - VCMPSD xmm, vex128, xmm/m64, imm8
    { const_string("VCMPSD"), 0x1c2, -1, 1, 0, 0, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.F2.0F.W1 c2 ib /r - VCMPSD xmm, vex128, xmm/m64, imm8
    { const_string("VCMPSD"), 0x1c2, -1, 1, 0, 0, 0, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.F2.0F.W0 c2 ib /r - VCMPSD xmm, vex128, xmm/m64, imm8
    { const_string("VCMPSD"), 0x1c2, -1, 1, 0, 0, 1, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.F2.0F.W1 c2 ib /r - VCMPSD xmm, vex128, xmm/m64, imm8
    { const_string("VCMPPD"), 0x1c2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 c2 ib /r - VCMPPD xmm, vex128, xmm/m128, imm8
    { const_string("VCMPPD"), 0x1c2, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 c2 ib /r - VCMPPD xmm, vex128, xmm/m128, imm8
    { const_string("VCMPPD"), 0x1c2, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 c2 ib /r - VCMPPD ymm, vex256, ymm/m256, imm8
    { const_string("VCMPPD"), 0x1c2, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 c2 ib /r - VCMPPD ymm, vex256, ymm/m256, imm8
    { const_string("VCMPPS"), 0x1c2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.0F.W0 c2 ib /r - VCMPPS xmm, vex128, xmm/m128, imm8
    { const_string("VCMPPS"), 0x1c2, -1, 0, 0, 0, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.0F.W1 c2 ib /r - VCMPPS xmm, vex128, xmm/m128, imm8
    { const_string("VCMPPS"), 0x1c2, -1, 0, 0, 0, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.0F.W0 c2 ib /r - VCMPPS ymm, vex256, ymm/m256, imm8
    { const_string("VCMPPS"), 0x1c2, -1, 0, 0, 0, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.0F.W1 c2 ib /r - VCMPPS ymm, vex256, ymm/m256, imm8
    { const_string("VPINSRW"), 0x1c4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm16_zero_extended, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 c4 ib /r - VPINSRW xmm, vex128, reg/m16, imm8
    { const_string("VPEXTRW"), 0x1c5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 c5 ib /r - VPEXTRW r64, xmm/m128, imm8
    { const_string("VSHUFPD"), 0x1c6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W0 c6 ib /r - VSHUFPD xmm, vex128, xmm/m128, imm8
    { const_string("VSHUFPD"), 0x1c6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F.W1 c6 ib /r - VSHUFPD xmm, vex128, xmm/m128, imm8
    { const_string("VSHUFPD"), 0x1c6, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W0 c6 ib /r - VSHUFPD ymm, vex256, ymm/m256, imm8
    { const_string("VSHUFPD"), 0x1c6, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F.W1 c6 ib /r - VSHUFPD ymm, vex256, ymm/m256, imm8
    { const_string("VSHUFPS"), 0x1c6, -1, 0, 0, 0, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.0F.W0 c6 ib /r - VSHUFPS xmm, vex128, xmm/m128, imm8
    { const_string("VSHUFPS"), 0x1c6, -1, 0, 0, 0, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.0F.W1 c6 ib /r - VSHUFPS xmm, vex128, xmm/m128, imm8
    { const_string("VSHUFPS"), 0x1c6, -1, 0, 0, 0, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.0F.W0 c6 ib /r - VSHUFPS ymm, vex256, ymm/m256, imm8
    { const_string("VSHUFPS"), 0x1c6, -1, 0, 0, 0, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.0F.W1 c6 ib /r - VSHUFPS ymm, vex256, ymm/m256, imm8
    { const_string("VADDSUBPS"), 0x1d0, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 d0 /r - VADDSUBPS xmm, vex128, xmm/m128
    { const_string("VADDSUBPS"), 0x1d0, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 d0 /r - VADDSUBPS xmm, vex128, xmm/m128
    { const_string("VADDSUBPS"), 0x1d0, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 d0 /r - VADDSUBPS ymm, vex256, ymm/m256
    { const_string("VADDSUBPS"), 0x1d0, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 d0 /r - VADDSUBPS ymm, vex256, ymm/m256
    { const_string("VADDSUBPD"), 0x1d0, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 d0 /r - VADDSUBPD xmm, vex128, xmm/m128
    { const_string("VADDSUBPD"), 0x1d0, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 d0 /r - VADDSUBPD xmm, vex128, xmm/m128
    { const_string("VADDSUBPD"), 0x1d0, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 d0 /r - VADDSUBPD ymm, vex256, ymm/m256
    { const_string("VADDSUBPD"), 0x1d0, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 d0 /r - VADDSUBPD ymm, vex256, ymm/m256
    { const_string("VPSRLW"), 0x1d1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 d1 /r - VPSRLW xmm, vex128, xmm/m128
    { const_string("VPSRLW"), 0x1d1, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 d1 /r - VPSRLW xmm, vex128, xmm/m128
    { const_string("VPSRLW"), 0x1d1, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 d1 /r - VPSRLW ymm, vex256, xmm/m128
    { const_string("VPSRLW"), 0x1d1, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 d1 /r - VPSRLW ymm, vex256, xmm/m128
    { const_string("VPSRLD"), 0x1d2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 d2 /r - VPSRLD xmm, vex128, xmm/m128
    { const_string("VPSRLD"), 0x1d2, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 d2 /r - VPSRLD xmm, vex128, xmm/m128
    { const_string("VPSRLD"), 0x1d2, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 d2 /r - VPSRLD ymm, vex256, xmm/m128
    { const_string("VPSRLD"), 0x1d2, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 d2 /r - VPSRLD ymm, vex256, xmm/m128
    { const_string("VPSRLQ"), 0x1d3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 d3 /r - VPSRLQ xmm, vex128, xmm/m128
    { const_string("VPSRLQ"), 0x1d3, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 d3 /r - VPSRLQ xmm, vex128, xmm/m128
    { const_string("VPSRLQ"), 0x1d3, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 d3 /r - VPSRLQ ymm, vex256, xmm/m128
    { const_string("VPSRLQ"), 0x1d3, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 d3 /r - VPSRLQ ymm, vex256, xmm/m128
    { const_string("VPADDQ"), 0x1d4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 d4 /r - VPADDQ xmm, vex128, xmm/m128
    { const_string("VPADDQ"), 0x1d4, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 d4 /r - VPADDQ xmm, vex128, xmm/m128
    { const_string("VPADDQ"), 0x1d4, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 d4 /r - VPADDQ ymm, vex256, ymm/m256
    { const_string("VPADDQ"), 0x1d4, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 d4 /r - VPADDQ ymm, vex256, ymm/m256
    { const_string("VPMULLW"), 0x1d5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 d5 /r - VPMULLW xmm, vex128, xmm/m128
    { const_string("VPMULLW"), 0x1d5, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 d5 /r - VPMULLW xmm, vex128, xmm/m128
    { const_string("VPMULLW"), 0x1d5, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 d5 /r - VPMULLW ymm, vex256, ymm/m256
    { const_string("VPMULLW"), 0x1d5, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 d5 /r - VPMULLW ymm, vex256, ymm/m256
    { const_string("VMOVQ"), 0x1d6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 d6 /r - VMOVQ xmm/m64, xmm
    { const_string("VMOVQ"), 0x1d6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 d6 /r - VMOVQ xmm/m64, xmm
    { const_string("VPMOVMSKB"), 0x1d7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 d7 /r - VPMOVMSKB r64, xmm/m128
    { const_string("VPMOVMSKB"), 0x1d7, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 d7 /r - VPMOVMSKB r64, xmm/m128
    { const_string("VPMOVMSKB"), 0x1d7, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 d7 /r - VPMOVMSKB r64, ymm/m256
    { const_string("VPMOVMSKB"), 0x1d7, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 d7 /r - VPMOVMSKB r64, ymm/m256
    { const_string("VPSUBUSB"), 0x1d8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 d8 /r - VPSUBUSB xmm, vex128, xmm/m128
    { const_string("VPSUBUSB"), 0x1d8, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 d8 /r - VPSUBUSB xmm, vex128, xmm/m128
    { const_string("VPSUBUSB"), 0x1d8, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 d8 /r - VPSUBUSB ymm, vex256, ymm/m256
    { const_string("VPSUBUSB"), 0x1d8, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 d8 /r - VPSUBUSB ymm, vex256, ymm/m256
    { const_string("VPSUBUSW"), 0x1d9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 d9 /r - VPSUBUSW xmm, vex128, xmm/m128
    { const_string("VPSUBUSW"), 0x1d9, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 d9 /r - VPSUBUSW xmm, vex128, xmm/m128
    { const_string("VPSUBUSW"), 0x1d9, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 d9 /r - VPSUBUSW ymm, vex256, ymm/m256
    { const_string("VPSUBUSW"), 0x1d9, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 d9 /r - VPSUBUSW ymm, vex256, ymm/m256
    { const_string("VPMINUB"), 0x1da, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 da /r - VPMINUB xmm, vex128, xmm/m128
    { const_string("VPMINUB"), 0x1da, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 da /r - VPMINUB xmm, vex128, xmm/m128
    { const_string("VPMINUB"), 0x1da, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 da /r - VPMINUB ymm, vex256, ymm/m256
    { const_string("VPMINUB"), 0x1da, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 da /r - VPMINUB ymm, vex256, ymm/m256
    { const_string("VPAND"), 0x1db, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 db /r - VPAND xmm, vex128, xmm/m128
    { const_string("VPAND"), 0x1db, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 db /r - VPAND xmm, vex128, xmm/m128
    { const_string("VPAND"), 0x1db, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 db /r - VPAND ymm, vex256, ymm/m256
    { const_string("VPAND"), 0x1db, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 db /r - VPAND ymm, vex256, ymm/m256
    { const_string("VPADDUSB"), 0x1dc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 dc /r - VPADDUSB xmm, vex128, xmm/m128
    { const_string("VPADDUSB"), 0x1dc, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 dc /r - VPADDUSB xmm, vex128, xmm/m128
    { const_string("VPADDUSB"), 0x1dc, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 dc /r - VPADDUSB ymm, vex256, ymm/m256
    { const_string("VPADDUSB"), 0x1dc, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 dc /r - VPADDUSB ymm, vex256, ymm/m256
    { const_string("VPADDUSW"), 0x1dd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 dd /r - VPADDUSW xmm, vex128, xmm/m128
    { const_string("VPADDUSW"), 0x1dd, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 dd /r - VPADDUSW xmm, vex128, xmm/m128
    { const_string("VPADDUSW"), 0x1dd, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 dd /r - VPADDUSW ymm, vex256, ymm/m256
    { const_string("VPADDUSW"), 0x1dd, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 dd /r - VPADDUSW ymm, vex256, ymm/m256
    { const_string("VPMAXUB"), 0x1de, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 de /r - VPMAXUB xmm, vex128, xmm/m128
    { const_string("VPMAXUB"), 0x1de, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 de /r - VPMAXUB xmm, vex128, xmm/m128
    { const_string("VPMAXUB"), 0x1de, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 de /r - VPMAXUB ymm, vex256, ymm/m256
    { const_string("VPMAXUB"), 0x1de, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 de /r - VPMAXUB ymm, vex256, ymm/m256
    { const_string("VPANDN"), 0x1df, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 df /r - VPANDN xmm, vex128, xmm/m128
    { const_string("VPANDN"), 0x1df, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 df /r - VPANDN xmm, vex128, xmm/m128
    { const_string("VPANDN"), 0x1df, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 df /r - VPANDN ymm, vex256, ymm/m256
    { const_string("VPANDN"), 0x1df, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 df /r - VPANDN ymm, vex256, ymm/m256
    { const_string("VPAVGB"), 0x1e0, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 e0 /r - VPAVGB xmm, vex128, xmm/m128
    { const_string("VPAVGB"), 0x1e0, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 e0 /r - VPAVGB xmm, vex128, xmm/m128
    { const_string("VPAVGB"), 0x1e0, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 e0 /r - VPAVGB ymm, vex256, ymm/m256
    { const_string("VPAVGB"), 0x1e0, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 e0 /r - VPAVGB ymm, vex256, ymm/m256
    { const_string("VPSRAW"), 0x1e1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 e1 /r - VPSRAW xmm, vex128, xmm/m128
    { const_string("VPSRAW"), 0x1e1, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 e1 /r - VPSRAW xmm, vex128, xmm/m128
    { const_string("VPSRAW"), 0x1e1, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 e1 /r - VPSRAW ymm, vex256, xmm/m128
    { const_string("VPSRAW"), 0x1e1, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 e1 /r - VPSRAW ymm, vex256, xmm/m128
    { const_string("VPSRAD"), 0x1e2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 e2 /r - VPSRAD xmm, vex128, xmm/m128
    { const_string("VPSRAD"), 0x1e2, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 e2 /r - VPSRAD xmm, vex128, xmm/m128
    { const_string("VPSRAD"), 0x1e2, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 e2 /r - VPSRAD ymm, vex256, xmm/m128
    { const_string("VPSRAD"), 0x1e2, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 e2 /r - VPSRAD ymm, vex256, xmm/m128
    { const_string("VPAVGW"), 0x1e3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 e3 /r - VPAVGW xmm, vex128, xmm/m128
    { const_string("VPAVGW"), 0x1e3, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 e3 /r - VPAVGW xmm, vex128, xmm/m128
    { const_string("VPAVGW"), 0x1e3, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 e3 /r - VPAVGW ymm, vex256, ymm/m256
    { const_string("VPAVGW"), 0x1e3, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 e3 /r - VPAVGW ymm, vex256, ymm/m256
    { const_string("VPMULHUW"), 0x1e4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 e4 /r - VPMULHUW xmm, vex128, xmm/m128
    { const_string("VPMULHUW"), 0x1e4, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 e4 /r - VPMULHUW xmm, vex128, xmm/m128
    { const_string("VPMULHUW"), 0x1e4, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 e4 /r - VPMULHUW ymm, vex256, ymm/m256
    { const_string("VPMULHUW"), 0x1e4, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 e4 /r - VPMULHUW ymm, vex256, ymm/m256
    { const_string("VPMULHW"), 0x1e5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 e5 /r - VPMULHW xmm, vex128, xmm/m128
    { const_string("VPMULHW"), 0x1e5, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 e5 /r - VPMULHW xmm, vex128, xmm/m128
    { const_string("VPMULHW"), 0x1e5, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 e5 /r - VPMULHW ymm, vex256, ymm/m256
    { const_string("VPMULHW"), 0x1e5, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 e5 /r - VPMULHW ymm, vex256, ymm/m256
    { const_string("VCVTDQ2PD"), 0x1e6, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W0 e6 /r - VCVTDQ2PD xmm, xmm/m64
    { const_string("VCVTDQ2PD"), 0x1e6, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.F3.0F.W1 e6 /r - VCVTDQ2PD xmm, xmm/m64
    { const_string("VCVTDQ2PD"), 0x1e6, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W0 e6 /r - VCVTDQ2PD ymm, xmm/m128
    { const_string("VCVTDQ2PD"), 0x1e6, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.F3.0F.W1 e6 /r - VCVTDQ2PD ymm, xmm/m128
    { const_string("VCVTPD2DQ"), 0x1e6, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 e6 /r - VCVTPD2DQ xmm, xmm/m128
    { const_string("VCVTPD2DQ"), 0x1e6, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 e6 /r - VCVTPD2DQ xmm, xmm/m128
    { const_string("VCVTPD2DQ"), 0x1e6, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 e6 /r - VCVTPD2DQ xmm, ymm/m256
    { const_string("VCVTPD2DQ"), 0x1e6, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 e6 /r - VCVTPD2DQ xmm, ymm/m256
    { const_string("VCVTTPD2DQ"), 0x1e6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 e6 /r - VCVTTPD2DQ xmm, xmm/m128
    { const_string("VCVTTPD2DQ"), 0x1e6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 e6 /r - VCVTTPD2DQ xmm, xmm/m128
    { const_string("VCVTTPD2DQ"), 0x1e6, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 e6 /r - VCVTTPD2DQ xmm, ymm/m256
    { const_string("VCVTTPD2DQ"), 0x1e6, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 e6 /r - VCVTTPD2DQ xmm, ymm/m256
    { const_string("VMOVNTDQ"), 0x1e7, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 e7 /r - VMOVNTDQ m128, xmm
    { const_string("VMOVNTDQ"), 0x1e7, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 e7 /r - VMOVNTDQ m128, xmm
    { const_string("VMOVNTDQ"), 0x1e7, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 e7 /r - VMOVNTDQ m256, ymm
    { const_string("VMOVNTDQ"), 0x1e7, -1, 0, 0, 1, 1, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 e7 /r - VMOVNTDQ m256, ymm
    { const_string("VPSUBSB"), 0x1e8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 e8 /r - VPSUBSB xmm, vex128, xmm/m128
    { const_string("VPSUBSB"), 0x1e8, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 e8 /r - VPSUBSB xmm, vex128, xmm/m128
    { const_string("VPSUBSB"), 0x1e8, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 e8 /r - VPSUBSB ymm, vex256, ymm/m256
    { const_string("VPSUBSB"), 0x1e8, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 e8 /r - VPSUBSB ymm, vex256, ymm/m256
    { const_string("VPSUBSW"), 0x1e9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 e9 /r - VPSUBSW xmm, vex128, xmm/m128
    { const_string("VPSUBSW"), 0x1e9, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 e9 /r - VPSUBSW xmm, vex128, xmm/m128
    { const_string("VPSUBSW"), 0x1e9, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 e9 /r - VPSUBSW ymm, vex256, ymm/m256
    { const_string("VPSUBSW"), 0x1e9, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 e9 /r - VPSUBSW ymm, vex256, ymm/m256
    { const_string("VPMINSW"), 0x1ea, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 ea /r - VPMINSW xmm, vex128, xmm/m128
    { const_string("VPMINSW"), 0x1ea, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 ea /r - VPMINSW xmm, vex128, xmm/m128
    { const_string("VPMINSW"), 0x1ea, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 ea /r - VPMINSW ymm, vex256, ymm/m256
    { const_string("VPMINSW"), 0x1ea, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 ea /r - VPMINSW ymm, vex256, ymm/m256
    { const_string("VPOR"), 0x1eb, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 eb /r - VPOR xmm, vex128, xmm/m128
    { const_string("VPOR"), 0x1eb, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 eb /r - VPOR xmm, vex128, xmm/m128
    { const_string("VPOR"), 0x1eb, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 eb /r - VPOR ymm, vex256, ymm/m256
    { const_string("VPOR"), 0x1eb, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 eb /r - VPOR ymm, vex256, ymm/m256
    { const_string("VPADDSB"), 0x1ec, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 ec /r - VPADDSB xmm, vex128, xmm/m128
    { const_string("VPADDSB"), 0x1ec, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 ec /r - VPADDSB xmm, vex128, xmm/m128
    { const_string("VPADDSB"), 0x1ec, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 ec /r - VPADDSB ymm, vex256, ymm/m256
    { const_string("VPADDSB"), 0x1ec, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 ec /r - VPADDSB ymm, vex256, ymm/m256
    { const_string("VPADDSW"), 0x1ed, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 ed /r - VPADDSW xmm, vex128, xmm/m128
    { const_string("VPADDSW"), 0x1ed, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 ed /r - VPADDSW xmm, vex128, xmm/m128
    { const_string("VPADDSW"), 0x1ed, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 ed /r - VPADDSW ymm, vex256, ymm/m256
    { const_string("VPADDSW"), 0x1ed, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 ed /r - VPADDSW ymm, vex256, ymm/m256
    { const_string("VPMAXSW"), 0x1ee, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 ee /r - VPMAXSW xmm, vex128, xmm/m128
    { const_string("VPMAXSW"), 0x1ee, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 ee /r - VPMAXSW xmm, vex128, xmm/m128
    { const_string("VPMAXSW"), 0x1ee, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 ee /r - VPMAXSW ymm, vex256, ymm/m256
    { const_string("VPMAXSW"), 0x1ee, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 ee /r - VPMAXSW ymm, vex256, ymm/m256
    { const_string("VPXOR"), 0x1ef, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 ef /r - VPXOR xmm, vex128, xmm/m128
    { const_string("VPXOR"), 0x1ef, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 ef /r - VPXOR xmm, vex128, xmm/m128
    { const_string("VPXOR"), 0x1ef, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 ef /r - VPXOR ymm, vex256, ymm/m256
    { const_string("VPXOR"), 0x1ef, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 ef /r - VPXOR ymm, vex256, ymm/m256
    { const_string("VLDDQU"), 0x1f0, -1, 1, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W0 f0 /r - VLDDQU xmm, m128
    { const_string("VLDDQU"), 0x1f0, -1, 1, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // VEX.128.F2.0F.W1 f0 /r - VLDDQU xmm, m128
    { const_string("VLDDQU"), 0x1f0, -1, 1, 0, 0, 0, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W0 f0 /r - VLDDQU ymm, m256
    { const_string("VLDDQU"), 0x1f0, -1, 1, 0, 0, 1, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // VEX.256.F2.0F.W1 f0 /r - VLDDQU ymm, m256
    { const_string("VPSLLW"), 0x1f1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 f1 /r - VPSLLW xmm, vex128, xmm/m128
    { const_string("VPSLLW"), 0x1f1, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 f1 /r - VPSLLW xmm, vex128, xmm/m128
    { const_string("VPSLLW"), 0x1f1, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 f1 /r - VPSLLW ymm, vex256, xmm/m128
    { const_string("VPSLLW"), 0x1f1, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 f1 /r - VPSLLW ymm, vex256, xmm/m128
    { const_string("VPSLLD"), 0x1f2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 f2 /r - VPSLLD xmm, vex128, xmm/m128
    { const_string("VPSLLD"), 0x1f2, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 f2 /r - VPSLLD xmm, vex128, xmm/m128
    { const_string("VPSLLD"), 0x1f2, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 f2 /r - VPSLLD ymm, vex256, xmm/m128
    { const_string("VPSLLD"), 0x1f2, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 f2 /r - VPSLLD ymm, vex256, xmm/m128
    { const_string("VPSLLQ"), 0x1f3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 f3 /r - VPSLLQ xmm, vex128, xmm/m128
    { const_string("VPSLLQ"), 0x1f3, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 f3 /r - VPSLLQ xmm, vex128, xmm/m128
    { const_string("VPSLLQ"), 0x1f3, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 f3 /r - VPSLLQ ymm, vex256, xmm/m128
    { const_string("VPSLLQ"), 0x1f3, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 f3 /r - VPSLLQ ymm, vex256, xmm/m128
    { const_string("VPMULUDQ"), 0x1f4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 f4 /r - VPMULUDQ xmm, vex128, xmm/m128
    { const_string("VPMULUDQ"), 0x1f4, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 f4 /r - VPMULUDQ xmm, vex128, xmm/m128
    { const_string("VPMULUDQ"), 0x1f4, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 f4 /r - VPMULUDQ ymm, vex256, ymm/m256
    { const_string("VPMULUDQ"), 0x1f4, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 f4 /r - VPMULUDQ ymm, vex256, ymm/m256
    { const_string("VPMADDWD"), 0x1f5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 f5 /r - VPMADDWD xmm, vex128, xmm/m128
    { const_string("VPMADDWD"), 0x1f5, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 f5 /r - VPMADDWD xmm, vex128, xmm/m128
    { const_string("VPMADDWD"), 0x1f5, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 f5 /r - VPMADDWD ymm, vex256, ymm/m256
    { const_string("VPMADDWD"), 0x1f5, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 f5 /r - VPMADDWD ymm, vex256, ymm/m256
    { const_string("VPSADBW"), 0x1f6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 f6 /r - VPSADBW xmm, vex128, xmm/m128
    { const_string("VPSADBW"), 0x1f6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 f6 /r - VPSADBW xmm, vex128, xmm/m128
    { const_string("VPSADBW"), 0x1f6, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 f6 /r - VPSADBW ymm, vex256, ymm/m256
    { const_string("VPSADBW"), 0x1f6, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 f6 /r - VPSADBW ymm, vex256, ymm/m256
    { const_string("VMASKMOVDQU"), 0x1f7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 f7 /r - VMASKMOVDQU xmm, xmm/m128
    { const_string("VMASKMOVDQU"), 0x1f7, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 f7 /r - VMASKMOVDQU xmm, xmm/m128
    { const_string("VPSUBB"), 0x1f8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 f8 /r - VPSUBB xmm, vex128, xmm/m128
    { const_string("VPSUBB"), 0x1f8, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 f8 /r - VPSUBB xmm, vex128, xmm/m128
    { const_string("VPSUBB"), 0x1f8, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 f8 /r - VPSUBB ymm, vex256, ymm/m256
    { const_string("VPSUBB"), 0x1f8, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 f8 /r - VPSUBB ymm, vex256, ymm/m256
    { const_string("VPSUBW"), 0x1f9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 f9 /r - VPSUBW xmm, vex128, xmm/m128
    { const_string("VPSUBW"), 0x1f9, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 f9 /r - VPSUBW xmm, vex128, xmm/m128
    { const_string("VPSUBW"), 0x1f9, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 f9 /r - VPSUBW ymm, vex256, ymm/m256
    { const_string("VPSUBW"), 0x1f9, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 f9 /r - VPSUBW ymm, vex256, ymm/m256
    { const_string("VPSUBD"), 0x1fa, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 fa /r - VPSUBD xmm, vex128, xmm/m128
    { const_string("VPSUBD"), 0x1fa, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 fa /r - VPSUBD xmm, vex128, xmm/m128
    { const_string("VPSUBD"), 0x1fa, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 fa /r - VPSUBD ymm, vex256, ymm/m256
    { const_string("VPSUBD"), 0x1fa, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 fa /r - VPSUBD ymm, vex256, ymm/m256
    { const_string("VPSUBQ"), 0x1fb, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 fb /r - VPSUBQ xmm, vex128, xmm/m128
    { const_string("VPSUBQ"), 0x1fb, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 fb /r - VPSUBQ xmm, vex128, xmm/m128
    { const_string("VPSUBQ"), 0x1fb, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 fb /r - VPSUBQ ymm, vex256, ymm/m256
    { const_string("VPSUBQ"), 0x1fb, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 fb /r - VPSUBQ ymm, vex256, ymm/m256
    { const_string("VPADDB"), 0x1fc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 fc /r - VPADDB xmm, vex128, xmm/m128
    { const_string("VPADDB"), 0x1fc, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 fc /r - VPADDB xmm, vex128, xmm/m128
    { const_string("VPADDB"), 0x1fc, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 fc /r - VPADDB ymm, vex256, ymm/m256
    { const_string("VPADDB"), 0x1fc, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 fc /r - VPADDB ymm, vex256, ymm/m256
    { const_string("VPADDW"), 0x1fd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 fd /r - VPADDW xmm, vex128, xmm/m128
    { const_string("VPADDW"), 0x1fd, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 fd /r - VPADDW xmm, vex128, xmm/m128
    { const_string("VPADDW"), 0x1fd, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 fd /r - VPADDW ymm, vex256, ymm/m256
    { const_string("VPADDW"), 0x1fd, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 fd /r - VPADDW ymm, vex256, ymm/m256
    { const_string("VPADDD"), 0x1fe, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W0 fe /r - VPADDD xmm, vex128, xmm/m128
    { const_string("VPADDD"), 0x1fe, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F.W1 fe /r - VPADDD xmm, vex128, xmm/m128
    { const_string("VPADDD"), 0x1fe, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W0 fe /r - VPADDD ymm, vex256, ymm/m256
    { const_string("VPADDD"), 0x1fe, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F.W1 fe /r - VPADDD ymm, vex256, ymm/m256
    { const_string("VPSHUFB"), 0x200, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 00 /r - VPSHUFB xmm, vex128, xmm/m128
    { const_string("VPSHUFB"), 0x200, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 00 /r - VPSHUFB xmm, vex128, xmm/m128
    { const_string("VPSHUFB"), 0x200, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 00 /r - VPSHUFB ymm, vex256, ymm/m256
    { const_string("VPSHUFB"), 0x200, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 00 /r - VPSHUFB ymm, vex256, ymm/m256
    { const_string("VPHADDW"), 0x201, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 01 /r - VPHADDW xmm, vex128, xmm/m128
    { const_string("VPHADDW"), 0x201, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 01 /r - VPHADDW xmm, vex128, xmm/m128
    { const_string("VPHADDW"), 0x201, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 01 /r - VPHADDW ymm, vex256, ymm/m256
    { const_string("VPHADDW"), 0x201, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 01 /r - VPHADDW ymm, vex256, ymm/m256
    { const_string("VPHADDD"), 0x202, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 02 /r - VPHADDD xmm, vex128, xmm/m128
    { const_string("VPHADDD"), 0x202, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 02 /r - VPHADDD xmm, vex128, xmm/m128
    { const_string("VPHADDD"), 0x202, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 02 /r - VPHADDD ymm, vex256, ymm/m256
    { const_string("VPHADDD"), 0x202, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 02 /r - VPHADDD ymm, vex256, ymm/m256
    { const_string("VPHADDSW"), 0x203, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 03 /r - VPHADDSW xmm, vex128, xmm/m128
    { const_string("VPHADDSW"), 0x203, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 03 /r - VPHADDSW xmm, vex128, xmm/m128
    { const_string("VPHADDSW"), 0x203, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 03 /r - VPHADDSW ymm, vex256, ymm/m256
    { const_string("VPHADDSW"), 0x203, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 03 /r - VPHADDSW ymm, vex256, ymm/m256
    { const_string("VPMADDUBSW"), 0x204, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 04 /r - VPMADDUBSW xmm, vex128, xmm/m128
    { const_string("VPMADDUBSW"), 0x204, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 04 /r - VPMADDUBSW xmm, vex128, xmm/m128
    { const_string("VPMADDUBSW"), 0x204, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 04 /r - VPMADDUBSW ymm, vex256, ymm/m256
    { const_string("VPMADDUBSW"), 0x204, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 04 /r - VPMADDUBSW ymm, vex256, ymm/m256
    { const_string("VPHSUBW"), 0x205, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 05 /r - VPHSUBW xmm, vex128, xmm/m128
    { const_string("VPHSUBW"), 0x205, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 05 /r - VPHSUBW xmm, vex128, xmm/m128
    { const_string("VPHSUBW"), 0x205, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 05 /r - VPHSUBW ymm, vex256, ymm/m256
    { const_string("VPHSUBW"), 0x205, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 05 /r - VPHSUBW ymm, vex256, ymm/m256
    { const_string("VPHSUBD"), 0x206, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 06 /r - VPHSUBD xmm, vex128, xmm/m128
    { const_string("VPHSUBD"), 0x206, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 06 /r - VPHSUBD xmm, vex128, xmm/m128
    { const_string("VPHSUBD"), 0x206, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 06 /r - VPHSUBD ymm, vex256, ymm/m256
    { const_string("VPHSUBD"), 0x206, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 06 /r - VPHSUBD ymm, vex256, ymm/m256
    { const_string("VPHSUBSW"), 0x207, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 07 /r - VPHSUBSW xmm, vex128, xmm/m128
    { const_string("VPHSUBSW"), 0x207, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 07 /r - VPHSUBSW xmm, vex128, xmm/m128
    { const_string("VPHSUBSW"), 0x207, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 07 /r - VPHSUBSW ymm, vex256, ymm/m256
    { const_string("VPHSUBSW"), 0x207, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 07 /r - VPHSUBSW ymm, vex256, ymm/m256
    { const_string("VPSIGNB"), 0x208, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 08 /r - VPSIGNB xmm, vex128, xmm/m128
    { const_string("VPSIGNB"), 0x208, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 08 /r - VPSIGNB xmm, vex128, xmm/m128
    { const_string("VPSIGNB"), 0x208, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 08 /r - VPSIGNB ymm, vex256, ymm/m256
    { const_string("VPSIGNB"), 0x208, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 08 /r - VPSIGNB ymm, vex256, ymm/m256
    { const_string("VPSIGNW"), 0x209, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 09 /r - VPSIGNW xmm, vex128, xmm/m128
    { const_string("VPSIGNW"), 0x209, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 09 /r - VPSIGNW xmm, vex128, xmm/m128
    { const_string("VPSIGNW"), 0x209, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 09 /r - VPSIGNW ymm, vex256, ymm/m256
    { const_string("VPSIGNW"), 0x209, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 09 /r - VPSIGNW ymm, vex256, ymm/m256
    { const_string("VPSIGND"), 0x20a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 0a /r - VPSIGND xmm, vex128, xmm/m128
    { const_string("VPSIGND"), 0x20a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 0a /r - VPSIGND xmm, vex128, xmm/m128
    { const_string("VPSIGND"), 0x20a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 0a /r - VPSIGND ymm, vex256, ymm/m256
    { const_string("VPSIGND"), 0x20a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 0a /r - VPSIGND ymm, vex256, ymm/m256
    { const_string("VPMULHRSW"), 0x20b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 0b /r - VPMULHRSW xmm, vex128, xmm/m128
    { const_string("VPMULHRSW"), 0x20b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 0b /r - VPMULHRSW xmm, vex128, xmm/m128
    { const_string("VPMULHRSW"), 0x20b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 0b /r - VPMULHRSW ymm, vex256, ymm/m256
    { const_string("VPMULHRSW"), 0x20b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 0b /r - VPMULHRSW ymm, vex256, ymm/m256
    { const_string("VPERMILPS"), 0x20c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 0c /r - VPERMILPS xmm, vex128, xmm/m128
    { const_string("VPERMILPS"), 0x20c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 0c /r - VPERMILPS ymm, vex256, ymm/m256
    { const_string("VPERMILPD"), 0x20d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 0d /r - VPERMILPD xmm, vex128, xmm/m128
    { const_string("VPERMILPD"), 0x20d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 0d /r - VPERMILPD ymm, vex256, ymm/m256
    { const_string("VTESTPS"), 0x20e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 0e /r - VTESTPS xmm, xmm/m128
    { const_string("VTESTPS"), 0x20e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 0e /r - VTESTPS ymm, ymm/m256
    { const_string("VTESTPD"), 0x20f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 0f /r - VTESTPD xmm, xmm/m128
    { const_string("VTESTPD"), 0x20f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 0f /r - VTESTPD ymm, ymm/m256
    { const_string("VCVTPH2PS"), 0x213, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 13 /r - VCVTPH2PS xmm, xmm/m64
    { const_string("VCVTPH2PS"), 0x213, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 13 /r - VCVTPH2PS ymm, xmm/m128
    { const_string("VPERMPS"), 0x216, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 16 /r - VPERMPS ymm, vex256, ymm/m256
    { const_string("VPTEST"), 0x217, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 17 /r - VPTEST xmm, xmm/m128
    { const_string("VPTEST"), 0x217, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 17 /r - VPTEST xmm, xmm/m128
    { const_string("VPTEST"), 0x217, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 17 /r - VPTEST ymm, ymm/m256
    { const_string("VPTEST"), 0x217, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 17 /r - VPTEST ymm, ymm/m256
    { const_string("VBROADCASTSS"), 0x218, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 18 /r - VBROADCASTSS xmm, m32
    { const_string("VBROADCASTSS"), 0x218, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 18 /r - VBROADCASTSS xmm, xmm/m128
    { const_string("VBROADCASTSS"), 0x218, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 18 /r - VBROADCASTSS ymm, m32
    { const_string("VBROADCASTSS"), 0x218, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 18 /r - VBROADCASTSS ymm, xmm/m128
    { const_string("VBROADCASTSD"), 0x219, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 19 /r - VBROADCASTSD ymm, m64
    { const_string("VBROADCASTSD"), 0x219, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 19 /r - VBROADCASTSD ymm, xmm/m128
    { const_string("VBROADCASTF128"), 0x21a, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 1a /r - VBROADCASTF128 ymm, m128
    { const_string("VPABSB"), 0x21c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 1c /r - VPABSB xmm, xmm/m128
    { const_string("VPABSB"), 0x21c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 1c /r - VPABSB xmm, xmm/m128
    { const_string("VPABSB"), 0x21c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 1c /r - VPABSB ymm, ymm/m256
    { const_string("VPABSB"), 0x21c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 1c /r - VPABSB ymm, ymm/m256
    { const_string("VPABSW"), 0x21d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 1d /r - VPABSW xmm, xmm/m128
    { const_string("VPABSW"), 0x21d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 1d /r - VPABSW xmm, xmm/m128
    { const_string("VPABSW"), 0x21d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 1d /r - VPABSW ymm, ymm/m256
    { const_string("VPABSW"), 0x21d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 1d /r - VPABSW ymm, ymm/m256
    { const_string("VPABSD"), 0x21e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 1e /r - VPABSD xmm, xmm/m128
    { const_string("VPABSD"), 0x21e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 1e /r - VPABSD xmm, xmm/m128
    { const_string("VPABSD"), 0x21e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 1e /r - VPABSD ymm, ymm/m256
    { const_string("VPABSD"), 0x21e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 1e /r - VPABSD ymm, ymm/m256
    { const_string("VPMOVSXBW"), 0x220, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 20 /r - VPMOVSXBW xmm, xmm/m64
    { const_string("VPMOVSXBW"), 0x220, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 20 /r - VPMOVSXBW xmm, xmm/m64
    { const_string("VPMOVSXBW"), 0x220, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 20 /r - VPMOVSXBW ymm, xmm/m128
    { const_string("VPMOVSXBW"), 0x220, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 20 /r - VPMOVSXBW ymm, xmm/m128
    { const_string("VPMOVSXBD"), 0x221, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 21 /r - VPMOVSXBD xmm, xmm/m32
    { const_string("VPMOVSXBD"), 0x221, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 21 /r - VPMOVSXBD xmm, xmm/m32
    { const_string("VPMOVSXBD"), 0x221, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 21 /r - VPMOVSXBD ymm, xmm/m64
    { const_string("VPMOVSXBD"), 0x221, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 21 /r - VPMOVSXBD ymm, xmm/m64
    { const_string("VPMOVSXBQ"), 0x222, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 22 /r - VPMOVSXBQ xmm, xmm/m64
    { const_string("VPMOVSXBQ"), 0x222, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 22 /r - VPMOVSXBQ xmm, xmm/m64
    { const_string("VPMOVSXBQ"), 0x222, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 22 /r - VPMOVSXBQ ymm, xmm/m32
    { const_string("VPMOVSXBQ"), 0x222, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 22 /r - VPMOVSXBQ ymm, xmm/m32
    { const_string("VPMOVSXWD"), 0x223, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 23 /r - VPMOVSXWD xmm, xmm/m64
    { const_string("VPMOVSXWD"), 0x223, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 23 /r - VPMOVSXWD xmm, xmm/m64
    { const_string("VPMOVSXWD"), 0x223, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 23 /r - VPMOVSXWD ymm, xmm/m128
    { const_string("VPMOVSXWD"), 0x223, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 23 /r - VPMOVSXWD ymm, xmm/m128
    { const_string("VPMOVSXWQ"), 0x224, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 24 /r - VPMOVSXWQ xmm, xmm/m32
    { const_string("VPMOVSXWQ"), 0x224, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 24 /r - VPMOVSXWQ xmm, xmm/m32
    { const_string("VPMOVSXWQ"), 0x224, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 24 /r - VPMOVSXWQ ymm, xmm/m64
    { const_string("VPMOVSXWQ"), 0x224, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 24 /r - VPMOVSXWQ ymm, xmm/m64
    { const_string("VPMOVSXDQ"), 0x225, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 25 /r - VPMOVSXDQ xmm, xmm/m64
    { const_string("VPMOVSXDQ"), 0x225, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 25 /r - VPMOVSXDQ xmm, xmm/m64
    { const_string("VPMOVSXDQ"), 0x225, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 25 /r - VPMOVSXDQ ymm, xmm/m128
    { const_string("VPMOVSXDQ"), 0x225, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 25 /r - VPMOVSXDQ ymm, xmm/m128
    { const_string("VPMULDQ"), 0x228, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 28 /r - VPMULDQ xmm, vex128, xmm/m128
    { const_string("VPMULDQ"), 0x228, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 28 /r - VPMULDQ xmm, vex128, xmm/m128
    { const_string("VPMULDQ"), 0x228, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 28 /r - VPMULDQ ymm, vex256, ymm/m256
    { const_string("VPMULDQ"), 0x228, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 28 /r - VPMULDQ ymm, vex256, ymm/m256
    { const_string("VPCMPEQQ"), 0x229, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 29 /r - VPCMPEQQ xmm, vex128, xmm/m128
    { const_string("VPCMPEQQ"), 0x229, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 29 /r - VPCMPEQQ xmm, vex128, xmm/m128
    { const_string("VPCMPEQQ"), 0x229, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 29 /r - VPCMPEQQ ymm, vex256, ymm/m256
    { const_string("VPCMPEQQ"), 0x229, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 29 /r - VPCMPEQQ ymm, vex256, ymm/m256
    { const_string("VMOVNTDQA"), 0x22a, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 2a /r - VMOVNTDQA xmm, m128
    { const_string("VMOVNTDQA"), 0x22a, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 2a /r - VMOVNTDQA xmm, m128
    { const_string("VMOVNTDQA"), 0x22a, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 2a /r - VMOVNTDQA ymm, m256
    { const_string("VMOVNTDQA"), 0x22a, -1, 0, 0, 1, 1, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 2a /r - VMOVNTDQA ymm, m256
    { const_string("VPACKUSDW"), 0x22b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 2b /r - VPACKUSDW xmm, vex128, xmm/m128
    { const_string("VPACKUSDW"), 0x22b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 2b /r - VPACKUSDW xmm, vex128, xmm/m128
    { const_string("VPACKUSDW"), 0x22b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 2b /r - VPACKUSDW ymm, vex256, ymm/m256
    { const_string("VPACKUSDW"), 0x22b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 2b /r - VPACKUSDW ymm, vex256, ymm/m256
    { const_string("VMASKMOVPS"), 0x22c, -1, 0, 0, 1, 0, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 2c /r - VMASKMOVPS xmm, vex128, m128
    { const_string("VMASKMOVPS"), 0x22c, -1, 0, 0, 1, 0, 1, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_m256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 2c /r - VMASKMOVPS ymm, vex256, m256
    { const_string("VMASKMOVPD"), 0x22d, -1, 0, 0, 1, 0, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 2d /r - VMASKMOVPD xmm, vex128, m128
    { const_string("VMASKMOVPD"), 0x22d, -1, 0, 0, 1, 0, 1, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_m256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 2d /r - VMASKMOVPD ymm, vex256, m256
    { const_string("VMASKMOVPS"), 0x22e, -1, 0, 0, 1, 0, 1, -1, 0, 0, 3, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 2e /r - VMASKMOVPS m128, vex128, xmm
    { const_string("VMASKMOVPS"), 0x22e, -1, 0, 0, 1, 0, 1, -1, 0, 1, 3, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 2e /r - VMASKMOVPS m256, vex256, ymm
    { const_string("VMASKMOVPD"), 0x22f, -1, 0, 0, 1, 0, 1, -1, 0, 0, 3, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 2f /r - VMASKMOVPD m128, vex128, xmm
    { const_string("VMASKMOVPD"), 0x22f, -1, 0, 0, 1, 0, 1, -1, 0, 1, 3, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 2f /r - VMASKMOVPD m256, vex256, ymm
    { const_string("VPMOVZXBW"), 0x230, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 30 /r - VPMOVZXBW xmm, xmm/m64
    { const_string("VPMOVZXBW"), 0x230, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 30 /r - VPMOVZXBW xmm, xmm/m64
    { const_string("VPMOVZXBW"), 0x230, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 30 /r - VPMOVZXBW ymm, xmm/m128
    { const_string("VPMOVZXBW"), 0x230, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 30 /r - VPMOVZXBW ymm, xmm/m128
    { const_string("VPMOVZXBD"), 0x231, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 31 /r - VPMOVZXBD xmm, xmm/m32
    { const_string("VPMOVZXBD"), 0x231, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 31 /r - VPMOVZXBD xmm, xmm/m32
    { const_string("VPMOVZXBD"), 0x231, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 31 /r - VPMOVZXBD ymm, xmm/m64
    { const_string("VPMOVZXBD"), 0x231, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 31 /r - VPMOVZXBD ymm, xmm/m64
    { const_string("VPMOVZXBQ"), 0x232, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 32 /r - VPMOVZXBQ xmm, xmm/m64
    { const_string("VPMOVZXBQ"), 0x232, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 32 /r - VPMOVZXBQ xmm, xmm/m64
    { const_string("VPMOVZXBQ"), 0x232, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 32 /r - VPMOVZXBQ ymm, xmm/m32
    { const_string("VPMOVZXBQ"), 0x232, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 32 /r - VPMOVZXBQ ymm, xmm/m32
    { const_string("VPMOVZXWD"), 0x233, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 33 /r - VPMOVZXWD xmm, xmm/m64
    { const_string("VPMOVZXWD"), 0x233, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 33 /r - VPMOVZXWD xmm, xmm/m64
    { const_string("VPMOVZXWD"), 0x233, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 33 /r - VPMOVZXWD ymm, xmm/m128
    { const_string("VPMOVZXWD"), 0x233, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 33 /r - VPMOVZXWD ymm, xmm/m128
    { const_string("VPMOVZXWQ"), 0x234, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 34 /r - VPMOVZXWQ xmm, xmm/m32
    { const_string("VPMOVZXWQ"), 0x234, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 34 /r - VPMOVZXWQ xmm, xmm/m32
    { const_string("VPMOVZXWQ"), 0x234, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 34 /r - VPMOVZXWQ ymm, xmm/m64
    { const_string("VPMOVZXWQ"), 0x234, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 34 /r - VPMOVZXWQ ymm, xmm/m64
    { const_string("VPMOVZXDQ"), 0x235, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 35 /r - VPMOVZXDQ xmm, xmm/m64
    { const_string("VPMOVZXDQ"), 0x235, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 35 /r - VPMOVZXDQ xmm, xmm/m64
    { const_string("VPMOVZXDQ"), 0x235, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 35 /r - VPMOVZXDQ ymm, xmm/m128
    { const_string("VPMOVZXDQ"), 0x235, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 35 /r - VPMOVZXDQ ymm, xmm/m128
    { const_string("VPERMD"), 0x236, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 36 /r - VPERMD ymm, vex256, ymm/m256
    { const_string("VPCMPGTQ"), 0x237, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 37 /r - VPCMPGTQ xmm, vex128, xmm/m128
    { const_string("VPCMPGTQ"), 0x237, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 37 /r - VPCMPGTQ xmm, vex128, xmm/m128
    { const_string("VPCMPGTQ"), 0x237, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 37 /r - VPCMPGTQ ymm, vex256, ymm/m256
    { const_string("VPCMPGTQ"), 0x237, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 37 /r - VPCMPGTQ ymm, vex256, ymm/m256
    { const_string("VPMINSB"), 0x238, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 38 /r - VPMINSB xmm, vex128, xmm/m128
    { const_string("VPMINSB"), 0x238, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 38 /r - VPMINSB xmm, vex128, xmm/m128
    { const_string("VPMINSB"), 0x238, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 38 /r - VPMINSB ymm, vex256, ymm/m256
    { const_string("VPMINSB"), 0x238, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 38 /r - VPMINSB ymm, vex256, ymm/m256
    { const_string("VPMINSD"), 0x239, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 39 /r - VPMINSD xmm, vex128, xmm/m128
    { const_string("VPMINSD"), 0x239, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 39 /r - VPMINSD xmm, vex128, xmm/m128
    { const_string("VPMINSD"), 0x239, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 39 /r - VPMINSD ymm, vex256, ymm/m256
    { const_string("VPMINSD"), 0x239, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 39 /r - VPMINSD ymm, vex256, ymm/m256
    { const_string("VPMINUW"), 0x23a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 3a /r - VPMINUW xmm, vex128, xmm/m128
    { const_string("VPMINUW"), 0x23a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 3a /r - VPMINUW xmm, vex128, xmm/m128
    { const_string("VPMINUW"), 0x23a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 3a /r - VPMINUW ymm, vex256, ymm/m256
    { const_string("VPMINUW"), 0x23a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 3a /r - VPMINUW ymm, vex256, ymm/m256
    { const_string("VPMINUD"), 0x23b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 3b /r - VPMINUD xmm, vex128, xmm/m128
    { const_string("VPMINUD"), 0x23b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 3b /r - VPMINUD xmm, vex128, xmm/m128
    { const_string("VPMINUD"), 0x23b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 3b /r - VPMINUD ymm, vex256, ymm/m256
    { const_string("VPMINUD"), 0x23b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 3b /r - VPMINUD ymm, vex256, ymm/m256
    { const_string("VPMAXSB"), 0x23c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 3c /r - VPMAXSB xmm, vex128, xmm/m128
    { const_string("VPMAXSB"), 0x23c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 3c /r - VPMAXSB xmm, vex128, xmm/m128
    { const_string("VPMAXSB"), 0x23c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 3c /r - VPMAXSB ymm, vex256, ymm/m256
    { const_string("VPMAXSB"), 0x23c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 3c /r - VPMAXSB ymm, vex256, ymm/m256
    { const_string("VPMAXSD"), 0x23d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 3d /r - VPMAXSD xmm, vex128, xmm/m128
    { const_string("VPMAXSD"), 0x23d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 3d /r - VPMAXSD xmm, vex128, xmm/m128
    { const_string("VPMAXSD"), 0x23d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 3d /r - VPMAXSD ymm, vex256, ymm/m256
    { const_string("VPMAXSD"), 0x23d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 3d /r - VPMAXSD ymm, vex256, ymm/m256
    { const_string("VPMAXUW"), 0x23e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 3e /r - VPMAXUW xmm, vex128, xmm/m128
    { const_string("VPMAXUW"), 0x23e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 3e /r - VPMAXUW xmm, vex128, xmm/m128
    { const_string("VPMAXUW"), 0x23e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 3e /r - VPMAXUW ymm, vex256, ymm/m256
    { const_string("VPMAXUW"), 0x23e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 3e /r - VPMAXUW ymm, vex256, ymm/m256
    { const_string("VPMAXUD"), 0x23f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 3f /r - VPMAXUD xmm, vex128, xmm/m128
    { const_string("VPMAXUD"), 0x23f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 3f /r - VPMAXUD xmm, vex128, xmm/m128
    { const_string("VPMAXUD"), 0x23f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 3f /r - VPMAXUD ymm, vex256, ymm/m256
    { const_string("VPMAXUD"), 0x23f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 3f /r - VPMAXUD ymm, vex256, ymm/m256
    { const_string("VPMULLD"), 0x240, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 40 /r - VPMULLD xmm, vex128, xmm/m128
    { const_string("VPMULLD"), 0x240, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 40 /r - VPMULLD xmm, vex128, xmm/m128
    { const_string("VPMULLD"), 0x240, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 40 /r - VPMULLD ymm, vex256, ymm/m256
    { const_string("VPMULLD"), 0x240, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 40 /r - VPMULLD ymm, vex256, ymm/m256
    { const_string("VPHMINPOSUW"), 0x241, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 41 /r - VPHMINPOSUW xmm, xmm/m128
    { const_string("VPHMINPOSUW"), 0x241, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 41 /r - VPHMINPOSUW xmm, xmm/m128
    { const_string("VPSRLVD"), 0x245, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 45 /r - VPSRLVD xmm, vex128, xmm/m128
    { const_string("VPSRLVQ"), 0x245, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 45 /r - VPSRLVQ xmm, vex128, xmm/m128
    { const_string("VPSRLVD"), 0x245, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 45 /r - VPSRLVD ymm, vex256, ymm/m256
    { const_string("VPSRLVQ"), 0x245, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 45 /r - VPSRLVQ ymm, vex256, ymm/m256
    { const_string("VPSRAVD"), 0x246, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 46 /r - VPSRAVD xmm, vex128, xmm/m128
    { const_string("VPSRAVD"), 0x246, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 46 /r - VPSRAVD ymm, vex256, ymm/m256
    { const_string("VPSLLVD"), 0x247, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 47 /r - VPSLLVD xmm, vex128, xmm/m128
    { const_string("VPSLLVQ"), 0x247, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 47 /r - VPSLLVQ xmm, vex128, xmm/m128
    { const_string("VPSLLVD"), 0x247, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 47 /r - VPSLLVD ymm, vex256, ymm/m256
    { const_string("VPSLLVQ"), 0x247, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 47 /r - VPSLLVQ ymm, vex256, ymm/m256
    { const_string("VPBROADCASTD"), 0x258, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 58 /r - VPBROADCASTD xmm, xmm/m32
    { const_string("VPBROADCASTD"), 0x258, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 58 /r - VPBROADCASTD ymm, xmm/m32
    { const_string("VPBROADCASTQ"), 0x259, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 59 /r - VPBROADCASTQ xmm, xmm/m64
    { const_string("VPBROADCASTQ"), 0x259, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 59 /r - VPBROADCASTQ ymm, xmm/m64
    { const_string("VBROADCASTI128"), 0x25a, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 5a /r - VBROADCASTI128 ymm, m128
    { const_string("VPBROADCASTB"), 0x278, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm8, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 78 /r - VPBROADCASTB xmm, xmm/m8
    { const_string("VPBROADCASTB"), 0x278, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm8, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 78 /r - VPBROADCASTB ymm, xmm/m8
    { const_string("VPBROADCASTW"), 0x279, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 79 /r - VPBROADCASTW xmm, xmm/m64
    { const_string("VPBROADCASTW"), 0x279, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 79 /r - VPBROADCASTW ymm, xmm/m64
    { const_string("VPMASKMOVD"), 0x28c, -1, 0, 0, 1, 0, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 8c /r - VPMASKMOVD xmm, vex128, m128
    { const_string("VPMASKMOVQ"), 0x28c, -1, 0, 0, 1, 1, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 8c /r - VPMASKMOVQ xmm, vex128, m128
    { const_string("VPMASKMOVD"), 0x28c, -1, 0, 0, 1, 0, 1, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_m256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 8c /r - VPMASKMOVD ymm, vex256, m256
    { const_string("VPMASKMOVQ"), 0x28c, -1, 0, 0, 1, 1, 1, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_m256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 8c /r - VPMASKMOVQ ymm, vex256, m256
    { const_string("VPMASKMOVD"), 0x28e, -1, 0, 0, 1, 0, 1, -1, 0, 0, 3, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 8e /r - VPMASKMOVD m128, vex128, xmm
    { const_string("VPMASKMOVQ"), 0x28e, -1, 0, 0, 1, 1, 1, -1, 0, 0, 3, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 8e /r - VPMASKMOVQ m128, vex128, xmm
    { const_string("VPMASKMOVD"), 0x28e, -1, 0, 0, 1, 0, 1, -1, 0, 1, 3, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 8e /r - VPMASKMOVD m256, vex256, ymm
    { const_string("VPMASKMOVQ"), 0x28e, -1, 0, 0, 1, 1, 1, -1, 0, 1, 3, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 8e /r - VPMASKMOVQ m256, vex256, ymm
    { const_string("VPGATHERDD"), 0x290, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.128.66.0F38.W0 90 /r - VPGATHERDD xmm, vm32x, xmm
    { const_string("VPGATHERDQ"), 0x290, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.128.66.0F38.W1 90 /r - VPGATHERDQ xmm, vm32x, xmm
    { const_string("VPGATHERDD"), 0x290, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32y, OPERAND_FLAG_read}, {OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.256.66.0F38.W0 90 /r - VPGATHERDD ymm, vm32y, ymm
    { const_string("VPGATHERDQ"), 0x290, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}, {OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.256.66.0F38.W1 90 /r - VPGATHERDQ ymm, vm32x, ymm
    { const_string("VPGATHERQD"), 0x291, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64x, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.128.66.0F38.W0 91 /r - VPGATHERQD xmm, vm64x, xmm
    { const_string("VPGATHERQQ"), 0x291, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64x, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.128.66.0F38.W1 91 /r - VPGATHERQQ xmm, vm64x, xmm
    { const_string("VPGATHERQD"), 0x291, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64y, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.256.66.0F38.W0 91 /r - VPGATHERQD xmm, vm64y, xmm
    { const_string("VPGATHERQQ"), 0x291, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64y, OPERAND_FLAG_read}, {OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.256.66.0F38.W1 91 /r - VPGATHERQQ ymm, vm64y, ymm
    { const_string("VGATHERDPS"), 0x292, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.128.66.0F38.W0 92 /r - VGATHERDPS xmm, vm32x, xmm
    { const_string("VGATHERDPD"), 0x292, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.128.66.0F38.W1 92 /r - VGATHERDPD xmm, vm32x, xmm
    { const_string("VGATHERDPS"), 0x292, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32y, OPERAND_FLAG_read}, {OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.256.66.0F38.W0 92 /r - VGATHERDPS ymm, vm32y, ymm
    { const_string("VGATHERDPD"), 0x292, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}, {OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.256.66.0F38.W1 92 /r - VGATHERDPD ymm, vm32x, ymm
    { const_string("VGATHERQPS"), 0x293, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64x, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.128.66.0F38.W0 93 /r - VGATHERQPS xmm, vm64x, xmm
    { const_string("VGATHERQPD"), 0x293, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64x, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.128.66.0F38.W1 93 /r - VGATHERQPD xmm, vm64x, xmm
    { const_string("VGATHERQPS"), 0x293, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64y, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.256.66.0F38.W0 93 /r - VGATHERQPS xmm, vm64y, xmm
    { const_string("VGATHERQPD"), 0x293, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64y, OPERAND_FLAG_read}, {OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}} }, // VEX.256.66.0F38.W1 93 /r - VGATHERQPD ymm, vm64y, ymm
    { const_string("VFMADDSUB132PS"), 0x296, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 96 /r - VFMADDSUB132PS xmm, vex128, xmm/m128
    { const_string("VFMADDSUB132PD"), 0x296, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 96 /r - VFMADDSUB132PD xmm, vex128, xmm/m128
    { const_string("VFMADDSUB132PS"), 0x296, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 96 /r - VFMADDSUB132PS ymm, vex256, ymm/m256
    { const_string("VFMADDSUB132PD"), 0x296, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 96 /r - VFMADDSUB132PD ymm, vex256, ymm/m256
    { const_string("VFMSUBADD132PS"), 0x297, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 97 /r - VFMSUBADD132PS xmm, vex128, xmm/m128
    { const_string("VFMSUBADD132PD"), 0x297, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 97 /r - VFMSUBADD132PD xmm, vex128, xmm/m128
    { const_string("VFMSUBADD132PS"), 0x297, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 97 /r - VFMSUBADD132PS ymm, vex256, ymm/m256
    { const_string("VFMSUBADD132PD"), 0x297, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 97 /r - VFMSUBADD132PD ymm, vex256, ymm/m256
    { const_string("VFMADD132PS"), 0x298, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 98 /r - VFMADD132PS xmm, vex128, xmm/m128
    { const_string("VFMADD132PD"), 0x298, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 98 /r - VFMADD132PD xmm, vex128, xmm/m128
    { const_string("VFMADD132PS"), 0x298, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 98 /r - VFMADD132PS ymm, vex256, ymm/m256
    { const_string("VFMADD132PD"), 0x298, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 98 /r - VFMADD132PD ymm, vex256, ymm/m256
    { const_string("VFMADD132SS"), 0x299, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 99 /r - VFMADD132SS xmm, vex128, xmm/m32
    { const_string("VFMADD132SD"), 0x299, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 99 /r - VFMADD132SD xmm, vex128, xmm/m64
    { const_string("VFMADD132SS"), 0x299, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 99 /r - VFMADD132SS xmm, vex128, xmm/m32
    { const_string("VFMADD132SD"), 0x299, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 99 /r - VFMADD132SD xmm, vex128, xmm/m64
    { const_string("VFMSUB132PS"), 0x29a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 9a /r - VFMSUB132PS xmm, vex128, xmm/m128
    { const_string("VFMSUB132PD"), 0x29a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 9a /r - VFMSUB132PD xmm, vex128, xmm/m128
    { const_string("VFMSUB132PS"), 0x29a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 9a /r - VFMSUB132PS ymm, vex256, ymm/m256
    { const_string("VFMSUB132PD"), 0x29a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 9a /r - VFMSUB132PD ymm, vex256, ymm/m256
    { const_string("VFMSUB132SS"), 0x29b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 9b /r - VFMSUB132SS xmm, vex128, xmm/m32
    { const_string("VFMSUB132SD"), 0x29b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 9b /r - VFMSUB132SD xmm, vex128, xmm/m64
    { const_string("VFMSUB132SS"), 0x29b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 9b /r - VFMSUB132SS xmm, vex128, xmm/m32
    { const_string("VFMSUB132SD"), 0x29b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 9b /r - VFMSUB132SD xmm, vex128, xmm/m64
    { const_string("VFNMADD132PS"), 0x29c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 9c /r - VFNMADD132PS xmm, vex128, xmm/m128
    { const_string("VFNMADD132PD"), 0x29c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 9c /r - VFNMADD132PD xmm, vex128, xmm/m128
    { const_string("VFNMADD132PS"), 0x29c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 9c /r - VFNMADD132PS ymm, vex256, ymm/m256
    { const_string("VFNMADD132PD"), 0x29c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 9c /r - VFNMADD132PD ymm, vex256, ymm/m256
    { const_string("VFNMADD132SS"), 0x29d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 9d /r - VFNMADD132SS xmm, vex128, xmm/m32
    { const_string("VFNMADD132SD"), 0x29d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 9d /r - VFNMADD132SD xmm, vex128, xmm/m64
    { const_string("VFNMADD132SS"), 0x29d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 9d /r - VFNMADD132SS xmm, vex128, xmm/m32
    { const_string("VFNMADD132SD"), 0x29d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 9d /r - VFNMADD132SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB132PS"), 0x29e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 9e /r - VFNMSUB132PS xmm, vex128, xmm/m128
    { const_string("VFNMSUB132PD"), 0x29e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 9e /r - VFNMSUB132PD xmm, vex128, xmm/m128
    { const_string("VFNMSUB132PS"), 0x29e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 9e /r - VFNMSUB132PS ymm, vex256, ymm/m256
    { const_string("VFNMSUB132PD"), 0x29e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 9e /r - VFNMSUB132PD ymm, vex256, ymm/m256
    { const_string("VFNMSUB132SS"), 0x29f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 9f /r - VFNMSUB132SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB132SD"), 0x29f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 9f /r - VFNMSUB132SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB132SS"), 0x29f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 9f /r - VFNMSUB132SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB132SD"), 0x29f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 9f /r - VFNMSUB132SD xmm, vex128, xmm/m64
    { const_string("VFMADDSUB213PS"), 0x2a6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 a6 /r - VFMADDSUB213PS xmm, vex128, xmm/m128
    { const_string("VFMADDSUB213PD"), 0x2a6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 a6 /r - VFMADDSUB213PD xmm, vex128, xmm/m128
    { const_string("VFMADDSUB213PS"), 0x2a6, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 a6 /r - VFMADDSUB213PS ymm, vex256, ymm/m256
    { const_string("VFMADDSUB213PD"), 0x2a6, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 a6 /r - VFMADDSUB213PD ymm, vex256, ymm/m256
    { const_string("VFMSUBADD213PS"), 0x2a7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 a7 /r - VFMSUBADD213PS xmm, vex128, xmm/m128
    { const_string("VFMSUBADD213PD"), 0x2a7, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 a7 /r - VFMSUBADD213PD xmm, vex128, xmm/m128
    { const_string("VFMSUBADD213PS"), 0x2a7, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 a7 /r - VFMSUBADD213PS ymm, vex256, ymm/m256
    { const_string("VFMSUBADD213PD"), 0x2a7, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 a7 /r - VFMSUBADD213PD ymm, vex256, ymm/m256
    { const_string("VFMADD213PS"), 0x2a8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 a8 /r - VFMADD213PS xmm, vex128, xmm/m128
    { const_string("VFMADD213PD"), 0x2a8, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 a8 /r - VFMADD213PD xmm, vex128, xmm/m128
    { const_string("VFMADD213PS"), 0x2a8, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 a8 /r - VFMADD213PS ymm, vex256, ymm/m256
    { const_string("VFMADD213PD"), 0x2a8, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 a8 /r - VFMADD213PD ymm, vex256, ymm/m256
    { const_string("VFMADD213SS"), 0x2a9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 a9 /r - VFMADD213SS xmm, vex128, xmm/m32
    { const_string("VFMADD213SD"), 0x2a9, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 a9 /r - VFMADD213SD xmm, vex128, xmm/m64
    { const_string("VFMADD213SS"), 0x2a9, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 a9 /r - VFMADD213SS xmm, vex128, xmm/m32
    { const_string("VFMADD213SD"), 0x2a9, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 a9 /r - VFMADD213SD xmm, vex128, xmm/m64
    { const_string("VFMSUB213PS"), 0x2aa, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 aa /r - VFMSUB213PS xmm, vex128, xmm/m128
    { const_string("VFMSUB213PD"), 0x2aa, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 aa /r - VFMSUB213PD xmm, vex128, xmm/m128
    { const_string("VFMSUB213PS"), 0x2aa, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 aa /r - VFMSUB213PS ymm, vex256, ymm/m256
    { const_string("VFMSUB213PD"), 0x2aa, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 aa /r - VFMSUB213PD ymm, vex256, ymm/m256
    { const_string("VFMSUB213SS"), 0x2ab, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 ab /r - VFMSUB213SS xmm, vex128, xmm/m32
    { const_string("VFMSUB213SD"), 0x2ab, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 ab /r - VFMSUB213SD xmm, vex128, xmm/m64
    { const_string("VFMSUB213SS"), 0x2ab, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 ab /r - VFMSUB213SS xmm, vex128, xmm/m32
    { const_string("VFMSUB213SD"), 0x2ab, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 ab /r - VFMSUB213SD xmm, vex128, xmm/m64
    { const_string("VFNMADD213PS"), 0x2ac, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 ac /r - VFNMADD213PS xmm, vex128, xmm/m128
    { const_string("VFNMADD213PD"), 0x2ac, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 ac /r - VFNMADD213PD xmm, vex128, xmm/m128
    { const_string("VFNMADD213PS"), 0x2ac, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 ac /r - VFNMADD213PS ymm, vex256, ymm/m256
    { const_string("VFNMADD213PD"), 0x2ac, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 ac /r - VFNMADD213PD ymm, vex256, ymm/m256
    { const_string("VFNMADD213SS"), 0x2ad, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 ad /r - VFNMADD213SS xmm, vex128, xmm/m32
    { const_string("VFNMADD213SD"), 0x2ad, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 ad /r - VFNMADD213SD xmm, vex128, xmm/m64
    { const_string("VFNMADD213SS"), 0x2ad, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 ad /r - VFNMADD213SS xmm, vex128, xmm/m32
    { const_string("VFNMADD213SD"), 0x2ad, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 ad /r - VFNMADD213SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB213PS"), 0x2ae, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 ae /r - VFNMSUB213PS xmm, vex128, xmm/m128
    { const_string("VFNMSUB213PD"), 0x2ae, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 ae /r - VFNMSUB213PD xmm, vex128, xmm/m128
    { const_string("VFNMSUB213PS"), 0x2ae, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 ae /r - VFNMSUB213PS ymm, vex256, ymm/m256
    { const_string("VFNMSUB213PD"), 0x2ae, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 ae /r - VFNMSUB213PD ymm, vex256, ymm/m256
    { const_string("VFNMSUB213SS"), 0x2af, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 af /r - VFNMSUB213SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB213SD"), 0x2af, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 af /r - VFNMSUB213SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB213SS"), 0x2af, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 af /r - VFNMSUB213SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB213SD"), 0x2af, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 af /r - VFNMSUB213SD xmm, vex128, xmm/m64
    { const_string("VFMADDSUB231PS"), 0x2b6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 b6 /r - VFMADDSUB231PS xmm, vex128, xmm/m128
    { const_string("VFMADDSUB231PD"), 0x2b6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 b6 /r - VFMADDSUB231PD xmm, vex128, xmm/m128
    { const_string("VFMADDSUB231PS"), 0x2b6, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 b6 /r - VFMADDSUB231PS ymm, vex256, ymm/m256
    { const_string("VFMADDSUB231PD"), 0x2b6, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 b6 /r - VFMADDSUB231PD ymm, vex256, ymm/m256
    { const_string("VFMSUBADD231PS"), 0x2b7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 b7 /r - VFMSUBADD231PS xmm, vex128, xmm/m128
    { const_string("VFMSUBADD231PD"), 0x2b7, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 b7 /r - VFMSUBADD231PD xmm, vex128, xmm/m128
    { const_string("VFMSUBADD231PS"), 0x2b7, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 b7 /r - VFMSUBADD231PS ymm, vex256, ymm/m256
    { const_string("VFMSUBADD231PD"), 0x2b7, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 b7 /r - VFMSUBADD231PD ymm, vex256, ymm/m256
    { const_string("VFMADD231PS"), 0x2b8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 b8 /r - VFMADD231PS xmm, vex128, xmm/m128
    { const_string("VFMADD231PD"), 0x2b8, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 b8 /r - VFMADD231PD xmm, vex128, xmm/m128
    { const_string("VFMADD231PS"), 0x2b8, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 b8 /r - VFMADD231PS ymm, vex256, ymm/m256
    { const_string("VFMADD231PD"), 0x2b8, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 b8 /r - VFMADD231PD ymm, vex256, ymm/m256
    { const_string("VFMADD231SS"), 0x2b9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 b9 /r - VFMADD231SS xmm, vex128, xmm/m32
    { const_string("VFMADD231SD"), 0x2b9, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 b9 /r - VFMADD231SD xmm, vex128, xmm/m64
    { const_string("VFMADD231SS"), 0x2b9, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 b9 /r - VFMADD231SS xmm, vex128, xmm/m32
    { const_string("VFMADD231SD"), 0x2b9, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 b9 /r - VFMADD231SD xmm, vex128, xmm/m64
    { const_string("VFMSUB231PS"), 0x2ba, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 ba /r - VFMSUB231PS xmm, vex128, xmm/m128
    { const_string("VFMSUB231PD"), 0x2ba, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 ba /r - VFMSUB231PD xmm, vex128, xmm/m128
    { const_string("VFMSUB231PS"), 0x2ba, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 ba /r - VFMSUB231PS ymm, vex256, ymm/m256
    { const_string("VFMSUB231PD"), 0x2ba, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 ba /r - VFMSUB231PD ymm, vex256, ymm/m256
    { const_string("VFMSUB231SS"), 0x2bb, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 bb /r - VFMSUB231SS xmm, vex128, xmm/m32
    { const_string("VFMSUB231SD"), 0x2bb, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 bb /r - VFMSUB231SD xmm, vex128, xmm/m64
    { const_string("VFMSUB231SS"), 0x2bb, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 bb /r - VFMSUB231SS xmm, vex128, xmm/m32
    { const_string("VFMSUB231SD"), 0x2bb, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 bb /r - VFMSUB231SD xmm, vex128, xmm/m64
    { const_string("VFNMADD231PS"), 0x2bc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 bc /r - VFNMADD231PS xmm, vex128, xmm/m128
    { const_string("VFNMADD231PD"), 0x2bc, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 bc /r - VFNMADD231PD xmm, vex128, xmm/m128
    { const_string("VFNMADD231PS"), 0x2bc, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 bc /r - VFNMADD231PS ymm, vex256, ymm/m256
    { const_string("VFNMADD231PD"), 0x2bc, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 bc /r - VFNMADD231PD ymm, vex256, ymm/m256
    { const_string("VFNMADD231SS"), 0x2bd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 bd /r - VFNMADD231SS xmm, vex128, xmm/m32
    { const_string("VFNMADD231SD"), 0x2bd, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 bd /r - VFNMADD231SD xmm, vex128, xmm/m64
    { const_string("VFNMADD231SS"), 0x2bd, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 bd /r - VFNMADD231SS xmm, vex128, xmm/m32
    { const_string("VFNMADD231SD"), 0x2bd, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 bd /r - VFNMADD231SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB231PS"), 0x2be, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 be /r - VFNMSUB231PS xmm, vex128, xmm/m128
    { const_string("VFNMSUB231PD"), 0x2be, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 be /r - VFNMSUB231PD xmm, vex128, xmm/m128
    { const_string("VFNMSUB231PS"), 0x2be, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 be /r - VFNMSUB231PS ymm, vex256, ymm/m256
    { const_string("VFNMSUB231PD"), 0x2be, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 be /r - VFNMSUB231PD ymm, vex256, ymm/m256
    { const_string("VFNMSUB231SS"), 0x2bf, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 bf /r - VFNMSUB231SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB231SD"), 0x2bf, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 bf /r - VFNMSUB231SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB231SS"), 0x2bf, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 bf /r - VFNMSUB231SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB231SD"), 0x2bf, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 bf /r - VFNMSUB231SD xmm, vex128, xmm/m64
    { const_string("VGF2P8MULB"), 0x2cf, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 cf /r - VGF2P8MULB xmm, vex128, xmm/m128
    { const_string("VGF2P8MULB"), 0x2cf, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 cf /r - VGF2P8MULB ymm, vex256, ymm/m256
    { const_string("VAESIMC"), 0x2db, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 db /r - VAESIMC xmm, xmm/m128
    { const_string("VAESIMC"), 0x2db, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 db /r - VAESIMC xmm, xmm/m128
    { const_string("VAESENC"), 0x2dc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 dc /r - VAESENC xmm, vex128, xmm/m128
    { const_string("VAESENC"), 0x2dc, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 dc /r - VAESENC xmm, vex128, xmm/m128
    { const_string("VAESENC"), 0x2dc, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 dc /r - VAESENC ymm, vex256, ymm/m256
    { const_string("VAESENC"), 0x2dc, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 dc /r - VAESENC ymm, vex256, ymm/m256
    { const_string("VAESENCLAST"), 0x2dd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 dd /r - VAESENCLAST xmm, vex128, xmm/m128
    { const_string("VAESENCLAST"), 0x2dd, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 dd /r - VAESENCLAST xmm, vex128, xmm/m128
    { const_string("VAESENCLAST"), 0x2dd, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 dd /r - VAESENCLAST ymm, vex256, ymm/m256
    { const_string("VAESENCLAST"), 0x2dd, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 dd /r - VAESENCLAST ymm, vex256, ymm/m256
    { const_string("VAESDEC"), 0x2de, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 de /r - VAESDEC xmm, vex128, xmm/m128
    { const_string("VAESDEC"), 0x2de, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 de /r - VAESDEC xmm, vex128, xmm/m128
    { const_string("VAESDEC"), 0x2de, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 de /r - VAESDEC ymm, vex256, ymm/m256
    { const_string("VAESDEC"), 0x2de, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 de /r - VAESDEC ymm, vex256, ymm/m256
    { const_string("VAESDECLAST"), 0x2df, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 df /r - VAESDECLAST xmm, vex128, xmm/m128
    { const_string("VAESDECLAST"), 0x2df, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 df /r - VAESDECLAST xmm, vex128, xmm/m128
    { const_string("VAESDECLAST"), 0x2df, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W0 df /r - VAESDECLAST ymm, vex256, ymm/m256
    { const_string("VAESDECLAST"), 0x2df, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // VEX.256.66.0F38.W1 df /r - VAESDECLAST ymm, vex256, ymm/m256
    { const_string("ANDN"), 0x2f2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_vex_reg32, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.0F38.W0 f2 /r - ANDN r32, vex32, r/m32
    { const_string("ANDN"), 0x2f2, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_vex_reg64, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.0F38.W1 f2 /r - ANDN r64, vex64, r/m64
    { const_string("BLSR"), 0x2f3, -1, 0, 0, 0, 0, 0, 1, 0, 0, 2, {{OPERAND_vex_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.0F38.W0 f3 /1 - BLSR vex32, r/m32
    { const_string("BLSR"), 0x2f3, -1, 0, 0, 0, 1, 0, 1, 0, 0, 2, {{OPERAND_vex_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.0F38.W1 f3 /1 - BLSR vex64, r/m64
    { const_string("BLSMSK"), 0x2f3, -1, 0, 0, 0, 0, 0, 2, 0, 0, 2, {{OPERAND_vex_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.0F38.W0 f3 /2 - BLSMSK vex32, r/m32
    { const_string("BLSMSK"), 0x2f3, -1, 0, 0, 0, 1, 0, 2, 0, 0, 2, {{OPERAND_vex_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.0F38.W1 f3 /2 - BLSMSK vex64, r/m64
    { const_string("BLSI"), 0x2f3, -1, 0, 0, 0, 0, 0, 3, 0, 0, 2, {{OPERAND_vex_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.0F38.W0 f3 /3 - BLSI vex32, r/m32
    { const_string("BLSI"), 0x2f3, -1, 0, 0, 0, 1, 0, 3, 0, 0, 2, {{OPERAND_vex_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.0F38.W1 f3 /3 - BLSI vex64, r/m64
    { const_string("PEXT"), 0x2f5, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_vex_reg32, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F38.W0 f5 /r - PEXT r32, vex32, r/m32
    { const_string("PEXT"), 0x2f5, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_vex_reg64, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.F3.0F38.W1 f5 /r - PEXT r64, vex64, r/m64
    { const_string("PDEP"), 0x2f5, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_vex_reg32, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.F2.0F38.W0 f5 /r - PDEP r32, vex32, r/m32
    { const_string("PDEP"), 0x2f5, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_vex_reg64, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F38.W1 f5 /r - PDEP r64, vex64, r/m64
    { const_string("BZHI"), 0x2f5, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_vex_reg32, OPERAND_FLAG_read}} }, // VEX.128.0F38.W0 f5 /r - BZHI r32, r/m32, vex32
    { const_string("BZHI"), 0x2f5, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_vex_reg64, OPERAND_FLAG_read}} }, // VEX.128.0F38.W1 f5 /r - BZHI r64, r/m64, vex64
    { const_string("MULX"), 0x2f6, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // VEX.128.F2.0F38.W0 f6 /r - MULX r32, r32, r/m32
    { const_string("MULX"), 0x2f6, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F38.W1 f6 /r - MULX r64, r64, r/m64
    { const_string("SARX"), 0x2f7, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_vex_reg32, OPERAND_FLAG_read}} }, // VEX.128.F3.0F38.W0 f7 /r - SARX r32, r/m32, vex32
    { const_string("SARX"), 0x2f7, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_vex_reg64, OPERAND_FLAG_read}} }, // VEX.128.F3.0F38.W1 f7 /r - SARX r64, r/m64, vex64
    { const_string("SHRX"), 0x2f7, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_vex_reg32, OPERAND_FLAG_read}} }, // VEX.128.F2.0F38.W0 f7 /r - SHRX r32, r/m32, vex32
    { const_string("SHRX"), 0x2f7, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_vex_reg64, OPERAND_FLAG_read}} }, // VEX.128.F2.0F38.W1 f7 /r - SHRX r64, r/m64, vex64
    { const_string("SHLX"), 0x2f7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_vex_reg32, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W0 f7 /r - SHLX r32, r/m32, vex32
    { const_string("SHLX"), 0x2f7, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_vex_reg64, OPERAND_FLAG_read}} }, // VEX.128.66.0F38.W1 f7 /r - SHLX r64, r/m64, vex64
    { const_string("BEXTR"), 0x2f7, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_vex_reg32, OPERAND_FLAG_read}} }, // VEX.128.0F38.W0 f7 /r - BEXTR r32, r/m32, vex32
    { const_string("BEXTR"), 0x2f7, -1, 0, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_vex_reg64, OPERAND_FLAG_read}} }, // VEX.128.0F38.W1 f7 /r - BEXTR r64, r/m64, vex64
    { const_string("VPERMQ"), 0x300, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 00 ib /r - VPERMQ ymm, ymm/m256, imm8
    { const_string("VPERMPD"), 0x301, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 01 ib /r - VPERMPD ymm, ymm/m256, imm8
    { const_string("VPBLENDD"), 0x302, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 02 ib /r - VPBLENDD xmm, vex128, xmm/m128, imm8
    { const_string("VPBLENDD"), 0x302, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 02 ib /r - VPBLENDD ymm, vex256, ymm/m256, imm8
    { const_string("VPERMILPS"), 0x304, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 04 ib /r - VPERMILPS xmm, xmm/m128, imm8
    { const_string("VPERMILPS"), 0x304, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 04 ib /r - VPERMILPS ymm, ymm/m256, imm8
    { const_string("VPERMILPD"), 0x305, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 05 ib /r - VPERMILPD xmm, xmm/m128, imm8
    { const_string("VPERMILPD"), 0x305, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 05 ib /r - VPERMILPD ymm, ymm/m256, imm8
    { const_string("VPERM2F128"), 0x306, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 06 ib /r - VPERM2F128 ymm, vex256, ymm/m256, imm8
    { const_string("VROUNDPS"), 0x308, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 08 ib /r - VROUNDPS xmm, xmm/m128, imm8
    { const_string("VROUNDPS"), 0x308, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 08 ib /r - VROUNDPS xmm, xmm/m128, imm8
    { const_string("VROUNDPS"), 0x308, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 08 ib /r - VROUNDPS ymm, ymm/m256, imm8
    { const_string("VROUNDPS"), 0x308, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 08 ib /r - VROUNDPS ymm, ymm/m256, imm8
    { const_string("VROUNDPD"), 0x309, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 09 ib /r - VROUNDPD xmm, xmm/m128, imm8
    { const_string("VROUNDPD"), 0x309, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 09 ib /r - VROUNDPD xmm, xmm/m128, imm8
    { const_string("VROUNDPD"), 0x309, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 09 ib /r - VROUNDPD ymm, ymm/m256, imm8
    { const_string("VROUNDPD"), 0x309, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 09 ib /r - VROUNDPD ymm, ymm/m256, imm8
    { const_string("VROUNDSS"), 0x30a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 0a ib /r - VROUNDSS xmm, vex128, xmm/m32, imm8
    { const_string("VROUNDSS"), 0x30a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 0a ib /r - VROUNDSS xmm, vex128, xmm/m32, imm8
    { const_string("VROUNDSS"), 0x30a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 0a ib /r - VROUNDSS xmm, vex128, xmm/m32, imm8
    { const_string("VROUNDSS"), 0x30a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 0a ib /r - VROUNDSS xmm, vex128, xmm/m32, imm8
    { const_string("VROUNDSD"), 0x30b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 0b ib /r - VROUNDSD xmm, vex128, xmm/m64, imm8
    { const_string("VROUNDSD"), 0x30b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 0b ib /r - VROUNDSD xmm, vex128, xmm/m64, imm8
    { const_string("VROUNDSD"), 0x30b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 0b ib /r - VROUNDSD xmm, vex128, xmm/m64, imm8
    { const_string("VROUNDSD"), 0x30b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 0b ib /r - VROUNDSD xmm, vex128, xmm/m64, imm8
    { const_string("VBLENDPS"), 0x30c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 0c ib /r - VBLENDPS xmm, vex128, xmm/m128, imm8
    { const_string("VBLENDPS"), 0x30c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 0c ib /r - VBLENDPS xmm, vex128, xmm/m128, imm8
    { const_string("VBLENDPS"), 0x30c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 0c ib /r - VBLENDPS ymm, vex256, ymm/m256, imm8
    { const_string("VBLENDPS"), 0x30c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 0c ib /r - VBLENDPS ymm, vex256, ymm/m256, imm8
    { const_string("VBLENDPD"), 0x30d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 0d ib /r - VBLENDPD xmm, vex128, xmm/m128, imm8
    { const_string("VBLENDPD"), 0x30d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 0d ib /r - VBLENDPD xmm, vex128, xmm/m128, imm8
    { const_string("VBLENDPD"), 0x30d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 0d ib /r - VBLENDPD ymm, vex256, ymm/m256, imm8
    { const_string("VBLENDPD"), 0x30d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 0d ib /r - VBLENDPD ymm, vex256, ymm/m256, imm8
    { const_string("VPBLENDW"), 0x30e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 0e ib /r - VPBLENDW xmm, vex128, xmm/m128, imm8
    { const_string("VPBLENDW"), 0x30e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 0e ib /r - VPBLENDW xmm, vex128, xmm/m128, imm8
    { const_string("VPBLENDW"), 0x30e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 0e ib /r - VPBLENDW ymm, vex256, ymm/m256, imm8
    { const_string("VPBLENDW"), 0x30e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 0e ib /r - VPBLENDW ymm, vex256, ymm/m256, imm8
    { const_string("VPALIGNR"), 0x30f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 0f ib /r - VPALIGNR xmm, vex128, xmm/m128, imm8
    { const_string("VPALIGNR"), 0x30f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 0f ib /r - VPALIGNR xmm, vex128, xmm/m128, imm8
    { const_string("VPALIGNR"), 0x30f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 0f ib /r - VPALIGNR ymm, vex256, ymm/m256, imm8
    { const_string("VPALIGNR"), 0x30f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 0f ib /r - VPALIGNR ymm, vex256, ymm/m256, imm8
    { const_string("VPEXTRB"), 0x314, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm8_zero_extended, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 14 ib /r - VPEXTRB reg/m8, xmm, imm8
    { const_string("VPEXTRW"), 0x315, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm16_zero_extended, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 15 ib /r - VPEXTRW reg/m16, xmm, imm8
    { const_string("VPEXTRD"), 0x316, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 16 ib /r - VPEXTRD r/m32, xmm, imm8
    { const_string("VPEXTRQ"), 0x316, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 16 ib /r - VPEXTRQ r/m64, xmm, imm8
    { const_string("VEXTRACTPS"), 0x317, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 17 ib /r - VEXTRACTPS r/m32, xmm, imm8
    { const_string("VEXTRACTPS"), 0x317, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 17 ib /r - VEXTRACTPS r/m32, xmm, imm8
    { const_string("VINSERTF128"), 0x318, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 18 ib /r - VINSERTF128 ymm, vex256, xmm/m128, imm8
    { const_string("VEXTRACTF128"), 0x319, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 19 ib /r - VEXTRACTF128 xmm/m128, ymm, imm8
    { const_string("VCVTPS2PH"), 0x31d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 1d ib /r - VCVTPS2PH xmm/m64, xmm, imm8
    { const_string("VCVTPS2PH"), 0x31d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 1d ib /r - VCVTPS2PH xmm/m128, ymm, imm8
    { const_string("VPINSRB"), 0x320, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm8_zero_extended, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 20 ib /r - VPINSRB xmm, vex128, reg/m8, imm8
    { const_string("VINSERTPS"), 0x321, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 21 ib /r - VINSERTPS xmm, vex128, xmm/m32, imm8
    { const_string("VINSERTPS"), 0x321, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 21 ib /r - VINSERTPS xmm, vex128, xmm/m32, imm8
    { const_string("VPINSRD"), 0x322, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 22 ib /r - VPINSRD xmm, vex128, r/m32, imm8
    { const_string("VPINSRQ"), 0x322, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 22 ib /r - VPINSRQ xmm, vex128, r/m64, imm8
    { const_string("KSHIFTRB"), 0x330, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 30 /r - KSHIFTRB k, k/m64, imm8
    { const_string("KSHIFTRW"), 0x330, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 30 /r - KSHIFTRW k, k/m64, imm8
    { const_string("KSHIFTRD"), 0x331, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 31 /r - KSHIFTRD k, k/m64, imm8
    { const_string("KSHIFTRQ"), 0x331, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 31 /r - KSHIFTRQ k, k/m64, imm8
    { const_string("KSHIFTLB"), 0x332, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 32 /r - KSHIFTLB k, k/m64, imm8
    { const_string("KSHIFTLW"), 0x332, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 32 /r - KSHIFTLW k, k/m64, imm8
    { const_string("KSHIFTLD"), 0x333, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 33 /r - KSHIFTLD k, k/m64, imm8
    { const_string("KSHIFTLQ"), 0x333, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 33 /r - KSHIFTLQ k, k/m64, imm8
    { const_string("VINSERTI128"), 0x338, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 38 ib /r - VINSERTI128 ymm, vex256, xmm/m128, imm8
    { const_string("VEXTRACTI128"), 0x339, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 39 ib /r - VEXTRACTI128 xmm/m128, ymm, imm8
    { const_string("VDPPS"), 0x340, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 40 ib /r - VDPPS xmm, vex128, xmm/m128, imm8
    { const_string("VDPPS"), 0x340, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 40 ib /r - VDPPS xmm, vex128, xmm/m128, imm8
    { const_string("VDPPS"), 0x340, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 40 ib /r - VDPPS ymm, vex256, ymm/m256, imm8
    { const_string("VDPPS"), 0x340, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 40 ib /r - VDPPS ymm, vex256, ymm/m256, imm8
    { const_string("VDPPD"), 0x341, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 41 ib /r - VDPPD xmm, vex128, xmm/m128, imm8
    { const_string("VDPPD"), 0x341, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 41 ib /r - VDPPD xmm, vex128, xmm/m128, imm8
    { const_string("VMPSADBW"), 0x342, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 42 ib /r - VMPSADBW xmm, vex128, xmm/m128, imm8
    { const_string("VMPSADBW"), 0x342, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 42 ib /r - VMPSADBW xmm, vex128, xmm/m128, imm8
    { const_string("VMPSADBW"), 0x342, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 42 ib /r - VMPSADBW ymm, vex256, ymm/m256, imm8
    { const_string("VMPSADBW"), 0x342, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 42 ib /r - VMPSADBW ymm, vex256, ymm/m256, imm8
    { const_string("VPCLMULQDQ"), 0x344, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 44 ib /r - VPCLMULQDQ xmm, vex128, xmm/m128, imm8
    { const_string("VPCLMULQDQ"), 0x344, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 44 ib /r - VPCLMULQDQ xmm, vex128, xmm/m128, imm8
    { const_string("VPCLMULQDQ"), 0x344, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 44 ib /r - VPCLMULQDQ ymm, vex256, ymm/m256, imm8
    { const_string("VPCLMULQDQ"), 0x344, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 44 ib /r - VPCLMULQDQ ymm, vex256, ymm/m256, imm8
    { const_string("VPERM2I128"), 0x346, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W0 46 ib /r - VPERM2I128 ymm, vex256, ymm/m256, imm8
    { const_string("VBLENDVPS"), 0x34a, -1, 0, 0, 1, 0, 0, -1, 1, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_xmm, 0}} }, // VEX.128.66.0F3A.W0 4a /is4 /r - VBLENDVPS xmm, vex128, xmm/m128, xmm
    { const_string("VBLENDVPS"), 0x34a, -1, 0, 0, 1, 0, 0, -1, 1, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_ymm, 0}} }, // VEX.256.66.0F3A.W0 4a /is4 /r - VBLENDVPS ymm, vex256, ymm/m256, ymm
    { const_string("VBLENDVPD"), 0x34b, -1, 0, 0, 1, 0, 0, -1, 1, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_xmm, 0}} }, // VEX.128.66.0F3A.W0 4b /is4 /r - VBLENDVPD xmm, vex128, xmm/m128, xmm
    { const_string("VBLENDVPD"), 0x34b, -1, 0, 0, 1, 0, 0, -1, 1, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_ymm, 0}} }, // VEX.256.66.0F3A.W0 4b /is4 /r - VBLENDVPD ymm, vex256, ymm/m256, ymm
    { const_string("VPBLENDVB"), 0x34c, -1, 0, 0, 1, 0, 0, -1, 1, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_xmm, 0}} }, // VEX.128.66.0F3A.W0 4c /is4 /r - VPBLENDVB xmm, vex128, xmm/m128, xmm
    { const_string("VPBLENDVB"), 0x34c, -1, 0, 0, 1, 0, 0, -1, 1, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_ymm, 0}} }, // VEX.256.66.0F3A.W0 4c /is4 /r - VPBLENDVB ymm, vex256, ymm/m256, ymm
    { const_string("VPCMPESTRM"), 0x360, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 60 ib /r - VPCMPESTRM xmm, xmm/m128, imm8
    { const_string("VPCMPESTRM"), 0x360, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 60 ib /r - VPCMPESTRM xmm, xmm/m128, imm8
    { const_string("VPCMPESTRI"), 0x361, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 61 ib /r - VPCMPESTRI xmm, xmm/m128, imm8
    { const_string("VPCMPESTRI"), 0x361, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 61 ib /r - VPCMPESTRI xmm, xmm/m128, imm8
    { const_string("VPCMPISTRM"), 0x362, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 62 ib /r - VPCMPISTRM xmm, xmm/m128, imm8
    { const_string("VPCMPISTRM"), 0x362, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 62 ib /r - VPCMPISTRM xmm, xmm/m128, imm8
    { const_string("VPCMPISTRI"), 0x363, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 63 ib /r - VPCMPISTRI xmm, xmm/m128, imm8
    { const_string("VPCMPISTRI"), 0x363, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 63 ib /r - VPCMPISTRI xmm, xmm/m128, imm8
    { const_string("VGF2P8AFFINEQB"), 0x3ce, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 ce ib /r - VGF2P8AFFINEQB xmm, vex128, xmm/m128, imm8
    { const_string("VGF2P8AFFINEQB"), 0x3ce, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 ce ib /r - VGF2P8AFFINEQB ymm, vex256, ymm/m256, imm8
    { const_string("VGF2P8AFFINEINVQB"), 0x3cf, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 cf ib /r - VGF2P8AFFINEINVQB xmm, vex128, xmm/m128, imm8
    { const_string("VGF2P8AFFINEINVQB"), 0x3cf, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.256.66.0F3A.W1 cf ib /r - VGF2P8AFFINEINVQB ymm, vex256, ymm/m256, imm8
    { const_string("VAESKEYGENASSIST"), 0x3df, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W0 df ib /r - VAESKEYGENASSIST xmm, xmm/m128, imm8
    { const_string("VAESKEYGENASSIST"), 0x3df, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.66.0F3A.W1 df ib /r - VAESKEYGENASSIST xmm, xmm/m128, imm8
    { const_string("RORX"), 0x3f0, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.F2.0F3A.W0 f0 ib /r - RORX r32, r/m32, imm8
    { const_string("RORX"), 0x3f0, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // VEX.128.F2.0F3A.W1 f0 ib /r - RORX r64, r/m64, imm8
};

struct instruction_table_entry evex_instructions[] = {
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_m32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 10 /r - VMOVSS xmm, m32
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 10 /r - VMOVSS xmm, vex128, xmm/m128
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 0, 1, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_m32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 10 /r - VMOVSS xmm, m32
    { const_string("VMOVSS"), 0x110, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 10 /r - VMOVSS xmm, vex128, xmm/m128
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 10 /r - VMOVSD xmm, m64
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 10 /r - VMOVSD xmm, vex128, xmm/m128
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 1, 1, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_m64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 10 /r - VMOVSD xmm, m64
    { const_string("VMOVSD"), 0x110, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 10 /r - VMOVSD xmm, vex128, xmm/m128
    { const_string("VMOVUPD"), 0x110, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 10 /r - VMOVUPD xmm, xmm/m128
    { const_string("VMOVUPD"), 0x110, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 10 /r - VMOVUPD ymm, ymm/m256
    { const_string("VMOVUPD"), 0x110, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 10 /r - VMOVUPD zmm, zmm/m512
    { const_string("VMOVUPS"), 0x110, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 10 /r - VMOVUPS xmm, xmm/m128
    { const_string("VMOVUPS"), 0x110, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 10 /r - VMOVUPS ymm, ymm/m256
    { const_string("VMOVUPS"), 0x110, -1, 0, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 10 /r - VMOVUPS zmm, zmm/m512
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 11 /r - VMOVSS m32, xmm
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 11 /r - VMOVSS xmm/m128, vex128, xmm
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 0, 1, -1, 0, 1, 2, {{OPERAND_m32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 11 /r - VMOVSS m32, xmm
    { const_string("VMOVSS"), 0x111, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 11 /r - VMOVSS xmm/m128, vex128, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 11 /r - VMOVSD m64, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 11 /r - VMOVSD xmm/m128, vex128, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 1, 1, -1, 0, 1, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 11 /r - VMOVSD m64, xmm
    { const_string("VMOVSD"), 0x111, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 11 /r - VMOVSD xmm/m128, vex128, xmm
    { const_string("VMOVUPD"), 0x111, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 11 /r - VMOVUPD xmm/m128, xmm
    { const_string("VMOVUPD"), 0x111, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 11 /r - VMOVUPD ymm/m256, ymm
    { const_string("VMOVUPD"), 0x111, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 11 /r - VMOVUPD zmm/m512, zmm
    { const_string("VMOVUPS"), 0x111, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 11 /r - VMOVUPS xmm/m128, xmm
    { const_string("VMOVUPS"), 0x111, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 11 /r - VMOVUPS ymm/m256, ymm
    { const_string("VMOVUPS"), 0x111, -1, 0, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 11 /r - VMOVUPS zmm/m512, zmm
    { const_string("VMOVSLDUP"), 0x112, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 12 /r - VMOVSLDUP xmm, xmm/m128
    { const_string("VMOVSLDUP"), 0x112, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 12 /r - VMOVSLDUP ymm, ymm/m256
    { const_string("VMOVSLDUP"), 0x112, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W0 12 /r - VMOVSLDUP zmm, zmm/m512
    { const_string("VMOVDDUP"), 0x112, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 12 /r - VMOVDDUP xmm, xmm/m64
    { const_string("VMOVDDUP"), 0x112, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 12 /r - VMOVDDUP ymm, ymm/m256
    { const_string("VMOVDDUP"), 0x112, -1, 1, 0, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F2.0F.W1 12 /r - VMOVDDUP zmm, zmm/m512
    { const_string("VMOVLPD"), 0x112, -1, 0, 0, 1, 1, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 12 /r - VMOVLPD xmm, vex128, m64
    { const_string("VMOVLPS"), 0x112, -1, 0, 0, 0, 0, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 12 /r - VMOVLPS xmm, vex128, m64
    { const_string("VMOVHLPS"), 0x112, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 12 /r - VMOVHLPS xmm, vex128, xmm/m128
    { const_string("VMOVLPD"), 0x113, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 13 /r - VMOVLPD m64, xmm
    { const_string("VMOVLPS"), 0x113, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 13 /r - VMOVLPS m64, xmm
    { const_string("VUNPCKLPD"), 0x114, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 14 /r - VUNPCKLPD xmm, vex128, xmm/m128
    { const_string("VUNPCKLPD"), 0x114, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 14 /r - VUNPCKLPD ymm, vex256, ymm/m256
    { const_string("VUNPCKLPD"), 0x114, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 14 /r - VUNPCKLPD zmm, vex512, zmm/m512
    { const_string("VUNPCKLPS"), 0x114, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 14 /r - VUNPCKLPS xmm, vex128, xmm/m128
    { const_string("VUNPCKLPS"), 0x114, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 14 /r - VUNPCKLPS ymm, vex256, ymm/m256
    { const_string("VUNPCKLPS"), 0x114, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 14 /r - VUNPCKLPS zmm, vex512, zmm/m512
    { const_string("VUNPCKHPD"), 0x115, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 15 /r - VUNPCKHPD xmm, vex128, xmm/m128
    { const_string("VUNPCKHPD"), 0x115, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 15 /r - VUNPCKHPD ymm, vex256, ymm/m256
    { const_string("VUNPCKHPD"), 0x115, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 15 /r - VUNPCKHPD zmm, vex512, zmm/m512
    { const_string("VUNPCKHPS"), 0x115, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 15 /r - VUNPCKHPS xmm, vex128, xmm/m128
    { const_string("VUNPCKHPS"), 0x115, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 15 /r - VUNPCKHPS ymm, vex256, ymm/m256
    { const_string("VUNPCKHPS"), 0x115, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 15 /r - VUNPCKHPS zmm, vex512, zmm/m512
    { const_string("VMOVSHDUP"), 0x116, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 16 /r - VMOVSHDUP xmm, xmm/m128
    { const_string("VMOVSHDUP"), 0x116, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 16 /r - VMOVSHDUP ymm, ymm/m256
    { const_string("VMOVSHDUP"), 0x116, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W0 16 /r - VMOVSHDUP zmm, zmm/m512
    { const_string("VMOVHPD"), 0x116, -1, 0, 0, 1, 1, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 16 /r - VMOVHPD xmm, vex128, m64
    { const_string("VMOVHPS"), 0x116, -1, 0, 0, 0, 0, 1, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_m64, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 16 /r - VMOVHPS xmm, vex128, m64
    { const_string("VMOVLHPS"), 0x116, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 16 /r - VMOVLHPS xmm, vex128, xmm/m128
    { const_string("VMOVHPD"), 0x117, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 17 /r - VMOVHPD m64, xmm
    { const_string("VMOVHPS"), 0x117, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 17 /r - VMOVHPS m64, xmm
    { const_string("VMOVAPD"), 0x128, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 28 /r - VMOVAPD xmm, xmm/m128
    { const_string("VMOVAPD"), 0x128, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 28 /r - VMOVAPD ymm, ymm/m256
    { const_string("VMOVAPD"), 0x128, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 28 /r - VMOVAPD zmm, zmm/m512
    { const_string("VMOVAPS"), 0x128, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 28 /r - VMOVAPS xmm, xmm/m128
    { const_string("VMOVAPS"), 0x128, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 28 /r - VMOVAPS ymm, ymm/m256
    { const_string("VMOVAPS"), 0x128, -1, 0, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 28 /r - VMOVAPS zmm, zmm/m512
    { const_string("VMOVAPD"), 0x129, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 29 /r - VMOVAPD xmm/m128, xmm
    { const_string("VMOVAPD"), 0x129, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 29 /r - VMOVAPD ymm/m256, ymm
    { const_string("VMOVAPD"), 0x129, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 29 /r - VMOVAPD zmm/m512, zmm
    { const_string("VMOVAPS"), 0x129, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 29 /r - VMOVAPS xmm/m128, xmm
    { const_string("VMOVAPS"), 0x129, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 29 /r - VMOVAPS ymm/m256, ymm
    { const_string("VMOVAPS"), 0x129, -1, 0, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 29 /r - VMOVAPS zmm/m512, zmm
    { const_string("VCVTSI2SS"), 0x12a, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 2a /r - VCVTSI2SS xmm, vex128, r/m32
    { const_string("VCVTSI2SS"), 0x12a, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 2a /r - VCVTSI2SS xmm, vex128, r/m64
    { const_string("VCVTSI2SS"), 0x12a, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 2a /r - VCVTSI2SS xmm, vex128, r/m32
    { const_string("VCVTSI2SS"), 0x12a, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W1 2a /r - VCVTSI2SS xmm, vex128, r/m64
    { const_string("VCVTSI2SD"), 0x12a, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W0 2a /r - VCVTSI2SD xmm, vex128, r/m32
    { const_string("VCVTSI2SD"), 0x12a, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 2a /r - VCVTSI2SD xmm, vex128, r/m64
    { const_string("VCVTSI2SD"), 0x12a, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W0 2a /r - VCVTSI2SD xmm, vex128, r/m32
    { const_string("VCVTSI2SD"), 0x12a, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 2a /r - VCVTSI2SD xmm, vex128, r/m64
    { const_string("VMOVNTPD"), 0x12b, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 2b /r - VMOVNTPD m128, xmm
    { const_string("VMOVNTPD"), 0x12b, -1, 0, 0, 1, 1, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 2b /r - VMOVNTPD m256, ymm
    { const_string("VMOVNTPD"), 0x12b, -1, 0, 0, 1, 1, 1, -1, 0, 2, 2, {{OPERAND_m512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 2b /r - VMOVNTPD m512, zmm
    { const_string("VMOVNTPS"), 0x12b, -1, 0, 0, 0, 0, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 2b /r - VMOVNTPS m128, xmm
    { const_string("VMOVNTPS"), 0x12b, -1, 0, 0, 0, 0, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 2b /r - VMOVNTPS m256, ymm
    { const_string("VMOVNTPS"), 0x12b, -1, 0, 0, 0, 0, 1, -1, 0, 2, 2, {{OPERAND_m512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 2b /r - VMOVNTPS m512, zmm
    { const_string("VCVTTSS2SI"), 0x12c, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 2c /r - VCVTTSS2SI r32, xmm/m32
    { const_string("VCVTTSS2SI"), 0x12c, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 2c /r - VCVTTSS2SI r64, xmm/m32
    { const_string("VCVTTSS2SI"), 0x12c, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 2c /r - VCVTTSS2SI r32, xmm/m32
    { const_string("VCVTTSS2SI"), 0x12c, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W1 2c /r - VCVTTSS2SI r64, xmm/m32
    { const_string("VCVTTSD2SI"), 0x12c, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W0 2c /r - VCVTTSD2SI r32, xmm/m64
    { const_string("VCVTTSD2SI"), 0x12c, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 2c /r - VCVTTSD2SI r64, xmm/m64
    { const_string("VCVTTSD2SI"), 0x12c, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W0 2c /r - VCVTTSD2SI r32, xmm/m64
    { const_string("VCVTTSD2SI"), 0x12c, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 2c /r - VCVTTSD2SI r64, xmm/m64
    { const_string("VCVTSS2SI"), 0x12d, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 2d /r - VCVTSS2SI r32, xmm/m32
    { const_string("VCVTSS2SI"), 0x12d, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 2d /r - VCVTSS2SI r64, xmm/m32
    { const_string("VCVTSS2SI"), 0x12d, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 2d /r - VCVTSS2SI r32, xmm/m32
    { const_string("VCVTSS2SI"), 0x12d, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W1 2d /r - VCVTSS2SI r64, xmm/m32
    { const_string("VCVTSD2SI"), 0x12d, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W0 2d /r - VCVTSD2SI r32, xmm/m64
    { const_string("VCVTSD2SI"), 0x12d, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 2d /r - VCVTSD2SI r64, xmm/m64
    { const_string("VCVTSD2SI"), 0x12d, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W0 2d /r - VCVTSD2SI r32, xmm/m64
    { const_string("VCVTSD2SI"), 0x12d, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 2d /r - VCVTSD2SI r64, xmm/m64
    { const_string("VUCOMISD"), 0x12e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 2e /r - VUCOMISD xmm, xmm/m64
    { const_string("VUCOMISD"), 0x12e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 2e /r - VUCOMISD xmm, xmm/m64
    { const_string("VUCOMISS"), 0x12e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 2e /r - VUCOMISS xmm, xmm/m32
    { const_string("VUCOMISS"), 0x12e, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 2e /r - VUCOMISS xmm, xmm/m32
    { const_string("VCOMISD"), 0x12f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 2f /r - VCOMISD xmm, xmm/m64
    { const_string("VCOMISD"), 0x12f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 2f /r - VCOMISD xmm, xmm/m64
    { const_string("VCOMISS"), 0x12f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 2f /r - VCOMISS xmm, xmm/m32
    { const_string("VCOMISS"), 0x12f, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 2f /r - VCOMISS xmm, xmm/m32
    { const_string("VSQRTSS"), 0x151, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 51 /r - VSQRTSS xmm, vex128, xmm/m32
    { const_string("VSQRTSS"), 0x151, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 51 /r - VSQRTSS xmm, vex128, xmm/m32
    { const_string("VSQRTSD"), 0x151, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 51 /r - VSQRTSD xmm, vex128, xmm/m64
    { const_string("VSQRTSD"), 0x151, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 51 /r - VSQRTSD xmm, vex128, xmm/m64
    { const_string("VSQRTPD"), 0x151, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 51 /r - VSQRTPD xmm, xmm/m128
    { const_string("VSQRTPD"), 0x151, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 51 /r - VSQRTPD ymm, ymm/m256
    { const_string("VSQRTPD"), 0x151, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 51 /r - VSQRTPD zmm, zmm/m512
    { const_string("VSQRTPS"), 0x151, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 51 /r - VSQRTPS xmm, xmm/m128
    { const_string("VSQRTPS"), 0x151, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 51 /r - VSQRTPS ymm, ymm/m256
    { const_string("VSQRTPS"), 0x151, -1, 0, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 51 /r - VSQRTPS zmm, zmm/m512
    { const_string("VANDPD"), 0x154, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 54 /r - VANDPD xmm, vex128, xmm/m128
    { const_string("VANDPD"), 0x154, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 54 /r - VANDPD ymm, vex256, ymm/m256
    { const_string("VANDPD"), 0x154, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 54 /r - VANDPD zmm, vex512, zmm/m512
    { const_string("VANDPS"), 0x154, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 54 /r - VANDPS xmm, vex128, xmm/m128
    { const_string("VANDPS"), 0x154, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 54 /r - VANDPS ymm, vex256, ymm/m256
    { const_string("VANDPS"), 0x154, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 54 /r - VANDPS zmm, vex512, zmm/m512
    { const_string("VANDNPD"), 0x155, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 55 /r - VANDNPD xmm, vex128, xmm/m128
    { const_string("VANDNPD"), 0x155, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 55 /r - VANDNPD ymm, vex256, ymm/m256
    { const_string("VANDNPD"), 0x155, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 55 /r - VANDNPD zmm, vex512, zmm/m512
    { const_string("VANDNPS"), 0x155, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 55 /r - VANDNPS xmm, vex128, xmm/m128
    { const_string("VANDNPS"), 0x155, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 55 /r - VANDNPS ymm, vex256, ymm/m256
    { const_string("VANDNPS"), 0x155, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 55 /r - VANDNPS zmm, vex512, zmm/m512
    { const_string("VORPD"), 0x156, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 56 /r - VORPD xmm, vex128, xmm/m128
    { const_string("VORPD"), 0x156, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 56 /r - VORPD ymm, vex256, ymm/m256
    { const_string("VORPD"), 0x156, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 56 /r - VORPD zmm, vex512, zmm/m512
    { const_string("VORPS"), 0x156, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 56 /r - VORPS xmm, vex128, xmm/m128
    { const_string("VORPS"), 0x156, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 56 /r - VORPS ymm, vex256, ymm/m256
    { const_string("VORPS"), 0x156, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 56 /r - VORPS zmm, vex512, zmm/m512
    { const_string("VXORPD"), 0x157, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 57 /r - VXORPD xmm, vex128, xmm/m128
    { const_string("VXORPD"), 0x157, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 57 /r - VXORPD ymm, vex256, ymm/m256
    { const_string("VXORPD"), 0x157, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 57 /r - VXORPD zmm, vex512, zmm/m512
    { const_string("VXORPS"), 0x157, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 57 /r - VXORPS xmm, vex128, xmm/m128
    { const_string("VXORPS"), 0x157, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 57 /r - VXORPS ymm, vex256, ymm/m256
    { const_string("VXORPS"), 0x157, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 57 /r - VXORPS zmm, vex512, zmm/m512
    { const_string("VADDSS"), 0x158, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 58 /r - VADDSS xmm, vex128, xmm/m32
    { const_string("VADDSS"), 0x158, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 58 /r - VADDSS xmm, vex128, xmm/m32
    { const_string("VADDSD"), 0x158, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 58 /r - VADDSD xmm, vex128, xmm/m64
    { const_string("VADDSD"), 0x158, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 58 /r - VADDSD xmm, vex128, xmm/m64
    { const_string("VADDPD"), 0x158, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 58 /r - VADDPD xmm, vex128, xmm/m128
    { const_string("VADDPD"), 0x158, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 58 /r - VADDPD ymm, vex256, ymm/m256
    { const_string("VADDPD"), 0x158, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 58 /r - VADDPD zmm, vex512, zmm/m512
    { const_string("VADDPS"), 0x158, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 58 /r - VADDPS xmm, vex128, xmm/m128
    { const_string("VADDPS"), 0x158, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 58 /r - VADDPS ymm, vex256, ymm/m256
    { const_string("VADDPS"), 0x158, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 58 /r - VADDPS zmm, vex512, zmm/m512
    { const_string("VMULSS"), 0x159, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 59 /r - VMULSS xmm, vex128, xmm/m32
    { const_string("VMULSS"), 0x159, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 59 /r - VMULSS xmm, vex128, xmm/m32
    { const_string("VMULSD"), 0x159, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 59 /r - VMULSD xmm, vex128, xmm/m64
    { const_string("VMULSD"), 0x159, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 59 /r - VMULSD xmm, vex128, xmm/m64
    { const_string("VMULPD"), 0x159, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 59 /r - VMULPD xmm, vex128, xmm/m128
    { const_string("VMULPD"), 0x159, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 59 /r - VMULPD ymm, vex256, ymm/m256
    { const_string("VMULPD"), 0x159, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 59 /r - VMULPD zmm, vex512, zmm/m512
    { const_string("VMULPS"), 0x159, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 59 /r - VMULPS xmm, vex128, xmm/m128
    { const_string("VMULPS"), 0x159, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 59 /r - VMULPS ymm, vex256, ymm/m256
    { const_string("VMULPS"), 0x159, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 59 /r - VMULPS zmm, vex512, zmm/m512
    { const_string("VCVTSS2SD"), 0x15a, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 5a /r - VCVTSS2SD xmm, vex128, xmm/m32
    { const_string("VCVTSS2SD"), 0x15a, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 5a /r - VCVTSS2SD xmm, vex128, xmm/m32
    { const_string("VCVTSD2SS"), 0x15a, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 5a /r - VCVTSD2SS xmm, vex128, xmm/m64
    { const_string("VCVTSD2SS"), 0x15a, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 5a /r - VCVTSD2SS xmm, vex128, xmm/m64
    { const_string("VCVTPD2PS"), 0x15a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 5a /r - VCVTPD2PS xmm, xmm/m128
    { const_string("VCVTPD2PS"), 0x15a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 5a /r - VCVTPD2PS xmm, ymm/m256
    { const_string("VCVTPD2PS"), 0x15a, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 5a /r - VCVTPD2PS ymm, zmm/m512
    { const_string("VCVTPS2PD"), 0x15a, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 5a /r - VCVTPS2PD xmm, xmm/m64
    { const_string("VCVTPS2PD"), 0x15a, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 5a /r - VCVTPS2PD ymm, xmm/m128
    { const_string("VCVTPS2PD"), 0x15a, -1, 0, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 5a /r - VCVTPS2PD zmm, ymm/m256
    { const_string("VCVTTPS2DQ"), 0x15b, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 5b /r - VCVTTPS2DQ xmm, xmm/m128
    { const_string("VCVTTPS2DQ"), 0x15b, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 5b /r - VCVTTPS2DQ ymm, ymm/m256
    { const_string("VCVTTPS2DQ"), 0x15b, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W0 5b /r - VCVTTPS2DQ zmm, zmm/m512
    { const_string("VCVTPS2DQ"), 0x15b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 5b /r - VCVTPS2DQ xmm, xmm/m128
    { const_string("VCVTPS2DQ"), 0x15b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 5b /r - VCVTPS2DQ ymm, ymm/m256
    { const_string("VCVTPS2DQ"), 0x15b, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 5b /r - VCVTPS2DQ zmm, zmm/m512
    { const_string("VCVTDQ2PS"), 0x15b, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 5b /r - VCVTDQ2PS xmm, xmm/m128
    { const_string("VCVTQQ2PS"), 0x15b, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W1 5b /r - VCVTQQ2PS xmm, xmm/m128
    { const_string("VCVTDQ2PS"), 0x15b, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 5b /r - VCVTDQ2PS ymm, ymm/m256
    { const_string("VCVTQQ2PS"), 0x15b, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W1 5b /r - VCVTQQ2PS xmm, ymm/m256
    { const_string("VCVTDQ2PS"), 0x15b, -1, 0, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 5b /r - VCVTDQ2PS zmm, zmm/m512
    { const_string("VCVTQQ2PS"), 0x15b, -1, 0, 0, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W1 5b /r - VCVTQQ2PS ymm, zmm/m512
    { const_string("VSUBSS"), 0x15c, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 5c /r - VSUBSS xmm, vex128, xmm/m32
    { const_string("VSUBSS"), 0x15c, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 5c /r - VSUBSS xmm, vex128, xmm/m32
    { const_string("VSUBSD"), 0x15c, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 5c /r - VSUBSD xmm, vex128, xmm/m64
    { const_string("VSUBSD"), 0x15c, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 5c /r - VSUBSD xmm, vex128, xmm/m64
    { const_string("VSUBPD"), 0x15c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 5c /r - VSUBPD xmm, vex128, xmm/m128
    { const_string("VSUBPD"), 0x15c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 5c /r - VSUBPD ymm, vex256, ymm/m256
    { const_string("VSUBPD"), 0x15c, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 5c /r - VSUBPD zmm, vex512, zmm/m512
    { const_string("VSUBPS"), 0x15c, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 5c /r - VSUBPS xmm, vex128, xmm/m128
    { const_string("VSUBPS"), 0x15c, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 5c /r - VSUBPS ymm, vex256, ymm/m256
    { const_string("VSUBPS"), 0x15c, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 5c /r - VSUBPS zmm, vex512, zmm/m512
    { const_string("VMINSS"), 0x15d, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 5d /r - VMINSS xmm, vex128, xmm/m32
    { const_string("VMINSS"), 0x15d, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 5d /r - VMINSS xmm, vex128, xmm/m32
    { const_string("VMINSD"), 0x15d, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 5d /r - VMINSD xmm, vex128, xmm/m64
    { const_string("VMINSD"), 0x15d, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 5d /r - VMINSD xmm, vex128, xmm/m64
    { const_string("VMINPD"), 0x15d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 5d /r - VMINPD xmm, vex128, xmm/m128
    { const_string("VMINPD"), 0x15d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 5d /r - VMINPD ymm, vex256, ymm/m256
    { const_string("VMINPD"), 0x15d, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 5d /r - VMINPD zmm, vex512, zmm/m512
    { const_string("VMINPS"), 0x15d, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 5d /r - VMINPS xmm, vex128, xmm/m128
    { const_string("VMINPS"), 0x15d, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 5d /r - VMINPS ymm, vex256, ymm/m256
    { const_string("VMINPS"), 0x15d, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 5d /r - VMINPS zmm, vex512, zmm/m512
    { const_string("VDIVSS"), 0x15e, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 5e /r - VDIVSS xmm, vex128, xmm/m32
    { const_string("VDIVSS"), 0x15e, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 5e /r - VDIVSS xmm, vex128, xmm/m32
    { const_string("VDIVSD"), 0x15e, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 5e /r - VDIVSD xmm, vex128, xmm/m64
    { const_string("VDIVSD"), 0x15e, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 5e /r - VDIVSD xmm, vex128, xmm/m64
    { const_string("VDIVPD"), 0x15e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 5e /r - VDIVPD xmm, vex128, xmm/m128
    { const_string("VDIVPD"), 0x15e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 5e /r - VDIVPD ymm, vex256, ymm/m256
    { const_string("VDIVPD"), 0x15e, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 5e /r - VDIVPD zmm, vex512, zmm/m512
    { const_string("VDIVPS"), 0x15e, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 5e /r - VDIVPS xmm, vex128, xmm/m128
    { const_string("VDIVPS"), 0x15e, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 5e /r - VDIVPS ymm, vex256, ymm/m256
    { const_string("VDIVPS"), 0x15e, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 5e /r - VDIVPS zmm, vex512, zmm/m512
    { const_string("VMAXSS"), 0x15f, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 5f /r - VMAXSS xmm, vex128, xmm/m32
    { const_string("VMAXSS"), 0x15f, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 5f /r - VMAXSS xmm, vex128, xmm/m32
    { const_string("VMAXSD"), 0x15f, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 5f /r - VMAXSD xmm, vex128, xmm/m64
    { const_string("VMAXSD"), 0x15f, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 5f /r - VMAXSD xmm, vex128, xmm/m64
    { const_string("VMAXPD"), 0x15f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 5f /r - VMAXPD xmm, vex128, xmm/m128
    { const_string("VMAXPD"), 0x15f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 5f /r - VMAXPD ymm, vex256, ymm/m256
    { const_string("VMAXPD"), 0x15f, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 5f /r - VMAXPD zmm, vex512, zmm/m512
    { const_string("VMAXPS"), 0x15f, -1, 0, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 5f /r - VMAXPS xmm, vex128, xmm/m128
    { const_string("VMAXPS"), 0x15f, -1, 0, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 5f /r - VMAXPS ymm, vex256, ymm/m256
    { const_string("VMAXPS"), 0x15f, -1, 0, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 5f /r - VMAXPS zmm, vex512, zmm/m512
    { const_string("VPUNPCKLBW"), 0x160, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 60 /r - VPUNPCKLBW xmm, vex128, xmm/m128
    { const_string("VPUNPCKLBW"), 0x160, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 60 /r - VPUNPCKLBW xmm, vex128, xmm/m128
    { const_string("VPUNPCKLBW"), 0x160, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 60 /r - VPUNPCKLBW ymm, vex256, ymm/m256
    { const_string("VPUNPCKLBW"), 0x160, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 60 /r - VPUNPCKLBW ymm, vex256, ymm/m256
    { const_string("VPUNPCKLBW"), 0x160, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 60 /r - VPUNPCKLBW zmm, vex512, zmm/m512
    { const_string("VPUNPCKLBW"), 0x160, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 60 /r - VPUNPCKLBW zmm, vex512, zmm/m512
    { const_string("VPUNPCKLWD"), 0x161, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 61 /r - VPUNPCKLWD xmm, vex128, xmm/m128
    { const_string("VPUNPCKLWD"), 0x161, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 61 /r - VPUNPCKLWD xmm, vex128, xmm/m128
    { const_string("VPUNPCKLWD"), 0x161, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 61 /r - VPUNPCKLWD ymm, vex256, ymm/m256
    { const_string("VPUNPCKLWD"), 0x161, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 61 /r - VPUNPCKLWD ymm, vex256, ymm/m256
    { const_string("VPUNPCKLWD"), 0x161, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 61 /r - VPUNPCKLWD zmm, vex512, zmm/m512
    { const_string("VPUNPCKLWD"), 0x161, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 61 /r - VPUNPCKLWD zmm, vex512, zmm/m512
    { const_string("VPUNPCKLDQ"), 0x162, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 62 /r - VPUNPCKLDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKLDQ"), 0x162, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 62 /r - VPUNPCKLDQ ymm, vex256, ymm/m256
    { const_string("VPUNPCKLDQ"), 0x162, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 62 /r - VPUNPCKLDQ zmm, vex512, zmm/m512
    { const_string("VPACKSSWB"), 0x163, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 63 /r - VPACKSSWB xmm, vex128, xmm/m128
    { const_string("VPACKSSWB"), 0x163, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 63 /r - VPACKSSWB xmm, vex128, xmm/m128
    { const_string("VPACKSSWB"), 0x163, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 63 /r - VPACKSSWB ymm, vex256, ymm/m256
    { const_string("VPACKSSWB"), 0x163, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 63 /r - VPACKSSWB ymm, vex256, ymm/m256
    { const_string("VPACKSSWB"), 0x163, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 63 /r - VPACKSSWB zmm, vex512, zmm/m512
    { const_string("VPACKSSWB"), 0x163, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 63 /r - VPACKSSWB zmm, vex512, zmm/m512
    { const_string("VPCMPGTB"), 0x164, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 64 /r - VPCMPGTB k, vex128, xmm/m128
    { const_string("VPCMPGTB"), 0x164, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 64 /r - VPCMPGTB k, vex128, xmm/m128
    { const_string("VPCMPGTB"), 0x164, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 64 /r - VPCMPGTB k, vex256, ymm/m256
    { const_string("VPCMPGTB"), 0x164, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 64 /r - VPCMPGTB k, vex256, ymm/m256
    { const_string("VPCMPGTB"), 0x164, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 64 /r - VPCMPGTB k, vex512, zmm/m512
    { const_string("VPCMPGTB"), 0x164, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 64 /r - VPCMPGTB k, vex512, zmm/m512
    { const_string("VPCMPGTW"), 0x165, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 65 /r - VPCMPGTW k, vex128, xmm/m128
    { const_string("VPCMPGTW"), 0x165, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 65 /r - VPCMPGTW k, vex128, xmm/m128
    { const_string("VPCMPGTW"), 0x165, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 65 /r - VPCMPGTW k, vex256, ymm/m256
    { const_string("VPCMPGTW"), 0x165, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 65 /r - VPCMPGTW k, vex256, ymm/m256
    { const_string("VPCMPGTW"), 0x165, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 65 /r - VPCMPGTW k, vex512, zmm/m512
    { const_string("VPCMPGTW"), 0x165, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 65 /r - VPCMPGTW k, vex512, zmm/m512
    { const_string("VPCMPGTD"), 0x166, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 66 /r - VPCMPGTD k, vex128, xmm/m128
    { const_string("VPCMPGTD"), 0x166, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 66 /r - VPCMPGTD k, vex256, ymm/m256
    { const_string("VPCMPGTD"), 0x166, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 66 /r - VPCMPGTD k, vex512, zmm/m512
    { const_string("VPACKUSWB"), 0x167, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 67 /r - VPACKUSWB xmm, vex128, xmm/m128
    { const_string("VPACKUSWB"), 0x167, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 67 /r - VPACKUSWB xmm, vex128, xmm/m128
    { const_string("VPACKUSWB"), 0x167, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 67 /r - VPACKUSWB ymm, vex256, ymm/m256
    { const_string("VPACKUSWB"), 0x167, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 67 /r - VPACKUSWB ymm, vex256, ymm/m256
    { const_string("VPACKUSWB"), 0x167, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 67 /r - VPACKUSWB zmm, vex512, zmm/m512
    { const_string("VPACKUSWB"), 0x167, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 67 /r - VPACKUSWB zmm, vex512, zmm/m512
    { const_string("VPUNPCKHBW"), 0x168, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 68 /r - VPUNPCKHBW xmm, vex128, xmm/m128
    { const_string("VPUNPCKHBW"), 0x168, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 68 /r - VPUNPCKHBW xmm, vex128, xmm/m128
    { const_string("VPUNPCKHBW"), 0x168, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 68 /r - VPUNPCKHBW ymm, vex256, ymm/m256
    { const_string("VPUNPCKHBW"), 0x168, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 68 /r - VPUNPCKHBW ymm, vex256, ymm/m256
    { const_string("VPUNPCKHBW"), 0x168, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 68 /r - VPUNPCKHBW zmm, vex512, zmm/m512
    { const_string("VPUNPCKHBW"), 0x168, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 68 /r - VPUNPCKHBW zmm, vex512, zmm/m512
    { const_string("VPUNPCKHWD"), 0x169, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 69 /r - VPUNPCKHWD xmm, vex128, xmm/m128
    { const_string("VPUNPCKHWD"), 0x169, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 69 /r - VPUNPCKHWD xmm, vex128, xmm/m128
    { const_string("VPUNPCKHWD"), 0x169, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 69 /r - VPUNPCKHWD ymm, vex256, ymm/m256
    { const_string("VPUNPCKHWD"), 0x169, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 69 /r - VPUNPCKHWD ymm, vex256, ymm/m256
    { const_string("VPUNPCKHWD"), 0x169, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 69 /r - VPUNPCKHWD zmm, vex512, zmm/m512
    { const_string("VPUNPCKHWD"), 0x169, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 69 /r - VPUNPCKHWD zmm, vex512, zmm/m512
    { const_string("VPUNPCKHDQ"), 0x16a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 6a /r - VPUNPCKHDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKHDQ"), 0x16a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 6a /r - VPUNPCKHDQ ymm, vex256, ymm/m256
    { const_string("VPUNPCKHDQ"), 0x16a, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 6a /r - VPUNPCKHDQ zmm, vex512, zmm/m512
    { const_string("VPACKSSDW"), 0x16b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 6b /r - VPACKSSDW xmm, vex128, xmm/m128
    { const_string("VPACKSSDW"), 0x16b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 6b /r - VPACKSSDW ymm, vex256, ymm/m256
    { const_string("VPACKSSDW"), 0x16b, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 6b /r - VPACKSSDW zmm, vex512, zmm/m512
    { const_string("VPUNPCKLQDQ"), 0x16c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 6c /r - VPUNPCKLQDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKLQDQ"), 0x16c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 6c /r - VPUNPCKLQDQ ymm, vex256, ymm/m256
    { const_string("VPUNPCKLQDQ"), 0x16c, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 6c /r - VPUNPCKLQDQ zmm, vex512, zmm/m512
    { const_string("VPUNPCKHQDQ"), 0x16d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 6d /r - VPUNPCKHQDQ xmm, vex128, xmm/m128
    { const_string("VPUNPCKHQDQ"), 0x16d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 6d /r - VPUNPCKHQDQ ymm, vex256, ymm/m256
    { const_string("VPUNPCKHQDQ"), 0x16d, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 6d /r - VPUNPCKHQDQ zmm, vex512, zmm/m512
    { const_string("VMOVD"), 0x16e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 6e /r - VMOVD xmm, r/m32
    { const_string("VMOVQ"), 0x16e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 6e /r - VMOVQ xmm, r/m64
    { const_string("VMOVDQU32"), 0x16f, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 6f /r - VMOVDQU32 xmm, xmm/m128
    { const_string("VMOVDQU64"), 0x16f, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 6f /r - VMOVDQU64 xmm, xmm/m128
    { const_string("VMOVDQU32"), 0x16f, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 6f /r - VMOVDQU32 ymm, ymm/m256
    { const_string("VMOVDQU64"), 0x16f, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W1 6f /r - VMOVDQU64 ymm, ymm/m256
    { const_string("VMOVDQU32"), 0x16f, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W0 6f /r - VMOVDQU32 zmm, zmm/m512
    { const_string("VMOVDQU64"), 0x16f, -1, 0, 1, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W1 6f /r - VMOVDQU64 zmm, zmm/m512
    { const_string("VMOVDQU8"), 0x16f, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W0 6f /r - VMOVDQU8 xmm, xmm/m128
    { const_string("VMOVDQU16"), 0x16f, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 6f /r - VMOVDQU16 xmm, xmm/m128
    { const_string("VMOVDQU8"), 0x16f, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W0 6f /r - VMOVDQU8 ymm, ymm/m256
    { const_string("VMOVDQU16"), 0x16f, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 6f /r - VMOVDQU16 ymm, ymm/m256
    { const_string("VMOVDQU8"), 0x16f, -1, 1, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F2.0F.W0 6f /r - VMOVDQU8 zmm, zmm/m512
    { const_string("VMOVDQU16"), 0x16f, -1, 1, 0, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F2.0F.W1 6f /r - VMOVDQU16 zmm, zmm/m512
    { const_string("VMOVDQA32"), 0x16f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 6f /r - VMOVDQA32 xmm, xmm/m128
    { const_string("VMOVDQA64"), 0x16f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 6f /r - VMOVDQA64 xmm, xmm/m128
    { const_string("VMOVDQA32"), 0x16f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 6f /r - VMOVDQA32 ymm, ymm/m256
    { const_string("VMOVDQA64"), 0x16f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 6f /r - VMOVDQA64 ymm, ymm/m256
    { const_string("VMOVDQA32"), 0x16f, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 6f /r - VMOVDQA32 zmm, zmm/m512
    { const_string("VMOVDQA64"), 0x16f, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 6f /r - VMOVDQA64 zmm, zmm/m512
    { const_string("VPSHUFHW"), 0x170, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.F3.0F.W0 70 ib /r - VPSHUFHW xmm, xmm/m128, imm8
    { const_string("VPSHUFHW"), 0x170, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.F3.0F.W1 70 ib /r - VPSHUFHW xmm, xmm/m128, imm8
    { const_string("VPSHUFHW"), 0x170, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.F3.0F.W0 70 ib /r - VPSHUFHW ymm, ymm/m256, imm8
    { const_string("VPSHUFHW"), 0x170, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.F3.0F.W1 70 ib /r - VPSHUFHW ymm, ymm/m256, imm8
    { const_string("VPSHUFHW"), 0x170, -1, 0, 1, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.F3.0F.W0 70 ib /r - VPSHUFHW zmm, zmm/m512, imm8
    { const_string("VPSHUFHW"), 0x170, -1, 0, 1, 0, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.F3.0F.W1 70 ib /r - VPSHUFHW zmm, zmm/m512, imm8
    { const_string("VPSHUFLW"), 0x170, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.F2.0F.W0 70 ib /r - VPSHUFLW xmm, xmm/m128, imm8
    { const_string("VPSHUFLW"), 0x170, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.F2.0F.W1 70 ib /r - VPSHUFLW xmm, xmm/m128, imm8
    { const_string("VPSHUFLW"), 0x170, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.F2.0F.W0 70 ib /r - VPSHUFLW ymm, ymm/m256, imm8
    { const_string("VPSHUFLW"), 0x170, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.F2.0F.W1 70 ib /r - VPSHUFLW ymm, ymm/m256, imm8
    { const_string("VPSHUFLW"), 0x170, -1, 1, 0, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.F2.0F.W0 70 ib /r - VPSHUFLW zmm, zmm/m512, imm8
    { const_string("VPSHUFLW"), 0x170, -1, 1, 0, 0, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.F2.0F.W1 70 ib /r - VPSHUFLW zmm, zmm/m512, imm8
    { const_string("VPSHUFD"), 0x170, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 70 ib /r - VPSHUFD xmm, xmm/m128, imm8
    { const_string("VPSHUFD"), 0x170, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 70 ib /r - VPSHUFD ymm, ymm/m256, imm8
    { const_string("VPSHUFD"), 0x170, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 70 ib /r - VPSHUFD zmm, zmm/m512, imm8
    { const_string("VPSRLW"), 0x171, -1, 0, 0, 1, 0, 0, 2, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 71 /2 ib - VPSRLW vex128, xmm/m128, imm8
    { const_string("VPSRLW"), 0x171, -1, 0, 0, 1, 1, 0, 2, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 71 /2 ib - VPSRLW vex128, xmm/m128, imm8
    { const_string("VPSRLW"), 0x171, -1, 0, 0, 1, 0, 0, 2, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 71 /2 ib - VPSRLW vex256, ymm/m256, imm8
    { const_string("VPSRLW"), 0x171, -1, 0, 0, 1, 1, 0, 2, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 71 /2 ib - VPSRLW vex256, ymm/m256, imm8
    { const_string("VPSRLW"), 0x171, -1, 0, 0, 1, 0, 0, 2, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 71 /2 ib - VPSRLW vex512, zmm/m512, imm8
    { const_string("VPSRLW"), 0x171, -1, 0, 0, 1, 1, 0, 2, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 71 /2 ib - VPSRLW vex512, zmm/m512, imm8
    { const_string("VPSRAW"), 0x171, -1, 0, 0, 1, 0, 0, 4, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 71 /4 ib - VPSRAW vex128, xmm/m128, imm8
    { const_string("VPSRAW"), 0x171, -1, 0, 0, 1, 1, 0, 4, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 71 /4 ib - VPSRAW vex128, xmm/m128, imm8
    { const_string("VPSRAW"), 0x171, -1, 0, 0, 1, 0, 0, 4, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 71 /4 ib - VPSRAW vex256, ymm/m256, imm8
    { const_string("VPSRAW"), 0x171, -1, 0, 0, 1, 1, 0, 4, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 71 /4 ib - VPSRAW vex256, ymm/m256, imm8
    { const_string("VPSRAW"), 0x171, -1, 0, 0, 1, 0, 0, 4, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 71 /4 ib - VPSRAW vex512, zmm/m512, imm8
    { const_string("VPSRAW"), 0x171, -1, 0, 0, 1, 1, 0, 4, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 71 /4 ib - VPSRAW vex512, zmm/m512, imm8
    { const_string("VPSLLW"), 0x171, -1, 0, 0, 1, 0, 0, 6, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 71 /6 ib - VPSLLW vex128, xmm/m128, imm8
    { const_string("VPSLLW"), 0x171, -1, 0, 0, 1, 1, 0, 6, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 71 /6 ib - VPSLLW vex128, xmm/m128, imm8
    { const_string("VPSLLW"), 0x171, -1, 0, 0, 1, 0, 0, 6, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 71 /6 ib - VPSLLW vex256, ymm/m256, imm8
    { const_string("VPSLLW"), 0x171, -1, 0, 0, 1, 1, 0, 6, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 71 /6 ib - VPSLLW vex256, ymm/m256, imm8
    { const_string("VPSLLW"), 0x171, -1, 0, 0, 1, 0, 0, 6, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 71 /6 ib - VPSLLW vex512, zmm/m512, imm8
    { const_string("VPSLLW"), 0x171, -1, 0, 0, 1, 1, 0, 6, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 71 /6 ib - VPSLLW vex512, zmm/m512, imm8
    { const_string("VPRORD"), 0x172, -1, 0, 0, 1, 0, 0, 0, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 72 /0 ib - VPRORD vex128, xmm/m128, imm8
    { const_string("VPRORQ"), 0x172, -1, 0, 0, 1, 1, 0, 0, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 72 /0 ib - VPRORQ vex128, xmm/m128, imm8
    { const_string("VPRORD"), 0x172, -1, 0, 0, 1, 0, 0, 0, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 72 /0 ib - VPRORD vex256, ymm/m256, imm8
    { const_string("VPRORQ"), 0x172, -1, 0, 0, 1, 1, 0, 0, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 72 /0 ib - VPRORQ vex256, ymm/m256, imm8
    { const_string("VPRORD"), 0x172, -1, 0, 0, 1, 0, 0, 0, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 72 /0 ib - VPRORD vex512, zmm/m512, imm8
    { const_string("VPRORQ"), 0x172, -1, 0, 0, 1, 1, 0, 0, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 72 /0 ib - VPRORQ vex512, zmm/m512, imm8
    { const_string("VPROLD"), 0x172, -1, 0, 0, 1, 0, 0, 1, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 72 /1 ib - VPROLD vex128, xmm/m128, imm8
    { const_string("VPROLQ"), 0x172, -1, 0, 0, 1, 1, 0, 1, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 72 /1 ib - VPROLQ vex128, xmm/m128, imm8
    { const_string("VPROLD"), 0x172, -1, 0, 0, 1, 0, 0, 1, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 72 /1 ib - VPROLD vex256, ymm/m256, imm8
    { const_string("VPROLQ"), 0x172, -1, 0, 0, 1, 1, 0, 1, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 72 /1 ib - VPROLQ vex256, ymm/m256, imm8
    { const_string("VPROLD"), 0x172, -1, 0, 0, 1, 0, 0, 1, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 72 /1 ib - VPROLD vex512, zmm/m512, imm8
    { const_string("VPROLQ"), 0x172, -1, 0, 0, 1, 1, 0, 1, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 72 /1 ib - VPROLQ vex512, zmm/m512, imm8
    { const_string("VPSRLD"), 0x172, -1, 0, 0, 1, 0, 0, 2, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 72 /2 ib - VPSRLD vex128, xmm/m128, imm8
    { const_string("VPSRLD"), 0x172, -1, 0, 0, 1, 0, 0, 2, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 72 /2 ib - VPSRLD vex256, ymm/m256, imm8
    { const_string("VPSRLD"), 0x172, -1, 0, 0, 1, 0, 0, 2, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 72 /2 ib - VPSRLD vex512, zmm/m512, imm8
    { const_string("VPSRAD"), 0x172, -1, 0, 0, 1, 0, 0, 4, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 72 /4 ib - VPSRAD vex128, xmm/m128, imm8
    { const_string("VPSRAQ"), 0x172, -1, 0, 0, 1, 1, 0, 4, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 72 /4 ib - VPSRAQ vex128, xmm/m128, imm8
    { const_string("VPSRAD"), 0x172, -1, 0, 0, 1, 0, 0, 4, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 72 /4 ib - VPSRAD vex256, ymm/m256, imm8
    { const_string("VPSRAQ"), 0x172, -1, 0, 0, 1, 1, 0, 4, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 72 /4 ib - VPSRAQ vex256, ymm/m256, imm8
    { const_string("VPSRAD"), 0x172, -1, 0, 0, 1, 0, 0, 4, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 72 /4 ib - VPSRAD vex512, zmm/m512, imm8
    { const_string("VPSRAQ"), 0x172, -1, 0, 0, 1, 1, 0, 4, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 72 /4 ib - VPSRAQ vex512, zmm/m512, imm8
    { const_string("VPSLLD"), 0x172, -1, 0, 0, 1, 0, 0, 6, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 72 /6 ib - VPSLLD vex128, xmm/m128, imm8
    { const_string("VPSLLD"), 0x172, -1, 0, 0, 1, 0, 0, 6, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 72 /6 ib - VPSLLD vex256, ymm/m256, imm8
    { const_string("VPSLLD"), 0x172, -1, 0, 0, 1, 0, 0, 6, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 72 /6 ib - VPSLLD vex512, zmm/m512, imm8
    { const_string("VPSRLQ"), 0x173, -1, 0, 0, 1, 1, 0, 2, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 73 /2 ib - VPSRLQ vex128, xmm/m128, imm8
    { const_string("VPSRLQ"), 0x173, -1, 0, 0, 1, 1, 0, 2, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 73 /2 ib - VPSRLQ vex256, ymm/m256, imm8
    { const_string("VPSRLQ"), 0x173, -1, 0, 0, 1, 1, 0, 2, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 73 /2 ib - VPSRLQ vex512, zmm/m512, imm8
    { const_string("VPSRLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 3, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 73 /3 ib - VPSRLDQ vex128, xmm/m128, imm8
    { const_string("VPSRLDQ"), 0x173, -1, 0, 0, 1, 1, 0, 3, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 73 /3 ib - VPSRLDQ vex128, xmm/m128, imm8
    { const_string("VPSRLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 3, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 73 /3 ib - VPSRLDQ vex256, ymm/m256, imm8
    { const_string("VPSRLDQ"), 0x173, -1, 0, 0, 1, 1, 0, 3, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 73 /3 ib - VPSRLDQ vex256, ymm/m256, imm8
    { const_string("VPSRLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 3, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 73 /3 ib - VPSRLDQ vex512, zmm/m512, imm8
    { const_string("VPSRLDQ"), 0x173, -1, 0, 0, 1, 1, 0, 3, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 73 /3 ib - VPSRLDQ vex512, zmm/m512, imm8
    { const_string("VPSLLQ"), 0x173, -1, 0, 0, 1, 1, 0, 6, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 73 /6 ib - VPSLLQ vex128, xmm/m128, imm8
    { const_string("VPSLLQ"), 0x173, -1, 0, 0, 1, 1, 0, 6, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 73 /6 ib - VPSLLQ vex256, ymm/m256, imm8
    { const_string("VPSLLQ"), 0x173, -1, 0, 0, 1, 1, 0, 6, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 73 /6 ib - VPSLLQ vex512, zmm/m512, imm8
    { const_string("VPSLLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 7, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 73 /7 ib - VPSLLDQ vex128, xmm/m128, imm8
    { const_string("VPSLLDQ"), 0x173, -1, 0, 0, 1, 1, 0, 7, 0, 0, 3, {{OPERAND_vex_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 73 /7 ib - VPSLLDQ vex128, xmm/m128, imm8
    { const_string("VPSLLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 7, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W0 73 /7 ib - VPSLLDQ vex256, ymm/m256, imm8
    { const_string("VPSLLDQ"), 0x173, -1, 0, 0, 1, 1, 0, 7, 0, 1, 3, {{OPERAND_vex_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 73 /7 ib - VPSLLDQ vex256, ymm/m256, imm8
    { const_string("VPSLLDQ"), 0x173, -1, 0, 0, 1, 0, 0, 7, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W0 73 /7 ib - VPSLLDQ vex512, zmm/m512, imm8
    { const_string("VPSLLDQ"), 0x173, -1, 0, 0, 1, 1, 0, 7, 0, 2, 3, {{OPERAND_vex_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 73 /7 ib - VPSLLDQ vex512, zmm/m512, imm8
    { const_string("VPCMPEQB"), 0x174, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 74 /r - VPCMPEQB k, vex128, xmm/m128
    { const_string("VPCMPEQB"), 0x174, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 74 /r - VPCMPEQB k, vex128, xmm/m128
    { const_string("VPCMPEQB"), 0x174, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 74 /r - VPCMPEQB k, vex256, ymm/m256
    { const_string("VPCMPEQB"), 0x174, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 74 /r - VPCMPEQB k, vex256, ymm/m256
    { const_string("VPCMPEQB"), 0x174, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 74 /r - VPCMPEQB k, vex512, zmm/m512
    { const_string("VPCMPEQB"), 0x174, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 74 /r - VPCMPEQB k, vex512, zmm/m512
    { const_string("VPCMPEQW"), 0x175, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 75 /r - VPCMPEQW k, vex128, xmm/m128
    { const_string("VPCMPEQW"), 0x175, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 75 /r - VPCMPEQW k, vex128, xmm/m128
    { const_string("VPCMPEQW"), 0x175, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 75 /r - VPCMPEQW k, vex256, ymm/m256
    { const_string("VPCMPEQW"), 0x175, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 75 /r - VPCMPEQW k, vex256, ymm/m256
    { const_string("VPCMPEQW"), 0x175, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 75 /r - VPCMPEQW k, vex512, zmm/m512
    { const_string("VPCMPEQW"), 0x175, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 75 /r - VPCMPEQW k, vex512, zmm/m512
    { const_string("VPCMPEQD"), 0x176, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 76 /r - VPCMPEQD k, vex128, xmm/m128
    { const_string("VPCMPEQD"), 0x176, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 76 /r - VPCMPEQD k, vex256, ymm/m256
    { const_string("VPCMPEQD"), 0x176, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 76 /r - VPCMPEQD k, vex512, zmm/m512
    { const_string("VCVTTSS2USI"), 0x178, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 78 /r - VCVTTSS2USI r32, xmm/m32
    { const_string("VCVTTSS2USI"), 0x178, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 78 /r - VCVTTSS2USI r64, xmm/m32
    { const_string("VCVTTSS2USI"), 0x178, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 78 /r - VCVTTSS2USI r32, xmm/m32
    { const_string("VCVTTSS2USI"), 0x178, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W1 78 /r - VCVTTSS2USI r64, xmm/m32
    { const_string("VCVTTSD2USI"), 0x178, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W0 78 /r - VCVTTSD2USI r32, xmm/m64
    { const_string("VCVTTSD2USI"), 0x178, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 78 /r - VCVTTSD2USI r64, xmm/m64
    { const_string("VCVTTSD2USI"), 0x178, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W0 78 /r - VCVTTSD2USI r32, xmm/m64
    { const_string("VCVTTSD2USI"), 0x178, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 78 /r - VCVTTSD2USI r64, xmm/m64
    { const_string("VCVTTPS2UQQ"), 0x178, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 78 /r - VCVTTPS2UQQ xmm, xmm/m64
    { const_string("VCVTTPD2UQQ"), 0x178, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 78 /r - VCVTTPD2UQQ xmm, xmm/m128
    { const_string("VCVTTPS2UQQ"), 0x178, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 78 /r - VCVTTPS2UQQ ymm, xmm/m128
    { const_string("VCVTTPD2UQQ"), 0x178, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 78 /r - VCVTTPD2UQQ ymm, ymm/m256
    { const_string("VCVTTPS2UQQ"), 0x178, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 78 /r - VCVTTPS2UQQ zmm, ymm/m256
    { const_string("VCVTTPD2UQQ"), 0x178, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 78 /r - VCVTTPD2UQQ zmm, zmm/m512
    { const_string("VCVTTPS2UDQ"), 0x178, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 78 /r - VCVTTPS2UDQ xmm, xmm/m128
    { const_string("VCVTTPD2UDQ"), 0x178, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W1 78 /r - VCVTTPD2UDQ xmm, xmm/m128
    { const_string("VCVTTPS2UDQ"), 0x178, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 78 /r - VCVTTPS2UDQ ymm, ymm/m256
    { const_string("VCVTTPD2UDQ"), 0x178, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W1 78 /r - VCVTTPD2UDQ xmm, ymm/m256
    { const_string("VCVTTPS2UDQ"), 0x178, -1, 0, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 78 /r - VCVTTPS2UDQ zmm, zmm/m512
    { const_string("VCVTTPD2UDQ"), 0x178, -1, 0, 0, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W1 78 /r - VCVTTPD2UDQ ymm, zmm/m512
    { const_string("VCVTSS2USI"), 0x179, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 79 /r - VCVTSS2USI r32, xmm/m32
    { const_string("VCVTSS2USI"), 0x179, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 79 /r - VCVTSS2USI r64, xmm/m32
    { const_string("VCVTSS2USI"), 0x179, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 79 /r - VCVTSS2USI r32, xmm/m32
    { const_string("VCVTSS2USI"), 0x179, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W1 79 /r - VCVTSS2USI r64, xmm/m32
    { const_string("VCVTSD2USI"), 0x179, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W0 79 /r - VCVTSD2USI r32, xmm/m64
    { const_string("VCVTSD2USI"), 0x179, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 79 /r - VCVTSD2USI r64, xmm/m64
    { const_string("VCVTSD2USI"), 0x179, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_reg32, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W0 79 /r - VCVTSD2USI r32, xmm/m64
    { const_string("VCVTSD2USI"), 0x179, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 79 /r - VCVTSD2USI r64, xmm/m64
    { const_string("VCVTPS2UQQ"), 0x179, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 79 /r - VCVTPS2UQQ xmm, xmm/m64
    { const_string("VCVTPD2UQQ"), 0x179, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 79 /r - VCVTPD2UQQ xmm, xmm/m128
    { const_string("VCVTPS2UQQ"), 0x179, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 79 /r - VCVTPS2UQQ ymm, xmm/m128
    { const_string("VCVTPD2UQQ"), 0x179, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 79 /r - VCVTPD2UQQ ymm, ymm/m256
    { const_string("VCVTPS2UQQ"), 0x179, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 79 /r - VCVTPS2UQQ zmm, ymm/m256
    { const_string("VCVTPD2UQQ"), 0x179, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 79 /r - VCVTPD2UQQ zmm, zmm/m512
    { const_string("VCVTPS2UDQ"), 0x179, -1, 0, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W0 79 /r - VCVTPS2UDQ xmm, xmm/m128
    { const_string("VCVTPD2UDQ"), 0x179, -1, 0, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.0F.W1 79 /r - VCVTPD2UDQ xmm, xmm/m128
    { const_string("VCVTPS2UDQ"), 0x179, -1, 0, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W0 79 /r - VCVTPS2UDQ ymm, ymm/m256
    { const_string("VCVTPD2UDQ"), 0x179, -1, 0, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.0F.W1 79 /r - VCVTPD2UDQ xmm, ymm/m256
    { const_string("VCVTPS2UDQ"), 0x179, -1, 0, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W0 79 /r - VCVTPS2UDQ zmm, zmm/m512
    { const_string("VCVTPD2UDQ"), 0x179, -1, 0, 0, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.0F.W1 79 /r - VCVTPD2UDQ ymm, zmm/m512
    { const_string("VCVTUDQ2PD"), 0x17a, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 7a /r - VCVTUDQ2PD xmm, xmm/m64
    { const_string("VCVTUQQ2PD"), 0x17a, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 7a /r - VCVTUQQ2PD xmm, xmm/m128
    { const_string("VCVTUDQ2PD"), 0x17a, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 7a /r - VCVTUDQ2PD ymm, xmm/m128
    { const_string("VCVTUQQ2PD"), 0x17a, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W1 7a /r - VCVTUQQ2PD ymm, ymm/m256
    { const_string("VCVTUDQ2PD"), 0x17a, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W0 7a /r - VCVTUDQ2PD zmm, ymm/m256
    { const_string("VCVTUQQ2PD"), 0x17a, -1, 0, 1, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W1 7a /r - VCVTUQQ2PD zmm, zmm/m512
    { const_string("VCVTUDQ2PS"), 0x17a, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W0 7a /r - VCVTUDQ2PS xmm, xmm/m128
    { const_string("VCVTUQQ2PS"), 0x17a, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 7a /r - VCVTUQQ2PS xmm, xmm/m128
    { const_string("VCVTUDQ2PS"), 0x17a, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W0 7a /r - VCVTUDQ2PS ymm, ymm/m256
    { const_string("VCVTUQQ2PS"), 0x17a, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 7a /r - VCVTUQQ2PS xmm, ymm/m256
    { const_string("VCVTUDQ2PS"), 0x17a, -1, 1, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F2.0F.W0 7a /r - VCVTUDQ2PS zmm, zmm/m512
    { const_string("VCVTUQQ2PS"), 0x17a, -1, 1, 0, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F2.0F.W1 7a /r - VCVTUQQ2PS ymm, zmm/m512
    { const_string("VCVTTPS2QQ"), 0x17a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 7a /r - VCVTTPS2QQ xmm, xmm/m64
    { const_string("VCVTTPD2QQ"), 0x17a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 7a /r - VCVTTPD2QQ xmm, xmm/m128
    { const_string("VCVTTPS2QQ"), 0x17a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 7a /r - VCVTTPS2QQ ymm, xmm/m128
    { const_string("VCVTTPD2QQ"), 0x17a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 7a /r - VCVTTPD2QQ ymm, ymm/m256
    { const_string("VCVTTPS2QQ"), 0x17a, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 7a /r - VCVTTPS2QQ zmm, ymm/m256
    { const_string("VCVTTPD2QQ"), 0x17a, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 7a /r - VCVTTPD2QQ zmm, zmm/m512
    { const_string("VCVTUSI2SS"), 0x17b, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 7b /r - VCVTUSI2SS xmm, vex128, r/m32
    { const_string("VCVTUSI2SS"), 0x17b, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 7b /r - VCVTUSI2SS xmm, vex128, r/m64
    { const_string("VCVTUSI2SS"), 0x17b, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 7b /r - VCVTUSI2SS xmm, vex128, r/m32
    { const_string("VCVTUSI2SS"), 0x17b, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W1 7b /r - VCVTUSI2SS xmm, vex128, r/m64
    { const_string("VCVTUSI2SD"), 0x17b, -1, 1, 0, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W0 7b /r - VCVTUSI2SD xmm, vex128, r/m32
    { const_string("VCVTUSI2SD"), 0x17b, -1, 1, 0, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 7b /r - VCVTUSI2SD xmm, vex128, r/m64
    { const_string("VCVTUSI2SD"), 0x17b, -1, 1, 0, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W0 7b /r - VCVTUSI2SD xmm, vex128, r/m32
    { const_string("VCVTUSI2SD"), 0x17b, -1, 1, 0, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 7b /r - VCVTUSI2SD xmm, vex128, r/m64
    { const_string("VCVTPS2QQ"), 0x17b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 7b /r - VCVTPS2QQ xmm, xmm/m64
    { const_string("VCVTPD2QQ"), 0x17b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 7b /r - VCVTPD2QQ xmm, xmm/m128
    { const_string("VCVTPS2QQ"), 0x17b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 7b /r - VCVTPS2QQ ymm, xmm/m128
    { const_string("VCVTPD2QQ"), 0x17b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 7b /r - VCVTPD2QQ ymm, ymm/m256
    { const_string("VCVTPS2QQ"), 0x17b, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 7b /r - VCVTPS2QQ zmm, ymm/m256
    { const_string("VCVTPD2QQ"), 0x17b, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 7b /r - VCVTPD2QQ zmm, zmm/m512
    { const_string("VMOVQ"), 0x17e, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 7e /r - VMOVQ xmm, xmm/m64
    { const_string("VMOVD"), 0x17e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 7e /r - VMOVD r/m32, xmm
    { const_string("VMOVQ"), 0x17e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 7e /r - VMOVQ r/m64, xmm
    { const_string("VMOVDQU32"), 0x17f, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 7f /r - VMOVDQU32 xmm/m128, xmm
    { const_string("VMOVDQU64"), 0x17f, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 7f /r - VMOVDQU64 xmm/m128, xmm
    { const_string("VMOVDQU32"), 0x17f, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 7f /r - VMOVDQU32 ymm/m256, ymm
    { const_string("VMOVDQU64"), 0x17f, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W1 7f /r - VMOVDQU64 ymm/m256, ymm
    { const_string("VMOVDQU32"), 0x17f, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W0 7f /r - VMOVDQU32 zmm/m512, zmm
    { const_string("VMOVDQU64"), 0x17f, -1, 0, 1, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W1 7f /r - VMOVDQU64 zmm/m512, zmm
    { const_string("VMOVDQU8"), 0x17f, -1, 1, 0, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W0 7f /r - VMOVDQU8 xmm/m128, xmm
    { const_string("VMOVDQU16"), 0x17f, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 7f /r - VMOVDQU16 xmm/m128, xmm
    { const_string("VMOVDQU8"), 0x17f, -1, 1, 0, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W0 7f /r - VMOVDQU8 ymm/m256, ymm
    { const_string("VMOVDQU16"), 0x17f, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 7f /r - VMOVDQU16 ymm/m256, ymm
    { const_string("VMOVDQU8"), 0x17f, -1, 1, 0, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F2.0F.W0 7f /r - VMOVDQU8 zmm/m512, zmm
    { const_string("VMOVDQU16"), 0x17f, -1, 1, 0, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F2.0F.W1 7f /r - VMOVDQU16 zmm/m512, zmm
    { const_string("VMOVDQA32"), 0x17f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 7f /r - VMOVDQA32 xmm/m128, xmm
    { const_string("VMOVDQA64"), 0x17f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 7f /r - VMOVDQA64 xmm/m128, xmm
    { const_string("VMOVDQA32"), 0x17f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 7f /r - VMOVDQA32 ymm/m256, ymm
    { const_string("VMOVDQA64"), 0x17f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 7f /r - VMOVDQA64 ymm/m256, ymm
    { const_string("VMOVDQA32"), 0x17f, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 7f /r - VMOVDQA32 zmm/m512, zmm
    { const_string("VMOVDQA64"), 0x17f, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 7f /r - VMOVDQA64 zmm/m512, zmm
    { const_string("VCMPSS"), 0x1c2, -1, 0, 1, 0, 0, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.F3.0F.W0 c2 ib /r - VCMPSS k, vex128, xmm/m32, imm8
    { const_string("VCMPSS"), 0x1c2, -1, 0, 1, 0, 0, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.F3.0F.W0 c2 ib /r - VCMPSS k, vex128, xmm/m32, imm8
    { const_string("VCMPSD"), 0x1c2, -1, 1, 0, 0, 1, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.F2.0F.W1 c2 ib /r - VCMPSD k, vex128, xmm/m64, imm8
    { const_string("VCMPSD"), 0x1c2, -1, 1, 0, 0, 1, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.F2.0F.W1 c2 ib /r - VCMPSD k, vex128, xmm/m64, imm8
    { const_string("VCMPPD"), 0x1c2, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 c2 ib /r - VCMPPD k, vex128, xmm/m128, imm8
    { const_string("VCMPPD"), 0x1c2, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 c2 ib /r - VCMPPD k, vex256, ymm/m256, imm8
    { const_string("VCMPPD"), 0x1c2, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 c2 ib /r - VCMPPD k, vex512, zmm/m512, imm8
    { const_string("VCMPPS"), 0x1c2, -1, 0, 0, 0, 0, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.0F.W0 c2 ib /r - VCMPPS k, vex128, xmm/m128, imm8
    { const_string("VCMPPS"), 0x1c2, -1, 0, 0, 0, 0, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.0F.W0 c2 ib /r - VCMPPS k, vex256, ymm/m256, imm8
    { const_string("VCMPPS"), 0x1c2, -1, 0, 0, 0, 0, 0, -1, 0, 2, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.0F.W0 c2 ib /r - VCMPPS k, vex512, zmm/m512, imm8
    { const_string("VPINSRW"), 0x1c4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm16_zero_extended, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 c4 ib /r - VPINSRW xmm, vex128, reg/m16, imm8
    { const_string("VPINSRW"), 0x1c4, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm16_zero_extended, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 c4 ib /r - VPINSRW xmm, vex128, reg/m16, imm8
    { const_string("VPEXTRW"), 0x1c5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W0 c5 ib /r - VPEXTRW r64, xmm/m128, imm8
    { const_string("VPEXTRW"), 0x1c5, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_reg64, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 c5 ib /r - VPEXTRW r64, xmm/m128, imm8
    { const_string("VSHUFPD"), 0x1c6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F.W1 c6 ib /r - VSHUFPD xmm, vex128, xmm/m128, imm8
    { const_string("VSHUFPD"), 0x1c6, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F.W1 c6 ib /r - VSHUFPD ymm, vex256, ymm/m256, imm8
    { const_string("VSHUFPD"), 0x1c6, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F.W1 c6 ib /r - VSHUFPD zmm, vex512, zmm/m512, imm8
    { const_string("VSHUFPS"), 0x1c6, -1, 0, 0, 0, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.0F.W0 c6 ib /r - VSHUFPS xmm, vex128, xmm/m128, imm8
    { const_string("VSHUFPS"), 0x1c6, -1, 0, 0, 0, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.0F.W0 c6 ib /r - VSHUFPS ymm, vex256, ymm/m256, imm8
    { const_string("VSHUFPS"), 0x1c6, -1, 0, 0, 0, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.0F.W0 c6 ib /r - VSHUFPS zmm, vex512, zmm/m512, imm8
    { const_string("VPSRLW"), 0x1d1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 d1 /r - VPSRLW xmm, vex128, xmm/m128
    { const_string("VPSRLW"), 0x1d1, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 d1 /r - VPSRLW xmm, vex128, xmm/m128
    { const_string("VPSRLW"), 0x1d1, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 d1 /r - VPSRLW ymm, vex256, xmm/m128
    { const_string("VPSRLW"), 0x1d1, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 d1 /r - VPSRLW ymm, vex256, xmm/m128
    { const_string("VPSRLW"), 0x1d1, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 d1 /r - VPSRLW zmm, vex512, xmm/m128
    { const_string("VPSRLW"), 0x1d1, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 d1 /r - VPSRLW zmm, vex512, xmm/m128
    { const_string("VPSRLD"), 0x1d2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 d2 /r - VPSRLD xmm, vex128, xmm/m128
    { const_string("VPSRLD"), 0x1d2, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 d2 /r - VPSRLD ymm, vex256, xmm/m128
    { const_string("VPSRLD"), 0x1d2, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 d2 /r - VPSRLD zmm, vex512, xmm/m128
    { const_string("VPSRLQ"), 0x1d3, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 d3 /r - VPSRLQ xmm, vex128, xmm/m128
    { const_string("VPSRLQ"), 0x1d3, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 d3 /r - VPSRLQ ymm, vex256, xmm/m128
    { const_string("VPSRLQ"), 0x1d3, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 d3 /r - VPSRLQ zmm, vex512, xmm/m128
    { const_string("VPADDQ"), 0x1d4, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 d4 /r - VPADDQ xmm, vex128, xmm/m128
    { const_string("VPADDQ"), 0x1d4, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 d4 /r - VPADDQ ymm, vex256, ymm/m256
    { const_string("VPADDQ"), 0x1d4, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 d4 /r - VPADDQ zmm, vex512, zmm/m512
    { const_string("VPMULLW"), 0x1d5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 d5 /r - VPMULLW xmm, vex128, xmm/m128
    { const_string("VPMULLW"), 0x1d5, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 d5 /r - VPMULLW xmm, vex128, xmm/m128
    { const_string("VPMULLW"), 0x1d5, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 d5 /r - VPMULLW ymm, vex256, ymm/m256
    { const_string("VPMULLW"), 0x1d5, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 d5 /r - VPMULLW ymm, vex256, ymm/m256
    { const_string("VPMULLW"), 0x1d5, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 d5 /r - VPMULLW zmm, vex512, zmm/m512
    { const_string("VPMULLW"), 0x1d5, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 d5 /r - VPMULLW zmm, vex512, zmm/m512
    { const_string("VMOVQ"), 0x1d6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 d6 /r - VMOVQ xmm/m64, xmm
    { const_string("VPSUBUSB"), 0x1d8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 d8 /r - VPSUBUSB xmm, vex128, xmm/m128
    { const_string("VPSUBUSB"), 0x1d8, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 d8 /r - VPSUBUSB xmm, vex128, xmm/m128
    { const_string("VPSUBUSB"), 0x1d8, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 d8 /r - VPSUBUSB ymm, vex256, ymm/m256
    { const_string("VPSUBUSB"), 0x1d8, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 d8 /r - VPSUBUSB ymm, vex256, ymm/m256
    { const_string("VPSUBUSB"), 0x1d8, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 d8 /r - VPSUBUSB zmm, vex512, zmm/m512
    { const_string("VPSUBUSB"), 0x1d8, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 d8 /r - VPSUBUSB zmm, vex512, zmm/m512
    { const_string("VPSUBUSW"), 0x1d9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 d9 /r - VPSUBUSW xmm, vex128, xmm/m128
    { const_string("VPSUBUSW"), 0x1d9, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 d9 /r - VPSUBUSW xmm, vex128, xmm/m128
    { const_string("VPSUBUSW"), 0x1d9, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 d9 /r - VPSUBUSW ymm, vex256, ymm/m256
    { const_string("VPSUBUSW"), 0x1d9, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 d9 /r - VPSUBUSW ymm, vex256, ymm/m256
    { const_string("VPSUBUSW"), 0x1d9, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 d9 /r - VPSUBUSW zmm, vex512, zmm/m512
    { const_string("VPSUBUSW"), 0x1d9, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 d9 /r - VPSUBUSW zmm, vex512, zmm/m512
    { const_string("VPMINUB"), 0x1da, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 da /r - VPMINUB xmm, vex128, xmm/m128
    { const_string("VPMINUB"), 0x1da, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 da /r - VPMINUB xmm, vex128, xmm/m128
    { const_string("VPMINUB"), 0x1da, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 da /r - VPMINUB ymm, vex256, ymm/m256
    { const_string("VPMINUB"), 0x1da, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 da /r - VPMINUB ymm, vex256, ymm/m256
    { const_string("VPMINUB"), 0x1da, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 da /r - VPMINUB zmm, vex512, zmm/m512
    { const_string("VPMINUB"), 0x1da, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 da /r - VPMINUB zmm, vex512, zmm/m512
    { const_string("VPANDD"), 0x1db, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 db /r - VPANDD xmm, vex128, xmm/m128
    { const_string("VPANDQ"), 0x1db, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 db /r - VPANDQ xmm, vex128, xmm/m128
    { const_string("VPANDD"), 0x1db, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 db /r - VPANDD ymm, vex256, ymm/m256
    { const_string("VPANDQ"), 0x1db, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 db /r - VPANDQ ymm, vex256, ymm/m256
    { const_string("VPANDD"), 0x1db, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 db /r - VPANDD zmm, vex512, zmm/m512
    { const_string("VPANDQ"), 0x1db, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 db /r - VPANDQ zmm, vex512, zmm/m512
    { const_string("VPADDUSB"), 0x1dc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 dc /r - VPADDUSB xmm, vex128, xmm/m128
    { const_string("VPADDUSB"), 0x1dc, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 dc /r - VPADDUSB xmm, vex128, xmm/m128
    { const_string("VPADDUSB"), 0x1dc, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 dc /r - VPADDUSB ymm, vex256, ymm/m256
    { const_string("VPADDUSB"), 0x1dc, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 dc /r - VPADDUSB ymm, vex256, ymm/m256
    { const_string("VPADDUSB"), 0x1dc, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 dc /r - VPADDUSB zmm, vex512, zmm/m512
    { const_string("VPADDUSB"), 0x1dc, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 dc /r - VPADDUSB zmm, vex512, zmm/m512
    { const_string("VPADDUSW"), 0x1dd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 dd /r - VPADDUSW xmm, vex128, xmm/m128
    { const_string("VPADDUSW"), 0x1dd, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 dd /r - VPADDUSW xmm, vex128, xmm/m128
    { const_string("VPADDUSW"), 0x1dd, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 dd /r - VPADDUSW ymm, vex256, ymm/m256
    { const_string("VPADDUSW"), 0x1dd, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 dd /r - VPADDUSW ymm, vex256, ymm/m256
    { const_string("VPADDUSW"), 0x1dd, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 dd /r - VPADDUSW zmm, vex512, zmm/m512
    { const_string("VPADDUSW"), 0x1dd, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 dd /r - VPADDUSW zmm, vex512, zmm/m512
    { const_string("VPMAXUB"), 0x1de, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 de /r - VPMAXUB xmm, vex128, xmm/m128
    { const_string("VPMAXUB"), 0x1de, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 de /r - VPMAXUB xmm, vex128, xmm/m128
    { const_string("VPMAXUB"), 0x1de, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 de /r - VPMAXUB ymm, vex256, ymm/m256
    { const_string("VPMAXUB"), 0x1de, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 de /r - VPMAXUB ymm, vex256, ymm/m256
    { const_string("VPMAXUB"), 0x1de, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 de /r - VPMAXUB zmm, vex512, zmm/m512
    { const_string("VPMAXUB"), 0x1de, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 de /r - VPMAXUB zmm, vex512, zmm/m512
    { const_string("VPANDND"), 0x1df, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 df /r - VPANDND xmm, vex128, xmm/m128
    { const_string("VPANDNQ"), 0x1df, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 df /r - VPANDNQ xmm, vex128, xmm/m128
    { const_string("VPANDND"), 0x1df, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 df /r - VPANDND ymm, vex256, ymm/m256
    { const_string("VPANDNQ"), 0x1df, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 df /r - VPANDNQ ymm, vex256, ymm/m256
    { const_string("VPANDND"), 0x1df, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 df /r - VPANDND zmm, vex512, zmm/m512
    { const_string("VPANDNQ"), 0x1df, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 df /r - VPANDNQ zmm, vex512, zmm/m512
    { const_string("VPAVGB"), 0x1e0, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 e0 /r - VPAVGB xmm, vex128, xmm/m128
    { const_string("VPAVGB"), 0x1e0, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 e0 /r - VPAVGB xmm, vex128, xmm/m128
    { const_string("VPAVGB"), 0x1e0, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 e0 /r - VPAVGB ymm, vex256, ymm/m256
    { const_string("VPAVGB"), 0x1e0, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 e0 /r - VPAVGB ymm, vex256, ymm/m256
    { const_string("VPAVGB"), 0x1e0, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 e0 /r - VPAVGB zmm, vex512, zmm/m512
    { const_string("VPAVGB"), 0x1e0, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 e0 /r - VPAVGB zmm, vex512, zmm/m512
    { const_string("VPSRAW"), 0x1e1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 e1 /r - VPSRAW xmm, vex128, xmm/m128
    { const_string("VPSRAW"), 0x1e1, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 e1 /r - VPSRAW xmm, vex128, xmm/m128
    { const_string("VPSRAW"), 0x1e1, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 e1 /r - VPSRAW ymm, vex256, xmm/m128
    { const_string("VPSRAW"), 0x1e1, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 e1 /r - VPSRAW ymm, vex256, xmm/m128
    { const_string("VPSRAW"), 0x1e1, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 e1 /r - VPSRAW zmm, vex512, xmm/m128
    { const_string("VPSRAW"), 0x1e1, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 e1 /r - VPSRAW zmm, vex512, xmm/m128
    { const_string("VPSRAD"), 0x1e2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 e2 /r - VPSRAD xmm, vex128, xmm/m128
    { const_string("VPSRAQ"), 0x1e2, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 e2 /r - VPSRAQ xmm, vex128, xmm/m128
    { const_string("VPSRAD"), 0x1e2, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 e2 /r - VPSRAD ymm, vex256, xmm/m128
    { const_string("VPSRAQ"), 0x1e2, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 e2 /r - VPSRAQ ymm, vex256, xmm/m128
    { const_string("VPSRAD"), 0x1e2, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 e2 /r - VPSRAD zmm, vex512, xmm/m128
    { const_string("VPSRAQ"), 0x1e2, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 e2 /r - VPSRAQ zmm, vex512, xmm/m128
    { const_string("VPAVGW"), 0x1e3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 e3 /r - VPAVGW xmm, vex128, xmm/m128
    { const_string("VPAVGW"), 0x1e3, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 e3 /r - VPAVGW xmm, vex128, xmm/m128
    { const_string("VPAVGW"), 0x1e3, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 e3 /r - VPAVGW ymm, vex256, ymm/m256
    { const_string("VPAVGW"), 0x1e3, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 e3 /r - VPAVGW ymm, vex256, ymm/m256
    { const_string("VPAVGW"), 0x1e3, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 e3 /r - VPAVGW zmm, vex512, zmm/m512
    { const_string("VPAVGW"), 0x1e3, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 e3 /r - VPAVGW zmm, vex512, zmm/m512
    { const_string("VPMULHUW"), 0x1e4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 e4 /r - VPMULHUW xmm, vex128, xmm/m128
    { const_string("VPMULHUW"), 0x1e4, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 e4 /r - VPMULHUW xmm, vex128, xmm/m128
    { const_string("VPMULHUW"), 0x1e4, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 e4 /r - VPMULHUW ymm, vex256, ymm/m256
    { const_string("VPMULHUW"), 0x1e4, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 e4 /r - VPMULHUW ymm, vex256, ymm/m256
    { const_string("VPMULHUW"), 0x1e4, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 e4 /r - VPMULHUW zmm, vex512, zmm/m512
    { const_string("VPMULHUW"), 0x1e4, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 e4 /r - VPMULHUW zmm, vex512, zmm/m512
    { const_string("VPMULHW"), 0x1e5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 e5 /r - VPMULHW xmm, vex128, xmm/m128
    { const_string("VPMULHW"), 0x1e5, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 e5 /r - VPMULHW xmm, vex128, xmm/m128
    { const_string("VPMULHW"), 0x1e5, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 e5 /r - VPMULHW ymm, vex256, ymm/m256
    { const_string("VPMULHW"), 0x1e5, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 e5 /r - VPMULHW ymm, vex256, ymm/m256
    { const_string("VPMULHW"), 0x1e5, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 e5 /r - VPMULHW zmm, vex512, zmm/m512
    { const_string("VPMULHW"), 0x1e5, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 e5 /r - VPMULHW zmm, vex512, zmm/m512
    { const_string("VCVTDQ2PD"), 0x1e6, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W0 e6 /r - VCVTDQ2PD xmm, xmm/m64
    { const_string("VCVTQQ2PD"), 0x1e6, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F.W1 e6 /r - VCVTQQ2PD xmm, xmm/m128
    { const_string("VCVTDQ2PD"), 0x1e6, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W0 e6 /r - VCVTDQ2PD ymm, xmm/m128
    { const_string("VCVTQQ2PD"), 0x1e6, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F.W1 e6 /r - VCVTQQ2PD ymm, ymm/m256
    { const_string("VCVTDQ2PD"), 0x1e6, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W0 e6 /r - VCVTDQ2PD zmm, ymm/m256
    { const_string("VCVTQQ2PD"), 0x1e6, -1, 0, 1, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F.W1 e6 /r - VCVTQQ2PD zmm, zmm/m512
    { const_string("VCVTPD2DQ"), 0x1e6, -1, 1, 0, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F2.0F.W1 e6 /r - VCVTPD2DQ xmm, xmm/m128
    { const_string("VCVTPD2DQ"), 0x1e6, -1, 1, 0, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F2.0F.W1 e6 /r - VCVTPD2DQ xmm, ymm/m256
    { const_string("VCVTPD2DQ"), 0x1e6, -1, 1, 0, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F2.0F.W1 e6 /r - VCVTPD2DQ ymm, zmm/m512
    { const_string("VCVTTPD2DQ"), 0x1e6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 e6 /r - VCVTTPD2DQ xmm, xmm/m128
    { const_string("VCVTTPD2DQ"), 0x1e6, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 e6 /r - VCVTTPD2DQ xmm, ymm/m256
    { const_string("VCVTTPD2DQ"), 0x1e6, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 e6 /r - VCVTTPD2DQ ymm, zmm/m512
    { const_string("VMOVNTDQ"), 0x1e7, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 e7 /r - VMOVNTDQ m128, xmm
    { const_string("VMOVNTDQ"), 0x1e7, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 e7 /r - VMOVNTDQ m256, ymm
    { const_string("VMOVNTDQ"), 0x1e7, -1, 0, 0, 1, 0, 1, -1, 0, 2, 2, {{OPERAND_m512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 e7 /r - VMOVNTDQ m512, zmm
    { const_string("VPSUBSB"), 0x1e8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 e8 /r - VPSUBSB xmm, vex128, xmm/m128
    { const_string("VPSUBSB"), 0x1e8, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 e8 /r - VPSUBSB xmm, vex128, xmm/m128
    { const_string("VPSUBSB"), 0x1e8, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 e8 /r - VPSUBSB ymm, vex256, ymm/m256
    { const_string("VPSUBSB"), 0x1e8, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 e8 /r - VPSUBSB ymm, vex256, ymm/m256
    { const_string("VPSUBSB"), 0x1e8, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 e8 /r - VPSUBSB zmm, vex512, zmm/m512
    { const_string("VPSUBSB"), 0x1e8, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 e8 /r - VPSUBSB zmm, vex512, zmm/m512
    { const_string("VPSUBSW"), 0x1e9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 e9 /r - VPSUBSW xmm, vex128, xmm/m128
    { const_string("VPSUBSW"), 0x1e9, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 e9 /r - VPSUBSW xmm, vex128, xmm/m128
    { const_string("VPSUBSW"), 0x1e9, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 e9 /r - VPSUBSW ymm, vex256, ymm/m256
    { const_string("VPSUBSW"), 0x1e9, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 e9 /r - VPSUBSW ymm, vex256, ymm/m256
    { const_string("VPSUBSW"), 0x1e9, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 e9 /r - VPSUBSW zmm, vex512, zmm/m512
    { const_string("VPSUBSW"), 0x1e9, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 e9 /r - VPSUBSW zmm, vex512, zmm/m512
    { const_string("VPMINSW"), 0x1ea, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 ea /r - VPMINSW xmm, vex128, xmm/m128
    { const_string("VPMINSW"), 0x1ea, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 ea /r - VPMINSW xmm, vex128, xmm/m128
    { const_string("VPMINSW"), 0x1ea, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 ea /r - VPMINSW ymm, vex256, ymm/m256
    { const_string("VPMINSW"), 0x1ea, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 ea /r - VPMINSW ymm, vex256, ymm/m256
    { const_string("VPMINSW"), 0x1ea, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 ea /r - VPMINSW zmm, vex512, zmm/m512
    { const_string("VPMINSW"), 0x1ea, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 ea /r - VPMINSW zmm, vex512, zmm/m512
    { const_string("VPORD"), 0x1eb, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 eb /r - VPORD xmm, vex128, xmm/m128
    { const_string("VPORQ"), 0x1eb, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 eb /r - VPORQ xmm, vex128, xmm/m128
    { const_string("VPORD"), 0x1eb, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 eb /r - VPORD ymm, vex256, ymm/m256
    { const_string("VPORQ"), 0x1eb, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 eb /r - VPORQ ymm, vex256, ymm/m256
    { const_string("VPORD"), 0x1eb, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 eb /r - VPORD zmm, vex512, zmm/m512
    { const_string("VPORQ"), 0x1eb, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 eb /r - VPORQ zmm, vex512, zmm/m512
    { const_string("VPADDSB"), 0x1ec, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 ec /r - VPADDSB xmm, vex128, xmm/m128
    { const_string("VPADDSB"), 0x1ec, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 ec /r - VPADDSB xmm, vex128, xmm/m128
    { const_string("VPADDSB"), 0x1ec, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 ec /r - VPADDSB ymm, vex256, ymm/m256
    { const_string("VPADDSB"), 0x1ec, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 ec /r - VPADDSB ymm, vex256, ymm/m256
    { const_string("VPADDSB"), 0x1ec, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 ec /r - VPADDSB zmm, vex512, zmm/m512
    { const_string("VPADDSB"), 0x1ec, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 ec /r - VPADDSB zmm, vex512, zmm/m512
    { const_string("VPADDSW"), 0x1ed, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 ed /r - VPADDSW xmm, vex128, xmm/m128
    { const_string("VPADDSW"), 0x1ed, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 ed /r - VPADDSW xmm, vex128, xmm/m128
    { const_string("VPADDSW"), 0x1ed, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 ed /r - VPADDSW ymm, vex256, ymm/m256
    { const_string("VPADDSW"), 0x1ed, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 ed /r - VPADDSW ymm, vex256, ymm/m256
    { const_string("VPADDSW"), 0x1ed, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 ed /r - VPADDSW zmm, vex512, zmm/m512
    { const_string("VPADDSW"), 0x1ed, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 ed /r - VPADDSW zmm, vex512, zmm/m512
    { const_string("VPMAXSW"), 0x1ee, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 ee /r - VPMAXSW xmm, vex128, xmm/m128
    { const_string("VPMAXSW"), 0x1ee, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 ee /r - VPMAXSW xmm, vex128, xmm/m128
    { const_string("VPMAXSW"), 0x1ee, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 ee /r - VPMAXSW ymm, vex256, ymm/m256
    { const_string("VPMAXSW"), 0x1ee, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 ee /r - VPMAXSW ymm, vex256, ymm/m256
    { const_string("VPMAXSW"), 0x1ee, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 ee /r - VPMAXSW zmm, vex512, zmm/m512
    { const_string("VPMAXSW"), 0x1ee, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 ee /r - VPMAXSW zmm, vex512, zmm/m512
    { const_string("VPXORD"), 0x1ef, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 ef /r - VPXORD xmm, vex128, xmm/m128
    { const_string("VPXORQ"), 0x1ef, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 ef /r - VPXORQ xmm, vex128, xmm/m128
    { const_string("VPXORD"), 0x1ef, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 ef /r - VPXORD ymm, vex256, ymm/m256
    { const_string("VPXORQ"), 0x1ef, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 ef /r - VPXORQ ymm, vex256, ymm/m256
    { const_string("VPXORD"), 0x1ef, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 ef /r - VPXORD zmm, vex512, zmm/m512
    { const_string("VPXORQ"), 0x1ef, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 ef /r - VPXORQ zmm, vex512, zmm/m512
    { const_string("VPSLLW"), 0x1f1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 f1 /r - VPSLLW xmm, vex128, xmm/m128
    { const_string("VPSLLW"), 0x1f1, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 f1 /r - VPSLLW xmm, vex128, xmm/m128
    { const_string("VPSLLW"), 0x1f1, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 f1 /r - VPSLLW ymm, vex256, xmm/m128
    { const_string("VPSLLW"), 0x1f1, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 f1 /r - VPSLLW ymm, vex256, xmm/m128
    { const_string("VPSLLW"), 0x1f1, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 f1 /r - VPSLLW zmm, vex512, xmm/m128
    { const_string("VPSLLW"), 0x1f1, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 f1 /r - VPSLLW zmm, vex512, xmm/m128
    { const_string("VPSLLD"), 0x1f2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 f2 /r - VPSLLD xmm, vex128, xmm/m128
    { const_string("VPSLLD"), 0x1f2, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 f2 /r - VPSLLD ymm, vex256, xmm/m128
    { const_string("VPSLLD"), 0x1f2, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 f2 /r - VPSLLD zmm, vex512, xmm/m128
    { const_string("VPSLLQ"), 0x1f3, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 f3 /r - VPSLLQ xmm, vex128, xmm/m128
    { const_string("VPSLLQ"), 0x1f3, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 f3 /r - VPSLLQ ymm, vex256, xmm/m128
    { const_string("VPSLLQ"), 0x1f3, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 f3 /r - VPSLLQ zmm, vex512, xmm/m128
    { const_string("VPMULUDQ"), 0x1f4, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 f4 /r - VPMULUDQ xmm, vex128, xmm/m128
    { const_string("VPMULUDQ"), 0x1f4, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 f4 /r - VPMULUDQ ymm, vex256, ymm/m256
    { const_string("VPMULUDQ"), 0x1f4, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 f4 /r - VPMULUDQ zmm, vex512, zmm/m512
    { const_string("VPMADDWD"), 0x1f5, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 f5 /r - VPMADDWD xmm, vex128, xmm/m128
    { const_string("VPMADDWD"), 0x1f5, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 f5 /r - VPMADDWD xmm, vex128, xmm/m128
    { const_string("VPMADDWD"), 0x1f5, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 f5 /r - VPMADDWD ymm, vex256, ymm/m256
    { const_string("VPMADDWD"), 0x1f5, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 f5 /r - VPMADDWD ymm, vex256, ymm/m256
    { const_string("VPMADDWD"), 0x1f5, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 f5 /r - VPMADDWD zmm, vex512, zmm/m512
    { const_string("VPMADDWD"), 0x1f5, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 f5 /r - VPMADDWD zmm, vex512, zmm/m512
    { const_string("VPSADBW"), 0x1f6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 f6 /r - VPSADBW xmm, vex128, xmm/m128
    { const_string("VPSADBW"), 0x1f6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 f6 /r - VPSADBW xmm, vex128, xmm/m128
    { const_string("VPSADBW"), 0x1f6, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 f6 /r - VPSADBW ymm, vex256, ymm/m256
    { const_string("VPSADBW"), 0x1f6, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 f6 /r - VPSADBW ymm, vex256, ymm/m256
    { const_string("VPSADBW"), 0x1f6, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 f6 /r - VPSADBW zmm, vex512, zmm/m512
    { const_string("VPSADBW"), 0x1f6, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 f6 /r - VPSADBW zmm, vex512, zmm/m512
    { const_string("VPSUBB"), 0x1f8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 f8 /r - VPSUBB xmm, vex128, xmm/m128
    { const_string("VPSUBB"), 0x1f8, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 f8 /r - VPSUBB xmm, vex128, xmm/m128
    { const_string("VPSUBB"), 0x1f8, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 f8 /r - VPSUBB ymm, vex256, ymm/m256
    { const_string("VPSUBB"), 0x1f8, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 f8 /r - VPSUBB ymm, vex256, ymm/m256
    { const_string("VPSUBB"), 0x1f8, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 f8 /r - VPSUBB zmm, vex512, zmm/m512
    { const_string("VPSUBB"), 0x1f8, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 f8 /r - VPSUBB zmm, vex512, zmm/m512
    { const_string("VPSUBW"), 0x1f9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 f9 /r - VPSUBW xmm, vex128, xmm/m128
    { const_string("VPSUBW"), 0x1f9, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 f9 /r - VPSUBW xmm, vex128, xmm/m128
    { const_string("VPSUBW"), 0x1f9, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 f9 /r - VPSUBW ymm, vex256, ymm/m256
    { const_string("VPSUBW"), 0x1f9, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 f9 /r - VPSUBW ymm, vex256, ymm/m256
    { const_string("VPSUBW"), 0x1f9, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 f9 /r - VPSUBW zmm, vex512, zmm/m512
    { const_string("VPSUBW"), 0x1f9, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 f9 /r - VPSUBW zmm, vex512, zmm/m512
    { const_string("VPSUBD"), 0x1fa, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 fa /r - VPSUBD xmm, vex128, xmm/m128
    { const_string("VPSUBD"), 0x1fa, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 fa /r - VPSUBD ymm, vex256, ymm/m256
    { const_string("VPSUBD"), 0x1fa, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 fa /r - VPSUBD zmm, vex512, zmm/m512
    { const_string("VPSUBQ"), 0x1fb, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 fb /r - VPSUBQ xmm, vex128, xmm/m128
    { const_string("VPSUBQ"), 0x1fb, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 fb /r - VPSUBQ ymm, vex256, ymm/m256
    { const_string("VPSUBQ"), 0x1fb, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 fb /r - VPSUBQ zmm, vex512, zmm/m512
    { const_string("VPADDB"), 0x1fc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 fc /r - VPADDB xmm, vex128, xmm/m128
    { const_string("VPADDB"), 0x1fc, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 fc /r - VPADDB xmm, vex128, xmm/m128
    { const_string("VPADDB"), 0x1fc, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 fc /r - VPADDB ymm, vex256, ymm/m256
    { const_string("VPADDB"), 0x1fc, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 fc /r - VPADDB ymm, vex256, ymm/m256
    { const_string("VPADDB"), 0x1fc, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 fc /r - VPADDB zmm, vex512, zmm/m512
    { const_string("VPADDB"), 0x1fc, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 fc /r - VPADDB zmm, vex512, zmm/m512
    { const_string("VPADDW"), 0x1fd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 fd /r - VPADDW xmm, vex128, xmm/m128
    { const_string("VPADDW"), 0x1fd, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W1 fd /r - VPADDW xmm, vex128, xmm/m128
    { const_string("VPADDW"), 0x1fd, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 fd /r - VPADDW ymm, vex256, ymm/m256
    { const_string("VPADDW"), 0x1fd, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W1 fd /r - VPADDW ymm, vex256, ymm/m256
    { const_string("VPADDW"), 0x1fd, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 fd /r - VPADDW zmm, vex512, zmm/m512
    { const_string("VPADDW"), 0x1fd, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W1 fd /r - VPADDW zmm, vex512, zmm/m512
    { const_string("VPADDD"), 0x1fe, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F.W0 fe /r - VPADDD xmm, vex128, xmm/m128
    { const_string("VPADDD"), 0x1fe, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F.W0 fe /r - VPADDD ymm, vex256, ymm/m256
    { const_string("VPADDD"), 0x1fe, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F.W0 fe /r - VPADDD zmm, vex512, zmm/m512
    { const_string("VPSHUFB"), 0x200, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 00 /r - VPSHUFB xmm, vex128, xmm/m128
    { const_string("VPSHUFB"), 0x200, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 00 /r - VPSHUFB xmm, vex128, xmm/m128
    { const_string("VPSHUFB"), 0x200, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 00 /r - VPSHUFB ymm, vex256, ymm/m256
    { const_string("VPSHUFB"), 0x200, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 00 /r - VPSHUFB ymm, vex256, ymm/m256
    { const_string("VPSHUFB"), 0x200, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 00 /r - VPSHUFB zmm, vex512, zmm/m512
    { const_string("VPSHUFB"), 0x200, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 00 /r - VPSHUFB zmm, vex512, zmm/m512
    { const_string("VPMADDUBSW"), 0x204, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 04 /r - VPMADDUBSW xmm, vex128, xmm/m128
    { const_string("VPMADDUBSW"), 0x204, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 04 /r - VPMADDUBSW xmm, vex128, xmm/m128
    { const_string("VPMADDUBSW"), 0x204, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 04 /r - VPMADDUBSW ymm, vex256, ymm/m256
    { const_string("VPMADDUBSW"), 0x204, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 04 /r - VPMADDUBSW ymm, vex256, ymm/m256
    { const_string("VPMADDUBSW"), 0x204, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 04 /r - VPMADDUBSW zmm, vex512, zmm/m512
    { const_string("VPMADDUBSW"), 0x204, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 04 /r - VPMADDUBSW zmm, vex512, zmm/m512
    { const_string("VPMULHRSW"), 0x20b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 0b /r - VPMULHRSW xmm, vex128, xmm/m128
    { const_string("VPMULHRSW"), 0x20b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 0b /r - VPMULHRSW xmm, vex128, xmm/m128
    { const_string("VPMULHRSW"), 0x20b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 0b /r - VPMULHRSW ymm, vex256, ymm/m256
    { const_string("VPMULHRSW"), 0x20b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 0b /r - VPMULHRSW ymm, vex256, ymm/m256
    { const_string("VPMULHRSW"), 0x20b, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 0b /r - VPMULHRSW zmm, vex512, zmm/m512
    { const_string("VPMULHRSW"), 0x20b, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 0b /r - VPMULHRSW zmm, vex512, zmm/m512
    { const_string("VPERMILPS"), 0x20c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 0c /r - VPERMILPS xmm, vex128, xmm/m128
    { const_string("VPERMILPS"), 0x20c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 0c /r - VPERMILPS ymm, vex256, ymm/m256
    { const_string("VPERMILPS"), 0x20c, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 0c /r - VPERMILPS zmm, vex512, zmm/m512
    { const_string("VPERMILPD"), 0x20d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 0d /r - VPERMILPD xmm, vex128, xmm/m128
    { const_string("VPERMILPD"), 0x20d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 0d /r - VPERMILPD ymm, vex256, ymm/m256
    { const_string("VPERMILPD"), 0x20d, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 0d /r - VPERMILPD zmm, vex512, zmm/m512
    { const_string("VPMOVUSWB"), 0x210, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 10 /r - VPMOVUSWB xmm/m64, xmm
    { const_string("VPMOVUSWB"), 0x210, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 10 /r - VPMOVUSWB xmm/m128, ymm
    { const_string("VPMOVUSWB"), 0x210, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 10 /r - VPMOVUSWB ymm/m256, zmm
    { const_string("VPSRLVW"), 0x210, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 10 /r - VPSRLVW xmm, vex128, xmm/m128
    { const_string("VPSRLVW"), 0x210, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 10 /r - VPSRLVW ymm, vex256, ymm/m256
    { const_string("VPSRLVW"), 0x210, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 10 /r - VPSRLVW zmm, vex512, zmm/m512
    { const_string("VPMOVUSDB"), 0x211, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 11 /r - VPMOVUSDB xmm/m32, xmm
    { const_string("VPMOVUSDB"), 0x211, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 11 /r - VPMOVUSDB xmm/m64, ymm
    { const_string("VPMOVUSDB"), 0x211, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 11 /r - VPMOVUSDB xmm/m128, zmm
    { const_string("VPSRAVW"), 0x211, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 11 /r - VPSRAVW xmm, vex128, xmm/m128
    { const_string("VPSRAVW"), 0x211, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 11 /r - VPSRAVW ymm, vex256, ymm/m256
    { const_string("VPSRAVW"), 0x211, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 11 /r - VPSRAVW zmm, vex512, zmm/m512
    { const_string("VPMOVUSQB"), 0x212, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm16, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 12 /r - VPMOVUSQB xmm/m16, xmm
    { const_string("VPMOVUSQB"), 0x212, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm32, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 12 /r - VPMOVUSQB xmm/m32, ymm
    { const_string("VPMOVUSQB"), 0x212, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 12 /r - VPMOVUSQB xmm/m64, zmm
    { const_string("VPSLLVW"), 0x212, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 12 /r - VPSLLVW xmm, vex128, xmm/m128
    { const_string("VPSLLVW"), 0x212, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 12 /r - VPSLLVW ymm, vex256, ymm/m256
    { const_string("VPSLLVW"), 0x212, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 12 /r - VPSLLVW zmm, vex512, zmm/m512
    { const_string("VPMOVUSDW"), 0x213, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 13 /r - VPMOVUSDW xmm/m64, xmm
    { const_string("VPMOVUSDW"), 0x213, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 13 /r - VPMOVUSDW xmm/m128, ymm
    { const_string("VPMOVUSDW"), 0x213, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 13 /r - VPMOVUSDW ymm/m256, zmm
    { const_string("VCVTPH2PS"), 0x213, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 13 /r - VCVTPH2PS xmm, xmm/m64
    { const_string("VCVTPH2PS"), 0x213, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 13 /r - VCVTPH2PS ymm, xmm/m128
    { const_string("VCVTPH2PS"), 0x213, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 13 /r - VCVTPH2PS zmm, ymm/m256
    { const_string("VPMOVUSQW"), 0x214, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 14 /r - VPMOVUSQW xmm/m32, xmm
    { const_string("VPMOVUSQW"), 0x214, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 14 /r - VPMOVUSQW xmm/m64, ymm
    { const_string("VPMOVUSQW"), 0x214, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 14 /r - VPMOVUSQW xmm/m128, zmm
    { const_string("VPRORVD"), 0x214, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 14 /r - VPRORVD xmm, vex128, xmm/m128
    { const_string("VPRORVQ"), 0x214, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 14 /r - VPRORVQ xmm, vex128, xmm/m128
    { const_string("VPRORVD"), 0x214, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 14 /r - VPRORVD ymm, vex256, ymm/m256
    { const_string("VPRORVQ"), 0x214, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 14 /r - VPRORVQ ymm, vex256, ymm/m256
    { const_string("VPRORVD"), 0x214, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 14 /r - VPRORVD zmm, vex512, zmm/m512
    { const_string("VPRORVQ"), 0x214, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 14 /r - VPRORVQ zmm, vex512, zmm/m512
    { const_string("VPMOVUSQD"), 0x215, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 15 /r - VPMOVUSQD xmm/m64, xmm
    { const_string("VPMOVUSQD"), 0x215, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 15 /r - VPMOVUSQD xmm/m128, ymm
    { const_string("VPMOVUSQD"), 0x215, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 15 /r - VPMOVUSQD ymm/m256, zmm
    { const_string("VPROLVD"), 0x215, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 15 /r - VPROLVD xmm, vex128, xmm/m128
    { const_string("VPROLVQ"), 0x215, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 15 /r - VPROLVQ xmm, vex128, xmm/m128
    { const_string("VPROLVD"), 0x215, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 15 /r - VPROLVD ymm, vex256, ymm/m256
    { const_string("VPROLVQ"), 0x215, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 15 /r - VPROLVQ ymm, vex256, ymm/m256
    { const_string("VPROLVD"), 0x215, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 15 /r - VPROLVD zmm, vex512, zmm/m512
    { const_string("VPROLVQ"), 0x215, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 15 /r - VPROLVQ zmm, vex512, zmm/m512
    { const_string("VPERMPS"), 0x216, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 16 /r - VPERMPS ymm, vex256, ymm/m256
    { const_string("VPERMPD"), 0x216, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 16 /r - VPERMPD ymm, vex256, ymm/m256
    { const_string("VPERMPS"), 0x216, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 16 /r - VPERMPS zmm, vex512, zmm/m512
    { const_string("VPERMPD"), 0x216, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 16 /r - VPERMPD zmm, vex512, zmm/m512
    { const_string("VBROADCASTSS"), 0x218, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 18 /r - VBROADCASTSS xmm, xmm/m32
    { const_string("VBROADCASTSS"), 0x218, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 18 /r - VBROADCASTSS ymm, xmm/m32
    { const_string("VBROADCASTSS"), 0x218, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 18 /r - VBROADCASTSS zmm, xmm/m32
    { const_string("VBROADCASTF32X2"), 0x219, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 19 /r - VBROADCASTF32X2 ymm, xmm/m64
    { const_string("VBROADCASTSD"), 0x219, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 19 /r - VBROADCASTSD ymm, xmm/m64
    { const_string("VBROADCASTF32X2"), 0x219, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 19 /r - VBROADCASTF32X2 zmm, xmm/m64
    { const_string("VBROADCASTSD"), 0x219, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 19 /r - VBROADCASTSD zmm, xmm/m64
    { const_string("VBROADCASTF32X4"), 0x21a, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 1a /r - VBROADCASTF32X4 ymm, m128
    { const_string("VBROADCASTF64X2"), 0x21a, -1, 0, 0, 1, 1, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 1a /r - VBROADCASTF64X2 ymm, m128
    { const_string("VBROADCASTF32X4"), 0x21a, -1, 0, 0, 1, 0, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 1a /r - VBROADCASTF32X4 zmm, m128
    { const_string("VBROADCASTF64X2"), 0x21a, -1, 0, 0, 1, 1, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 1a /r - VBROADCASTF64X2 zmm, m128
    { const_string("VBROADCASTF32X8"), 0x21b, -1, 0, 0, 1, 0, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 1b /r - VBROADCASTF32X8 zmm, m256
    { const_string("VBROADCASTF64X4"), 0x21b, -1, 0, 0, 1, 1, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 1b /r - VBROADCASTF64X4 zmm, m256
    { const_string("VPABSB"), 0x21c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 1c /r - VPABSB xmm, xmm/m128
    { const_string("VPABSB"), 0x21c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 1c /r - VPABSB xmm, xmm/m128
    { const_string("VPABSB"), 0x21c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 1c /r - VPABSB ymm, ymm/m256
    { const_string("VPABSB"), 0x21c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 1c /r - VPABSB ymm, ymm/m256
    { const_string("VPABSB"), 0x21c, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 1c /r - VPABSB zmm, zmm/m512
    { const_string("VPABSB"), 0x21c, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 1c /r - VPABSB zmm, zmm/m512
    { const_string("VPABSW"), 0x21d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 1d /r - VPABSW xmm, xmm/m128
    { const_string("VPABSW"), 0x21d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 1d /r - VPABSW xmm, xmm/m128
    { const_string("VPABSW"), 0x21d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 1d /r - VPABSW ymm, ymm/m256
    { const_string("VPABSW"), 0x21d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 1d /r - VPABSW ymm, ymm/m256
    { const_string("VPABSW"), 0x21d, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 1d /r - VPABSW zmm, zmm/m512
    { const_string("VPABSW"), 0x21d, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 1d /r - VPABSW zmm, zmm/m512
    { const_string("VPABSD"), 0x21e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 1e /r - VPABSD xmm, xmm/m128
    { const_string("VPABSD"), 0x21e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 1e /r - VPABSD ymm, ymm/m256
    { const_string("VPABSD"), 0x21e, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 1e /r - VPABSD zmm, zmm/m512
    { const_string("VPABSQ"), 0x21f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 1f /r - VPABSQ xmm, xmm/m128
    { const_string("VPABSQ"), 0x21f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 1f /r - VPABSQ ymm, ymm/m256
    { const_string("VPABSQ"), 0x21f, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 1f /r - VPABSQ zmm, zmm/m512
    { const_string("VPMOVSWB"), 0x220, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 20 /r - VPMOVSWB xmm/m64, xmm
    { const_string("VPMOVSWB"), 0x220, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 20 /r - VPMOVSWB xmm/m128, ymm
    { const_string("VPMOVSWB"), 0x220, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 20 /r - VPMOVSWB ymm/m256, zmm
    { const_string("VPMOVSXBW"), 0x220, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 20 /r - VPMOVSXBW xmm, xmm/m64
    { const_string("VPMOVSXBW"), 0x220, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 20 /r - VPMOVSXBW xmm, xmm/m64
    { const_string("VPMOVSXBW"), 0x220, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 20 /r - VPMOVSXBW ymm, xmm/m128
    { const_string("VPMOVSXBW"), 0x220, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 20 /r - VPMOVSXBW ymm, xmm/m128
    { const_string("VPMOVSXBW"), 0x220, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 20 /r - VPMOVSXBW zmm, ymm/m256
    { const_string("VPMOVSXBW"), 0x220, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 20 /r - VPMOVSXBW zmm, ymm/m256
    { const_string("VPMOVSDB"), 0x221, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 21 /r - VPMOVSDB xmm/m32, xmm
    { const_string("VPMOVSDB"), 0x221, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 21 /r - VPMOVSDB xmm/m64, ymm
    { const_string("VPMOVSDB"), 0x221, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 21 /r - VPMOVSDB xmm/m128, zmm
    { const_string("VPMOVSXBD"), 0x221, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 21 /r - VPMOVSXBD xmm, xmm/m32
    { const_string("VPMOVSXBD"), 0x221, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 21 /r - VPMOVSXBD xmm, xmm/m32
    { const_string("VPMOVSXBD"), 0x221, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 21 /r - VPMOVSXBD ymm, xmm/m64
    { const_string("VPMOVSXBD"), 0x221, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 21 /r - VPMOVSXBD ymm, xmm/m64
    { const_string("VPMOVSXBD"), 0x221, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 21 /r - VPMOVSXBD zmm, xmm/m128
    { const_string("VPMOVSXBD"), 0x221, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 21 /r - VPMOVSXBD zmm, xmm/m128
    { const_string("VPMOVSQB"), 0x222, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm16, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 22 /r - VPMOVSQB xmm/m16, xmm
    { const_string("VPMOVSQB"), 0x222, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm32, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 22 /r - VPMOVSQB xmm/m32, ymm
    { const_string("VPMOVSQB"), 0x222, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 22 /r - VPMOVSQB xmm/m64, zmm
    { const_string("VPMOVSXBQ"), 0x222, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 22 /r - VPMOVSXBQ xmm, xmm/m64
    { const_string("VPMOVSXBQ"), 0x222, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 22 /r - VPMOVSXBQ xmm, xmm/m64
    { const_string("VPMOVSXBQ"), 0x222, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 22 /r - VPMOVSXBQ ymm, xmm/m32
    { const_string("VPMOVSXBQ"), 0x222, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 22 /r - VPMOVSXBQ ymm, xmm/m32
    { const_string("VPMOVSXBQ"), 0x222, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 22 /r - VPMOVSXBQ zmm, xmm/m64
    { const_string("VPMOVSXBQ"), 0x222, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 22 /r - VPMOVSXBQ zmm, xmm/m64
    { const_string("VPMOVSDW"), 0x223, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 23 /r - VPMOVSDW xmm/m64, xmm
    { const_string("VPMOVSDW"), 0x223, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 23 /r - VPMOVSDW xmm/m128, ymm
    { const_string("VPMOVSDW"), 0x223, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 23 /r - VPMOVSDW ymm/m256, zmm
    { const_string("VPMOVSXWD"), 0x223, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 23 /r - VPMOVSXWD xmm, xmm/m64
    { const_string("VPMOVSXWD"), 0x223, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 23 /r - VPMOVSXWD xmm, xmm/m64
    { const_string("VPMOVSXWD"), 0x223, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 23 /r - VPMOVSXWD ymm, xmm/m128
    { const_string("VPMOVSXWD"), 0x223, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 23 /r - VPMOVSXWD ymm, xmm/m128
    { const_string("VPMOVSXWD"), 0x223, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 23 /r - VPMOVSXWD zmm, ymm/m256
    { const_string("VPMOVSXWD"), 0x223, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 23 /r - VPMOVSXWD zmm, ymm/m256
    { const_string("VPMOVSQW"), 0x224, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 24 /r - VPMOVSQW xmm/m32, xmm
    { const_string("VPMOVSQW"), 0x224, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 24 /r - VPMOVSQW xmm/m64, ymm
    { const_string("VPMOVSQW"), 0x224, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 24 /r - VPMOVSQW xmm/m128, zmm
    { const_string("VPMOVSXWQ"), 0x224, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 24 /r - VPMOVSXWQ xmm, xmm/m32
    { const_string("VPMOVSXWQ"), 0x224, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 24 /r - VPMOVSXWQ xmm, xmm/m32
    { const_string("VPMOVSXWQ"), 0x224, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 24 /r - VPMOVSXWQ ymm, xmm/m64
    { const_string("VPMOVSXWQ"), 0x224, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 24 /r - VPMOVSXWQ ymm, xmm/m64
    { const_string("VPMOVSXWQ"), 0x224, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 24 /r - VPMOVSXWQ zmm, xmm/m128
    { const_string("VPMOVSXWQ"), 0x224, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 24 /r - VPMOVSXWQ zmm, xmm/m128
    { const_string("VPMOVSQD"), 0x225, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 25 /r - VPMOVSQD xmm/m64, xmm
    { const_string("VPMOVSQD"), 0x225, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 25 /r - VPMOVSQD xmm/m128, ymm
    { const_string("VPMOVSQD"), 0x225, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 25 /r - VPMOVSQD ymm/m256, zmm
    { const_string("VPMOVSXDQ"), 0x225, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 25 /r - VPMOVSXDQ xmm, xmm/m64
    { const_string("VPMOVSXDQ"), 0x225, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 25 /r - VPMOVSXDQ ymm, xmm/m128
    { const_string("VPMOVSXDQ"), 0x225, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 25 /r - VPMOVSXDQ zmm, ymm/m256
    { const_string("VPTESTNMB"), 0x226, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 26 /r - VPTESTNMB k, vex128, xmm/m128
    { const_string("VPTESTNMW"), 0x226, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W1 26 /r - VPTESTNMW k, vex128, xmm/m128
    { const_string("VPTESTNMB"), 0x226, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 26 /r - VPTESTNMB k, vex256, ymm/m256
    { const_string("VPTESTNMW"), 0x226, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W1 26 /r - VPTESTNMW k, vex256, ymm/m256
    { const_string("VPTESTNMB"), 0x226, -1, 0, 1, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 26 /r - VPTESTNMB k, vex512, zmm/m512
    { const_string("VPTESTNMW"), 0x226, -1, 0, 1, 0, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W1 26 /r - VPTESTNMW k, vex512, zmm/m512
    { const_string("VPTESTMB"), 0x226, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 26 /r - VPTESTMB k, vex128, xmm/m128
    { const_string("VPTESTMW"), 0x226, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 26 /r - VPTESTMW k, vex128, xmm/m128
    { const_string("VPTESTMB"), 0x226, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 26 /r - VPTESTMB k, vex256, ymm/m256
    { const_string("VPTESTMW"), 0x226, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 26 /r - VPTESTMW k, vex256, ymm/m256
    { const_string("VPTESTMB"), 0x226, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 26 /r - VPTESTMB k, vex512, zmm/m512
    { const_string("VPTESTMW"), 0x226, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 26 /r - VPTESTMW k, vex512, zmm/m512
    { const_string("VPTESTNMD"), 0x227, -1, 0, 1, 0, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 27 /r - VPTESTNMD k, vex128, xmm/m128
    { const_string("VPTESTNMQ"), 0x227, -1, 0, 1, 0, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W1 27 /r - VPTESTNMQ k, vex128, xmm/m128
    { const_string("VPTESTNMD"), 0x227, -1, 0, 1, 0, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 27 /r - VPTESTNMD k, vex256, ymm/m256
    { const_string("VPTESTNMQ"), 0x227, -1, 0, 1, 0, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W1 27 /r - VPTESTNMQ k, vex256, ymm/m256
    { const_string("VPTESTNMD"), 0x227, -1, 0, 1, 0, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 27 /r - VPTESTNMD k, vex512, zmm/m512
    { const_string("VPTESTNMQ"), 0x227, -1, 0, 1, 0, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W1 27 /r - VPTESTNMQ k, vex512, zmm/m512
    { const_string("VPTESTMD"), 0x227, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 27 /r - VPTESTMD k, vex128, xmm/m128
    { const_string("VPTESTMQ"), 0x227, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 27 /r - VPTESTMQ k, vex128, xmm/m128
    { const_string("VPTESTMD"), 0x227, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 27 /r - VPTESTMD k, vex256, ymm/m256
    { const_string("VPTESTMQ"), 0x227, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 27 /r - VPTESTMQ k, vex256, ymm/m256
    { const_string("VPTESTMD"), 0x227, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 27 /r - VPTESTMD k, vex512, zmm/m512
    { const_string("VPTESTMQ"), 0x227, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 27 /r - VPTESTMQ k, vex512, zmm/m512
    { const_string("VPMOVM2B"), 0x228, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 28 /r - VPMOVM2B xmm, k/m64
    { const_string("VPMOVM2W"), 0x228, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W1 28 /r - VPMOVM2W xmm, k/m64
    { const_string("VPMOVM2B"), 0x228, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 28 /r - VPMOVM2B ymm, k/m64
    { const_string("VPMOVM2W"), 0x228, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W1 28 /r - VPMOVM2W ymm, k/m64
    { const_string("VPMOVM2B"), 0x228, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 28 /r - VPMOVM2B zmm, k/m64
    { const_string("VPMOVM2W"), 0x228, -1, 0, 1, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W1 28 /r - VPMOVM2W zmm, k/m64
    { const_string("VPMULDQ"), 0x228, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 28 /r - VPMULDQ xmm, vex128, xmm/m128
    { const_string("VPMULDQ"), 0x228, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 28 /r - VPMULDQ ymm, vex256, ymm/m256
    { const_string("VPMULDQ"), 0x228, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 28 /r - VPMULDQ zmm, vex512, zmm/m512
    { const_string("VPMOVB2M"), 0x229, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 29 /r - VPMOVB2M k, xmm/m128
    { const_string("VPMOVW2M"), 0x229, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W1 29 /r - VPMOVW2M k, xmm/m128
    { const_string("VPMOVB2M"), 0x229, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 29 /r - VPMOVB2M k, ymm/m256
    { const_string("VPMOVW2M"), 0x229, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W1 29 /r - VPMOVW2M k, ymm/m256
    { const_string("VPMOVB2M"), 0x229, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 29 /r - VPMOVB2M k, zmm/m512
    { const_string("VPMOVW2M"), 0x229, -1, 0, 1, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W1 29 /r - VPMOVW2M k, zmm/m512
    { const_string("VPCMPEQQ"), 0x229, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 29 /r - VPCMPEQQ k, vex128, xmm/m128
    { const_string("VPCMPEQQ"), 0x229, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 29 /r - VPCMPEQQ k, vex256, ymm/m256
    { const_string("VPCMPEQQ"), 0x229, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 29 /r - VPCMPEQQ k, vex512, zmm/m512
    { const_string("VPBROADCASTMB2Q"), 0x22a, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W1 2a /r - VPBROADCASTMB2Q xmm, k/m64
    { const_string("VPBROADCASTMB2Q"), 0x22a, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W1 2a /r - VPBROADCASTMB2Q ymm, k/m64
    { const_string("VPBROADCASTMB2Q"), 0x22a, -1, 0, 1, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W1 2a /r - VPBROADCASTMB2Q zmm, k/m64
    { const_string("VMOVNTDQA"), 0x22a, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 2a /r - VMOVNTDQA xmm, m128
    { const_string("VMOVNTDQA"), 0x22a, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 2a /r - VMOVNTDQA ymm, m256
    { const_string("VMOVNTDQA"), 0x22a, -1, 0, 0, 1, 0, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 2a /r - VMOVNTDQA zmm, m512
    { const_string("VPACKUSDW"), 0x22b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 2b /r - VPACKUSDW xmm, vex128, xmm/m128
    { const_string("VPACKUSDW"), 0x22b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 2b /r - VPACKUSDW ymm, vex256, ymm/m256
    { const_string("VPACKUSDW"), 0x22b, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 2b /r - VPACKUSDW zmm, vex512, zmm/m512
    { const_string("VSCALEFPS"), 0x22c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 2c /r - VSCALEFPS xmm, vex128, xmm/m128
    { const_string("VSCALEFPD"), 0x22c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 2c /r - VSCALEFPD xmm, vex128, xmm/m128
    { const_string("VSCALEFPS"), 0x22c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 2c /r - VSCALEFPS ymm, vex256, ymm/m256
    { const_string("VSCALEFPD"), 0x22c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 2c /r - VSCALEFPD ymm, vex256, ymm/m256
    { const_string("VSCALEFPS"), 0x22c, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 2c /r - VSCALEFPS zmm, vex512, zmm/m512
    { const_string("VSCALEFPD"), 0x22c, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 2c /r - VSCALEFPD zmm, vex512, zmm/m512
    { const_string("VSCALEFSS"), 0x22d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 2d /r - VSCALEFSS xmm, vex128, xmm/m32
    { const_string("VSCALEFSD"), 0x22d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 2d /r - VSCALEFSD xmm, vex128, xmm/m64
    { const_string("VSCALEFSS"), 0x22d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 2d /r - VSCALEFSS xmm, vex128, xmm/m32
    { const_string("VSCALEFSD"), 0x22d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 2d /r - VSCALEFSD xmm, vex128, xmm/m64
    { const_string("VPMOVWB"), 0x230, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 30 /r - VPMOVWB xmm/m64, xmm
    { const_string("VPMOVWB"), 0x230, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 30 /r - VPMOVWB xmm/m128, ymm
    { const_string("VPMOVWB"), 0x230, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 30 /r - VPMOVWB ymm/m256, zmm
    { const_string("VPMOVZXBW"), 0x230, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 30 /r - VPMOVZXBW ymm, xmm/m128
    { const_string("VPMOVZXBW"), 0x230, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 30 /r - VPMOVZXBW ymm, xmm/m128
    { const_string("VPMOVZXBW"), 0x230, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 30 /r - VPMOVZXBW zmm, ymm/m256
    { const_string("VPMOVZXBW"), 0x230, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 30 /r - VPMOVZXBW zmm, ymm/m256
    { const_string("VPMOVDB"), 0x231, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 31 /r - VPMOVDB xmm/m32, xmm
    { const_string("VPMOVDB"), 0x231, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 31 /r - VPMOVDB xmm/m64, ymm
    { const_string("VPMOVDB"), 0x231, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 31 /r - VPMOVDB xmm/m128, zmm
    { const_string("VPMOVZXBD"), 0x231, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 31 /r - VPMOVZXBD xmm, xmm/m32
    { const_string("VPMOVZXBD"), 0x231, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 31 /r - VPMOVZXBD xmm, xmm/m32
    { const_string("VPMOVZXBD"), 0x231, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 31 /r - VPMOVZXBD ymm, xmm/m64
    { const_string("VPMOVZXBD"), 0x231, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 31 /r - VPMOVZXBD ymm, xmm/m64
    { const_string("VPMOVZXBD"), 0x231, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 31 /r - VPMOVZXBD zmm, xmm/m128
    { const_string("VPMOVZXBD"), 0x231, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 31 /r - VPMOVZXBD zmm, xmm/m128
    { const_string("VPMOVQB"), 0x232, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm16, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 32 /r - VPMOVQB xmm/m16, xmm
    { const_string("VPMOVQB"), 0x232, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm32, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 32 /r - VPMOVQB xmm/m32, ymm
    { const_string("VPMOVQB"), 0x232, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 32 /r - VPMOVQB xmm/m64, zmm
    { const_string("VPMOVZXBQ"), 0x232, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 32 /r - VPMOVZXBQ xmm, xmm/m64
    { const_string("VPMOVZXBQ"), 0x232, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 32 /r - VPMOVZXBQ xmm, xmm/m64
    { const_string("VPMOVZXBQ"), 0x232, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 32 /r - VPMOVZXBQ ymm, xmm/m32
    { const_string("VPMOVZXBQ"), 0x232, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 32 /r - VPMOVZXBQ ymm, xmm/m32
    { const_string("VPMOVZXBQ"), 0x232, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 32 /r - VPMOVZXBQ zmm, xmm/m64
    { const_string("VPMOVZXBQ"), 0x232, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 32 /r - VPMOVZXBQ zmm, xmm/m64
    { const_string("VPMOVDW"), 0x233, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 33 /r - VPMOVDW xmm/m64, xmm
    { const_string("VPMOVDW"), 0x233, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 33 /r - VPMOVDW xmm/m128, ymm
    { const_string("VPMOVDW"), 0x233, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 33 /r - VPMOVDW ymm/m256, zmm
    { const_string("VPMOVZXWD"), 0x233, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 33 /r - VPMOVZXWD xmm, xmm/m64
    { const_string("VPMOVZXWD"), 0x233, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 33 /r - VPMOVZXWD xmm, xmm/m64
    { const_string("VPMOVZXWD"), 0x233, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 33 /r - VPMOVZXWD ymm, xmm/m128
    { const_string("VPMOVZXWD"), 0x233, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 33 /r - VPMOVZXWD ymm, xmm/m128
    { const_string("VPMOVZXWD"), 0x233, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 33 /r - VPMOVZXWD zmm, ymm/m256
    { const_string("VPMOVZXWD"), 0x233, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 33 /r - VPMOVZXWD zmm, ymm/m256
    { const_string("VPMOVQW"), 0x234, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 34 /r - VPMOVQW xmm/m32, xmm
    { const_string("VPMOVQW"), 0x234, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 34 /r - VPMOVQW xmm/m64, ymm
    { const_string("VPMOVQW"), 0x234, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 34 /r - VPMOVQW xmm/m128, zmm
    { const_string("VPMOVZXWQ"), 0x234, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 34 /r - VPMOVZXWQ xmm, xmm/m32
    { const_string("VPMOVZXWQ"), 0x234, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 34 /r - VPMOVZXWQ xmm, xmm/m32
    { const_string("VPMOVZXWQ"), 0x234, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 34 /r - VPMOVZXWQ ymm, xmm/m64
    { const_string("VPMOVZXWQ"), 0x234, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 34 /r - VPMOVZXWQ ymm, xmm/m64
    { const_string("VPMOVZXWQ"), 0x234, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 34 /r - VPMOVZXWQ zmm, xmm/m128
    { const_string("VPMOVZXWQ"), 0x234, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 34 /r - VPMOVZXWQ zmm, xmm/m128
    { const_string("VPMOVQD"), 0x235, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 35 /r - VPMOVQD xmm/m128, xmm
    { const_string("VPMOVQD"), 0x235, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 35 /r - VPMOVQD xmm/m128, ymm
    { const_string("VPMOVQD"), 0x235, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 35 /r - VPMOVQD ymm/m256, zmm
    { const_string("VPMOVZXDQ"), 0x235, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 35 /r - VPMOVZXDQ xmm, xmm/m64
    { const_string("VPMOVZXDQ"), 0x235, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 35 /r - VPMOVZXDQ ymm, xmm/m128
    { const_string("VPMOVZXDQ"), 0x235, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 35 /r - VPMOVZXDQ zmm, ymm/m256
    { const_string("VPERMD"), 0x236, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 36 /r - VPERMD ymm, vex256, ymm/m256
    { const_string("VPERMQ"), 0x236, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 36 /r - VPERMQ ymm, vex256, ymm/m256
    { const_string("VPERMD"), 0x236, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 36 /r - VPERMD zmm, vex512, zmm/m512
    { const_string("VPERMQ"), 0x236, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 36 /r - VPERMQ zmm, vex512, zmm/m512
    { const_string("VPCMPGTQ"), 0x237, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 37 /r - VPCMPGTQ k, vex128, xmm/m128
    { const_string("VPCMPGTQ"), 0x237, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 37 /r - VPCMPGTQ k, vex256, ymm/m256
    { const_string("VPCMPGTQ"), 0x237, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 37 /r - VPCMPGTQ k, vex512, zmm/m512
    { const_string("VPMOVM2D"), 0x238, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 38 /r - VPMOVM2D xmm, k/m64
    { const_string("VPMOVM2Q"), 0x238, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W1 38 /r - VPMOVM2Q xmm, k/m64
    { const_string("VPMOVM2D"), 0x238, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 38 /r - VPMOVM2D ymm, k/m64
    { const_string("VPMOVM2Q"), 0x238, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W1 38 /r - VPMOVM2Q ymm, k/m64
    { const_string("VPMOVM2D"), 0x238, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 38 /r - VPMOVM2D zmm, k/m64
    { const_string("VPMOVM2Q"), 0x238, -1, 0, 1, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W1 38 /r - VPMOVM2Q zmm, k/m64
    { const_string("VPMINSB"), 0x238, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 38 /r - VPMINSB xmm, vex128, xmm/m128
    { const_string("VPMINSB"), 0x238, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 38 /r - VPMINSB xmm, vex128, xmm/m128
    { const_string("VPMINSB"), 0x238, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 38 /r - VPMINSB ymm, vex256, ymm/m256
    { const_string("VPMINSB"), 0x238, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 38 /r - VPMINSB ymm, vex256, ymm/m256
    { const_string("VPMINSB"), 0x238, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 38 /r - VPMINSB zmm, vex512, zmm/m512
    { const_string("VPMINSB"), 0x238, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 38 /r - VPMINSB zmm, vex512, zmm/m512
    { const_string("VPMOVD2M"), 0x239, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 39 /r - VPMOVD2M k, xmm/m128
    { const_string("VPMOVQ2M"), 0x239, -1, 0, 1, 0, 1, 0, -1, 0, 0, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W1 39 /r - VPMOVQ2M k, xmm/m128
    { const_string("VPMOVD2M"), 0x239, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 39 /r - VPMOVD2M k, ymm/m256
    { const_string("VPMOVQ2M"), 0x239, -1, 0, 1, 0, 1, 0, -1, 0, 1, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W1 39 /r - VPMOVQ2M k, ymm/m256
    { const_string("VPMOVD2M"), 0x239, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 39 /r - VPMOVD2M k, zmm/m512
    { const_string("VPMOVQ2M"), 0x239, -1, 0, 1, 0, 1, 0, -1, 0, 2, 2, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W1 39 /r - VPMOVQ2M k, zmm/m512
    { const_string("VPMINSD"), 0x239, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 39 /r - VPMINSD xmm, vex128, xmm/m128
    { const_string("VPMINSQ"), 0x239, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 39 /r - VPMINSQ xmm, vex128, xmm/m128
    { const_string("VPMINSD"), 0x239, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 39 /r - VPMINSD ymm, vex256, ymm/m256
    { const_string("VPMINSQ"), 0x239, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 39 /r - VPMINSQ ymm, vex256, ymm/m256
    { const_string("VPMINSD"), 0x239, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 39 /r - VPMINSD zmm, vex512, zmm/m512
    { const_string("VPMINSQ"), 0x239, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 39 /r - VPMINSQ zmm, vex512, zmm/m512
    { const_string("VPBROADCASTMW2D"), 0x23a, -1, 0, 1, 0, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.128.F3.0F38.W0 3a /r - VPBROADCASTMW2D xmm, k/m64
    { const_string("VPBROADCASTMW2D"), 0x23a, -1, 0, 1, 0, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.256.F3.0F38.W0 3a /r - VPBROADCASTMW2D ymm, k/m64
    { const_string("VPBROADCASTMW2D"), 0x23a, -1, 0, 1, 0, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_km64, OPERAND_FLAG_read}} }, // EVEX.512.F3.0F38.W0 3a /r - VPBROADCASTMW2D zmm, k/m64
    { const_string("VPMINUW"), 0x23a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 3a /r - VPMINUW xmm, vex128, xmm/m128
    { const_string("VPMINUW"), 0x23a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 3a /r - VPMINUW xmm, vex128, xmm/m128
    { const_string("VPMINUW"), 0x23a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 3a /r - VPMINUW ymm, vex256, ymm/m256
    { const_string("VPMINUW"), 0x23a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 3a /r - VPMINUW ymm, vex256, ymm/m256
    { const_string("VPMINUW"), 0x23a, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 3a /r - VPMINUW zmm, vex512, zmm/m512
    { const_string("VPMINUW"), 0x23a, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 3a /r - VPMINUW zmm, vex512, zmm/m512
    { const_string("VPMINUD"), 0x23b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 3b /r - VPMINUD xmm, vex128, xmm/m128
    { const_string("VPMINUQ"), 0x23b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 3b /r - VPMINUQ xmm, vex128, xmm/m128
    { const_string("VPMINUD"), 0x23b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 3b /r - VPMINUD ymm, vex256, ymm/m256
    { const_string("VPMINUQ"), 0x23b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 3b /r - VPMINUQ ymm, vex256, ymm/m256
    { const_string("VPMINUD"), 0x23b, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 3b /r - VPMINUD zmm, vex512, zmm/m512
    { const_string("VPMINUQ"), 0x23b, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 3b /r - VPMINUQ zmm, vex512, zmm/m512
    { const_string("VPMAXSB"), 0x23c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 3c /r - VPMAXSB xmm, vex128, xmm/m128
    { const_string("VPMAXSB"), 0x23c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 3c /r - VPMAXSB xmm, vex128, xmm/m128
    { const_string("VPMAXSB"), 0x23c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 3c /r - VPMAXSB ymm, vex256, ymm/m256
    { const_string("VPMAXSB"), 0x23c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 3c /r - VPMAXSB ymm, vex256, ymm/m256
    { const_string("VPMAXSB"), 0x23c, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 3c /r - VPMAXSB zmm, vex512, zmm/m512
    { const_string("VPMAXSB"), 0x23c, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 3c /r - VPMAXSB zmm, vex512, zmm/m512
    { const_string("VPMAXSD"), 0x23d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 3d /r - VPMAXSD xmm, vex128, xmm/m128
    { const_string("VPMAXSQ"), 0x23d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 3d /r - VPMAXSQ xmm, vex128, xmm/m128
    { const_string("VPMAXSD"), 0x23d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 3d /r - VPMAXSD ymm, vex256, ymm/m256
    { const_string("VPMAXSQ"), 0x23d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 3d /r - VPMAXSQ ymm, vex256, ymm/m256
    { const_string("VPMAXSD"), 0x23d, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 3d /r - VPMAXSD zmm, vex512, zmm/m512
    { const_string("VPMAXSQ"), 0x23d, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 3d /r - VPMAXSQ zmm, vex512, zmm/m512
    { const_string("VPMAXUW"), 0x23e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 3e /r - VPMAXUW xmm, vex128, xmm/m128
    { const_string("VPMAXUW"), 0x23e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 3e /r - VPMAXUW xmm, vex128, xmm/m128
    { const_string("VPMAXUW"), 0x23e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 3e /r - VPMAXUW ymm, vex256, ymm/m256
    { const_string("VPMAXUW"), 0x23e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 3e /r - VPMAXUW ymm, vex256, ymm/m256
    { const_string("VPMAXUW"), 0x23e, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 3e /r - VPMAXUW zmm, vex512, zmm/m512
    { const_string("VPMAXUW"), 0x23e, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 3e /r - VPMAXUW zmm, vex512, zmm/m512
    { const_string("VPMAXUD"), 0x23f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 3f /r - VPMAXUD xmm, vex128, xmm/m128
    { const_string("VPMAXUQ"), 0x23f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 3f /r - VPMAXUQ xmm, vex128, xmm/m128
    { const_string("VPMAXUD"), 0x23f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 3f /r - VPMAXUD ymm, vex256, ymm/m256
    { const_string("VPMAXUQ"), 0x23f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 3f /r - VPMAXUQ ymm, vex256, ymm/m256
    { const_string("VPMAXUD"), 0x23f, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 3f /r - VPMAXUD zmm, vex512, zmm/m512
    { const_string("VPMAXUQ"), 0x23f, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 3f /r - VPMAXUQ zmm, vex512, zmm/m512
    { const_string("VPMULLD"), 0x240, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 40 /r - VPMULLD xmm, vex128, xmm/m128
    { const_string("VPMULLQ"), 0x240, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 40 /r - VPMULLQ xmm, vex128, xmm/m128
    { const_string("VPMULLD"), 0x240, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 40 /r - VPMULLD ymm, vex256, ymm/m256
    { const_string("VPMULLQ"), 0x240, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 40 /r - VPMULLQ ymm, vex256, ymm/m256
    { const_string("VPMULLD"), 0x240, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 40 /r - VPMULLD zmm, vex512, zmm/m512
    { const_string("VPMULLQ"), 0x240, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 40 /r - VPMULLQ zmm, vex512, zmm/m512
    { const_string("VGETEXPPS"), 0x242, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 42 /r - VGETEXPPS xmm, xmm/m128
    { const_string("VGETEXPPD"), 0x242, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 42 /r - VGETEXPPD xmm, xmm/m128
    { const_string("VGETEXPPS"), 0x242, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 42 /r - VGETEXPPS ymm, ymm/m256
    { const_string("VGETEXPPD"), 0x242, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 42 /r - VGETEXPPD ymm, ymm/m256
    { const_string("VGETEXPPS"), 0x242, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 42 /r - VGETEXPPS zmm, zmm/m512
    { const_string("VGETEXPPD"), 0x242, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 42 /r - VGETEXPPD zmm, zmm/m512
    { const_string("VGETEXPSS"), 0x243, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 43 /r - VGETEXPSS xmm, vex128, xmm/m32
    { const_string("VGETEXPSD"), 0x243, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 43 /r - VGETEXPSD xmm, vex128, xmm/m64
    { const_string("VGETEXPSS"), 0x243, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 43 /r - VGETEXPSS xmm, vex128, xmm/m32
    { const_string("VGETEXPSD"), 0x243, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 43 /r - VGETEXPSD xmm, vex128, xmm/m64
    { const_string("VPLZCNTD"), 0x244, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 44 /r - VPLZCNTD xmm, xmm/m128
    { const_string("VPLZCNTQ"), 0x244, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 44 /r - VPLZCNTQ xmm, xmm/m128
    { const_string("VPLZCNTD"), 0x244, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 44 /r - VPLZCNTD ymm, ymm/m256
    { const_string("VPLZCNTQ"), 0x244, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 44 /r - VPLZCNTQ ymm, ymm/m256
    { const_string("VPLZCNTD"), 0x244, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 44 /r - VPLZCNTD zmm, zmm/m512
    { const_string("VPLZCNTQ"), 0x244, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 44 /r - VPLZCNTQ zmm, zmm/m512
    { const_string("VPSRLVD"), 0x245, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 45 /r - VPSRLVD xmm, vex128, xmm/m128
    { const_string("VPSRLVQ"), 0x245, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 45 /r - VPSRLVQ xmm, vex128, xmm/m128
    { const_string("VPSRLVD"), 0x245, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 45 /r - VPSRLVD ymm, vex256, ymm/m256
    { const_string("VPSRLVQ"), 0x245, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 45 /r - VPSRLVQ ymm, vex256, ymm/m256
    { const_string("VPSRLVD"), 0x245, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 45 /r - VPSRLVD zmm, vex512, zmm/m512
    { const_string("VPSRLVQ"), 0x245, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 45 /r - VPSRLVQ zmm, vex512, zmm/m512
    { const_string("VPSRAVD"), 0x246, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 46 /r - VPSRAVD xmm, vex128, xmm/m128
    { const_string("VPSRAVQ"), 0x246, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 46 /r - VPSRAVQ xmm, vex128, xmm/m128
    { const_string("VPSRAVD"), 0x246, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 46 /r - VPSRAVD ymm, vex256, ymm/m256
    { const_string("VPSRAVQ"), 0x246, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 46 /r - VPSRAVQ ymm, vex256, ymm/m256
    { const_string("VPSRAVD"), 0x246, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 46 /r - VPSRAVD zmm, vex512, zmm/m512
    { const_string("VPSRAVQ"), 0x246, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 46 /r - VPSRAVQ zmm, vex512, zmm/m512
    { const_string("VPSLLVD"), 0x247, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 47 /r - VPSLLVD xmm, vex128, xmm/m128
    { const_string("VPSLLVQ"), 0x247, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 47 /r - VPSLLVQ xmm, vex128, xmm/m128
    { const_string("VPSLLVD"), 0x247, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 47 /r - VPSLLVD ymm, vex256, ymm/m256
    { const_string("VPSLLVQ"), 0x247, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 47 /r - VPSLLVQ ymm, vex256, ymm/m256
    { const_string("VPSLLVD"), 0x247, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 47 /r - VPSLLVD zmm, vex512, zmm/m512
    { const_string("VPSLLVQ"), 0x247, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 47 /r - VPSLLVQ zmm, vex512, zmm/m512
    { const_string("VRCP14PS"), 0x24c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 4c /r - VRCP14PS xmm, xmm/m128
    { const_string("VRCP14PD"), 0x24c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 4c /r - VRCP14PD xmm, xmm/m128
    { const_string("VRCP14PS"), 0x24c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 4c /r - VRCP14PS ymm, ymm/m256
    { const_string("VRCP14PD"), 0x24c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 4c /r - VRCP14PD ymm, ymm/m256
    { const_string("VRCP14PS"), 0x24c, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 4c /r - VRCP14PS zmm, zmm/m512
    { const_string("VRCP14PD"), 0x24c, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 4c /r - VRCP14PD zmm, zmm/m512
    { const_string("VRCP14SS"), 0x24d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 4d /r - VRCP14SS xmm, vex128, xmm/m32
    { const_string("VRCP14SD"), 0x24d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 4d /r - VRCP14SD xmm, vex128, xmm/m64
    { const_string("VRCP14SS"), 0x24d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 4d /r - VRCP14SS xmm, vex128, xmm/m32
    { const_string("VRCP14SD"), 0x24d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 4d /r - VRCP14SD xmm, vex128, xmm/m64
    { const_string("VRSQRT14PS"), 0x24e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 4e /r - VRSQRT14PS xmm, xmm/m128
    { const_string("VRSQRT14PD"), 0x24e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 4e /r - VRSQRT14PD xmm, xmm/m128
    { const_string("VRSQRT14PS"), 0x24e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 4e /r - VRSQRT14PS ymm, ymm/m256
    { const_string("VRSQRT14PD"), 0x24e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 4e /r - VRSQRT14PD ymm, ymm/m256
    { const_string("VRSQRT14PS"), 0x24e, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 4e /r - VRSQRT14PS zmm, zmm/m512
    { const_string("VRSQRT14PD"), 0x24e, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 4e /r - VRSQRT14PD zmm, zmm/m512
    { const_string("VRSQRT14SS"), 0x24f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 4f /r - VRSQRT14SS xmm, vex128, xmm/m32
    { const_string("VRSQRT14SD"), 0x24f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 4f /r - VRSQRT14SD xmm, vex128, xmm/m64
    { const_string("VRSQRT14SS"), 0x24f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 4f /r - VRSQRT14SS xmm, vex128, xmm/m32
    { const_string("VRSQRT14SD"), 0x24f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 4f /r - VRSQRT14SD xmm, vex128, xmm/m64
    { const_string("VPDPBUSD"), 0x250, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 50 /r - VPDPBUSD xmm, vex128, xmm/m128
    { const_string("VPDPBUSD"), 0x250, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 50 /r - VPDPBUSD ymm, vex256, ymm/m256
    { const_string("VPDPBUSD"), 0x250, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 50 /r - VPDPBUSD zmm, vex512, zmm/m512
    { const_string("VPDPBUSDS"), 0x251, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 51 /r - VPDPBUSDS xmm, vex128, xmm/m128
    { const_string("VPDPBUSDS"), 0x251, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 51 /r - VPDPBUSDS ymm, vex256, ymm/m256
    { const_string("VPDPBUSDS"), 0x251, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 51 /r - VPDPBUSDS zmm, vex512, zmm/m512
    { const_string("VPDPWSSD"), 0x252, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 52 /r - VPDPWSSD xmm, vex128, xmm/m128
    { const_string("VPDPWSSD"), 0x252, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 52 /r - VPDPWSSD ymm, vex256, ymm/m256
    { const_string("VPDPWSSD"), 0x252, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 52 /r - VPDPWSSD zmm, vex512, zmm/m512
    { const_string("VPDPWSSDS"), 0x253, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 53 /r - VPDPWSSDS xmm, vex128, xmm/m128
    { const_string("VPDPWSSDS"), 0x253, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 53 /r - VPDPWSSDS ymm, vex256, ymm/m256
    { const_string("VPDPWSSDS"), 0x253, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 53 /r - VPDPWSSDS zmm, vex512, zmm/m512
    { const_string("VPOPCNTB"), 0x254, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 54 /r - VPOPCNTB xmm, xmm/m128
    { const_string("VPOPCNTW"), 0x254, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 54 /r - VPOPCNTW xmm, xmm/m128
    { const_string("VPOPCNTB"), 0x254, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 54 /r - VPOPCNTB ymm, ymm/m256
    { const_string("VPOPCNTW"), 0x254, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 54 /r - VPOPCNTW ymm, ymm/m256
    { const_string("VPOPCNTB"), 0x254, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 54 /r - VPOPCNTB zmm, zmm/m512
    { const_string("VPOPCNTW"), 0x254, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 54 /r - VPOPCNTW zmm, zmm/m512
    { const_string("VPOPCNTD"), 0x255, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 55 /r - VPOPCNTD xmm, xmm/m128
    { const_string("VPOPCNTQ"), 0x255, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 55 /r - VPOPCNTQ xmm, xmm/m128
    { const_string("VPOPCNTD"), 0x255, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 55 /r - VPOPCNTD ymm, ymm/m256
    { const_string("VPOPCNTQ"), 0x255, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 55 /r - VPOPCNTQ ymm, ymm/m256
    { const_string("VPOPCNTD"), 0x255, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 55 /r - VPOPCNTD zmm, zmm/m512
    { const_string("VPOPCNTQ"), 0x255, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 55 /r - VPOPCNTQ zmm, zmm/m512
    { const_string("VPBROADCASTD"), 0x258, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 58 /r - VPBROADCASTD xmm, xmm/m32
    { const_string("VPBROADCASTD"), 0x258, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 58 /r - VPBROADCASTD ymm, xmm/m32
    { const_string("VPBROADCASTD"), 0x258, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 58 /r - VPBROADCASTD zmm, xmm/m32
    { const_string("VBROADCASTI32x2"), 0x259, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 59 /r - VBROADCASTI32x2 xmm, xmm/m64
    { const_string("VPBROADCASTQ"), 0x259, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 59 /r - VPBROADCASTQ xmm, xmm/m64
    { const_string("VBROADCASTI32x2"), 0x259, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 59 /r - VBROADCASTI32x2 ymm, xmm/m64
    { const_string("VPBROADCASTQ"), 0x259, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 59 /r - VPBROADCASTQ ymm, xmm/m64
    { const_string("VBROADCASTI32x2"), 0x259, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 59 /r - VBROADCASTI32x2 zmm, xmm/m64
    { const_string("VPBROADCASTQ"), 0x259, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 59 /r - VPBROADCASTQ zmm, xmm/m64
    { const_string("VBROADCASTI32X4"), 0x25a, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 5a /r - VBROADCASTI32X4 ymm, m128
    { const_string("VBROADCASTI64X2"), 0x25a, -1, 0, 0, 1, 1, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 5a /r - VBROADCASTI64X2 ymm, m128
    { const_string("VBROADCASTI32X4"), 0x25a, -1, 0, 0, 1, 0, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 5a /r - VBROADCASTI32X4 zmm, m128
    { const_string("VBROADCASTI64X2"), 0x25a, -1, 0, 0, 1, 1, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 5a /r - VBROADCASTI64X2 zmm, m128
    { const_string("VBROADCASTI32X8"), 0x25b, -1, 0, 0, 1, 0, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 5b /r - VBROADCASTI32X8 zmm, m256
    { const_string("VBROADCASTI64X4"), 0x25b, -1, 0, 0, 1, 1, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 5b /r - VBROADCASTI64X4 zmm, m256
    { const_string("VPEXPANDB"), 0x262, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 62 /r - VPEXPANDB xmm, m128
    { const_string("VPEXPANDB"), 0x262, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 62 /r - VPEXPANDB xmm, xmm/m128
    { const_string("VPEXPANDW"), 0x262, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_m128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 62 /r - VPEXPANDW xmm, m128
    { const_string("VPEXPANDW"), 0x262, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 62 /r - VPEXPANDW xmm, xmm/m128
    { const_string("VPEXPANDB"), 0x262, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 62 /r - VPEXPANDB ymm, m256
    { const_string("VPEXPANDB"), 0x262, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 62 /r - VPEXPANDB ymm, ymm/m256
    { const_string("VPEXPANDW"), 0x262, -1, 0, 0, 1, 1, 1, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_m256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 62 /r - VPEXPANDW ymm, m256
    { const_string("VPEXPANDW"), 0x262, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 62 /r - VPEXPANDW ymm, ymm/m256
    { const_string("VPEXPANDB"), 0x262, -1, 0, 0, 1, 0, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 62 /r - VPEXPANDB zmm, m512
    { const_string("VPEXPANDB"), 0x262, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 62 /r - VPEXPANDB zmm, zmm/m512
    { const_string("VPEXPANDW"), 0x262, -1, 0, 0, 1, 1, 1, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_m512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 62 /r - VPEXPANDW zmm, m512
    { const_string("VPEXPANDW"), 0x262, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 62 /r - VPEXPANDW zmm, zmm/m512
    { const_string("VPCOMPRESSB"), 0x263, -1, 0, 0, 1, 0, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 63 /r - VPCOMPRESSB m128, xmm
    { const_string("VPCOMPRESSB"), 0x263, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 63 /r - VPCOMPRESSB xmm/m128, xmm
    { const_string("VPCOMPRESSW"), 0x263, -1, 0, 0, 1, 1, 1, -1, 0, 0, 2, {{OPERAND_m128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 63 /r - VPCOMPRESSW m128, xmm
    { const_string("VPCOMPRESSW"), 0x263, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 63 /r - VPCOMPRESSW xmm/m128, xmm
    { const_string("VPCOMPRESSB"), 0x263, -1, 0, 0, 1, 0, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 63 /r - VPCOMPRESSB m256, ymm
    { const_string("VPCOMPRESSB"), 0x263, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 63 /r - VPCOMPRESSB ymm/m256, ymm
    { const_string("VPCOMPRESSW"), 0x263, -1, 0, 0, 1, 1, 1, -1, 0, 1, 2, {{OPERAND_m256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 63 /r - VPCOMPRESSW m256, ymm
    { const_string("VPCOMPRESSW"), 0x263, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 63 /r - VPCOMPRESSW ymm/m256, ymm
    { const_string("VPCOMPRESSB"), 0x263, -1, 0, 0, 1, 0, 1, -1, 0, 2, 2, {{OPERAND_m512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 63 /r - VPCOMPRESSB m512, zmm
    { const_string("VPCOMPRESSB"), 0x263, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 63 /r - VPCOMPRESSB zmm/m512, zmm
    { const_string("VPCOMPRESSW"), 0x263, -1, 0, 0, 1, 1, 1, -1, 0, 2, 2, {{OPERAND_m512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 63 /r - VPCOMPRESSW m512, zmm
    { const_string("VPCOMPRESSW"), 0x263, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 63 /r - VPCOMPRESSW zmm/m512, zmm
    { const_string("VPBLENDMD"), 0x264, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 64 /r - VPBLENDMD xmm, vex128, xmm/m128
    { const_string("VPBLENDMQ"), 0x264, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 64 /r - VPBLENDMQ xmm, vex128, xmm/m128
    { const_string("VPBLENDMD"), 0x264, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 64 /r - VPBLENDMD ymm, vex256, ymm/m256
    { const_string("VPBLENDMQ"), 0x264, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 64 /r - VPBLENDMQ ymm, vex256, ymm/m256
    { const_string("VPBLENDMD"), 0x264, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 64 /r - VPBLENDMD zmm, vex512, zmm/m512
    { const_string("VPBLENDMQ"), 0x264, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 64 /r - VPBLENDMQ zmm, vex512, zmm/m512
    { const_string("VBLENDMPS"), 0x265, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 65 /r - VBLENDMPS xmm, vex128, xmm/m128
    { const_string("VBLENDMPD"), 0x265, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 65 /r - VBLENDMPD xmm, vex128, xmm/m128
    { const_string("VBLENDMPS"), 0x265, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 65 /r - VBLENDMPS ymm, vex256, ymm/m256
    { const_string("VBLENDMPD"), 0x265, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 65 /r - VBLENDMPD ymm, vex256, ymm/m256
    { const_string("VBLENDMPS"), 0x265, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 65 /r - VBLENDMPS zmm, vex512, zmm/m512
    { const_string("VBLENDMPD"), 0x265, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 65 /r - VBLENDMPD zmm, vex512, zmm/m512
    { const_string("VPBLENDMB"), 0x266, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 66 /r - VPBLENDMB xmm, vex128, xmm/m128
    { const_string("VPBLENDMW"), 0x266, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 66 /r - VPBLENDMW xmm, vex128, xmm/m128
    { const_string("VPBLENDMB"), 0x266, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 66 /r - VPBLENDMB ymm, vex256, ymm/m256
    { const_string("VPBLENDMW"), 0x266, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 66 /r - VPBLENDMW ymm, vex256, ymm/m256
    { const_string("VPBLENDMB"), 0x266, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 66 /r - VPBLENDMB zmm, vex512, zmm/m512
    { const_string("VPBLENDMW"), 0x266, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 66 /r - VPBLENDMW zmm, vex512, zmm/m512
    { const_string("VPSHLDVW"), 0x270, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 70 /r - VPSHLDVW xmm, vex128, xmm/m128
    { const_string("VPSHLDVW"), 0x270, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 70 /r - VPSHLDVW ymm, vex256, ymm/m256
    { const_string("VPSHLDVW"), 0x270, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 70 /r - VPSHLDVW zmm, vex512, zmm/m512
    { const_string("VPSHLDVD"), 0x271, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 71 /r - VPSHLDVD xmm, vex128, xmm/m128
    { const_string("VPSHLDVQ"), 0x271, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 71 /r - VPSHLDVQ xmm, vex128, xmm/m128
    { const_string("VPSHLDVD"), 0x271, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 71 /r - VPSHLDVD ymm, vex256, ymm/m256
    { const_string("VPSHLDVQ"), 0x271, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 71 /r - VPSHLDVQ ymm, vex256, ymm/m256
    { const_string("VPSHLDVD"), 0x271, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 71 /r - VPSHLDVD zmm, vex512, zmm/m512
    { const_string("VPSHLDVQ"), 0x271, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 71 /r - VPSHLDVQ zmm, vex512, zmm/m512
    { const_string("VPSHRDVW"), 0x272, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 72 /r - VPSHRDVW xmm, vex128, xmm/m128
    { const_string("VPSHRDVW"), 0x272, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 72 /r - VPSHRDVW ymm, vex256, ymm/m256
    { const_string("VPSHRDVW"), 0x272, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 72 /r - VPSHRDVW zmm, vex512, zmm/m512
    { const_string("VPSHRDVD"), 0x273, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 73 /r - VPSHRDVD xmm, vex128, xmm/m128
    { const_string("VPSHRDVQ"), 0x273, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 73 /r - VPSHRDVQ xmm, vex128, xmm/m128
    { const_string("VPSHRDVD"), 0x273, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 73 /r - VPSHRDVD ymm, vex256, ymm/m256
    { const_string("VPSHRDVQ"), 0x273, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 73 /r - VPSHRDVQ ymm, vex256, ymm/m256
    { const_string("VPSHRDVD"), 0x273, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 73 /r - VPSHRDVD zmm, vex512, zmm/m512
    { const_string("VPSHRDVQ"), 0x273, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 73 /r - VPSHRDVQ zmm, vex512, zmm/m512
    { const_string("VPERMI2B"), 0x275, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 75 /r - VPERMI2B xmm, vex128, xmm/m128
    { const_string("VPERMI2W"), 0x275, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 75 /r - VPERMI2W xmm, vex128, xmm/m128
    { const_string("VPERMI2B"), 0x275, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 75 /r - VPERMI2B ymm, vex256, ymm/m256
    { const_string("VPERMI2W"), 0x275, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 75 /r - VPERMI2W ymm, vex256, ymm/m256
    { const_string("VPERMI2B"), 0x275, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 75 /r - VPERMI2B zmm, vex512, zmm/m512
    { const_string("VPERMI2W"), 0x275, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 75 /r - VPERMI2W zmm, vex512, zmm/m512
    { const_string("VPERMI2D"), 0x276, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 76 /r - VPERMI2D xmm, vex128, xmm/m128
    { const_string("VPERMI2Q"), 0x276, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 76 /r - VPERMI2Q xmm, vex128, xmm/m128
    { const_string("VPERMI2D"), 0x276, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 76 /r - VPERMI2D ymm, vex256, ymm/m256
    { const_string("VPERMI2Q"), 0x276, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 76 /r - VPERMI2Q ymm, vex256, ymm/m256
    { const_string("VPERMI2D"), 0x276, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 76 /r - VPERMI2D zmm, vex512, zmm/m512
    { const_string("VPERMI2Q"), 0x276, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 76 /r - VPERMI2Q zmm, vex512, zmm/m512
    { const_string("VPERMI2PS"), 0x277, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 77 /r - VPERMI2PS xmm, vex128, xmm/m128
    { const_string("VPERMI2PD"), 0x277, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 77 /r - VPERMI2PD xmm, vex128, xmm/m128
    { const_string("VPERMI2PS"), 0x277, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 77 /r - VPERMI2PS ymm, vex256, ymm/m256
    { const_string("VPERMI2PD"), 0x277, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 77 /r - VPERMI2PD ymm, vex256, ymm/m256
    { const_string("VPERMI2PS"), 0x277, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 77 /r - VPERMI2PS zmm, vex512, zmm/m512
    { const_string("VPERMI2PD"), 0x277, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 77 /r - VPERMI2PD zmm, vex512, zmm/m512
    { const_string("VPBROADCASTB"), 0x278, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm8, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 78 /r - VPBROADCASTB xmm, xmm/m8
    { const_string("VPBROADCASTB"), 0x278, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm8, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 78 /r - VPBROADCASTB ymm, xmm/m8
    { const_string("VPBROADCASTB"), 0x278, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm8, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 78 /r - VPBROADCASTB zmm, xmm/m8
    { const_string("VPBROADCASTW"), 0x279, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 79 /r - VPBROADCASTW xmm, xmm/m64
    { const_string("VPBROADCASTW"), 0x279, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 79 /r - VPBROADCASTW ymm, xmm/m64
    { const_string("VPBROADCASTW"), 0x279, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 79 /r - VPBROADCASTW zmm, xmm/m64
    { const_string("VPBROADCASTB"), 0x27a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 7a /r - VPBROADCASTB xmm, r/m64
    { const_string("VPBROADCASTB"), 0x27a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 7a /r - VPBROADCASTB ymm, r/m64
    { const_string("VPBROADCASTB"), 0x27a, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 7a /r - VPBROADCASTB zmm, r/m64
    { const_string("VPBROADCASTW"), 0x27b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 7b /r - VPBROADCASTW xmm, r/m64
    { const_string("VPBROADCASTW"), 0x27b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 7b /r - VPBROADCASTW ymm, r/m64
    { const_string("VPBROADCASTW"), 0x27b, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 7b /r - VPBROADCASTW zmm, r/m64
    { const_string("VPBROADCASTD"), 0x27c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 7c /r - VPBROADCASTD xmm, r/m32
    { const_string("VPBROADCASTQ"), 0x27c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 7c /r - VPBROADCASTQ xmm, r/m64
    { const_string("VPBROADCASTD"), 0x27c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 7c /r - VPBROADCASTD ymm, r/m32
    { const_string("VPBROADCASTQ"), 0x27c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 7c /r - VPBROADCASTQ ymm, r/m64
    { const_string("VPBROADCASTD"), 0x27c, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_regm32, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 7c /r - VPBROADCASTD zmm, r/m32
    { const_string("VPBROADCASTQ"), 0x27c, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_regm64, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 7c /r - VPBROADCASTQ zmm, r/m64
    { const_string("VPERMT2B"), 0x27d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 7d /r - VPERMT2B xmm, vex128, xmm/m128
    { const_string("VPERMT2W"), 0x27d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 7d /r - VPERMT2W xmm, vex128, xmm/m128
    { const_string("VPERMT2B"), 0x27d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 7d /r - VPERMT2B ymm, vex256, ymm/m256
    { const_string("VPERMT2W"), 0x27d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 7d /r - VPERMT2W ymm, vex256, ymm/m256
    { const_string("VPERMT2B"), 0x27d, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 7d /r - VPERMT2B zmm, vex512, zmm/m512
    { const_string("VPERMT2W"), 0x27d, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 7d /r - VPERMT2W zmm, vex512, zmm/m512
    { const_string("VPERMT2D"), 0x27e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 7e /r - VPERMT2D xmm, vex128, xmm/m128
    { const_string("VPERMT2Q"), 0x27e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 7e /r - VPERMT2Q xmm, vex128, xmm/m128
    { const_string("VPERMT2D"), 0x27e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 7e /r - VPERMT2D ymm, vex256, ymm/m256
    { const_string("VPERMT2Q"), 0x27e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 7e /r - VPERMT2Q ymm, vex256, ymm/m256
    { const_string("VPERMT2D"), 0x27e, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 7e /r - VPERMT2D zmm, vex512, zmm/m512
    { const_string("VPERMT2Q"), 0x27e, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 7e /r - VPERMT2Q zmm, vex512, zmm/m512
    { const_string("VPERMT2PS"), 0x27f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 7f /r - VPERMT2PS xmm, vex128, xmm/m128
    { const_string("VPERMT2PD"), 0x27f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 7f /r - VPERMT2PD xmm, vex128, xmm/m128
    { const_string("VPERMT2PS"), 0x27f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 7f /r - VPERMT2PS ymm, vex256, ymm/m256
    { const_string("VPERMT2PD"), 0x27f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 7f /r - VPERMT2PD ymm, vex256, ymm/m256
    { const_string("VPERMT2PS"), 0x27f, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 7f /r - VPERMT2PS zmm, vex512, zmm/m512
    { const_string("VPERMT2PD"), 0x27f, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 7f /r - VPERMT2PD zmm, vex512, zmm/m512
    { const_string("VPMULTISHIFTQB"), 0x283, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 83 /r - VPMULTISHIFTQB xmm, vex128, xmm/m128
    { const_string("VPMULTISHIFTQB"), 0x283, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 83 /r - VPMULTISHIFTQB ymm, vex256, ymm/m256
    { const_string("VPMULTISHIFTQB"), 0x283, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 83 /r - VPMULTISHIFTQB zmm, vex512, zmm/m512
    { const_string("VEXPANDPS"), 0x288, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 88 /r - VEXPANDPS xmm, xmm/m128
    { const_string("VEXPANDPD"), 0x288, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 88 /r - VEXPANDPD xmm, xmm/m128
    { const_string("VEXPANDPS"), 0x288, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 88 /r - VEXPANDPS ymm, ymm/m256
    { const_string("VEXPANDPD"), 0x288, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 88 /r - VEXPANDPD ymm, ymm/m256
    { const_string("VEXPANDPS"), 0x288, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 88 /r - VEXPANDPS zmm, zmm/m512
    { const_string("VEXPANDPD"), 0x288, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 88 /r - VEXPANDPD zmm, zmm/m512
    { const_string("VPEXPANDD"), 0x289, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 89 /r - VPEXPANDD xmm, xmm/m128
    { const_string("VPEXPANDQ"), 0x289, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 89 /r - VPEXPANDQ xmm, xmm/m128
    { const_string("VPEXPANDD"), 0x289, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 89 /r - VPEXPANDD ymm, ymm/m256
    { const_string("VPEXPANDQ"), 0x289, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 89 /r - VPEXPANDQ ymm, ymm/m256
    { const_string("VPEXPANDD"), 0x289, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 89 /r - VPEXPANDD zmm, zmm/m512
    { const_string("VPEXPANDQ"), 0x289, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 89 /r - VPEXPANDQ zmm, zmm/m512
    { const_string("VCOMPRESSPS"), 0x28a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 8a /r - VCOMPRESSPS xmm/m128, xmm
    { const_string("VCOMPRESSPD"), 0x28a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 8a /r - VCOMPRESSPD xmm/m128, xmm
    { const_string("VCOMPRESSPS"), 0x28a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 8a /r - VCOMPRESSPS ymm/m256, ymm
    { const_string("VCOMPRESSPD"), 0x28a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 8a /r - VCOMPRESSPD ymm/m256, ymm
    { const_string("VCOMPRESSPS"), 0x28a, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 8a /r - VCOMPRESSPS zmm/m512, zmm
    { const_string("VCOMPRESSPD"), 0x28a, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 8a /r - VCOMPRESSPD zmm/m512, zmm
    { const_string("VPCOMPRESSD"), 0x28b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 8b /r - VPCOMPRESSD xmm/m128, xmm
    { const_string("VPCOMPRESSQ"), 0x28b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 8b /r - VPCOMPRESSQ xmm/m128, xmm
    { const_string("VPCOMPRESSD"), 0x28b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 8b /r - VPCOMPRESSD ymm/m256, ymm
    { const_string("VPCOMPRESSQ"), 0x28b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 8b /r - VPCOMPRESSQ ymm/m256, ymm
    { const_string("VPCOMPRESSD"), 0x28b, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 8b /r - VPCOMPRESSD zmm/m512, zmm
    { const_string("VPCOMPRESSQ"), 0x28b, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmmm512, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 8b /r - VPCOMPRESSQ zmm/m512, zmm
    { const_string("VPERMB"), 0x28d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 8d /r - VPERMB xmm, vex128, xmm/m128
    { const_string("VPERMW"), 0x28d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 8d /r - VPERMW xmm, vex128, xmm/m128
    { const_string("VPERMB"), 0x28d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 8d /r - VPERMB ymm, vex256, ymm/m256
    { const_string("VPERMW"), 0x28d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 8d /r - VPERMW ymm, vex256, ymm/m256
    { const_string("VPERMB"), 0x28d, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 8d /r - VPERMB zmm, vex512, zmm/m512
    { const_string("VPERMW"), 0x28d, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 8d /r - VPERMW zmm, vex512, zmm/m512
    { const_string("VPSHUFBITQMB"), 0x28f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 8f /r - VPSHUFBITQMB k, vex128, xmm/m128
    { const_string("VPSHUFBITQMB"), 0x28f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 8f /r - VPSHUFBITQMB k, vex256, ymm/m256
    { const_string("VPSHUFBITQMB"), 0x28f, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 8f /r - VPSHUFBITQMB k, vex512, zmm/m512
    { const_string("VPGATHERDD"), 0x290, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 90 - VPGATHERDD xmm, vm32x
    { const_string("VPGATHERDQ"), 0x290, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 90 - VPGATHERDQ xmm, vm32x
    { const_string("VPGATHERDD"), 0x290, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32y, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 90 - VPGATHERDD ymm, vm32y
    { const_string("VPGATHERDQ"), 0x290, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 90 - VPGATHERDQ ymm, vm32x
    { const_string("VPGATHERDD"), 0x290, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32z, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 90 - VPGATHERDD zmm, vm32z
    { const_string("VPGATHERDQ"), 0x290, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32y, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 90 - VPGATHERDQ zmm, vm32y
    { const_string("VPGATHERQD"), 0x291, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64x, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 91 - VPGATHERQD xmm, vm64x
    { const_string("VPGATHERQQ"), 0x291, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64x, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 91 - VPGATHERQQ xmm, vm64x
    { const_string("VPGATHERQD"), 0x291, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64y, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 91 - VPGATHERQD xmm, vm64y
    { const_string("VPGATHERQQ"), 0x291, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64y, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 91 - VPGATHERQQ ymm, vm64y
    { const_string("VPGATHERQD"), 0x291, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64z, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 91 - VPGATHERQD ymm, vm64z
    { const_string("VPGATHERQQ"), 0x291, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64z, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 91 - VPGATHERQQ zmm, vm64z
    { const_string("VGATHERDPS"), 0x292, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 92 - VGATHERDPS xmm, vm32x
    { const_string("VGATHERDPD"), 0x292, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 92 - VGATHERDPD xmm, vm32x
    { const_string("VGATHERDPS"), 0x292, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32y, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 92 - VGATHERDPS ymm, vm32y
    { const_string("VGATHERDPD"), 0x292, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32x, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 92 - VGATHERDPD ymm, vm32x
    { const_string("VGATHERDPS"), 0x292, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32z, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 92 - VGATHERDPS zmm, vm32z
    { const_string("VGATHERDPD"), 0x292, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm32y, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 92 - VGATHERDPD zmm, vm32y
    { const_string("VGATHERQPS"), 0x293, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64x, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 93 - VGATHERQPS xmm, vm64x
    { const_string("VGATHERQPD"), 0x293, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64x, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 93 - VGATHERQPD xmm, vm64x
    { const_string("VGATHERQPS"), 0x293, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64y, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 93 - VGATHERQPS xmm, vm64y
    { const_string("VGATHERQPD"), 0x293, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64y, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 93 - VGATHERQPD ymm, vm64y
    { const_string("VGATHERQPS"), 0x293, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64z, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 93 - VGATHERQPS ymm, vm64z
    { const_string("VGATHERQPD"), 0x293, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vm64z, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 93 - VGATHERQPD zmm, vm64z
    { const_string("VFMADDSUB132PS"), 0x296, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 96 /r - VFMADDSUB132PS xmm, vex128, xmm/m128
    { const_string("VFMADDSUB132PD"), 0x296, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 96 /r - VFMADDSUB132PD xmm, vex128, xmm/m128
    { const_string("VFMADDSUB132PS"), 0x296, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 96 /r - VFMADDSUB132PS ymm, vex256, ymm/m256
    { const_string("VFMADDSUB132PD"), 0x296, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 96 /r - VFMADDSUB132PD ymm, vex256, ymm/m256
    { const_string("VFMADDSUB132PS"), 0x296, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 96 /r - VFMADDSUB132PS zmm, vex512, zmm/m512
    { const_string("VFMADDSUB132PD"), 0x296, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 96 /r - VFMADDSUB132PD zmm, vex512, zmm/m512
    { const_string("VFMSUBADD132PS"), 0x297, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 97 /r - VFMSUBADD132PS xmm, vex128, xmm/m128
    { const_string("VFMSUBADD132PD"), 0x297, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 97 /r - VFMSUBADD132PD xmm, vex128, xmm/m128
    { const_string("VFMSUBADD132PS"), 0x297, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 97 /r - VFMSUBADD132PS ymm, vex256, ymm/m256
    { const_string("VFMSUBADD132PD"), 0x297, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 97 /r - VFMSUBADD132PD ymm, vex256, ymm/m256
    { const_string("VFMSUBADD132PS"), 0x297, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 97 /r - VFMSUBADD132PS zmm, vex512, zmm/m512
    { const_string("VFMSUBADD132PD"), 0x297, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 97 /r - VFMSUBADD132PD zmm, vex512, zmm/m512
    { const_string("VFMADD132PS"), 0x298, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 98 /r - VFMADD132PS xmm, vex128, xmm/m128
    { const_string("VFMADD132PD"), 0x298, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 98 /r - VFMADD132PD xmm, vex128, xmm/m128
    { const_string("VFMADD132PS"), 0x298, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 98 /r - VFMADD132PS ymm, vex256, ymm/m256
    { const_string("VFMADD132PD"), 0x298, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 98 /r - VFMADD132PD ymm, vex256, ymm/m256
    { const_string("VFMADD132PS"), 0x298, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 98 /r - VFMADD132PS zmm, vex512, zmm/m512
    { const_string("VFMADD132PD"), 0x298, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 98 /r - VFMADD132PD zmm, vex512, zmm/m512
    { const_string("VFMADD132SS"), 0x299, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 99 /r - VFMADD132SS xmm, vex128, xmm/m32
    { const_string("VFMADD132SD"), 0x299, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 99 /r - VFMADD132SD xmm, vex128, xmm/m64
    { const_string("VFMADD132SS"), 0x299, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 99 /r - VFMADD132SS xmm, vex128, xmm/m32
    { const_string("VFMADD132SD"), 0x299, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 99 /r - VFMADD132SD xmm, vex128, xmm/m64
    { const_string("VFMSUB132PS"), 0x29a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 9a /r - VFMSUB132PS xmm, vex128, xmm/m128
    { const_string("VFMSUB132PD"), 0x29a, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 9a /r - VFMSUB132PD xmm, vex128, xmm/m128
    { const_string("VFMSUB132PS"), 0x29a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 9a /r - VFMSUB132PS ymm, vex256, ymm/m256
    { const_string("VFMSUB132PD"), 0x29a, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 9a /r - VFMSUB132PD ymm, vex256, ymm/m256
    { const_string("VFMSUB132PS"), 0x29a, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 9a /r - VFMSUB132PS zmm, vex512, zmm/m512
    { const_string("VFMSUB132PD"), 0x29a, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 9a /r - VFMSUB132PD zmm, vex512, zmm/m512
    { const_string("VFMSUB132SS"), 0x29b, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 9b /r - VFMSUB132SS xmm, vex128, xmm/m32
    { const_string("VFMSUB132SD"), 0x29b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 9b /r - VFMSUB132SD xmm, vex128, xmm/m64
    { const_string("VFMSUB132SS"), 0x29b, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 9b /r - VFMSUB132SS xmm, vex128, xmm/m32
    { const_string("VFMSUB132SD"), 0x29b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 9b /r - VFMSUB132SD xmm, vex128, xmm/m64
    { const_string("VFNMADD132PS"), 0x29c, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 9c /r - VFNMADD132PS xmm, vex128, xmm/m128
    { const_string("VFNMADD132PD"), 0x29c, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 9c /r - VFNMADD132PD xmm, vex128, xmm/m128
    { const_string("VFNMADD132PS"), 0x29c, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 9c /r - VFNMADD132PS ymm, vex256, ymm/m256
    { const_string("VFNMADD132PD"), 0x29c, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 9c /r - VFNMADD132PD ymm, vex256, ymm/m256
    { const_string("VFNMADD132PS"), 0x29c, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 9c /r - VFNMADD132PS zmm, vex512, zmm/m512
    { const_string("VFNMADD132PD"), 0x29c, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 9c /r - VFNMADD132PD zmm, vex512, zmm/m512
    { const_string("VFNMADD132SS"), 0x29d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 9d /r - VFNMADD132SS xmm, vex128, xmm/m32
    { const_string("VFNMADD132SD"), 0x29d, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 9d /r - VFNMADD132SD xmm, vex128, xmm/m64
    { const_string("VFNMADD132SS"), 0x29d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 9d /r - VFNMADD132SS xmm, vex128, xmm/m32
    { const_string("VFNMADD132SD"), 0x29d, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 9d /r - VFNMADD132SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB132PS"), 0x29e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 9e /r - VFNMSUB132PS xmm, vex128, xmm/m128
    { const_string("VFNMSUB132PD"), 0x29e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 9e /r - VFNMSUB132PD xmm, vex128, xmm/m128
    { const_string("VFNMSUB132PS"), 0x29e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 9e /r - VFNMSUB132PS ymm, vex256, ymm/m256
    { const_string("VFNMSUB132PD"), 0x29e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 9e /r - VFNMSUB132PD ymm, vex256, ymm/m256
    { const_string("VFNMSUB132PS"), 0x29e, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 9e /r - VFNMSUB132PS zmm, vex512, zmm/m512
    { const_string("VFNMSUB132PD"), 0x29e, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 9e /r - VFNMSUB132PD zmm, vex512, zmm/m512
    { const_string("VFNMSUB132SS"), 0x29f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 9f /r - VFNMSUB132SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB132SD"), 0x29f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 9f /r - VFNMSUB132SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB132SS"), 0x29f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 9f /r - VFNMSUB132SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB132SD"), 0x29f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 9f /r - VFNMSUB132SD xmm, vex128, xmm/m64
    { const_string("VPSCATTERDD"), 0x2a0, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_vm32x, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 a0 - VPSCATTERDD vm32x, xmm
    { const_string("VPSCATTERDQ"), 0x2a0, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_vm32x, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 a0 - VPSCATTERDQ vm32x, xmm
    { const_string("VPSCATTERDD"), 0x2a0, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_vm32y, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 a0 - VPSCATTERDD vm32y, ymm
    { const_string("VPSCATTERDQ"), 0x2a0, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_vm32x, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 a0 - VPSCATTERDQ vm32x, ymm
    { const_string("VPSCATTERDD"), 0x2a0, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_vm32z, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 a0 - VPSCATTERDD vm32z, zmm
    { const_string("VPSCATTERDQ"), 0x2a0, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_vm32y, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 a0 - VPSCATTERDQ vm32y, zmm
    { const_string("VPSCATTERQD"), 0x2a1, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_vm64x, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 a1 - VPSCATTERQD vm64x, xmm
    { const_string("VPSCATTERQQ"), 0x2a1, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_vm64x, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 a1 - VPSCATTERQQ vm64x, xmm
    { const_string("VPSCATTERQD"), 0x2a1, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_vm64y, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 a1 - VPSCATTERQD vm64y, xmm
    { const_string("VPSCATTERQQ"), 0x2a1, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_vm64y, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 a1 - VPSCATTERQQ vm64y, ymm
    { const_string("VPSCATTERQD"), 0x2a1, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_vm64z, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 a1 - VPSCATTERQD vm64z, ymm
    { const_string("VPSCATTERQQ"), 0x2a1, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_vm64z, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 a1 - VPSCATTERQQ vm64z, zmm
    { const_string("VSCATTERDPS"), 0x2a2, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_vm32x, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 a2 - VSCATTERDPS vm32x, xmm
    { const_string("VSCATTERDPD"), 0x2a2, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_vm32x, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 a2 - VSCATTERDPD vm32x, xmm
    { const_string("VSCATTERDPS"), 0x2a2, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_vm32y, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 a2 - VSCATTERDPS vm32y, ymm
    { const_string("VSCATTERDPD"), 0x2a2, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_vm32x, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 a2 - VSCATTERDPD vm32x, ymm
    { const_string("VSCATTERDPS"), 0x2a2, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_vm32z, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 a2 - VSCATTERDPS vm32z, zmm
    { const_string("VSCATTERDPD"), 0x2a2, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_vm32y, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 a2 - VSCATTERDPD vm32y, zmm
    { const_string("VSCATTERQPS"), 0x2a3, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_vm64x, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 a3 - VSCATTERQPS vm64x, xmm
    { const_string("VSCATTERQPD"), 0x2a3, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_vm64x, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 a3 - VSCATTERQPD vm64x, xmm
    { const_string("VSCATTERQPS"), 0x2a3, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_vm64y, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 a3 - VSCATTERQPS vm64y, xmm
    { const_string("VSCATTERQPD"), 0x2a3, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_vm64y, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 a3 - VSCATTERQPD vm64y, ymm
    { const_string("VSCATTERQPS"), 0x2a3, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_vm64z, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 a3 - VSCATTERQPS vm64z, ymm
    { const_string("VSCATTERQPD"), 0x2a3, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_vm64z, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 a3 - VSCATTERQPD vm64z, zmm
    { const_string("VFMADDSUB213PS"), 0x2a6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 a6 /r - VFMADDSUB213PS xmm, vex128, xmm/m128
    { const_string("VFMADDSUB213PD"), 0x2a6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 a6 /r - VFMADDSUB213PD xmm, vex128, xmm/m128
    { const_string("VFMADDSUB213PS"), 0x2a6, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 a6 /r - VFMADDSUB213PS ymm, vex256, ymm/m256
    { const_string("VFMADDSUB213PD"), 0x2a6, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 a6 /r - VFMADDSUB213PD ymm, vex256, ymm/m256
    { const_string("VFMADDSUB213PS"), 0x2a6, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 a6 /r - VFMADDSUB213PS zmm, vex512, zmm/m512
    { const_string("VFMADDSUB213PD"), 0x2a6, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 a6 /r - VFMADDSUB213PD zmm, vex512, zmm/m512
    { const_string("VFMSUBADD213PS"), 0x2a7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 a7 /r - VFMSUBADD213PS xmm, vex128, xmm/m128
    { const_string("VFMSUBADD213PD"), 0x2a7, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 a7 /r - VFMSUBADD213PD xmm, vex128, xmm/m128
    { const_string("VFMSUBADD213PS"), 0x2a7, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 a7 /r - VFMSUBADD213PS ymm, vex256, ymm/m256
    { const_string("VFMSUBADD213PD"), 0x2a7, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 a7 /r - VFMSUBADD213PD ymm, vex256, ymm/m256
    { const_string("VFMSUBADD213PS"), 0x2a7, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 a7 /r - VFMSUBADD213PS zmm, vex512, zmm/m512
    { const_string("VFMSUBADD213PD"), 0x2a7, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 a7 /r - VFMSUBADD213PD zmm, vex512, zmm/m512
    { const_string("VFMADD213PS"), 0x2a8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 a8 /r - VFMADD213PS xmm, vex128, xmm/m128
    { const_string("VFMADD213PD"), 0x2a8, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 a8 /r - VFMADD213PD xmm, vex128, xmm/m128
    { const_string("VFMADD213PS"), 0x2a8, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 a8 /r - VFMADD213PS ymm, vex256, ymm/m256
    { const_string("VFMADD213PD"), 0x2a8, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 a8 /r - VFMADD213PD ymm, vex256, ymm/m256
    { const_string("VFMADD213PS"), 0x2a8, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 a8 /r - VFMADD213PS zmm, vex512, zmm/m512
    { const_string("VFMADD213PD"), 0x2a8, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 a8 /r - VFMADD213PD zmm, vex512, zmm/m512
    { const_string("VFMADD213SS"), 0x2a9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 a9 /r - VFMADD213SS xmm, vex128, xmm/m32
    { const_string("VFMADD213SD"), 0x2a9, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 a9 /r - VFMADD213SD xmm, vex128, xmm/m64
    { const_string("VFMADD213SS"), 0x2a9, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 a9 /r - VFMADD213SS xmm, vex128, xmm/m32
    { const_string("VFMADD213SD"), 0x2a9, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 a9 /r - VFMADD213SD xmm, vex128, xmm/m64
    { const_string("VFMSUB213PS"), 0x2aa, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 aa /r - VFMSUB213PS xmm, vex128, xmm/m128
    { const_string("VFMSUB213PD"), 0x2aa, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 aa /r - VFMSUB213PD xmm, vex128, xmm/m128
    { const_string("VFMSUB213PS"), 0x2aa, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 aa /r - VFMSUB213PS ymm, vex256, ymm/m256
    { const_string("VFMSUB213PD"), 0x2aa, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 aa /r - VFMSUB213PD ymm, vex256, ymm/m256
    { const_string("VFMSUB213PS"), 0x2aa, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 aa /r - VFMSUB213PS zmm, vex512, zmm/m512
    { const_string("VFMSUB213PD"), 0x2aa, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 aa /r - VFMSUB213PD zmm, vex512, zmm/m512
    { const_string("VFMSUB213SS"), 0x2ab, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 ab /r - VFMSUB213SS xmm, vex128, xmm/m32
    { const_string("VFMSUB213SD"), 0x2ab, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 ab /r - VFMSUB213SD xmm, vex128, xmm/m64
    { const_string("VFMSUB213SS"), 0x2ab, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 ab /r - VFMSUB213SS xmm, vex128, xmm/m32
    { const_string("VFMSUB213SD"), 0x2ab, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 ab /r - VFMSUB213SD xmm, vex128, xmm/m64
    { const_string("VFNMADD213PS"), 0x2ac, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 ac /r - VFNMADD213PS xmm, vex128, xmm/m128
    { const_string("VFNMADD213PD"), 0x2ac, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 ac /r - VFNMADD213PD xmm, vex128, xmm/m128
    { const_string("VFNMADD213PS"), 0x2ac, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 ac /r - VFNMADD213PS ymm, vex256, ymm/m256
    { const_string("VFNMADD213PD"), 0x2ac, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 ac /r - VFNMADD213PD ymm, vex256, ymm/m256
    { const_string("VFNMADD213PS"), 0x2ac, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 ac /r - VFNMADD213PS zmm, vex512, zmm/m512
    { const_string("VFNMADD213PD"), 0x2ac, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 ac /r - VFNMADD213PD zmm, vex512, zmm/m512
    { const_string("VFNMADD213SS"), 0x2ad, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 ad /r - VFNMADD213SS xmm, vex128, xmm/m32
    { const_string("VFNMADD213SD"), 0x2ad, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 ad /r - VFNMADD213SD xmm, vex128, xmm/m64
    { const_string("VFNMADD213SS"), 0x2ad, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 ad /r - VFNMADD213SS xmm, vex128, xmm/m32
    { const_string("VFNMADD213SD"), 0x2ad, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 ad /r - VFNMADD213SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB213PS"), 0x2ae, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 ae /r - VFNMSUB213PS xmm, vex128, xmm/m128
    { const_string("VFNMSUB213PD"), 0x2ae, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 ae /r - VFNMSUB213PD xmm, vex128, xmm/m128
    { const_string("VFNMSUB213PS"), 0x2ae, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 ae /r - VFNMSUB213PS ymm, vex256, ymm/m256
    { const_string("VFNMSUB213PD"), 0x2ae, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 ae /r - VFNMSUB213PD ymm, vex256, ymm/m256
    { const_string("VFNMSUB213PS"), 0x2ae, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 ae /r - VFNMSUB213PS zmm, vex512, zmm/m512
    { const_string("VFNMSUB213PD"), 0x2ae, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 ae /r - VFNMSUB213PD zmm, vex512, zmm/m512
    { const_string("VFNMSUB213SS"), 0x2af, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 af /r - VFNMSUB213SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB213SD"), 0x2af, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 af /r - VFNMSUB213SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB213SS"), 0x2af, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 af /r - VFNMSUB213SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB213SD"), 0x2af, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 af /r - VFNMSUB213SD xmm, vex128, xmm/m64
    { const_string("VPMADD52LUQ"), 0x2b4, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 b4 /r - VPMADD52LUQ xmm, vex128, xmm/m128
    { const_string("VPMADD52LUQ"), 0x2b4, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 b4 /r - VPMADD52LUQ ymm, vex256, ymm/m256
    { const_string("VPMADD52LUQ"), 0x2b4, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 b4 /r - VPMADD52LUQ zmm, vex512, zmm/m512
    { const_string("VPMADD52HUQ"), 0x2b5, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 b5 /r - VPMADD52HUQ xmm, vex128, xmm/m128
    { const_string("VPMADD52HUQ"), 0x2b5, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 b5 /r - VPMADD52HUQ ymm, vex256, ymm/m256
    { const_string("VPMADD52HUQ"), 0x2b5, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 b5 /r - VPMADD52HUQ zmm, vex512, zmm/m512
    { const_string("VFMADDSUB231PS"), 0x2b6, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 b6 /r - VFMADDSUB231PS xmm, vex128, xmm/m128
    { const_string("VFMADDSUB231PD"), 0x2b6, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 b6 /r - VFMADDSUB231PD xmm, vex128, xmm/m128
    { const_string("VFMADDSUB231PS"), 0x2b6, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 b6 /r - VFMADDSUB231PS ymm, vex256, ymm/m256
    { const_string("VFMADDSUB231PD"), 0x2b6, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 b6 /r - VFMADDSUB231PD ymm, vex256, ymm/m256
    { const_string("VFMADDSUB231PS"), 0x2b6, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 b6 /r - VFMADDSUB231PS zmm, vex512, zmm/m512
    { const_string("VFMADDSUB231PD"), 0x2b6, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 b6 /r - VFMADDSUB231PD zmm, vex512, zmm/m512
    { const_string("VFMSUBADD231PS"), 0x2b7, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 b7 /r - VFMSUBADD231PS xmm, vex128, xmm/m128
    { const_string("VFMSUBADD231PD"), 0x2b7, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 b7 /r - VFMSUBADD231PD xmm, vex128, xmm/m128
    { const_string("VFMSUBADD231PS"), 0x2b7, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 b7 /r - VFMSUBADD231PS ymm, vex256, ymm/m256
    { const_string("VFMSUBADD231PD"), 0x2b7, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 b7 /r - VFMSUBADD231PD ymm, vex256, ymm/m256
    { const_string("VFMSUBADD231PS"), 0x2b7, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 b7 /r - VFMSUBADD231PS zmm, vex512, zmm/m512
    { const_string("VFMSUBADD231PD"), 0x2b7, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 b7 /r - VFMSUBADD231PD zmm, vex512, zmm/m512
    { const_string("VFMADD231PS"), 0x2b8, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 b8 /r - VFMADD231PS xmm, vex128, xmm/m128
    { const_string("VFMADD231PD"), 0x2b8, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 b8 /r - VFMADD231PD xmm, vex128, xmm/m128
    { const_string("VFMADD231PS"), 0x2b8, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 b8 /r - VFMADD231PS ymm, vex256, ymm/m256
    { const_string("VFMADD231PD"), 0x2b8, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 b8 /r - VFMADD231PD ymm, vex256, ymm/m256
    { const_string("VFMADD231PS"), 0x2b8, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 b8 /r - VFMADD231PS zmm, vex512, zmm/m512
    { const_string("VFMADD231PD"), 0x2b8, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 b8 /r - VFMADD231PD zmm, vex512, zmm/m512
    { const_string("VFMADD231SS"), 0x2b9, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 b9 /r - VFMADD231SS xmm, vex128, xmm/m32
    { const_string("VFMADD231SD"), 0x2b9, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 b9 /r - VFMADD231SD xmm, vex128, xmm/m64
    { const_string("VFMADD231SS"), 0x2b9, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 b9 /r - VFMADD231SS xmm, vex128, xmm/m32
    { const_string("VFMADD231SD"), 0x2b9, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 b9 /r - VFMADD231SD xmm, vex128, xmm/m64
    { const_string("VFMSUB231PS"), 0x2ba, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 ba /r - VFMSUB231PS xmm, vex128, xmm/m128
    { const_string("VFMSUB231PD"), 0x2ba, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 ba /r - VFMSUB231PD xmm, vex128, xmm/m128
    { const_string("VFMSUB231PS"), 0x2ba, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 ba /r - VFMSUB231PS ymm, vex256, ymm/m256
    { const_string("VFMSUB231PD"), 0x2ba, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 ba /r - VFMSUB231PD ymm, vex256, ymm/m256
    { const_string("VFMSUB231PS"), 0x2ba, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 ba /r - VFMSUB231PS zmm, vex512, zmm/m512
    { const_string("VFMSUB231PD"), 0x2ba, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 ba /r - VFMSUB231PD zmm, vex512, zmm/m512
    { const_string("VFMSUB231SS"), 0x2bb, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 bb /r - VFMSUB231SS xmm, vex128, xmm/m32
    { const_string("VFMSUB231SD"), 0x2bb, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 bb /r - VFMSUB231SD xmm, vex128, xmm/m64
    { const_string("VFMSUB231SS"), 0x2bb, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 bb /r - VFMSUB231SS xmm, vex128, xmm/m32
    { const_string("VFMSUB231SD"), 0x2bb, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 bb /r - VFMSUB231SD xmm, vex128, xmm/m64
    { const_string("VFNMADD231PS"), 0x2bc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 bc /r - VFNMADD231PS xmm, vex128, xmm/m128
    { const_string("VFNMADD231PD"), 0x2bc, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 bc /r - VFNMADD231PD xmm, vex128, xmm/m128
    { const_string("VFNMADD231PS"), 0x2bc, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 bc /r - VFNMADD231PS ymm, vex256, ymm/m256
    { const_string("VFNMADD231PD"), 0x2bc, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 bc /r - VFNMADD231PD ymm, vex256, ymm/m256
    { const_string("VFNMADD231PS"), 0x2bc, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 bc /r - VFNMADD231PS zmm, vex512, zmm/m512
    { const_string("VFNMADD231PD"), 0x2bc, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 bc /r - VFNMADD231PD zmm, vex512, zmm/m512
    { const_string("VFNMADD231SS"), 0x2bd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 bd /r - VFNMADD231SS xmm, vex128, xmm/m32
    { const_string("VFNMADD231SD"), 0x2bd, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 bd /r - VFNMADD231SD xmm, vex128, xmm/m64
    { const_string("VFNMADD231SS"), 0x2bd, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 bd /r - VFNMADD231SS xmm, vex128, xmm/m32
    { const_string("VFNMADD231SD"), 0x2bd, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 bd /r - VFNMADD231SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB231PS"), 0x2be, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 be /r - VFNMSUB231PS xmm, vex128, xmm/m128
    { const_string("VFNMSUB231PD"), 0x2be, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 be /r - VFNMSUB231PD xmm, vex128, xmm/m128
    { const_string("VFNMSUB231PS"), 0x2be, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 be /r - VFNMSUB231PS ymm, vex256, ymm/m256
    { const_string("VFNMSUB231PD"), 0x2be, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 be /r - VFNMSUB231PD ymm, vex256, ymm/m256
    { const_string("VFNMSUB231PS"), 0x2be, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 be /r - VFNMSUB231PS zmm, vex512, zmm/m512
    { const_string("VFNMSUB231PD"), 0x2be, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 be /r - VFNMSUB231PD zmm, vex512, zmm/m512
    { const_string("VFNMSUB231SS"), 0x2bf, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 bf /r - VFNMSUB231SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB231SD"), 0x2bf, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 bf /r - VFNMSUB231SD xmm, vex128, xmm/m64
    { const_string("VFNMSUB231SS"), 0x2bf, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 bf /r - VFNMSUB231SS xmm, vex128, xmm/m32
    { const_string("VFNMSUB231SD"), 0x2bf, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 bf /r - VFNMSUB231SD xmm, vex128, xmm/m64
    { const_string("VPCONFLICTD"), 0x2c4, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 c4 /r - VPCONFLICTD xmm, xmm/m128
    { const_string("VPCONFLICTQ"), 0x2c4, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 c4 /r - VPCONFLICTQ xmm, xmm/m128
    { const_string("VPCONFLICTD"), 0x2c4, -1, 0, 0, 1, 0, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 c4 /r - VPCONFLICTD ymm, ymm/m256
    { const_string("VPCONFLICTQ"), 0x2c4, -1, 0, 0, 1, 1, 0, -1, 0, 1, 2, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 c4 /r - VPCONFLICTQ ymm, ymm/m256
    { const_string("VPCONFLICTD"), 0x2c4, -1, 0, 0, 1, 0, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 c4 /r - VPCONFLICTD zmm, zmm/m512
    { const_string("VPCONFLICTQ"), 0x2c4, -1, 0, 0, 1, 1, 0, -1, 0, 2, 2, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 c4 /r - VPCONFLICTQ zmm, zmm/m512
    { const_string("VGF2P8MULB"), 0x2cf, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 cf /r - VGF2P8MULB xmm, vex128, xmm/m128
    { const_string("VGF2P8MULB"), 0x2cf, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 cf /r - VGF2P8MULB ymm, vex256, ymm/m256
    { const_string("VGF2P8MULB"), 0x2cf, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 cf /r - VGF2P8MULB zmm, vex512, zmm/m512
    { const_string("VAESENC"), 0x2dc, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 dc /r - VAESENC xmm, vex128, xmm/m128
    { const_string("VAESENC"), 0x2dc, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 dc /r - VAESENC xmm, vex128, xmm/m128
    { const_string("VAESENC"), 0x2dc, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 dc /r - VAESENC ymm, vex256, ymm/m256
    { const_string("VAESENC"), 0x2dc, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 dc /r - VAESENC ymm, vex256, ymm/m256
    { const_string("VAESENC"), 0x2dc, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 dc /r - VAESENC zmm, vex512, zmm/m512
    { const_string("VAESENC"), 0x2dc, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 dc /r - VAESENC zmm, vex512, zmm/m512
    { const_string("VAESENCLAST"), 0x2dd, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 dd /r - VAESENCLAST xmm, vex128, xmm/m128
    { const_string("VAESENCLAST"), 0x2dd, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 dd /r - VAESENCLAST xmm, vex128, xmm/m128
    { const_string("VAESENCLAST"), 0x2dd, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 dd /r - VAESENCLAST ymm, vex256, ymm/m256
    { const_string("VAESENCLAST"), 0x2dd, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 dd /r - VAESENCLAST ymm, vex256, ymm/m256
    { const_string("VAESENCLAST"), 0x2dd, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 dd /r - VAESENCLAST zmm, vex512, zmm/m512
    { const_string("VAESENCLAST"), 0x2dd, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 dd /r - VAESENCLAST zmm, vex512, zmm/m512
    { const_string("VAESDEC"), 0x2de, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 de /r - VAESDEC xmm, vex128, xmm/m128
    { const_string("VAESDEC"), 0x2de, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 de /r - VAESDEC xmm, vex128, xmm/m128
    { const_string("VAESDEC"), 0x2de, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 de /r - VAESDEC ymm, vex256, ymm/m256
    { const_string("VAESDEC"), 0x2de, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 de /r - VAESDEC ymm, vex256, ymm/m256
    { const_string("VAESDEC"), 0x2de, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 de /r - VAESDEC zmm, vex512, zmm/m512
    { const_string("VAESDEC"), 0x2de, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 de /r - VAESDEC zmm, vex512, zmm/m512
    { const_string("VAESDECLAST"), 0x2df, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W0 df /r - VAESDECLAST xmm, vex128, xmm/m128
    { const_string("VAESDECLAST"), 0x2df, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}} }, // EVEX.128.66.0F38.W1 df /r - VAESDECLAST xmm, vex128, xmm/m128
    { const_string("VAESDECLAST"), 0x2df, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W0 df /r - VAESDECLAST ymm, vex256, ymm/m256
    { const_string("VAESDECLAST"), 0x2df, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}} }, // EVEX.256.66.0F38.W1 df /r - VAESDECLAST ymm, vex256, ymm/m256
    { const_string("VAESDECLAST"), 0x2df, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W0 df /r - VAESDECLAST zmm, vex512, zmm/m512
    { const_string("VAESDECLAST"), 0x2df, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}} }, // EVEX.512.66.0F38.W1 df /r - VAESDECLAST zmm, vex512, zmm/m512
    { const_string("VPERMQ"), 0x300, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 00 ib /r - VPERMQ ymm, ymm/m256, imm8
    { const_string("VPERMQ"), 0x300, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 00 ib /r - VPERMQ zmm, zmm/m512, imm8
    { const_string("VPERMPD"), 0x301, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 01 ib /r - VPERMPD ymm, ymm/m256, imm8
    { const_string("VPERMPD"), 0x301, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 01 ib /r - VPERMPD zmm, zmm/m512, imm8
    { const_string("VALIGND"), 0x303, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 03 ib /r - VALIGND xmm, vex128, xmm/m128, imm8
    { const_string("VALIGNQ"), 0x303, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 03 ib /r - VALIGNQ xmm, vex128, xmm/m128, imm8
    { const_string("VALIGND"), 0x303, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 03 ib /r - VALIGND ymm, vex256, ymm/m256, imm8
    { const_string("VALIGNQ"), 0x303, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 03 ib /r - VALIGNQ ymm, vex256, ymm/m256, imm8
    { const_string("VALIGND"), 0x303, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 03 ib /r - VALIGND zmm, vex512, zmm/m512, imm8
    { const_string("VALIGNQ"), 0x303, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 03 ib /r - VALIGNQ zmm, vex512, zmm/m512, imm8
    { const_string("VPERMILPS"), 0x304, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 04 ib /r - VPERMILPS xmm, xmm/m128, imm8
    { const_string("VPERMILPS"), 0x304, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 04 ib /r - VPERMILPS ymm, ymm/m256, imm8
    { const_string("VPERMILPS"), 0x304, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 04 ib /r - VPERMILPS zmm, zmm/m512, imm8
    { const_string("VPERMILPD"), 0x305, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 05 ib /r - VPERMILPD xmm, xmm/m128, imm8
    { const_string("VPERMILPD"), 0x305, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 05 ib /r - VPERMILPD ymm, ymm/m256, imm8
    { const_string("VPERMILPD"), 0x305, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 05 ib /r - VPERMILPD zmm, zmm/m512, imm8
    { const_string("VRNDSCALEPS"), 0x308, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 08 ib /r - VRNDSCALEPS xmm, xmm/m128, imm8
    { const_string("VRNDSCALEPS"), 0x308, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 08 ib /r - VRNDSCALEPS ymm, ymm/m256, imm8
    { const_string("VRNDSCALEPS"), 0x308, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 08 ib /r - VRNDSCALEPS zmm, zmm/m512, imm8
    { const_string("VRNDSCALEPD"), 0x309, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 09 ib /r - VRNDSCALEPD xmm, xmm/m128, imm8
    { const_string("VRNDSCALEPD"), 0x309, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 09 ib /r - VRNDSCALEPD ymm, ymm/m256, imm8
    { const_string("VRNDSCALEPD"), 0x309, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 09 ib /r - VRNDSCALEPD zmm, zmm/m512, imm8
    { const_string("VRNDSCALESS"), 0x30a, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 0a ib /r - VRNDSCALESS xmm, vex128, xmm/m32, imm8
    { const_string("VRNDSCALESS"), 0x30a, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 0a ib /r - VRNDSCALESS xmm, vex128, xmm/m32, imm8
    { const_string("VRNDSCALESD"), 0x30b, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 0b ib /r - VRNDSCALESD xmm, vex128, xmm/m64, imm8
    { const_string("VRNDSCALESD"), 0x30b, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 0b ib /r - VRNDSCALESD xmm, vex128, xmm/m64, imm8
    { const_string("VPALIGNR"), 0x30f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 0f ib /r - VPALIGNR xmm, vex128, xmm/m128, imm8
    { const_string("VPALIGNR"), 0x30f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 0f ib /r - VPALIGNR xmm, vex128, xmm/m128, imm8
    { const_string("VPALIGNR"), 0x30f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 0f ib /r - VPALIGNR ymm, vex256, ymm/m256, imm8
    { const_string("VPALIGNR"), 0x30f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 0f ib /r - VPALIGNR ymm, vex256, ymm/m256, imm8
    { const_string("VPALIGNR"), 0x30f, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 0f ib /r - VPALIGNR zmm, vex512, zmm/m512, imm8
    { const_string("VPALIGNR"), 0x30f, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 0f ib /r - VPALIGNR zmm, vex512, zmm/m512, imm8
    { const_string("VPEXTRB"), 0x314, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm8_zero_extended, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 14 ib /r - VPEXTRB reg/m8, xmm, imm8
    { const_string("VPEXTRB"), 0x314, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_regm8_zero_extended, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 14 ib /r - VPEXTRB reg/m8, xmm, imm8
    { const_string("VPEXTRW"), 0x315, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm16_zero_extended, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 15 ib /r - VPEXTRW reg/m16, xmm, imm8
    { const_string("VPEXTRW"), 0x315, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_regm16_zero_extended, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 15 ib /r - VPEXTRW reg/m16, xmm, imm8
    { const_string("VPEXTRD"), 0x316, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 16 ib /r - VPEXTRD r/m32, xmm, imm8
    { const_string("VPEXTRQ"), 0x316, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_regm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 16 ib /r - VPEXTRQ r/m64, xmm, imm8
    { const_string("VEXTRACTPS"), 0x317, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 17 ib /r - VEXTRACTPS r/m32, xmm, imm8
    { const_string("VEXTRACTPS"), 0x317, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_regm32, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 17 ib /r - VEXTRACTPS r/m32, xmm, imm8
    { const_string("VINSERTF32X4"), 0x318, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 18 ib /r - VINSERTF32X4 ymm, vex256, xmm/m128, imm8
    { const_string("VINSERTF64X2"), 0x318, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 18 ib /r - VINSERTF64X2 ymm, vex256, xmm/m128, imm8
    { const_string("VINSERTF32X4"), 0x318, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 18 ib /r - VINSERTF32X4 zmm, vex512, xmm/m128, imm8
    { const_string("VINSERTF64X2"), 0x318, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 18 ib /r - VINSERTF64X2 zmm, vex512, xmm/m128, imm8
    { const_string("VEXTRACTF32X4"), 0x319, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 19 ib /r - VEXTRACTF32X4 xmm/m128, ymm, imm8
    { const_string("VEXTRACTF64X2"), 0x319, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 19 ib /r - VEXTRACTF64X2 xmm/m128, ymm, imm8
    { const_string("VEXTRACTF32x4"), 0x319, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 19 ib /r - VEXTRACTF32x4 xmm/m128, zmm, imm8
    { const_string("VEXTRACTF64X2"), 0x319, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 19 ib /r - VEXTRACTF64X2 xmm/m128, zmm, imm8
    { const_string("VINSERTF32X8"), 0x31a, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 1a ib /r - VINSERTF32X8 zmm, vex512, ymm/m256, imm8
    { const_string("VINSERTF64X4"), 0x31a, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 1a ib /r - VINSERTF64X4 zmm, vex512, ymm/m256, imm8
    { const_string("VEXTRACTF32X8"), 0x31b, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 1b ib /r - VEXTRACTF32X8 ymm/m256, zmm, imm8
    { const_string("VEXTRACTF64x4"), 0x31b, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 1b ib /r - VEXTRACTF64x4 ymm/m256, zmm, imm8
    { const_string("VCVTPS2PH"), 0x31d, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmmm64, OPERAND_FLAG_write}, {OPERAND_xmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 1d ib /r - VCVTPS2PH xmm/m64, xmm, imm8
    { const_string("VCVTPS2PH"), 0x31d, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 1d ib /r - VCVTPS2PH xmm/m128, ymm, imm8
    { const_string("VCVTPS2PH"), 0x31d, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 1d ib /r - VCVTPS2PH ymm/m256, zmm, imm8
    { const_string("VPCMPUD"), 0x31e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 1e ib /r - VPCMPUD k, vex128, xmm/m128, imm8
    { const_string("VPCMPUQ"), 0x31e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 1e ib /r - VPCMPUQ k, vex128, xmm/m128, imm8
    { const_string("VPCMPUD"), 0x31e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 1e ib /r - VPCMPUD k, vex256, ymm/m256, imm8
    { const_string("VPCMPUQ"), 0x31e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 1e ib /r - VPCMPUQ k, vex256, ymm/m256, imm8
    { const_string("VPCMPUD"), 0x31e, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 1e ib /r - VPCMPUD k, vex512, zmm/m512, imm8
    { const_string("VPCMPUQ"), 0x31e, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 1e ib /r - VPCMPUQ k, vex512, zmm/m512, imm8
    { const_string("VPCMPD"), 0x31f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 1f ib /r - VPCMPD k, vex128, xmm/m128, imm8
    { const_string("VPCMPQ"), 0x31f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 1f ib /r - VPCMPQ k, vex128, xmm/m128, imm8
    { const_string("VPCMPD"), 0x31f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 1f ib /r - VPCMPD k, vex256, ymm/m256, imm8
    { const_string("VPCMPQ"), 0x31f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 1f ib /r - VPCMPQ k, vex256, ymm/m256, imm8
    { const_string("VPCMPD"), 0x31f, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 1f ib /r - VPCMPD k, vex512, zmm/m512, imm8
    { const_string("VPCMPQ"), 0x31f, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 1f ib /r - VPCMPQ k, vex512, zmm/m512, imm8
    { const_string("VPINSRB"), 0x320, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm8_zero_extended, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 20 ib /r - VPINSRB xmm, vex128, reg/m8, imm8
    { const_string("VPINSRB"), 0x320, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm8_zero_extended, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 20 ib /r - VPINSRB xmm, vex128, reg/m8, imm8
    { const_string("VINSERTPS"), 0x321, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 21 ib /r - VINSERTPS xmm, vex128, xmm/m32, imm8
    { const_string("VPINSRD"), 0x322, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 22 ib /r - VPINSRD xmm, vex128, r/m32, imm8
    { const_string("VPINSRQ"), 0x322, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_regm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 22 ib /r - VPINSRQ xmm, vex128, r/m64, imm8
    { const_string("VSHUFF32X4"), 0x323, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 23 ib /r - VSHUFF32X4 ymm, vex256, ymm/m256, imm8
    { const_string("VSHUFF64X2"), 0x323, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 23 ib /r - VSHUFF64X2 ymm, vex256, ymm/m256, imm8
    { const_string("VSHUFF32x4"), 0x323, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 23 ib /r - VSHUFF32x4 zmm, vex512, zmm/m512, imm8
    { const_string("VSHUFF64x2"), 0x323, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 23 ib /r - VSHUFF64x2 zmm, vex512, zmm/m512, imm8
    { const_string("VPTERNLOGD"), 0x325, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 25 ib /r - VPTERNLOGD xmm, vex128, xmm/m128, imm8
    { const_string("VPTERNLOGQ"), 0x325, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 25 ib /r - VPTERNLOGQ xmm, vex128, xmm/m128, imm8
    { const_string("VPTERNLOGD"), 0x325, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 25 ib /r - VPTERNLOGD ymm, vex256, ymm/m256, imm8
    { const_string("VPTERNLOGQ"), 0x325, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 25 ib /r - VPTERNLOGQ ymm, vex256, ymm/m256, imm8
    { const_string("VPTERNLOGD"), 0x325, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 25 ib /r - VPTERNLOGD zmm, vex512, zmm/m512, imm8
    { const_string("VPTERNLOGQ"), 0x325, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 25 ib /r - VPTERNLOGQ zmm, vex512, zmm/m512, imm8
    { const_string("VGETMANTPS"), 0x326, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 26 ib /r - VGETMANTPS xmm, xmm/m128, imm8
    { const_string("VGETMANTPD"), 0x326, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 26 ib /r - VGETMANTPD xmm, xmm/m128, imm8
    { const_string("VGETMANTPS"), 0x326, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 26 ib /r - VGETMANTPS ymm, ymm/m256, imm8
    { const_string("VGETMANTPD"), 0x326, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 26 ib /r - VGETMANTPD ymm, ymm/m256, imm8
    { const_string("VGETMANTPS"), 0x326, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 26 ib /r - VGETMANTPS zmm, zmm/m512, imm8
    { const_string("VGETMANTPD"), 0x326, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 26 ib /r - VGETMANTPD zmm, zmm/m512, imm8
    { const_string("VGETMANTSS"), 0x327, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 27 ib /r - VGETMANTSS xmm, vex128, xmm/m32, imm8
    { const_string("VGETMANTSD"), 0x327, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 27 ib /r - VGETMANTSD xmm, vex128, xmm/m64, imm8
    { const_string("VGETMANTSS"), 0x327, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 27 ib /r - VGETMANTSS xmm, vex128, xmm/m32, imm8
    { const_string("VGETMANTSD"), 0x327, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 27 ib /r - VGETMANTSD xmm, vex128, xmm/m64, imm8
    { const_string("VPMOVZXBW"), 0x330, -1, 0, 0, 1, 0, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F3A.W0 30 /r - VPMOVZXBW xmm, xmm/m64
    { const_string("VPMOVZXBW"), 0x330, -1, 0, 0, 1, 1, 0, -1, 0, 0, 2, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}} }, // EVEX.128.66.0F3A.W1 30 /r - VPMOVZXBW xmm, xmm/m64
    { const_string("VINSERTI32X4"), 0x338, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 38 ib /r - VINSERTI32X4 ymm, vex256, xmm/m128, imm8
    { const_string("VINSERTI64X2"), 0x338, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 38 ib /r - VINSERTI64X2 ymm, vex256, xmm/m128, imm8
    { const_string("VINSERTI32X4"), 0x338, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 38 ib /r - VINSERTI32X4 zmm, vex512, xmm/m128, imm8
    { const_string("VINSERTI64X2"), 0x338, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 38 ib /r - VINSERTI64X2 zmm, vex512, xmm/m128, imm8
    { const_string("VEXTRACTI32X4"), 0x339, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 39 ib /r - VEXTRACTI32X4 xmm/m128, ymm, imm8
    { const_string("VEXTRACTI64X2"), 0x339, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_ymm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 39 ib /r - VEXTRACTI64X2 xmm/m128, ymm, imm8
    { const_string("VEXTRACTI32x4"), 0x339, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 39 ib /r - VEXTRACTI32x4 xmm/m128, zmm, imm8
    { const_string("VEXTRACTI64X2"), 0x339, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_xmmm128, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 39 ib /r - VEXTRACTI64X2 xmm/m128, zmm, imm8
    { const_string("VINSERTI32X8"), 0x33a, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 3a ib /r - VINSERTI32X8 zmm, vex512, ymm/m256, imm8
    { const_string("VINSERTI64X4"), 0x33a, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 3a ib /r - VINSERTI64X4 zmm, vex512, ymm/m256, imm8
    { const_string("VEXTRACTI32X8"), 0x33b, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 3b ib /r - VEXTRACTI32X8 ymm/m256, zmm, imm8
    { const_string("VEXTRACTI64x4"), 0x33b, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_ymmm256, OPERAND_FLAG_write}, {OPERAND_zmm, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 3b ib /r - VEXTRACTI64x4 ymm/m256, zmm, imm8
    { const_string("VPCMPUB"), 0x33e, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 3e ib /r - VPCMPUB k, vex128, xmm/m128, imm8
    { const_string("VPCMPUW"), 0x33e, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 3e ib /r - VPCMPUW k, vex128, xmm/m128, imm8
    { const_string("VPCMPUB"), 0x33e, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 3e ib /r - VPCMPUB k, vex256, ymm/m256, imm8
    { const_string("VPCMPUW"), 0x33e, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 3e ib /r - VPCMPUW k, vex256, ymm/m256, imm8
    { const_string("VPCMPUB"), 0x33e, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 3e ib /r - VPCMPUB k, vex512, zmm/m512, imm8
    { const_string("VPCMPUW"), 0x33e, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 3e ib /r - VPCMPUW k, vex512, zmm/m512, imm8
    { const_string("VPCMPB"), 0x33f, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 3f ib /r - VPCMPB k, vex128, xmm/m128, imm8
    { const_string("VPCMPW"), 0x33f, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 3f ib /r - VPCMPW k, vex128, xmm/m128, imm8
    { const_string("VPCMPB"), 0x33f, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 3f ib /r - VPCMPB k, vex256, ymm/m256, imm8
    { const_string("VPCMPW"), 0x33f, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 3f ib /r - VPCMPW k, vex256, ymm/m256, imm8
    { const_string("VPCMPB"), 0x33f, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 3f ib /r - VPCMPB k, vex512, zmm/m512, imm8
    { const_string("VPCMPW"), 0x33f, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 3f ib /r - VPCMPW k, vex512, zmm/m512, imm8
    { const_string("VDBPSADBW"), 0x342, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 42 ib /r - VDBPSADBW xmm, vex128, xmm/m128, imm8
    { const_string("VDBPSADBW"), 0x342, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 42 ib /r - VDBPSADBW ymm, vex256, ymm/m256, imm8
    { const_string("VDBPSADBW"), 0x342, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 42 ib /r - VDBPSADBW zmm, vex512, zmm/m512, imm8
    { const_string("VSHUFI32X4"), 0x343, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 43 ib /r - VSHUFI32X4 ymm, vex256, ymm/m256, imm8
    { const_string("VSHUFI64X2"), 0x343, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 43 ib /r - VSHUFI64X2 ymm, vex256, ymm/m256, imm8
    { const_string("VSHUFI32x4"), 0x343, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 43 ib /r - VSHUFI32x4 zmm, vex512, zmm/m512, imm8
    { const_string("VSHUFI64x2"), 0x343, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 43 ib /r - VSHUFI64x2 zmm, vex512, zmm/m512, imm8
    { const_string("VPCLMULQDQ"), 0x344, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 44 ib /r - VPCLMULQDQ xmm, vex128, xmm/m128, imm8
    { const_string("VPCLMULQDQ"), 0x344, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 44 ib /r - VPCLMULQDQ xmm, vex128, xmm/m128, imm8
    { const_string("VPCLMULQDQ"), 0x344, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 44 ib /r - VPCLMULQDQ ymm, vex256, ymm/m256, imm8
    { const_string("VPCLMULQDQ"), 0x344, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 44 ib /r - VPCLMULQDQ ymm, vex256, ymm/m256, imm8
    { const_string("VPCLMULQDQ"), 0x344, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 44 ib /r - VPCLMULQDQ zmm, vex512, zmm/m512, imm8
    { const_string("VPCLMULQDQ"), 0x344, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 44 ib /r - VPCLMULQDQ zmm, vex512, zmm/m512, imm8
    { const_string("VRANGEPS"), 0x350, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 50 ib /r - VRANGEPS xmm, vex128, xmm/m128, imm8
    { const_string("VRANGEPD"), 0x350, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 50 ib /r - VRANGEPD xmm, vex128, xmm/m128, imm8
    { const_string("VRANGEPS"), 0x350, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 50 ib /r - VRANGEPS ymm, vex256, ymm/m256, imm8
    { const_string("VRANGEPD"), 0x350, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 50 ib /r - VRANGEPD ymm, vex256, ymm/m256, imm8
    { const_string("VRANGEPS"), 0x350, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 50 ib /r - VRANGEPS zmm, vex512, zmm/m512, imm8
    { const_string("VRANGEPD"), 0x350, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 50 ib /r - VRANGEPD zmm, vex512, zmm/m512, imm8
    { const_string("VRANGESS"), 0x351, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 51 /r - VRANGESS xmm, vex128, xmm/m32, imm8
    { const_string("VRANGESD"), 0x351, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 51 /r - VRANGESD xmm, vex128, xmm/m64, imm8
    { const_string("VRANGESS"), 0x351, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 51 /r - VRANGESS xmm, vex128, xmm/m32, imm8
    { const_string("VRANGESD"), 0x351, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 51 /r - VRANGESD xmm, vex128, xmm/m64, imm8
    { const_string("VFIXUPIMMPS"), 0x354, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 54 /r - VFIXUPIMMPS xmm, vex128, xmm/m128, imm8
    { const_string("VFIXUPIMMPD"), 0x354, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 54 ib /r - VFIXUPIMMPD xmm, vex128, xmm/m128, imm8
    { const_string("VFIXUPIMMPS"), 0x354, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 54 /r - VFIXUPIMMPS ymm, vex256, ymm/m256, imm8
    { const_string("VFIXUPIMMPD"), 0x354, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 54 ib /r - VFIXUPIMMPD ymm, vex256, ymm/m256, imm8
    { const_string("VFIXUPIMMPS"), 0x354, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 54 ib /r - VFIXUPIMMPS zmm, vex512, zmm/m512, imm8
    { const_string("VFIXUPIMMPD"), 0x354, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 54 ib /r - VFIXUPIMMPD zmm, vex512, zmm/m512, imm8
    { const_string("VFIXUPIMMSS"), 0x355, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 55 ib /r - VFIXUPIMMSS xmm, vex128, xmm/m32, imm8
    { const_string("VFIXUPIMMSD"), 0x355, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 55 ib /r - VFIXUPIMMSD xmm, vex128, xmm/m64, imm8
    { const_string("VFIXUPIMMSS"), 0x355, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 55 ib /r - VFIXUPIMMSS xmm, vex128, xmm/m32, imm8
    { const_string("VFIXUPIMMSD"), 0x355, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_read | OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 55 ib /r - VFIXUPIMMSD xmm, vex128, xmm/m64, imm8
    { const_string("VREDUCEPS"), 0x356, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 56 ib /r - VREDUCEPS xmm, xmm/m128, imm8
    { const_string("VREDUCEPD"), 0x356, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 56 ib /r - VREDUCEPD xmm, xmm/m128, imm8
    { const_string("VREDUCEPS"), 0x356, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 56 ib /r - VREDUCEPS ymm, ymm/m256, imm8
    { const_string("VREDUCEPD"), 0x356, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 56 ib /r - VREDUCEPD ymm, ymm/m256, imm8
    { const_string("VREDUCEPS"), 0x356, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 56 ib /r - VREDUCEPS zmm, zmm/m512, imm8
    { const_string("VREDUCEPD"), 0x356, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 56 ib /r - VREDUCEPD zmm, zmm/m512, imm8
    { const_string("VREDUCESS"), 0x357, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 57 ib /r - VREDUCESS xmm, vex128, xmm/m32, imm8
    { const_string("VREDUCESD"), 0x357, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 57 ib /r - VREDUCESD xmm, vex128, xmm/m64, imm8
    { const_string("VREDUCESS"), 0x357, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 57 ib /r - VREDUCESS xmm, vex128, xmm/m32, imm8
    { const_string("VREDUCESD"), 0x357, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 57 ib /r - VREDUCESD xmm, vex128, xmm/m64, imm8
    { const_string("VFPCLASSPS"), 0x366, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 66 ib /r - VFPCLASSPS k, xmm/m128, imm8
    { const_string("VFPCLASSPD"), 0x366, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 66 ib /r - VFPCLASSPD k, xmm/m128, imm8
    { const_string("VFPCLASSPS"), 0x366, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 66 ib /r - VFPCLASSPS k, ymm/m256, imm8
    { const_string("VFPCLASSPD"), 0x366, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 66 ib /r - VFPCLASSPD k, ymm/m256, imm8
    { const_string("VFPCLASSPS"), 0x366, -1, 0, 0, 1, 0, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 66 ib /r - VFPCLASSPS k, zmm/m512, imm8
    { const_string("VFPCLASSPD"), 0x366, -1, 0, 0, 1, 1, 0, -1, 0, 2, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 66 ib /r - VFPCLASSPD k, zmm/m512, imm8
    { const_string("VFPCLASSSS"), 0x367, -1, 0, 0, 1, 0, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 67 /r - VFPCLASSSS k, xmm/m32, imm8
    { const_string("VFPCLASSSD"), 0x367, -1, 0, 0, 1, 1, 0, -1, 0, 0, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 67 ib /r - VFPCLASSSD k, xmm/m64, imm8
    { const_string("VFPCLASSSS"), 0x367, -1, 0, 0, 1, 0, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_xmmm32, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 67 /r - VFPCLASSSS k, xmm/m32, imm8
    { const_string("VFPCLASSSD"), 0x367, -1, 0, 0, 1, 1, 0, -1, 0, 1, 3, {{OPERAND_k, OPERAND_FLAG_write}, {OPERAND_xmmm64, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 67 ib /r - VFPCLASSSD k, xmm/m64, imm8
    { const_string("VPSHLDW"), 0x370, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 70 ib /r - VPSHLDW xmm, vex128, xmm/m128, imm8
    { const_string("VPSHLDW"), 0x370, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 70 ib /r - VPSHLDW ymm, vex256, ymm/m256, imm8
    { const_string("VPSHLDW"), 0x370, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 70 ib /r - VPSHLDW zmm, vex512, zmm/m512, imm8
    { const_string("VPSHLDD"), 0x371, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 71 ib /r - VPSHLDD xmm, vex128, xmm/m128, imm8
    { const_string("VPSHLDQ"), 0x371, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 71 ib /r - VPSHLDQ xmm, vex128, xmm/m128, imm8
    { const_string("VPSHLDD"), 0x371, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 71 ib /r - VPSHLDD ymm, vex256, ymm/m256, imm8
    { const_string("VPSHLDQ"), 0x371, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 71 ib /r - VPSHLDQ ymm, vex256, ymm/m256, imm8
    { const_string("VPSHLDD"), 0x371, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 71 ib /r - VPSHLDD zmm, vex512, zmm/m512, imm8
    { const_string("VPSHLDQ"), 0x371, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 71 ib /r - VPSHLDQ zmm, vex512, zmm/m512, imm8
    { const_string("VPSHRDW"), 0x372, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 72 ib /r - VPSHRDW xmm, vex128, xmm/m128, imm8
    { const_string("VPSHRDW"), 0x372, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 72 ib /r - VPSHRDW ymm, vex256, ymm/m256, imm8
    { const_string("VPSHRDW"), 0x372, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 72 ib /r - VPSHRDW zmm, vex512, zmm/m512, imm8
    { const_string("VPSHRDD"), 0x373, -1, 0, 0, 1, 0, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W0 73 ib /r - VPSHRDD xmm, vex128, xmm/m128, imm8
    { const_string("VPSHRDQ"), 0x373, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 73 ib /r - VPSHRDQ xmm, vex128, xmm/m128, imm8
    { const_string("VPSHRDD"), 0x373, -1, 0, 0, 1, 0, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W0 73 ib /r - VPSHRDD ymm, vex256, ymm/m256, imm8
    { const_string("VPSHRDQ"), 0x373, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 73 ib /r - VPSHRDQ ymm, vex256, ymm/m256, imm8
    { const_string("VPSHRDD"), 0x373, -1, 0, 0, 1, 0, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W0 73 ib /r - VPSHRDD zmm, vex512, zmm/m512, imm8
    { const_string("VPSHRDQ"), 0x373, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 73 ib /r - VPSHRDQ zmm, vex512, zmm/m512, imm8
    { const_string("VGF2P8AFFINEQB"), 0x3ce, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 ce ib /r - VGF2P8AFFINEQB xmm, vex128, xmm/m128, imm8
    { const_string("VGF2P8AFFINEQB"), 0x3ce, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 ce ib /r - VGF2P8AFFINEQB ymm, vex256, ymm/m256, imm8
    { const_string("VGF2P8AFFINEQB"), 0x3ce, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 ce ib /r - VGF2P8AFFINEQB zmm, vex512, zmm/m512, imm8
    { const_string("VGF2P8AFFINEINVQB"), 0x3cf, -1, 0, 0, 1, 1, 0, -1, 0, 0, 4, {{OPERAND_xmm, OPERAND_FLAG_write}, {OPERAND_vex_xmm, OPERAND_FLAG_read}, {OPERAND_xmmm128, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.128.66.0F3A.W1 cf ib /r - VGF2P8AFFINEINVQB xmm, vex128, xmm/m128, imm8
    { const_string("VGF2P8AFFINEINVQB"), 0x3cf, -1, 0, 0, 1, 1, 0, -1, 0, 1, 4, {{OPERAND_ymm, OPERAND_FLAG_write}, {OPERAND_vex_ymm, OPERAND_FLAG_read}, {OPERAND_ymmm256, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.256.66.0F3A.W1 cf ib /r - VGF2P8AFFINEINVQB ymm, vex256, ymm/m256, imm8
    { const_string("VGF2P8AFFINEINVQB"), 0x3cf, -1, 0, 0, 1, 1, 0, -1, 0, 2, 4, {{OPERAND_zmm, OPERAND_FLAG_write}, {OPERAND_vex_zmm, OPERAND_FLAG_read}, {OPERAND_zmmm512, OPERAND_FLAG_read}, {OPERAND_imm8, 0}} }, // EVEX.512.66.0F3A.W1 cf ib /r - VGF2P8AFFINEINVQB zmm, vex512, zmm/m512, imm8
};

