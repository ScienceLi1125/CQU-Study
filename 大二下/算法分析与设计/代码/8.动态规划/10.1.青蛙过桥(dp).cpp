/*青蛙过桥：
题目：一座长度为n的桥，起点的一端坐标为0，且在整数坐标i处有a[i]个石头(0<=a[i]<=4)，一只青蛙从坐
    标0处开始起跳，一步可以跳的距离为1或2或3(即每一步都会落在整数点处)，青蛙落在i处会踩着该点的
    所有石头，求青蛙跳出这座桥最少踩多少个石头？并且输出依次跳过的坐标点路线，如果存在多种路线，
    输出字典序最小的那一条。
输入：第一行整数n(<150000),接着下一行会有n+1个由空格隔开的整数,即桥上各个坐标处石头数量。
输出：第一行为踩着最少石头个数,第二行为依次跳过的坐标点(字典序最小的)。
输入样例1:
10
1 2 1 3 0 3 1 2 1 1 2
输出样例1:
4
0 2 4 6 8
输入样例2:
100
1 2 0 4 0 1 3 4 2 2 1 3 1 4 0 3 0 1 2 3 3 2 2 0 1 0 0 0 0 1 2 1 3 4 0 3 4 4 1 0
4 1 3 1 1 2 3 4 4 4 0 2 0 1 1 1 3 1 3 2 1 2 4 1 2 1 4 1 0 0 1 2 3 0 2 4 4 0 0 4
2 0 0 2 1 3 3 3 0 0 2 0 0 1 2 4 2 2 2 4 0
输出样例:
36
0 2 4 5 8 10 12 14 16 17 20 23 25 26 27 28 31 34 35 38 39 41 44 47 50 52 54 57 60 63 65 68 69 70 73 74 77 78 81 82 85 88 89 91 92 94 97 100
思路：形同上周凑零钱问题，但凑零钱的硬币面额可以排序，与输入顺序无关；而本题中各点不能排序，与输入
    顺序有关。也就是说本题每一个状态只由其前3个状态决定，开一维数组记录踩过石头数量即可。但记录选
    择需要再开一个数组用来存储序列开头元素，若两组路径踩过的石头数量相同，则从序列开头向后遍历并判
    断序列字典序大小。为了减少重复子问题的计算，用string数组记录序列
    递推关系式：
    dp[i]=min{dp[i-1],dp[i-2],dp[i-3]}
*/
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int stone[155]={0};
int cnt[155]={0};           //记录前i步踩过的最少石头数
string sequence[155];       //记录序列

string toString(int n){
    stringstream ss;
    ss<<n;
    string s;
    ss>>s;
    return s;
}

void min(int n){            //查找cnt[i-1],cnt[i-2],cnt[i-3]最小值
    if(cnt[n-1]<cnt[n-2]){
        if(cnt[n-1]<cnt[n-3]){
            cnt[n]=cnt[n-1]+stone[n];
            sequence[n]=sequence[n-1]+" "+toString(n);
            return;
        }
        else if(cnt[n-1]>cnt[n-3]){
            cnt[n]=cnt[n-3]+stone[n];
            sequence[n]=sequence[n-3]+" "+toString(n);
            return;
        }
        else{               //需要比较序列大小
            cnt[n]=cnt[n-1]+stone[n];
            if(sequence[n-1]<sequence[n-2]){
                sequence[n]=sequence[n-1]+" "+toString(n);
            }
            else{           //若sequence[n-1]=sequence[n-2]显然选择n-2
                sequence[n]=sequence[n-2]+" "+toString(n);
            }
            return;
        }
    }
    else if(cnt[n-1]>cnt[n-2]){
        if(cnt[n-2]<cnt[n-3]){
            cnt[n]=cnt[n-2]+stone[n];
            sequence[n]=sequence[n-2]+" "+toString(n);
            return;
        }
        else if(cnt[n-2]>cnt[n-3]){
            cnt[n]=cnt[n-3]+stone[n];
            sequence[n]=sequence[n-3]+" "+toString(n);
            return;
        }
        else{
            cnt[n]=cnt[n-2]+stone[n];
            if(sequence[n-2]<sequence[n-3]){
                sequence[n]=sequence[n-2]+" "+toString(n);
            }
            else{
                sequence[n]=sequence[n-3]+" "+toString(n);
            }
            return;
        }
    }
    else{                   //cnt[n-1]=cnt[n-2]
        if(cnt[n-2]>cnt[n-3]){
            cnt[n]=cnt[n-3]+stone[n];
            sequence[n]=sequence[n-3]+" "+toString(n);
            return;
        }
        else if(cnt[n-2]<cnt[n-3]){
            cnt[n]=cnt[n-2]+stone[n];
            if(sequence[n-1]<sequence[n-2]){
                sequence[n]=sequence[n-1]+" "+toString(n);
            }
            else{
                sequence[n]=sequence[n-2]+" "+toString(n);
            }
            return;
        }
        else{               //cnt[n-1]=cnt[n-2]=cnt[n-3]
            cnt[n]=cnt[n-1]+stone[n];
            sequence[n]=sequence[n-1]+" "+toString(n);  //防止没进任何一层循环
            string a=sequence[n-1];
            string b=sequence[n-2];
            string c=sequence[n-3];
            if(a>b){
                if(b>=c){   //需要挂等号，因为相等时选择n-3
                    sequence[n]=c+" "+toString(n);
                    return;
                }
                else{
                    sequence[n]=b+" "+toString(n);
                    return;
                }
            }
            else if(a<b){
                if(a>=c){
                    sequence[n]=sequence[n-3]+" "+toString(n);
                    return;
                }
                else{
                    sequence[n]=sequence[n-1]+" "+toString(n);
                    return;
                }
            }else{
                if(b>=c){
                    sequence[n]=sequence[n-3]+" "+toString(n);
                    return;
                }
                else{
                    sequence[n]=sequence[n-2]+" "+toString(n);
                    return;
                }
            }
            return;
        }
    }
}/*
min函数写的有点复杂，可以采用for循环(line181~191)遍历min代码量只有10行
*/

int main(){
    int N;
    cin>>N;
    for(int i=0;i<=N;i++){
        cin>>stone[i];
    }
    if(N==0){
        cout<<stone[0]<<endl<<0<<endl;
        return 0;
    }
    else if(N==1){
        cout<<stone[0]<<endl<<0<<endl;
        return 0;
    }else if(N==2){
        cout<<stone[0]<<endl<<0<<endl;
        return 0;
    }
    cnt[0]=stone[0];
    cnt[1]=stone[0]+stone[1];
    cnt[2]=stone[0]+stone[2];
    cnt[3]=stone[0]+stone[3];
    sequence[0]="0";
    sequence[1]="0 1";
    sequence[2]="0 2";
    sequence[3]="0 3";

    for(int i=4;i<=N;i++){
        min(i);
        // cout<<"cnt["<<i<<"]="<<cnt[i]<<"sequence["<<i<<"]="<<sequence[i]<<endl;
    }
    int ans=100000;
    string s="9";
    for(int i=N-2;i<=N;i++){
        if(ans>cnt[i]){
            ans=cnt[i];
            s=sequence[i];
        }
        else if(ans==cnt[i]){
            if(s>sequence[i]){
                s=sequence[i];
            }
        }
    }
    cout<<ans<<endl<<s<<endl;
    // for(int i=0;i<=N;i++){
    //     cout<<cnt[i]<<" "<<sequence[i]<<endl;
    // }

    return 0;
}