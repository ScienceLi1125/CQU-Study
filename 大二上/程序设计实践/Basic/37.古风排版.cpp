/*古风排版：
题目：中国的古人写文字，是从右向左竖向排版的。本题就请你编写程序，把一段文字按古风排版。
输入：在第一行给出一个正整数N（<100），是每一列的字符数。第二行给出一个长度不超过1000的非空字符串，以回车结束。
输出：按古风格式排版给定的字符串，每列N个字符（除了最后一列可能不足N个）。
*/
#include <iostream>
#include <string>
using namespace std;

int main(){
    int N;
    cin>>N;
    getchar();                      //吃掉空格！！！
    string s;
    getline(cin,s);
    int l=s.length();
    if(l%N){
        l/=N;
        s.resize(N*l+N,' ');        //用resize补齐文末空格
    }

    for(int j=0;j<N;j++){
        for(int i=s.length()-N+j;i>=0;i-=N){
            cout<<s[i];
        }
        cout<<endl;
    }
    

    return 0;
}