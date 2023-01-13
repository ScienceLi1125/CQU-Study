/*已知和积猜数字
题目：有两个整数a和b满足1≤a≤b≤N，甲只知道a+b的值，乙只知道a×b。下面是两个人的一段对话，要求从
中推测出正整数a和b的值。
    甲：我不知道是什么数
    乙：我也不知道
    甲：我知道了
    乙：我也知道了
输入：只有一行，给出1个整数N (1<N≤1000)。
输出：在一行中输出一组可行解a b，用空格分开。如果有多组解，每一行一组解，按字典升序从上向下排列。
*/
#include <iostream>
#include <math.h>
using namespace std;

const int MAX=1002;
int sum[2*MAX]={0};
int product[MAX*MAX]={0};
//不必再开一个a[1001][1001]，浪费空间，直接对sum和product数组操作即可

int main(){
	int N;
	cin>>N;
	for(int i=1;i<=N;i++){
        for(int j=1;j<=i;j++){  //数据的对称性只计算一次，因此j的上界为i
            sum[i+j]++;
            product[i*j]++;
        }
    }
    for(int i=1;i<=N;i++){      //对应甲的第一句话
        for(int j=1;j<=i;j++){
            if(sum[i+j]==1){
                sum[i+j]--;
                product[i*j]--; //i j和与积同时去掉    
            }
        }
    }
    //乙说“我也不知道”不仅表明他不知道，还表明在已知甲不知道的情况下还是不知道，
    //不过这已经被上一步排除，因此不用考虑
    for(int i=1;i<=N;i++){      //对应乙的第一句话
        for(int j=1;j<=i;j++){
            if(product[i*j]==1){
                sum[i+j]--;
                product[i*j]--;
            }
        }
    }
    for(int i=1;i<=N;i++){      
        for(int j=1;j<=i;j++){
    /*sum[i+j]!=1的情况不必考虑（也可以处理为0，不过没有必要），因为甲已经知道了，说明只需要
    在sum[i+j]=1的情况里找答案*/
            if(sum[i+j]==1){    //对应甲的第二句话
                /*若product[i*j]>1且其中不止一组数满足sum[i+j]==1，则不符合题意，第一次出现
                时被赋为1，第二次以后就变成了0*/
                product[i*j]=product[i*j]>1 ? 1:0;  //对应乙的第二句话
            }
        }
    }
    for(int i=1;i<=N;i++){
        for(int j=1;j<=i;j++){
            if(sum[i+j]==1 && product[i*j]==1){
                cout<<j<<" "<<i<<endl;
            }
        }
    }
    
    return 0;
}