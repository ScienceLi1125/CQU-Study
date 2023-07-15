// 修改AstNode构造函数，加入push_back操作
#include"front/abstract_syntax_tree.h"
#include"ir/ir.h"

#include<cassert>

using frontend::AstNode;
using frontend::Term;
using frontend::CompUnit;
using frontend::Decl;
using frontend::FuncDef;
using frontend::ConstDecl;
using frontend::BType;
using frontend::ConstDef;
using frontend::ConstInitVal;
using frontend::VarDecl;
using frontend::VarDef;
using frontend::InitVal;
using frontend::FuncType;
using frontend::FuncFParam;
using frontend::FuncFParams;
using frontend::Block;
using frontend::BlockItem;
using frontend::Stmt;
using frontend::Exp;
using frontend::Cond;
using frontend::LVal;
using frontend::Number;
using frontend::PrimaryExp;
using frontend::UnaryExp;
using frontend::UnaryOp;
using frontend::FuncRParams;
using frontend::MulExp;
using frontend::AddExp;
using frontend::RelExp;
using frontend::EqExp;
using frontend::LAndExp;
using frontend::LOrExp;
using frontend::ConstExp;

AstNode::AstNode(NodeType t, AstNode* p): type(t), parent(p), children() {
    if(p != nullptr)    p->children.push_back(this);   // 修改构造函数
}

AstNode::~AstNode() {
    for(auto it: children)
        delete it;
}

void AstNode::get_json_output(Json::Value& root) const {
    root["name"] = toString(type);
    if (type == NodeType::TERMINAL) {
        auto termP = dynamic_cast<Term*>(const_cast<AstNode*>(this));
        assert(termP);
        root["type"] = toString(termP->token.type);
        root["value"] = termP->token.value;
    }
    else {
        root["subtree"] = Json::Value();
        for(const auto& node: children) {
            Json::Value tmp;
            node->get_json_output(tmp);
            root["subtree"].append(tmp);
        }
    }
}

Term::Term(Token t, AstNode* p): AstNode(NodeType::TERMINAL, p), token(t) {}

CompUnit::CompUnit(AstNode* p): AstNode(NodeType::COMPUINT, p) {}

Decl::Decl(AstNode* p): AstNode(NodeType::DECL, p) {}

FuncDef::FuncDef(AstNode* p): AstNode(NodeType::FUNCDEF, p) {}

ConstDecl::ConstDecl(AstNode* p): AstNode(NodeType::CONSTDECL, p) {}

BType::BType(AstNode* p): AstNode(NodeType::BTYPE, p) {}

ConstDef::ConstDef(AstNode* p): AstNode(NodeType::CONSTDEF, p) {}

ConstInitVal::ConstInitVal(AstNode* p): AstNode(NodeType::CONSTINITVAL, p) {}

VarDecl::VarDecl(AstNode* p): AstNode(NodeType::VARDECL, p) {}

VarDef::VarDef(AstNode* p): AstNode(NodeType::VARDEF, p) {}

InitVal::InitVal(AstNode* p): AstNode(NodeType::INITVAL, p) {}

FuncType::FuncType(AstNode* p): AstNode(NodeType::FUNCTYPE, p) {}

FuncFParam::FuncFParam(AstNode* p): AstNode(NodeType::FUNCFPARAM, p) {}

FuncFParams::FuncFParams(AstNode* p): AstNode(NodeType::FUNCFPARAMS, p) {}

Block::Block(AstNode* p): AstNode(NodeType::BLOCK, p) {}

BlockItem::BlockItem(AstNode* p): AstNode(NodeType::BLOCKITEM, p) {}

Stmt::Stmt(AstNode* p): AstNode(NodeType::STMT, p) {}

Exp::Exp(AstNode* p): AstNode(NodeType::EXP, p) {}

Cond::Cond(AstNode* p): AstNode(NodeType::COND, p) {}

LVal::LVal(AstNode* p): AstNode(NodeType::LVAL, p) {}

Number::Number(AstNode* p): AstNode(NodeType::NUMBER, p) {}

PrimaryExp::PrimaryExp(AstNode* p): AstNode(NodeType::PRIMARYEXP, p) {}

UnaryExp::UnaryExp(AstNode* p): AstNode(NodeType::UNARYEXP, p) {}

UnaryOp::UnaryOp(AstNode* p): AstNode(NodeType::UNARYOP, p) {}

FuncRParams::FuncRParams(AstNode* p): AstNode(NodeType::FUNCRPARAMS, p) {}

MulExp::MulExp(AstNode* p): AstNode(NodeType::MULEXP, p) {}

AddExp::AddExp(AstNode* p): AstNode(NodeType::ADDEXP, p) {}

RelExp::RelExp(AstNode* p): AstNode(NodeType::RELEXP, p) {}

EqExp::EqExp(AstNode* p): AstNode(NodeType::EQEXP, p) {}

LAndExp::LAndExp(AstNode* p): AstNode(NodeType::LANDEXP, p) {}

LOrExp::LOrExp(AstNode* p): AstNode(NodeType::LOREXP, p) {}

ConstExp::ConstExp(AstNode* p): AstNode(NodeType::CONSTEXP, p) {}

std::string frontend::toString(NodeType nt) {
    switch (nt) {
    case NodeType::TERMINAL: return "Terminal";
    case NodeType::COMPUINT: return "CompUnit";
    case NodeType::DECL: return "Decl";
    case NodeType::FUNCDEF: return "FuncDef";
    case NodeType::CONSTDECL: return "ConstDecl";
    case NodeType::BTYPE: return "BType";
    case NodeType::CONSTDEF: return "ConstDef";
    case NodeType::CONSTINITVAL: return "ConstInitVal";
    case NodeType::VARDECL: return "VarDecl";
    case NodeType::VARDEF: return "VarDef";
    case NodeType::INITVAL: return "InitVal";
    case NodeType::FUNCTYPE: return "FuncType";
    case NodeType::FUNCFPARAM: return "FuncFParam";
    case NodeType::FUNCFPARAMS: return "FuncFParams";
    case NodeType::BLOCK: return "Block";
    case NodeType::BLOCKITEM: return "BlockItem";
    case NodeType::STMT: return "Stmt";
    case NodeType::EXP: return "Exp";
    case NodeType::COND: return "Cond";
    case NodeType::LVAL: return "LVal";
    case NodeType::NUMBER: return "Number";
    case NodeType::PRIMARYEXP: return "PrimaryExp";
    case NodeType::UNARYEXP: return "UnaryExp";
    case NodeType::UNARYOP: return "UnaryOp";
    case NodeType::FUNCRPARAMS: return "FuncRParams";
    case NodeType::MULEXP: return "MulExp";
    case NodeType::ADDEXP: return "AddExp";
    case NodeType::RELEXP: return "RelExp";
    case NodeType::EQEXP: return "EqExp";
    case NodeType::LANDEXP: return "LAndExp";
    case NodeType::LOREXP: return "LOrExp";
    case NodeType::CONSTEXP: return "ConstExp";
    default:
        assert(0 && "invalid node type");
        break;
    }
    return "";
}