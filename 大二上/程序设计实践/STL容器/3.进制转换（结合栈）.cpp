/*进制转换:
    输入十进制整数N和待转换的进制x（2、8、16），分别代表十进制N转换成二进制、八进制和十六进制，输出对应的结果。十六进制中A~F用大写字母表示。

输入格式:
输入两个整数N（十进制整数N）和x（x进制），中间用空格隔开。

输出格式:
输出对应的结果。

输入样例1:
123 2
输出样例1:
1111011
输入样例2:
123 16
输出样例2:
7B
*/

#include <iostream>
#include <stack>
using namespace std;

int main(){
    int N,x;
    cin>>N>>x;
    stack<int> s;

    while(N!=0) {
        int a=N%x;
        s.push(a);
        N=N/x;
    }

    while(!s.empty()) {
        if(s.top()==10){         //确保十六进制输出
            cout<<'A';
        }
        if(s.top()==11){
            cout<<'B';
        }
        if(s.top()==12){
            cout<<'C';
        }
        if(s.top()==13){
            cout<<'D';
        }
        if(s.top()==14){
            cout<<'E';
        }
        if(s.top()==15){
            cout<<'F';
        }
        if(s.top()<10){         //top配合pop输出stack元素 
            cout<<s.top();
        }
        s.pop();
    }
    cout<<endl;

    return 0;
}