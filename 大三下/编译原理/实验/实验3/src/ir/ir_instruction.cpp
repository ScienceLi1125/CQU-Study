#include "ir/ir_instruction.h"
#include "ir/ir_operand.h"
#include "ir/ir_operator.h"


ir::Instruction::Instruction() {}

ir::Instruction::Instruction(const Operand& op1, const Operand& op2, const Operand& des, const Operator& op)
    : op1(op1), op2(op2), des(des), op(op) {}

ir::CallInst::CallInst(const Operand &op1, std::vector<Operand> paraList, const Operand &des) 
    : Instruction(op1, Operand(), des, Operator::call), argumentList(paraList) {}

ir::CallInst::CallInst(const Operand &op1, const Operand &des)
    : Instruction(op1, Operand(), des, Operator::call), argumentList() {}

std::string ir::CallInst::draw() const {
    std::string res = "call " + this->des.name + ", " + this->op1.name + "(";
    for(const auto& arg: argumentList)
        res += arg.name + ", ";
    if(argumentList.size())
        res = res.substr(0,res.size()-2);
    res += ")";
    return res;
}

std::string ir::Instruction::draw() const {
    switch (this->op) {
        case ir::Operator::_return:
            return "return " + this->op1.name;
        case ir::Operator::_goto:
        {
            if (this->op1.name != "null") return "if " + this->op1.name + " goto [pc, " + this->des.name + "]";
            else return "goto [pc, " + this->des.name + "]";
        }
        case ir::Operator::alloc:
            return "alloc " + this->des.name + ", " + this->op1.name;
        case ir::Operator::mov:
            return "mov " + this->des.name + ", " + this->op1.name;
        case ir::Operator::fmov:
            return "fmov " + this->des.name + ", " + this->op1.name;
        case ir::Operator::cvt_f2i:
            return "cvt_f2i " + this->des.name + ", " + this->op1.name;
        case ir::Operator::cvt_i2f:
            return "cvt_i2f " + this->des.name + ", " + this->op1.name;
        case ir::Operator::def:
            return "def " + this->des.name + ", " + this->op1.name;
        case ir::Operator::fdef:
            return "fdef " + this->des.name + ", " + this->op1.name;
        case ir::Operator::_not:
            return "not " + this->des.name + ", " + this->op1.name;
        default:
            return toString(this->op) + " " + this->des.name + ", " + this->op1.name + ", " + this->op2.name;
        // case ir::Operator::add:
        //     return this->des.name + " = " + this->op1.name + " add " + this->op2.name;
        // case ir::Operator::addi:
        //     return this->des.name + " = " + this->op1.name + " addi " + this->op2.name;
        // case ir::Operator::fadd:
        //     return this->des.name + " = " + this->op1.name + " fadd " + this->op2.name;
        // case ir::Operator::sub:
        //     return this->des.name + " = " + this->op1.name + " sub " + this->op2.name;
        // case ir::Operator::subi:
        //     return this->des.name + " = " + this->op1.name + " subi " + this->op2.name;
        // case ir::Operator::fsub:
        //     return this->des.name + " = " + this->op1.name + " fsub " + this->op2.name;
        // case ir::Operator::mul:
        //     return this->des.name + " = " + this->op1.name + " mul " + this->op2.name;
        // case ir::Operator::fmul:
        //     return this->des.name + " = " + this->op1.name + " fmul " + this->op2.name;
        // case ir::Operator::div:
        //     return this->des.name + " = " + this->op1.name + " div " + this->op2.name;
        // case ir::Operator::fdiv:
        //     return this->des.name + " = " + this->op1.name + " fdiv " + this->op2.name;
        // case ir::Operator::mod:
        //     return this->des.name + " = " + this->op1.name + " mod " + this->op2.name;
        // case ir::Operator::lss:
        //     return this->des.name + " = " + this->op1.name + " lss " + this->op2.name;
        // case ir::Operator::lssi:
        //     return this->des.name + " = " + this->op1.name + " lssi " + this->op2.name;
        // case ir::Operator::leq:
        //     return this->des.name + " = " + this->op1.name + " leq " + this->op2.name;
        // case ir::Operator::leqi:
        //     return this->des.name + " = " + this->op1.name + " leqi " + this->op2.name;
        // case ir::Operator::geq:
        //     return this->des.name + " = " + this->op1.name + " geq " + this->op2.name;
        // case ir::Operator::geqi:
        //     return this->des.name + " = " + this->op1.name + " geqi " + this->op2.name;
        // case ir::Operator::gtr:
        //     return this->des.name + " = " + this->op1.name + " gtr " + this->op2.name;
        // case ir::Operator::gtri:
        //     return this->des.name + " = " + this->op1.name + " gtri " + this->op2.name;
        // case ir::Operator::eq:
        //     return this->des.name + " = " + this->op1.name + " eq " + this->op2.name;
        // case ir::Operator::eqi:
        //     return this->des.name + " = " + this->op1.name + " eqi " + this->op2.name;
        // case ir::Operator::neq:
        //     return this->des.name + " = " + this->op1.name + " neq " + this->op2.name;
        // case ir::Operator::neqi:
        //     return this->des.name + " = " + this->op1.name + " neqi " + this->op2.name;
        // case ir::Operator::_and:
        //     return this->des.name + " = " + this->op1.name + " && " + this->op2.name;
        // case ir::Operator::_or:
        //     return this->des.name + " = " + this->op1.name + " || " + this->op2.name;
    }
    return "invalid instruction";
}