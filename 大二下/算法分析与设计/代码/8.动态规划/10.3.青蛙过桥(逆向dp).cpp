/*青蛙过桥：
    本题实质上与8凑零钱问题如出一辙，因此采用逆向dp：即将从桥头到桥尾的path反过来看，从路径尾部
向前遍历，其中stone[n]、stone[n-1]、stone[n-2]均可以视为初始点，递推式不变，终点为stone[0]。当
求cnt[i]时若出现cnt[i+1]=cnt[i+2]或类似情况，相当于path从0~i都相同，在下一个结点处出现分歧，此
时为了字典序最小，显然选i+1
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main(){
    int N;
    cin>>N;
    int stone[155]={0};
    int cnt[155]={0};               //记录path后N-i步踩过的最少石头数
    int post[155]={0};              //记录后驱节点
    for(int i=0;i<=N;i++){
        cin>>stone[i];
    }
    cnt[N]=stone[N];                //注意这里初值不是0
    cnt[N-1]=stone[N-1];
    cnt[N-2]=stone[N-2];

    for(int i=N-3;i>=0;i--){
        int next=i+3;               //先赋初值，后面满足条件则调整
        if(cnt[i+2]<=cnt[i+3]){     //要挂等号，因为相等时选字典序小的
            next=i+2;
        }                           //两个if都要执行，不可以加else
        if(cnt[i+1]<=cnt[next]){    //巧妙比较最小值，而不必枚举所有情况
            next=i+1;
        }
        post[i]=next;
        cnt[i]=cnt[next]+stone[i];
    }
    
    cout<<cnt[0]<<endl;
    vector<int> path;
    for(int i=0;i<=N;i=post[i]){
        path.push_back(i);
        if(post[i]==0){
            break;
        }
    }
    for(int i=0;i<path.size();i++){
        if(i!=0)    cout<<" ";
        cout<<path[i];
    } 

    return 0;
}