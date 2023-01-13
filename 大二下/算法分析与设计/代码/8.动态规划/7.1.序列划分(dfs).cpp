/*序列划分：
题目：给定一个长度为N(N>0)的序列，将其划分为K(K>0)段，使得每段的和的最大值最小
输入：第一行给出N，K，随后一行给出N个数的序列
输出：段的和的最大值的最小值
输入样例：
8 4
5 2 3 7 6 8 1 9
输出样例：
13
思路：dfs，循环内部比较最大值，每一步循环结束比较最小值
	注意分隔位置有0~N+1
*/
#include <iostream>
#include <vector>
using namespace std;

int Min=10000;				//min最大分段和
int N,K;
int sequence[100]={0};
vector<int> divide;			//存储分割位置(1~N-1)
int sum(int start,int end){	//计算[start,end)的序列和
	int cnt=0;
	for(int i=start;i<end;i++){
		cnt+=sequence[i];
	}
	return cnt;
}
void dfs(int cur,int sur){	//cur表示当前可分割位置，sur表示剩余分割数
	// cout<<"dfs("<<cur<<","<<sur<<")"<<endl;
	if(sur==0){				//划分为K段只需要K-1个划分
		int Max=sum(0,divide[0]);	//最大分段和
		// cout<<Max<<" ";
		for(int j=1;j<K-1;j++){
			int tmp=sum(divide[j-1],divide[j]);
			// cout<<tmp<<" ";
			if(tmp>Max)	Max=tmp;
		}
		int tmp=sum(divide[K-2],N);
		// cout<<tmp<<endl;
		// cout<<divide[K-2]<<" "<<N<<endl;
		if(tmp>Max)	Max=tmp;
		// cout<<Max<<endl;
		if(Max<Min){		//更新最大分段和的最小值
			Min=Max;
		}
		return;
	}
	for(int i=cur;i<=N-sur;i++){
		divide.push_back(i);
		dfs(i+1,sur-1);
		divide.pop_back();
	}
	return;
}

int main(){ 
	cin>>N>>K;	
	for(int i=0;i<N;i++){
		cin>>sequence[i];
	} 
	if(K==0){
		cout<<"No solution!";
		return 0;
	}
	dfs(1,K-1);				//分K段只需要K-1个分割处
	cout<<Min<<endl;

    return 0;
}