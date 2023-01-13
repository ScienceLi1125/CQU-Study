/*Left-pad：
题目：根据新浪微博上的消息，有一位开发者不满NPM（Node Package Manager）的做法，收回了自己的开源代码，其中包括一个叫left-pad的模块，就是这个模块把javascript里面的React/Babel干瘫痪了。这是个什么样的模块？就是在字符串前填充一些东西到一定的长度。例如用*去填充字符串GPLT，使之长度为10，调用left-pad的结果就应该是******GPLT。Node社区曾经对left-pad紧急发布了一个替代，被严重吐槽。下面就请你来实现一下这个模块。
输入：在第一行给出一个正整数N（≤1000）和一个字符，分别是填充结果字符串的长度和用于填充的字符，中间以1个空格分开。第二行给出原始的非空字符串，以回车结束。
输出：在一行中输出结果字符串。
*/
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    int N;
    char c;
    cin>>N>>c;
    getchar();                          //一定要getchar吃掉空格！！！
    string s;
    getline(cin,s);
    if(s.length()<=N){
        cout<<setw(N)<<setfill(c)<<s;   //妙用setw(N)<<setfill(c)输出
    }
    else{
        for(int i=s.length()-N;i<s.length();i++){
            cout<<s[i];
        }
    }

        
    return 0;
}