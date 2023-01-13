/*交换最小值和最大值：
题目：本题要求编写程序，先将输入的一系列整数中的最小值与第一个数交换，然后将最大值与最后一个数
    交换，最后输出交换后的序列。
    注意：题目保证最大和最小值都是唯一的。
输入：第一行中给出一个正整数N（≤10），第二行给出N个整数，数字间以空格分隔。
输出：在一行中顺序输出交换后的序列，每个整数后跟一个空格。
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> vec1(N);
    int max=-32767,min=32767;   //max,min用来查找最值
    int num1=0,num2=0;          //num1,num2用来记min和max取值的数组下标    
    for(int i=0;i<N;i++){       //将最小值、最大值分开取，依据题意，先求最小值
        int m;
        cin >> m;
        vec1[i]=m;
        if(m<min){
            min=m;
            num1=i;
        }
    }
    vec1[num1]=vec1[0];         //判断出最小值下标先交换，再判断最大值
    vec1[0]=min;
    for(int i=0;i<N;i++){       //若同时交换，会因为最小值交换后下标发生改变造成首尾项混乱
        if(vec1[i]>max){
            max=vec1[i];
            num2=i;
        }
    }
    vec1[num2]=vec1[N-1];
    vec1[N-1]=max;
    for(int j=0;j<N;j++){
        cout << vec1[j] <<" ";
    }
    return 0;
}