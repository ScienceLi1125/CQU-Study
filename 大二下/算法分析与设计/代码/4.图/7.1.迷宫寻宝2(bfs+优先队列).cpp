/*迷宫寻宝2：
题目：用字符矩阵表示迷宫，其中字符'#'表示不可达的墙壁，'@'表示可达的位置，和位于其上下左右的可达位
    置相互连通，但和斜方向的位置不连通。从可达位置走到与其连通的位置需要花费一分钟。'S’和'G'分别表
    示迷宫的起点位置和终点位置（可达），小写英文字母表示该位置可达且放置有宝物箱。每个宝物箱有唯一
    的编号：第1号箱子用'a'表示，第2号用'b'，依次连续编号。冒险者的任务是从起点出发搜寻各宝物箱，打
    开全部箱子并取走宝物，最终走到终点'G'。第k号箱子只能在前面的k-1个箱子全部打开后才能打开，否则
    该位置只能经过。打开箱子不需要时间，但无论打不打开箱子，每次走到有箱子的位置时都必须滞留额外的
    一分钟时间，然后才能经过该位置。求冒险者完成任务所需的最短时间。
输入：第一行给出两个整数N和K(2<N≤100, 1≤K≤20)。接下来N行，每行有长度为N的字符串，以换行符结尾，
    表示N×N的迷宫。K表示迷宫中放置的宝物箱数量，用英文字符'a','b',...,'a'+K-1表示。
输出：冒险者从起点位置出发，依次取走所有宝物，最终到达终点的最少时间。
思路：利用贪心算法，将路径划分为S->a,a->b,b->c,...,x->G，再分段进行bfs即可。
注意：此时继续使用队列存储的话，会因宝箱滞留时间造成错误，样例如下：
@ @ @ @ @ @
a c d e @ b
bfs时a->c->d->e->@->b会比a->@->@->@->@->@->@->b先进入队列（bfs步数决定），但前者耗时更多
    因此采用!!!优先队列!!!，进入队列的顺序仍按遍历顺序，但队列自动排序功能将不同节点按从起点到达
该点的时间长短排序，于是bfs搜索顺序不再受影响
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Pos{
    int x,y;
};
int N,K;
int mp[101][101]={{0}};     //-2表示不通，-1表示通路，0表示起点，1~K表示宝物，K+1表示终点
int path[101][101]={{0}};   //记录路径
Pos node[21];               //存储宝物位置
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

struct cmp{                                 //定义优先队列的比较方式
    bool operator()(Pos a, Pos b) {
        return path[a.x][a.y]>path[b.x][b.y];
    }
};
priority_queue<Pos,vector<Pos>,cmp> q;      //优先队列存储节点
Pos cur{-1,-1};
int time=0;                                 //总时间

void bfs(Pos p){
    while(!q.empty()){
        cur=q.top();
        q.pop();
        int level=path[cur.x][cur.y];       //当前节点的层数
        if(cur.x==p.x && cur.y==p.y){       //出队才算到达
            time+=path[cur.x][cur.y];
            return;
        }
        for(int i=0;i<4;i++){
            int tmpx=cur.x+dir[i][0];
            int tmpy=cur.y+dir[i][1];
            if(tmpx>=0&&tmpx<N && tmpy>=0&&tmpy<N && mp[tmpx][tmpy]!=-2){//保证边界内的通路 
                //if(cur.x==p.x && cur.y==p.y)  //遍历到并不代表结束，只是入队
                //用path标记走过代替标记mp，否则下一段bfs无法恢复mp
                if(mp[tmpx][tmpy]==-1 && path[tmpx][tmpy]==-1){
                    path[tmpx][tmpy]=level+1;
                    q.push(Pos{tmpx,tmpy});
                }
                else if(mp[tmpx][tmpy]>=1 && mp[tmpx][tmpy]<=K && path[tmpx][tmpy]==-1){
                    path[tmpx][tmpy]=level+2;
                    q.push(Pos{tmpx,tmpy});
                }
                else if(mp[tmpx][tmpy]==K+1 && path[tmpx][tmpy]==-1){   //遍历到G
                    path[tmpx][tmpy]=level+1;
                    q.push(Pos{tmpx,tmpy});
                }
            }
        }
    }
}

int main(){
    cin>>N>>K;
    char c;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>c;
            if(c=='#'){
                mp[i][j]=-2;
            }
            else if(c=='@'){
                mp[i][j]=-1;
            }
            else if(c=='S'){
                mp[i][j]=0;
                node[0]=Pos{i,j};
            }
            else if(c=='G'){
                mp[i][j]=K+1;
                node[K+1]=Pos{i,j};
            }
            else{           //输入的是宝物编号
                mp[i][j]=c-'a'+1;
                node[c-'a'+1]=Pos{i,j};
            }
        }
        getchar();
    }
    for(int i=0;i<=K;i++){          //分段bfs
        q.push(node[i]);            //起点入队
        for(int i=0;i<N;i++){       //bfs前需要刷新路径
            for(int j=0;j<N;j++){
                path[i][j]=-1;
            }
        }
        path[node[i].x][node[i].y]=0;
        bfs(node[i+1]);
        while(!q.empty()){          //清空队列
            q.pop();
        }
    }
    cout<<time<<endl;
    // for(int i=0;i<=K+1;i++){
    //     cout<<node[i].x<<" "<<node[i].y<<endl;
    // }
    // for(int i=0;i<N;i++){
    //     for(int j=0;j<N;j++){
    //         cout<<mp[i][j];
    //     }
    //     cout<<endl;
    // }
    
    return 0;
}