/*列车调度：
题目：火车站的列车调度铁轨的结构为：两端分别是一条入口轨道和一条出口轨道，它们之间有N条平行的轨道。每趟列车从入口可以选择任意一条轨道进入，最后从出口离开。例如：有9趟列车，在入口处按照{8，4，2，5，3，9，1，6，7}的顺序排队等待进入。如果要求它们必须按序号递减的顺序从出口离开，则至少需要多少条平行铁轨用于调度？
输入：第一行给出一个整数N (2≤N≤100000)，下一行给出从1到N的整数序号的一个重排列。数字间以空格分隔。
输出：在一行中输出可以将输入的列车按序号递减的顺序调离所需要的最少的铁轨条数。
思路：1.最开始的思路类似彩虹瓶，vector<vector<int> >存储降序序列。但操作复杂，因此需要转化
	2.由题意可知，所需要的最少的铁轨条数即为序列中最少下降子序列的个数，如题目中即为{8,4,2,1},{5,3},{9,6},{7},则为4条，因此在输入序列中寻找最少下降子序列个数即可。具体思路为遍历数组，后面元素比v[0]小即存入vector，遍历完一遍则将存入元素删除，再一次遍历，直至vector为空。
	3.由于2中是用vector进行删除，因此效率较低，测试样例极易超时，故改用list，比v[0]小的元素存储还用vector，便于访问。
	4.尽管上述做出的种种优化，还是会在N较大时出现超时，故需要在寻找最少下降子序列个数时做出优化。最少下降子序列个数可以用每个序列末位值（即最小值）来代替，又有集合自动排序，因此在向集合中插入元素时，寻找比该数字大的数字替代掉即可（由于操作的连贯性，最多只会出现一个），若集合中数字没有更大的，则直接插入。
*/
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

int main(){
	int N;
	cin>>N;
	list<int> l;
	for(int i=0;i<N;i++){
		int m;
		cin>>m;
		l.push_back(m);
	}
	int cnt=0;
	while(!l.empty()){
		vector<int> index;
		int tmp=l.front();
		for(list<int>::iterator i=l.begin();i!=l.end();i++){	
			if(*i<=tmp){
				index.push_back(*i);	//存入的是值而非下标
				tmp=*i;			//递减子序列的前一个值
			}
		}
		cnt++;
		for(int j=0;j<index.size();j++){
			for(list<int>::iterator it=l.begin();it!=l.end();it++){
				if(*it==index[j]){
					l.erase(it);
					break;
				}
			}
		}
	}
	cout<<cnt<<endl;

    return 0;
}