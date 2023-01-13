/*括号匹配：
题目：给定仅包含“()[]{}”六种括号的字符串，请你判断该字符串中，括号的匹配是否是合法的，也就是对应括号的数量、嵌套顺序完全正确。
输入：第一行一个整数T（T<=10），其后T行每行一个字符串只包含[{()}]六种字符（字符串长度2e5以内）
输出：对于每个字符串，匹配输出Yes,否则输出No
*/
#include <iostream>
#include <list>
#include <string>
using namespace std;

char match(char a){
    if(a=='('){         //不能用）匹配（，否则）（也可以通过
        return ')';
    }
    else if(a=='['){
        return ']';
    }
    else if(a=='{'){
        return '}';
    }
    else{
        return '0';
    }
}

int main(){
    int T;
    cin>>T;
    string s;
    for(int i=0;i<T;i++){
        cin>>s;
        list<char> ls;                                  //必须在内部声明list，否则每次循环会使其越来越长
        for(int j=0;j<s.length();j++){
            if(!ls.empty()&&match(ls.back())==s[j]){    //必须检验是否非空！
                ls.pop_back();
            }
            else{
                ls.push_back(s[j]);
            }
              
        }
        if(ls.empty()){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }

    return 0;
}