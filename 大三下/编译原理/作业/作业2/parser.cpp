/*语法分析
【问题描述】
	对标准输入的四则运算表达式字符串词法分析得到 Token 串进行分析，构造一棵语法树，并计算四则运算表达式的值。本次作业需要在上一次作业的基础上完成语法解析器 Parser 的实现，其核心是 AstNode* get_abstract_syntax_tree() 函数，它应该对 token 串进行分析并构造一棵语法树。
	框架定义好了语法树相关的数据结构和枚举类，可以看到 AstNode 有一个 int value 成员变量，它代表以该节点为根节点的子树所代表的表达式的运算结果，你应该在构建语法树的过程中或者构建完成后的语义分析中填充该变量的值，在 main 函数中将输出语法树 root 的 value 作为你的答案。
	运算表达式的文法为：
Exp -> AddExp
Number -> IntConst | floatConst
PrimaryExp -> '(' Exp ')' | Number
UnaryExp -> PrimaryExp | UnaryOp UnaryExp
UnaryOp -> '+' | '-'
MulExp -> UnaryExp { ('*' | '/') UnaryExp }
AddExp -> MulExp { ('+' | '-') MulExp }
	为了调试与观察语法树的构建过程，框架提供了 log 函数帮助本地编写代码时调试，具体请 RTFSC
【样例输入】
100 - 11 / 2
【样例输出】
95
【测试点】
in:
101  - 10 / 2
0b10111000 / 0b1000 * 0b11
(3)
0177 + 0777 - 021 * 5
0xAF + 0x1000 + 0x1B
100 - 3 /4
100  /  (24-28)
(76 - 99 * 0) - 66 / 3
88 - (99 - 88) / 11 * 8 - -20
(1 + 2 + (3 + 4) - 10) + 9 *(2*50 - 4*25 + 1) +(8 - 11 * 8) / (100/5+47-(18 - -19) + 110 / 10 -1) + 9
out:
96
69
3
553
4298
100
-25
54
100
16
【设计思路】
    由文法规则可知：IntConst、floatConst、'+'、'-' 为终结符，节点类型为 TERMINAL，节点值可以强制转换为 int；其余为非终结符，节点类型即为名称，无需设置节点值。
    语法分析时，按照当前 Token 类型选择合适的文法进行匹配。选择合适文法时，可以借助当前 Token 类型判断，如 `UnaryExp -> PrimaryExp | UnaryOp UnaryExp` 就可以判断当前 Token 是否是 '+' 或 '-' 得知是否是 `UnaryExp -> | UnaryOp UnaryExp`。
	主函数中，先调用词法分析，将分词结果存入 vector。然后调用语法分析，对 vector 中 token 进行读取，根据文法规则构建 AST。最后调用外部函数 get_value 递归求解得到 AST 根节点的值。
*/
#include<map>
#include<cassert>
#include<string>
#include<iostream>
#include<vector>
#include<set>
#include<queue>

#define  TODO  assert(0  &&  "TODO")
//  #define  DEBUG_DFA
//  #define  DEBUG_PARSER

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
enum class TokenType {
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
	    default: assert(0 && "invalid token type");
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
     *  @brief constructor, set the init state to State::Empty
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
     *  @brief take a char as input, change state to next state, and output a Token if necessary
     *  @param[in] input: the input character
     *  @param[out] buf: the output Token buffer
     *  @return: return true if a Token is produced, the buf is valid then
     */
    bool next(char input, Token& buf);
    
    /**
     *  @brief reset the DFA state to begin
     */
    void  reset();

private:
    State cur_state;        // record current state of the DFA
    std::string cur_str;    // record current string composed of input characters
};

DFA::DFA(): cur_state(State::Empty), cur_str() {}

DFA::~DFA() {}

// determine if c is an operator
bool isoperator(char c) {
	return c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')';
}

/**
 *  @brief: get buf.type from cur_str which only consists of operator or digits
 *  @param s: current string
 *  @return: return TokenType of cur_str
 */
TokenType get_op_type(std::string s) {
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

bool DFA::next(char input, Token& buf) {
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

void DFA::reset() {
    cur_state = State::Empty;
    cur_str = "";
}

// definition of NodeType
enum class NodeType {
	TERMINAL,		// terminal lexical unit(useless in fact)
	EXP,			// expression
	NUMBER,			// number
	PRIMARYEXP,		// primary expression(float, int, variable, bracket...)
	UNARYEXP,		// unary expression, composed of an operand and an unary operator
	UNARYOP,		// unary operator('!'、'-'、'++'...)
	MULEXP,			// multiply expression
	ADDEXP,			// add expression
	NONE
};

// translate NodeType to string
std::string toString(NodeType nt) {
    switch (nt) {
        case NodeType::TERMINAL: return "Terminal";
        case NodeType::EXP: return "Exp";
        case NodeType::NUMBER: return "Number";
        case NodeType::PRIMARYEXP: return "PrimaryExp";
        case NodeType::UNARYEXP: return "UnaryExp";
        case NodeType::UNARYOP: return "UnaryOp";
        case NodeType::MULEXP: return "MulExp";
        case NodeType::ADDEXP: return "AddExp";
        case NodeType::NONE: return "NONE";
        default:
			assert(0 && "invalid node type");
			break;
        }
    return "";
}

// definition of tree node
struct AstNode {
	int value;
	NodeType type;    				// the node type to differentiate 
	AstNode* parent;        		// the parent node
	std::vector<AstNode*> children;	// children of node

	/**
	 *  @brief constructor
	 */
	AstNode(NodeType t = NodeType::NONE, AstNode* p = nullptr): type(t), parent(p), value(0) {}

	/**
	 *  @brief  destructor
	 */
	virtual ~AstNode() {
		for(auto child: children) {
			delete child;
		}
	}

	// rejcet copy and assignment
	AstNode(const AstNode&) = delete;
	AstNode& operator=(const AstNode&) = delete;
};

// definition of Parser
// a parser should take a token stream as input, then parsing it, output a AST
struct Parser {
	uint32_t index;  	// index of current token
	const std::vector<Token>& token_stream;	// vector of token, read only

	/**
	 *  @brief constructor
	 *  @param tokens: the input token_stream
	 */
	Parser(const std::vector<Token>& tokens): index(0), token_stream(tokens) {}

	/**
	 *  @brief destructor
	 */
	~Parser() {}

	// helper function

	/**
	 *  @brief creat AST by `Exp -> AddExp`
	 *  @return the root of current subAST
	 */
	AstNode* OP_Exp() {
		AstNode* root = new AstNode(NodeType::EXP);
		AstNode* child = OP_AddExp();		// construct subtree
		root->children.push_back(child);
		child->parent = root;
		return root;
	}

	/**
	 *  @brief creat AST by `Number -> IntConst | floatConst`
	 *  @return the root of current subAST
	 */
	AstNode* OP_Number() {
		AstNode* root = new AstNode(NodeType::NUMBER);
		if(token_stream[index].type != TokenType::INTLTR){
			assert(0 && "invalid token type in function OP_Number");
			return nullptr;
		}
		// determine radix
        AstNode* child = new AstNode(NodeType::TERMINAL);       // terminal node
        root->children.push_back(child);
		std::string val = token_stream[index].value;
        if(val.length()>=3 && val[0]=='0' && (val[1]=='x' || val[1]=='X')){ // hexadecimal integer
            child->value = std::stoi(val.substr(2),nullptr,16);
            child->parent = root;
        }
        else if(val.length()>=3 && val[0]=='0' && (val[1]=='b' || val[1]=='B')){    // binary integer
            child->value = std::stoi(val.substr(2),nullptr,2);
            child->parent = root;
        }
        else if(val.length()>=2 && val[0]=='0'){                            // octal integer
            child->value = std::stoi(val,nullptr,8);
            child->parent = root;
        }
        else{           // decimal integer (or float)
            child->value = std::stoi(val,nullptr,10);
            child->parent = root;
        }
        index++;        // no more calls to other OP functions for UnaryOp
		return root;
	}

	/**
	 *  @brief creat AST by `PrimaryExp -> '(' Exp ')' | Number`
	 *  @return the root of current subAST
	 */
	AstNode* OP_PrimaryExp() {
		AstNode* root = new AstNode(NodeType::PRIMARYEXP);
		if(token_stream[index].type == TokenType::LPARENT) {    // PrimaryExp -> '(' Exp ')'
            index++;            // discard '('
            AstNode* child = OP_Exp();
            if(token_stream[index].type == TokenType::RPARENT) {
                index++;        // discard ')'
            } else {
                assert(0 && "Missing RPARENT");
            }
            root->children.push_back(child);
            child->parent = root;
        }
        else{   // PrimaryExp -> Number
            AstNode *child = OP_Number();
            root->children.push_back(child);
            child->parent = root;
        }
		return root;
	}

	/**
	 *  @brief creat AST by `UnaryExp -> PrimaryExp | UnaryOp UnaryExp`
	 *  @return the root of current subAST
	 */
	AstNode* OP_UnaryExp() {
		AstNode* root = new AstNode(NodeType::UNARYEXP);
        if (token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU) {   // UnaryExp -> UnaryOp UnaryExp
            AstNode *child1 = OP_UnaryOp();
            AstNode *child2 = OP_UnaryExp();
            child1->parent = root;
            child2->parent = root;
            root->children.push_back(child1);
            root->children.push_back(child2);
        }
        else {      // UnaryExp -> PrimaryExp
            AstNode *child = OP_PrimaryExp();
            child->parent = root;
            root->children.push_back(child);
        }
		return root;
	}

	/**
	 *  @brief creat AST by `UnaryOp -> '+' | '-'`
	 *  @return the root of current subAST
	 */
	AstNode* OP_UnaryOp() {
		AstNode* root = new AstNode(NodeType::UNARYOP);
		if(token_stream[index].type != TokenType::PLUS && token_stream[index].type != TokenType::MINU){
			assert(0 && "invalid token type in function OP_UnaryOp");
			return nullptr;
		}
        AstNode* child = new AstNode(NodeType::TERMINAL);       // terminal node
        root->children.push_back(child);
		std::string val = token_stream[index].value;
        if(token_stream[index].type==TokenType::PLUS){
            child->value = static_cast<int>(TokenType::PLUS);
            child->parent = root;
        }
        else{
            child->value = static_cast<int>(TokenType::MINU);
            child->parent = root;
        }
        index++;        // no more calls to other OP functions for UnaryOp
		return root;
	}

	/**
	 *  @brief creat AST by `MulExp -> UnaryExp { ('*' | '/') UnaryExp }`
	 *  @return the root of current subAST
	 */
	AstNode* OP_MulExp() {
		AstNode* root = new AstNode(NodeType::MULEXP);
        AstNode *child1 = OP_UnaryExp();
        root->children.push_back(child1);
        child1->parent = root;
        while (index < token_stream.size() && (token_stream[index].type == TokenType::MULT || token_stream[index].type == TokenType::DIV)) {
            // '*' and '/' have no intermediate node
            AstNode* child2 = new AstNode(NodeType::TERMINAL);
            child2->value = static_cast<int>(token_stream[index].type);
            child2->parent = root;
            root->children.push_back(child2);
            index++;    // no more calls to other OP functions for '*' and '/'
            AstNode *child3 = OP_UnaryExp();
            root->children.push_back(child3);
            child3->parent = root;
        }
		return root;
	}

	/**
	 *  @brief creat AST by `AddExp -> MulExp { ('+' | '-') MulExp }`
	 *  @return the root of current subAST
	 */
	AstNode* OP_AddExp() {
		AstNode* root = new AstNode(NodeType::ADDEXP);
		AstNode* child1 = OP_MulExp();
		root->children.push_back(child1);
		child1->parent = root;
		while(index < token_stream.size() && (token_stream[index].type == TokenType::PLUS || token_stream[index].type == TokenType::MINU)){
            // no need to call function OP_UnaryOP, because that will add more intermediate nodes in AST
            AstNode* child2 = new AstNode(NodeType::TERMINAL);
            child2->value = static_cast<int>(token_stream[index].type);
            child2->parent = root;
            root->children.push_back(child2);
            index++;    // no more calls to other OP functions for '+' and '-'
            AstNode *child3 = OP_MulExp();
            root->children.push_back(child3);
            child3->parent = root;
		}
		return root;
	}

	/**
	 *  @brief creat the abstract syntax tree
	 *  @return the root of abstract syntax tree
	 */
	AstNode* get_abstract_syntax_tree() {
        return OP_Exp();
	}

	// for debug, u r not required to use this
	// how to use this: in ur local enviroment, defines the macro DEBUG_PARSER and add this function in every parse fuction
	void log(AstNode* node){
		#ifdef DEBUG_PARSER
			std::cout << "in parse" << toString(node->type) << ", cur_token_type::" << toString(token_stream[index].type) << ", token_val::" << token_stream[index].value << 'n';
		#endif
	}
};

/**
 *  @brief calculate the result of AST by recursion, lack of variable `visit` causes many repeated recursive calls
 *  @return the root value of AST
 */
int get_value(AstNode* root) {
    if(root->type == NodeType::TERMINAL){       // value has been assigned
        return root->value;
    }
    else if(root->type == NodeType::EXP){       // Exp -> AddExp
        root->value = get_value(root->children[0]);         // AddExp
        return root->value;
    }
    else if(root->type == NodeType::NUMBER){    // Number -> IntConst | floatConst
        root->value = get_value(root->children[0]);         // IntConst or floatConst
        return root->value;
    }
    else if(root->type == NodeType::PRIMARYEXP){// PrimaryExp -> '(' Exp ')' | Number
        root->value = get_value(root->children[0]);         // Exp or Number
        return root->value;
    }
    else if(root->type == NodeType::UNARYEXP){  // UnaryExp -> PrimaryExp | UnaryOp UnaryExp
        if(root->children[0]->type == NodeType::PRIMARYEXP){// UnaryExp -> PrimaryExp
            root->value = get_value(root->children[0]);     // PrimaryExp
        }
        else{                                               // UnaryExp -> UnaryOp UnaryExp
            int unaryop = get_value(root->children[0]);
            if (unaryop == static_cast<int>(TokenType::PLUS)){      // '+'
                root->value = get_value(root->children[1]);         // UnaryExp
            }
            else{                                                   // '-'
                root->value = -get_value(root->children[1]);        // UnaryExp
            }
        }
        return root->value;
    }
    else if(root->type == NodeType::UNARYOP){   // UnaryOp -> '+' | '-'
        root->value = get_value(root->children[0]);         // '+' or '-'
        return root->value;
    }
    else if(root->type == NodeType::MULEXP){    // MulExp -> UnaryExp { ('*' | '/') UnaryExp }
        int result = get_value(root->children[0]);          // UnaryExp
        for(int i = 1; i < root->children.size(); i += 2){  // ('*' | '/') UnaryExp
            int val = root->children[i]->value;
            if (val == static_cast<int>(TokenType::MULT)){  // '*'
                result *= get_value(root->children[i+1]);   // UnaryExp
            }
            else{                                           // '/'
                result /= get_value(root->children[i+1]);   // UnaryExp
            }
        }
        root->value = result;
        return root->value;
    }
    else if(root->type == NodeType::ADDEXP){    // AddExp -> MulExp { ('+' | '-') MulExp }
        int result = get_value(root->children[0]);          // MULEXP
        for(int i = 1; i < root->children.size(); i += 2){  // ('+' | '-') MulExp
            int val = root->children[i]->value;
            if (val == static_cast<int>(TokenType::PLUS)){  // '+'
                result += get_value(root->children[i+1]);   // MulExp
            }
            else{                                           // '-'
                result -= get_value(root->children[i+1]);   // MulExp
            }
        }
        root->value = result;
        return root->value;
    }
    else{
        assert(0 && "invalid  NodeType");
        return -1; 
    }
}

/**
 *  @brief print AST in level order
 */
void printAST(AstNode* root){
    if(root==nullptr){
        return;
    }
    std::queue<AstNode*> q;
    std::queue<int> level;
    q.push(root);
    level.push(0);
    while(!q.empty()){
        AstNode* top = q.front();
        int top_level = level.front();
        q.pop();
        level.pop();
        if(top_level>0) std::cout<< top_level <<": "<< toString(top->type) <<" "<< top->value <<", father:"<< toString(top->parent->type) <<" "<< top->parent->value <<std::endl;
        else    std::cout<< top_level <<": "<< toString(top->type) <<" "<< top->value <<std::endl;
        for(int i = 0; i < top->children.size(); i++){
            q.push(top->children[i]);
            level.push(top_level+1);
        }
    }
    return;
}

int main(){
	std::string stdin_str;
	std::getline(std::cin, stdin_str);
	stdin_str += "\n";
	DFA dfa;
	Token tk;
	std::vector<Token> tokens;
	for (size_t i = 0; i < stdin_str.size(); i++) {
		if(dfa.next(stdin_str[i], tk)){
			tokens.push_back(tk);
            // std::cout<<toString(tk.type)<<" "<<tk.value<<std::endl;
		}
	}

	Parser parser(tokens);
	auto root = parser.get_abstract_syntax_tree();
	get_value(root);
    //printAST(root);

	std::cout << root->value;

	return  0;
}