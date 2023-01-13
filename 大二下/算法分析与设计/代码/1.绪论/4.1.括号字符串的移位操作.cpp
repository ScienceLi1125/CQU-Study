/* 括号字符串的移位操作：
题目：由相同数量的左括号'('和右括号')'构成的字符串，只需要将一定长度（可以为0）的前缀移动到字符串的
    末尾，就可以使其中的左右括号匹配成功，即成为括号语句。在这里，我们不用数学方法去证明该命题的正
    确性，而是编程求出所有可行的前缀长度。
输入：在一行中给出由'('和')'构成的字符串，长度不超过1000000。题目保证字符串中左右括号的数量相同。
输出：在一行中输出所有可行的前缀长度，按升序排列。数值间用空格分开，末尾的值后面没有空格。
思路：最直观的就是遍历字符串拼接n次，每次用栈判断是否可行，但当n~1000000时，容易超时
*/
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

bool ismatch(string s){
    stack<char> st;
    for(int i=0;i<s.length();i++){
        if(s[i]=='('){
            st.push(s[i]);
        }
        else{
            if(!st.empty()&&st.top()=='('){
                st.pop();
            }
        }
    }
    return st.empty();
}

int main(){
    string s;
    cin>>s;
    vector<int> v;
    for(int i=0;i<s.length();i++){
        string subs1(s,0,i);
        string subs2(s,i);
        string s2=subs2+subs1;
        if(ismatch(s2)){
            v.push_back(i);
        }
    }
    cout<<v[0];
    for(int i=1;i<v.size();i++){
        cout<<" "<<v[i];
    }

    return 0;

} 