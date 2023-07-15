#include"tools/sylib.h"
#include"front/semantic.h"
#include"tools/ir_executor.h"

#include<stdio.h>
#include<cassert>
#include<iostream>

#define TODO assert(0 && "TODO");
#define DEBUG_EXEC_BRIEF  1
#define DEBUG_EXEC_DETAIL 0
#define IS_INT_OPERAND(operand) (operand.type == Type::Int || operand.type == Type::IntLiteral)
#define IS_FLOAT_OPERAND(operand) (operand.type == Type::Float || operand.type == Type::FloatLiteral)


using ir::Type;

int ir::eval_int(std::string s) {
#if (DEBUG_EXEC_DETAIL)
    std::cout << "\teval_int: " << s << std::endl;
#endif
    if (s.size() >= 2 && (s.substr(0,2)=="0b" || s.substr(0,2)=="0B")) {
        return std::stoi(s.substr(2, s.size()-2), nullptr, 2); 
    }
    else if (s.size() >= 2 && (s.substr(0,2)=="0x" || s.substr(0,2)=="0X")) {
        return std::stoi(s.substr(2, s.size()-2), nullptr, 16);
    }
    else if (s.size() > 1 && s.substr(0,1)=="0") {
        return std::stoi(s.substr(1, s.size()-1), nullptr, 8);
    }
    else {
        return std::stoi(s);
    }
}

ir::Context::Context(const ir::Function* pf): pc(0), retval_addr(nullptr), mem(std::map<std::string, Value>()), pfunc(pf) {} 

ir::Executor::Executor(const ir::Program* pp, std::ostream& os): out(os), program(pp), global_vars(std::map<std::string, Value>()), cur_ctx(nullptr), cxt_stack(std::stack<Context*>()) {}

ir::Value ir::Executor::find_src_operand(Operand op) {
#if (DEBUG_EXEC_DETAIL)
    std::cout << "\tin find_src_operand(" << toString(op.type) << " " << op.name  << ")";
#endif
    ir::Value retval;
    
    if (op.type == Type::IntLiteral) {
        return {Type::Int, eval_int(op.name)};
    }
    else if (op.type == Type::FloatLiteral) {
        retval.t = Type::Float;
        retval._val.fval = (float)std::atof(op.name.c_str());
        return retval;
    }

    auto iter = cur_ctx->mem.find(op.name);
    if (iter == cur_ctx->mem.end()) {
        iter = global_vars.find(op.name);
        assert(iter != global_vars.end() && "can not find the arguement in current conxtext or global variables");
    } 
    retval = iter->second;
    assert(retval.t == op.type && "type not match");
#if (DEBUG_EXEC_DETAIL)
    std::cout << ", value = ";
    switch (retval.t) {
    case Type::Int:
    case Type::IntLiteral:
        std::cout << retval._val.ival << std::endl;
    break;
    case Type::Float:
    case Type::FloatLiteral:
        std::cout << retval._val.fval << std::endl;
    break;
    default:
        std::cout << retval._val.iptr << std::endl;
        break;
    }
#endif
    return retval;      
}

ir::Value* ir::Executor::get_des_operand(Operand op) {
#if (DEBUG_EXEC_DETAIL)
    std::cout << "\tin get_des_operand(" << toString(op.type) << " " << op.name  << ")";
#endif
    ir::Value* retval = nullptr;
    auto iter = cur_ctx->mem.find(op.name);
    if (iter != cur_ctx->mem.end()) {                   // find the operand in current context
        retval = &iter->second;
    }
    else {
        iter = global_vars.find(op.name);
        if (iter != global_vars.end()) {               // find the operand in global variable
            retval = &iter->second;
        }
        else {                                              // both not, then create a new one
#if (DEBUG_EXEC_DETAIL)
    std::cout << ", new des (" << toString(op.type) << " " << op.name  << ")";
#endif
            cur_ctx->mem.insert({op.name, {op.type, 0}});
            retval = &cur_ctx->mem.find(op.name)->second;
        }
    }

#if (DEBUG_EXEC_DETAIL)
    std::cout << ", value = ";
    switch (retval->t) {
    case Type::Int:
    case Type::IntLiteral:
        std::cout << retval->_val.ival << std::endl;
    break;
    case Type::Float:
    case Type::FloatLiteral:
        std::cout << retval->_val.fval << std::endl;
    break;
    default:
        std::cout << retval->_val.iptr << std::endl;
        break;
    }
#endif
    return retval;
}

int ir::Executor::run() {
    // init global variables
    for(const auto& gte: program->globalVal) {
        std::pair<std::string, Value> entry = {gte.val.name, {gte.val.type, 0}};
        if (gte.maxlen) {
            if (gte.val.type == Type::IntPtr) {
                entry.second._val.iptr = new int[gte.maxlen];
                // global variable need to init as 0
                for (size_t i = 0; i < gte.maxlen; i++) {
                    entry.second._val.iptr[i] = 0;
                }
                
            }
            else if (gte.val.type == Type::FloatPtr) {
                entry.second._val.fptr = new float[gte.maxlen];
                // global variable need to init as 0
                for (size_t i = 0; i < gte.maxlen; i++) {
                    entry.second._val.fptr[i] = 0;
                }
            }
            else {
                assert(0 && "wrong global value type with maxlen > 0");
            }
        }
        global_vars.insert(entry);
    }

    // find main function and set cur_cxt
    for(const auto& f: program->functions) {
        if (f.name == "main") {
            cur_ctx = new Context(&f);
            break;
        }
    }

    // check cur_ctx valid
    if (!cur_ctx) {
        std::cout << "no main function";
        exit(-1);
    }

    // run
    Value main_func_retval;
    cur_ctx->retval_addr = &main_func_retval;
    cxt_stack.push(cur_ctx);
    while (cur_ctx) {
        exec_ir();
    }
    
    return main_func_retval._val.ival;
}

bool ir::Executor::exec_ir(size_t n) {
    while (n--) {
        assert(cur_ctx->pc < cur_ctx->pfunc->InstVec.size());
        auto inst = cur_ctx->pfunc->InstVec[cur_ctx->pc];
#if (DEBUG_EXEC_BRIEF || DEBUG_EXEC_DETAIL)
    std::cout << cur_ctx->pc << ": " << inst->draw() << std::endl;
#endif
        switch (inst->op) {
            case Operator::_return: {
                if (cur_ctx->retval_addr != nullptr) {
                    switch (inst->op1.type) {
                    case Type::IntLiteral:
                        cur_ctx->retval_addr->t = Type::Int;
                        cur_ctx->retval_addr->_val.ival = eval_int(inst->op1.name);
                    break;
                    case Type::FloatLiteral:
                        cur_ctx->retval_addr->t = Type::Float;
                        cur_ctx->retval_addr->_val.fval = std::atof(inst->op1.name.c_str());
                    break;
                    case Type::Int:
                    case Type::Float:
                        *cur_ctx->retval_addr = find_src_operand(inst->op1);
                    break;
                    default:
                        assert(0 && "invalid return value type");
                        break;
                    }
                }
                // switch context
                if (cxt_stack.size()) {        // in main function return
                    cur_ctx = cxt_stack.top();
                    cxt_stack.pop();
                }
                else {
                    delete cur_ctx;     // FIXME destructor for Context
                    cur_ctx = nullptr;
                }
            } break;
            case Operator::_goto: {
                int off = 0;
                if (IS_INT_OPERAND(inst->des)) {
                    off = find_src_operand(inst->des)._val.ival;
                }
                else {
                    assert(0 && "in Operator::goto, des should be a Type::Int or Type::IntLiteral");
                }

                if (inst->op1.type == Type::null || find_src_operand(inst->op1)._val.ival) {
                    cur_ctx->pc += off;
                }
                else {
                    cur_ctx->pc++;
                }
#if (DEBUG_EXEC_BRIEF || DEBUG_EXEC_DETAIL)
    std::cout << "\tin goto: pc = " << cur_ctx->pc << std::endl;
#endif
            } break;
            case Operator::call: {
                auto callinst = dynamic_cast<CallInst*>(inst); 
                auto fn = callinst->op1.name;

                // lib functions
                Value libfunc_retval;
                if (exec_lib_function(callinst, &libfunc_retval)) {
                    if (callinst->des.type != Type::null) {
                        *get_des_operand(inst->des) = libfunc_retval; 
                    }
                    cur_ctx->pc++;
                    break;
                }

                // ir::Function
                Context* cxt = nullptr;
                for(auto& f: program->functions) {
                    if (f.name == fn) {
                        cxt = new Context(&f);
                    }
                } 

                // return type checking
                assert(cxt->pfunc->returnType == Type::null || inst->des.type == cxt->pfunc->returnType);
                if (cxt->pfunc->returnType != Type::null) {
                    cxt->retval_addr = get_des_operand(inst->des);
                }

                if (cxt) {
                    // type checking
                    for (size_t i = 0; i < cxt->pfunc->ParameterList.size(); i++) {
                        auto para = cxt->pfunc->ParameterList[i];
                        assert(i < callinst->argumentList.size() && "callinst's arguement list should match function's parameter list");
                        auto arg = callinst->argumentList[i];
                        switch (arg.type) {
                        case Type::Int:
                        case Type::IntLiteral:
                            assert(para.type == Type::Int);
                            break;
                        case Type::Float:
                        case Type::FloatLiteral:
                            assert(para.type == Type::Float);
                            break;                        
                        // pointers
                        default:
                            assert(arg.type == para.type);
                            break;
                        }
                        // pass arguement into new context
                        cxt->mem.insert({para.name, find_src_operand(arg)});
                    }
                    cur_ctx->pc++;
                    cxt_stack.push(cur_ctx);
                    cur_ctx = cxt;
                } 
                else {
                    assert(0 && "could not find the function in ir::Program");
                }
            } break;
            case Operator::alloc: {
                int size;
                if (IS_INT_OPERAND(inst->op1)) {
                    size = find_src_operand(inst->op1)._val.ival;
                }
                else {
                    assert(0 && "in Operator::alloc, op1 should be integer");
                }
                
                if (inst->des.type == Type::IntPtr) {
                    get_des_operand(inst->des)->_val.iptr = new int[size];
                }
                else if (inst->des.type == Type::FloatPtr) {
                    get_des_operand(inst->des)->_val.fptr = new float[size];
                }
                else {
                    assert(0 && "in Operator::alloc, des should be pointer");
                }
            } break;
            case Operator::store: {
                int off;
                if (IS_INT_OPERAND(inst->op2)) {
                    off = find_src_operand(inst->op2)._val.ival;
                }
                else {
                    assert(0 && "in Operator::store, op2 should be integer");
                }

                if (IS_INT_OPERAND(inst->des) && inst->op1.type == Type::IntPtr) {
                    find_src_operand(inst->op1)._val.iptr[off] = find_src_operand(inst->des)._val.ival;
                }
                else if (IS_FLOAT_OPERAND(inst->des) && inst->op1.type == Type::FloatPtr) {
                    find_src_operand(inst->op1)._val.fptr[off] = find_src_operand(inst->des)._val.fval;
                }
                else {
                    assert(0 && "in Operator::store, op1 should be a pointer and des should be the matched type");
                }
            } break;
            case Operator::load: {
                int off;
                if (IS_INT_OPERAND(inst->op2)) {
                    off = find_src_operand(inst->op2)._val.ival;
                }
                else {
                    assert(0 && "in Operator::load, op2 should be integer");
                }

                if (IS_INT_OPERAND(inst->des) && inst->op1.type == Type::IntPtr) {
                    get_des_operand(inst->des)->_val.ival = find_src_operand(inst->op1)._val.iptr[off];
                }
                else if (IS_FLOAT_OPERAND(inst->des) && inst->op1.type == Type::FloatPtr) {
                    get_des_operand(inst->des)->_val.fval = find_src_operand(inst->op1)._val.fptr[off];
                }
                else {
                    assert(0 && "in Operator::load, op1 should be a pointer and des should be the matched type");
                }
            } break;
            case Operator::getptr: {
                int off;
                if (IS_INT_OPERAND(inst->op2)) {
                    off = find_src_operand(inst->op2)._val.ival;
                }
                else {
                    assert(0 && "in Operator::getptr, op2 should be integer");
                }

                if (inst->des.type == Type::IntPtr && inst->op1.type == Type::IntPtr) {
                    get_des_operand(inst->des)->_val.iptr = find_src_operand(inst->op1)._val.iptr + off;
                }
                else if (inst->des.type == Type::FloatPtr && inst->op1.type == Type::FloatPtr) {
                    get_des_operand(inst->des)->_val.fptr = find_src_operand(inst->op1)._val.fptr + off;
                }
                else {
                    assert(0 && "in Operator::getptr, op1 should be a pointer and des should be the matched type");
                }
            } break;
            case Operator::mov: 
            case Operator::def: {
                assert(IS_INT_OPERAND(inst->des));
                auto pvalue = get_des_operand(inst->des);
                if (IS_INT_OPERAND(inst->op1)) {
                    *pvalue = find_src_operand(inst->op1);
                }
                else {
                    assert(0 && "in Operator::def[mov], op1 has a wrong type");
                }
#if (DEBUG_EXEC_DETAIL)
                    std::cout << "\tdes operand(" << toString(inst->des.type) << " " << inst->des.name  << "), value = " << pvalue->_val.ival << std::endl;
#endif
            } break;
            case Operator::_not: {
                assert(inst->des.type == Type::Int);
                auto pvalue = get_des_operand(inst->des);
                int value = 0;
                if (IS_INT_OPERAND(inst->op1)) {
                    value = find_src_operand(inst->op1)._val.ival;
                }
                else {
                    assert(0 && "in Operator::_not, op1 has a wrong type");
                }
                pvalue->_val.ival = (value == 0);
#if (DEBUG_EXEC_DETAIL)
                    std::cout << "\tdes operand(" << toString(inst->des.type) << " " << inst->des.name  << "), value = " << pvalue->_val.ival << std::endl;
#endif
            } break;
            case Operator::fdef: 
            case Operator::fmov: {
                assert(inst->des.type == Type::Float);
                auto pvalue = get_des_operand(inst->des);
                if (IS_FLOAT_OPERAND(inst->op1)) {
                    *pvalue = find_src_operand(inst->op1);
                }
                else {
                    assert(0 && "in Operator::fdef[fmov], op1 has a wrong type");
                }
#if (DEBUG_EXEC_DETAIL)
                    std::cout << "\tdes operand(" << toString(inst->des.type) << " " << inst->des.name  << "), value = " << pvalue->_val.ival << std::endl;
#endif
            } break;
            case Operator::cvt_i2f: {
                assert(inst->des.type == Type::Float);
                auto pvalue = get_des_operand(inst->des);
                if (IS_INT_OPERAND(inst->op1)) {
                    pvalue->_val.fval = (float)find_src_operand(inst->op1)._val.ival;
                }
                else {
                    assert(0 && "in Operator::cvt_i2f, op1 has a wrong type");
                }
#if (DEBUG_EXEC_DETAIL)
                    std::cout << "\tdes operand(" << toString(inst->des.type) << " " << inst->des.name  << "), value = " << pvalue->_val.fval << std::endl;
#endif
            } break;
            case Operator::cvt_f2i: {
                assert(inst->des.type == Type::Int);
                auto pvalue = get_des_operand(inst->des);
                if (IS_FLOAT_OPERAND(inst->op1)) {
                    pvalue->_val.ival = (int)find_src_operand(inst->op1)._val.fval;
                }
                else {
                    assert(0 && "in Operator::cvt_f2i, op1 has a wrong type");
                }
#if (DEBUG_EXEC_DETAIL)
                    std::cout << "\tdes operand(" << toString(inst->des.type) << " " << inst->des.name  << "), value = " << pvalue->_val.ival << std::endl;
#endif
            } break;
            // 2 int operand
            case Operator::add: 
            case Operator::sub:
            case Operator::mul:
            case Operator::div:
            case Operator::mod:
            case Operator::lss:
            case Operator::leq:
            case Operator::gtr:
            case Operator::geq:
            case Operator::eq:
            case Operator::neq:
            case Operator::_and: 
            case Operator::_or: 
            {
                assert(inst->des.type == Type::Int);
                // op1
                int v1;
                if (IS_INT_OPERAND(inst->op1)) {
                    v1 = find_src_operand(inst->op1)._val.ival;
                }
                else {
                    assert(0 && "type of op1 is not Type::Int or Type::IntLiteral");
                }
                // op2
                int v2;
                if (IS_INT_OPERAND(inst->op2)) {
                    v2 = find_src_operand(inst->op2)._val.ival;
                }
                else {
                    assert(0 && "type of op2 is not Type::Int or Type::IntLiteral");
                }
                auto pvalue = get_des_operand(inst->des);
                switch (inst->op) {
                    case Operator::add:
                        pvalue->_val.ival = v1 + v2;
                    break; 
                    case Operator::sub:
                        pvalue->_val.ival = v1 - v2;
                    break; 
                    case Operator::mul:
                        pvalue->_val.ival = v1 * v2;
                    break; 
                    case Operator::div:
                        pvalue->_val.ival = v1 / v2;
                    break; 
                    case Operator::mod:
                        pvalue->_val.ival = v1 % v2;
                    break; 
                    case Operator::lss:
                        pvalue->_val.ival = (v1 < v2);
                    break; 
                    case Operator::leq:
                        pvalue->_val.ival = (v1 <= v2);
                    break; 
                    case Operator::gtr:
                        pvalue->_val.ival = (v1 > v2);
                    break; 
                    case Operator::geq:
                        pvalue->_val.ival = (v1 >= v2);
                    break; 
                    case Operator::eq:
                        pvalue->_val.ival = (v1 == v2);
                    break; 
                    case Operator::neq:
                        pvalue->_val.ival = (v1 != v2);
                    break; 
                    case Operator::_and:
                        pvalue->_val.ival = (v1 != 0 && v2 != 0);
                    break; 
                    case Operator::_or:
                        pvalue->_val.ival = (v1 != 0 || v2 != 0);
                    break; 
                    default:
                        assert(0 && "should not reach hear!");
                }
#if (DEBUG_EXEC_DETAIL)
                    std::cout << "\tdes operand(" << toString(inst->des.type) << " " << inst->des.name  << "), value = " << pvalue->_val.ival << std::endl;
#endif
            } break;
            case Operator::addi: 
            case Operator::subi:
            {
                int v1 = find_src_operand(inst->op1)._val.ival;
                assert(inst->op1.type == Type::Int);
                int v2 = eval_int(inst->op2.name);
                assert((inst->op2.type == Type::IntLiteral));
                get_des_operand(inst->des)->_val.ival = (inst->op == Operator::addi) ? v1 + v2 : v1 - v2;
            } break;
            case Operator::fadd:
            case Operator::fsub:
            case Operator::fmul:
            case Operator::fdiv:
            case Operator::flss:
            case Operator::fleq:
            case Operator::fgtr:
            case Operator::fgeq:
            case Operator::feq:
            case Operator::fneq:
            {
                assert(inst->des.type == Type::Float);
                // op1
                float v1;
                if (IS_FLOAT_OPERAND(inst->op1)) {
                    v1 = find_src_operand(inst->op1)._val.fval;
                }
                else {
                    assert(0 && "type of op1 is not Type::Int or Type::IntLiteral");
                }
                // op2
                float v2;
                if (IS_FLOAT_OPERAND(inst->op2)) {
                    v2 = find_src_operand(inst->op2)._val.fval;
                }
                else {
                    assert(0 && "type of op2 is not Type::Int or Type::IntLiteral");
                }
                auto pvalue = get_des_operand(inst->des);
                switch (inst->op) {
                    case Operator::fadd:
                        pvalue->_val.fval = v1 + v2;
                    break; 
                    case Operator::fsub:
                        pvalue->_val.fval = v1 - v2;
                    break; 
                    case Operator::fmul:
                        pvalue->_val.fval = v1 * v2;
                    break; 
                    case Operator::fdiv:
                        pvalue->_val.fval = v1 / v2;
                    break; 
                    case Operator::flss:
                        pvalue->_val.fval = (v1 < v2);
                    break; 
                    case Operator::fleq:
                        pvalue->_val.fval = (v1 <= v2);
                    break; 
                    case Operator::fgtr:
                        pvalue->_val.fval = (v1 > v2);
                    break; 
                    case Operator::fgeq:
                        pvalue->_val.fval = (v1 >= v2);
                    break; 
                    case Operator::feq:
                        pvalue->_val.fval = (v1 == v2);
                    break; 
                    case Operator::fneq:
                        pvalue->_val.fval = (v1 != v2);
                    break; 
                    default:
                        assert(0 && "should not reach hear!");
                }
#if (DEBUG_EXEC_DETAIL)
                    std::cout << "\tdes operand(" << toString(inst->des.type) << " " << inst->des.name  << "), value = " << pvalue->_val.fval << std::endl;
#endif
            } break;
        case Operator::__unuse__:
            break;
        // default:
        //     break;
        }
        // increase pc
        switch (inst->op) {
        case Operator::_return:
        case Operator::call:
        case Operator::_goto:
            break;
        default:
            cur_ctx->pc++;
            break;
        }
    }
    return true;
}

using frontend::get_lib_funcs;
bool ir::Executor::exec_lib_function(const ir::CallInst* callinst, Value* p_retval) {
    auto fn = callinst->op1.name;
    if (get_lib_funcs()->find(fn) == get_lib_funcs()->end()) {
        return false;
    }
    switch (callinst->des.type) {
    case Type::Int: {
        p_retval->t = Type::Int;
        if (fn == "getint") {
            p_retval->_val.ival = getint();
        }
        else if (fn == "getch") {
            p_retval->_val.ival = getch();
        }
        else if (fn == "getarray") {
            auto arr = find_src_operand(callinst->argumentList[0]);
            assert(arr.t == Type::IntPtr && "argument do not match getarray(int*)");
            p_retval->_val.ival = getarray(arr._val.iptr);
        }
        else if (fn == "getfarray") {
            auto arr = find_src_operand(callinst->argumentList[0]);
            assert(arr.t == Type::FloatPtr && "argument do not match getfarray(float*)");
            p_retval->_val.ival = getfarray(arr._val.fptr);
        } 
        else {
            assert(0 && "lib function returnType do not match des.type");
        }
    } break;
    case Type::Float: {
        assert(fn == "getfloat" && "lib function returnType do not match des.type");
        p_retval->t = Type::Float;
        p_retval->_val.fval = getfloat();
    } break;
    case Type::null: {
        auto arg1 = find_src_operand(callinst->argumentList[0]);
        if (fn == "putint") {
            assert(arg1.t == Type::Int && "argument do not match putint(int)");
            putint(arg1._val.ival);
        }
        else if (fn == "putch") {
            assert(arg1.t == Type::Int && "argument do not match putch(int)");
            putch(arg1._val.ival);
        }
        else if (fn == "putfloat") {
            assert(arg1.t == Type::Float && "argument do not match putfloat(float)");
            putfloat(arg1._val.fval);
        }
        else if (fn == "putarray") {
            auto arg2 = find_src_operand(callinst->argumentList[1]);
            assert(arg1.t == Type::Int && arg2.t == Type::IntPtr && "argument do not match putarray(int,int*)");
            putarray(arg1._val.ival, arg2._val.iptr);
        }
        else if (fn == "putfarray") {
            auto arg2 = find_src_operand(callinst->argumentList[1]);
            assert(arg1.t == Type::Int && arg2.t == Type::FloatPtr && "argument do not match putfarray(int,float*)");
            putfarray(arg1._val.ival, arg2._val.fptr);
        }
        else {
            assert(0 && "lib function returnType do not match des.type");
        }
    }
    break;
    default:
        assert(0 && "lib function returnType do not match des.type");
        break;
    }
    return true;
}


FILE* ir::reopen_output_file = nullptr;
FILE* ir::reopen_input_file = nullptr;

/* Input & output functions */
int getint() {
    int t; 
    fscanf(ir::reopen_input_file, "%d",&t); 
    return t; 
}

int getch() {
    char c; 
    fscanf(ir::reopen_input_file, "%c",&c); 
    return (int)c; 
}

float getfloat(){
    float n;
    fscanf(ir::reopen_input_file, "%a", &n);
    return n;
}

int getarray(int a[]){
  int n;
  fscanf(ir::reopen_input_file, "%d",&n);
  for(int i=0;i<n;i++)fscanf(ir::reopen_input_file, "%d",&a[i]);
  return n;
}

int getfarray(float a[]) {
    int n;
    fscanf(ir::reopen_input_file, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(ir::reopen_input_file, "%a", &a[i]);
    }
    return n;
}

void putint(int a) { 
    fprintf(ir::reopen_output_file, "%d",a);
}

void putch(int a) {
    fprintf(ir::reopen_output_file, "%c",a);
}

void putarray(int n,int a[]){
  fprintf(ir::reopen_output_file, "%d:",n);
  for(int i=0;i<n;i++)fprintf(ir::reopen_output_file, " %d",a[i]);
  fprintf(ir::reopen_output_file, "\n");
}

void putfloat(float a) {
  fprintf(ir::reopen_output_file, "%a", a);
}

void putfarray(int n, float a[]) {
    fprintf(ir::reopen_output_file, "%d:", n);
    for (int i = 0; i < n; i++) {
        fprintf(ir::reopen_output_file, " %a", a[i]);
    }
    fprintf(ir::reopen_output_file, "\n");
}
