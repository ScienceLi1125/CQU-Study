/*字符串对称:
    编写一个算法利用顺序栈判断一个字符串是否是对称串。所谓对称串是指从左向右读和从右向左读的序列相同。

输入格式:
输入一个无空格的字符串。

输出格式:
如果该字符是对称的，输出yes，否则输出no。

输入样例1:
abba
输出样例1:
yes
输入样例2:
abcd
输出样例2:
no
*/

/*判断回文串，可以通过两个字符串比较，也可以根据栈和队列的思想
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s1,s2="";
    cin>>s1;
    for(int i=0;i<s1.length();i++){
        s2+=s1[s1.length()-1-i];
    }
    if(s1==s2){
        cout<<"yes"<<endl;
    }
    else{
        cout<<"no"<<endl;
    }

    return 0;
}
*/

#include<iostream>
#include<string>
#include<stack>
#include<queue>
using namespace std;

int main() {
    string s;
    bool flag=1;
    cin>>s;
    stack<char> sta;
    queue<char> que;
    for(int i=0;i<s.size();i++){
        sta.push(s[i]);
        que.push(s[i]);
    }
    for(int i=0;i<s.length();i++) {
        if(sta.top()!=que.front()) {
            flag=0;
            break;
        }
        sta.pop();			//stack弹出栈顶元素（末位）
        que.pop();			//queue弹出队首元素（首位）
    }

    if(flag==1){
		cout<<"yes";
	}
    else{
		cout<<"no";
	}
	
    return 0;
}
