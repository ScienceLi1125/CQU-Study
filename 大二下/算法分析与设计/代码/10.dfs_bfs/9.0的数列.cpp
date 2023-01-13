/*计算结果为0的数列：
题目：递增数列：1 2 3 ... N，在相邻数字之间插入符号+，-或空格。其中‘+’表示加，‘-’表示减，
	空格' '表示组合成多位整数，比如“2+3  4+5  6-7”表示“2+34+56-7”。
	找出所有计算结果为0的长度为 N 的数列。
思路：由于顺序固定，又没有括号，因此直接深搜即可
*/
#include<iostream>
using namespace std;

int n,num;
char c0[50];
char c[3]= {' ','+','-'};

void dfs(int step) {
	if(step==n) {
		int sum=1,t=0;
		for(int i=1;i<=n-1;i++) {
			if(c0[i]==' '&&i==1) {
				t=1;
				while(c0[i]==' '&&i<=n-1){
					t*=10;
					t+=i+1;
					i++;
				}
 
				sum=t;
				i--;
				t=0;
				continue;
			}
			if(c0[i]=='+'&&c0[i+1]!=' ')
				sum+=i+1;
			else if(c0[i]=='-'&&c0[i+1]!=' ')
				sum-=(i+1);
			else if((c0[i]=='-'||c0[i]=='+')&&c0[i+1]==' ') {
				char s=c0[i++];
				while(c0[i]==' '&&i<=n-1) {
					t*=10;
					t+=i;
					i++;
				}
				t*=10;
				t+=i;
				if(s=='+')
					sum+=t;
				else
					sum-=t;
				i--;
				t=0;
			}
		}
		if(sum==0) {
			num++;
			for(int i=1; i<=n-1; i++)
				printf("%d%c",i,c0[i]);
			printf("%d\n",n);
		}
		return ;
	}
 
	for(int i=0;i<3;i++){
		c0[step]=c[i];
		dfs(step+1);
	}
 
 
}
int main() {
	cin>>n;
	for(int i=1;i<=n+2;i++){
		c0[i]='+';
	}
	dfs(1);

	return 0;
}