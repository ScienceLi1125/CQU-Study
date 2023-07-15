// RISC-V指令结构体
#ifndef RV_INST_IMPL_H
#define RV_INST_IMPL_H

#include "backend/rv_def.h"

namespace rv {

// RISC-V指令结构体
struct rv_inst {
    // 必选项
    rvREG rd, rs1, rs2;         // 操作数寄存器
    rvOPCODE op;                // 操作码
    // 可选项
    uint32_t imm;               // 立即数指令的立即数
    std::string label;          // beq/jarl指令
    // 打印指令
    std::string draw() const;
};

};

#endif