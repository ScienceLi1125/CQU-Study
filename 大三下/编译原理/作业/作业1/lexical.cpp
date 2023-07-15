/*词法分析
【问题描述】
	对标准输入的四则运算表达式字符串进行词法分析，得到 Token 串。请注意并不是每一次状态转移都伴随着输出，所以只有当该函数返回 true 时表示 buf 是一个合法输出，main 函数在此时将自动状态机的输出打印到 stdout。
【输入形式】
	从 stdin 输入，每个测试用例一行，如：
100 - 10 / 2 
(0x101 + 01100 / 4)- 017 * (019 - 178)
【输出形式】
	对得到的 Token 串，每行输出一个 Token，输出 TokenType [空格] TokenValue。如：
INTLTR 101
【样例输入】
100 - 10 / 2
【样例输出】
INTLTR 100
MINU -
INTLTR 10
DIV /
INTLTR 2
【设计思路】
	使用有限状态机模型，在不同状态下处理对应的 Token 并转移状态，使用 cur_str 和 cur_state 分别记录当前字符串和状态。词法分析阶段只管分词，不考虑语法问题。
	因为 INTLTR 型分词只有在接收到非 INTLTR 型输入时才能够跳出 IntLiteral 状态，所以所有分词获取成功后都在下一状态输出。返回 true 表示即将输出 buf，只有返回 true 前才更新 buf.value 和 buf.type。为了最后一个分词能够输出，在 stdin_str 末尾加上了 "\n"。
状态转移如下：
    Empty：输入 INTLTR 转变为 IntLiteral；输入运算符转变为 op；否则不变；
    IntLiteral：输入 INTLTR 不变；输入其他时表示此前已经找到一个完整的 Token，可以返回 true；
    op：输入 INTLTR 转变为 IntLiteral；输入运算符转变为 op；否则为 Empty；此时一定返回 true，因为前一个状态为操作符时一定可以输出；
返回 true 前需要将 cur_str 赋给 buf.value，并调用 get_op_type 函数赋值 buf.type，然后调用 reset 函数。返回 true 时接收的输入（即当时的 input）被保存在 cur_str 中，不会被丢弃。
*/

#include<map>
#include<cassert>
#include<string>
#include<iostream>

#define TODO assert(0 && "TODO")
// #define DEBUG_DFA

// enumerate for State
enum class State {
    Empty,		// space, \n, \r ...
    IntLiteral,	// int literal, like '1', '01900', '0xAB', '0b11001'
    op			// operators and '(', ')'
};
// translate State to string
std::string toString(State s) {
    switch (s) {
	    case State::Empty: return "Empty";
	    case State::IntLiteral: return "IntLiteral";
	    case State::op: return "op";
	    default: assert(0 && "invalid  State");
	}
    return "";
}

// enumerate for Token type
enum class TokenType{
    INTLTR,		// int literal
    PLUS,		// +
    MINU,		// -
    MULT,		// *
    DIV,		// /
    LPARENT,	// (
    RPARENT,	// )
};
// translate TokenType to string
std::string toString(TokenType type) {
    switch (type) {
	    case TokenType::INTLTR: return "INTLTR";
	    case TokenType::PLUS: return "PLUS";
	    case TokenType::MINU: return "MINU";
	    case TokenType::MULT: return "MULT";
	    case TokenType::DIV: return "DIV";
	    case TokenType::LPARENT: return "LPARENT";
	    case TokenType::RPARENT: return "RPARENT";
	    default: assert(0  &&  "invalid  token  type");
	    break;
    }
    return "";
}

// definition of Token
struct Token {
	TokenType type;
    std::string value;
};

// definition of DFA
struct DFA {
    /**
      * @brief constructor, set the init state to State::Empty
      */
    DFA();
    /**
      * @brief destructor
      */
    ~DFA();
    // the meaning of copy and assignment for a DFA is not clear, so we do not allow them
    DFA(const  DFA&) = delete;      		// copy constructor
    DFA& operator=(const DFA&) = delete;   	// assignment

    /**
      * @brief take a char as input, change state to next state, and output a Token if necessary
      * @param[in] input: the input character
      * @param[out] buf: the output Token buffer
      * @return: return true if a Token is produced, the buf is valid then
      */
    bool next(char input, Token& buf);
    
    /**
      * @brief reset the DFA state to begin
      */
    void  reset();

private:
    State cur_state;        // record current state of the DFA
    std::string cur_str;    // record current string composed of input characters
};


DFA::DFA(): cur_state(State::Empty), cur_str() {}

DFA::~DFA() {}

/**
  * @brief: get buf.type from cur_str which only consists of operator or digits
  * @param s: current string
  * @return: return TokenType of cur_str
  */
TokenType get_op_type(std::string s)  {
    if(s == "("){
        return TokenType::LPARENT;
    }else if(s == ")"){
        return TokenType::RPARENT;
    }else if(s == "+"){
        return TokenType::PLUS;
    }else if(s == "-"){
        return TokenType::MINU;
    }else if(s == "*"){
        return TokenType::MULT;
    }else if(s == "/"){
        return TokenType::DIV;
    }else{
    	return TokenType::INTLTR;
	}
}

bool DFA::next(char input, Token& buf)  {
    switch(cur_state){      // current state may shift after inputting char
        case State::Empty:      // previous state was reset
            if(input == '('){
                cur_str = "(";
                cur_state = State::op;
                return false;           // return false to continue loop in main function
            }else if(input == ')'){
                cur_str = ")";
                cur_state = State::op;
                return false;
            }else if(input == '+'){
                cur_str = "+";
                cur_state = State::op;
                return false;
            }else if(input == '-'){
                cur_str = "-";
                cur_state = State::op;
                return false;
            }else if(input == '*'){
                cur_str = "*";
                cur_state = State::op;
                return false;
            }else if(input == '/'){
                cur_str = "/";
                cur_state = State::op;
                return false;
            }else if(input >= '0' && input <= '9'){
                cur_str = std::string(1,input);
                cur_state = State::IntLiteral;
                return false;
            }else{                  // remain `State::Empty`
                return false;
            }
        case State::op:         // return true to output previous operator
            buf.value = cur_str;		// assign buf with cur_str and its type 
            buf.type = get_op_type(cur_str);
            if(input >= '0' && input <= '9'){
            	cur_state = State::IntLiteral;
                cur_str = std::string(1, input);
            }else if(input == '+' || input == '-' || input == '*' || input == '/' || input == '(' || input == ')'){
                cur_str = std::string(1, input);
            }else{
                reset();
			}
            return true;
        case State::IntLiteral:
            if((input >= '0' && input <= '9') || (input >= 'A' && input <= 'F') || (input >= 'a' && input <= 'f') || input == 'x' || input == 'X'){
                cur_str.push_back(input);	
                return false;				// remain `State::IntLiteral`
            }else if(input == '+' || input == '-' || input == '*' || input == '/' || input == '(' || input == ')'){
                buf.value = cur_str;
                buf.type = get_op_type(cur_str);
                cur_state = State::op;
                cur_str = std::string(1, input);
                return true;				// return true to output previous digits
            }else{
            	buf.value = cur_str;
            	buf.type = get_op_type(cur_str);
                reset();
                return true;				// return true to output previous digits
			}
		default: return false;
    }
}

void DFA::reset()  {
    cur_state = State::Empty;
    cur_str = "";
}

int main(){
    std::string stdin_str;
    std::getline(std::cin, stdin_str);
    stdin_str += "\n";
    DFA dfa;
    Token tk;
    for(size_t i = 0; i < stdin_str.size(); i++)  {
        if(dfa.next(stdin_str[i], tk)){
            std::cout << toString(tk.type) <<"  "<< tk.value << std::endl;
        }
    }
    return 0;
}