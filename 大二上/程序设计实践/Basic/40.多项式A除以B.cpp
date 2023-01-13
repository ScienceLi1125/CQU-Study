/*多项式A除以B：
题目：这仍然是一道关于A/B的题，只不过A和B都换成了多项式。你需要计算两个多项式相除的商Q和余R，其中R的阶数必须小于B的阶数。
输入：分两行，每行给出一个非零多项式，先给出A，再给出B。每行的格式如下：
	N e[1] c[1] ... e[N] c[N]
	其中N是该多项式非零项的个数，e[i]是第i个非零项的指数，c[i]是第i个非零项的系数。各项按照指数递减的顺序给出，保证所有指数是各不相同的非负整数，所有系数是非零整数，所有整数在整型范围内。
输出：分两行先后输出商和余，输出格式与输入格式相同，输出的系数保留小数点后1位。同行数字间以1个空格分隔，行首尾不得有多余空格。注意：零多项式是一个特殊多项式，对应输出为0 0 0.0。但非零多项式不能输出零系数（包括舍入后为0.0）的项。在样例中，余多项式其实有常数项-1/27，但因其舍入后为0.0，故不输出。
输入样例：
4 4 1 2 -3 1 -1 0 -1
3 2 3 1 -2 0 1
输出样例：
3 2 0.3 1 0.2 0 -1.0
1 1 -3.1
思路：按照大除法思路一步步填数字
难点：精度问题，可以用round函数事先处理，但要注意round函数会省略小数点后的0，因此输出时要补零也可以输出前不做处理，用fabs(q[i])<0.05来判断四舍五入保留一位小数后为0
*/
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

//数组大小设大一点，原先设的100，14分，有一个段错误；改成1000和2000，都是17分；改成5000，20分
double A[5000]={0};			//被除式
double B[5000]={0};			//除式
double q[5000]={0};			//商式
double r[5000]={0};			//余式

int main(){
	int N;
	cin>>N;
	int Amax;			   	//被除式最高次指数(用double无法读取下标)
	for(int i=0;i<N;i++){
		int a,b;
		cin>>a>>b;
		A[a]=b;
		if(i==0){
			Amax=a;
		}
	}
	int M;
	cin>>M;
	int Bmax;				//除式最高次指数
	for(int i=0;i<M;i++){
		int a,b;
		cin>>a>>b;
		B[a]=b;
		if(i==0){
			Bmax=a;
		}
	}

	for(int i=Amax-Bmax;i>=0;i--){
		q[i]=A[i+Bmax]/B[Bmax];
		for(int j=Bmax;j>=0;j--){
			A[i+j]-=q[i]*B[j];
		}
	}
	for(int i=0;i<=Amax;i++){
		r[i]=A[i];			//A[i]在求解过程中被不断改变，最终值即为余式
	}
	
	int qmax=0;				//商式最高次数
	int rmax=0;				//余式最高次数
	int qcnt=0;				//商式非零项总数
	int rcnt=0;				//余式非零项总数
	for(int i=0;i<=Amax-Bmax;i++){
		q[i]=round(q[i]*10)/10;		//保留一位小数（若小数点后为0则不会保留）
		if(q[i]){
			qcnt++;
			qmax=i;
		}
	}
	for(int i=0;i<Bmax;i++){
		r[i]=round(r[i]*10)/10;
		if(r[i]){
			rcnt++;
			rmax=i;
		}
	}

	cout<<qcnt;
	if(!qcnt){				//题干交代“零多项式是一个特殊多项式，对应输出为0 0 0.0”
		cout<<" 0 0.0";
	}
	else{
		for(int i=qmax;i>=0;i--){
			if(q[i]){
				printf(" %d %.1f",i,q[i]);
			}
		}
	}
	cout<<endl;
	cout<<rcnt;
	if(!rcnt){
		cout<<" 0 0.0";
	}
	else{
		for(int i=rmax;i>=0;i--){
			if(r[i]){
				printf(" %d %.1f",i,r[i]);
			}
		}
	}

    return 0;
}