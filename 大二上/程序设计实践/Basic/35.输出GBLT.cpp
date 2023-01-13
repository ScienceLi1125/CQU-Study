/*输出GPLT
题目：给定一个长度不超过10000的、仅由英文字母构成的字符串。请将字符重新调整顺序，按GPLTGPLT...
    这样的顺序输出，并忽略其它字符。当然，四种字符（不区分大小写）的个数不一定是一样多的，若某种字符已经输出完，则余下的字符仍按GPLT的顺序打印，直到所有字符都被输出。
输入：一个长度不超过10000的、仅由英文字母构成的非空字符串。
输出：排序后的字符串。题目保证输出非空。
*/
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    getline(cin,s);
    int a[4]={0};
    for(int i=0;i<s.length();i++){                  //直接忽略其他字母
        if(s[i]=='G'||s[i]=='g')   a[0]++;          //注意题目中大小写均可
        else if(s[i]=='P'||s[i]=='p')   a[1]++;
        else if(s[i]=='L'||s[i]=='l')   a[2]++;
        else if(s[i]=='T'||s[i]=='t')   a[3]++;
    }
    //GPLT按顺序与个数输出
    while(a[0]||a[1]||a[2]||a[3]){
        if(a[0]){
            cout<<"G";
            a[0]--;
        }
        if(a[1]){
            cout<<"P";
            a[1]--;
        }
        if(a[2]){
            cout<<"L";
            a[2]--;
        }
        if(a[3]){
            cout<<"T";
            a[3]--;
        }
    }
    

    return 0;
}