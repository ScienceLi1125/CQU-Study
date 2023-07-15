// 指令结构体，用于IR中描述指令
#ifndef IRINSTRUCTION_H
#define IRINSTRUCTION_H

#include "ir/ir_operand.h"
#include "ir/ir_operator.h"

#include <vector>
#include <string>


namespace ir{

// IR: (opcode, des, operand1, operand2)
struct Instruction {
    Operand op1;    // 源操作数1
    Operand op2;    // 源操作数2
    Operand des;    // 目的操作数
    Operator op;    // IR 功能
    Instruction();
    Instruction(const Operand& op1, const Operand& op2, const Operand& des, const Operator& op);
    virtual std::string draw() const;   // 展示当前IR
};

struct CallInst: public Instruction{
    std::vector<Operand> argumentList;
    CallInst(const Operand& op1, std::vector<Operand> paraList, const Operand& des);
    CallInst(const Operand& op1, const Operand& des);   //无参数情况
    std::string draw() const;
};


}
#endif
