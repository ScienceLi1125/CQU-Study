/*24点游戏：
假设输入数字顺序固定
思路：由于顺序固定，在不考虑括号的情况，运算式的形式为:a#b#c#d（＃表示加减乘除运算符）。
	接下来，考虑括号，在运算符号确定时，有下面这5种情况：
	1.((a#b)#c)#d
	2.(a#(b#c))#d
	3.a#((b#c)#d)
	4.(a#b)#(c#d)
	5.a#(b#(c#d))
	本题难度在于将循环的下标转换为加减乘除的函数，应采用函数指针数组
*/
#include <iostream>
using namespace std;

int Add(int a, int b){
    return a+b;
}
int Sub(int a, int b){
    return a-b;
}
int Mul(int a, int b){
	return a*b;
}
int Div(int a, int b){
    if(b == 0||a%b!=0)						//a%b!=0保证整除，否则不成立
        return -10000;						//返回一个足够小的数字使计算不成立
    return a/b;
}
 
int(*op[4])(int,int)={Add,Sub,Mul,Div};		//函数指针（C++强大之处）

char print(int i){							//打印凑24点的方法
	switch (i)
	{
	case 0:
		return '+';
		break;
	case 1:
		return '-';
		break;
	case 2:
		return '*';
		break;
	case 3:
		return '/';
		break;
	
	default:
		break;
	}
	return '0';
}

bool Game24Points(int a,int b,int c,int d){
	int num;								//表示计算的结果
    for(int i=0;i<4;i++){					//a,b之间的运算
        for(int j=0; j<4; j++){				//b,c之间的运算
            for(int k=0; k<4; k++){			//c,d之间的运算
                //((a#b)#c)#d
                num=op[k](op[j](op[i](a, b),c),d);
                if(num==24){
					cout<<"(("<<a<<print(i)<<b<<")"<<print(j)<<c<<")"<<print(k)<<d<<"=24"<<endl;
                    return true;
				}
                //(a#(b#c))#d
                num=op[k](op[j](a,op[i](b,c)),d);
                if(num==24){
					cout<<"("<<a<<print(j)<<"("<<b<<print(i)<<c<<"))"<<print(k)<<d<<"=24"<<endl;
                    return true;
				}
                //a#((b#c)#d)
                num=op[k](a,op[j](op[i](b,c),d));
                if(num==24){
					cout<<a<<print(k)<<"(("<<b<<print(i)<<c<<")"<<print(j)<<d<<")=24"<<endl;
                    return true;
				}
                //(a#b)#(c#d)
                num=op[k](op[i](a,b),op[j](c,d));
                if(num==24){
					cout<<"("<<a<<print(i)<<b<<")"<<print(k)<<"("<<c<<print(j)<<d<<")=24"<<endl;
                    return true;
				}
                //a#(b#(c#d))
                num=op[k](a,op[j](b,op[i](c,d)));
                if(num==24){
					cout<<a<<print(i)<<"("<<b<<print(k)<<"("<<c<<print(i)<<d<<"))=24"<<endl;
                    return true;
				}
            }
        }
    }
    return false;
}


int main(){
    int a,b,c,d;
	cin>>a>>b>>c>>d;
	if(Game24Points(a,b,c,d)){
		cout<<"Solvable!"<<endl;
	}
	else{
		cout<<"No Solutions!"<<endl;
	}
    
    return 0;
}