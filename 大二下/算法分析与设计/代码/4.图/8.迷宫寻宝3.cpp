/*迷宫寻宝1中要求最短路径，显然bfs更具优势。若只判断通路，则bfs/dfs均可。bfs同6.1，下用dfs判断
是否有通路
思路：dfs+栈
Sample Input1：
5
S.#..
#.#.#
#.#.#
#...E
#....
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
*/
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Pos{                                 //位置
    int x,y;
};
int n;
int mp[1001][1001]={{0}};       //迷宫(-1表示墙壁，0表示通路，1表示起点，2表示终点，3表示走过)
int path[1001][1001];
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};  //方向
stack<Pos> st;                              //路径
bool flag=0;                                //判断是否有通路

void printPath(stack<Pos> s){
    vector<Pos> v;
    while(!s.empty()){
        Pos tmp=s.top();
        s.pop();
        v.push_back(tmp);
    }
    for(int i=v.size()-1;i>=0;i--){
        cout<<"("<<v[i].x<<","<<v[i].y<<")";
    }
}

void dfs(Pos p){
    Pos cur=p;
    for(int i=0;i<4;i++){
        int tmpx=cur.x+dir[i][0];
        int tmpy=cur.y+dir[i][1];
        Pos tmpp{tmpx,tmpy};
        if(tmpx>=0&&tmpx<n && tmpy>=0&&tmpy<n && mp[tmpx][tmpy]!=-1){
            if(mp[tmpx][tmpy]==3){
                continue;           //查找过了，继续下一次查找
            }
            else if(mp[tmpx][tmpy]==2){
                st.push(tmpp);
                flag=1;
                return;
            }
            mp[tmpx][tmpy]=3;
            st.push(tmpp);
            dfs(tmpp);
            if(flag){               //快速跳出递归
                return;
            }
            st.pop();
        }
        
    }

}

int main(){
    cin>>n;
    char c;
    Pos start;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>c;
            path[i][j]=-1;
            if(c=='#'){
                mp[i][j]=-1;
            }
            else if(c=='.'){
                mp[i][j]=0;
            }
            else if(c=='S'){
                mp[i][j]=1;
                start=Pos{i,j};
                st.push(start);
                path[i][j]=0;
            }
            else if(c=='E'){
                mp[i][j]=2;
            }
        }
        getchar();
    }
    dfs(start);
    if(flag){
        cout<<"Accessible!\nOne of the path:\n";
        printPath(st);
    }
    else{
        cout<<"No solution!"<<endl;
    }

    return 0;
}