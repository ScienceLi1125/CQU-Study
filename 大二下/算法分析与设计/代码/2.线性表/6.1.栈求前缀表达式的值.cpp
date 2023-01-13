/*栈可以用于前中后缀表达式的求值
前缀表达式求值：从 右至左 扫描表达式,遇到数字时,将数字压入栈,遇到运算符时,弹出栈顶的两个数,用
    运算符对它们做相应的计算,并将结果入栈,重复上述过程直到表达式最左端,最后运算得到的值即为表
    达式的结果
中缀表达式求值：中缀表达式便于人脑理解与计算，但不加括号会出现二义性，加了括号又不方便计算机处
    理，因此计算机遇到中缀表达式一般处理成前/后缀表达式，方便运算
后缀表达式求值：从 左至右 扫描表达式,遇到数字时,将数字压入栈中,遇到运算符时,弹出栈顶的两个数,
    用运算符对它们做相应的计算,并将结果入栈,重复上述过程直到表达式最右端,最后运算得出的值即为
    表达式的结果
输入：前缀表达式（数字或运算符以空格分隔）
输出：运算结果
注：题目没有规定所有数字均为一位整数，因此直接使用字符串难以确定数字的位数，故采用vector，并将
    其元素都转换成string
*/
#include <iostream>
#include <stack>            //stack用来执行运算
#include <vector>           //vector用来进行存储
#include <sstream>
using namespace std;

bool isPunct(string c){
    if(c=="+"||c=="-"||c=="*"||c=="/"){
        return 1;
    }
    return 0;
}
double Operation(int a,int b,string c){
    if(c=="+"){
        return a+b;
    }
    else if(c=="-"){
        return a-b;
    }
    else if(c=="*"){
        return a*b;
    }
    else if(c=="/"){
        return a/b;
    }
}
double string_to_double(string s){
    double ans;
    stringstream ss;
    ss<<s;
    ss>>ans;
    return ans;
}

int main() {
    string s;
    getline(cin,s);                         //输入前缀表达式
    vector<string> v;
    stack<int> stk;
    while(s.find(' ')!=string::npos){       //s中存在空格
        int pos=s.find(' ');
        string subs=s.substr(0,pos);        //空格前的字符串
        v.push_back(subs);
        string tmp(s,pos+1);                //空格后的字符串
        s=tmp;
    }
    v.push_back(s);                         //将所有数字与运算符压入vector
    for(int i=v.size()-1;i>=0;i--){
        if(!isPunct(v[i])){                 //不是运算符号，则是数字
            stk.push(string_to_double(v[i]));
        }
        else{
            double a=stk.top();
            stk.pop();
            double b=stk.top();
            stk.pop();
            double num=Operation(a,b,v[i]);
            stk.push(num);
        }
    }
    cout<<stk.top()<<endl;

    return 0;
}
