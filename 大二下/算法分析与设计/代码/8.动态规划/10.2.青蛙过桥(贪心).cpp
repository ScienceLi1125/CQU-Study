/*青蛙过桥：
    但9.1的思路有些暴力，当N~150000时内存超限，下尝试一下贪心算法：引入一个新的数组len[]，表示青
蛙跳到该步时的经过的站次数（记len[0]=1）。当每次发现求dp[i]有多个选择时，我们总是选择len[i]的
较大者，因为len[i]越大说明序列越长，字典序越小（应该不太对）。当然，如果len相等就选择编号小的。
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int stone[155]={0};
int cnt[155]={0};           //记录前i步踩过的最少石头数
int len[155]={0};           //记录序列长度
int pre[155]={0};           //记录前驱节点

int main(){
    int N;
    cin>>N;
    for(int i=0;i<=N;i++){
        cin>>stone[i];
    }
    cnt[0]=stone[0];
    cnt[1]=stone[0]+stone[1];
    cnt[2]=stone[0]+stone[2];
    cnt[3]=stone[0]+stone[3];
    len[0]=1;
    len[1]=2;
    len[2]=2;
    len[3]=2;
    for(int i=4;i<=N;i++){
        int tmp_cnt=10000000;
        int tmp_len=0;
        int index;
        for(int j=i-3;j<i;j++){
            if(cnt[j]<tmp_cnt){
                tmp_cnt=cnt[j];
                tmp_len=len[j];
                index=j;
            }
            else if(cnt[j]==tmp_cnt){
                if(len[j]>tmp_len){
                    tmp_len=len[j];
                    index=j;
                }
                else if(len[j]==tmp_len){
                    index=index;        //长度相等的取小的
                }
            }
        }
        cnt[i]=tmp_cnt+stone[i];
        len[i]=tmp_len+1;
        pre[i]=index;
    }
    int ans=1000000;
    int s=150000;
    int index;
    for(int i=N-2;i<=N;i++){
        if(ans>cnt[i]){
            ans=cnt[i];
            s=len[i];
            index=i;
        }
        else if(ans==cnt[i]){
            if(s<len[i]){
                s=len[i];
                index=i;
            }
        }
    }
    cout<<ans<<endl;
    stack<int> st;
    while(index>0){
        st.push(index);
        index=pre[index];
    }
    st.push(0);
    while(!st.empty()){
        cout<<st.top();
        st.pop();
        if(!st.empty()){
            cout<<" ";
        }
    }

    return 0;
}