/*最长对称子串：
题目：对给定的字符串，本题要求你输出最长对称子串的长度。例如，给定Is PAT&TAP symmetric?，最长对称子串为s PAT&TAP s，于是你应该输出11。
输入：在一行中给出长度不超过1000的非空字符串。
输出：在一行中输出最长对称子串的长度。
*/
#include <iostream>
using namespace std;

int main(){
    string s;
    getline(cin,s);
    int len=s.length();
    int max=0;                  //空字符串max为0
    if(len){                    //长度为1的字符串不会进入下面的for循环，因此要改变初值
        max=1;                  //max初值不可以随意设，因为只要字符串非空则至少为1而不是0
    }
    for(int i=1;i<len-1;i++){
        int tmp=1;
        bool flag=0;            //判断回文子串长度奇偶性
        if(s[i]==s[i+1]){
            flag=1;
            tmp++;
        }
        if(!flag){              //回文子串形如sdfds
            for(int j=1;i-j>=0,i+j<=len-1;j++){
                if(s[i-j]==s[i+j]){
                    tmp+=2;
                }
                else{
                    break;
                }
            }
            if(max<tmp){
                max=tmp;
            }
        }
        else{                   //回文子串形如sdffds
            for(int j=1;i-j>=0,i+j+1<=len-1;j++){
                if(s[i-j]==s[i+j+1]){
                    tmp+=2;
                }
                else{
                    break;
                }
            }
            if(max<tmp){
                max=tmp;
            }
        }
        
    }
    cout<<max<<endl;
    
    return 0;
}