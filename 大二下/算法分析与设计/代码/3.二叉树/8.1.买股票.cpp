/*买股票：
题目：刘大师买股票的神器有两个功能：第一，设置N天为一个周期，除最后一天不买之外，其它天每天都买进且
    只买一支股票，做到细水长流；第二，每天买进股票的同时，把之前买进的且还留在手头上的股票，只要买
    进价格比当天交易额低，就立马卖出赚差价，见好就收。如果到最后一天还有没卖掉的，就全部出售。
输入：两行数据，第一行只有一个整数N (1<N≤1000000)。第二行有N个正整数，第i∈[1,N]个数si∈[1,100000]
    表示第i天的单支股票的交易额。数据间用空格分开，末尾的数后面没有空格。
输出：一个整数，表示N天的股票交易总收益。
思路：简单的用数组加循环解决，发现有一个测试点要将数组开到1000000，运行超时
（母题为 计算右侧小于当前元素的个数）
*/
#include <iostream>
using namespace std;

int main(){
    int N;
    cin>>N;
    int price[10000]={0};               //存储N天的价格
    bool trade[10000]={0};              //存储是否交易
    int Pay=0;
    int Income=0;
    for(int i=0;i<N;i++){
        cin>>price[i];
        Pay+=price[i];
    }
    Pay-=price[N-1];                    //最后一天不买股票
    for(int i=0;i<N;i++){
        for(int j=0;j<i;j++){
            if(trade[j]==0 && price[j]<price[i]){
                trade[j]=1;
                Income+=price[i];
            }
        }
    }
    for(int i=0;i<N-1;i++){             //最后一天没买，因此也不卖
        if(trade[i]==0){
            Income+=price[N-1];
        }
    }
    cout<<Income-Pay<<endl;


    return 0;

}