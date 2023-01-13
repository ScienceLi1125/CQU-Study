/*派对灯：
题目：在一次IOI派对上有N个灯(10<=N<=100)和4个灯开关，第一个开关可以使所有灯改变状态（关上开着
    的灯，开启关着的灯），第二个开关可以改变所有奇数位上灯的状态，第三个开关可以改变所有偶数位
    上灯的状态，第四个开关控制着灯 1、4、7、10……（3n+1）。
    一个计数器C记录按钮被按下的次数。当宴会开始，所有的灯都亮着，此时计数器C为0. 
    你将得到计数器C(0<=C<=10000)上的数值和经过若干操作后某些灯的状态，写一个程序去找出所有的
    灯最后可能的与所给出信息相符的状态，并且没有重复。
输入：不会有灯会在输入中出现两次
    第一行：N
    第二行：C最后显示的数值
    第三行：最后亮着的灯,用一个空格分开,以-1为结束
    第四行：最后关着的灯,用一个空格分开,以-1为结束
输出：每一行是所有灯可能的最后状态(没有重复)。如果没有可能的状态，则输出一行'IMPOSSIBLE'。
    每一行有N个字符，第1个字符表示1号灯，最后一个字符表示N号灯。0表示关闭，1表示亮着。
    这些行必须从小到大排列（看作是二进制数）。
思路：无论有多少个灯，由于开关控制的特殊性，都会出现6个灯一次循环的情况，
    即1号灯的状态永远与7，13，19号灯……相同，2号灯的状态也永远与8，14，20号灯……相同。
    并且，按同一个开关两次就相当于没有按该开关，所以每一个开关就只需要考虑按一次或没有按。
    那么这题的枚举量就很小了。
    （但由于本体给定了C，即按开关总数确定，因此按两次开关有存在的意义且不会出现无穷递归。
    若题目类似 时钟调整 ，则需判断开关次数保证无重复操作）
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N,C;
int Light[7]={0,1,1,1,1,1,1};   //只用考虑1~6号灯
vector<int> v1;                 //存储最后亮着的灯
vector<int> v0;                 //存储最后关着的灯
bool flag=0;                    //表示是否有合适解

int change(int light){          //01互换
    if(light==0){
        return 1;
    }
    else{
        return 0;
    }
}
void button(int n){             //按下开关n的操作
    if(n==1){
        for(int i=1;i<=6;i++){
            Light[i]=change(Light[i]);
        }
    }
    if(n==2){
        for(int i=1;i<=6;i+=2){
            Light[i]=change(Light[i]);
        }
    }
    if(n==3){
        for(int i=2;i<=6;i+=2){
            Light[i]=change(Light[i]);
        }
    }
    if(n==4){
        for(int i=1;i<=6;i+=3){
            Light[i]=change(Light[i]);
        }
    }
    return;
}

void dfs(int cnt){              //cnt表示操作数
    if(cnt==C){
        for(int j=0;j<v1.size();j++){
            if(Light[v1[j]]!=1){
                return;
            }
        }
        for(int j=0;j<v0.size();j++){
            if(Light[v0[j]]!=0){
                return;
            }
        }
//到这里还没有return表示灯最后的状态与所给出信息相符
        for(int i=1;i<=N/6;i++){
            for(int j=1;j<=6;j++){
                cout<<Light[j]<<" ";
            }
        }
        for(int k=1;k<=N%6;k++){
            cout<<Light[k]<<" ";
        }
        cout<<endl;
        flag=1;
        return;
    }
    else{
        for(int i=1;i<=4;i++){  //按下开关i
            button(i);
            dfs(cnt+1);
            button(i);          //再按一次相当于还原
        }
    }
    if(!flag){
        cout<<"IMPOSSIBLE"<<endl;
    }
}

int main(){
    cin>>N>>C;
    int m;
    while(cin>>m&&m!=-1){
        v1.push_back(m%6);      //%6只考虑1~6号灯
    }
    while(cin>>m&&m!=-1){
        v0.push_back(m%6);
    }
    dfs(0);

    return 0;
}