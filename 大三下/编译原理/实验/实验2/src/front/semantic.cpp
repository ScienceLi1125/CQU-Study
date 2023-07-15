/* 语义分析
    实验1已经得到了抽象语法树AST，实验2通过深度遍历AST按源程序的顺序来分析源程序，得到中间表示IR
    作用域允许嵌套且不同作用域中可以定义同名变量，在翻译成IR的过程中为解决不同作用域中同名变量需要重命名
    语义分析的核心函数是get_ir_program，根据所给文法调用analyze_XX函数生成IR指令
*/
#include "front/semantic.h"

#include <cassert>
#include <iostream>

using ir::Function;
using ir::Instruction;
using ir::Operand;
using ir::Operator;

#define TODO assert(0 && "TODO");

// 获取index处的特定类型的子节点的指针
#define GET_CHILD_PTR(node, type, index) auto node = dynamic_cast<type*>(root->children[index]); assert(node); 
#define ANALYSIS(node, type, index) auto node = dynamic_cast<type*>(root->children[index]); assert(node); analysis##type(node, buffer);
#define COPY_EXP_NODE(from, to) to->is_computable = from->is_computable; to->v = from->v; to->t = from->t;

map<std::string, ir::Function *> *frontend::get_lib_funcs(){
    // IO库函数名称到对应库函数的映射
    static map<std::string, ir::Function *> lib_funcs = {
        {"getint", new Function("getint", Type::Int)},
        {"getch", new Function("getch", Type::Int)},
        {"getfloat", new Function("getfloat", Type::Float)},
        {"getarray", new Function("getarray", {Operand("arr", Type::IntPtr)}, Type::Int)},
        {"getfarray", new Function("getfarray", {Operand("arr", Type::FloatPtr)}, Type::Int)},
        {"putint", new Function("putint", {Operand("i", Type::Int)}, Type::null)},
        {"putch", new Function("putch", {Operand("i", Type::Int)}, Type::null)},
        {"putfloat", new Function("putfloat", {Operand("f", Type::Float)}, Type::null)},
        {"putarray", new Function("putarray", {Operand("n", Type::Int), Operand("arr", Type::IntPtr)}, Type::null)},
        {"putfarray", new Function("putfarray", {Operand("n", Type::Int), Operand("arr", Type::FloatPtr)}, Type::null)},
    };
    return &lib_funcs;
}

void frontend::SymbolTable::add_scope(){
    ScopeInfo scope_info;
    scope_info.cnt = block_cnt;     // 当前作用域编号
    scope_info.name = "block" + std::to_string(block_cnt++);    // 作用域编号递增
    scope_stack.push_back(scope_info);
}

void frontend::SymbolTable::exit_scope(){
    scope_stack.pop_back();     // 结束当前作用域，弹出scope_stack末尾元素
}

string frontend::SymbolTable::get_scoped_name(string id) const{
    // 从内向外查找作用域
    for (int i = scope_stack.size()-1; i>=0; i--){
        if (scope_stack[i].table.find(id) != scope_stack[i].table.end())
            return id + "_" + scope_stack[i].name;      // 返回最近作用域的相应变量的重命名
    }
    assert(0 && "Symbol Not Found");
}

Operand frontend::SymbolTable::get_operand(string id) const{
    // 从内向外查找作用域
    for (int i = scope_stack.size()-1; i>=0; i--){
        auto find_result = scope_stack[i].table.find(id);
        if (find_result != scope_stack[i].table.end())
            return find_result->second.operand;         // 返回最近作用域的相应变量的Operand（变量名+变量类型）
    }
    assert(0 && "Operand Not Found");
}

frontend::STE frontend::SymbolTable::get_ste(string id) const{
    // 从内向外查找作用域
    for (int i=scope_stack.size()-1; i>=0; i--){
        auto find_result = scope_stack[i].table.find(id);
        if (find_result != scope_stack[i].table.end())
            return find_result->second;                 // 返回最近作用域的相应变量的符号表条目
    }
    assert(0 && "STE Not Found");
}

frontend::Analyzer::Analyzer() : tmp_cnt(0), symbol_table(){}

ir::Program frontend::Analyzer::get_ir_program(CompUnit *root){
    // 向全局符号表的作用域数组中压入全局作用域
    symbol_table.add_scope();
    // 向全局符号表的函数字典中压入全局函数
    ir::Function *global_func = new ir::Function("global", ir::Type::null);
    symbol_table.functions["global"] = global_func;
    // 向全局符号表的函数字典中添加库函数
    auto lib_funcs = *get_lib_funcs();
    for (auto it = lib_funcs.begin(); it != lib_funcs.end(); it++)
        symbol_table.functions[it->first] = it->second;
    // DFS遍历AST
    analyze_compunit(root);
    // 向程序的全局变量数组中插入重命名后的全局变量
    for (auto it = symbol_table.scope_stack[0].table.begin(); it != symbol_table.scope_stack[0].table.end(); it++){
        // 该条目是数组
        if (it->second.dimension.size() != 0){
            int arr_len = 1;
            for (int i = 0; i < it->second.dimension.size(); i++)
                arr_len *= it->second.dimension[i];
            ir_program.globalVal.push_back({{symbol_table.get_scoped_name(it->second.operand.name),it->second.operand.type}, arr_len});
        }
        // 该条目是普通变量
        else {
            // FloatLiteral改为Float，IntLiteral改为Int
            if (it->second.operand.type == Type::FloatLiteral)
                ir_program.globalVal.push_back({{symbol_table.get_scoped_name(it->second.operand.name),Type::Float}});
            else if (it->second.operand.type == Type::IntLiteral)
                ir_program.globalVal.push_back({{symbol_table.get_scoped_name(it->second.operand.name),Type::Int}});
            else
                ir_program.globalVal.push_back({{symbol_table.get_scoped_name(it->second.operand.name),it->second.operand.type}});
        }
    }
    // 向全局函数中添加返回值
    ir::Instruction* globalreturn = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(), ir::Operator::_return);
    global_func->addInst(globalreturn);
    ir_program.addFunction(*global_func);

    return ir_program;
}

/*
CompUnit -> (Decl | FuncDef) [CompUnit]
Decl -> ConstDecl | VarDecl
ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
BType -> 'int' | 'float'
ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
ConstInitVal -> ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
VarDecl -> BType VarDef { ',' VarDef } ';'
VarDef -> Ident { '[' ConstExp ']' } [ '=' InitVal ]
InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'
FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
FuncType -> 'void' | 'int' | 'float'
FuncFParam -> BType Ident ['[' ']' { '[' Exp ']' }]
FuncFParams -> FuncFParam { ',' FuncFParam }
Block -> '{' { BlockItem } '}'
BlockItem -> Decl | Stmt
Stmt -> LVal '=' Exp ';' | Block | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] | 'while' '(' Cond ')' Stmt | 'break' ';' | 'continue' ';' | 'return' [Exp] ';' | [Exp] ';'
Exp -> AddExp
Cond -> LOrExp
LVal -> Ident {'[' Exp ']'}
Number -> IntConst | floatConst
PrimaryExp -> '(' Exp ')' | LVal | Number
UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
UnaryOp -> '+' | '-' | '!'
FuncRParams -> Exp { ',' Exp }
MulExp -> UnaryExp { ('*' | '/' | '%') UnaryExp }
AddExp -> MulExp { ('+' | '-') MulExp }
RelExp -> AddExp { ('<' | '>' | '<=' | '>=') AddExp }
EqExp -> RelExp { ('==' | '!=') RelExp }
LAndExp -> EqExp [ '&&' LAndExp ]
LOrExp -> LAndExp [ '||' LOrExp ]
ConstExp -> AddExp
*/

// ---------- 辅助函数，分析表达式的结构 ----------

// CompUnit -> (Decl | FuncDef) [CompUnit]
void frontend::Analyzer::analyze_compunit(CompUnit *root){
    assert(root->children.size() != 0);
    // ----- 判断分支 -----
    if (Decl *decl = dynamic_cast<Decl *>(root->children[0])){  // 分支Decl，此处声明的都是全局变量
        // 调用analyze_decl获取该部分的IR指令
        vector<ir::Instruction *> decl_insts = analyze_decl(decl);
        for (auto inst : decl_insts)
            // 该部分的IR指令都是全局函数的内部指令
            symbol_table.functions["global"]->addInst(inst);
    }
    else if (FuncDef *funcdef = dynamic_cast<FuncDef *>(root->children[0])){    // 分支FuncDef
        analyze_funcdef(funcdef);                               // 函数声明，其指令都放在函数内部
    }
    else{
        assert(0 && "Invalid CompUnit");
    }
    // ----- 可选CompUnit -----
    if (root->children.size() > 1){                             // 若children的长度为2，则继续分析
        CompUnit *dcast_compunit = dynamic_cast<CompUnit *>(root->children[1]);
        assert(dcast_compunit != nullptr);
        analyze_compunit(dcast_compunit);
    }
}

// Decl -> ConstDecl | VarDecl
vector<ir::Instruction *> frontend::Analyzer::analyze_decl(Decl *root){
    assert(root->children.size() != 0);
    // ----- 判断分支 -----
    if (ConstDecl *constdecl = dynamic_cast<ConstDecl *>(root->children[0])){   // 分支ConstDecl
        return analyze_constdecl(constdecl);
    }
    else if (VarDecl *vardecl = dynamic_cast<VarDecl *>(root->children[0])){    // 分支VarDecl
        return analyze_vardecl(vardecl);
    }
    else{
        assert(0 && "Invalid Decl");
    }
}

// ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
vector<ir::Instruction *> frontend::Analyzer::analyze_constdecl(ConstDecl* root){
    vector<ir::Instruction *> result;
    // BType
    auto btype = dynamic_cast<BType*>(root->children[1]);
    assert(btype != nullptr);
    ir::Type type = analyze_btype(btype);
    // ConstDef { ',' ConstDef }
    for (int i=2; i<root->children.size(); i+=2){       // 并列声明的常量放在for循环里一起处理
        // ConstDef
        ConstDef* constdef = dynamic_cast<ConstDef*>(root->children[i]);
        assert(constdef != nullptr);
        vector<Instruction *> cal_insts = analyze_constdef(constdef, type);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
    }
    return result;
}

// ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
vector<ir::Instruction *> frontend::Analyzer::analyze_constdef(ConstDef* root, ir::Type type){
    vector<ir::Instruction *> result;
    // Ident，返回标识符名称
    string var_name = analyze_ident(dynamic_cast<Term*>(root->children[0]));
    
    // 普通常量 Ident '=' ConstInitVal
    if (root->children.size() == 3){ // 只是定义一个非数组
        // 记录符号表条目
        STE var_ste;
        if (type == ir::Type::Int){
            var_ste.operand = ir::Operand(var_name, ir::Type::IntLiteral);
            // Literal值的计算放在后面
        }
        else if (type == ir::Type::Float){
            var_ste.operand = ir::Operand(var_name, ir::Type::FloatLiteral);
            // Literal值的计算放在后面
        }
        else{
            assert(0 && "Invalid Type");
        }
        // 插入符号表
        symbol_table.scope_stack.back().table[var_name] = var_ste;
        // ConstInitVal
        ConstInitVal* constinit = dynamic_cast<ConstInitVal*>(root->children.back());
        assert(constinit != nullptr);
        // ConstExp
        ConstExp* constexp = dynamic_cast<ConstExp*>(constinit->children[0]);
        assert(constexp != nullptr);
        // 计算ConstExp的值
        analyze_constexp(constexp);
        // 符号表中存放Literal值
        symbol_table.scope_stack.back().table[var_name].literalVal = constexp->v;
        if (type == ir::Type::Int){
            int val;
            if (constexp->t == ir::Type::FloatLiteral)
                val = std::stof(constexp->v);
            else if (constexp->t == ir::Type::IntLiteral)
                val = std::stoi(constexp->v);
            else
                assert(0 && "Invalid Type");
            ir::Instruction* defInst = new ir::Instruction(ir::Operand(std::to_string(val),ir::Type::IntLiteral),
                                                           ir::Operand(),
                                                           ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Int),ir::Operator::def);
            result.push_back(defInst);
        }
        else if (type == ir::Type::Float){
            float val = std::stof(constexp->v);
            ir::Instruction* defInst = new ir::Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                           ir::Operand(),
                                                           ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Float),ir::Operator::fdef);
            result.push_back(defInst);
        }
        else{
            assert(0 && "Invalid Type");
        }
    }
    // 一维数组 Ident '[' ConstExp ']' '=' ConstInitVal
    else if (root->children.size() == 6){
        ConstExp* constexp = dynamic_cast<ConstExp*>(root->children[2]);
        assert(constexp != nullptr);
        // ConstExp计算数组形状
        analyze_constexp(constexp);     // 返回空数组，不必接收
        assert(constexp->t == ir::Type::IntLiteral);
        int array_size = std::stoi(constexp->v);
        // 记录符号表条目
        STE arr_ste;
        ir::Type curr_type = type;
        arr_ste.dimension.push_back(array_size);
        if (curr_type == ir::Type::Int){
            curr_type = ir::Type::IntPtr;
        }
        else if (curr_type == ir::Type::Float){
            curr_type = ir::Type::FloatPtr;
        }
        else{
            assert(0 && "Invalid Type");
        }
        arr_ste.operand = ir::Operand(var_name, curr_type);
        // 插入符号表
        symbol_table.scope_stack.back().table[var_name] = arr_ste;
        // 生成IR指令 (为全局数组时不用!!)
        if (symbol_table.scope_stack.size() > 1){
            ir::Instruction* allocInst = new ir::Instruction(ir::Operand(std::to_string(array_size),ir::Type::IntLiteral),
                                                             ir::Operand(),
                                                             ir::Operand(symbol_table.get_scoped_name(var_name),curr_type),ir::Operator::alloc);
            result.push_back(allocInst);
        }
        // ConstInitVal，一维数组的初始化只能为{a,b,c...}
        ConstInitVal* constinit = dynamic_cast<ConstInitVal*>(root->children.back());
        assert(constinit != nullptr);
        vector<Instruction *> cal_insts = analyze_constinitval(constinit,curr_type,array_size,var_name);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
    }
    // 二维数组Ident '[' ConstExp ']' '=' ConstInitVal
    else if (root->children.size() == 9){
        // Ident '[' ConstExp ']' '[' ConstExp ']' '=' ConstInitVal
        ConstExp* constexp1 = dynamic_cast<ConstExp*>(root->children[2]);
        assert(constexp1 != nullptr);
        ConstExp* constexp2 = dynamic_cast<ConstExp*>(root->children[5]);
        assert(constexp2 != nullptr);
        // ConstExp计算数组形状
        analyze_constexp(constexp1);
        analyze_constexp(constexp2);
        assert(constexp1->t == ir::Type::IntLiteral && constexp2->t == ir::Type::IntLiteral);
        int array_dim1 = std::stoi(constexp1->v); // 第一维大小
        int array_dim2 = std::stoi(constexp2->v); // 第二维大小
        int array_size = array_dim1 * array_dim2;
        // 记录符号表条目
        STE arr_ste;
        arr_ste.dimension.push_back(array_dim1);
        arr_ste.dimension.push_back(array_dim2);
        ir::Type curr_type = type;
        if (curr_type == ir::Type::Int){
            curr_type = ir::Type::IntPtr;
        }
        else if (curr_type == ir::Type::Float){
            curr_type = ir::Type::FloatPtr;
        }
        else{
            assert(0 && "Invalid Type");
        }
        arr_ste.operand = ir::Operand(var_name, curr_type);
        // 插入符号表
        symbol_table.scope_stack.back().table[var_name] = arr_ste;
        // 生成IR指令 (为全局数组时不用!!)
        if (symbol_table.scope_stack.size() > 1){
            ir::Instruction* allocInst = new ir::Instruction(ir::Operand(std::to_string(array_size),ir::Type::IntLiteral),
                                                             ir::Operand(),
                                                             ir::Operand(symbol_table.get_scoped_name(var_name),curr_type),ir::Operator::alloc);
            result.push_back(allocInst);
        }
        // ConstInitVal，测试用例中二维的初始化也为{a,b,c...}
        ConstInitVal* constinit = dynamic_cast<ConstInitVal*>(root->children.back());
        assert(constinit != nullptr);
        vector<Instruction *> cal_insts = analyze_constinitval(constinit,curr_type,array_size,var_name);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
    }
    else{   // C++语法最多允许二维数组
        assert(0 && "Invalid ConstDef");
    }

    return result;
}

// ConstInitVal -> ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
vector<ir::Instruction *> frontend::Analyzer::analyze_constinitval(ConstInitVal* root, ir::Type curr_type, int array_size, string var_name){
    vector<ir::Instruction *> result;
    // ConstInitVal
    int cnt = 0;
    for (int i=1; i<root->children.size()-1; i+=2, cnt+=1){
        // ConstInitVal
        ConstInitVal* child_constinit = dynamic_cast<ConstInitVal*>(root->children[i]);
        assert(child_constinit != nullptr);
        // ConstExp
        ConstExp* constexp = dynamic_cast<ConstExp*>(child_constinit->children[0]);
        assert(constexp != nullptr);
        // 计算ConstExp的值
        analyze_constexp(constexp);
        if (curr_type == ir::Type::IntPtr){
            // 允许隐式类型转化 Float -> Int
            assert(constexp->t == ir::Type::FloatLiteral || constexp->t == ir::Type::IntLiteral);
            int val;
            if (constexp->t == ir::Type::Float){
                val = std::stof(constexp->v);
            }
            else{
                val = std::stoi(constexp->v);
            }
            ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                             ir::Operand(std::to_string(cnt),ir::Type::IntLiteral),
                                                             ir::Operand(std::to_string(val),ir::Type::IntLiteral),ir::Operator::store);
            result.push_back(storeInst);
        }
        else if (curr_type == ir::Type::FloatPtr){
            // 允许类型提升 Int -> Float
            assert(constexp->t == ir::Type::FloatLiteral || constexp->t == ir::Type::IntLiteral);
            float val = std::stof(constexp->v);
            ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                                             ir::Operand(std::to_string(cnt),ir::Type::IntLiteral),
                                                             ir::Operand(std::to_string(val),ir::Type::FloatLiteral),ir::Operator::store);
            result.push_back(storeInst);
        }
        else{
            assert(0 && "Invalid analyze Type");
        }
    }
    // 判断是否是全局数组的初始化，若为全局，则ir库会帮我自动将值初始化为0
    // 局部变量初始化，注意此处为Const数组，则其必须使用{}，未指定值的元素一定会被置为0
    if (symbol_table.scope_stack.size() > 1){
        // 局部变量，未指定值置为0
        for (int i=cnt; i<array_size; i++){
            ir::Instruction* storeInst;
            if (curr_type == ir::Type::FloatPtr)
                storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                                ir::Operand(std::to_string(i),ir::Type::IntLiteral),
                                                ir::Operand("0.0",ir::Type::FloatLiteral),ir::Operator::store);
            else if (curr_type == ir::Type::IntPtr)
                storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                ir::Operand(std::to_string(i),ir::Type::IntLiteral),
                                                ir::Operand("0",ir::Type::IntLiteral),ir::Operator::store);
            else
                assert(0 && "Invalid Type");
            result.push_back(storeInst);
        }
    }
    return result;
}

// VarDecl -> BType VarDef { ',' VarDef } ';'
vector<ir::Instruction *> frontend::Analyzer::analyze_vardecl(VarDecl* root){
    vector<ir::Instruction *> result;
    // BType
    auto btype = dynamic_cast<BType*>(root->children[0]);
    assert(btype != nullptr);
    ir::Type type = analyze_btype(btype);
    // VarDef { ',' VarDef }
    for (int i=1; i<root->children.size(); i+=2){
        // VarDef
        VarDef* vardef = dynamic_cast<VarDef*>(root->children[i]);
        assert(vardef != nullptr);
        vector<Instruction *> cal_insts = analyze_vardef(vardef, type);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
    }
    return result;
}

// VarDef -> Ident { '[' ConstExp ']' } [ '=' InitVal ]
vector<ir::Instruction *> frontend::Analyzer::analyze_vardef(VarDef* root, ir::Type type){
    vector<ir::Instruction *> result;
    // Ident，返回标识符名称
    string var_name = analyze_ident(dynamic_cast<Term*>(root->children[0]));

    // 普通变量 Ident 或 Ident '=' InitVal
    if (root->children.size() == 1 || root->children.size() == 3){
        // 记录符号表条目
        STE var_ste;
        var_ste.operand = ir::Operand(var_name, type);
        symbol_table.scope_stack.back().table[var_name] = var_ste;
        // 判断是否初始化，即[ '=' InitVal ]
        if (InitVal* initval = dynamic_cast<InitVal*>(root->children.back())){   // 有初始化值
            // ConstExp
            Exp* exp = dynamic_cast<Exp*>(initval->children[0]);
            assert(exp != nullptr);
            // 计算ConstExp的值
            vector<Instruction*> cal_insts = analyze_exp(exp);
            result.insert(result.end(),cal_insts.begin(),cal_insts.end());
            // 根据当前type判断类型提升
            if (type == ir::Type::Int){     // 允许 Float -> Int
                assert(exp->t == ir::Type::Int || exp->t == ir::Type::IntLiteral || exp->t == ir::Type::Float || exp->t == ir::Type::FloatLiteral);
                if (exp->t == ir::Type::Int || exp->t == ir::Type::IntLiteral){
                    ir::Instruction* defInst = new ir::Instruction(ir::Operand(exp->v,exp->t),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Int),ir::Operator::def);
                    result.push_back(defInst);
                }
                else if (exp->t == ir::Type::Float || exp->t == ir::Type::FloatLiteral){
                    // 需类型转换
                    string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                    if (exp->t == ir::Type::Float){
                        ir::Instruction* cvtInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Float),
                                                                       ir::Operand(),
                                                                       ir::Operand(tmp_intcvt_name,ir::Type::Int),ir::Operator::cvt_f2i);
                        ir::Instruction* defInst = new ir::Instruction(ir::Operand(tmp_intcvt_name,ir::Type::Int),
                                                                       ir::Operand(),
                                                                       ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Int),ir::Operator::def);
                        result.push_back(cvtInst);
                        result.push_back(defInst);
                    }
                    else{
                        int val = std::stof(exp->v);
                        ir::Instruction* defInst = new ir::Instruction(ir::Operand(std::to_string(val),ir::Type::IntLiteral),
                                                                       ir::Operand(),
                                                                       ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Int),ir::Operator::def);
                        result.push_back(defInst);
                    }
                }
                else{
                    assert(0 && "Invalid Type");
                }
            }
            else{                           // 允许 Int -> Float
                if (exp->t == ir::Type::IntLiteral || exp->t == ir::Type::FloatLiteral){
                    float val = std::stof(exp->v);
                    ir::Instruction* defInst = new ir::Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Float),ir::Operator::fdef);
                    result.push_back(defInst);
                }
                else if (exp->t == ir::Type::Int){
                    // 为了支持类型提升，需要将int转换为float
                    string curr_tmp_name = "t" + std::to_string(tmp_cnt++);
                    ir::Instruction* cvtInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Int),
                                                                   ir::Operand(),
                                                                   ir::Operand(curr_tmp_name,ir::Type::Float),ir::Operator::cvt_i2f);                        
                    ir::Instruction* defInst = new ir::Instruction(ir::Operand(curr_tmp_name,ir::Type::Float),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Float),ir::Operator::fdef);
                    result.push_back(cvtInst);
                    result.push_back(defInst);
                }
                else if (exp->t == ir::Type::Float){
                    ir::Instruction* defInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Float),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Float),ir::Operator::fdef);
                    result.push_back(defInst);
                }
                else{
                    assert(0 && "Invalid Type");
                }
            }
        }
        else{ // 没有初始化值，无论是局部还是全局，都初始化为0
            if (type == ir::Type::Int){
                ir::Instruction* defInst = new ir::Instruction(ir::Operand("0",ir::Type::IntLiteral),
                                                               ir::Operand(),
                                                               ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Int),ir::Operator::def);
                result.push_back(defInst);
            }
            else if (type == ir::Type::Float){
                ir::Instruction* defInst = new ir::Instruction(ir::Operand("0.0",ir::Type::FloatLiteral),
                                                               ir::Operand(),
                                                               ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Float),ir::Operator::fdef);
                result.push_back(defInst);
            }
            else{
                assert(0 && "Invalid Type");
            }
        }
    }
    // 一维数组 Ident '[' ConstExp ']' 或 Ident '[' ConstExp ']' '=' InitVal
    else if (root->children.size() == 4 || root->children.size() == 6){
        // ConstExp
        ConstExp* constexp = dynamic_cast<ConstExp*>(root->children[2]);
        assert(constexp != nullptr);
        // ConstExp计算数组形状
        analyze_constexp(constexp);
        assert(constexp->t == ir::Type::IntLiteral);
        int array_size = std::stoi(constexp->v);
        // 记录符号表条目
        STE arr_ste;
        arr_ste.dimension.push_back(array_size);
        ir::Type curr_type = type;
        if (curr_type == ir::Type::Int){
            curr_type = ir::Type::IntPtr;
        }
        else if (curr_type == ir::Type::Float){
            curr_type = ir::Type::FloatPtr;
        }
        else{
            assert(0 && "Invalid Type");
        }
        arr_ste.operand = ir::Operand(var_name, curr_type);
        // 插入符号表
        symbol_table.scope_stack.back().table[var_name] = arr_ste;
        // 生成IR指令 (为全局数组时不用!!)
        if (symbol_table.scope_stack.size() > 1){
            ir::Instruction* allocInst = new ir::Instruction(ir::Operand(std::to_string(array_size),ir::Type::IntLiteral),
                                                             ir::Operand(),
                                                             ir::Operand(symbol_table.get_scoped_name(var_name),curr_type),ir::Operator::alloc);
            result.push_back(allocInst);
        }
        // 判断是否初始化，即[ '=' InitVal ]
        if (InitVal* initval = dynamic_cast<InitVal*>(root->children.back())){  // 需要进行初始化
            // InitVal：一维数组的初始化只能为{a,b,c...}
            vector<Instruction *> cal_insts = analyze_initval(initval,curr_type,array_size,var_name);
            result.insert(result.end(),cal_insts.begin(),cal_insts.end());
        }
    }
    // 二维数组 Ident '[' ConstExp ']' '[' ConstExp ']' 或 Ident '[' ConstExp ']' '[' ConstExp ']' '=' InitVal
    else if (root->children.size() == 7 || root->children.size() == 9){
        // Ident '[' ConstExp ']' '[' ConstExp ']' 或 Ident '[' ConstExp ']' '[' ConstExp ']' '=' InitVal
        ConstExp* constexp1 = dynamic_cast<ConstExp*>(root->children[2]);
        assert(constexp1 != nullptr);
        ConstExp* constexp2 = dynamic_cast<ConstExp*>(root->children[5]);
        assert(constexp2 != nullptr);
        // ConstExp计算数组形状
        analyze_constexp(constexp1);
        analyze_constexp(constexp2);
        assert(constexp1->t == ir::Type::IntLiteral && constexp2->t == ir::Type::IntLiteral);
        int array_dim1 = std::stoi(constexp1->v); // 第一维大小
        int array_dim2 = std::stoi(constexp2->v); // 第二维大小
        int array_size = array_dim1 * array_dim2;
        // 记录符号表条目
        STE arr_ste;
        arr_ste.dimension.push_back(array_dim1);
        arr_ste.dimension.push_back(array_dim2);
        ir::Type curr_type = type;
        if (curr_type == ir::Type::Int){
            curr_type = ir::Type::IntPtr;
        }
        else if (curr_type == ir::Type::Float){
            curr_type = ir::Type::FloatPtr;
        }
        else{
            assert(0 && "Invalid Type");
        }
        arr_ste.operand = ir::Operand(var_name, curr_type);
        // 插入符号表
        symbol_table.scope_stack.back().table[var_name] = arr_ste;
        // 生成IR指令 (为全局数组时不用!!)
        if (symbol_table.scope_stack.size() > 1){
            ir::Instruction* allocInst = new ir::Instruction(ir::Operand(std::to_string(array_size),ir::Type::IntLiteral),
                                                             ir::Operand(),
                                                             ir::Operand(symbol_table.get_scoped_name(var_name),curr_type),ir::Operator::alloc);
            result.push_back(allocInst);
        }
        // 判断是否初始化，即[ '=' InitVal ]
        if (InitVal* initval = dynamic_cast<InitVal*>(root->children.back())){
            // InitVal：测试用例中二维的初始化也为{a,b,c...}
            vector<Instruction *> cal_insts = analyze_initval(initval,curr_type,array_size,var_name);
            result.insert(result.end(),cal_insts.begin(),cal_insts.end());
        }
    }
    else{
        assert(0 && "Invalid ConstDef");
    }
    return result;
}


// InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'
vector<ir::Instruction *> frontend::Analyzer::analyze_initval(InitVal* root, ir::Type curr_type, int array_size, string var_name){
    vector<ir::Instruction *> result;
    // InitVal
    int cnt = 0;
    for (int i=1; i<root->children.size()-1; i+=2, cnt+=1){
        // InitVal
        InitVal* child_initval = dynamic_cast<InitVal*>(root->children[i]);
        assert(child_initval != nullptr);
        // Exp
        Exp* exp = dynamic_cast<Exp*>(child_initval->children[0]);
        assert(exp != nullptr);
        // 计算Exp的值
        vector<Instruction *> cal_insts = analyze_exp(exp);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
        if (curr_type == ir::Type::IntPtr){
            // 允许类型隐式转化 Float -> Int
            assert(exp->t == ir::Type::Float || exp->t == ir::Type::Int || exp->t == ir::Type::IntLiteral || exp->t == ir::Type::FloatLiteral);
            if (exp->t == Type::IntLiteral || exp->t == Type::Int){
                ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                                 ir::Operand(std::to_string(cnt),ir::Type::IntLiteral),
                                                                 ir::Operand(exp->v,exp->t),ir::Operator::store);
                result.push_back(storeInst);
            }
            else{
                if (exp->t == Type::FloatLiteral){
                    int val = std::stof(exp->v);
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                                     ir::Operand(std::to_string(cnt),ir::Type::IntLiteral),
                                                                     ir::Operand(std::to_string(val),Type::IntLiteral),ir::Operator::store);
                    result.push_back(storeInst);
                }
                else{
                    string tmp_floatcvt_name = "t";
                    tmp_floatcvt_name += std::to_string(tmp_cnt++);
                    ir::Instruction* cvtInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Float),
                                                                   ir::Operand(),
                                                                   ir::Operand(tmp_floatcvt_name,ir::Type::Int),ir::Operator::cvt_f2i);
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                                     ir::Operand(std::to_string(cnt),ir::Type::IntLiteral),
                                                                     ir::Operand(tmp_floatcvt_name,Type::Int),ir::Operator::store);
                    result.push_back(cvtInst);
                    result.push_back(storeInst);
                }
            }
        }
        else if (curr_type == ir::Type::FloatPtr){
            // 允许类型提升 Int -> Float
            assert(exp->t == ir::Type::Float || exp->t == ir::Type::Int || exp->t == ir::Type::IntLiteral || exp->t == ir::Type::FloatLiteral);
            if (exp->t == Type::IntLiteral || exp->t == Type::FloatLiteral){
                float val = std::stof(exp->v);
                ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                                                 ir::Operand(std::to_string(cnt),ir::Type::IntLiteral),
                                                                 ir::Operand(std::to_string(val),ir::Type::FloatLiteral),ir::Operator::store);
                result.push_back(storeInst);               
            }
            else if (exp->t == Type::Int){
                // 需类型转换
                string tmp_intcvt_name = "t";
                tmp_intcvt_name += std::to_string(tmp_cnt++);
                ir::Instruction* cvtInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Int),
                                                               ir::Operand(),
                                                               ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::cvt_i2f);
                ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                                                 ir::Operand(std::to_string(cnt),ir::Type::IntLiteral),
                                                                 ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::store);
                result.push_back(cvtInst);
                result.push_back(storeInst); 
            }
            else if (exp->t == Type::Float){
                ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                                                 ir::Operand(std::to_string(cnt),ir::Type::IntLiteral),
                                                                 ir::Operand(exp->v,ir::Type::Float),ir::Operator::store);
                result.push_back(storeInst);
            }
        }
        else{
            assert(0 && "Invalid analyze Type");
        }
    }
    // 判断是否是全局数组的初始化，若为全局，则ir库会帮我自动将值初始化为0
    // 局部变量初始化，注意此处为Const数组，则其必须使用{}，未指定值的元素一定会被置为0
    if (symbol_table.scope_stack.size() > 1){
        // 局部变量，未指定值置为0
        for (int i = cnt; i < array_size; i++){ // 理论上，测试代码运行该循环时，cnt一定为0
            ir::Instruction* storeInst;
            if (curr_type == ir::Type::FloatPtr)
                storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                                ir::Operand(std::to_string(i),ir::Type::IntLiteral),
                                                ir::Operand("0.0",ir::Type::FloatLiteral),ir::Operator::store);
            else if (curr_type == ir::Type::IntPtr)
                storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                ir::Operand(std::to_string(i),ir::Type::IntLiteral),
                                                ir::Operand("0",ir::Type::IntLiteral),ir::Operator::store);
            else
                assert(0 && "Invalid Type");
            result.push_back(storeInst);
        }
    }
    
    return result;
}

// FuncType -> 'void' | 'int' | 'float'
ir::Type frontend::Analyzer::analyze_functype(FuncType *root){
    Term *term = dynamic_cast<Term *>(root->children[0]);
    assert(term != nullptr);
    // 'void'
    if (term->token.type == TokenType::VOIDTK){
        return ir::Type::null;
    }
    // 'int'
    else if (term->token.type == TokenType::INTTK){
        return ir::Type::Int;
    }
    // 'float'
    else if (term->token.type == TokenType::FLOATTK){
        return ir::Type::Float;
    }
    else{
        assert(0 && "Invalid FuncType");
    }
}

// 获取词法分析中token的值
string frontend::Analyzer::analyze_ident(Term *root){
    assert(root->token.type == TokenType::IDENFR);
    return root->token.value;
}

// FuncFParam -> BType Ident ['[' ']' { '[' Exp ']' }]
ir::Operand frontend::Analyzer::analyze_funcfparam(FuncFParam *root){
    assert(root->children.size()>=2);
    // BType
    ir::Type param_type = analyze_btype(dynamic_cast<BType *>(root->children[0]));
    // Ident
    string param_name = analyze_ident(dynamic_cast<Term *>(root->children[1]));
    // 存储数组维数
    vector<int> dimension(1, -1); // [-1,]
    // 可选项 ['[' ']' { '[' Exp ']' }]：当前参数为数组指针
    if (root->children.size() > 2){
        // BType类型设为指针
        if (param_type == ir::Type::Int){
            param_type = ir::Type::IntPtr;
        }
        else if (param_type == ir::Type::Float){
            param_type = ir::Type::FloatPtr;
        }
        else{
            assert(0 && "Invalid FuncFParam");
        }
        // 判断数组的形状，一维就无{ '[' Exp ']' }，二维则有{ '[' Exp ']' }
        // 由于C++中数组指针最多只接受二维，因此此处不必再考虑更多次的{ '[' Exp ']' }
        if (root->children.size() == 4){}       // 一维数组
        // { '[' Exp ']' }
        else if (root->children.size() == 7){   // 二维数组
            // Exp
            Exp *exp = dynamic_cast<Exp *>(root->children[6]);
            vector<Instruction*> cal_insts = analyze_exp(exp);
            assert(cal_insts.size() == 0);
            if (exp->t != Type::IntLiteral)
                assert(0 && "ConstExp In Array Decl Must Be IntLiteral");
            int exp_result = std::stoi(exp->v);
            // push back to dimension
            dimension.push_back(exp_result);
        }
        else {
            assert(0 && "Invalid FuncFParam");
        }
    }

    // 构造Operand
    ir::Operand param(param_name, param_type);
    // 加入到当前作用域，为接下来函数体的分析做准备
    symbol_table.scope_stack.back().table[param_name] = {param, dimension};
    std::cout << toString(param.type) << std::endl;
    // 函数参数重命名
    ir::Operand func_param(symbol_table.get_scoped_name(param.name),param.type);
    return func_param;
}

// FuncFParams -> FuncFParam { ',' FuncFParam }
vector<ir::Operand> frontend::Analyzer::analyze_funcfparams(FuncFParams *root){
    // 存储函数参数列表
    vector<ir::Operand> func_params;
    for (int i = 0; i<root->children.size(); i+=2){
        // 只读FuncFParam
        FuncFParam *funcfparam = dynamic_cast<FuncFParam *>(root->children[i]);
        assert(funcfparam != nullptr);
        ir::Operand func_param = analyze_funcfparam(funcfparam);
        // 函数参数重命名
        func_params.push_back(func_param);
    }
    return func_params;
}

// BType -> 'int' | 'float'
ir::Type frontend::Analyzer::analyze_btype(BType *root){
    // 'int' | 'float'
    Term *term = dynamic_cast<Term *>(root->children[0]);
    assert(term != nullptr);
    // 'int'
    if (term->token.type == TokenType::INTTK){
        return ir::Type::Int;
    }
    // 'float'
    else if (term->token.type == TokenType::FLOATTK){
        return ir::Type::Float;
    }
    else{
        assert(0 && "Invalid BType");
    }
}

// FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
void frontend::Analyzer::analyze_funcdef(FuncDef *root){
    // FuncType返回值类型
    ir::Type func_type = analyze_functype(dynamic_cast<FuncType *>(root->children[0]));
    // Ident函数名
    string func_name = analyze_ident(dynamic_cast<Term *>(root->children[1]));
    // [FuncFParams]参数列表
    symbol_table.add_scope();       // 进入函数的作用域 (函数参数默认在作用域中)
    vector<ir::Operand> func_params;
    FuncFParams *funcfparams = dynamic_cast<FuncFParams *>(root->children[3]);
    if(funcfparams != nullptr){
        func_params = analyze_funcfparams(funcfparams);
    }
    // 构造Function
    ir::Function *func = new ir::Function(func_name, func_params, func_type);
    // 如果函数为main函数，则在其中增加全局函数调用
    if (func_name == "main"){
        ir::CallInst *callGlobal = new ir::CallInst(ir::Operand("global", ir::Type::null), ir::Operand("t"+std::to_string(tmp_cnt++), ir::Type::null));
        func->addInst(callGlobal);
    }
    // 加入符号表
    symbol_table.functions[func_name] = func;
    // Block函数体
    curr_function = func;
    vector<ir::Instruction *> func_body = analyze_block(dynamic_cast<Block *>(root->children.back()), true);
    // 推出函数作用域
    symbol_table.exit_scope();
    // 填充编译出的函数体
    for (auto inst : func_body){
        func->addInst(inst);
    }
    // main函数加一条return 0
    if (func_name == "main"){
        Instruction *retInst = new ir::Instruction(ir::Operand("0",ir::Type::IntLiteral), ir::Operand(), ir::Operand(),ir::Operator::_return);
        func->addInst(retInst);
    }
    // VOID函数添加return null指令
    if (func_type == ir::Type::null){
        Instruction *retInst = new ir::Instruction(ir::Operand(), ir::Operand(), ir::Operand(),ir::Operator::_return);
        func->addInst(retInst);
    }
    // Function加入到IR程序中
    ir_program.addFunction(*func);
}

// Block -> '{' { BlockItem } '}'
vector<ir::Instruction *> frontend::Analyzer::analyze_block(Block *root, bool is_func_block){
    if (!is_func_block)
        symbol_table.add_scope();

    // { BlockItem }
    vector<ir::Instruction *> block_body;
    for (int i = 1; i<int(root->children.size())-1; i++){
        BlockItem *blockitem = dynamic_cast<BlockItem *>(root->children[i]);
        assert(blockitem != nullptr);
        vector<ir::Instruction *> blockitem_body = analyze_blockitem(blockitem);
        block_body.insert(block_body.end(), blockitem_body.begin(), blockitem_body.end());
    }

    if (!is_func_block)
        symbol_table.exit_scope();
    return block_body;
}

// BlockItem -> Decl | Stmt
vector<ir::Instruction *> frontend::Analyzer::analyze_blockitem(BlockItem *root){
    // Decl
    if (dynamic_cast<Decl *>(root->children[0]) != nullptr){
        return analyze_decl(dynamic_cast<Decl *>(root->children[0]));
    }
    // Stmt
    else if (dynamic_cast<Stmt *>(root->children[0]) != nullptr){
        return analyze_stmt(dynamic_cast<Stmt *>(root->children[0]));
    }
    else{
        assert(0 && "Invalid BlockItem");
    }
}

// Stmt -> LVal '=' Exp ';' | Block | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] | 'while' '(' Cond ')' Stmt | 'break' ';' | 'continue' ';' | 'return' [Exp] ';' | [Exp] ';'
vector<ir::Instruction *> frontend::Analyzer::analyze_stmt(Stmt* root){
    vector<ir::Instruction *> result;
    // LVal '=' Exp ';'
    if (LVal* lval = dynamic_cast<LVal*>(root->children[0])){
        // Exp (赋值表达式的右值需要先解析)
        Exp* exp = dynamic_cast<Exp*>(root->children[2]);
        assert(exp != nullptr);
        vector<ir::Instruction *> cal_insts = analyze_exp(exp);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
        // 根据LVal的类型与Exp结果类型生成赋值IR指令，需要进行适当的类型转换
        // 获取变量名
        string var_name = analyze_ident(dynamic_cast<Term*>(lval->children[0]));
        STE ident_ste = symbol_table.get_ste(var_name);
        // Int or Float变量赋值
        if (lval->children.size() == 1){
            // Float/Int/FloatLiteral/IntLiteral -> Int
            if (ident_ste.operand.type == Type::Int){
                if (exp->t == Type::Int){
                    ir::Instruction* movInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Int),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Int),ir::Operator::mov);
                    result.push_back(movInst);
                }
                else if (exp->t == Type::IntLiteral){
                    ir::Instruction* movInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::IntLiteral),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Int),ir::Operator::mov);
                    result.push_back(movInst);
                }
                else if (exp->t == Type::Float){
                    ir::Instruction* f2iInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Float),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Int),ir::Operator::cvt_f2i);
                    result.push_back(f2iInst);
                }
                else if (exp->t == Type::FloatLiteral){
                    int val = std::stof(exp->v);
                    ir::Instruction* movInst = new ir::Instruction(ir::Operand(std::to_string(val),ir::Type::IntLiteral),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Int),ir::Operator::mov);
                    result.push_back(movInst);
                }
            }
            // Float/Int/FloatLiteral/IntLiteral -> Float
            else if (ident_ste.operand.type == Type::Float){                
                if (exp->t == Type::Int){
                    ir::Instruction* i2fInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Int),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Float),ir::Operator::cvt_i2f);
                    result.push_back(i2fInst);
                }
                else if (exp->t == Type::IntLiteral){
                    float val = std::stoi(exp->v);
                    ir::Instruction* movInst = new ir::Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Float),ir::Operator::fmov);
                    result.push_back(movInst);
                }
                else if (exp->t == Type::Float){
                    ir::Instruction* movInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Float),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Float),ir::Operator::fmov);
                    result.push_back(movInst);
                }
                else if (exp->t == Type::FloatLiteral){
                    ir::Instruction* movInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::FloatLiteral),
                                                                   ir::Operand(),
                                                                   ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::Float),ir::Operator::fmov);
                    result.push_back(movInst);
                }
            }
            else
                assert(0 && "Error Type");
        }
        // 一维数组赋值
        else if (lval->children.size() == 4){
            assert(ident_ste.dimension.size() == 1);
            // 计算偏移量
            Exp* offset_exp = dynamic_cast<Exp*>(lval->children[2]);
            assert(offset_exp != nullptr);
            vector<ir::Instruction *> cal_insts = analyze_exp(offset_exp);
            assert(offset_exp->t == Type::Int || offset_exp->t == Type::IntLiteral);
            result.insert(result.end(),cal_insts.begin(),cal_insts.end());
            // Int or Float变量赋值
            if (ident_ste.operand.type == Type::IntPtr){
                if (exp->t == Type::Int || exp->t == Type::IntLiteral){
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                                     ir::Operand(offset_exp->v,offset_exp->t),
                                                                     ir::Operand(exp->v,exp->t),ir::Operator::store);
                    result.push_back(storeInst);
                }
                else if (exp->t == Type::Float){
                    string tmp_float_to_int_name = "t" + std::to_string(tmp_cnt++);
                    ir::Instruction* f2iInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Float),
                                                                   ir::Operand(),
                                                                   ir::Operand(tmp_float_to_int_name,ir::Type::Int),ir::Operator::cvt_f2i);
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                                     ir::Operand(offset_exp->v,offset_exp->t),
                                                                     ir::Operand(tmp_float_to_int_name,Type::Int),ir::Operator::store);
                    result.push_back(f2iInst);
                    result.push_back(storeInst);
                }
                else if (exp->t == Type::FloatLiteral){
                    int val = std::stof(exp->v);
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                                     ir::Operand(offset_exp->v,offset_exp->t),
                                                                     ir::Operand(std::to_string(val),Type::IntLiteral),ir::Operator::store);
                    result.push_back(storeInst);
                }
            }
            else if (ident_ste.operand.type == Type::FloatPtr){
                if (exp->t == Type::Int){
                    string tmp_int_to_float_name = "t" + std::to_string(tmp_cnt++);
                    ir::Instruction* i2fInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Int),
                                                                   ir::Operand(),
                                                                   ir::Operand(tmp_int_to_float_name,ir::Type::Float),ir::Operator::cvt_i2f);
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                                                     ir::Operand(offset_exp->v,offset_exp->t),
                                                                     ir::Operand(tmp_int_to_float_name,Type::Float),ir::Operator::store);
                    result.push_back(i2fInst);
                    result.push_back(storeInst);
                }
                else if (exp->t == Type::IntLiteral){
                    float val = std::stoi(exp->v);
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                                                     ir::Operand(offset_exp->v,offset_exp->t),
                                                                     ir::Operand(std::to_string(val),Type::FloatLiteral),ir::Operator::store);
                    result.push_back(storeInst);
                }
                else if (exp->t == Type::Float || exp->t == Type::FloatLiteral){
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                                                     ir::Operand(offset_exp->v,offset_exp->t),
                                                                     ir::Operand(exp->v,exp->t),ir::Operator::store);
                    result.push_back(storeInst);
                }
            }
            else
                assert(0 && "Error Type");
        }
        // 二维数组赋值
        else if (lval->children.size() == 7){
            assert(ident_ste.dimension.size() == 2);
            // 计算偏移量
            Exp* dim1_exp = dynamic_cast<Exp*>(lval->children[2]);
            assert(dim1_exp != nullptr);
            vector<ir::Instruction *> cal1_insts = analyze_exp(dim1_exp);
            assert(dim1_exp->t == Type::Int || dim1_exp->t == Type::IntLiteral);
            result.insert(result.end(),cal1_insts.begin(),cal1_insts.end());
            Exp* dim2_exp = dynamic_cast<Exp*>(lval->children[5]);
            assert(dim2_exp != nullptr);
            vector<ir::Instruction *> cal2_insts = analyze_exp(dim2_exp);
            assert(dim2_exp->t == Type::Int || dim2_exp->t == Type::IntLiteral);
            result.insert(result.end(),cal2_insts.begin(),cal2_insts.end());
            // 为了从二维数组中取值，需计算偏移，此处可先直接将两个exp1和exp2计算的结果都放入临时变量中
            string tmp_dim1_name = "t" + std::to_string(tmp_cnt++);
            string tmp_dim2_name = "t" + std::to_string(tmp_cnt++);
            Instruction *def1Inst = new ir::Instruction(ir::Operand(dim1_exp->v, dim1_exp->t),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_dim1_name, Type::Int), ir::Operator::def);
            Instruction *def2Inst = new ir::Instruction(ir::Operand(dim2_exp->v, dim2_exp->t),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_dim2_name, Type::Int), ir::Operator::def);
            string tmp_col_len_name = "t" + std::to_string(tmp_cnt++);
            Instruction *def3Inst = new ir::Instruction(ir::Operand(std::to_string(ident_ste.dimension[1]), Type::IntLiteral),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_col_len_name, Type::Int), ir::Operator::def);
            string tmp_lineoffset_name = "t" + std::to_string(tmp_cnt++);
            // 计算行偏移
            Instruction *mulOffsetInst = new ir::Instruction(ir::Operand(tmp_dim1_name, Type::Int),
                                                             ir::Operand(tmp_col_len_name, Type::Int),
                                                             ir::Operand(tmp_lineoffset_name, Type::Int), ir::Operator::mul);
            // 计算总偏移
            string tmp_totaloffset_name = "t" + std::to_string(tmp_cnt++);
            Instruction *addOffsetInst = new ir::Instruction(ir::Operand(tmp_lineoffset_name, Type::Int),
                                                             ir::Operand(tmp_dim2_name, Type::Int),
                                                             ir::Operand(tmp_totaloffset_name, Type::Int), ir::Operator::add);
            result.push_back(def1Inst);
            result.push_back(def2Inst);
            result.push_back(def3Inst);
            result.push_back(mulOffsetInst);
            result.push_back(addOffsetInst);
            // Int or Float变量赋值
            if (ident_ste.operand.type == Type::IntPtr){
                if (exp->t == Type::Int || exp->t == Type::IntLiteral){
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                                     ir::Operand(tmp_totaloffset_name,Type::Int),
                                                                     ir::Operand(exp->v,exp->t),ir::Operator::store);
                    result.push_back(storeInst);
                }
                else if (exp->t == Type::Float){
                    string tmp_float_to_int_name = "t" + std::to_string(tmp_cnt++);
                    ir::Instruction* f2iInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Float),
                                                                   ir::Operand(),
                                                                   ir::Operand(tmp_float_to_int_name,ir::Type::Int),ir::Operator::cvt_f2i);
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                                     ir::Operand(tmp_totaloffset_name,Type::Int),
                                                                     ir::Operand(tmp_float_to_int_name,Type::Int),ir::Operator::store);
                    result.push_back(f2iInst);
                    result.push_back(storeInst);
                }
                else if (exp->t == Type::FloatLiteral){
                    int val = std::stof(exp->v);
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::IntPtr),
                                                                     ir::Operand(tmp_totaloffset_name,Type::Int),
                                                                     ir::Operand(std::to_string(val),Type::IntLiteral),ir::Operator::store);
                    result.push_back(storeInst);
                }
            }
            else if (ident_ste.operand.type == Type::FloatPtr){
                if (exp->t == Type::Int){
                    string tmp_int_to_float_name = "t";
                    tmp_int_to_float_name += std::to_string(tmp_cnt++);
                    ir::Instruction* i2fInst = new ir::Instruction(ir::Operand(exp->v,ir::Type::Int),
                                        ir::Operand(),
                                        ir::Operand(tmp_int_to_float_name,ir::Type::Float),ir::Operator::cvt_i2f);
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                        ir::Operand(tmp_totaloffset_name,Type::Int),
                                        ir::Operand(tmp_int_to_float_name,Type::Float),ir::Operator::store);
                    result.push_back(i2fInst);
                    result.push_back(storeInst);
                }
                else if (exp->t == Type::IntLiteral){
                    float val = std::stoi(exp->v);
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                        ir::Operand(tmp_totaloffset_name,Type::Int),
                                        ir::Operand(std::to_string(val),Type::FloatLiteral),ir::Operator::store);
                    result.push_back(storeInst);
                }
                else if (exp->t == Type::Float || exp->t == Type::FloatLiteral){
                    ir::Instruction* storeInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),ir::Type::FloatPtr),
                                        ir::Operand(tmp_totaloffset_name,Type::Int),
                                        ir::Operand(exp->v,exp->t),ir::Operator::store);
                    result.push_back(storeInst);
                }
            }
            else
                assert(0 && "Error Type");
        }
        return result;
    }
    // Block分支
    if (Block* block = dynamic_cast<Block*>(root->children[0])){
        return analyze_block(block,false);
    }

    Term* term = dynamic_cast<Term*>(root->children[0]);
    // [Exp] ';'
    if (term == nullptr){       // 除了前两种情况，只有Exp ';'开头不是终结符
        Exp* exp = dynamic_cast<Exp*>(root->children[0]);
        assert(exp != nullptr);
        return analyze_exp(exp);
    }
    // ';' (即[Exp] ';'中不取Exp)
    if (term->token.type == TokenType::SEMICN){
        return result;
    }
    // 'return' [Exp] ';'
    if (term->token.type == TokenType::RETURNTK){
        // Exp ';'
        if (root->children.size() == 3){
            // Exp
            Exp* exp = dynamic_cast<Exp*>(root->children[1]);
            assert(exp != nullptr);
            vector<ir::Instruction*> exp_insts = analyze_exp(exp);
            result.insert(result.end(),exp_insts.begin(),exp_insts.end());
            // 根据函数返回类型进行返回
            if (curr_function->returnType == Type::Int){
                // Int or IntLiteral
                if (exp->t == Type::Int || exp->t == Type::IntLiteral){
                    ir::Instruction* retInst = new ir::Instruction(ir::Operand(exp->v,exp->t),
                                                                   ir::Operand(),
                                                                   ir::Operand(),ir::Operator::_return);
                    result.push_back(retInst);
                }
                // Float or FloatLiteral
                else if (exp->t == Type::FloatLiteral){
                    int val = std::stof(exp->v);
                    ir::Instruction* retInst = new ir::Instruction(ir::Operand(std::to_string(val),Type::IntLiteral),
                                                                   ir::Operand(),
                                                                   ir::Operand(),ir::Operator::_return);
                    result.push_back(retInst);
                }
                else if (exp->t == Type::Float){
                    string tmp_float_to_int_name = "t" + std::to_string(tmp_cnt++);
                    ir::Instruction* cvtInst = new ir::Instruction(ir::Operand(exp->v,Type::Float),
                                                                   ir::Operand(),
                                                                   ir::Operand(tmp_float_to_int_name,Type::Int),ir::Operator::cvt_f2i);
                    ir::Instruction* retInst = new ir::Instruction(ir::Operand(tmp_float_to_int_name,Type::Int),
                                                                   ir::Operand(),
                                                                   ir::Operand(),ir::Operator::_return);
                    result.push_back(cvtInst);
                    result.push_back(retInst);
                }
                else
                    assert(0 && "Error Type");
            }
            else if (curr_function->returnType == Type::Float){
                // Float or FloatLiteral
                if (exp->t == Type::Float || exp->t == Type::FloatLiteral){
                    ir::Instruction* retInst = new ir::Instruction(ir::Operand(exp->v,exp->t),
                                                                   ir::Operand(),
                                                                   ir::Operand(),ir::Operator::_return);
                    result.push_back(retInst);
                }
                // Int or IntLiteral
                else if (exp->t == Type::IntLiteral){
                    float val = std::stoi(exp->v);
                    ir::Instruction* retInst = new ir::Instruction(ir::Operand(std::to_string(val),Type::FloatLiteral),
                                                                   ir::Operand(),
                                                                   ir::Operand(),ir::Operator::_return);
                    result.push_back(retInst);
                }
                else if (exp->t == Type::Int){
                    string tmp_int_to_float_name = "t" + std::to_string(tmp_cnt++);
                    ir::Instruction* cvtInst = new ir::Instruction(ir::Operand(exp->v,Type::Int),
                                                                   ir::Operand(),
                                                                   ir::Operand(tmp_int_to_float_name,Type::Float),ir::Operator::cvt_i2f);
                    ir::Instruction* retInst = new ir::Instruction(ir::Operand(tmp_int_to_float_name,Type::Float),
                                                                   ir::Operand(),
                                                                   ir::Operand(),ir::Operator::_return);
                    result.push_back(cvtInst);
                    result.push_back(retInst);
                }
                else
                    assert(0 && "Error Type");
            }
            else
                assert(0 && "Invalid Return Type");
        }
        // ;
        else{
            ir::Instruction* retInst = new ir::Instruction(ir::Operand(),
                                                           ir::Operand(),
                                                           ir::Operand(),ir::Operator::_return);
            result.push_back(retInst);
        }
        return result;
    }
    // 'if' '(' Cond ')' Stmt [ 'else' Stmt ]
    if (term->token.type == TokenType::IFTK){
        // Cond
        Cond* cond = dynamic_cast<Cond*>(root->children[2]);
        assert(cond != nullptr);
        vector<ir::Instruction*> cal_insts = analyze_cond(cond);
        // 若Cond为Float或FloatLiteral则需转换为Int或IntLiteral
        if (cond->t == Type::Float || cond->t == Type::FloatLiteral){
            if (cond->t == Type::FloatLiteral){
                float val = std::stof(cond->v);
                cond->v = std::to_string(val != 0);
                cond->t = Type::IntLiteral;
            }
            else{
                string tmp1_name = "t" + std::to_string(tmp_cnt++);
                ir::Instruction* cvt1Inst = new ir::Instruction(ir::Operand(cond->v,Type::Float),
                                                                ir::Operand("0.0",Type::FloatLiteral),
                                                                ir::Operand(tmp1_name,Type::Float),ir::Operator::fneq);
                string tmp2_name = "t" + std::to_string(tmp_cnt++);
                ir::Instruction* cvt2Inst = new ir::Instruction(ir::Operand(tmp1_name,Type::Float),
                                                                ir::Operand(),
                                                                ir::Operand(tmp2_name,Type::Int),ir::Operator::cvt_f2i);
                cal_insts.push_back(cvt1Inst);
                cal_insts.push_back(cvt2Inst);
                cond->v = tmp2_name;
                cond->t = Type::Int;
            }
        }
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
        // 生成跳转指令

        // if情况的跳转
        ir::Instruction* goto_if_Inst = new ir::Instruction(ir::Operand(cond->v,cond->t),
                                                            ir::Operand(),
                                                            ir::Operand("2",Type::IntLiteral),ir::Operator::_goto);
        result.push_back(goto_if_Inst);

        symbol_table.add_scope();
        // 先分析if后的stmt
        vector<ir::Instruction *> stmt_after_if_insts = analyze_stmt(dynamic_cast<Stmt*>(root->children[4]));
        symbol_table.exit_scope();

        // 判断有没有else
        if (root->children.size() == 7){   // 有else
            symbol_table.add_scope();
            // 先分析else后的stmt
            vector<ir::Instruction *> stmt_after_else_insts = analyze_stmt(dynamic_cast<Stmt*>(root->children[6]));
            symbol_table.exit_scope();

            // if情况执行完毕的跳转(跳过整个else)
            ir::Instruction* goto_if_last_Inst = new ir::Instruction(ir::Operand(),
                                                                     ir::Operand(),
                                                                     ir::Operand(std::to_string(stmt_after_else_insts.size()+1),Type::IntLiteral),ir::Operator::_goto);
            stmt_after_if_insts.push_back(goto_if_last_Inst);

            // else情况的跳转(跳转到else后的Stmt)
            ir::Instruction* goto_else_Inst = new ir::Instruction(ir::Operand(),
                                                                     ir::Operand(),
                                                                     ir::Operand(std::to_string(stmt_after_if_insts.size()+1),Type::IntLiteral),ir::Operator::_goto);
            result.push_back(goto_else_Inst);
            // 合并if后Stmt
            result.insert(result.end(),stmt_after_if_insts.begin(),stmt_after_if_insts.end());
            // 合并else后Stmt
            result.insert(result.end(),stmt_after_else_insts.begin(),stmt_after_else_insts.end());
            // 增加unuse
            Instruction* unuse_Inst = new ir::Instruction(ir::Operand(),
                                                          ir::Operand(),
                                                          ir::Operand(),ir::Operator::__unuse__);
            result.push_back(unuse_Inst);
        }
        else{       // 没有else
            // 非if情况的跳转
            ir::Instruction* goto_else_Inst = new ir::Instruction(ir::Operand(),
                                                                  ir::Operand(),
                                                                  ir::Operand(std::to_string(stmt_after_if_insts.size()+1),Type::IntLiteral),ir::Operator::_goto);
            result.push_back(goto_else_Inst);
            // 合并if后的stmt
            result.insert(result.end(),stmt_after_if_insts.begin(),stmt_after_if_insts.end());
            // 增加unuse
            Instruction* unuse_Inst = new ir::Instruction(ir::Operand(),
                                                          ir::Operand(),
                                                          ir::Operand(),ir::Operator::__unuse__);
            result.push_back(unuse_Inst);
        }
        return result;
    }
    // 'while' '(' Cond ')' Stmt
    if (term->token.type == TokenType::WHILETK){
        // Cond
        Cond* cond = dynamic_cast<Cond*>(root->children[2]);
        assert(cond != nullptr);
        vector<Instruction *> cal_insts = analyze_cond(cond);
        // 若Cond为Float或FloatLiteral则需转换为Int或IntLiteral
        if (cond->t == Type::Float || cond->t == Type::FloatLiteral){
            if (cond->t == Type::FloatLiteral){
                float val = std::stof(cond->v);
                cond->v = std::to_string(val != 0);
                cond->t = Type::IntLiteral;
            }
            else{
                string tmp1_name = "t" + std::to_string(tmp_cnt++);
                ir::Instruction* cvt1Inst = new ir::Instruction(ir::Operand(cond->v,Type::Float),
                                                                ir::Operand("0.0",Type::FloatLiteral),
                                                                ir::Operand(tmp1_name,Type::Float),ir::Operator::fneq);
                string tmp2_name = "t" + std::to_string(tmp_cnt++);
                ir::Instruction* cvt2Inst = new ir::Instruction(ir::Operand(tmp1_name,Type::Float),
                                                                ir::Operand(),
                                                                ir::Operand(tmp2_name,Type::Int),ir::Operator::cvt_f2i);
                cal_insts.push_back(cvt1Inst);
                cal_insts.push_back(cvt2Inst);
                cond->v = tmp2_name;
                cond->t = Type::Int;
            }
        }
        symbol_table.add_scope();
        // 分析Stmt的指令，便于给出While跳转指令(PC值)
        vector<Instruction *> stmt_insts = analyze_stmt(dynamic_cast<Stmt*>(root->children[4]));
        symbol_table.exit_scope();
        // 满足条件，则进入While体内
        Instruction* goto_while_Inst = new ir::Instruction(ir::Operand(cond->v,cond->t),
                                                           ir::Operand(),
                                                           ir::Operand("2",Type::IntLiteral),ir::Operator::_goto);
        // 每轮WHILE结束都要返回到开头
        Instruction* goto_return_begin_mark = new ir::Instruction(ir::Operand("continue",Type::null), // 为了实现简单, 直接添加一个标记指令
                                                                  ir::Operand(),
                                                                  ir::Operand(),ir::Operator::__unuse__);
        stmt_insts.push_back(goto_return_begin_mark);
        // 不满足条件, 则跳出While
        Instruction* goto_exit_while_Inst = new ir::Instruction(ir::Operand(),
                                                                ir::Operand(),
                                                                ir::Operand(std::to_string(stmt_insts.size()+1),Type::IntLiteral),ir::Operator::_goto);
        for (int i = 0; i < stmt_insts.size(); i++){    // 遍历WHILE体中的BREAK与CONTINUE标记指令, 修改为_goto
            if (stmt_insts[i]->op == Operator::__unuse__ && stmt_insts[i]->op1.type == Type::null){
                if (stmt_insts[i]->op1.name == "break"){
                    Instruction *replace_break_inst = new ir::Instruction(ir::Operand(),
                                                                          ir::Operand(),
                                                                          ir::Operand(std::to_string(int(stmt_insts.size())-i),Type::IntLiteral),ir::Operator::_goto);
                    stmt_insts[i] = replace_break_inst;
                }
                else if (stmt_insts[i]->op1.name == "continue"){
                    Instruction *replace_continue_inst = new ir::Instruction(ir::Operand(),
                                                                             ir::Operand(),
                                                                             ir::Operand(std::to_string(-(2+i+int(cal_insts.size()))),Type::IntLiteral),ir::Operator::_goto);
                    stmt_insts[i] = replace_continue_inst;
                }
            }
        }
        // 合并所有指令到result
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
        result.push_back(goto_while_Inst);
        result.push_back(goto_exit_while_Inst);
        result.insert(result.end(),stmt_insts.begin(),stmt_insts.end());
        // Unuse
        Instruction * unuse_Inst = new ir::Instruction(ir::Operand(),
                                                       ir::Operand(),
                                                       ir::Operand(),ir::Operator::__unuse__);
        result.push_back(unuse_Inst);
        return result;
    }
    // 'break' ';'
    if (term->token.type == TokenType::BREAKTK){
        Instruction *mark_break_inst = new Instruction(Operand("break",Type::null), 
                                                       Operand(), 
                                                       Operand(), 
                                                       Operator::__unuse__);
        result.push_back(mark_break_inst); // 添加标记指令, 在WHILE中解析完全部STMT指令后, 遍历指令寻找标记指令, 并替换为goto指令
        return result;
    }
    // 'continue' ';'
    if (term->token.type == TokenType::CONTINUETK){
        Instruction *mark_continue_inst = new Instruction(Operand("continue",Type::null), 
                                                          Operand(), 
                                                          Operand(), 
                                                          Operator::__unuse__);
        result.push_back(mark_continue_inst); // 添加标记指令, 在WHILE中解析完全部STMT指令后, 遍历指令寻找标记指令, 并替换为goto指令
        return result;
    }
}


// ---------- 辅助函数，计算表达式的值 ----------

// Exp -> AddExp
vector<ir::Instruction *> frontend::Analyzer::analyze_exp(Exp* root){
    // AddExp
    AddExp *addexp = dynamic_cast<AddExp *>(root->children[0]);
    assert(addexp != nullptr);
    vector<ir::Instruction *> cal_insts = analyze_addexp(addexp);
    root->v = addexp->v;
    root->t = addexp->t;
    return cal_insts;
}

// ConstExp -> AddExp
vector<ir::Instruction *> frontend::Analyzer::analyze_constexp(ConstExp *root){
    // AddExp
    AddExp *addexp = dynamic_cast<AddExp *>(root->children[0]);
    assert(addexp != nullptr);
    vector<ir::Instruction *> cal_insts = analyze_addexp(addexp);
    assert(cal_insts.size() == 0);
    root->v = addexp->v;        // 整数字面量或浮点数字面量
    root->t = addexp->t;
    return cal_insts;
}

// AddExp -> MulExp { ('+' | '-') MulExp }
vector<ir::Instruction *> frontend::Analyzer::analyze_addexp(AddExp *root){
    vector<Instruction *> result;
    // 根据所有MulExp确定当前AddExp的类型 (类型提升: 整数 + - 浮点 -> 浮点) 只要有浮点数出现, 就会让当前表达式的结果类型提升为浮点, 变量 + - 常量 -> 变量，只要有变量， 就会类型提升为常量

    // 默认类型为整数,常量
    Type target_type = Type::IntLiteral;

    // 深度优先遍历，先计算其所有子MulExp
    for (int i = 0; i < root->children.size(); i += 2){
        MulExp *mulexp = dynamic_cast<MulExp *>(root->children[i]);
        assert(mulexp != nullptr);
        vector<Instruction *> cal_insts = analyze_mulexp(mulexp);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());

        // 确定类型提升
        if (mulexp->t == ir::Type::Float)
            target_type = ir::Type::Float;
        else if (mulexp->t == ir::Type::Int && target_type == ir::Type::IntLiteral)
            target_type = ir::Type::Int;
        else if (mulexp->t == ir::Type::FloatLiteral && target_type == ir::Type::IntLiteral)
            target_type = ir::Type::FloatLiteral;
        else if ((mulexp->t == ir::Type::FloatLiteral && target_type == ir::Type::Int) || (target_type == ir::Type::FloatLiteral && mulexp->t == ir::Type::Int)) // 提升没有顺序
            target_type = ir::Type::Float;
    }

    // 计算表达式的结果
    // 默认为第一个MulExp的值
    MulExp* firstMulExp = dynamic_cast<MulExp*>(root->children[0]);
    assert(firstMulExp != nullptr);
    root->t = firstMulExp->t;
    root->v = firstMulExp->v;

    if (root->children.size() == 1)
        return result; // 结果只有一个时，无视类型提升
    
    // 将第一个MulExp的值进行类型转换
    if (target_type != root->t){
        // IntLiteral -> Int
        if (target_type == Type::Int){
            assert(root->t == Type::IntLiteral);
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(root->v,ir::Type::IntLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Int),ir::Operator::def);
            result.push_back(cvtInst);
            root->v = tmp_intcvt_name;
            root->t = Type::Int;
        }
        // IntLiteral -> FloatLiteral
        else if (target_type == Type::FloatLiteral){
            assert(root->t == Type::IntLiteral);
            float val = std::stoi(root->v);
            root->v = std::to_string(val);
            root->t = Type::FloatLiteral;
        }
        // IntLiteral -> Float, Int -> Float, FloatLiteral -> Float
        else if (target_type == Type::Float){
            if (root->t == Type::IntLiteral){
                float val = std::stof(root->v);
                string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                Instruction * cvtInst = new Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
                result.push_back(cvtInst);
                root->v = tmp_intcvt_name;
                root->t = Type::Float;
            }
            else if (root->t == Type::Int){
                string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                Instruction * cvtInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::cvt_i2f);
                result.push_back(cvtInst);
                root->v = tmp_intcvt_name;
                root->t = Type::Float; 
            }
            else if (root->t == Type::FloatLiteral){
                string tmp_floatcvt_name = "t" + std::to_string(tmp_cnt++);
                Instruction * cvtInst = new Instruction(ir::Operand(root->v,ir::Type::FloatLiteral),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_floatcvt_name,ir::Type::Float),ir::Operator::fdef);
                result.push_back(cvtInst);
                root->v = tmp_floatcvt_name;
                root->t = Type::Float;
            }
            else
                assert(0 && "Error");
        }
        else
            assert(0 && "Error");
    }

    // 开始对2,4,6等进行计算
    for (int i=2; i<root->children.size(); i+=2){
        // 注意，此时root->t已为正确的类型
        MulExp *mulexp = dynamic_cast<MulExp *>(root->children[i]);

        // 符号
        Term* op_term  = dynamic_cast<Term*>(root->children[i-1]);

        // 在计算之前，先将两个操作数的类型变为相同的
        if (target_type != mulexp->t){      // 复用
            if (target_type == Type::Int){
                assert(mulexp->t == Type::IntLiteral);
                string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                Instruction * cvtInst = new Instruction(ir::Operand(mulexp->v,ir::Type::IntLiteral),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_intcvt_name,ir::Type::Int),ir::Operator::def);
                result.push_back(cvtInst);
                mulexp->v = tmp_intcvt_name;
                mulexp->t = Type::Int;
            }
            else if (target_type == Type::FloatLiteral){
                assert(mulexp->t == Type::IntLiteral);
                float val = std::stoi(mulexp->v);
                mulexp->v = std::to_string(val);
                mulexp->t = Type::FloatLiteral;
            }
            else if (target_type == Type::Float){
                if (mulexp->t == Type::IntLiteral){
                    float val = std::stof(mulexp->v);
                    string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                    Instruction * cvtInst = new Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                            ir::Operand(),
                                                            ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
                    result.push_back(cvtInst);
                    mulexp->v = tmp_intcvt_name;
                    mulexp->t = Type::Float;
                }
                else if (mulexp->t == Type::Int){
                    string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                    Instruction * cvtInst = new Instruction(ir::Operand(mulexp->v,ir::Type::Int),
                                                            ir::Operand(),
                                                            ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::cvt_i2f);
                    result.push_back(cvtInst);
                    mulexp->v = tmp_intcvt_name;
                    mulexp->t = Type::Float; 
                }
                else if (mulexp->t == Type::FloatLiteral){
                    string tmp_floatcvt_name = "t" + std::to_string(tmp_cnt++);
                    Instruction * cvtInst = new Instruction(ir::Operand(mulexp->v,ir::Type::FloatLiteral),
                                                            ir::Operand(),
                                                            ir::Operand(tmp_floatcvt_name,ir::Type::Float),ir::Operator::fdef);
                    result.push_back(cvtInst);
                    mulexp->v = tmp_floatcvt_name;
                    mulexp->t = Type::Float;
                }
                else
                    assert(0 && "Error");
            }
            else
                assert(0 && "Error");
        }
    
        // 已经化为相同类型，开始计算
        if (target_type == Type::IntLiteral){
            int val1 = std::stoi(root->v);
            int val2 = std::stoi(mulexp->v);
            if (op_term->token.type == TokenType::PLUS)
                root->v = std::to_string(val1+val2);
            else if (op_term->token.type == TokenType::MINU)
                root->v = std::to_string(val1-val2);
            else
                assert(0 && "Invalid Op");
        }
        else if (target_type == Type::FloatLiteral){
            float val1 = std::stof(root->v);
            float val2 = std::stof(mulexp->v);
            if (op_term->token.type == TokenType::PLUS)
                root->v = std::to_string(val1+val2);
            else if (op_term->token.type == TokenType::MINU)
                root->v = std::to_string(val1-val2);
            else
                assert(0 && "Invalid Op");
        }
        else if (target_type == Type::Int){
            string tmp_cal_name = "t" + std::to_string(tmp_cnt++);
            Instruction * calInst;
            if (op_term->token.type == TokenType::PLUS)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(mulexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::add);
            else if (op_term->token.type == TokenType::MINU)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(mulexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::sub);
            else
                assert(0 && "Invalid Op");
            result.push_back(calInst);
            root->v = tmp_cal_name;
        }
        else if (target_type == Type::Float){
            string tmp_cal_name = "t" + std::to_string(tmp_cnt++);
            Instruction * calInst;
            if (op_term->token.type == TokenType::PLUS)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Float),
                                          ir::Operand(mulexp->v,ir::Type::Float),
                                          ir::Operand(tmp_cal_name,ir::Type::Float),ir::Operator::fadd);
            else if (op_term->token.type == TokenType::MINU)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Float),
                                          ir::Operand(mulexp->v,ir::Type::Float),
                                          ir::Operand(tmp_cal_name,ir::Type::Float),ir::Operator::fsub);
            else
                assert(0 && "Invalid Op");
            result.push_back(calInst);
            root->v = tmp_cal_name;
        }
        else
            assert(0 && "Error");
    }
    return result;

}

// MulExp -> UnaryExp { ('*' | '/' | '%') UnaryExp }
vector<ir::Instruction *> frontend::Analyzer::analyze_mulexp(MulExp *root){
    vector<Instruction *> result;
    // 根据所有UnaryExp确定当前MulExp的类型 (类型提升: 整数 * / 浮点 -> 浮点) 只要有浮点数出现, 就会让当前表达式的结果类型提升为浮点, 变量 * / % 常量 -> 变量，只要有变量， 就会类型提升为常量

    // 默认类型为整数常量
    Type target_type = Type::IntLiteral;

    // 深度优先遍历，先计算其所有子UnaryExp
    for (int i=0; i<root->children.size(); i+=2){
        UnaryExp *unaryexp = dynamic_cast<UnaryExp *>(root->children[i]);
        assert(unaryexp != nullptr);
        vector<Instruction *> cal_insts = analyze_unaryexp(unaryexp);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());

        // 确定类型提升
        if (unaryexp->t == ir::Type::Float)
            target_type = ir::Type::Float;
        else if (unaryexp->t == ir::Type::Int && target_type == ir::Type::IntLiteral)
            target_type = ir::Type::Int;
        else if (unaryexp->t == ir::Type::FloatLiteral && target_type == ir::Type::IntLiteral)
            target_type = ir::Type::FloatLiteral;
        else if ((unaryexp->t == ir::Type::FloatLiteral && target_type == ir::Type::Int) || (target_type == ir::Type::FloatLiteral && unaryexp->t == ir::Type::Int)) // 提升没有顺序
            target_type = ir::Type::Float;
    }

    // 计算表达式的结果
    // 默认为第一个UnaryExp的值
    UnaryExp* firstUnaryExp = dynamic_cast<UnaryExp*>(root->children[0]);
    assert(firstUnaryExp != nullptr);
    root->t = firstUnaryExp->t;
    root->v = firstUnaryExp->v;

    // 结果只有一个时，无视类型提升
    if (root->children.size() == 1)
        return result; 

    // 否则，进行进行计算
    if (target_type != root->t){
        if (target_type == Type::Int){
            assert(root->t == Type::IntLiteral);
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(root->v,ir::Type::IntLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Int),ir::Operator::def);
            result.push_back(cvtInst);
            root->v = tmp_intcvt_name;
            root->t = Type::Int;
        }
        else if (target_type == Type::FloatLiteral){
            assert(root->t == Type::IntLiteral);
            float val = std::stoi(root->v);
            root->v = std::to_string(val);
            root->t = Type::FloatLiteral;
        }
        else if (target_type == Type::Float){
            if (root->t == Type::IntLiteral){
                float val = std::stof(root->v);
                string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                Instruction * cvtInst = new Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
                result.push_back(cvtInst);
                root->v = tmp_intcvt_name;
                root->t = Type::Float;
            }
            else if (root->t == Type::Int){
                string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                Instruction * cvtInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::cvt_i2f);
                result.push_back(cvtInst);
                root->v = tmp_intcvt_name;
                root->t = Type::Float; 
            }
            else if (root->t == Type::FloatLiteral){
                string tmp_floatcvt_name = "t" + std::to_string(tmp_cnt++);
                Instruction * cvtInst = new Instruction(ir::Operand(root->v,ir::Type::FloatLiteral),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_floatcvt_name,ir::Type::Float),ir::Operator::fdef);
                result.push_back(cvtInst);
                root->v = tmp_floatcvt_name;
                root->t = Type::Float;
            }
            else
                assert(0 && "Error");
        }
        else
            assert(0 && "Error");
    }

    // 开始对2,4,6等进行计算
    for (int i=2; i<root->children.size(); i+=2){
        // 注意，此时root->t已为正确的类型
        UnaryExp *unaryexp = dynamic_cast<UnaryExp *>(root->children[i]);

        // 符号
        Term* op_term  = dynamic_cast<Term*>(root->children[i-1]);

        // 在计算之前，先将两个操作数的类型变为相同的
        if (target_type != unaryexp->t){
            if (target_type == Type::Int){
                assert(unaryexp->t == Type::IntLiteral);
                string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                Instruction * cvtInst = new Instruction(ir::Operand(unaryexp->v,ir::Type::IntLiteral),
                                                        ir::Operand(),
                                                        ir::Operand(tmp_intcvt_name,ir::Type::Int),ir::Operator::def);
                result.push_back(cvtInst);
                unaryexp->v = tmp_intcvt_name;
                unaryexp->t = Type::Int;
            }
            else if (target_type == Type::FloatLiteral){
                assert(unaryexp->t == Type::IntLiteral);
                float val = std::stoi(unaryexp->v);
                unaryexp->v = std::to_string(val);
                unaryexp->t = Type::FloatLiteral;
            }
            else if (target_type == Type::Float){
                if (unaryexp->t == Type::IntLiteral){
                    float val = std::stof(unaryexp->v);
                    string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                    Instruction * cvtInst = new Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                            ir::Operand(),
                                                            ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
                    result.push_back(cvtInst);
                    unaryexp->v = tmp_intcvt_name;
                    unaryexp->t = Type::Float;
                }
                else if (unaryexp->t == Type::Int){
                    string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
                    Instruction * cvtInst = new Instruction(ir::Operand(unaryexp->v,ir::Type::Int),
                                                            ir::Operand(),
                                                            ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::cvt_i2f);
                    result.push_back(cvtInst);
                    unaryexp->v = tmp_intcvt_name;
                    unaryexp->t = Type::Float; 
                }
                else if (unaryexp->t == Type::FloatLiteral){
                    string tmp_floatcvt_name = "t" + std::to_string(tmp_cnt++);
                    Instruction * cvtInst = new Instruction(ir::Operand(unaryexp->v,ir::Type::FloatLiteral),
                                                            ir::Operand(),
                                                            ir::Operand(tmp_floatcvt_name,ir::Type::Float),ir::Operator::fdef);
                    result.push_back(cvtInst);
                    unaryexp->v = tmp_floatcvt_name;
                    unaryexp->t = Type::Float;
                }
                else
                    assert(0 && "Error");
            }
            else
                assert(0 && "Error");
        }
        // 已经化为相同类型
        // 开始计算
        if (target_type == Type::IntLiteral){
            int val1 = std::stoi(root->v);
            int val2 = std::stoi(unaryexp->v);
            if (op_term->token.type == TokenType::MULT)
                root->v = std::to_string(val1*val2);
            else if (op_term->token.type == TokenType::DIV)
                root->v = std::to_string(val1/val2);
            else if (op_term->token.type == TokenType::MOD)
                root->v = std::to_string(val1%val2);
            else
                assert(0 && "Invalid Op");
        }
        else if (target_type == Type::FloatLiteral){
            float val1 = std::stof(root->v);
            float val2 = std::stof(unaryexp->v);
            if (op_term->token.type == TokenType::MULT)
                root->v = std::to_string(val1*val2);
            else if (op_term->token.type == TokenType::DIV)
                root->v = std::to_string(val1/val2);
            else
                assert(0 && "Invalid Op");
        }
        else if (target_type == Type::Int){
            string tmp_cal_name = "t";
            tmp_cal_name += std::to_string(tmp_cnt++);
            Instruction * calInst;
            if (op_term->token.type == TokenType::MULT)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(unaryexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::mul);
            else if (op_term->token.type == TokenType::DIV)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(unaryexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::div);
            else if (op_term->token.type == TokenType::MOD)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(unaryexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::mod);
            else
                assert(0 && "Invalid Op");
            result.push_back(calInst);
            root->v = tmp_cal_name;
        }
        else if (target_type == Type::Float){
            string tmp_cal_name = "t" + std::to_string(tmp_cnt++);
            Instruction * calInst;
            if (op_term->token.type == TokenType::MULT)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Float),
                                          ir::Operand(unaryexp->v,ir::Type::Float),
                                          ir::Operand(tmp_cal_name,ir::Type::Float),ir::Operator::fmul);
            else if (op_term->token.type == TokenType::DIV)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Float),
                                          ir::Operand(unaryexp->v,ir::Type::Float),
                                          ir::Operand(tmp_cal_name,ir::Type::Float),ir::Operator::fdiv);
            else
                assert(0 && "Invalid Op");
            result.push_back(calInst);
            root->v = tmp_cal_name;
        }
        else
            assert(0 && "Error");
    }
    return result;
}

// UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
vector<ir::Instruction *> frontend::Analyzer::analyze_unaryexp(UnaryExp *root){
    vector<ir::Instruction *> result;
    // PrimaryExp分支
    PrimaryExp *primaryexp = dynamic_cast<PrimaryExp *>(root->children[0]);
    if (primaryexp != nullptr){
        // PrimaryExp
        vector<Instruction *> cal_insts = analyze_primaryexp(primaryexp);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
        root->v = primaryexp->v;
        root->t = primaryexp->t;
        return result;
    }

    // Ident '(' [FuncRParams] ')'分支
    Term *term = dynamic_cast<Term *>(root->children[0]);
    if (term != nullptr && term->token.type == TokenType::IDENFR){
        string func_name = term->token.value;
        Function* call_func = symbol_table.functions[func_name];
        vector<Operand> paraVec;
        // [FuncRParams]
        FuncRParams *funcrparams = dynamic_cast<FuncRParams *>(root->children[2]);
        if (funcrparams != nullptr){
            // 获取函数的参数列表
            vector<Operand> func_para_type = call_func->ParameterList;
            vector<ir::Instruction *> tmp_result = analyze_funcrparams(funcrparams, func_para_type, paraVec);
            result.insert(result.end(), tmp_result.begin(), tmp_result.end());
        }
        // 函数名
        string func_result_name = "t" + std::to_string(tmp_cnt++);
        // 函数调用指令
        ir::CallInst* callInst = new ir::CallInst(ir::Operand(call_func->name,call_func->returnType), paraVec, ir::Operand(func_result_name,call_func->returnType));
        result.push_back(callInst);
        // 结果写入root
        root->v = func_result_name;
        root->t = call_func->returnType;
        return result;
    }

    // UnaryOp UnaryExp分支
    UnaryOp *unaryop = dynamic_cast<UnaryOp *>(root->children[0]);
    if (unaryop != nullptr){
        // UnaryExp（先计算UnaryExp，再根据UnaryOp类型计算UnaryOp UnaryExp）
        UnaryExp *unaryexp = dynamic_cast<UnaryExp *>(root->children[1]);
        assert(unaryexp != nullptr);
        vector<ir::Instruction *> cal_insts = analyze_unaryexp(unaryexp);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
        // 根据UnaryOp的类型和UnaryExp的值进行计算
        Term *unaryop_term = dynamic_cast<Term *>(unaryop->children[0]);
        if (unaryop_term->token.type == TokenType::PLUS){
            root->v = unaryexp->v;
            root->t = unaryexp->t;
        }
        else if (unaryop_term->token.type == TokenType::MINU){
            if (unaryexp->t == Type::IntLiteral || unaryexp->t == Type::FloatLiteral){  // 字面量
                root->v = std::to_string(-std::stof(unaryexp->v));
                root->t = unaryexp->t;
            }
            else if (unaryexp->t == Type::Int || unaryexp->t == Type::Float) {  // 常量
                // 使用sub/fsub取反

                // 0临时变量
                string tmp_zero_name = "t" + std::to_string(tmp_cnt++);
                string operand_name = (unaryexp->t == Type::Int) ? "0" : "0.0";
                ir::Type operand_type = (unaryexp->t == Type::Int) ? (ir::Type::IntLiteral) : (ir::Type::FloatLiteral);
                ir::Operator operator_defname = (unaryexp->t == Type::Int) ? (ir::Operator::def) : (ir::Operator::fdef);    // 宏定义
                ir::Operator operator_name = (unaryexp->t == Type::Int) ? (ir::Operator::sub) : (ir::Operator::fsub);
                ir::Instruction* defInst = new ir::Instruction(ir::Operand(operand_name, operand_type), 
                                                               ir::Operand(), 
                                                               ir::Operand(tmp_zero_name, unaryexp->t), operator_defname);
                // 结果临时变量
                string tmp_minu_name = "t" + std::to_string(tmp_cnt++);
                ir::Instruction* minuInst = new ir::Instruction(ir::Operand(tmp_zero_name,unaryexp->t),
                                                               ir::Operand(unaryexp->v,unaryexp->t),
                                                               ir::Operand(tmp_minu_name,unaryexp->t), operator_name);
                result.push_back(defInst);
                result.push_back(minuInst);
                root->v = tmp_minu_name;
                root->t = unaryexp->t;
            }
            else
                assert(0 && "Error");
        }
        else if (unaryop_term->token.type == TokenType::NOT){
            if (unaryexp->t == Type::IntLiteral || unaryexp->t == Type::FloatLiteral){
                int tmp_result = (unaryexp->t == Type::IntLiteral) ? (!std::stoi(unaryexp->v)) : (!std::stof(unaryexp->v));
                root->v = std::to_string(tmp_result);
                root->t = Type::IntLiteral;     // 取非的计算结果为int型字面量
            }
            else if (unaryexp->t == Type::Int || unaryexp->t == Type::Float){
                // 使用not进行转换
                string tmp_not_name = "t" + std::to_string(tmp_cnt++);
                ir::Instruction* notInst = new ir::Instruction(ir::Operand(unaryexp->v,unaryexp->t),
                                                               ir::Operand(),
                                                               ir::Operand(tmp_not_name,ir::Type::Int),ir::Operator::_not);
                result.push_back(notInst);
                root->v = tmp_not_name;
                root->t = Type::Int;
            }
            else
                assert(0 && "Error");
        }
        else
            assert(0 && "Unknown UnaryOp");
        return result;
    }

    assert(0 && "Error");
}

// FuncRParams -> Exp { ',' Exp }
// root存储AST节点，func_para_type存储函数参数列表类型，paraVec存储返回参数列表
vector<Instruction *> frontend::Analyzer::analyze_funcrparams(FuncRParams *root, vector<Operand> &func_para_type, vector<Operand> &paraVec){
    vector<ir::Instruction *> result;   // result存储IR指令，paraVec存储返回参数列表
    // Exp { ',' Exp }
    for (int i=0, cnt=0; i<root->children.size(); i+=2, cnt+=1){
        Exp *exp = dynamic_cast<Exp *>(root->children[i]);
        vector<ir::Instruction *> cal_insts = analyze_exp(exp);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
        // 根据func_para_type[i]的类型进行类型提升
        if (func_para_type[cnt].type == ir::Type::Float){
            if (exp->t == Type::Int){
                string tmp_type_cvt_name = "t" + std::to_string(tmp_cnt++);
                ir::Instruction* cvtInst = new Instruction(ir::Operand(exp->v,ir::Type::Int), ir::Operand(), ir::Operand(tmp_type_cvt_name,ir::Type::Float),ir::Operator::cvt_i2f);
                result.push_back(cvtInst);
                paraVec.push_back(Operand(tmp_type_cvt_name, ir::Type::Float));
            }
            else if (exp->t == Type::IntLiteral) {
                float val = std::stoi(exp->v);
                paraVec.push_back(Operand(std::to_string(val), ir::Type::FloatLiteral));
            }
            else {
                assert(exp->t == Type::Float || exp->t == Type::FloatLiteral);
                paraVec.push_back(Operand(exp->v, exp->t));
            }
        }
        else if (func_para_type[cnt].type == ir::Type::Int) {
            if (exp->t == Type::Float) {
                string tmp_type_cvt_name = "t" + std::to_string(tmp_cnt++);
                ir::Instruction* cvtInst = new Instruction(ir::Operand(exp->v,ir::Type::Float), 
                                                           ir::Operand(), 
                                                           ir::Operand(tmp_type_cvt_name,ir::Type::Int),ir::Operator::cvt_f2i);
                result.push_back(cvtInst);
                paraVec.push_back(Operand(tmp_type_cvt_name, ir::Type::Int));
            }
            else if (exp->t == Type::FloatLiteral) {
                int val = std::stoi(exp->v);
                paraVec.push_back(Operand(std::to_string(val), ir::Type::IntLiteral));
            }
            else {
                assert(exp->t == Type::Int || exp->t == Type::IntLiteral);
                paraVec.push_back(Operand(exp->v, exp->t));
            }
        }
        else{   // 不需要类型提升
            paraVec.push_back(Operand(exp->v, exp->t));
        }
    }
    return result;
}

// PrimaryExp -> '(' Exp ')' | LVal | Number
vector<Instruction *> frontend::Analyzer::analyze_primaryexp(PrimaryExp *root){
    vector<Instruction *> result;
    // Exp
    if (root->children.size() == 3){
        Exp *exp = dynamic_cast<Exp *>(root->children[1]);
        result = analyze_exp(exp);
        root->t = exp->t;
        root->v = exp->v;
        return result;
    }
    // LVal
    if (LVal *lval = dynamic_cast<LVal *>(root->children[0])){
        result = analyze_lval(lval);
        root->v = lval->v;
        root->t = lval->t;
        return result;
    }
    // Number
    if (Number *number = dynamic_cast<Number *>(root->children[0])){
        analyze_number(number);
        root->v = number->v;
        root->t = number->t;
        return result;
    }
    assert(0 && "Error In analyze PrimaryExp");
}

// LVal -> Ident {'[' Exp ']'}
vector<Instruction *> frontend::Analyzer::analyze_lval(LVal *root){
    vector<Instruction *> result;
    // Ident
    Term* term = dynamic_cast<Term*>(root->children[0]);
    assert(term && term->token.type == TokenType::IDENFR);
    string var_name = term->token.value;
    // 普通变量 (可能的类型: Int, IntLiteral, Float, FloatLiteral, IntPtr, FloatPtr)
    if (root->children.size() == 1){
        // 通过符号表获取变量类型
        STE operand_ste = symbol_table.get_ste(var_name);
        root->t = operand_ste.operand.type;
        if (root->t == Type::IntLiteral || root->t == Type::FloatLiteral){
            root->v = operand_ste.literalVal;
        }
        else
            root->v = symbol_table.get_scoped_name(var_name); // 在此处返回重命名后的变量名, 后续计算时, 会在IR指令生成中使用重命名后的变量名
        return result;
    }
    // 一维数组
    else if (root->children.size() == 4){
        // Exp
        Exp* exp = dynamic_cast<Exp*>(root->children[2]);
        assert(exp != nullptr);
        // 计算数组下标
        vector<Instruction *> exp_result = analyze_exp(exp);
        assert(exp->t == Type::Int || exp->t == Type::IntLiteral);
        // 合并计算指令
        result.insert(result.end(), exp_result.begin(), exp_result.end());
        // 判断当前返回类型: Int, Float, IntPtr, FloatPtr
        STE operand_ste = symbol_table.get_ste(var_name);
        assert(operand_ste.operand.type == Type::IntPtr || operand_ste.operand.type == Type::FloatPtr);
        // 判断是一维数组还是二维数组
        if (operand_ste.dimension.size() == 1){ // 一维数组
            // 返回类型: Int or Float
            Type target_type = operand_ste.operand.type == Type::IntPtr ? Type::Int : Type::Float;
            // 从基址 + 偏移 从内存中LOAD出值
            string tmp_var_name = "t";
            tmp_var_name += std::to_string(tmp_cnt++);
            Instruction* loadInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),operand_ste.operand.type),
                                                        ir::Operand(exp->v,exp->t),
                                                        ir::Operand(tmp_var_name,target_type),ir::Operator::load);
            result.push_back(loadInst);
            root->t = target_type;
            root->v = tmp_var_name;
            return result;
        }
        else{       // 二维数组
            // 返回类型 IntPtr or FloatPtr
            Type target_type = operand_ste.operand.type; // 与原类型相同

            // 利用基址 + 偏移 计算出一维数组的基址
            string tmp_var_name = "t" + std::to_string(tmp_cnt++);
            // 偏移需要 乘上 数组列长度
            if (exp->t == Type::IntLiteral){
                int val = std::stoi(exp->v);
                val *= operand_ste.dimension[1];
                Instruction* getptrInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),operand_ste.operand.type),
                                                              ir::Operand(std::to_string(val),Type::IntLiteral),
                                                              ir::Operand(tmp_var_name,target_type),ir::Operator::getptr);
                result.push_back(getptrInst);
            }
            else{   // 否则需要生成指令，计算变量中的下标对应的偏移量
                // 需要新增一个临时变量
                string tmp_offset_name = "t" + std::to_string(tmp_cnt++);
                // 由于建议mul指令全为变量, 先将exp->v存入一个临时变量
                string tmp_mul_name = "t" + std::to_string(tmp_cnt++);
                Instruction* defInst = new ir::Instruction(ir::Operand(std::to_string(operand_ste.dimension[1]),Type::IntLiteral),
                                                           ir::Operand(),
                                                           ir::Operand(tmp_mul_name,Type::Int),ir::Operator::def);
                Instruction* mulInst = new ir::Instruction(ir::Operand(exp->v,Type::Int),
                                                           ir::Operand(tmp_mul_name,Type::Int),
                                                           ir::Operand(tmp_offset_name,Type::Int),ir::Operator::mul);
                Instruction* getptrInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name),operand_ste.operand.type),
                                                           ir::Operand(tmp_offset_name,Type::Int),
                                                           ir::Operand(tmp_var_name,target_type),ir::Operator::getptr);
                result.push_back(defInst);
                result.push_back(mulInst);
                result.push_back(getptrInst);
            }
            root->t = target_type;
            root->v = tmp_var_name;
            return result;
        }
        assert(0 && "Error");
    }
    // 二维数组
    else if (root->children.size() == 7){
        Exp* exp1 = dynamic_cast<Exp*>(root->children[2]);
        assert(exp1 != nullptr);
        Exp* exp2 = dynamic_cast<Exp*>(root->children[5]);
        assert(exp2 != nullptr);
        // 计算数组下标
        vector<Instruction *> exp1_result = analyze_exp(exp1);
        vector<Instruction *> exp2_result = analyze_exp(exp2);
        assert(exp1->t == Type::Int || exp1->t == Type::IntLiteral);
        assert(exp2->t == Type::Int || exp2->t == Type::IntLiteral);
        // 合并计算指令
        result.insert(result.end(), exp1_result.begin(), exp1_result.end());
        result.insert(result.end(), exp2_result.begin(), exp2_result.end());
        // 判断当前返回类型: Int, Float
        STE operand_ste = symbol_table.get_ste(var_name);
        assert(operand_ste.dimension.size() == 2);
        assert(operand_ste.operand.type == Type::IntPtr || operand_ste.operand.type == Type::FloatPtr);

        // 返回类型 Int or Float
        Type target_type = operand_ste.operand.type == Type::IntPtr ? Type::Int : Type::Float;

        // 为了从二维数组中取值，需计算偏移，此处可先直接将两个exp1和exp2计算的结果都放入临时变量中
        string tmp_dim1_name = "t" + std::to_string(tmp_cnt++);
        string tmp_dim2_name = "t" + std::to_string(tmp_cnt++);
        Instruction *def1Inst = new ir::Instruction(ir::Operand(exp1->v, exp1->t),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_dim1_name, Type::Int), ir::Operator::def);
        Instruction *def2Inst = new ir::Instruction(ir::Operand(exp2->v, exp2->t),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_dim2_name, Type::Int), ir::Operator::def);
        string tmp_col_len_name = "t" + std::to_string(tmp_cnt++);
        Instruction *def3Inst = new ir::Instruction(ir::Operand(std::to_string(operand_ste.dimension[1]), Type::IntLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_col_len_name, Type::Int), ir::Operator::def);
        string tmp_lineoffset_name = "t" + std::to_string(tmp_cnt++);
        // 计算行偏移
        Instruction *mulOffsetInst = new ir::Instruction(ir::Operand(tmp_dim1_name, Type::Int),
                                                         ir::Operand(tmp_col_len_name, Type::Int),
                                                         ir::Operand(tmp_lineoffset_name, Type::Int), ir::Operator::mul);
        // 计算总偏移
        string tmp_totaloffset_name = "t" + std::to_string(tmp_cnt++);
        Instruction *addOffsetInst = new ir::Instruction(ir::Operand(tmp_lineoffset_name, Type::Int),
                                                         ir::Operand(tmp_dim2_name, Type::Int),
                                                         ir::Operand(tmp_totaloffset_name, Type::Int), ir::Operator::add);
        // 取值
        string tmp_loadval_name = "t" + std::to_string(tmp_cnt++);
        Instruction *loadInst = new ir::Instruction(ir::Operand(symbol_table.get_scoped_name(var_name), operand_ste.operand.type),
                                                    ir::Operand(tmp_totaloffset_name, Type::Int),
                                                    ir::Operand(tmp_loadval_name, target_type), ir::Operator::load);
        result.push_back(def1Inst);
        result.push_back(def2Inst);
        result.push_back(def3Inst);
        result.push_back(mulOffsetInst);
        result.push_back(addOffsetInst);
        result.push_back(loadInst);
        root->v = tmp_loadval_name;
        root->t = target_type;
        return result;
    }
}

// Number -> IntConst | floatConst
vector<ir::Instruction *> frontend::Analyzer::analyze_number(Number *root){
    Term *term = dynamic_cast<Term *>(root->children[0]);
    // IntConst
    if (term->token.type == TokenType::INTLTR){
        root->t = Type::IntLiteral;
        // 针对二进制、八进制、十六进制的特殊转换处理
        const string &token_val = term->token.value;
        // 十六进制
        if (token_val.length() >= 3 && token_val[0] == '0' && (token_val[1] == 'x' || token_val[1] == 'X')){
            root->v = std::to_string(std::stoi(token_val, nullptr, 16));
        }
        // 二进制
        else if (token_val.length() >= 3 && token_val[0] == '0' && (token_val[1] == 'b' || token_val[1] == 'B')){
            root->v = std::to_string(std::stoi(token_val.substr(2), nullptr, 2));
        }
        // 八进制
        else if (token_val.length() >= 2 && token_val[0] == '0'){
            root->v = std::to_string(std::stoi(token_val, nullptr, 8));
        }
        // 十进制
        else
            root->v = token_val;
    }
    // floatConst
    else if (term->token.type == TokenType::FLOATLTR){
        root->t = Type::FloatLiteral;
        root->v = term->token.value;
    }
    else
        assert(0 && "Unknown Number Type");
    return {};
}

// Cond -> LOrExp
vector<ir::Instruction *> frontend::Analyzer::analyze_cond(Cond* root){
    LOrExp* lorexp = dynamic_cast<LOrExp*>(root->children[0]);
    assert(lorexp != nullptr);
    vector<ir::Instruction *> cal_insts = analyze_lorexp(lorexp);
    root->v = lorexp->v;
    root->t = lorexp->t;
    return cal_insts;
}

// LOrExp -> LAndExp [ '||' LOrExp ]
vector<ir::Instruction *> frontend::Analyzer::analyze_lorexp(LOrExp* root){
    vector<ir::Instruction *> result;
    // LAndExp
    assert(root->children.size()>=1);
    LAndExp* landexp = dynamic_cast<LAndExp*>(root->children[0]);
    assert(landexp != nullptr);
    vector<ir::Instruction *> cal_insts = analyze_landexp(landexp);
    result.insert(result.end(),cal_insts.begin(),cal_insts.end());
    root->v = landexp->v;
    root->t = landexp->t;
    // [ '||' LOrExp ]
    if (root->children.size() == 1){
        return result;
    }
    else{
        // LOrExp
        LOrExp* lorexp = dynamic_cast<LOrExp*>(root->children[2]);
        assert(lorexp != nullptr);
        vector<ir::Instruction *> cal_insts = analyze_lorexp(lorexp); // 并不立即加入到result中，在确定跳转后再加入

        // 处理操作数1 (计算其是否为真 or 假)
        if (root->t == Type::Float){
            string tmp_name = "t" + std::to_string(tmp_cnt++);
            ir::Instruction* cvtInst = new ir::Instruction(ir::Operand(root->v,Type::Float),
                                                           ir::Operand("0.0",Type::FloatLiteral),
                                                           ir::Operand(tmp_name,Type::Int),ir::Operator::fneq);
            result.push_back(cvtInst);
            root->v = tmp_name;
            root->t = Type::Int;
        }
        else if (root->t == Type::FloatLiteral){
            float val = std::stof(root->v);
            root->t = Type::IntLiteral;
            root->v = std::to_string(val != 0);
        }

        // 处理操作数2 (计算其是否为真 or 假)
        if (lorexp->t == Type::Float){
            string tmp_name = "t";
            tmp_name += std::to_string(tmp_cnt++);
            ir::Instruction* cvtInst = new ir::Instruction(ir::Operand(lorexp->v,Type::Float),
                                                           ir::Operand("0.0",Type::FloatLiteral),
                                                           ir::Operand(tmp_name,Type::Int),ir::Operator::fneq);
            cal_insts.push_back(cvtInst);
            lorexp->v = tmp_name;
            lorexp->t = Type::Int;
        }
        else if (lorexp->t == Type::FloatLiteral){
            float val = std::stof(lorexp->v);
            lorexp->t = Type::IntLiteral;
            lorexp->v = std::to_string(val != 0);
        }

        // 计算LAndExp || LOrExp
        if (root->t == Type::IntLiteral && lorexp->t == Type::IntLiteral){
            root->v = std::to_string(std::stoi(root->v) || std::stoi(lorexp->v));
        }
        else{
            // 注意短路规则: 左侧为真则不计算右侧
            string tmp_cal_name = "t" + std::to_string(tmp_cnt++);

            // 真逻辑: 跳转PC+2,tmp_cal_name赋为1, 然后跳转至结束
            Instruction * root_true_goto = new Instruction(ir::Operand(root->v,root->t),
                                ir::Operand(),
                                ir::Operand("2",Type::IntLiteral),ir::Operator::_goto);
            Instruction * root_true_assign = new Instruction(ir::Operand("1",Type::IntLiteral),
                                                             ir::Operand(),
                                                             ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::mov);

            // 假逻辑: 跳转PC+(1+2)
            Instruction * root_false_goto = new Instruction(ir::Operand(),
                                                            ir::Operand(),
                                                            ir::Operand("3",Type::IntLiteral),ir::Operator::_goto);

            // 假逻辑中需要使用的or指令
            Instruction * calInst = new Instruction(ir::Operand(root->v,root->t),
                                                    ir::Operand(lorexp->v,lorexp->t),
                                                    ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::_or);
            cal_insts.push_back(calInst);

            Instruction * true_logic_goto = new Instruction(ir::Operand(),
                                                            ir::Operand(),
                                                            ir::Operand(std::to_string(cal_insts.size()+1),Type::IntLiteral),ir::Operator::_goto);

            result.push_back(root_true_goto);
            result.push_back(root_false_goto);
            result.push_back(root_true_assign);
            result.push_back(true_logic_goto);
            result.insert(result.end(),cal_insts.begin(),cal_insts.end());

            root->v = tmp_cal_name;
            root->t = Type::Int;
        }
        return result;
    }
}

// LAndExp -> EqExp [ '&&' LAndExp ]
vector<ir::Instruction *> frontend::Analyzer::analyze_landexp(LAndExp* root){
    vector<ir::Instruction *> result;
    // EqExp
    assert(root->children.size()>=1);
    EqExp* eqexp = dynamic_cast<EqExp*>(root->children[0]);
    assert(eqexp != nullptr);
    vector<ir::Instruction *> cal_insts = analyze_eqexp(eqexp);
    result.insert(result.end(),cal_insts.begin(),cal_insts.end());
    root->v = eqexp->v;
    root->t = eqexp->t;
    // [ '&&' LAndExp ]
    if (root->children.size() == 1){
        return result;
    }
    else{
        // LAndExp
        LAndExp* landexp = dynamic_cast<LAndExp*>(root->children[2]);
        assert(landexp);
        vector<ir::Instruction *> cal_insts = analyze_landexp(landexp); // 并不立即加入到result中，在确定跳转后再加入
        
        // 处理操作数1 (计算其是否为真 or 假)
        if (root->t == Type::Float){
            string tmp_name = "t" + std::to_string(tmp_cnt++);
            ir::Instruction* cvtInst = new ir::Instruction(ir::Operand(root->v,Type::Float),
                                                           ir::Operand("0.0",Type::FloatLiteral),
                                                           ir::Operand(tmp_name,Type::Int),ir::Operator::fneq);
            result.push_back(cvtInst);
            root->v = tmp_name;
            root->t = Type::Int;
        }
        else if (root->t == Type::FloatLiteral){
            float val = std::stof(root->v);
            root->t = Type::IntLiteral;
            root->v = std::to_string(val != 0);
        }

        // 处理操作数2 (计算其是否为真 or 假)
        if (landexp->t == Type::Float){
            string tmp_name = "t" + std::to_string(tmp_cnt++);
            ir::Instruction* cvtInst = new ir::Instruction(ir::Operand(landexp->v,Type::Float),
                                                           ir::Operand("0.0",Type::FloatLiteral),
                                                           ir::Operand(tmp_name,Type::Int),ir::Operator::fneq);
            cal_insts.push_back(cvtInst);
            landexp->v = tmp_name;
            landexp->t = Type::Int;
        }
        else if (landexp->t == Type::FloatLiteral){
            float val = std::stof(landexp->v);
            landexp->t = Type::IntLiteral;
            landexp->v = std::to_string(val != 0);
        }

        // 计算EqExp && LAndExp
        if (root->t == Type::IntLiteral && landexp->t == Type::IntLiteral){
            root->v = std::to_string(std::stoi(root->v) && std::stoi(landexp->v));
        }
        else{
            // 注意短路规则: 左侧为假，则不计算右侧！！！
            string tmp_cal_name = "t";
            tmp_cal_name += std::to_string(tmp_cnt++);
            Instruction * root_true_goto = new Instruction(ir::Operand(root->v,root->t),
                                                           ir::Operand(),
                                                           ir::Operand("2",Type::IntLiteral),ir::Operator::_goto);
            result.push_back(root_true_goto);
            // 真逻辑部分，此时不短路，开始计算右侧并赋值
            vector<Instruction *> true_logic_inst = cal_insts;
            Instruction * calInst = new Instruction(ir::Operand(root->v,root->t),
                                                    ir::Operand(landexp->v,landexp->t),
                                                    ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::_and);
            true_logic_inst.push_back(calInst);
            // 真逻辑结束后，需跳出假逻辑部分
            Instruction * true_logic_goto = new Instruction(ir::Operand(),
                                                            ir::Operand(),
                                                            ir::Operand("2",Type::IntLiteral),ir::Operator::_goto);
            true_logic_inst.push_back(true_logic_goto);
            // 如果root为假，则不进行右侧计算，直接跳转出结束
            Instruction * root_false_goto = new Instruction(ir::Operand(),
                                                            ir::Operand(),
                                                            ir::Operand(std::to_string(true_logic_inst.size()+1),Type::IntLiteral),ir::Operator::_goto);
            // root为假时，tmp_cal_name为0
            Instruction * root_false_assign = new Instruction(ir::Operand("0",Type::IntLiteral),
                                ir::Operand(),
                                ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::mov);
            result.push_back(root_false_goto);
            result.insert(result.end(),true_logic_inst.begin(),true_logic_inst.end());
            result.push_back(root_false_assign);
            root->v = tmp_cal_name;
            root->t = Type::Int;
        }
        return result;
    }
}

// EqExp -> RelExp { ('==' | '!=') RelExp }
vector<ir::Instruction *> frontend::Analyzer::analyze_eqexp(EqExp* root){
    // 可能的类型: Int or IntLiteral or Float or FloatLiteral (Float or FloatLiteral: 仅有一个RelExp, 不进行关系运算)

    // 类似RelExp与MulExp，需要将所有参与计算的值统一才可以进行计算
    vector<Instruction *> result;

    // 深度优先遍历, 先计算其所有子RelExp
    for (int i = 0; i < root->children.size(); i += 2){
        RelExp *relexp = dynamic_cast<RelExp *>(root->children[i]);
        assert(relexp != nullptr);
        vector<Instruction *> cal_insts = analyze_relexp(relexp);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
    }

    // 计算表达式的结果
    // 默认为第一个RelExp的值
    RelExp* firstRelExp = dynamic_cast<RelExp*>(root->children[0]);
    assert(firstRelExp != nullptr);
    root->t = firstRelExp->t;
    root->v = firstRelExp->v;

    // RelExp
    if (root->children.size() == 1){
        return result;
    }

    // { ('==' | '!=') RelExp }
    for (int i=2; i<root->children.size(); i+=2){
        RelExp *relexp = dynamic_cast<RelExp *>(root->children[i]);
        Term* op_term  = dynamic_cast<Term*>(root->children[i-1]);
        Type target_type = root->t;
        // 在计算之前，先将两个操作数的类型变为相同的
        if (root->t != relexp->t){
            // 确定类型提升
            if (relexp->t == ir::Type::Float)
                target_type = ir::Type::Float;
            else if (relexp->t == ir::Type::Int && target_type == ir::Type::IntLiteral)
                target_type = ir::Type::Int;
            else if (relexp->t == ir::Type::FloatLiteral && target_type == ir::Type::IntLiteral)
                target_type = ir::Type::FloatLiteral;
            else if ((relexp->t == ir::Type::FloatLiteral && target_type == ir::Type::Int) || (target_type == ir::Type::FloatLiteral && relexp->t == ir::Type::Int)) // 提升没有顺序
                target_type = ir::Type::Float;
            
            // 执行类型转换
            if (target_type == Type::Int){                  // IntLiteral -> Int
                IntLiteral2Int(root, relexp, frontend::NodeType::RELEXP, result);
            }
            else if (target_type == Type::FloatLiteral){    // IntLiteral -> FloatLiteral
                IntLiteral2FloatLiteral(root, relexp, frontend::NodeType::RELEXP);
            }
            else if (target_type == Type::Float){           // IntLiteral -> Float, Int -> Float, FloatLiteral -> Float
                IntLiteral2Float(root, relexp, frontend::NodeType::RELEXP, result);
                Int2Float(root, relexp, frontend::NodeType::RELEXP, result);
                FloatLiteral2Float(root, relexp, frontend::NodeType::RELEXP, result);
            }
            else
                assert(0 && "Error");
        }
        // 已经化为相同类型，可以开始计算
        if (target_type == Type::IntLiteral){
            int val1 = std::stoi(root->v);
            int val2 = std::stoi(relexp->v);
            if (op_term->token.type == TokenType::EQL)
                root->v = std::to_string(val1 == val2);
            else if (op_term->token.type == TokenType::NEQ)
                root->v = std::to_string(val1 != val2);
            else
                assert(0 && "Invalid Op");
        }
        else if (target_type == Type::FloatLiteral){
            float val1 = std::stof(root->v);
            float val2 = std::stof(relexp->v);
            if (op_term->token.type == TokenType::EQL)
                root->v = std::to_string(val1 == val2);
            else if (op_term->token.type == TokenType::NEQ)
                root->v = std::to_string(val1 != val2);
            else
                assert(0 && "Invalid Op");
            
            root->t = Type::IntLiteral;
        }
        else if (target_type == Type::Int){
            // 无法在编译期确定结果，生成指令
            string tmp_cal_name = "t" + std::to_string(tmp_cnt++);
            Instruction * calInst;
            if (op_term->token.type == TokenType::EQL)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(relexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::eq);
            else if (op_term->token.type == TokenType::NEQ)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(relexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::neq);
            else
                assert(0 && "Invalid Op");
            result.push_back(calInst);
            root->v = tmp_cal_name;
            root->t = Type::Int;
        }
        else if (target_type == Type::Float){
            // 无法在编译期确定结果，生成指令
            string tmp_cal_name = "t" + std::to_string(tmp_cnt++);
            Instruction * calInst;
            if (op_term->token.type == TokenType::LSS)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Float),
                                          ir::Operand(relexp->v,ir::Type::Float),
                                          ir::Operand(tmp_cal_name,ir::Type::Float),ir::Operator::feq);
            else if (op_term->token.type == TokenType::GTR)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Float),
                                          ir::Operand(relexp->v,ir::Type::Float),
                                          ir::Operand(tmp_cal_name,ir::Type::Float),ir::Operator::fneq);
            else
                assert(0 && "Invalid Op");
            result.push_back(calInst);
            root->v = tmp_cal_name;
            root->t = Type::Float;
        }
        else
            assert(0 && "Error");
    }
    return result;
}

// RelExp -> AddExp { ('<' | '>' | '<=' | '>=') AddExp }
vector<ir::Instruction *> frontend::Analyzer::analyze_relexp(RelExp* root){
    // 可能的类型: Int or IntLiteral or Float or FloatLiteral (Float or FloatLiteral: 仅有一个AddExp, 不进行关系运算)

    // 类似AddExp与MulExp, 需要将所有参与计算的值统一才可以进行计算
    vector<Instruction *> result;

    // 深度优先遍历, 先计算其所有子AddExp
    for (int i=0; i<root->children.size(); i+=2){
        AddExp *addexp = dynamic_cast<AddExp *>(root->children[i]);
        assert(addexp != nullptr);
        vector<Instruction *> cal_insts = analyze_addexp(addexp);
        result.insert(result.end(),cal_insts.begin(),cal_insts.end());
    }

    // 计算表达式的结果
    // 默认为第一个AddExp的值
    AddExp* firstAddExp = dynamic_cast<AddExp*>(root->children[0]);
    assert(firstAddExp);
    root->t = firstAddExp->t;
    root->v = firstAddExp->v;

    // AddExp
    if (root->children.size() == 1){
        return result;
    }

    // { ('<' | '>' | '<=' | '>=') AddExp }
    for (int i=2; i<root->children.size(); i+=2){
        AddExp *addexp = dynamic_cast<AddExp *>(root->children[i]);
        Term* op_term  = dynamic_cast<Term*>(root->children[i-1]);
        Type target_type = root->t;

        // 在计算之前，先将两个操作数的类型变为相同的
        if (root->t != addexp->t){
            // 确定类型提升
            if (addexp->t == ir::Type::Float)
                target_type = ir::Type::Float;
            else if (addexp->t == ir::Type::Int && target_type == ir::Type::IntLiteral)
                target_type = ir::Type::Int;
            else if (addexp->t == ir::Type::FloatLiteral && target_type == ir::Type::IntLiteral)
                target_type = ir::Type::FloatLiteral;
            else if ((addexp->t == ir::Type::FloatLiteral && target_type == ir::Type::Int) || (target_type == ir::Type::FloatLiteral && addexp->t == ir::Type::Int)) // 提升没有顺序
                target_type = ir::Type::Float;
            
            // 执行类型转换
            if (target_type == Type::Int){                  // IntLiteral -> Int
                IntLiteral2Int(root, addexp, frontend::NodeType::ADDEXP, result);
            }
            else if (target_type == Type::FloatLiteral){    // IntLiteral -> FloatLiteral
                IntLiteral2FloatLiteral(root, addexp, frontend::NodeType::ADDEXP);
            }
            else if (target_type == Type::Float){           // IntLiteral -> Float, Int -> Float, FloatLiteral -> Float
                IntLiteral2Float(root, addexp, frontend::NodeType::ADDEXP, result);
                Int2Float(root, addexp, frontend::NodeType::ADDEXP, result);
                FloatLiteral2Float(root, addexp, frontend::NodeType::ADDEXP, result);
            }
            else
                assert(0 && "Error");
        }

        // 已经化为相同类型，可以开始计算
        if (target_type == Type::IntLiteral){
            int val1 = std::stoi(root->v);
            int val2 = std::stoi(addexp->v);
            if (op_term->token.type == TokenType::LSS)
                root->v = std::to_string(val1 < val2);
            else if (op_term->token.type == TokenType::GTR)
                root->v = std::to_string(val1 > val2);
            else if (op_term->token.type == TokenType::LEQ)
                root->v = std::to_string(val1 <= val2);
            else if (op_term->token.type == TokenType::GEQ)
                root->v = std::to_string(val1 >= val2);
            else
                assert(0 && "Invalid Op");
        }
        else if (target_type == Type::FloatLiteral){
            float val1 = std::stof(root->v);
            float val2 = std::stof(addexp->v);
            if (op_term->token.type == TokenType::LSS)
                root->v = std::to_string(val1 < val2);
            else if (op_term->token.type == TokenType::GTR)
                root->v = std::to_string(val1 > val2);
            else if (op_term->token.type == TokenType::LEQ)
                root->v = std::to_string(val1 <= val2);
            else if (op_term->token.type == TokenType::GEQ)
                root->v = std::to_string(val1 >= val2);
            else
                assert(0 && "Invalid Op");
            
            root->t = Type::IntLiteral;
        }
        else if (target_type == Type::Int){
            // 无法在编译期确定结果，生成指令
            string tmp_cal_name = "t" + std::to_string(tmp_cnt++);
            Instruction * calInst;
            if (op_term->token.type == TokenType::LSS)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(addexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::lss);
            else if (op_term->token.type == TokenType::GTR)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(addexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::gtr);
            else if (op_term->token.type == TokenType::LEQ)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(addexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::leq);
            else if (op_term->token.type == TokenType::GEQ)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Int),
                                          ir::Operand(addexp->v,ir::Type::Int),
                                          ir::Operand(tmp_cal_name,ir::Type::Int),ir::Operator::geq);
            else
                assert(0 && "Invalid Op");
            result.push_back(calInst);
            root->v = tmp_cal_name;
            root->t = Type::Int;
        }
        else if (target_type == Type::Float){
            // 无法在编译期确定结果，生成指令
            string tmp_cal_name = "t" + std::to_string(tmp_cnt++);
            Instruction * calInst;
            if (op_term->token.type == TokenType::LSS)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Float),
                                          ir::Operand(addexp->v,ir::Type::Float),
                                          ir::Operand(tmp_cal_name,ir::Type::Float),ir::Operator::flss);
            else if (op_term->token.type == TokenType::GTR)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Float),
                                          ir::Operand(addexp->v,ir::Type::Float),
                                          ir::Operand(tmp_cal_name,ir::Type::Float),ir::Operator::fgtr);
            else if (op_term->token.type == TokenType::LEQ)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Float),
                                          ir::Operand(addexp->v,ir::Type::Float),
                                          ir::Operand(tmp_cal_name,ir::Type::Float),ir::Operator::fleq);
            else if (op_term->token.type == TokenType::GEQ)
                calInst = new Instruction(ir::Operand(root->v,ir::Type::Float),
                                          ir::Operand(addexp->v,ir::Type::Float),
                                          ir::Operand(tmp_cal_name,ir::Type::Float),ir::Operator::fgeq);
            else
                assert(0 && "Invalid Op");
            result.push_back(calInst);
            root->v = tmp_cal_name;
            root->t = Type::Float;
        }
        else
            assert(0 && "Error");
    }
    return result;
}


// ---------- 辅助函数，在计算表达式的值的时候进行类型转换 ----------
// 一开始是为了重用代码而将其抽象成函数，但由于C++中无法对变量进行原地类型转换，因此下面的函数中重用的代码还是需要写两遍，并没有减少代码量

void frontend::Analyzer::IntLiteral2Int(AstNode* root, AstNode* child, frontend::NodeType type, vector<Instruction *> &result){
    if(type == frontend::NodeType::RELEXP){
        EqExp *rt = dynamic_cast<EqExp *>(root);
        RelExp *chd = dynamic_cast<RelExp *>(child);
        assert(rt != nullptr && chd != nullptr);
        if (chd->t == Type::IntLiteral){
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(chd->v,ir::Type::IntLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Int),ir::Operator::def);
            result.push_back(cvtInst);
            chd->v = tmp_intcvt_name;
            chd->t = Type::Int;
        }
        if (rt->t == Type::IntLiteral){
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(rt->v,ir::Type::IntLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Int),ir::Operator::def);
            result.push_back(cvtInst);
            rt->v = tmp_intcvt_name;
            rt->t = Type::Int;
        }
    }
    else if(type == frontend::NodeType::ADDEXP){
        RelExp *rt = dynamic_cast<RelExp *>(root);
        AddExp *chd = dynamic_cast<AddExp *>(child);
        assert(rt != nullptr && chd != nullptr);
        if (chd->t == Type::IntLiteral){
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(chd->v,ir::Type::IntLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Int),ir::Operator::def);
            result.push_back(cvtInst);
            chd->v = tmp_intcvt_name;
            chd->t = Type::Int;
        }
        if (rt->t == Type::IntLiteral){
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(rt->v,ir::Type::IntLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Int),ir::Operator::def);
            result.push_back(cvtInst);
            rt->v = tmp_intcvt_name;
            rt->t = Type::Int;
        }
    }
    else{
        assert(0 && "NodeType Error");
    }
    return;
}

void frontend::Analyzer::IntLiteral2FloatLiteral(AstNode* root, AstNode* child, frontend::NodeType type){
    if(type == frontend::NodeType::RELEXP){
        EqExp *rt = dynamic_cast<EqExp *>(root);
        RelExp *chd = dynamic_cast<RelExp *>(child);
        assert(rt != nullptr && chd != nullptr);
        if (chd->t == Type::IntLiteral){
            float val = std::stoi(chd->v);
            chd->v = std::to_string(val);
            chd->t = Type::FloatLiteral;
        }
        if (rt->t == Type::IntLiteral){
            float val = std::stoi(rt->v);
            rt->v = std::to_string(val);
            rt->t = Type::FloatLiteral;
        }
    }
    else if(type == frontend::NodeType::ADDEXP){
        RelExp *rt = dynamic_cast<RelExp *>(root);
        AddExp *chd = dynamic_cast<AddExp *>(child);
        assert(rt != nullptr && chd != nullptr);
        if (chd->t == Type::IntLiteral){
            float val = std::stoi(chd->v);
            chd->v = std::to_string(val);
            chd->t = Type::FloatLiteral;
        }
        if (rt->t == Type::IntLiteral){
            float val = std::stoi(rt->v);
            rt->v = std::to_string(val);
            rt->t = Type::FloatLiteral;
        }
    }
    else{
        assert(0 && "NodeType Error");
    }
    return;
}

void frontend::Analyzer::IntLiteral2Float(AstNode* root, AstNode* child, frontend::NodeType type, vector<Instruction *> &result){
    if(type == frontend::NodeType::RELEXP){
        EqExp *rt = dynamic_cast<EqExp *>(root);
        RelExp *chd = dynamic_cast<RelExp *>(child);
        assert(rt != nullptr && chd != nullptr);
        if (chd->t == Type::IntLiteral){
            float val = std::stof(chd->v);
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
            result.push_back(cvtInst);
            chd->v = tmp_intcvt_name;
            chd->t = Type::Float;
        }
        if (rt->t == Type::IntLiteral){
            float val = std::stof(rt->v);
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
            result.push_back(cvtInst);
            rt->v = tmp_intcvt_name;
            rt->t = Type::Float;
        }
    }
    else if(type == frontend::NodeType::ADDEXP){
        RelExp *rt = dynamic_cast<RelExp *>(root);
        AddExp *chd = dynamic_cast<AddExp *>(child);
        assert(rt != nullptr && chd != nullptr);
        if (chd->t == Type::IntLiteral){         // IntLiteral -> Float
            float val = std::stof(chd->v);
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
            result.push_back(cvtInst);
            chd->v = tmp_intcvt_name;
            chd->t = Type::Float;
        }
        if (rt->t == Type::IntLiteral){
            float val = std::stof(rt->v);
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(std::to_string(val),ir::Type::FloatLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
            result.push_back(cvtInst);
            rt->v = tmp_intcvt_name;
            rt->t = Type::Float;
        }
    }
    else{
        assert(0 && "NodeType Error");
    }
    return;
}

void frontend::Analyzer::Int2Float(AstNode* root, AstNode* child, frontend::NodeType type, vector<Instruction *> &result){
    if(type == frontend::NodeType::RELEXP){
        EqExp *rt = dynamic_cast<EqExp *>(root);
        RelExp *chd = dynamic_cast<RelExp *>(child);
        assert(rt != nullptr && chd != nullptr);
        if (chd->t == Type::Int){
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(chd->v,ir::Type::Int),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::cvt_i2f);
            result.push_back(cvtInst);
            chd->v = tmp_intcvt_name;
            chd->t = Type::Float;
        }
        if (rt->t == Type::Int){
            float val = std::stof(rt->v);
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(rt->v,ir::Type::Int),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::cvt_i2f);
            result.push_back(cvtInst);
            rt->v = tmp_intcvt_name;
            rt->t = Type::Float;
        }
    }
    else if(type == frontend::NodeType::ADDEXP){
        RelExp *rt = dynamic_cast<RelExp *>(root);
        AddExp *chd = dynamic_cast<AddExp *>(child);
        assert(rt != nullptr && chd != nullptr);
        if (chd->t == Type::Int){
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(chd->v,ir::Type::Int),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::cvt_i2f);
            result.push_back(cvtInst);
            chd->v = tmp_intcvt_name;
            chd->t = Type::Float;
        }
        if (rt->t == Type::Int){
            float val = std::stof(rt->v);
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(rt->v,ir::Type::Int),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::cvt_i2f);
            result.push_back(cvtInst);
            rt->v = tmp_intcvt_name;
            rt->t = Type::Float;
        }
    }
    else{
        assert(0 && "NodeType Error");
    }
    return;
}

void frontend::Analyzer::FloatLiteral2Float(AstNode* root, AstNode* child, frontend::NodeType type, vector<Instruction *> &result){
    if(type == frontend::NodeType::RELEXP){
        EqExp *rt = dynamic_cast<EqExp *>(root);
        RelExp *chd = dynamic_cast<RelExp *>(child);
        assert(rt != nullptr && chd != nullptr);
        if (chd->t == Type::FloatLiteral){
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(chd->v,ir::Type::FloatLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
            result.push_back(cvtInst);
            chd->v = tmp_intcvt_name;
            chd->t = Type::Float;
        }
        if (rt->t == Type::FloatLiteral){
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(rt->v,ir::Type::FloatLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
            result.push_back(cvtInst);
            rt->v = tmp_intcvt_name;
            rt->t = Type::Float;
        }
    }
    else if(type == frontend::NodeType::ADDEXP){
        RelExp *rt = dynamic_cast<RelExp *>(root);
        AddExp *chd = dynamic_cast<AddExp *>(child);
        assert(rt != nullptr && chd != nullptr);
        if (chd->t == Type::FloatLiteral){
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(chd->v,ir::Type::FloatLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
            result.push_back(cvtInst);
            chd->v = tmp_intcvt_name;
            chd->t = Type::Float;
        }
        if (rt->t == Type::FloatLiteral){
            string tmp_intcvt_name = "t" + std::to_string(tmp_cnt++);
            Instruction * cvtInst = new Instruction(ir::Operand(rt->v,ir::Type::FloatLiteral),
                                                    ir::Operand(),
                                                    ir::Operand(tmp_intcvt_name,ir::Type::Float),ir::Operator::fdef);
            result.push_back(cvtInst);
            rt->v = tmp_intcvt_name;
            rt->t = Type::Float;
        }
    }
    else{
        assert(0 && "NodeType Error");
    }
    return;
}
