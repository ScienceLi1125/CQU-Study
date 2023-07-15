// 在Parser中增加Match_XX、retreat和parseXX的函数声明
/**
 * @file syntax.h
 * @author Yuntao Dai (d1581209858@live.com)
 * @brief 
 * in the second part, we already has a token stream, now we should analysis it and result in a syntax tree, 
 * which we also called it AST(abstract syntax tree)
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SYNTAX_H
#define SYNTAX_H

#include"front/abstract_syntax_tree.h"
#include"front/token.h"

#include<vector>
#include<unordered_set>

namespace frontend {

// definition of Parser
// a parser should take a token stream as input, then parsing it, output a AST
struct Parser {
    uint32_t index; // current token index
    const std::vector<Token>& token_stream;

    /**
     * @brief constructor
     * @param tokens: the input token_stream
     */
    Parser(const std::vector<Token>& tokens);

    /**
     * @brief destructor
     */
    ~Parser();
    
    /**
     * @brief creat the abstract syntax tree
     * @return the root of abstract syntax tree
     */
    CompUnit* get_abstract_syntax_tree();

    CompUnit *parseCompUnit(AstNode *parent);
    bool parseDecl(AstNode *parent);
    bool parseFuncDef(AstNode *parent);
    bool parseConstDecl(AstNode *parent);
    bool parseVarDecl(AstNode *parent);
    bool parseBType(AstNode *parent);
    bool parseConstDef(AstNode *parent);
    bool parseConstInitVal(AstNode *parent);
    bool parseConstExp(AstNode *parent);
    bool parseTerm(AstNode *parent);
    bool parseVarDef(AstNode *parent);
    bool parseInitVal(AstNode *parent);
    bool parseExp(AstNode *parent);
    bool parseFuncType(AstNode *parent);
    bool parseFuncFParams(AstNode *parent);
    bool parseBlock(AstNode *parent);
    bool parseFuncFParam(AstNode *parent);
    bool parseBlockItem(AstNode *parent);
    bool parseStmt(AstNode *parent);
    bool parseLVal(AstNode *parent);
    bool parseCond(AstNode *parent);
    bool parseAddExp(AstNode *parent);
    bool parseLOrExp(AstNode *parent);
    bool parseNumber(AstNode *parent);
    bool parsePrimaryExp(AstNode *parent);
    bool parseUnaryExp(AstNode *parent);
    bool parseUnaryOp(AstNode *parent);
    bool parseFuncRParams(AstNode *parent);
    bool parseMulExp(AstNode *parent);
    bool parseRelExp(AstNode *parent);
    bool parseEqExp(AstNode *parent);
    bool parseLAndExp(AstNode *parent);

    void retreat(int saved_index, AstNode* curr_result, int target_child_nums);

    std::unordered_set<frontend::TokenType> Match_Compunit();
    std::unordered_set<frontend::TokenType> Match_Decl();
    std::unordered_set<frontend::TokenType> Match_ConstDecl();
    std::unordered_set<frontend::TokenType> Match_BType();
    std::unordered_set<frontend::TokenType> Match_ConstDef();
    std::unordered_set<frontend::TokenType> Match_ConstInitVal();
    std::unordered_set<frontend::TokenType> Match_VarDecl();
    std::unordered_set<frontend::TokenType> Match_VarDef();
    std::unordered_set<frontend::TokenType> Match_InitVal();
    std::unordered_set<frontend::TokenType> Match_FuncDef();
    std::unordered_set<frontend::TokenType> Match_FuncType();
    std::unordered_set<frontend::TokenType> Match_FuncFParam();
    std::unordered_set<frontend::TokenType> Match_FuncFParams();
    std::unordered_set<frontend::TokenType> Match_Block();
    std::unordered_set<frontend::TokenType> Match_BlockItem(); // 1
    std::unordered_set<frontend::TokenType> Match_Stmt();
    std::unordered_set<frontend::TokenType> Match_Exp();
    std::unordered_set<frontend::TokenType> Match_Cond();
    std::unordered_set<frontend::TokenType> Match_LVal();
    std::unordered_set<frontend::TokenType> Match_Number();
    std::unordered_set<frontend::TokenType> Match_PrimaryExp();
    std::unordered_set<frontend::TokenType> Match_UnaryExp();
    std::unordered_set<frontend::TokenType> Match_UnaryOp();
    std::unordered_set<frontend::TokenType> Match_FuncRParams();
    std::unordered_set<frontend::TokenType> Match_MulExp();
    std::unordered_set<frontend::TokenType> Match_AddExp();
    std::unordered_set<frontend::TokenType> Match_RelExp();
    std::unordered_set<frontend::TokenType> Match_EqExp();
    std::unordered_set<frontend::TokenType> Match_LAndExp();
    std::unordered_set<frontend::TokenType> Match_LOrExp();
    std::unordered_set<frontend::TokenType> Match_ConstExp();

    /**
     * @brief for debug, should be called in the beginning of recursive descent functions 
     * @param node: current parsing node 
     */
    void log(AstNode* node);
};

} // namespace frontend

#endif