/*图的m着色问题：
题目：给定无向连通图和m种不同的颜色，用这些颜色为该图各顶点着色，相邻顶点颜色不同，m尽可能小
    输入：第一行是顶点个数n(2<=n<=10),颜色数m(1<=m<=n),接下来为顶点关系(a,b为0时输入结束)
    输出：所有着色方案和方案总数
思路：用二维数组存储点的关系，一维数组存储点的着色情况(1,2,3...)，数组下标对应点的坐标
    利用回溯搜索答案，该过程实质为枚举所有情况，而不必运用图论的着色定理
    若无解则输出0，若着色数小于m也输出
*/
#include <iostream>
#include <vector>
using namespace std;

int graph[20][20]={0};
int color[20]={0};
int n,m;                        //放在全局减少函数中参数个数
int cnt=0;

bool judge(int p){              //判断与p点连通的点的着色情况
    for(int i=1;i<=n;i++){      //从1计数，让0保留默认值
        if(graph[i][p]&&color[i]==color[p]){
            return 0;
        }
    }
    return 1;
}

void dfs(int NO){               //NO表示着色点的编号
    if(NO>n){                   //满足条件，直接打印
        for(int i=1;i<=n;i++){
            cout<<color[i]<<" ";
        }
        cout<<endl;
        cnt++;
    }
    else{
        for(int i=1;i<=m;i++){
            color[NO]=i;
            if(judge(NO)){
                dfs(NO+1);
            }
            color[NO]=0;
        }
    }

}

int main(){
    cin>>n>>m;
    int a,b;
    while(scanf("%d %d",&a,&b)!=EOF&&a!=0&&b!=0){
        graph[a][b]=1;
        graph[b][a]=1;          //无向连通图
    }
    dfs(1);
    cout<<cnt;

    return 0;
}