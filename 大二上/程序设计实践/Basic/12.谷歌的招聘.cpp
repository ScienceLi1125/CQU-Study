/*谷歌的招聘：
题目：自然常数e是一个著名的超越数，前面若干位写出来是这样的：e=2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427427466391932003059921...
    其中粗体标出的10位数：7427466391就是答案。
    本题要求你编程解决一个更通用的问题：从任一给定的长度为L的数字中，找出最早出现的K位连续数字所组成的素数。
输入：第一行给出2个正整数，分别是L（不超过 1000 的正整数，为数字长度）和K（小于 10 的正整数）。接下来一行给出一个长度为L的正整数N。
输出：在一行中输出N中最早出现的K位连续数字所组成的素数。如果这样的素数不存在，则输出 404。
    注意，原始数字中的前导零也计算在位数之内。例如在200236中找4位素数，0023算是解；但第一位2不能被当成0002输出，因为在原始数字中不存在这个2的前导零。
*/
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
using namespace std;
bool isprime(int n){
    if(n==0||n==1||n==4){
        return 0;
    }
    else if(n==2||n==3){
        return 1;
    }
    else{
        for(int i=2;i<sqrt(n)+1;i++){   //循环用sqrt函数简化运算，但必须循环到+1
            if(n%i==0){
                return 0;
            }
        }
        return 1;
    }
}
int main(){
    int L,K;
    string N;
    cin>>L>>K>>N;
    int result=0;                       //若没有符合要求的tmp赋给result，则保持初值0
    int tmp;
    for(int i=0;i<L-K+1;i++){           //因为还有K位长的s，所以i只用遍历到L-K，否则超出部分仍会循环超出预期
        string s="";
        for(int j=0;j<K;j++){
            s+=N[i+j];
        }
        stringstream ss;                //巧用stringstream转换类型
        ss<<s;
        ss>>tmp;
        if(isprime(tmp)){
            result=tmp;                 //遇到符合条件的tmp赋给result，终止循环
            printf("%0*d",K,result);    //题干让输出K位，就必须保证满足条件的数字的先导零不能丢失
            break;
        }
    }
    if(result==0){
        cout<<404<<endl;
    }


    return 0;
}

