/*对称排序：
题目：你供职于由一群丑星作为台柱子的信天翁马戏团。你刚完成了一个程序编写，它按明星们姓名字符串的长度非降序（即当前姓名的长度至少与前一个姓名长度一样）顺序输出他们的名单。然而，你的老板不喜欢这种输出格式，提议输出的首、尾名字长度较短，而中间部分长度稍长，显得有对称性。老板说的具体办法是对已按长度排好序的名单逐对处理，将前者放于当前序列的首部，后者放在尾部。如输入样例中的第一个案例，Bo和Pat是首对名字，Jean和Kevin是第二对，余此类推。
输入：输入包含若干个测试案例。每个案例的第一行含一个整数n（n>=1），表示名字串个数。接下来n行每行为一个名字串，这些串是按长度排列的。名字串中不包含空格，每个串至少包含一个字符。n=0为输入结束的标志。
输出：对每一个测试案例，先输出一行“Set n”，其中n从1开始取值，表示案例序号。接着是n行名字输出，如输出样例所示。
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int main(){
    int n=1;
    int cnt=1;
    while(cin>>n&&n!=0){    //输入0停止
        vector<string> v;
        for(int i=0;i<n;i++){
            string s;
            cin>>s;
            v.push_back(s);
        }
        int l=v.size();
        int r = l%2;        //取l模2的余数
        cout<<"SET "<<cnt<<endl;
        for(int j=0;j<l;j+=2){
            cout<<v[j]<<endl;
        }
        for(int k=l-1-r;k>=0;k-=2){     //k的初值巧妙解决奇偶性
            cout<<v[k]<<endl;
        }
        cnt++;
    }

    return 0;
}