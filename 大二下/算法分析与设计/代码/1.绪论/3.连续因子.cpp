/*连续因子：
题目：一个正整数N的因子中可能存在若干连续的数字。例如630可以分解为3×5×6×7，其中5、6、7就是3个
    连续的数字。给定任一正整数N，要求编写程序求出最长连续因子的个数，并输出最小的连续因子序列。
输入：在一行中给出一个正整数 N（1<N<2**31）。
输出：首先在第1行输出最长连续因子的个数；然后在第2行中按因子1*因子2*……*因子k的格式输出最小的连
    续因子序列，其中因子按递增顺序输出，1不算在内。
思路：直接遍历搜索即可
*/
#include <iostream>
#include <math.h>
using namespace std;

int main(){
    int N;
    cin>>N;
    //因为要输出，所以作为全局变量
    int start=0,len=0;              //start表示最长连续因子起始值，len表示其长度
    for(int i=2;i<sqrt(N)+1;i++){   //i表示连续因子的起始值，显然合数的起始因子不会超过根号N
        //因为下面操作要改变i和N的值，所以另起变量
        int cur=i,l=0,num=N;        //cur表示当前因子，l表示连续因子长度，num表示分解掉cur所剩的值
        for(;num%cur==0;cur++,l++){ //只要不满足num%cur==0，则不连续，循环终止
            num/=cur;
        }
        if(l>len){
            start=i;
            len=l;
        }
    }
    if(len!=0){
        cout<<len<<endl<<start;
        for(int i=1;i<len;i++){
            cout<<'*'<<start+i;
        }
    }
    else{
        cout<<1<<endl<<N;
    }

    return 0;
}