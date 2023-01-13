/*打印杨辉三角：
题目：本题要求按照规定格式打印前N行杨辉三角。
输入：在一行中给出N（1≤N≤10）。
输出：以正三角形的格式输出前N行杨辉三角。每个数字占固定4位。
*/
#include <iostream>
using namespace std;

int ComNum(int n,int m){		//定义函数计算组合数combination number Cnm
	int tmp1=1,tmp2=1;
	for(int i=n;i>n-m;i--){
		tmp1*=i;
	}
	for(int j=1;j<m+1;j++){
		tmp2*=j;
	}
	return tmp1/tmp2;
}

int length(int p){				//定义函数输出1000以内正整数的位数
	if(p<10){
		return 1;
	}
	else if(p>=10 && p<100){
		return 2;
	}
	else{
		return 3;
	}
}

int main() {
	int N;
	cin >> N;
	for(int t=0;t<N+2;t++){				//组合数C00无意义，单独输出
		cout << " ";
	}
	cout<<1<<endl;			
	for(int i=1;i<N;i++){				//行循环
		for(int k=0;k<N-i-1;k++){		//事先打印每行开头多出的空格（N-i-1个）
			cout << " ";
		}
		for(int j=0;j<i+1;j++){			//列循环
			int tmp3=ComNum(i,j);		//tmp3表示第i行第j列的数字
			for(int q=0;q<4-length(tmp3);q++){
				cout<<" ";
			}
			cout << tmp3;
		}
		cout << endl;				//每行输出结束需要换行

	}
	

	return 0;
}