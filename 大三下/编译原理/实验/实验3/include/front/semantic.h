// 符号表条目STE中增加属性literalVal以记录该操作数的字面量
/**
 * @file semantic.h
 * @author Yuntao Dai (d1581209858@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-06
 * 
 * a Analyzer should 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include"ir/ir.h"
#include"front/abstract_syntax_tree.h"

#include<map>
#include<string>
#include<vector>
using std::map;
using std::string;
using std::vector;

namespace frontend{

// 符号表条目（Symbol Table Entry），即符号表中的一条记录
struct STE {
    ir::Operand operand;    // 操作数（变量名+变量类型）
    vector<int> dimension;  // 当操作数为数组时存储数组维数，dimension大小表示维数，每个元素表示各维度上的大小
    string literalVal;      // 字面量（即该变量的值）
};

// 定义map<string, STE>容器（即符号表）类型的别名为map_str_ste
using map_str_ste = map<string, STE>;
// 作用域：可以嵌套，最外层的是全局作用域，名称按顺序记录
struct ScopeInfo {
    int cnt;                // 作用域编号
    string name;            // 作用域名称（block cnt）
    map_str_ste table;      // 该作用域内操作数的原始变量名->符号表条目（map_str_ste即map<string, STE>）
};

// IO库函数名称到对应库函数的映射
map<std::string,ir::Function*>* get_lib_funcs();

// 符号表（Symbol Table）
struct SymbolTable{
    vector<ScopeInfo> scope_stack;  // 一张符号表中可以存储多个作用域，因为作用域可以嵌套。scope_stack大小为1时表示在全局作用域
    map<std::string,ir::Function*> functions;   // 函数名称到对应函数的映射
    int block_cnt = 0;              // 记录当前作用域序号（虽然作用域i结束后会被弹出scope_stack，但作用域名称中的编号是只增不减的）

    // 增加作用域
    void add_scope();

    // 结束最内层作用域，弹出scope_stack末尾元素
    void exit_scope();

    // 根据操作数的原始变量名查找最近作用域内的相应变量并返回其在该前作用域下重命名后的名字{变量名, 作用域名}
    string get_scoped_name(string id) const;

    // 根据操作数的原始变量名查找最近作用域内的相应变量并返回该操作数（重命名后的变量名+变量类型）
    ir::Operand get_operand(string id) const;

    // 根据操作数的原始变量名查找最近作用域内的符号表条目
    STE get_ste(string id) const;
};


// singleton class
struct Analyzer {
    int tmp_cnt;
    vector<ir::Instruction*> g_init_inst;   // 全局变量初始化指令
    SymbolTable symbol_table;               // 全局符号表
    ir::Program ir_program;                 // 程序
    ir::Function* curr_function = nullptr;  // 当前函数指针

    // 构造函数
    Analyzer();
    // 禁止复制或赋值函数
    Analyzer(const Analyzer&) = delete;
    Analyzer& operator=(const Analyzer&) = delete;

    // 核心函数，根据AST得到IR
    ir::Program get_ir_program(CompUnit*);

    // 辅助函数，分析表达式的结构，返回中间生成的IR指令
    void analyze_compunit(CompUnit*);
    vector<ir::Instruction *> analyze_decl(Decl*);
    void analyze_funcdef(FuncDef*);
    ir::Type analyze_functype(FuncType*);
    string analyze_ident(Term*);
    ir::Operand analyze_funcfparam(FuncFParam *root);
    vector<ir::Operand> analyze_funcfparams(FuncFParams*);
    vector<ir::Instruction *> analyze_funcrparams(FuncRParams*, vector<ir::Operand> &, vector<ir::Operand> &);  // 分析函数返回参数列表还需要返回IR指令，也需要函数传入参数列表
    ir::Type analyze_btype(BType*);
    vector<ir::Instruction *> analyze_block(Block*, bool);
    vector<ir::Instruction *> analyze_blockitem(BlockItem*);
    vector<ir::Instruction *> analyze_stmt(Stmt*);
    vector<ir::Instruction *> analyze_constdecl(ConstDecl*);
    vector<ir::Instruction *> analyze_constdef(ConstDef*, ir::Type);
    vector<ir::Instruction *> analyze_constinitval(ConstInitVal*, ir::Type, int, string);
    vector<ir::Instruction *> analyze_vardecl(VarDecl*);
    vector<ir::Instruction *> analyze_vardef(VarDef*, ir::Type);
    vector<ir::Instruction *> analyze_initval(InitVal*, ir::Type, int, string);
    
    // 辅助函数，计算表达式的值，结果写入v，类型写入t，返回中间生成的IR指令
    vector<ir::Instruction *> analyze_exp(Exp*);
    vector<ir::Instruction *> analyze_constexp(ConstExp*);    // 常数计算不生成指令，因此返回空数组
    vector<ir::Instruction *> analyze_addexp(AddExp*);
    vector<ir::Instruction *> analyze_mulexp(MulExp*);
    vector<ir::Instruction *> analyze_unaryexp(UnaryExp*);
    vector<ir::Instruction *> analyze_primaryexp(PrimaryExp*);
    vector<ir::Instruction *> analyze_lval(LVal*);
    vector<ir::Instruction *> analyze_number(Number*);        // 常数计算不生成指令，因此返回空数组
    vector<ir::Instruction *> analyze_cond(Cond*);
    vector<ir::Instruction *> analyze_lorexp(LOrExp*);
    vector<ir::Instruction *> analyze_landexp(LAndExp*);
    vector<ir::Instruction *> analyze_eqexp(EqExp*);
    vector<ir::Instruction *> analyze_relexp(RelExp*);

    // 辅助函数，在计算表达式的值的时候进行类型转换
    void IntLiteral2Int(AstNode*, AstNode*, frontend::NodeType, vector<ir::Instruction *> &);
    void IntLiteral2FloatLiteral(AstNode*, AstNode*, frontend::NodeType);
    void IntLiteral2Float(AstNode*, AstNode*, frontend::NodeType, vector<ir::Instruction *> &);
    void Int2Float(AstNode*, AstNode*, frontend::NodeType, vector<ir::Instruction *> &);
    void FloatLiteral2Float(AstNode*, AstNode*, frontend::NodeType, vector<ir::Instruction *> &);
};

} // namespace frontend

#endif