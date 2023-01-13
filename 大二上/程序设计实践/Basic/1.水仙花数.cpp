/*水仙花数：
题目：水仙花数是指一个N位正整数（N≥3），它的每个位上的数字的N次幂之和等于它本身。
	例如：153=1**3+5**3+3**3。本题要求编写程序,计算所有N位水仙花数。
输入：在一行中给出一个正整数N（3≤N≤7）。
输出:按递增顺序输出所有N位水仙花数，每个数字占一行。
*/
#include <iostream>
#include <iomanip>
#include<math.h>
using namespace std;

int main() {
	int N;
	cin >> N;
	int min = pow(10, N - 1);
	int max = pow(10, N) - 1;
	for (int i = min; i < max; ++i) {
		int n = i;
		int q = 0;
		for (int j = 1; j < N + 1; ++j) {
			q += pow(n % 10, N);    //模10得到末位数字
			n = n / 10;             //整除10可以去掉末位数字
		}
		if (q == i)
			cout << i << endl;
	}
	
	return 0;
}