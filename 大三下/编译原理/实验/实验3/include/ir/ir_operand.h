// 操作数结构体，用于IR中描述操作数
#ifndef IROPERAND_H
#define IROPERAND_H

#include <string>


namespace ir {

enum class Type {
    Int,
    Float,
    IntLiteral,
    FloatLiteral,
    IntPtr,
    FloatPtr,
    null
};

std::string toString(Type t);

struct Operand {
    std::string name;   // 变量名（标识符）
    Type type;          // 变量类型
    Operand(std::string = "null", Type = Type::null);
};

}
#endif
