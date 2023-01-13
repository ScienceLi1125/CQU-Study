/*用栈实现中缀表达式转换成后缀表达式
输入：在一行中给出不含空格的中缀表达式，可包含+、-、*、/以及左右括号()，表达式不超过20个字符。
输出：在一行中输出转换后的后缀表达式，要求不同对象（运算数、运算符号）之间以空格分隔，但结尾不得
    有多余空格。
思路：中缀转后缀的实质就是寻找运算的优先级，将运算符放到第二个操作数后面
    1.初始化两个栈,运算符栈s1和存储中间结果的栈s2
    2.从左到右扫描中缀表达式
    3.遇到操作数时,将其压s2
    4.遇到运算符时,比较其与s1栈顶运算符的优先级(括号不算运算符)
        4.1如果s1为空,或栈顶运算符为左括号"(",则直接将此运算符入栈
        4.2否则,若优先级比栈顶的运算符的高,也将运算符压入s1
        4.3否则,将s1栈顶的运算符弹出并压入到s2中,再次转到4.1步骤与s1中新的栈顶运算符相比较
    5.遇到括号时
        5.1如果是左括号,直接压入s1
        5.2如果是右括号,则依次弹出s1栈顶的运算符,并压入s2,直到遇到左括号为止,此时将这一对括号丢弃
    6.重复步骤2到5,直到表达式的最右边
    7.将s1中剩余的运算符依次弹出并压入s2
    8.依次弹出s2中的元素并输出,结果的逆序即是中缀表达式转后缀表达式的结果
注：为方便存储，仍使用字符串作为操作数和运算符的数据类型
坑：1.误认为小数为整数，如：1314+25.5*12
    2.括号嵌套，如：((2+3)*4-(8+2))/5
    3.正负号，如：-2*(+3)，输出应该是-2 3 *  (单独考虑)
    4.不含运算符，如：123
*/
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <sstream>
using namespace std;

bool isPunct(char c){
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'){
        return 1;
    }
    return 0;
}
bool isPunct(string c){
    if(c=="+"||c=="-"||c=="*"||c=="/"||c=="("||c==")"){
        return 1;
    }
    return 0;
}
bool compare(string a,char b){
    if((a=="*"||a=="/")&&(b=='+')||b=='-'){
        return 1;
    }
    return 0;
}

int main() {
    //分割操作数与运算符
    string s;
    getline(cin,s);
    vector<string> v;           //用来存储中缀表达式的操作数和运算符
    stack<char> s1;             //运算符栈
    queue<string> q2;           //输出结果，因为弹出时要逆序，因此采用队列
    int index=-1;               //存储上一个运算符的位置
    for(int i=0;i<s.length();i++){
        if(s[i]=='-'&&(i==0||s[i-1]=='(')){     //+-表示正负出现的位置：开头或者(后面
            continue;
        }
        if(s[i]=='+'&&(i==0||s[i-1]=='(')){
            index++;                            //+不出现在表达式
            continue;
        }
        if(isPunct(s[i])){
            string subs1=s.substr(index+1,i-index-1);
            if(subs1!="")   v.push_back(subs1); //保证非空
            string c(1,s[i]);   //运算符一定非空，将char转为string
            v.push_back(c);
            //string tmp(s,i);  //s不可分割，否则循环的下标发生紊乱
            //s=tmp;
            index=i;
        }
    }
    string subs2=s.substr(index+1,s.length());
    if(subs2!="")   v.push_back(subs2);         //保证非空
    //转换表达式
    for(int i=0;i<v.size();i++){
        if(!isPunct(v[i])){
            q2.push(v[i]);
        }
        else{
            if(v[i]=="("){
                s1.push('(');
            }
            else if(v[i]==")"){
                while(s1.top()!='('){
                    string c(1,s1.top());
                    q2.push(c);
                    s1.pop();
                }
                s1.pop();
            }
            else{
                label:{         //label实现跳转
                    if(s1.empty()||s1.top()=='('){
                        s1.push(v[i][0]);   //string转char
                    }
                    else if(compare(v[i],s1.top())){
                        s1.push(v[i][0]);
                    }
                    else{
                        string c(1,s1.top());
                        q2.push(c);
                        s1.pop();
                        goto label;
                    }
                }
                
            }
        }
    }
    while(!s1.empty()){
        string c(1,s1.top());
        q2.push(c);
        s1.pop();
    }
    cout<<q2.front();
    q2.pop();
    while(!q2.empty()){
        cout<<" "<<q2.front();
        q2.pop();
    }
    

    return 0;
}
