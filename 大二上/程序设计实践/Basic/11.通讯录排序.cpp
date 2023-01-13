/*通讯录排序：
题目：输入n个朋友的信息，包括姓名、生日、电话号码，本题要求编写程序，按照年龄从大到小的顺序依次输出通讯录。题目保证所有人的生日均不相同。
输入：第一行给出正整数n（<10）。随后n行，每行按照“姓名 生日 电话号码”的格式给出一位朋友的信息。
	其中“姓名”是长度不超过10的英文字母组成的字符串，“生日”是yyyymmdd格式的日期，“电话号码”是不超过17位的数字及+、-组成的字符串。
输出：按照年龄从大到小输出朋友的信息，格式同输出。
*/
#include <iostream>
#include <algorithm>		//sort函数的头文件
using namespace std;

typedef struct Book{		//定义一个名为Book的结构体
	char name[10];
	long int bir;
	char tel[18];
};					//此处必须加分号

bool compare(Book b1,Book b2){
	return b1.bir<b2.bir;
}


int main() {
	int n;
	cin >> n;
	Book a[100];		//Book结构体的数组，a是其名称，a[i]是把不同学生，里面存放三个元素，即name,bir,tel
	for(int i=0;i<n;i++){
		cin>>a[i].name;
		cin>>a[i].bir;
		cin>>a[i].tel;
	}

	sort(a,a+n,compare);	//sort函数

	for(int i=0;i<n;i++){
		cout<<a[i].name<<" "<<a[i].bir<<" "<<a[i].tel<<endl;
	}

	return 0;
}