/*词法分析
    思路同作业1，将作业1中主函数构造token数组的过程封装为Scanner::run()函数，返回token数组
*/
#include"front/lexical.h"

#include<map>
#include<cassert>
#include<string>

#define TODO assert(0 && "todo")

// #define DEBUG_DFA
// #define DEBUG_SCANNER

// 辅助函数
frontend::TokenType get_op_type(std::string s){     // 获取运算符类型
    if (s == "+")   return frontend::TokenType::PLUS;
    else if (s == "-")  return frontend::TokenType::MINU;
    else if (s == "*")  return frontend::TokenType::MULT;
    else if (s == "/")  return frontend::TokenType::DIV;
    else if (s == "%")  return frontend::TokenType::MOD;
    else if (s == "<")  return frontend::TokenType::LSS;
    else if (s == ">")  return frontend::TokenType::GTR;
    else if (s == ":")  return frontend::TokenType::COLON;
    else if (s == "=")  return frontend::TokenType::ASSIGN;
    else if (s == ";")  return frontend::TokenType::SEMICN;
    else if (s == ",")  return frontend::TokenType::COMMA;
    else if (s == "(")  return frontend::TokenType::LPARENT;
    else if (s == ")")  return frontend::TokenType::RPARENT;
    else if (s == "[")  return frontend::TokenType::LBRACK;
    else if (s == "]")  return frontend::TokenType::RBRACK;
    else if (s == "{")  return frontend::TokenType::LBRACE;
    else if (s == "}")  return frontend::TokenType::RBRACE;
    else if (s == "!")  return frontend::TokenType::NOT;
    else if (s == "<=") return frontend::TokenType::LEQ;
    else if (s == ">=") return frontend::TokenType::GEQ;
    else if (s == "==") return frontend::TokenType::EQL;
    else if (s == "!=") return frontend::TokenType::NEQ;
    else if (s == "&&") return frontend::TokenType::AND;
    else if (s == "||") return frontend::TokenType::OR;
    else    std::cout << "invalid Op:" << s << std::endl;
}

frontend::TokenType get_ident_type(std::string s){  // 获取关键字类型
    // TokenType中IDENFR、INTLTR、FLOATLTR都不是确定字符串，因此无法都在函数内判断
    if (s == "const")   return frontend::TokenType::CONSTTK;
    else if (s == "void")   return frontend::TokenType::VOIDTK;
    else if (s == "int")    return frontend::TokenType::INTTK;
    else if (s == "float")  return frontend::TokenType::FLOATTK;
    else if (s == "if")     return frontend::TokenType::IFTK;
    else if (s == "else")   return frontend::TokenType::ELSETK;
    else if (s == "while")  return frontend::TokenType::WHILETK;
    else if (s == "continue")   return frontend::TokenType::CONTINUETK;
    else if (s == "break")  return frontend::TokenType::BREAKTK;
    else if (s == "return") return frontend::TokenType::RETURNTK;
    else    return frontend::TokenType::IDENFR;     // 函数名或变量名
}

bool isCharOp(char c){
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='<'||c=='>'||c=='='||c==':'||c==';'||c=='('||c==')'||c=='['||c==']'||c=='{'||c=='}'||c=='!'||c=='&'||c=='|'||c==','){
        return true;
    }else{
        return false;
    }
}

bool isStringOp(std::string s){
    if(s=="+"||s=="-"||s=="*"||s=="/"||s=="%"||s=="<"||s==">"||s=="="||s==":"||s==";"||s=="("||s==")"||s=="["||s=="]"||s=="{"||s=="}"||s=="!"||s=="&"||s=="|"||s==","||s=="<="||s==">="||s=="=="||s=="!="||s=="&&"||s=="||"){
        return true;
    }else{
        return false;
    }
}

std::string frontend::toString(State s) {
    switch (s) {
    case State::Empty: return "Empty";
    case State::Ident: return "Ident";
    case State::IntLiteral: return "IntLiteral";
    case State::FloatLiteral: return "FloatLiteral";
    case State::op: return "op";
    default:
        assert(0 && "invalid State");
    }
    return "";
}

std::set<std::string> frontend::keywords= {
    "const", "int", "float", "if", "else", "while", "continue", "break", "return", "void"
};

std::string preScanner(std::ifstream &fin){        // Scanner的辅助函数，返回去除注释的字符串
    std::string result;
    std::string line;
    bool inMultiLineComment = false;    // 当前位于多行注释内部
    while (std::getline(fin, line)) {
        size_t pos = 0;
        if (inMultiLineComment) {       // 在多行注释内部时需要查找结束位置
            pos = line.find("*/");
            if (pos != std::string::npos) {
                inMultiLineComment = false;
                line.erase(0, pos + 2); // 移除"*/"前的内容
            } else {
                continue;               // 跳过当前行，继续读取下一行
            }
        }
        while (pos != std::string::npos) {
            // 查找单行注释和多行注释的起始位置
            size_t posSingle = line.find("//", pos);
            size_t posMulti = line.find("/*", pos);
            if (posSingle == pos) {     // 单行注释在本行内
                line.erase(pos);        // 移除"//"后的所有内容
                break;                  // 不再查找其他注释
            }
            else if (posMulti == pos) { // 多行注释在本行内
                size_t posMultiEnd = line.find("*/", posMulti + 2);     // 查找多行注释结束位置
                if (posMultiEnd != std::string::npos) {
                    line.erase(posMulti, posMultiEnd - posMulti + 2);   // 移除多行注释
                }
                else {
                    line.erase(posMulti);           // 移除多行注释后的内容
                    inMultiLineComment = true;
                }
                break;                  // 不再查找其他注释
            }
            pos = std::min(posSingle, posMulti);    // 更新 pos，查找下一个注释的起始位置
        }
        result += line+"\n";            // 将处理后的行添加到结果字符串中
    }
    return result;
}

// 待定义函数
frontend::DFA::DFA(): cur_state(frontend::State::Empty), cur_str() {}

frontend::DFA::~DFA() {}

bool frontend::DFA::next(char input, Token& buf) {
    // 打印当前状态
    #ifdef DEBUG_DFA
    #include<iostream>
        std::cout << "in state [" << toString(cur_state) << "], input = \'" << input << "\', str = " << cur_str << "\t";
    #endif
    // 核心函数
    bool flag = false;      // 不直接返回true/false，否则结尾的"next state"无法输出
    switch (cur_state){
        case frontend::State::Empty:    // State刚被reset过
            if (isspace(input)){                    // 维持Empty状态
                reset();
                break;
            }
            else if (isalpha(input) || input=='_'){ // 转换到Ident状态(a~z、A~Z、_)
                cur_state = frontend::State::Ident;
                cur_str += input;
                break;
            }
            else if (isdigit(input)){               // 转换到IntLiteral状态
                cur_state = frontend::State::IntLiteral;
                cur_str += input;
                break;
            }
            else if (input == '.'){                 // 转换到FloatLiteral状态
                cur_state = frontend::State::FloatLiteral;
                cur_str += input;
                break;
            }
            else if (isCharOp(input)){              // 转换到op状态
                cur_state = frontend::State::op;
                cur_str += input;
                break;
            }
            else{                                   // 状态转换非法
                assert(0 && "invalid next State");
                break;
            }
        case frontend::State::Ident:
            if (isspace(input)){                    // 转换到Empty状态
                buf.type = get_ident_type(cur_str);
                buf.value = cur_str;
                reset();
                flag = true;
                break;
            }
            else if (isalpha(input) || isdigit(input) || input == '_'){ // 维持Ident状态
                cur_str += input;
                break;
            }
            else if (isCharOp(input)){              // 转换到Op状态
                buf.type = get_ident_type(cur_str);
                buf.value = cur_str;                // 将此前字符串同步至buf以供输出
                cur_state = frontend::State::op;
                cur_str = input;
                flag = true;
                break;
            }
            else{                                   // 其余转换均非法
                assert(0 && "invalid next State");
                break;
            }
        case frontend::State::op:
            if (isspace(input)){                    // 转换到Empty状态
                buf.type = get_op_type(cur_str);
                buf.value = cur_str;
                reset();
                flag = true;
                break;
            }
            else if (isalpha(input) || input=='_'){ // 转换到Ident状态
                buf.type = get_op_type(cur_str);
                buf.value = cur_str;
                cur_state = frontend::State::Ident;
                cur_str = input;
                flag = true;
                break;
            }
            else if (isdigit(input)){               // 转换到IntLiteral状态
                buf.type = get_op_type(cur_str);
                buf.value = cur_str;
                cur_state = frontend::State::IntLiteral;
                cur_str = input;
                flag = true;
                break;
            }
            else if (input == '.'){                 // 转换到FloatLiteral状态
                buf.type = get_op_type(cur_str);
                buf.value = cur_str;
                cur_state = frontend::State::FloatLiteral;
                cur_str = input;
                flag = true;
                break;
            }
            else if (isCharOp(input)){              // 维持Op状态
                if (isStringOp(cur_str + input)){
                    cur_str += input;
                    break;
                }
                else{       // 已经获得完整操作符
                    buf.type = get_op_type(cur_str);
                    buf.value = cur_str;
                    cur_state = frontend::State::op;
                    cur_str = input;
                    flag = true;
                    break;
                }
            }
            else{                                   // 其余转换均非法
                assert(0 && "invalid next State");
                break;
            }
        case frontend::State::IntLiteral:
            if (isspace(input)){                    // 转换到Empty状态
                buf.type = frontend::TokenType::INTLTR;
                buf.value = cur_str;
                reset();
                flag = true;
                break;
            }
            else if (isdigit(input) || (input >= 'a' && input <= 'f') || (input >= 'A' && input <= 'F') || input == 'x' || input == 'X'){   // 维持IntLiteral状态
                cur_str += input;
                break;
            }
            else if (input == '.'){                 // 转换到FloatLiteral状态
                cur_state = frontend::State::FloatLiteral;
                cur_str += input;
                break;
            }
            else if (isCharOp(input)){              // 转换到Op状态
                buf.type = frontend::TokenType::INTLTR;
                buf.value = cur_str;
                cur_state = frontend::State::op;
                cur_str = input;
                flag = true;
                break;
            }
            else{                                   // 其余转换均非法
                assert(0 && "invalid next State");
                break;
            }
        case frontend::State::FloatLiteral:
            if (isspace(input)){                    // 转换到Empty状态
                buf.type = frontend::TokenType::FLOATLTR;
                buf.value = cur_str;
                reset();
                flag = true;
                break;
            }
            else if (isdigit(input)){               // 转换到FloatLiteral状态
                cur_str += input;
                break;
            }            
            else if (isCharOp(input)){              // 转换到Op状态
                buf.type = frontend::TokenType::FLOATLTR;
                buf.value = cur_str;
                cur_state = frontend::State::op;
                cur_str = input;
                flag = true;
                break;
            }
            else{                                   // 其余转换均非法
                assert(0 && "invalid next State");
                break;
            }
        default: assert(0 && "invalid State");
    }
    // 打印下一个状态
    #ifdef DEBUG_DFA
        std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
    #endif

    return flag;
}

void frontend::DFA::reset() {
    cur_state = State::Empty;
    cur_str = "";
}

frontend::Scanner::Scanner(std::string filename): fin(filename) {
    if(!fin.is_open()) {
        assert(0 && "in Scanner constructor, input file cannot open");
    }
}

frontend::Scanner::~Scanner() {
    fin.close();
}

std::vector<frontend::Token> frontend::Scanner::run() { // 使用DFA接受字符串前需要对字符串进行预处理
    std::vector<Token> result;
    Token tk;
    DFA dfa;
    std::string s = preScanner(fin);    // 删除注释
    s += "\n";                          // s结尾加上换行符
    for (auto c : s){
        if (dfa.next(c, tk)){
            // 压入token
            result.push_back(tk);
            // 打印结果
            #ifdef DEBUG_SCANNER
            #include <iostream>
                std::cout << "token: " << toString(tk.type) << "\t" << tk.value << std::endl;
            #endif
        }
    }
    return result;
}