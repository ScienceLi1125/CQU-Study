/*有理数加法：
题目：本题要求编写程序，计算两个有理数的和。
输入：在一行中按照a1/b1 a2/b2的格式给出两个分数形式的有理数，其中分子和分母全是整形范围内的正整数。
输出：一行中按照a/b的格式输出两个有理数的和。注意必须是该有理数的最简分数形式，若分母为1，则只输出分子。
*/
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int a1,b1,a2,b2;
    scanf("%d/%d %d/%d",&a1,&b1,&a2,&b2);   //用scanf输入简单明了
    int c1=a1*b2+a2*b1;
    int d1=b1*b2;
    int gcd=__gcd(c1,d1);                   //最大公因数
    c1=c1/gcd;
    d1=d1/gcd;
    if(d1==1){
        cout<<c1<<endl;
    }
    else{
        cout<<c1<<"/"<<d1<<endl;
    }

    return 0;
}