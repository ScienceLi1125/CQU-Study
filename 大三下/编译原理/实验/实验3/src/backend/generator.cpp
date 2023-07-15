/* 汇编指令生成：
    实验2已经得到了中间表示IR，实验3生成可以与sylib.a链接的risc-v汇编
*/
#include"backend/generator.h"
#include "backend/rv_def.h"

#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>


#define TODO assert(0 && "todo")

/* ---------- rv_def.h ---------- */
std::string rv::toString(rv::rvREG r){
    switch (r){
        case rv::rvREG::ZERO:   return "zero";
        case rv::rvREG::RA:     return "ra";
        case rv::rvREG::SP:     return "sp";
        case rv::rvREG::GP:     return "gp";
        case rv::rvREG::TP:     return "tp";
        case rv::rvREG::T0:     return "t0";
        case rv::rvREG::T1:     return "t1";
        case rv::rvREG::T2:     return "t2";
        case rv::rvREG::S0:     return "s0";
        case rv::rvREG::S1:     return "s1";
        case rv::rvREG::A0:     return "a0";
        case rv::rvREG::A1:     return "a1";
        case rv::rvREG::A2:     return "a2";
        case rv::rvREG::A3:     return "a3";
        case rv::rvREG::A4:     return "a4";
        case rv::rvREG::A5:     return "a5";
        case rv::rvREG::A6:     return "a6";
        case rv::rvREG::A7:     return "a7";
        case rv::rvREG::S2:     return "s2";
        case rv::rvREG::S3:     return "s3";
        case rv::rvREG::S4:     return "s4";
        case rv::rvREG::S5:     return "s5";
        case rv::rvREG::S6:     return "s6";
        case rv::rvREG::S7:     return "s7";
        case rv::rvREG::S8:     return "s8";
        case rv::rvREG::S9:     return "s9";
        case rv::rvREG::S10:    return "s10";
        case rv::rvREG::S11:    return "s11";
        case rv::rvREG::T3:     return "t3";
        case rv::rvREG::T4:     return "t4";
        case rv::rvREG::T5:     return "t5";
        case rv::rvREG::T6:     return "t6";
        case rv::rvREG::FT0:    return "ft0";
        case rv::rvREG::FT1:    return "ft1";
        case rv::rvREG::FT2:    return "ft2";
        case rv::rvREG::FT3:    return "ft3";
        case rv::rvREG::FT4:    return "ft4";
        case rv::rvREG::FT5:    return "ft5";
        case rv::rvREG::FT6:    return "ft6";
        case rv::rvREG::FT7:    return "ft7";
        case rv::rvREG::FS0:    return "fs0";
        case rv::rvREG::FS1:    return "fs1";
        case rv::rvREG::FA0:    return "fa0";
        case rv::rvREG::FA1:    return "fa1";
        case rv::rvREG::FA2:    return "fa2";
        case rv::rvREG::FA3:    return "fa3";
        case rv::rvREG::FA4:    return "fa4";
        case rv::rvREG::FA5:    return "fa5";
        case rv::rvREG::FA6:    return "fa6";
        case rv::rvREG::FA7:    return "fa7";
        case rv::rvREG::FS2:    return "fs2";
        case rv::rvREG::FS3:    return "fs3";
        case rv::rvREG::FS4:    return "fs4";
        case rv::rvREG::FS5:    return "fs5";
        case rv::rvREG::FS6:    return "fs6";
        case rv::rvREG::FS7:    return "fs7";
        case rv::rvREG::FS8:    return "fs8";
        case rv::rvREG::FS9:    return "fs9";
        case rv::rvREG::FS10:   return "fs10";
        case rv::rvREG::FS11:   return "fs11";
        case rv::rvREG::FT8:    return "ft8";
        case rv::rvREG::FT9:    return "ft9";
        case rv::rvREG::FT10:   return "ft10";
        case rv::rvREG::FT11:   return "ft11";
        default:    assert(0 && "Error rvREG Type");
    }
}

/* ---------- generator.h ---------- */

/* ---------- 框架函数 ---------- */

backend::Generator::Generator(ir::Program& p, std::ofstream& f): program(p), fout(f) {}

void backend::Generator::gen() {
    // 输出基本头部
    set_nopic();
    // 处理全局变量
    solve_global_data();
    // 进入代码段
    set_text();
    // 按顺序处理每个函数
    for (int i = 0; i < int(this->program.functions.size())-1; i++)
        solve_func(this->program.functions[i]);
}

void backend::Generator::solve_global_data(){
    // 处理全局变量（包括整型/浮点型变量/数组）
    set_data();
    const ir::Function& global_func = this->program.functions.back();   // 语义分析中最后一个是最大的全局函数

    // 1.处理整型与浮点型变量声明
    for (const ir::Instruction* instr : global_func.InstVec){
        auto instr_des = instr->des;
        auto instr_op1 = instr->op1;
        auto instr_op2 = instr->op2;
        auto instr_op = instr->op;
        if (instr_op == ir::Operator::def || instr_op == ir::Operator::fdef){
            this->fout << "\t.globl\t" << instr_des.name << "\n";
            this->fout << "\t.type\t" << instr_des.name << ", @object\n";
            this->fout << "\t.size\t" << instr_des.name << ", 4\n";
            this->fout << "\t.align\t" << "4\n";
            set_label(instr_des.name);
            assert(instr_op1.type != ir::Type::Int && instr_op1.type != ir::Type::Float);
            if (instr_des.type == ir::Type::Int){       // 不处理浮点数
                assert(instr_op1.type == ir::Type::IntLiteral);
                this->fout << "\t.word\t" << instr_op1.name << "\n";
            }
        }
    }

    // 2.处理有初始值的数组
    std::unordered_map<std::string,ir::GlobalVal> global_array_vals;
    for (const ir::GlobalVal& array_globalval : this->program.globalVal){
        if (array_globalval.val.type == ir::Type::IntPtr)
            global_array_vals.emplace(array_globalval.val.name, array_globalval);
    }
    for (const ir::Instruction* instr : global_func.InstVec){
        auto instr_des = instr->des;
        auto instr_op1 = instr->op1;
        auto instr_op2 = instr->op2;
        auto instr_op = instr->op;
        if (instr_op == ir::Operator::store){
            if (global_array_vals.count(instr_op1.name)){
                auto& array_globalval = global_array_vals.find(instr_op1.name)->second;
                int arr_len = array_globalval.maxlen;
                this->fout << "\t.globl\t" << instr_op1.name << "\n";
                this->fout << "\t.type\t" << instr_op1.name << ", @object\n";
                this->fout << "\t.size\t" << instr_op1.name << ", " << arr_len * 4 << "\n";
                this->fout << "\t.align\t" << "4\n";
                set_label(instr_op1.name);
                global_array_vals.erase(instr_op1.name);
            }
            assert(instr_des.type != ir::Type::Int && instr_des.type != ir::Type::Float);
            if (instr_des.type == ir::Type::IntLiteral){
                this->fout << "\t.word\t" << instr_des.name << "\n";
            }
        }
    }

    // 3.将所有没有进行初始化的数组放入bss中
    if (global_array_vals.size() > 0){
        set_bss();
        for (const auto& array_globalval : global_array_vals){
            this->fout << "\t.globl\t" << array_globalval.first << "\n";
            this->fout << "\t.type\t" << array_globalval.first << ", @object\n";
            this->fout << "\t.size\t" << array_globalval.first << ", " << array_globalval.second.maxlen * 4 << "\n";
            this->fout << "\t.align\t" << "4\n";
            set_label(array_globalval.first);
            this->fout << "\t.space\t" << array_globalval.second.maxlen * 4 << "\n";
        }
    }
}

void backend::Generator::solve_func(const ir::Function& func){
    this->fout << "\t.globl\t" << func.name << "\n";
    this->fout << "\t.type\t" << func.name << ", @function\n";
    set_label(func.name);

    // 函数初始化：计算所用栈空间、为相关参数分配寄存器
    init_func(&func);

    // 根据函数中的每条指令生成汇编
    for (const ir::Instruction* instr : func.InstVec){
        this->curr_ir_addr++;
        if (this->jump_label_map.count(this->curr_ir_addr)){
            set_label(this->jump_label_map[this->curr_ir_addr]);
        }
        generate_INST(*instr);
    }

    this->fout << "\t.size\t" << func.name << ", .-" << func.name << "\n";
}

void backend::Generator::generate_INST(const ir::Instruction& instr){
    ir::Operator instr_op = instr.op;
    switch (instr_op){
        case ir::Operator::add:
            generate_add(instr);
            break;
        case ir::Operator::sub:
            generate_sub(instr);
            break;
        case ir::Operator::mul:
            generate_mul(instr);
            break;
        case ir::Operator::div:
            generate_div(instr);
            break;
        case ir::Operator::mod:
            generate_mod(instr);
            break;
        case ir::Operator::lss:
            generate_lss(instr);
            break;
        case ir::Operator::leq:
            generate_leq(instr);
            break;
        case ir::Operator::gtr:
            generate_gtr(instr);
            break;
        case ir::Operator::geq:
            generate_geq(instr);
            break;
        case ir::Operator::eq:
            generate_eq(instr);
            break;
        case ir::Operator::neq:
            generate_neq(instr);
            break;
        case ir::Operator::_not:
            generate_not(instr);
            break;
        case ir::Operator::_and:
            generate_and(instr);
            break;
        case ir::Operator::_or:
            generate_or(instr);
            break;
        case ir::Operator::alloc:
            generate_alloc(instr);
            break;
        case ir::Operator::load:
            generate_load(instr);
            break;
        case ir::Operator::store:
            generate_store(instr);
            break;
        case ir::Operator::getptr:
            generate_getptr(instr);
            break;
        case ir::Operator::_return:
            generate_return(instr);
            break;
        case ir::Operator::call:
            generate_call(instr);
            break;
        case ir::Operator::_goto:
            generate_goto(instr);
            break;
        case ir::Operator::def:
        case ir::Operator::mov:
            generate_mov(instr);
            break;
        case ir::Operator::__unuse__:
            generate_unuse(instr);
            break;
        default:
            std::cout << "Not Implemented:" << ir::toString(instr_op) << std::endl;
            break;
    }
}

void backend::Generator::init_func(const ir::Function* func){
    // 清空所有记录
    this->var_in_sta.clear();
    this->jump_label_map.clear();
    this->curr_ir_addr = -1;
    this->curr_stack_used_bytes = 0;
    this->free_int_regs.clear();

    // 重置寄存器分配记录
    this->free_int_regs.insert(this->int_regs.begin(), this->int_regs.end());

    // 统计函数func中的变量数量并压入集合
    std::unordered_set<std::string> operand_set;
    // 扫描函数的参数列表
    for (ir::Operand para:func->ParameterList){
        operand_set.insert(para.name);
    }
    // 扫描所有相关指令中的操作数（全局变量不会被计入）
    for (int i = 0; i < func->InstVec.size(); i++){
        // 分别扫描des、op1、op2
        auto instr_des = func->InstVec[i]->des;
        auto instr_op1 = func->InstVec[i]->op1;
        auto instr_op2 = func->InstVec[i]->op2;
        // des
        if (instr_des.type != ir::Type::null && instr_des.type != ir::Type::IntLiteral){
            if (!is_global(instr_des.name))
                operand_set.insert(instr_des.name);
        }
        // op1
        if (instr_op1.type != ir::Type::null && instr_op1.type != ir::Type::IntLiteral){
            if (!is_global(instr_op1.name))
                operand_set.insert(instr_op1.name);
        }
        // op2
        if (instr_op2.type != ir::Type::null && instr_op2.type != ir::Type::IntLiteral){
            if (!is_global(instr_op2.name))
                operand_set.insert(instr_op2.name);
        }
    }

    // 计算需要腾出寄存器的数量
    this->stack_size = (operand_set.size() + 13) * 4;
    std::cout << "Estimated Stack Size For " << func->name << " :" << this->stack_size << "\n";
    this->fout << "\taddi\tsp,sp,-" << this->stack_size << "\n";

    // 记录变量在栈中的位置，即var_in_sta
    int curr_offset = 0;
    // 将S0~S11、RA存入栈
    for (rv::rvREG reg: this->saved_callee_regs){
        this->var_in_sta["saved_callee_"+toString(reg)] = curr_offset;
        // 保存寄存器内容到栈中
        this->fout << "\tsw\t" << toString(reg) << "," << curr_offset << "(sp)\n";
        curr_offset += 4;
    }

    // 将函数参数列表存入栈
    for (int i = 0; i < func->ParameterList.size(); i++){
        // 不支持浮点数函数参数
        assert(func->ParameterList[i].type == ir::Type::Int || func->ParameterList[i].type == ir::Type::IntPtr);
        this->var_in_sta[func->ParameterList[i].name] = curr_offset;
        // 还需要完成从寄存器/帧中加载到栈
        if (i <= 7){        // 将函数相关寄存器（A0~A7）中参数存储到栈
            this->fout << "\tsw\t" << toString(this->int_arg_regs[i]) << ", " << curr_offset << "(sp)\n";
        }
        else{               // 函数参数列表太长时需要存储到栈
            this->fout << "\tlw\tt0, " << this->stack_size+(i-8)*4 << "(sp)\n";
            this->fout << "\tsw\tt0, " << curr_offset << "(sp)\n";
        }
        curr_offset += 4;
    }

    // 为函数体中的变量分配寄存器（全局变量不会被计入）
    for (int i = 0; i < func->InstVec.size(); i++){
        // 分别扫描des、op1、op2
        auto instr_des = func->InstVec[i]->des;
        auto instr_op1 = func->InstVec[i]->op1;
        auto instr_op2 = func->InstVec[i]->op2;
        // des
        if (instr_des.type != ir::Type::null && instr_des.type != ir::Type::IntLiteral){
            if (!is_global(instr_des.name) && this->var_in_sta.find(instr_des.name) == this->var_in_sta.end()){
                this->var_in_sta[instr_des.name] = curr_offset;
                curr_offset += 4;
            }
        }
        // op1
        if (instr_op1.type != ir::Type::null && instr_op1.type != ir::Type::IntLiteral){
            if (!is_global(instr_op1.name) && this->var_in_sta.find(instr_op1.name) == this->var_in_sta.end()){
                this->var_in_sta[instr_op1.name] = curr_offset;
                curr_offset += 4;
            }
        }
        // op2
        if (instr_op2.type != ir::Type::null && instr_op2.type != ir::Type::IntLiteral){
            if (!is_global(instr_op2.name) && this->var_in_sta.find(instr_op2.name) == this->var_in_sta.end()){
                this->var_in_sta[instr_op2.name] = curr_offset;
                curr_offset += 4;
            }
        }
    }

    // 扫描所有GOTO指令，分配LABEL名对应的IR指令地址
    for (int i = 0; i < func->InstVec.size(); i++){
        auto instr = func->InstVec[i];
        if (instr->op == ir::Operator::_goto){
            int jump_label_offset = std::stoi(instr->des.name);
            if (!this->jump_label_map.count(i + jump_label_offset))
                this->jump_label_map[i + jump_label_offset] = "_ir_goto_label" + std::to_string(this->label_count++);
        }
    }
}

/* ---------- 寄存器分配相关函数 ---------- */

bool backend::Generator::is_global(const std::string& operand_name){
    for (auto globalval: this->program.globalVal){
        if(globalval.val.name == operand_name)    return true;
    }
    return false;
}

rv::rvREG backend::Generator::alloc_and_load_int_reg(ir::Operand operand){
    assert((operand.type == ir::Type::Int) || (operand.type == ir::Type::IntPtr));
    // 分配整数寄存器
    rv::rvREG result = alloc_int_reg();
    // 判断是全局变量还是局部变量
    if (!is_global(operand.name)){      // 局部变量从栈中加载
        this->fout << "\tlw\t" << toString(result) << ", " << this->var_in_sta[operand.name] << "(sp)\n";
    }
    else{                               // 全局变量从全局变量表中加载
        if (operand.type == ir::Type::Int){
            rv::rvREG tmp_addr_reg = alloc_int_reg();
            this->fout << "\tla\t" << toString(tmp_addr_reg) << ", " << operand.name << "\n";
            this->fout << "\tlw\t" << toString(result) << ", 0(" << toString(tmp_addr_reg) << ")\n";
            free_int_reg(tmp_addr_reg);
        }
        else
            this->fout << "\tla\t" << toString(result) << ", " << operand.name << "\n";
    }
    return result;
}

rv::rvREG backend::Generator::alloc_int_reg(){
    // 从空闲的整数寄存器中取出一个并从free_int_regs中弹出
    rv::rvREG result = *(this->free_int_regs.begin());  
    this->free_int_regs.erase(result);
    return result;
}

void backend::Generator::free_int_reg(rv::rvREG int_reg){
    // 将用完了的寄存器还原回空闲的整数寄存器中
    this->free_int_regs.insert(int_reg);
}

void backend::Generator::save_int_operand(ir::Operand operand, rv::rvREG int_reg){
    assert(operand.type == ir::Type::Int || operand.type == ir::Type::IntPtr);
    // 判断是全局变量还是局部变量
    if (!is_global(operand.name)){      // 局部变量存入栈中
        this->fout << "\tsw\t" << toString(int_reg) << ", " << this->var_in_sta[operand.name] << "(sp)\n";
    }
    else{                               // 全局变量存入全局变量表中
        rv::rvREG tmp_addr_reg = alloc_int_reg();
        this->fout << "\tla\t" << toString(tmp_addr_reg) << ", " << operand.name << "\n";
        this->fout << "\tsw\t" << toString(int_reg) << ", 0(" << toString(tmp_addr_reg) << ")\n";
        free_int_reg(tmp_addr_reg);
    }
}

/* ---------- 根据不同指令生成汇编函数（辅助generate_INST函数） ---------- */

void backend::Generator::generate_add(const ir::Instruction& instr){
    // op1 + op2 -> des，实验2中保证了计算结果均为变量
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\tadd\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_sub(const ir::Instruction& instr){
    //op1 - op2 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\tsub\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_mul(const ir::Instruction& instr){
    //op1 * op2 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\tmul\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_div(const ir::Instruction& instr){
    //op1 / op2 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\tdiv\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_mod(const ir::Instruction& instr){
    //op1 % op2 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\trem\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_lss(const ir::Instruction& instr){
    //op1 < op2 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\tslt\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_leq(const ir::Instruction& instr){
    //op1 <= op2 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\tslt\t" << toString(tmp_des_reg) << "," << toString(tmp_op2_reg) << "," << toString(tmp_op1_reg) << "\n";
    this->fout << "\txori\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_gtr(const ir::Instruction& instr){
    //op1 > op2 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\tslt\t" << toString(tmp_des_reg) << "," << toString(tmp_op2_reg) << "," << toString(tmp_op1_reg) << "\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_geq(const ir::Instruction& instr){
    //op1 >= op2 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\tslt\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    this->fout << "\txori\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_eq(const ir::Instruction& instr){
    //op1 == op2 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\txor\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    this->fout << "\tsltiu\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);  
}

void backend::Generator::generate_neq(const ir::Instruction& instr){
    //op1 != op2 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\txor\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    this->fout << "\tsltiu\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n";
    this->fout << "\txori\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);  
}

void backend::Generator::generate_not(const ir::Instruction& instr){
    //!op1 -> des
    rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\tsltiu\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << ",1\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_and(const ir::Instruction& instr){
    //op1 && op2 -> des
    rv::rvREG tmp_op1_reg;
    rv::rvREG tmp_op2_reg;
    rv::rvREG tmp_des_reg;
    if (instr.op1.type == ir::Type::IntLiteral){        // op1为常量
        tmp_op1_reg = alloc_int_reg();
        tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
        tmp_des_reg = alloc_int_reg();
        this->fout << "\tli\t" << toString(tmp_op1_reg) << "," << instr.op1.name << "\n";
        this->fout << "\tsltiu\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tsltiu\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tand\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << "," << toString(tmp_op2_reg) << "\n";
    }
    else if (instr.op2.type == ir::Type::IntLiteral){   // op2为常量
        tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        tmp_op2_reg = alloc_int_reg();
        tmp_des_reg = alloc_int_reg();
        this->fout << "\tli\t" << toString(tmp_op2_reg) << "," << instr.op2.name << "\n";
        this->fout << "\tsltiu\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tsltiu\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tand\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << "," << toString(tmp_op2_reg) << "\n";
    }
    else{                                               // 全变量
        tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
        tmp_des_reg = alloc_int_reg();
        this->fout << "\tsltiu\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tsltiu\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tand\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << "," << toString(tmp_op2_reg) << "\n";
    }
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_or(const ir::Instruction& instr){
    //op1 || op2 -> des
    rv::rvREG tmp_op1_reg;
    rv::rvREG tmp_op2_reg;
    rv::rvREG tmp_des_reg;
    if (instr.op1.type == ir::Type::IntLiteral){        // op1为常量
        tmp_op1_reg = alloc_int_reg();
        tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
        tmp_des_reg = alloc_int_reg();
        this->fout << "\tli\t" << toString(tmp_op1_reg) << "," << instr.op1.name << "\n";
        this->fout << "\tsltiu\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tsltiu\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tor\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << "," << toString(tmp_op2_reg) << "\n";
    }
    else if (instr.op2.type == ir::Type::IntLiteral){   // op2为常量
        tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        tmp_op2_reg = alloc_int_reg();
        tmp_des_reg = alloc_int_reg();
        this->fout << "\tli\t" << toString(tmp_op2_reg) << "," << instr.op2.name << "\n";
        this->fout << "\tsltiu\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tsltiu\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tor\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << "," << toString(tmp_op2_reg) << "\n";
    }
    else{                                               // 全变量
        tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
        tmp_des_reg = alloc_int_reg();
        this->fout << "\tsltiu\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tsltiu\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 1  非0 - 0
        this->fout << "\txori\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",1\n"; // 0 - 0  非0 - 1
        this->fout << "\tor\t" << toString(tmp_des_reg) << "," << toString(tmp_des_reg) << "," << toString(tmp_op2_reg) << "\n";
    }
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_alloc(const ir::Instruction& instr){
    // op1为数组长度，des为数组名

    // 申请内存
    this->curr_stack_used_bytes += std::stoi(instr.op1.name) * 4;
    // 将申请到的内存地址存入目的操作数
    rv::rvREG tmp_des_reg = alloc_int_reg();
    this->fout << "\taddi\t" << toString(tmp_des_reg) << "," << "sp" << "," << -(this->curr_stack_used_bytes) << "\n";
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_load(const ir::Instruction& instr){
    // op1为数组名，op2为数组下标，des为目标变量
    rv::rvREG tmp_op1_reg;
    rv::rvREG tmp_op2_reg;
    rv::rvREG tmp_des_reg;
    if (instr.op2.type == ir::Type::IntLiteral){        // op2为常量IntLiteral
        tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        tmp_op2_reg = alloc_int_reg();
        int arr_offset = std::stoi(instr.op2.name) * 4; // 计算数组下标对应的地址
        tmp_des_reg = alloc_int_reg();
        this->fout << "\tli\t" << toString(tmp_op2_reg) << "," << arr_offset << "\n";
        this->fout << "\tadd\t" << toString(tmp_op1_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
        this->fout << "\tlw\t" << toString(tmp_des_reg) << "," << "0("+toString(tmp_op1_reg)+")" << "\n";
    }
    else{                                               // op2为变量
        tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
        tmp_des_reg = alloc_int_reg();
        this->fout << "\tslli\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",2\n";
        this->fout << "\tadd\t" << toString(tmp_op1_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
        this->fout << "\tlw\t" << toString(tmp_des_reg) << "," << "0("+toString(tmp_op1_reg)+")" << "\n";
    }
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_store(const ir::Instruction& instr){
    // op1为数组名，op2为数组下标，des为目标变量
    rv::rvREG tmp_op1_reg;
    rv::rvREG tmp_op2_reg;
    rv::rvREG tmp_des_reg;
    if (instr.op2.type == ir::Type::IntLiteral){
        tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        tmp_op2_reg = alloc_int_reg();
        int arr_offset = std::stoi(instr.op2.name) * 4;
        if (instr.des.type == ir::Type::IntLiteral){
            tmp_des_reg = alloc_int_reg();
            this->fout << "\tli\t" << toString(tmp_des_reg) << "," << instr.des.name << "\n";
        }
        else{
            tmp_des_reg = alloc_and_load_int_reg(instr.des);
        }
        this->fout << "\tli\t" << toString(tmp_op2_reg) << "," << arr_offset << "\n";
        this->fout << "\tadd\t" << toString(tmp_op1_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
        this->fout << "\tsw\t" << toString(tmp_des_reg) << "," << "0("+toString(tmp_op1_reg)+")" << "\n";
    }
    else{
        tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
        if (instr.des.type == ir::Type::IntLiteral){
            tmp_des_reg = alloc_int_reg();
            this->fout << "\tli\t" << toString(tmp_des_reg) << "," << instr.des.name << "\n";
        }
        else{
            tmp_des_reg = alloc_and_load_int_reg(instr.des);
        }
        this->fout << "\tslli\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",2\n";
        this->fout << "\tadd\t" << toString(tmp_op1_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
        this->fout << "\tsw\t" << toString(tmp_des_reg) << "," << "0("+toString(tmp_op1_reg)+")" << "\n";
    }
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_getptr(const ir::Instruction& instr){
    // op1为数组名，op2为数组下标，des为指针
    rv::rvREG tmp_op1_reg;
    rv::rvREG tmp_op2_reg;
    rv::rvREG tmp_des_reg;
    if (instr.op2.type == ir::Type::IntLiteral){
        if (!is_global(instr.op1.name))
            tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        else{
            tmp_op1_reg = alloc_int_reg();
            this->fout << "\tla\t" << toString(tmp_op1_reg) << "," << instr.op1.name << "\n";
        }
        tmp_op2_reg = alloc_int_reg();
        int arr_offset = std::stoi(instr.op2.name) * 4;
        tmp_des_reg = alloc_int_reg();
        this->fout << "\tli\t" << toString(tmp_op2_reg) << "," << arr_offset << "\n";
        this->fout << "\tadd\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    }
    else{
        if (!is_global(instr.op1.name))
            tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        else{
            tmp_op1_reg = alloc_int_reg();
            this->fout << "\tla\t" << toString(tmp_op1_reg) << "," << instr.op1.name << "\n";
        }
        tmp_op2_reg = alloc_and_load_int_reg(instr.op2);
        tmp_des_reg = alloc_int_reg();
        this->fout << "\tslli\t" << toString(tmp_op2_reg) << "," << toString(tmp_op2_reg) << ",2\n";
        this->fout << "\tadd\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "," << toString(tmp_op2_reg) << "\n";
    }
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_op1_reg);
    free_int_reg(tmp_op2_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_return(const ir::Instruction& instr){
    // 根据函数返回值类型，将结果保存在a0或fa0中
    if (instr.op1.type == ir::Type::IntLiteral){
        this->fout << "\tli\ta0," << std::stoi(instr.op1.name) << "\n";
    }
    else if (instr.op1.type == ir::Type::Int){
        rv::rvREG tmp_reg = alloc_and_load_int_reg(instr.op1);
        this->fout << "\tmv\ta0," << toString(tmp_reg) << "\n";
        free_int_reg(tmp_reg);
    }
    else if (instr.op1.type == ir::Type::Float){
        assert(0 && "Float not supported.");
    }
    // 恢复保存寄存器
    for (auto reg : this->saved_callee_regs){
        this->fout << "\tlw\t" << toString(reg) << "," << this->var_in_sta["saved_callee_"+toString(reg)] << "(sp)\n";
    }
    // 恢复sp寄存器
    this->fout << "\taddi\tsp,sp," << this->stack_size << "\n";
    // 返回
    this->fout << "\tret\n";
}

void backend::Generator::generate_call(const ir::Instruction& instr){
    // op1.name为函数名，des为函数返回值
    const auto* instr_ptr = &instr;
    auto callinst_ptr = dynamic_cast<const ir::CallInst*>(instr_ptr);
    assert(callinst_ptr != nullptr);
    if (instr.op1.name == "main" || instr.op1.name == "global"){
        return;
    }
    // 判断是否要多开栈空间
    if (callinst_ptr->argumentList.size() > 8){
        this->curr_stack_used_bytes += (callinst_ptr->argumentList.size() - 8) * 4;
    }
    // 首先将所有参数存入对应的寄存器
    for (int i = 0; i < callinst_ptr->argumentList.size(); i++){
        if (i <= 7){            // 放入a0~a7
            if (callinst_ptr->argumentList[i].type == ir::Type::IntLiteral){
                this->fout << "\tli\t" << toString(this->int_arg_regs[i]) << "," << callinst_ptr->argumentList[i].name << "\n";
            }
            else{
                rv::rvREG tmp_reg = alloc_and_load_int_reg(callinst_ptr->argumentList[i]);
                this->fout << "\tmv\t" << toString(this->int_arg_regs[i]) << "," << toString(tmp_reg) << "\n";
                free_int_reg(tmp_reg);
            }
        }
        else{                   // 放入栈中
            if (callinst_ptr->argumentList[i].type == ir::Type::IntLiteral){
                rv::rvREG tmp = alloc_int_reg();
                rv::rvREG tmp_stack_addr = alloc_int_reg();
                this->fout << "\tli\t" << toString(tmp) << "," << callinst_ptr->argumentList[i].name << "\n";
                this->fout << "\taddi\t" << toString(tmp_stack_addr) << "," << toString(rv::rvREG::SP) << "," << -(this->curr_stack_used_bytes) << "\n";
                this->fout << "\tsw\t" << toString(tmp) << "," << (i-8)*4 << "(" << toString(tmp_stack_addr) << ")\n";
                free_int_reg(tmp);
                free_int_reg(tmp_stack_addr);
            }
            else{
                rv::rvREG tmp = alloc_and_load_int_reg(callinst_ptr->argumentList[i]);
                rv::rvREG tmp_stack_addr = alloc_int_reg();
                this->fout << "\taddi\t" << toString(tmp_stack_addr) << "," << toString(rv::rvREG::SP) << "," << -(this->curr_stack_used_bytes) << "\n";
                this->fout << "\tsw\t" << toString(tmp) << "," << (i-8)*4 << "(" << toString(tmp_stack_addr) << ")\n";
                free_int_reg(tmp);
                free_int_reg(tmp_stack_addr);
            }
        }
    }
    // 设置栈指针
    this->fout << "\taddi\t" << toString(rv::rvREG::SP) << "," << toString(rv::rvREG::SP) << "," << -(this->curr_stack_used_bytes) << "\n";
    // 然后CALL
    this->fout << "\tcall\t" << callinst_ptr->op1.name << "\n";
    // 恢复栈指针
    this->fout << "\taddi\t" << toString(rv::rvREG::SP) << "," << toString(rv::rvREG::SP) << "," << this->curr_stack_used_bytes << "\n";
    // 获取结果
    if (instr.des.type != ir::Type::null)
        save_int_operand(instr.des, rv::rvREG::A0);
}

void backend::Generator::generate_goto(const ir::Instruction& instr){
    // op1为跳转条件，op2不使用，des为跳转相对目前pc的偏移量
    int ir_jump_offset = std::stoi(instr.des.name);
    // 判断有条件/无条件跳转
    if (instr.op1.type == ir::Type::IntLiteral || instr.op1.type == ir::Type::Int){ // 有条件
        rv::rvREG tmp_reg;
        if (instr.op1.type == ir::Type::Int){
            tmp_reg = alloc_and_load_int_reg(instr.op1);
        }
        else{
            tmp_reg = alloc_int_reg();
            this->fout << "\tli\t" << toString(tmp_reg) << "," << instr.op1.name << "\n";
        }
        this->fout << "\tbnez\t" << toString(tmp_reg) << "," << this->jump_label_map[this->curr_ir_addr+ir_jump_offset] << "\n";
        free_int_reg(tmp_reg);
    }
    else{       // 无条件
        this->fout << "\tj\t" << this->jump_label_map[this->curr_ir_addr+ir_jump_offset] << "\n";
    }
}

void backend::Generator::generate_mov(const ir::Instruction& instr){
    // 赋值有2种情况：操作数1为立即数或操作数1为变量
    rv::rvREG tmp_des_reg = alloc_int_reg();
    // 操作数1为立即数
    if (instr.op1.type == ir::Type::IntLiteral){
        this->fout << "\tli\t" << toString(tmp_des_reg) << "," << std::stoi(instr.op1.name) << "\n";
    }
    // 操作数1为变量
    else{
        rv::rvREG tmp_op1_reg = alloc_and_load_int_reg(instr.op1);
        this->fout << "\tmv\t" << toString(tmp_des_reg) << "," << toString(tmp_op1_reg) << "\n";
        free_int_reg(tmp_op1_reg);
    }
    save_int_operand(instr.des, tmp_des_reg);
    free_int_reg(tmp_des_reg);
}

void backend::Generator::generate_unuse(const ir::Instruction& instr){
    this->fout << "\tnop\n";
}

/* ---------- 生成汇编语言的指令前缀函数 ---------- */

void backend::Generator::set_nopic(){
    // 禁用的位置无关代码PIC，可以简化代码
    this->fout << "\t.option nopic\n";
}

void backend::Generator::set_data(){
    // 汇编中包含数据段定义，用于存储变量和常量的内存分配
    this->fout << "\t.data\n";
}

void backend::Generator::set_bss(){
    // 汇编中包含未初始化的全局变量或静态变量
    this->fout << "\t.bss\n";
}

void backend::Generator::set_label(const std::string& lable){
    // 汇编中包含label
    this->fout << lable << ":\n";
}

void backend::Generator::set_text(){
    // 汇编中包含可执行代码
    this->fout << "\t.text\n";
}