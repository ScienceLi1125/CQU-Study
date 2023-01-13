/*栈实现迷宫走法：
题目：一个a*b的矩阵（边缘有围墙），-1表示墙，0表示通路，给定矩阵和起点、终点，判断是否有通路
思路：用栈存储走过的点，并时刻标记与更新，-2表示已走过；-3表示此路不通
    1.最初以起点初始化当前点p
    2.判断p是否为出口
        2.1.若p为出口，p入栈，并在地图相应位置赋-2，表示已经过，然后结束。
        2.2.若p不为出口，判断p是否有空白邻接点
            2.2.1.若有，p入栈，在地图相应位置赋-2，同时p更新为下一个空白邻接点
            2.2.2.若无，在p对应的地图位置上赋-3，同时弹出栈顶作为p
    3.栈非空，重复步骤2
输入样例1：
3
1 1
3 3
-1 -1 -1 -1 -1
-1 0 0 0 -1
-1 -1 0 0 -1
-1 -1 -1 0 -1
-1 -1 -1 -1 -1
输入样例2:
10
1 4
1 8
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1
-1 0 0 -1 0 0 0 -1 0 -1
-1 0 0 -1 0 0 0 -1 0 -1
-1 0 0 0 0 -1 -1 0 0 -1
-1 0 -1 -1 -1 0 0 0 0 -1
-1 0 0 0 -1 0 0 0 0 -1
-1 0 -1 0 0 0 -1 0 0 -1
-1 0 -1 -1 -1 0 -1 -1 0 -1
-1 -1 0 0 0 0 0 0 0 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1
*/
#include <iostream>
#include <stack>
#include <iomanip>
using namespace std;

#define N 20

struct Pos{
	int x,y;
};
struct Maze{                        //结构体Maze不仅包含迷宫图，还包含迷宫图大小和起点、终点
	int n;                          //迷宫大小
	Pos start,end;                  //起止坐标 
	int maze[N][N]={0};             //迷宫分布图:-1-->墙；0-->通路 
	//maze记得赋初值，否则默认值随机，易产生错误
}; 
//根据输入创建迷宫 
void CreateMaze(Maze &m){
    cin>>m.n;
	cin>>m.start.x>>m.start.y;
	cin>>m.end.x>>m.end.y;
	
	for(int i=0;i<=m.n+1;i++){
		for(int j=0;j<=m.n+1;j++){
			cin>>m.maze[i][j];
		}
	}
}
//判断当前点是否存在通路，通，返回第一个可通的坐标；不通，返回（-1，-1） 
Pos Pass(Maze m,Pos curpos){
	Pos nextpos={-1,-1};            //初始化表示无通路 
	int x=curpos.x;
	int y=curpos.y;
	//每次都按顺序查找，走过的路被标记为-2，所以不会再走 
	//此处按照东西南北顺序查找，二维数组x朝下，y朝右，所以应注意方向 
	if(m.maze[x][y+1]==0){          //东 
		nextpos.x=x;
		nextpos.y=y+1;
	}
	else if(m.maze[x+1][y]==0){     //南 
		nextpos.x=x+1;
		nextpos.y=y;
	}
	else if(m.maze[x][y-1]==0){     //西 
		nextpos.x=x;
		nextpos.y=y-1;
	}else if(m.maze[x-1][y]==0){    //北 
		nextpos.x=x-1;
		nextpos.y=y;
	}
	return nextpos; 
}
//走迷宫
void MazePath(Maze m){
	Pos curpos=m.start;
    Pos nextpos=Pass(m,curpos);
	stack<Pos> path_stack;          //路径栈存储走通迷宫的路径
	path_stack.push(m.start);
    while(!path_stack.empty()){
		nextpos=Pass(m,curpos);
        if(curpos.x==m.end.x && curpos.y==m.end.y){ //当前点为终点
			path_stack.push(curpos);                //当前点入路径栈
			m.maze[curpos.x][curpos.y]=-2;          //走过标记为-2
			break;
		}
        else{
            if(nextpos.x!=-1){                      //此路可通 
			    path_stack.push(curpos);            //当前点入路径栈
			    m.maze[curpos.x][curpos.y]=-2;      //该点已经走过
			    curpos = nextpos;                   //当前点更新为下一个点 
		    }
		    else{
			    m.maze[curpos.x][curpos.y]=-3;      //表示当前点不通
			    curpos=path_stack.top();            //当前点更新为栈顶元素 
			    path_stack.pop();                   //删除栈顶 
		    } 
        }
    }
	//展示结果
	if(path_stack.empty()){
        cout<<"死路一条！"<<endl;
    }
 	else{
        cout<<"成功走出迷宫！"<<endl;
 		stack<Pos> tmp_stack;       //由于path_stack弹出的元素是逆序，因此用tmp_stack存储
		int ord=0; 
 		//被标记为1的不全是路径上的点，但在栈中一定是路径上的点 
 		while(!path_stack.empty()){
 			curpos=path_stack.top();
 			path_stack.pop();
 			tmp_stack.push(curpos);	
		}
		while(!tmp_stack.empty()){
 			curpos=tmp_stack.top();
 			tmp_stack.pop();
 			m.maze[curpos.x][curpos.y]=ord;
            ord++;
		}
 		cout<<endl;
		for(int i=0;i<=m.n+1;i++){
			for(int j=0;j<=m.n+1;j++){
				if(m.maze[i][j]>0){
					cout<<setw(2)<<m.maze[i][j]<<" ";
				}
				else{
                    cout<<setw(2)<<" # ";
                }
			}
			cout<<endl;
		}
	}
} 
int main(){
	Maze m;
	CreateMaze(m);
    MazePath(m);

	return 0;
} 