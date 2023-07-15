// 生成汇编指令
#ifndef GENERARATOR_H
#define GENERARATOR_H

#include "ir/ir.h"
#include "backend/rv_def.h"
#include "backend/rv_inst_impl.h"

#include<unordered_map>
#include<unordered_set>
#include<string>
#include<vector>
#include<fstream>

namespace backend {


struct Generator {
    /* ---------- 属性 ---------- */

    // 输入输出属性
    const ir::Program& program;     // Lab2中生成的整个最大程序，包含多个全局变量和各种函数
    std::ofstream& fout;            // 输出文件流
    // 函数调用需要用到的属性
    std::unordered_map<std::string, int> var_in_sta;            // 记录变量在栈中的位置：$sp+var_in_sta[name]
    int stack_size;                 // 调用函数前扫描函数中涉及的变量数目以腾出相应数量的寄存器
    std::vector<rv::rvREG> saved_callee_regs {rv::rvREG::S0, rv::rvREG::S1, rv::rvREG::S2, rv::rvREG::S3, rv::rvREG::S4,
                                              rv::rvREG::S5, rv::rvREG::S6, rv::rvREG::S7, rv::rvREG::S8, rv::rvREG::S9,
                                              rv::rvREG::S10,rv::rvREG::S11,rv::rvREG::RA};     // 被调用者需要保存的寄存器
    std::vector<rv::rvREG> int_regs {rv::rvREG::T0, rv::rvREG::T1, rv::rvREG::T2, rv::rvREG::T3, rv::rvREG::T4,
                                     rv::rvREG::T5, rv::rvREG::T6, rv::rvREG::S0, rv::rvREG::S1, rv::rvREG::S2,
                                     rv::rvREG::S3, rv::rvREG::S4, rv::rvREG::S5, rv::rvREG::S6, rv::rvREG::S7,
                                     rv::rvREG::S8,rv::rvREG::S9,rv::rvREG::S10,rv::rvREG::S11};// 所有可用的整数寄存器
    std::vector<rv::rvREG> int_arg_regs {rv::rvREG::A0, rv::rvREG::A1, rv::rvREG::A2, rv::rvREG::A3, rv::rvREG::A4,
                                         rv::rvREG::A5, rv::rvREG::A6, rv::rvREG::A7};          // 函数返回值/参数列表寄存器
    std::unordered_set<rv::rvREG> free_int_regs;                // 所有空闲的整数寄存器
    // IR地址跳转需要用到的属性
    std::unordered_map<int, std::string> jump_label_map;        // 地址->标签的映射
    int curr_ir_addr;               // 当前正在生成指令的IR地址
    int label_count = 0;            // 标记跳转标签
    // 开局部数组需要用到的属性
    int curr_stack_used_bytes;      // 记录栈内除了变量外使用的空间字节数


    /* ---------- 框架函数 ---------- */

    // 构造函数
    Generator(ir::Program&, std::ofstream&);

    // 核心函数，生成汇编代码，封装后供main.cpp调用
    void gen();
    // 处理全局变量（辅助gen函数）
    void solve_global_data();
    // 处理全局函数（辅助gen函数）
    void solve_func(const ir::Function&);
    // 为指令生成汇编代码（辅助solve_func函数）
    void generate_INST(const ir::Instruction&);
    // 函数初始化：计算所用栈空间、为相关参数分配寄存器（辅助solve_func函数）
    void init_func(const ir::Function*);


    /* ---------- 寄存器分配相关函数 ---------- */

    // 判断是否为全局变量
    bool is_global(const std::string&);

    // 为操作数分配寄存器产生汇编语句
    rv::rvREG alloc_and_load_int_reg(ir::Operand);
    // 分配整数寄存器（辅助alloc_and_load_int_reg函数）
    rv::rvREG alloc_int_reg();
    // 回收整数寄存器
    void free_int_reg(rv::rvREG int_reg);

    // 将寄存器中的值存入内存（全局变量表/栈）
    void save_int_operand(ir::Operand operand, rv::rvREG int_reg);


    /* ---------- 根据不同指令生成汇编函数（辅助generate_INST函数） ---------- */

    // 算术运算（没有立即数运算，因为LAB2中没有使用addi/subi）
    void generate_add(const ir::Instruction&);
    void generate_sub(const ir::Instruction&);
    void generate_mul(const ir::Instruction&);
    void generate_div(const ir::Instruction&);
    void generate_mod(const ir::Instruction&);

    // 逻辑运算
    void generate_lss(const ir::Instruction&);
    void generate_leq(const ir::Instruction&);
    void generate_gtr(const ir::Instruction&);
    void generate_geq(const ir::Instruction&);
    void generate_eq(const ir::Instruction&);
    void generate_neq(const ir::Instruction&);
    void generate_not(const ir::Instruction&);
    void generate_and(const ir::Instruction&);
    void generate_or(const ir::Instruction&);

    // 访存与指针
    void generate_alloc(const ir::Instruction&);
    void generate_load(const ir::Instruction&);
    void generate_store(const ir::Instruction&);
    void generate_getptr(const ir::Instruction&);

    // 调用返回
    void generate_return(const ir::Instruction&);
    void generate_call(const ir::Instruction&);

    // 跳转
    void generate_goto(const ir::Instruction&);

    // 移位
    void generate_mov(const ir::Instruction&);

    // 空
    void generate_unuse(const ir::Instruction&);


    /* ---------- 生成汇编语言的指令前缀函数 ---------- */
    // 汇编语言的指令前缀
    void set_nopic();
    void set_data();
    void set_bss();
    void set_label(const std::string&);
    void set_text();
};


} // namespace backend


#endif