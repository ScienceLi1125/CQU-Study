#ifndef IRFUNCTION_H
#define IRFUNCTION_H
#include <vector>
#include <string>
#include "ir/ir_operand.h"
#include "ir/ir_instruction.h"
namespace ir
{

struct Function {
    std::string name;
    ir::Type returnType;
    std::vector<Operand> ParameterList;
    std::vector<Instruction*> InstVec;
    Function();
    Function(const std::string&, const ir::Type&);
    Function(const std::string&, const std::vector<Operand>&, const ir::Type&);
    void addInst(Instruction* inst);
    std::string draw();
};

}
#endif
