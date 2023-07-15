#include "ir/ir_operator.h"

#include <string>


namespace ir {

std::string toString(Operator t)
{
    switch (t) {
        case Operator::_return: return "return";
        case Operator::_goto: return "goto";
        case Operator::call: return "call";
        case Operator::alloc: return "alloc";
        case Operator::store: return "store";
        case Operator::getptr: return "getptr";
        case Operator::load: return "load";
        case Operator::def: return "def";
        case Operator::fdef: return "fdef";
        case Operator::mov: return "mov";
        case Operator::fmov: return "fmov";
        case Operator::add: return "add";
        case Operator::addi: return "addi";
        case Operator::fadd: return "fadd";
        case Operator::sub: return "sub";
        case Operator::subi: return "subi";
        case Operator::fsub: return "fsub";
        case Operator::mul: return "mul";
        case Operator::fmul: return "fmul";
        case Operator::div: return "div";
        case Operator::fdiv: return "fdiv";
        case Operator::mod: return "mod";
        case Operator::lss: return "lss";
        case Operator::flss: return "flss";
        case Operator::leq: return "leq";
        case Operator::fleq: return "fleq";
        case Operator::gtr: return "gtr";
        case Operator::fgtr: return "fgtr";
        case Operator::geq: return "geq";
        case Operator::fgeq: return "fgeq";
        case Operator::eq: return "eq";
        case Operator::feq: return "feq";
        case Operator::neq: return "neq";
        case Operator::fneq: return "neq";
        case Operator::_not: return "not";
        case Operator::_or: return "or";
        case Operator::_and: return "and";
        case Operator::cvt_i2f: return "cvt_i2f";
        case Operator::cvt_f2i: return "cvt_f2i";
        case Operator::__unuse__: return "__unuse__";
        default:
            return "OpSpace::error operator::" + std::to_string(static_cast<int>(t));
    }
}
    
} // namespace IR
