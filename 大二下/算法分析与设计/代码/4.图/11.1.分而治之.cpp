/*分而治之:
题目：分而治之，各个击破是兵家常用的策略之一。在战争中，我们希望首先攻下敌方的部分城市，使其剩余
	的城市变成孤立无援，然后再分头各个击破。为此参谋部提供了若干打击方案。本题就请你编写程序，判
	断每个方案的可行性。
输入：在第一行给出两个正整数N和M（均不超过10000），分别为敌方城市个数（于是默认城市从1到N编号）
	和连接两城市的通路条数。随后M行，每行给出一条通路所连接的两个城市的编号，其间以一个空格分隔。
	在城市信息之后给出参谋部的系列方案，即一个正整数K（≤ 100）和随后的K行方案，每行按以下格式给
	出： Np v[1] v[2] ... v[Np] 。其中Np是该方案中计划攻下的城市数量，后面的系列v[i]是计划攻
	下的城市编号。
输出：对每一套方案，如果可行就输出YES，否则输出NO。
输入样例：
10 11
8 7
6 8
4 5
8 4
8 1
1 2
1 4
9 8
9 1
1 10
2 4
5
4 10 3 8 4
6 6 1 7 5 4 9
3 1 8 4
2 2 8
7 9 8 7 6 5 4 2
输出样例：
NO
YES
YES
NO
NO
思路：本以为邻接表实现图会简单一点，但本题为无向图，删除边时无法同时删除，因此还是采用相邻矩阵
	注意：判断每个样例是否成立时如果对图进行操作会造成后面结果无法还原(cutEdge行不通)，因此记录
	边的度比较即可(误)
	后发现上述办法行不通...
*/
#include <iostream>
using namespace std;

class Graph{
public:
    Graph(){}
    virtual ~Graph(){}
    virtual void Init(int n)=0;
    virtual int n()=0;
    virtual int e()=0;
    virtual int first(int v)=0;
    virtual int next(int v,int w)=0;
    virtual void setEdge(int v1,int v2,int weight)=0;
    virtual void delEdge(int v1,int v2)=0;
    virtual bool isEdge(int i,int j)=0;
    virtual int weight(int v1,int v2)=0;
    virtual int getMark(int v)=0;
    virtual void setMark(int v,int value)=0;
};
class Graphm:public Graph{
private:
    int numVertex,numEdge;
    int **matrix;
    int *mark;          //mark数组描述节点状态，0表示未访问，1表示已访问
public:
    Graphm(int num){
        Init(num);
    }
    ~Graphm(){
        delete [] mark;
        for(int i=0;i<=numVertex;i++){
            delete [] matrix[i];
        }
        delete [] matrix;
    }
    void Init(int n){
        numVertex=n;
        numEdge=0;
        mark=new int[n+1];
        for(int i=0;i<=numVertex;i++){
            mark[i]=0;
        }
        matrix=(int**)new int*[numVertex+1];
        for(int i=0;i<=numVertex;i++){
            matrix[i]=new int[numVertex+1];
        }
        for(int i=0;i<=numVertex;i++){
            for(int j=0;j<=numVertex;j++){
                matrix[i][j]=0;
            }
        }
    }
    int n(){
        return numVertex;
    }
    int e(){
        return numEdge;
    }
    int first(int v){
        for(int i=1;i<=numVertex;i++){
            if(matrix[v][i]!=0){
                return i;
            }
        }
        return numVertex+1;
    }
    int next(int v,int w){
        for(int i=w+1;i<=numVertex;i++){
            if(matrix[v][i]!=0){
                return i;
            }
        }
        return numVertex+1;
    }
    void setEdge(int v1,int v2,int weight){
        if(matrix[v1][v2]==0){
            numEdge++;
        }
        matrix[v1][v2]=weight;
    }
    void delEdge(int v1,int v2){
        if(matrix[v1][v2]!=0){
            numEdge--;
        }
        matrix[v1][v2]=0;
    }
    bool isEdge(int i,int j){
        return matrix[i][j]!=0;
    }
    int weight(int v1,int v2){
        return matrix[v1][v2];
    }
    int getMark(int v){
        return mark[v];
    }
    void setMark(int v,int value){
        mark[v]=value;
    }
	int degree(int v){
		int cnt=0;
		for(int i=1;i<=numVertex;i++){
			if(matrix[v][i]!=0)	cnt++;
		}
		return cnt;
	}
	// void cutEdge(int n){	//删除掉节点n的所有边
	// 	for(int j=1;j<=numVertex;j++){
	// 		matrix[n][j]=0;
	// 	}
	// 	for(int i=1;i<=numVertex;i++){
	// 		matrix[i][n]=0;
	// 	}
	// }
	// bool isIsolated(){
	// 	for(int i=1;i<=numVertex;i++){
	// 		for(int j=1;j<=numVertex;j++){
	// 			if(matrix[i][j]!=0)	return 0;
	// 		}
	// 	}
	// 	return 1;
	// }
	void Print(){
		for(int i=1;i<=numVertex;i++){
			for(int j=1;j<=numVertex;j++){
				cout<<matrix[i][j]<<" ";
			}
			cout<<endl;
		}
	}
};

int main(){
    int N,M;
	cin>>N>>M;
	Graphm graph(N);
	for(int i=0;i<M;i++){
		int a,b;
		cin>>a>>b;
		graph.setEdge(a,b,1);
		graph.setEdge(b,a,1);
	}
	int K;
	cin>>K;
	for(int i=0;i<K;i++){
		int Np;
		cin>>Np;
		int cnt=0;
		for(int j=1;j<=Np;j++){
			int c;
			cin>>c;
			cnt+=graph.degree(c);
		}
		if(graph.e()==cnt*2)	cout<<"YES"<<endl;
		else	cout<<"NO"<<endl;
	}
	// graph.Print();

    return 0;
}
