/*语法分析
    因为文法规则加入了许多需要递归的产生式，作业2的思路不再适用。
    定义辅助函数 Match_XX 为每种产生式的构造提供可选的终结符/非终结符，以集合方式返回；
    定义辅助函数 retreat 为匹配失败的情形恢复原状态；
    在构造产生式时从左向右依次判断当前token是否符合文法规则，符合则匹配成功，失败则回退。构造产生式的函数除了 CompUnit 返回 AstNode 类型，其余均为 bool 型。
*/
#include"front/syntax.h"

#include<iostream>
#include<cassert>
#include<unordered_set>

using frontend::Parser;

// #define DEBUG_PARSER
// #define TODO assert(0 && "todo")
// #define CUR_TOKEN_IS(tk_type) (token_stream[index].type == TokenType::tk_type)
// #define PARSE_TOKEN(tk_type) root->children.push_back(parseTerm(root, TokenType::tk_type))
// #define PARSE(name, type) auto name = new type(root); assert(parse##type(name)); root->children.push_back(name); 

/*消除了左递归的文法规则：
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

Parser::Parser(const std::vector<frontend::Token>& tokens): index(0), token_stream(tokens) {}

Parser::~Parser() {}

frontend::CompUnit* Parser::get_abstract_syntax_tree(){
    return parseCompUnit(nullptr);
}

void Parser::log(AstNode* node){
    #ifdef DEBUG_PARSER
        std::cout << "in parse" << toString(node->type) << ", cur_token_type::" << toString(token_stream[index].type) << ", token_val::" << token_stream[index].value << '\n';
    #endif
}

// 辅助函数，用于判断某文法内的分支
std::unordered_set<frontend::TokenType> Parser::Match_Compunit(){
    auto first_decl = Match_Decl();
    auto first_funcdef = Match_FuncDef();
    first_funcdef.insert(first_decl.begin(), first_decl.end());
    return first_funcdef;       // 返回两个集合的并集
}

std::unordered_set<frontend::TokenType> Parser::Match_Decl(){
    auto first_constdecl = Match_ConstDecl();
    auto first_vardecl = Match_VarDecl();
    first_vardecl.insert(first_constdecl.begin(), first_constdecl.end());
    return first_vardecl;       // 返回两个集合的并集
}

std::unordered_set<frontend::TokenType> Parser::Match_ConstDecl(){
    return {frontend::TokenType::CONSTTK};  // 返回'const'
}

std::unordered_set<frontend::TokenType> Parser::Match_BType(){
    return {frontend::TokenType::INTTK, frontend::TokenType::FLOATTK};  // 返回'int'、'float'
}

std::unordered_set<frontend::TokenType> Parser::Match_ConstDef(){
    return {frontend::TokenType::IDENFR};   // 返回Ident
}

std::unordered_set<frontend::TokenType> Parser::Match_ConstInitVal(){
    auto first_constexp = Match_ConstExp();
    first_constexp.insert(frontend::TokenType::LBRACE);
    return first_constexp;      // 返回ConstExp、'{'
}

std::unordered_set<frontend::TokenType> Parser::Match_VarDecl(){
    return Match_BType();       // 返回BType
}

std::unordered_set<frontend::TokenType> Parser::Match_VarDef(){
    return {frontend::TokenType::IDENFR};   // 返回Ident
}

std::unordered_set<frontend::TokenType> Parser::Match_InitVal(){
    auto first_exp = Match_Exp();
    first_exp.insert(frontend::TokenType::LBRACE);
    return first_exp;           // 返回Exp、'{'
}

std::unordered_set<frontend::TokenType> Parser::Match_FuncDef(){
    return Match_FuncType();    // 返回FuncType
}

std::unordered_set<frontend::TokenType> Parser::Match_FuncType(){
    return {frontend::TokenType::VOIDTK, frontend::TokenType::INTTK, frontend::TokenType::FLOATTK}; // 返回'void'、'int'、'float'
}

std::unordered_set<frontend::TokenType> Parser::Match_FuncFParam(){
    return Match_BType();       // 返回BType
}

std::unordered_set<frontend::TokenType> Parser::Match_FuncFParams(){
    return Match_FuncFParam();  // 返回FuncFParam
}

std::unordered_set<frontend::TokenType> Parser::Match_Block(){
    return {frontend::TokenType::LBRACE};   // 返回'{'
}

std::unordered_set<frontend::TokenType> Parser::Match_BlockItem(){
    auto first_decl = Match_Decl();
    auto first_stmt = Match_Stmt();
    first_stmt.insert(first_decl.begin(), first_decl.end());
    return first_stmt;          // 返回Decl、Stmt
}

std::unordered_set<frontend::TokenType> Parser::Match_Stmt(){
    auto first_lval = Match_LVal();
    auto first_block = Match_Block();
    first_lval.insert(first_block.begin(), first_block.end());
    first_lval.insert(frontend::TokenType::IFTK);
    first_lval.insert(frontend::TokenType::WHILETK);
    first_lval.insert(frontend::TokenType::BREAKTK);
    first_lval.insert(frontend::TokenType::CONTINUETK);
    first_lval.insert(frontend::TokenType::RETURNTK);
    auto first_exp = Match_Exp();
    first_lval.insert(first_exp.begin(), first_exp.end());
    first_lval.insert(frontend::TokenType::SEMICN);     // 因为[Exp]是可选项，所以';'也可能作为开头
    return first_lval;          // 返回LVal、Block、'if'、'while'、'break'、'continue'、'return'、[Exp]、';'
}

std::unordered_set<frontend::TokenType> Parser::Match_Exp(){
    return Match_AddExp();      // 返回AddExp
}

std::unordered_set<frontend::TokenType> Parser::Match_Cond(){
    return Match_LOrExp();      // 返回LOrExp
}

std::unordered_set<frontend::TokenType> Parser::Match_LVal(){
    return {frontend::TokenType::IDENFR};   // 返回Ident
}

std::unordered_set<frontend::TokenType> Parser::Match_Number(){
    return {frontend::TokenType::INTLTR, frontend::TokenType::FLOATLTR};    // 返回IntConst、floatConst
}

std::unordered_set<frontend::TokenType> Parser::Match_PrimaryExp(){
    auto first_lval = Match_LVal();
    auto first_number = Match_Number();
    first_lval.insert(first_number.begin(), first_number.end());
    first_lval.insert(frontend::TokenType::LPARENT);
    return first_lval;          // 返回'('、LVal、Number
}

std::unordered_set<frontend::TokenType> Parser::Match_UnaryExp(){
    auto first_primaryexp = Match_PrimaryExp();
    first_primaryexp.insert(frontend::TokenType::IDENFR);
    auto first_unaryop = Match_UnaryOp();
    first_primaryexp.insert(first_unaryop.begin(), first_unaryop.end());
    return first_primaryexp;    // 返回PrimaryExp、Ident、UnaryOp
}

std::unordered_set<frontend::TokenType> Parser::Match_UnaryOp(){
    return {frontend::TokenType::PLUS, frontend::TokenType::MINU, frontend::TokenType::NOT};    // '+'、'-'、'!'
}

std::unordered_set<frontend::TokenType> Parser::Match_FuncRParams(){
    return Match_Exp();         // 返回Exp
}

std::unordered_set<frontend::TokenType> Parser::Match_MulExp(){
    return Match_UnaryExp();    // 返回UnaryExp
}

std::unordered_set<frontend::TokenType> Parser::Match_AddExp(){
    return Match_MulExp();      // 返回MulExp
}

std::unordered_set<frontend::TokenType> Parser::Match_RelExp(){
    return Match_AddExp();      // 返回AddExp
}

std::unordered_set<frontend::TokenType> Parser::Match_EqExp(){
    return Match_RelExp();      // 返回RelExp
}

std::unordered_set<frontend::TokenType> Parser::Match_LAndExp(){
    return Match_EqExp();       // 返回EqExp
}

std::unordered_set<frontend::TokenType> Parser::Match_LOrExp(){
    return Match_LAndExp();     // 返回LAndExp
}

std::unordered_set<frontend::TokenType> Parser::Match_ConstExp(){
    return Match_AddExp();      // 返回AddExp
}


// 辅助函数，撤回上一步匹配
void Parser::retreat(int last_index, AstNode *curr_result, int target_child_nums){
    index = last_index;         // 恢复匹配前的index
    while (int(curr_result->children.size()) > target_child_nums){
        curr_result->children.pop_back();                   // 恢复到进入分支前的children数量
    }
    return;
}


// 辅助函数，用于判断某文法的构造
// CompUnit -> (Decl | FuncDef) [CompUnit]
frontend::CompUnit *Parser::parseCompUnit(AstNode *parent){ // 构造的是根节点，因此返回值不是bool型
    // ----- 构造CompUnit根节点 -----
    CompUnit *result = new CompUnit(parent);
    log(result);
    bool decl_flag = false;     // 匹配Decl
    bool funcdef_flag = false;  // 匹配FuncDef
    int last_index = index;     // 存在分支，需要保存当前index
    int target_child_nums = result->children.size();        // 记录进入分支前的children数量

    // ----- 判断分支 -----
    if (Match_Decl().count(token_stream[index].type)){      // 分支Decl
        decl_flag = parseDecl(result);
        if (!decl_flag){
            retreat(last_index, result, target_child_nums);
        }
    }
    if (!decl_flag && Match_FuncDef().count(token_stream[index].type)){ // 分支FuncDef
        funcdef_flag = parseFuncDef(result);
    }
    if (!decl_flag && !funcdef_flag){                       // 分支Decl和FuncDef都匹配失败
        assert(0 && "error in parseCompUnit");
    }

    // ----- 可选CompUnit -----
    if (Match_Compunit().count(token_stream[index].type)){
        parseCompUnit(result);
    }

    return result;
}

// Decl -> ConstDecl | VarDecl
bool Parser::parseDecl(AstNode *parent){
    // ----- 构造Decl根节点 -----
    Decl *result = new Decl(parent);
    log(result);
    bool constdecl_flag = false;
    bool vardecl_flag = false;
    int last_index = index;
    int target_child_nums = result->children.size();

    // ----- 判断分支 -----
    if (Match_ConstDecl().count(token_stream[index].type)){ // 分支ConstDecl
        constdecl_flag = parseConstDecl(result);
        if (!constdecl_flag){
            retreat(last_index, result, target_child_nums);
        }
    }
    if (!constdecl_flag && Match_VarDecl().count(token_stream[index].type)){    // 分支VarDecl
        vardecl_flag = parseVarDecl(result);
    }
    if (!constdecl_flag && !vardecl_flag){                  // 分支ConstDecl和VarDecl都匹配失败
        return false;
    }

    return true;
}

// ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
bool Parser::parseConstDecl(AstNode *parent){
    // ----- 构造ConstDecl根节点 -----
    ConstDecl *result = new ConstDecl(parent);
    log(result);

    // ----- 没有分支，直接匹配 -----
    if (token_stream[index].type != frontend::TokenType::CONSTTK){
        return false;
    }
    new Term(token_stream[index++], result);// 匹配'const'成功
    if (!parseBType(result)){               // 匹配BType失败
        return false;
    }
    if (!parseConstDef(result)){            // 匹配ConstDef失败
        return false;
    }

    // ----- 0~n次 ',' ConstDef -----
    while (token_stream[index].type == frontend::TokenType::COMMA){
        new Term(token_stream[index++], result);
        if (!parseConstDef(result)){
            return false;
        }
    }

    if (token_stream[index].type != frontend::TokenType::SEMICN){   
        return false;
    }
    new Term(token_stream[index++], result);// 匹配';'成功

    return true;
}

// BType -> 'int' | 'float'
bool Parser::parseBType(AstNode *parent){
    BType *result = new BType(parent);
    log(result);

    if (token_stream[index].type == frontend::TokenType::INTTK){
        new Term(token_stream[index++], result);
    }
    else if (token_stream[index].type == frontend::TokenType::FLOATTK){
        new Term(token_stream[index++], result);
    }
    else{
        return false;
    }

    return true;
}

// ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
bool Parser::parseConstDef(AstNode *parent){
    ConstDef *result = new ConstDef(parent);
    log(result);

    if (token_stream[index].type != frontend::TokenType::IDENFR){
        return false;
    }
    new Term(token_stream[index++], result);

    while (token_stream[index].type == frontend::TokenType::LBRACK){
        new Term(token_stream[index++], result);
        if (!parseConstExp(result)){
            return false;
        }
        if (token_stream[index].type != frontend::TokenType::RBRACK){
            return false;
        }
        new Term(token_stream[index++], result);
    }

    if (token_stream[index].type != frontend::TokenType::ASSIGN){
        return false;
    }
    new Term(token_stream[index++], result);

    if (!parseConstInitVal(result)){
        return false;
    }

    return true;
}

// ConstInitVal -> ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
bool Parser::parseConstInitVal(AstNode *parent){
    // ----- 构造ConstInitVal根节点 -----
    ConstInitVal *result = new ConstInitVal(parent);
    log(result);
    bool constexp_flag = false;
    bool lbrace_flag = false;
    int last_index = index;
    int target_child_nums = result->children.size();

    // ----- 判断分支 -----
    if (Match_ConstExp().count(token_stream[index].type)){  // 分支ConstExp
        constexp_flag = parseConstExp(result);
        if (!constexp_flag){
            retreat(last_index, result, target_child_nums);
        }
    }
    if (!constexp_flag && token_stream[index].type == frontend::TokenType::LBRACE){ // 分支'{' [ ConstInitVal { ',' ConstInitVal } ] '}'
        new Term(token_stream[index++], result);
        if (Match_ConstInitVal().count(token_stream[index].type)){  // 可选ConstInitVal { ',' ConstInitVal }
            if (!parseConstInitVal(result)){
                return false;
            }
            while (token_stream[index].type == frontend::TokenType::COMMA){ // 0~n次',' ConstInitVal
                new Term(token_stream[index++], result);
                if (!parseConstInitVal(result)){
                    return false;
                }
            }
        }
        if (token_stream[index].type != frontend::TokenType::RBRACE){
            return false;
        }
        new Term(token_stream[index++], result);
        lbrace_flag = true;
        if (!lbrace_flag){
            return false;
        }
    }
    if (!constexp_flag && !lbrace_flag){    // 分支都匹配失败
        return false;
    }

    return true;
}

// VarDecl -> BType VarDef { ',' VarDef } ';'
bool Parser::parseVarDecl(AstNode *parent){
    VarDecl *result = new VarDecl(parent);
    log(result);

    if (!parseBType(result)){
        return false;
    }

    if (!parseVarDef(result)){
        return false;
    }

    while (token_stream[index].type == frontend::TokenType::COMMA){ // 0~n次',' VarDef
        new Term(token_stream[index++], result);
        if (!parseVarDef(result)){
            return false;
        }
    }

    if (token_stream[index].type != frontend::TokenType::SEMICN){
        return false;
    }
    new Term(token_stream[index++], result);

    return true;
}

// VarDef -> Ident { '[' ConstExp ']' } [ '=' InitVal ]
bool Parser::parseVarDef(AstNode *parent){
    VarDef *result = new VarDef(parent);
    log(result);

    if (token_stream[index].type != frontend::TokenType::IDENFR){
        return false;
    }
    new Term(token_stream[index++], result);

    while (token_stream[index].type == frontend::TokenType::LBRACK){
        new Term(token_stream[index++], result);
        if (!parseConstExp(result)){
            return false;
        }

        if (token_stream[index].type != frontend::TokenType::RBRACK){
            return false;
        }
        new Term(token_stream[index++], result);
    }

    if (token_stream[index].type == frontend::TokenType::ASSIGN){
        new Term(token_stream[index++], result);
        if (!parseInitVal(result)){
            return false;
        }
    }

    return true;
}

// InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'
bool Parser::parseInitVal(AstNode *parent){
    InitVal *result = new InitVal(parent);
    log(result);
    bool exp_flag = false;
    bool lbrace_flag = false;
    int last_index = index;
    int target_child_nums = result->children.size();

    if (Match_Exp().count(token_stream[index].type)){   // 分支Exp
        exp_flag = parseExp(result);
        if (!exp_flag){
            retreat(last_index, result, target_child_nums);
        }
    }
    if (!exp_flag && token_stream[index].type == frontend::TokenType::LBRACE){  // 分支'{' [ InitVal { ',' InitVal } ] '}'
        new Term(token_stream[index++], result);

        if (Match_InitVal().count(token_stream[index].type)){
            if (!parseInitVal(result)){
                return false;
            }

            while (token_stream[index].type == frontend::TokenType::COMMA){
                new Term(token_stream[index++], result);

                if (!parseInitVal(result)){
                    return false;
                }
            }
        }

        if (token_stream[index].type != frontend::TokenType::RBRACE){
            return false;
        }
        new Term(token_stream[index++], result);
        lbrace_flag = true;
    }
    if (!lbrace_flag && !exp_flag){
        return false;
    }

    return true;
}

// FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
bool Parser::parseFuncDef(AstNode *parent){
    FuncDef *result = new FuncDef(parent);
    log(result);

    if (!parseFuncType(result)){
        return false;
    }

    if (token_stream[index].type != frontend::TokenType::IDENFR){
        return false;
    }
    new Term(token_stream[index++], result);

    if (token_stream[index].type != frontend::TokenType::LPARENT){
        return false;
    }
    new Term(token_stream[index++], result);

    if (Match_FuncFParams().count(token_stream[index].type)){
        if (!parseFuncFParams(result)){
            return false;
        }
    }

    if (token_stream[index].type != frontend::TokenType::RPARENT){
        return false;
    }
    new Term(token_stream[index++], result);

    if (!parseBlock(result)){
        return false;
    }

    return true;
}

// FuncType -> 'void' | 'int' | 'float'
bool Parser::parseFuncType(AstNode *parent){
    FuncType *result = new FuncType(parent);
    log(result);

    if (token_stream[index].type == frontend::TokenType::VOIDTK){
        new Term(token_stream[index++], result);
    }
    else if (token_stream[index].type == frontend::TokenType::INTTK){
        new Term(token_stream[index++], result);
    }
    else if (token_stream[index].type == frontend::TokenType::FLOATTK){
        new Term(token_stream[index++], result);
    }
    else{
        return false;
    }

    return true;
}

// FuncFParam -> BType Ident ['[' ']' { '[' Exp ']' }]
bool Parser::parseFuncFParam(AstNode *parent){
    FuncFParam *result = new FuncFParam(parent);
    log(result);

    if (!parseBType(result)){
        return false;
    }
    
    if (token_stream[index].type != frontend::TokenType::IDENFR){
        return false;
    }
    new Term(token_stream[index++], result);

    if (token_stream[index].type == frontend::TokenType::LBRACK){
        new Term(token_stream[index++], result);

        if (token_stream[index].type != frontend::TokenType::RBRACK){
            return false;
        }
        new Term(token_stream[index++], result);

        while (token_stream[index].type == frontend::TokenType::LBRACK){
            new Term(token_stream[index++], result);

            if (!parseExp(result)){
                return false;
            }

            if (token_stream[index].type != frontend::TokenType::RBRACK){
                return false;
            }
            new Term(token_stream[index++], result);
        }
    }

    return true;
}

// FuncFParams -> FuncFParam { ',' FuncFParam }
bool Parser::parseFuncFParams(AstNode *parent){
    FuncFParams *result = new FuncFParams(parent);
    log(result);
 
    if (!parseFuncFParam(result)){
        return false;
    }

    while (token_stream[index].type == frontend::TokenType::COMMA){
        new Term(token_stream[index++], result);

        if (!parseFuncFParam(result)){
            return false;
        }
    }

    return true;
}

// Block -> '{' { BlockItem } '}'
bool Parser::parseBlock(AstNode *parent){
    Block *result = new Block(parent);
    log(result);

    if (token_stream[index].type != frontend::TokenType::LBRACE){
        return false;
    }
    new Term(token_stream[index++], result);

    while (Match_BlockItem().count(token_stream[index].type)){
        bool blockitem_result = parseBlockItem(result);
        if (!blockitem_result){
            return false;
        }
    }

    if (token_stream[index].type != frontend::TokenType::RBRACE){
        return false;
    }
    new Term(token_stream[index++], result);

    return true;
}

// BlockItem -> Decl | Stmt
bool Parser::parseBlockItem(AstNode *parent){
    BlockItem *result = new BlockItem(parent);
    log(result);
    bool decl_flag = false;
    bool stmt_flag = false;
    int last_index = index;
    int target_child_nums = result->children.size();

    if (Match_Decl().count(token_stream[index].type)){
        decl_flag = parseDecl(result);
        if (!decl_flag){
            retreat(last_index, result, target_child_nums);
        }
    }
    if (!decl_flag && Match_Stmt().count(token_stream[index].type)){
        stmt_flag = parseStmt(result);
    }
    if (!decl_flag && !stmt_flag){
        return false;
    }

    return true;
}

// Stmt -> LVal '=' Exp ';' | Block | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] | 'while' '(' Cond ')' Stmt | 'break' ';' | 'continue' ';' | 'return' [Exp] ';' | [Exp] ';'
bool Parser::parseStmt(AstNode *parent){
    Stmt *result = new Stmt(parent);
    log(result);
    bool lval_flag = false;
    bool block_flag = false;
    bool keyword_flag = false;  // 匹配'if'、'while'、'break'、'continue'、'return'
    bool exp_flag = false;
    bool semicn_flag = false;
    int last_index = index;
    int target_child_nums = result->children.size();

    if (Match_LVal().count(token_stream[index].type)){  // 分支LVal '=' Exp ';'
        // 此处逻辑需要微调，不能像parseFuncDef一样直接return
        lval_flag = parseLVal(result);                  // LVal

        if (!lval_flag){
            retreat(last_index, result, target_child_nums);
            goto BlockCase;                             // 进入下一分支
        }

        if (token_stream[index].type != frontend::TokenType::ASSIGN){   // '='
            lval_flag = false;
            retreat(last_index, result, target_child_nums);
            goto BlockCase;
        }
        new Term(token_stream[index++], result);

        if (!parseExp(result)){                         // Exp
            lval_flag = false;
            retreat(last_index, result, target_child_nums);
            goto BlockCase;
        }

        if (token_stream[index].type != frontend::TokenType::SEMICN){   // ';'
            lval_flag = false;
            retreat(last_index, result, target_child_nums);
            goto BlockCase;
        }
        new Term(token_stream[index++], result);

        return true;
    }

    BlockCase:
    if (!lval_flag && Match_Block().count(token_stream[index].type)){   // 分支Block
        block_flag = parseBlock(result);
        if (!block_flag){
            retreat(last_index, result, target_child_nums);
        }
        else{
            return true;
        }
    }

    if (token_stream[index].type == frontend::TokenType::IFTK){ // 'if' '(' Cond ')' Stmt [ 'else' Stmt ]
        new Term(token_stream[index++], result);        // 'if'

        if (token_stream[index].type != frontend::TokenType::LPARENT){  // '('
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }
        new Term(token_stream[index++], result);

        if (!parseCond(result)){                        // Cond
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }

        if (token_stream[index].type != frontend::TokenType::RPARENT){  // ')'
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }
        new Term(token_stream[index++], result);

        if (!parseStmt(result)){                        // Stmt
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }

        if (token_stream[index].type == frontend::TokenType::ELSETK){   // [ 'else' Stmt ]
            new Term(token_stream[index++], result);    // 'else'
            if (!parseStmt(result)){                    // Stmt
                keyword_flag = false;
                retreat(last_index, result, target_child_nums);
                goto ExpCase;
            }
        }

        return true;
    }
    else if (token_stream[index].type == frontend::TokenType::WHILETK){ // 'while' '(' Cond ')' Stmt
        new Term(token_stream[index++], result);        // 'while'

        if (token_stream[index].type != frontend::TokenType::LPARENT){  // '('
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }
        new Term(token_stream[index++], result);

        if (!parseCond(result)){                        // Cond
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }

        if (token_stream[index].type != frontend::TokenType::RPARENT){  // ')'
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }
        new Term(token_stream[index++], result);

        if (!parseStmt(result)){                        // Stmt
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }

        return true;
    }
    else if (token_stream[index].type == frontend::TokenType::BREAKTK){     // 'break' ';'
        new Term(token_stream[index++], result);        // 'break'

        if (token_stream[index].type != frontend::TokenType::SEMICN){       // ';'
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }
        new Term(token_stream[index++], result);

        return true;
    }
    else if (token_stream[index].type == frontend::TokenType::CONTINUETK){  // 'continue' ';'
        new Term(token_stream[index++], result);        // 'continue'

        if (token_stream[index].type != frontend::TokenType::SEMICN){       // ';'
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }
        new Term(token_stream[index++], result);

        return true;
    }
    else if (token_stream[index].type == frontend::TokenType::RETURNTK){    // 'return' [Exp] ';'
        new Term(token_stream[index++], result);        // 'return'
        
        if (Match_Exp().count(token_stream[index].type)){                   // [Exp]
            parseExp(result);
        }

        if (token_stream[index].type != frontend::TokenType::SEMICN){       // ';'
            keyword_flag = false;
            retreat(last_index, result, target_child_nums);
            goto ExpCase;
        }
        new Term(token_stream[index++], result);
        
        return true;
    }

    ExpCase:
    if (!lval_flag && !block_flag && !keyword_flag && Match_Exp().count(token_stream[index].type)){ // 分支[Exp] ';'
        exp_flag = parseExp(result);                    // Exp

        if (exp_flag){
            if (token_stream[index].type == frontend::TokenType::SEMICN){
                new Term(token_stream[index++], result);
                return true;
            }
            else{
                exp_flag = false;
                retreat(last_index, result, target_child_nums);
                goto SEMICNCase;
            }
        }
        else{
            exp_flag = false;
            retreat(last_index, result, target_child_nums);
            goto SEMICNCase;
        }
    }

    SEMICNCase:
    if (!lval_flag && !block_flag && !keyword_flag && !exp_flag && token_stream[index].type == frontend::TokenType::SEMICN){ // ';'
        new Term(token_stream[index++], result);        // ';'
        return true;
    }

    if (!lval_flag && !block_flag && !keyword_flag && !exp_flag && !semicn_flag){
        return false;
    }

    return true;
}

// Exp -> AddExp
bool Parser::parseExp(AstNode *parent){
    Exp *result = new Exp(parent);
    log(result);

    if (!parseAddExp(result)){
        return false;
    }

    return true;
}

// Cond -> LOrExp
bool Parser::parseCond(AstNode *parent){
    Cond *result = new Cond(parent);

    if (!parseLOrExp(result)){
        return false;
    }

    return true;
}

// LVal -> Ident {'[' Exp ']'}
bool Parser::parseLVal(AstNode *parent){
    LVal *result = new LVal(parent);
    log(result);

    if (token_stream[index].type != frontend::TokenType::IDENFR){
        return false;
    }
    new Term(token_stream[index++], result);

    while (token_stream[index].type == frontend::TokenType::LBRACK){
        new Term(token_stream[index++], result);

        if (!parseExp(result)){
            return false;
        }

        if (token_stream[index].type != frontend::TokenType::RBRACK){
            return false;
        }
        new Term(token_stream[index++], result);
    }

    return true;
}

// Number -> IntConst | floatConst
bool Parser::parseNumber(AstNode *parent){
    Number *result = new Number(parent);
    log(result);

    if (token_stream[index].type != frontend::TokenType::INTLTR && token_stream[index].type != frontend::TokenType::FLOATLTR){
        return false;
    }
    new Term(token_stream[index++], result);

    return true;
}

// PrimaryExp -> '(' Exp ')' | LVal | Number
bool Parser::parsePrimaryExp(AstNode *parent){
    PrimaryExp *result = new PrimaryExp(parent);
    log(result);
    bool lparent_flag = false;
    bool lval_flag = false;
    bool number_flag = false;
    int last_index = index;
    int target_child_nums = result->children.size();

    if (token_stream[index].type == frontend::TokenType::LPARENT){          // '(' Exp ')'
        new Term(token_stream[index++], result);        // '('
        
        lparent_flag = parseExp(result);                // Exp
        if (lparent_flag && token_stream[index].type == frontend::TokenType::RPARENT){
            new Term(token_stream[index++], result);    // ')'
            return true;
        }else{
            lparent_flag = false;
            retreat(last_index, result, target_child_nums);
        }
    }
    if (!lparent_flag && Match_LVal().count(token_stream[index].type)){     // LVal
        lval_flag = parseLVal(result);
        if (!lval_flag){
            retreat(last_index, result, target_child_nums);
        }
        else{
            return true;
        }
    }
    if (!lparent_flag && !lval_flag && Match_Number().count(token_stream[index].type)){ // Number
        number_flag = parseNumber(result);
        if (!number_flag){
            retreat(last_index, result, target_child_nums);
        }
        else{
            return true;
        }
    }
    if (!lparent_flag && !lval_flag && !number_flag){
        return false;
    }

    return true;
}

// UnaryExp -> PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
/* 
bool Parser::parseUnaryExp(AstNode *parent){
    UnaryExp *result = new UnaryExp(parent);
    log(result);
    bool primaryexp_flag = false;
    bool ident_flag = false;
    bool unaryop_flag = false;
    int last_index = index;
    int target_child_nums = result->children.size();

    if (Match_PrimaryExp().count(token_stream[index].type)){
        primaryexp_flag = parsePrimaryExp(result);
        if (!primaryexp_flag){
            retreat(last_index, result, target_child_nums);
        }else{
            return true;
        }
    }

    if (!primaryexp_flag && token_stream[index].type == frontend::TokenType::IDENFR){
        new Term(token_stream[index++], result);

        if (token_stream[index].type != frontend::TokenType::LPARENT){
            ident_flag = false;
            retreat(last_index, result, target_child_nums);
            goto UnaryOpCase;
        }
        new Term(token_stream[index++], result);

        if (Match_FuncRParams().count(token_stream[index].type)){
            if (!parseFuncRParams(result)){
                ident_flag = false;
                retreat(last_index, result, target_child_nums);
                goto UnaryOpCase;
            }
        }

        if (token_stream[index].type != frontend::TokenType::RPARENT){
            ident_flag = false;
            retreat(last_index, result, target_child_nums);
            goto UnaryOpCase;
        }
        new Term(token_stream[index++], result);

        return true;
    }

    UnaryOpCase:
    if (!primaryexp_flag && !ident_flag && Match_UnaryOp().count(token_stream[index].type)){
        unaryop_flag = parseUnaryOp(result);
        if (!unaryop_flag){
            retreat(last_index, result, target_child_nums);
            return false;
        }
        
        if (!parseUnaryExp(result)){
            return false;
        }
    }

    if (!primaryexp_flag && !ident_flag && !unaryop_flag){
        return false;
    }

    return true;
}
*/
// 不要改动以下函数，否则会莫名其妙报错，来源：https://gitee.com/wangxingran222/Compiler_Theory_EXP1/blob/master/src/front/syntax.cpp
bool Parser::parseUnaryExp(AstNode *parent){ // 此函数采用纯回溯会出现问题,需要改用LL(2),所以本函数中无视分支
    UnaryExp *result = new UnaryExp(parent);
    log(result);

    if (token_stream[index].type == frontend::TokenType::IDENFR){   // Ident '(' or PrimaryExp
        if (token_stream[index + 1].type == frontend::TokenType::LPARENT){
            // Ident '('
            new Term(token_stream[index++], result);
            new Term(token_stream[index++], result);
            // 可选FuncRParams
            if (Match_FuncRParams().count(token_stream[index].type)){
                if (!parseFuncRParams(result)){
                    return false;
                }
            }
            if (token_stream[index].type != frontend::TokenType::RPARENT){
                return false;
            }
            // ')'
            new Term(token_stream[index++], result);
            return true;
        }
        else{ // PrimaryExp
            if (!parsePrimaryExp(result)){
                return false;
            }
            return true;
        }
    }
    if (Match_PrimaryExp().count(token_stream[index].type)){        // PrimaryExp
        if (!parsePrimaryExp(result)){
            return false;
        }
        return true;
    }
    if (Match_UnaryOp().count(token_stream[index].type)){           // UnaryOp UnaryExp
        if (!parseUnaryOp(result)){
            return false;
        }
        if (!parseUnaryExp(result)){
            return false;
        }
        return true;
    }
    return false;
}

// UnaryOp -> '+' | '-' | '!'
bool Parser::parseUnaryOp(AstNode *parent){
    UnaryOp *result = new UnaryOp(parent);
    log(result);

    if (token_stream[index].type != frontend::TokenType::PLUS && token_stream[index].type != frontend::TokenType::MINU && token_stream[index].type != frontend::TokenType::NOT){
        return false;
    }
    new Term(token_stream[index++], result);

    return true;
}

// FuncRParams -> Exp { ',' Exp }
bool Parser::parseFuncRParams(AstNode *parent){
    FuncRParams *result = new FuncRParams(parent);
    log(result);

    if (!parseExp(result)){
        return false;
    }

    while (token_stream[index].type == frontend::TokenType::COMMA){
        new Term(token_stream[index++], result);
        if (!parseExp(result)){
            return false;
        }
    }

    return true;
}

// MulExp -> UnaryExp { ('*' | '/' | '%') UnaryExp }
bool Parser::parseMulExp(AstNode *parent){
    MulExp *result = new MulExp(parent);
    log(result);

    if (!parseUnaryExp(result)){
        return false;
    }

    while (token_stream[index].type == frontend::TokenType::MULT || token_stream[index].type == frontend::TokenType::DIV || token_stream[index].type == frontend::TokenType::MOD){
        new Term(token_stream[index++], result);
        if (!parseUnaryExp(result)){
            return false;
        }
    }

    return true;
}

// AddExp -> MulExp { ('+' | '-') MulExp }
bool Parser::parseAddExp(AstNode *parent){
    AddExp *result = new AddExp(parent);
    log(result);

    if (!parseMulExp(result)){
        return false;
    }

    while (token_stream[index].type == frontend::TokenType::PLUS || token_stream[index].type == frontend::TokenType::MINU){
        new Term(token_stream[index++], result);
        if (!parseMulExp(result)){
            return false;
        }
    }

    return true;
}

// RelExp -> AddExp { ('<' | '>' | '<=' | '>=') AddExp }
bool Parser::parseRelExp(AstNode *parent){
    RelExp *result = new RelExp(parent);
    log(result);

    if (!parseAddExp(result)){
        return false;
    }
    
    while (token_stream[index].type == frontend::TokenType::LSS || token_stream[index].type == frontend::TokenType::GTR || token_stream[index].type == frontend::TokenType::LEQ || token_stream[index].type == frontend::TokenType::GEQ){
        new Term(token_stream[index++], result);
        if (!parseAddExp(result)){
            return false;
        }
    }

    return true;
}

// EqExp -> RelExp { ('==' | '!=') RelExp }
bool Parser::parseEqExp(AstNode *parent){
    EqExp *result = new EqExp(parent);
    log(result);

    if (!parseRelExp(result)){
        return false;
    }

    while (token_stream[index].type == frontend::TokenType::EQL || token_stream[index].type == frontend::TokenType::NEQ){
        new Term(token_stream[index++], result);
        if (!parseRelExp(result)){
            return false;
        }
    }

    return true;
}

// LAndExp -> EqExp [ '&&' LAndExp ]
bool Parser::parseLAndExp(AstNode *parent){
    LAndExp *result = new LAndExp(parent);
    log(result);

    if (!parseEqExp(result)){
        return false;
    }

    if (token_stream[index].type == frontend::TokenType::AND){
        new Term(token_stream[index++], result);

        if (!parseLAndExp(result)){
            return false;
        }
    }

    return true;
}

// LOrExp -> LAndExp [ '||' LOrExp ]
bool Parser::parseLOrExp(AstNode *parent){
    LOrExp *result = new LOrExp(parent);
    log(result);
    
    if (!parseLAndExp(result)){
        return false;
    }

    if (token_stream[index].type == frontend::TokenType::OR){
        new Term(token_stream[index++], result);
        if (!parseLOrExp(result)){
            return false;
        }
    }

    return true;
}

// ConstExp -> AddExp
bool Parser::parseConstExp(AstNode *parent){
    ConstExp *result = new ConstExp(parent);
    log(result);

    if (!parseAddExp(result)){
        return false;
    }

    return true;
}