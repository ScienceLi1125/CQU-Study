/*装箱问题：
题目：假设有N项物品，大小分别为s1,s2,...,si,...,sN,其中si为满足1≤si≤100的整数。要把这些物品装
    入到容量为100的一批箱子（序号1-N）中。装箱方法是：对每项物品, 顺序扫描箱子，把该物品放入足以
    能够容下它的第一个箱子中。请写一个程序模拟这种装箱过程，并输出每个物品所在的箱子序号，以及放
    置全部物品所需的箱子数目。
输入：第一行给出物品个数N（≤1000）；第二行给出N个正整数si（1≤si≤100，表示第i项物品的大小）。
输出：按照输入顺序输出每个物品的大小及其所在的箱子序号，每个物品占1行，最后一行输出所需的箱子数目。
输入样例：
8
60 70 80 90 30 40 10 20
输出样例：
60 1
70 2
80 3
90 4
30 1
40 5
10 1
20 2
5
*/ 
#include <iostream>
#include <vector>
using namespace std;

//int Vsum(vector<int> v){
//	int ans=0;
//	for(int i=0;i<v.size();i++){
//		ans+=v[i];
//	}
//	return ans;
//}

int main(){
	int N;
	cin>>N;
	vector<int> v;
	for(int i=0;i<N;i++){
		int s;
		cin>>s;
		bool flag=0;
		for(int j=0;j<v.size();j++){
			if(v[j]+s<=100){
				v[j]+=s;
				flag=1;
				cout<<s<<" "<<j+1<<endl;
				break;
			}
		}
		if(!flag){
			v.push_back(s);
			cout<<s<<" "<<v.size()<<endl;
		}
	}
	cout<<v.size()<<endl;
	
	return 0;
}