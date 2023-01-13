/*估算数学常数e的值：
题目：数学常数e是数学中一个重要的常数，它是一个无限不循环小数，其值约为2.71828。其计算公式为：
	e=1+1/1!+1/2!+1/3!+⋯+1/i!。这里输入需要的e值精度n（即参与计算e值的项1/i!都不小于1/10**n），
	其中3≤n≤10。编程计算输出相应精度的e值（保留n位小数）。
输入格式:e值精度，即e值的小数位数。
输出格式:相应精度的e值。
*/
#include <iostream>
#include <math.h>
using namespace std;

int main() {
	int n;
	cin>>n;
	double e = 1;		//float精度不足以算那么多位，用更高精度的double!!!
	double tmp=1;		//中间变量负责计算阶乘
	for(int i=1;i<15;++i){
		if(tmp<=pow(10,n)){
			tmp*=i;
        	e+=(1/tmp);
		}	
	}
	printf("%.*f",n,e);	//若用cout别忘了fixed（补零），否则会自动省去末位的0造成精度错误

	return 0;
}