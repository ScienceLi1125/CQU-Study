/*关于堆的判断：
题目：将一系列给定数字顺序插入一个初始为空的小顶堆H[]。随后判断一系列相关命题是否为真。
	命题分下列几种：
	1.x is the root：x是根结点；
	2.x and y are siblings：x和y是兄弟结点；
	3.x is the parent of y：x是y的父结点；
	4.x is a child of y：x是y的一个子结点。
输入：每组测试第1行包含2个正整数N（≤ 1000）和M（≤ 20），分别是插入元素的个数、以及需要判断的
	命题数。下一行给出区间[-10000,10000]内的N个要被插入一个初始为空的小顶堆的整数。之后M行，
	每行给出一个命题。题目保证命题中的结点键值都是存在的。
输出：对输入的每个命题，如果其为真，则在一行中输出T，否则输出F。

link：满二叉树是除最后一层无任何子节点外，其余每一层上的所有结点都有两个子结点。
	即共k层共有2**k-1个子叶。
	  完全二叉树（设深度为h），除第h层外，其它各层的结点数都达到最大个数，且第h层所有的结点都
	连续集中在最左边。
	  堆可以被看作一个完全二叉树，是利用完全二叉树的结构来维护的一维数组。
	  大顶堆：每个结点的值都大于或等于其左右孩子结点的值（arr[i]>=arr[2i+1]&&arr[i]>=arr[2i+2]）
	  小顶堆：每个结点的值都小于或等于其左右孩子结点的值（arr[i]<=arr[2i+1]&&arr[i]<=arr[2i+2]）
	其中arr[2i+1]是左节点 arr[2i+2]是右节点
*/
#include <iostream>
using namespace std;

int a[1002];
int n,m;

int find(int x){					//找到节点位置，即数组下标
	for (int i=1;i<=n;i++){
		if(a[i]==x){
			return i;
		}
	}
	return 0;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
//建立小顶堆的过程：按照序列顺序将元素逐层放入，若不满足结点小于等于其左右子结点，则交换
		cin>>a[i];
		int k=i;
		while(k>1 && a[k]<a[k/2]){		//即不满足arr[i]<=arr[2i+1]&&arr[i]<=arr[2i+2]
			swap(a[k],a[k/2]);
			k/=2;
		}
	}
	for(int j=0;j<m;j++){
		int x;
		cin>>x;
		string s;
		cin>>s;
		if(s=="is"){
			string ss;
			cin>>ss;
			if(ss=="the"){
				string sss;
				cin>>sss;
				if(sss=="root"){
					if(a[1]==x){
						cout<<"T"<<endl;		//a[1]就是根，看看是不是相等
					}
					else{
						cout<<"F"<<endl;
					}
				}
				else{
					string s1;
					int xx;
					cin>>s1>>xx;
					if(find(x)==find(xx)/2){	//父亲的下标等于儿子的下标除以二
						cout<<"T"<<endl;
					}
					else{
						cout<<"F"<<endl;
					}
				}
			}
			else if(ss=="a"){
				string s1,s2;
				int xx;
				cin>>s1>>s2>>xx;
				if(find(x)/2==find(xx)){		//儿子的下标除以二等于父亲的下标
					cout<<"T"<<endl;
				}
				else{
					cout<<"F"<<endl;
				}
			}
		}
		else if(s=="and"){
			int xx;
			string s1,s2;
			cin>>xx>>s1>>s2;
//父亲的下标等于儿子的下标整除以二，看看两个儿子的父亲是否相等，即判断两个人是不是siblings
			if(find(x)/2==find(xx)/2){
				cout<<"T"<<endl;
			}
			else{
				cout<<"F"<<endl;
			}
		}
	}
	return 0;
} 