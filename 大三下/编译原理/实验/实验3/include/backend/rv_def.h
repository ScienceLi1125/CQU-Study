// RISC-V基本量，包括64个寄存器和操作码
#ifndef RV_DEF_H
#define RV_DEF_H

#include<string>

namespace rv {

// RISC-V寄存器
enum class rvREG {
    /* ---------- RISC-V 32个整数寄存器 ---------- */
    // x0：zero寄存器，存储0，只读
    ZERO,
    // x1：ra寄存器，存储函数调用的返回地址
    RA,
    // x2：sp寄存器，存储栈指针
    SP,
    // x3：gp寄存器，存储全局指针
    GP,
    // x4：tp寄存器，存储线程指针
    TP,
    // x5~x7：t0~t3临时寄存器，存储临时变量
    T0,
    T1,
    T2,
    // x8：s0/fp保存寄存器，存储函数的栈帧指针
    S0,
    // x9：s1/sp保存寄存器，存储栈指针
    S1,
    // x10~x11：a0~a1寄存器，存储函数返回值
    A0,
    A1,
    // x12~x17：a2~a7寄存器，存储函数参数
    A2,
    A3,
    A4,
    A5,
    A6,
    A7,
    // x18~x27：s2~s11保存寄存器，存储函数调用期间需要保持不变并在调用结束后恢复寄存器原值的寄存器的值（即Ti寄存器的备份）
    S2,
    S3,
    S4,
    S5,
    S6,
    S7,
    S8,
    S9,
    S10,
    S11,
    // x28~x31：t3~t6临时寄存器，存储临时变量
    T3,
    T4,
    T5,
    T6,

    /* ---------- RISC-V 32个浮点数寄存器 ---------- */
    // f0~f7：ft0~ft7寄存器，存储临时浮点数
    FT0,
    FT1,
    FT2,
    FT3,
    FT4,
    FT5,
    FT6,
    FT7,
    // f8~f9：fs0~fs1寄存器，存储保存浮点数
    FS0,
    FS1,
    // f10~f11：fa0~fa1寄存器，存储函数的浮点数返回值
    FA0,
    FA1,
    // f12~f17：fa2~fa7寄存器，存储函数的浮点数参数
    FA2,
    FA3,
    FA4,
    FA5,
    FA6,
    FA7,
    // f18~f27：fs2~fs11寄存器，存储保存浮点数
    FS2,
    FS3,
    FS4,
    FS5,
    FS6,
    FS7,
    FS8,
    FS9,
    FS10,
    FS11,
    // f28~f31：ft8~ft11临时寄存器，存储临时浮点数
    FT8,
    FT9,
    FT10,
    FT11,
};
std::string toString(rvREG r);

// 为了处理方便，将浮点数寄存器统一合并到rvREG里
// enum class rvFREG {
//     F0,
//     F1,
//     F2,
//     F3,
//     F4,
//     F5,
//     F6,
//     F7,
//     F8,
//     F9,
//     F10,
//     F11,
//     F12,
//     F13,
//     F14,
//     F15,
//     F16,
//     F17,
//     F18,
//     F19,
//     F20,
//     F21,
//     F22,
//     F23,
//     F24,
//     F25,
//     F26,
//     F27,
//     F28,
//     F29,
//     F30,
//     F31,
// };
// std::string toString(rvFREG r);

// RISC-V指令操作码
enum class rvOPCODE {
    // RV32I Base Integer Instructions
    ADD, SUB, XOR, OR, AND, SLL, SRL, SRA, SLT, SLTU,       // arithmetic & logic
    ADDI, XORI, ORI, ANDI, SLLI, SRLI, SRAI, SLTI, SLTIU,   // immediate
    LW, SW,                                                 // load & store
    BEQ, BNE, BLT, BGE, BLTU, BGEU,                         // conditional branch
    JAL, JALR,                                              // jump
    // RV32M Multiply Extension

    // RV32F / D Floating-Point Extensions

    // Pseudo Instructions
    LA, LI, MOV, J,
};
std::string toString(rvOPCODE r);  // implement this in ur own way

} // namespace rv


#endif