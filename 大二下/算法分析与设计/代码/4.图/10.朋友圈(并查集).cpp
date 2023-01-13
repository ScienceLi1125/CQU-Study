/*朋友圈:
题目：某学校有N个学生，形成M个俱乐部。每个俱乐部里的学生有着一定相似的兴趣爱好，形成一个朋友圈。
    一个学生可以同时属于若干个不同的俱乐部。根据“我的朋友的朋友也是我的朋友”这个推论可以得出，
    如果A和B是朋友，且B和C是朋友，则A和C也是朋友。请编写程序计算最大朋友圈中有多少人。
输入：第一行包含两个正整数N（≤30000）和M（≤1000），分别代表学校的学生总数和俱乐部的个数。后面的
    M行每行按以下格式给出1个俱乐部的信息，其中学生从1~N编号：
        第i个俱乐部的人数Mi 学生1 学生2 … 学生Mi
输出：给出一个整数，表示在最大朋友圈中有多少人。
输入样例:
7 4
3 1 2 3
2 1 4
3 5 6 7
1 6
输出样例:
4
思路：基础并查集
*/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int fa[30005]={0};
int find(int x){
	if(x == fa[x])
		return x;
	return fa[x]=find(fa[x]);
}

void Union(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy){
        return;
    }
	fa[fy]=fx;
}

int main()  {  
	int n,m,mi;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
        fa[i] = i ;
    }
	for(int i=0;i<m;i++){
		cin>>mi;
        int stu0,stu;
		for(int j=0;j<mi;j++){
			cin>>stu;
            if(j==0){
                stu0=stu;
            }
            else{
                Union(stu0,stu);
            }
		}
	}
	int max=0;
	map<int,int> mp;
	for(int i=1;i<=n;i++){
		mp[find(i)]++ ;
		if(mp[find(i)]>max){
			max=mp[find(i)];
		}
	}
	cout<<max<<endl;    

    return 0;
}