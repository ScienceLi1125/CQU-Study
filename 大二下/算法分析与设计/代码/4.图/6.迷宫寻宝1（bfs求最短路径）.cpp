/*迷宫寻宝：
题目：洪尼玛今天准备去寻宝，在一个n*n （n行, n列）的迷宫中，存在着一个入口、一些墙壁以及一个宝藏。
    由于迷宫是四连通的，即在迷宫中的一个位置，只能走到与它直接相邻的其他四个位置（上、下、左、右）。
    现洪尼玛在迷宫的入口处，问他最少需要走几步才能拿到宝藏？若永远无法拿到宝藏，则输出-1。
输入：第一行为正整数n（n≤1000），表示迷宫大小。接下来n行，每行包括n个字符，其中字符“.”表示该位置为
    空地，字符“#”表示该位置为墙壁，字符“S”表示该位置为入口，字符“E”表示该位置为宝藏，输入数据中只
    有这四种字符，并且“S”和“E”仅出现一次。
输出：拿到宝藏最少需要走的步数，若永远无法拿到宝藏，则输出-1。
思路：定义结构体Pos，表示位置(x,y)。bfs结合队列实现。
    bfs类似于层序遍历，搜索最短路径根据层数即可，再开一个二维数组存储每层元素即可
Sample Input1：
5
S.#..
#.#.#
#.#.#
#...E
#....
Sample Output1：
7
Sample Input2：
10
#S######.#
......#..#
.#.##.##.#
.#........
##.##.####
....#....#
.#######.#
....#.....
.####.###.
....#...E#
Sample Output2：
22
*/
#include <iostream>
#include <queue>
using namespace std;

struct Pos{                                 //位置
    int x,y;
};
int n;
int mp[1001][1001]={{0}};       //迷宫(-1表示墙壁，0表示通路，1表示起点，2表示终点，3表示走过)
int path[1001][1001];
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};  //方向
queue<Pos> q;                               //路径
Pos cur{0,0};                               //当前位置
int cnt;                                    //最短路径
bool flag=0;                                //判断是否有通路

void bfs(){
    while(!q.empty()){
        cur=q.front();
        q.pop();
        int level=path[cur.x][cur.y];       //当前节点的层数
        for(int i=0;i<4;i++){
            int tmpx=cur.x+dir[i][0];
            int tmpy=cur.y+dir[i][1];
            if(tmpx>=0&&tmpx<n&&tmpy>=0&&tmpy<n){   //保证没超出边界
                //cout<<"mp["<<tmpx<<","<<tmpy<<"]"<<"="<<mp[tmpx][tmpy]<<",cnt="<<cnt<<endl;
                if(mp[tmpx][tmpy]==0){
                    mp[tmpx][tmpy]=3;               //标记走过
                    q.push(Pos{tmpx,tmpy});
                    path[tmpx][tmpy]=level+1;
                }
                else if(mp[tmpx][tmpy]==2){
                    flag=1;
                    path[tmpx][tmpy]=level+1;
                    cnt=level+1;
                    //break              //break只能跳出for循环，要想完全跳出函数需用return
                    return;              //达到终点（没必要继续进行了，因为后面的路径显然更长）
                }
            }
        }
    }
}

int main(){
    cin>>n;
    char c;
    for(int i=0;i<n;i++){                   //构造迷宫和路径
        for(int j=0;j<n;j++){
            cin>>c;
            path[i][j]=-1;                  //路径初值为-1，表示不在树中
            if(c=='#'){
                mp[i][j]=-1;
            }
            else if(c=='.'){
                mp[i][j]=0;
            }
            else if(c=='S'){
                mp[i][j]=1;
                q.push(Pos{i,j});
                path[i][j]=0;               //起点赋为第0层
            }
            else if(c=='E'){
                mp[i][j]=2;
            }
        }
        getchar();
    }
    bfs();
    if(flag){
        cout<<cnt<<endl;
    }
    else{
        cout<<-1<<endl;
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<path[i][j];
    //     }
    //     cout<<endl;
    // }

    return 0;
}