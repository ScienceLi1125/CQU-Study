/**
 * @file ir_executor.h
 * @author Yuntao Dai (d1581209858@live.com)
 * @brief the ir executor, take a ir::Program as input, then execute it
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef IR_EXECUTOR_H
#define IR_EXECUTOR_H

#include"ir/ir.h"

#include<map>
#include<stack>
#include<string>
#include<cstdint>
#include<fstream>
#include<iostream>


namespace ir {

// for Input & output functions
extern FILE* reopen_output_file;
extern FILE* reopen_input_file;

// helper function

/**
 * @brief evaluate the int literal
 * @return int 
 */
int eval_int(std::string);


union _4bytes {
    int32_t ival;
    float   fval;
    int*    iptr;
    float*  fptr;
};

// definition of value of a operand in memory
struct Value {
    Type t;
    _4bytes _val;
};

// definition of function context
struct Context {
    uint32_t pc;                            // program counter of a function
    Value* retval_addr;                   // if it's not nullptr, this addr will be written when exit a context, 
    std::map<std::string, Value> mem;
    const ir::Function* pfunc;              // executing which function 

    /**
     * @brief constructor
     */
    Context(const ir::Function*);
};


// definition of ir executor
struct Executor {
    std::ostream& out;

    const ir::Program* program;
    std::map<std::string, Value> global_vars;

    Context* cur_ctx;
    Instruction* cur_inst;
    std::stack<Context*> cxt_stack;

    /**
     * @brief constructor
     */
    Executor(const ir::Program*, std::ostream& os = std::cout);

    /**
     * @brief execute the ir program and return its main function's return value
     * @return int: the main function's return value
     */
    int run();

    /**
     * @brief execute next n IRs
     * @return true : execute without error occurs
     * @return false: sth bad happens
     */
    bool exec_ir(size_t n = 1);

private:
    /**
     * @brief find the Value of Operand.name in current context, and check if the type match, create a temp Value for Literal operand
     * @return Value : return the Value 
     */
    Value find_src_operand(Operand);

    /**
     * @brief find the Value of Operand.name in current context, and check if the type match
     *        if do not find one, then create a new operand
     * @return Value* : return poniter of the Value 
     */
    Value* get_des_operand(Operand);

    /**
     * @brief if the ir::CallInst is calling a lib function, then execute the function and return true
     * @param[in]   callinst: the ir::CallInst  
     * @param[out]  p_retval: the return value address
     * @return bool : return true if the callinst calling a lib function
    */
    bool exec_lib_function(const ir::CallInst* callinst, Value* p_retval);
};



} // namespace ir


#endif