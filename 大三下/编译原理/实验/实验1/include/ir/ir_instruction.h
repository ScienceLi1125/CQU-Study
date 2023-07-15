#ifndef IRINSTRUCTION_H
#define IRINSTRUCTION_H

#include "ir/ir_operand.h"
#include "ir/ir_operator.h"

#include <vector>
#include <string>


namespace ir
{

struct Instruction {
    Operand op1;
    Operand op2;
    Operand des;
    Operator op;
    Instruction();
    Instruction(const Operand& op1, const Operand& op2, const Operand& des, const Operator& op);
    virtual std::string draw() const;
};

struct CallInst: public Instruction{
    std::vector<Operand> argumentList;
    CallInst(const Operand& op1, std::vector<Operand> paraList, const Operand& des);
    CallInst(const Operand& op1, const Operand& des);   //无参数情况
    std::string draw() const;
};


}
#endif
