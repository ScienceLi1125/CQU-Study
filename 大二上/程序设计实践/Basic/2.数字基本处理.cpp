/*三个整数的统计：
题目：输入3个整数，计算这3个整数的和、平均值、乘积、最小值和最大值。
输入:在一行中给出3个整数。
输出:分别输出3个整数的和、平均值、乘积、最小值和最大值。每个结果各占一行。
*/
#include <iostream>
using namespace std;

int main() {
	int sum=0,multiply=1;
	float average;
	int max=0,min=32767;	//int型最大取值32767
	int num;
	for(int i=0;i<1000;i++){
		int m;
		cin>>m;
		num=i;
		if(m==-1)
			break;
		sum+=m;
		multiply*=m;
		max = max>m ? max:m;
		min = min<m ? min:m;
	}
	average = (float)sum/num;	//注意整形or浮点数以及几位小数
	cout << "Sum is " << sum << endl;
	cout << "Average is " << average << endl;
	cout << "Product is " << multiply << endl;
	cout << "Smallest is " << min << endl;
	cout << "Largest is " << max << endl;

	return 0;
}