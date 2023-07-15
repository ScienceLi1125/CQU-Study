/**
 * @file Token.h
 * @author Yuntao Dai (d1581209858@live.com)
 * @brief 
 * definition of Token
 * a Token should has its type and its value(the string)
 * @version 0.1
 * @date 2022-12-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TOKEN_H
#define TOKEN_H

#include<string>

namespace frontend {

// enumerate for Token type
enum class TokenType{
    IDENFR,     // identifier	
    INTLTR,		// int literal
    FLOATLTR,		// float literal
    CONSTTK,		// const
    VOIDTK,		// void
    INTTK,		// int
    FLOATTK,		// float
    IFTK,		// if
    ELSETK,		// else
    WHILETK,		// while
    CONTINUETK,		// continue
    BREAKTK,		// break
    RETURNTK,		// return
    PLUS,		// +
    MINU,		// -
    MULT,		// *
    DIV,		// /
    MOD,      // %
    LSS,		// <
    GTR,		// >
    COLON,		// :
    ASSIGN,		// =
    SEMICN,		// ;
    COMMA,		// ,
    LPARENT,		// (
    RPARENT,		// )
    LBRACK,		// [
    RBRACK,		// ]
    LBRACE,		// {
    RBRACE,		// }
    NOT,		// !
    LEQ,		// <=
    GEQ,		// >=
    EQL,		// ==
    NEQ,		// !=
    AND,        // &&
    OR,         // ||
};
std::string toString(TokenType);

struct Token {
    TokenType type;
    std::string value;
};


} // namespace frontend


#endif