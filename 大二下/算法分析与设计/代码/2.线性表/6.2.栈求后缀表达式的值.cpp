/*输入：后缀表达式（数字或运算符以空格分隔）
*/
#include <iostream>
#include <stack>
#include <vector>
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
    getline(cin,s);                         //输入后缀表达式
    vector<string> v;
    stack<int> stk;
    while(s.find(' ')!=string::npos){
        int pos=s.find(' ');
        string subs=s.substr(0,pos);
        v.push_back(subs);
        string tmp(s,pos+1);
        s=tmp;
    }
    v.push_back(s);
    for(int i=0;i<v.size();i++){
        if(!isPunct(v[i])){
            stk.push(string_to_double(v[i]));
        }
        else{
            double a=stk.top();
            stk.pop();
            double b=stk.top();
            stk.pop();
            double num=Operation(b,a,v[i]);     //b为第一个操作数，a为第二个，但是a在栈顶，因此调换顺序
            stk.push(num);
        }
    }
    cout<<stk.top()<<endl;

    return 0;
}
