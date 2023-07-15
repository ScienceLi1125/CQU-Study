// 程序结构体，实验二核心函数的返回值就是一个程序结构体。用于IR中描述程序，一个程序包含多个全局变量和函数。
#ifndef PROGRAM_H
#define PROGRAM_H

#include "ir/ir_function.h"
#include "ir/ir_operand.h"

#include <vector>
#include <string>

namespace ir{
    // 全局变量
    struct GlobalVal{
        ir::Operand val;
        int maxlen = 0;     //为数组长度设计
        GlobalVal(ir::Operand va);
        GlobalVal(ir::Operand va, int len);
    };
    // 程序
    struct Program {
        std::vector<Function> functions;    // ir_function.h中的Function
        std::vector<GlobalVal> globalVal;
        Program();
        void addFunction(const Function& proc);
        std::string draw();
    };

}
#endif
