/*序列划分：
输入样例：
8 4
5 2 3 7 6 8 1 9
输出样例：
13
思路：动态规划，设d[i][j]表示将前i个元素划分为j段的最小最大和，sum[i][j]为序列i~j位的和(i<=j)
	则满足递推式：
		d[i][j]=sum[1][i]										(j=1)
				max(sequence[k])(k=1,...,i)						(i=j)
				min(max{d[k][j-1],sum[k+1][i]})	(k=j-1,...,i-1)	(i>j)
*/
#include <iostream>
#include <vector>
using namespace std;
#define Inf 100000

int main(){ 
	int N,K;
	int sequence[100]={0};
	cin>>N>>K;	
	for(int i=1;i<=N;i++){
		cin>>sequence[i];
	}
	int sum[100][100];		//i~j的序列和
	int dp[100][100];		//前i个任务划分成j段的最小sum值
	for(int i=1;i<=N;i++){
		for(int j=i;j<=N;j++){
			if(j==i)	sum[i][j]=sequence[i];
			else{
				sum[i][j]=sum[i][j-1]+sequence[j];
			}
		}
	}
	dp[0][0]=0;
	for(int i=1;i<=N;i++){
		for(int j=1;j<N;j++){
			if(j==1)	dp[i][j]=sum[1][i];
			if(i==j)	dp[i][j]=dp[i-1][j-1]>sequence[i]?dp[i-1][j-1]:sequence[i];
		}
	}
	
	for(int i=2;i<=N;i++){
		for(int j=2;j<i;j++){
			int min=Inf;
			for(int k=j-1;k<i;k++){
				int tmp=dp[k][j-1]>sum[k+1][i]?dp[k][j-1]:sum[k+1][i];
				if(min>tmp)	min=tmp;
			}
			dp[i][j]=min;
		}
	}
	// for(int i=1;i<=N;i++){
	// 	for(int j=1;j<=i;j++){
	// 		cout<<dp[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	if(K==0||K>N){
		cout<<"No solution!";
	}
	else{
		cout<<dp[N][K]<<endl;
	}

    return 0;
}