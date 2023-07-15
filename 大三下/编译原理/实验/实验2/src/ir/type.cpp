#include "ir/ir_operand.h"

#include <string>


namespace ir {

std::string toString(Type t) {
    switch (t) {
        case Type::Int: return "int";
        case Type::IntPtr: return "int*";
        case Type::Float: return "float";
        case Type::FloatPtr: return "float*";
        case Type::null: return "void";
        case Type::FloatLiteral: return "floatLiteral";
        case Type::IntLiteral: return "intLiteral";
        default:
            return "Type error: error type number" + std::to_string(static_cast<int>(t));
    }
}

}