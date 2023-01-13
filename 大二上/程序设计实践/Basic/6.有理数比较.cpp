/*有理数比较：
题目：本题要求编写程序，比较两个有理数的大小。
输入：输入在一行中按照“a1/b1 a2/b2”的格式给出两个分数形式的有理数，其中分子和分母全是整形范围
	内的正整数。
输出：在一行中按照“a1/b1 关系符 a2/b2”的格式输出两个有理数的关系。其中“>”表示“大于”，“<”表示
	“小于”，“=”表示“等于”。
*/
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main() {
	string s1,s2;
	cin >> s1 >>s2;						//s1表示字符串"a1/b1",若用float表示会自动保存为整数
	int a1=0,b1=0,a2=0,b2=0,num1,num2;			//num1,num2用来标记‘/’在s1,s2出现位置
	for(int i=0;i<s1.size();i++){
		if(s1[i]=='/'){
			num1=i;					//找到“/”
			break;
		}
	}
	for(int i=0;i<num1;i++){
		a1+=((int)s1[i]-48)*pow(10,num1-i-1);	//C++中不支持string转int,并且不支持切片
	}
	for(int i=num1+1;i<s1.size();i++){			//通过ACSII码转成int,其中减去的48是0的ASCII码的值
		b1+=((int)s1[i]-48)*pow(10,s1.size()-i-1);//将每一位转成十进制整数
	}

	for(int i=0;i<s2.size();i++){
		if(s2[i]=='/'){
			num2=i;
			break;
		}
	}
	for(int i=0;i<num2;i++){
		a2+=((int)s2[i]-48)*pow(10,num2-i-1);
	}
	for(int i=num2+1;i<s2.size();i++){
		b2+=((int)s2[i]-48)*pow(10,s2.size()-i-1);
	}
	
	if(a1*b2>a2*b1)
        	cout <<s1<<" > "<<s2<<endl;
    	if(a1*b2<a2*b1)
        	cout <<s1<<" < "<<s2<<endl;
    	if(a1*b2==a2*b1)
        	cout <<s1<<" = "<<s2<<endl;


	return 0;
}