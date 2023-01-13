/*顺序栈
*/
#include <iostream>
#include <stack>
using namespace std;

typedef int ElemType;
struct SqStack{
    ElemType *elem;             //数组
    int maxSize;
	int top;					//栈顶元素下标
};

//全局函数需要改动SqStack，因此参数必须为引用类型
void InitStack(SqStack &sq){
	cin>>sq.maxSize;
	sq.top=-1;					//top表示栈顶元素，因此初值不能为0
	sq.elem=new ElemType[sq.maxSize];
	int n;
	while(cin>>n && n!=-1){
		if(sq.top<sq.maxSize){
			sq.elem[sq.top+1]=n;
			sq.top++;
		}
		else{
			cout<<"SqStack is full!"<<endl;
			break;
		}
	}
}
void push(SqStack &sq,ElemType it){
	if(sq.top<sq.maxSize){
		sq.elem[sq.top+1]=it;
		sq.top++;
	}
	else{
		cout<<"SqStack is full!"<<endl;
	}
}
void pop(SqStack &sq){
	if(sq.top>=0){
		sq.top--;
	}
	else{
		cout<<"SqStack is empty!"<<endl;
	}
}
ElemType topValue(SqStack sq){
	//使用前需判断非空
	return sq.elem[sq.top];
}
int size(SqStack sq){
	return sq.top+1;
}

int main(){
	SqStack sq1;
	InitStack(sq1);
	cout<<sq1.top<<endl;
	push(sq1,98);
	cout<<topValue(sq1)<<endl;
	pop(sq1);
	cout<<topValue(sq1)<<endl;

	return 0;
}