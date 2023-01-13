/*最大k乘积问题：
题目：设I是一个n位十进制整数。如果将I划分为k段，则可得到k个整数。
    这k个整数的乘积称为I的一个k乘积。试设计一个算法，对于给定的I和k，求出I的最大k乘积。
思路：此处为动态规划的思路，p位整数划分为q段的最大乘积等于x(1<=x<=p-1)位整数划分为n-1段乘x+1到
    p的数字。令number(i,j)表示第i位到第j位组成的j-i+1位整数，product(p,q)表示前p位被划分为q段
    的最大乘积（注：若p<q时product(p,q)=0）
    初始子问题(q=1)：product(p,1)=number(1,p)
    下一阶段子问题：product(p,q)=max{product(x,q-1)*number(x+1,p)}
    例如：将1234划分为3段
        product(1,1)=1,product(2,1)=12,product(3,1)=123,product(4,1)=1234
        product(2,2)=max{product(1,1)*number(2,2)}=2
        product(3,2)=max{product(1,1)*number(2,3),product(2,1)*number(3,3)}=36
        product(4,2)=max{product(1,1)*number(2,4),product(2,1)*number(3,4),product(3,1)*number(4,4)}=492
    同理得product(3,3),product(4,3),product(4,4)
*/
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int number(string I){
    int num=0;
    for(int i=0;i<I.length();i++){
        num+=(I[i]-'0')*pow(10,I.length()-i-1);
    }
    return num;
}

int main(){
    string I;                   //位数太长用数组或字符串存储
    int k;
    cin>>I>>k;
    int product[20][20]={0};    //二维数组存储product(p,q)，遵循上面分析，从1开始取
    for(int i=1;i<=I.length();i++){
        string s1(I,0,i);       //i表示截取I的长度
        product[i][1]=number(s1);
    }
    for(int q=2;q<=I.length();q++){         //q=1已经赋初值，从2开始遍历
        for(int p=q;p<=I.length();p++){     //p>=q时才进行动态规划，对product(p,q)赋值
            int max=0;
            for(int x=1;x<p;x++){           //寻找max{product(x,q-1)*number(x+1,p)}
                string s2(I,x,p-x);         //s2不是取到I末位而是p位,p-x表示字符串长度
                if(max<product[x][q-1]*number(s2)){
                    max=product[x][q-1]*number(s2);
                }
            }
            product[p][q]=max;
        }
    }
    cout<<product[I.length()][k];

    return 0;
}