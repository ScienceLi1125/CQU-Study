/*用栈实现中缀表达式转换成前缀表达式
思路：
    1.初始化两个栈,运算符栈s1和存储中间结果的栈s2
    2.从 右到左 扫描中缀表达式
    3.遇到操作数时,将其压s2
    4.遇到运算符时,比较其与s1栈顶运算符的优先级(括号不算运算符)
        4.1如果s1为空,或栈顶运算符为 右 括号")",则直接将此运算符入栈
        4.2否则,若优先级比栈顶的运算符的高 或相等 ,也将运算符压入s1
        4.3否则,将s1栈顶的运算符弹出并压入到s2中,再次转到4.1步骤与s1中新的栈顶运算符相比较
    5.遇到括号时
        5.1如果是 右 括号,直接压入s1
        5.2如果是 左 括号,则依次弹出s1栈顶的运算符,并压入s2,直到遇到左括号为止,此时将这一对括号丢弃
    6.重复步骤2到5,直到表达式的最右边
    7.将s1中剩余的运算符依次弹出并压入s2
    8.依次弹出s2中的元素并输出,结果 即是中缀表达式转 前 缀表达式的结果
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
    if((a=="+"||a=="-")&&(b=='*')||b=='/'){
        return 0;
    }
    return 1;
}

int main() {
    string s;
    getline(cin,s);
    vector<string> v;
    stack<char> s1;
    stack<string> s2;
    int index=-1;
    for(int i=0;i<s.length();i++){
        if(s[i]=='-'&&(i==0||s[i-1]=='(')){
            continue;
        }
        if(s[i]=='+'&&(i==0||s[i-1]=='(')){
            index++;
            continue;
        }
        if(isPunct(s[i])){
            string subs1=s.substr(index+1,i-index-1);
            if(subs1!="")   v.push_back(subs1);
            string c(1,s[i]);
            v.push_back(c);
            index=i;
        }
    }
    string subs2=s.substr(index+1,s.length());
    if(subs2!="")   v.push_back(subs2);
    //转换表达式
    for(int i=v.size()-1;i>=0;i--){
        if(!isPunct(v[i])){
            s2.push(v[i]);
        }
        else{
            if(v[i]==")"){
                s1.push(')');
            }
            else if(v[i]=="("){
                while(s1.top()!=')'){
                    string c(1,s1.top());
                    s2.push(c);
                    s1.pop();
                }
                s1.pop();
            }
            else{
                label:{         //label实现跳转
                    if(s1.empty()||s1.top()==')'){
                        s1.push(v[i][0]);   //string转char
                    }
                    else if(compare(v[i],s1.top())){
                        s1.push(v[i][0]);
                    }
                    else{
                        string c(1,s1.top());
                        s2.push(c);
                        s1.pop();
                        goto label;
                    }
                }
                
            }
        }
    }
    while(!s1.empty()){
        string c(1,s1.top());
        s2.push(c);
        s1.pop();
    }
    cout<<s2.top();
    s2.pop();
    while(!s2.empty()){
        cout<<" "<<s2.top();
        s2.pop();
    }

    return 0;
}
