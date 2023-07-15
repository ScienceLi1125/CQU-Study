#include"front/token.h"

#include<cassert>

std::string frontend::toString(frontend::TokenType type){
    switch (type) {
    case TokenType::IDENFR: return "IDENFR";
    case TokenType::INTLTR: return "INTLTR";
    case TokenType::FLOATLTR: return "FLOATLTR";
    case TokenType::CONSTTK: return "CONSTTK";
    case TokenType::VOIDTK: return "VOIDTK";
    case TokenType::INTTK: return "INTTK";
    case TokenType::FLOATTK: return "FLOATTK";
    case TokenType::IFTK: return "IFTK";
    case TokenType::ELSETK: return "ELSETK";
    case TokenType::WHILETK: return "WHILETK";
    case TokenType::CONTINUETK: return "CONTINUETK";
    case TokenType::BREAKTK: return "BREAKTK";
    case TokenType::RETURNTK: return "RETURNTK";
    case TokenType::PLUS: return "PLUS";
    case TokenType::MINU: return "MINU";
    case TokenType::MULT: return "MULT";
    case TokenType::DIV: return "DIV";
    case TokenType::MOD: return "MOD";
    case TokenType::LSS: return "LSS";
    case TokenType::GTR: return "GTR";
    case TokenType::COLON: return "COLON";
    case TokenType::ASSIGN: return "ASSIGN";
    case TokenType::SEMICN: return "SEMICN";
    case TokenType::COMMA: return "COMMA";
    case TokenType::LPARENT: return "LPARENT";
    case TokenType::RPARENT: return "RPARENT";
    case TokenType::LBRACK: return "LBRACK";
    case TokenType::RBRACK: return "RBRACK";
    case TokenType::LBRACE: return "LBRACE";
    case TokenType::RBRACE: return "RBRACE";
    case TokenType::NOT: return "NOT";
    case TokenType::LEQ: return "LEQ";
    case TokenType::GEQ: return "GEQ";
    case TokenType::EQL: return "EQL";
    case TokenType::NEQ: return "NEQ";
    case TokenType::AND: return "AND";
    case TokenType::OR: return "OR";
    default:
        assert(0 && "invalid token type");
        break;
    }
    return "";
}