/*顺序队列：假定数组是循环的，在数组中动态指定front和rear，来解决“移动队列”问题
此处为避免front和rear重合时无法判别数组为空还是满，采用n+1的数组存储n个元素的方法
*/
#include <iostream>
#include <stack>
using namespace std;

typedef int ElemType;
struct SqQueue{
    ElemType *array;            //数组
    int maxSize;				//顺序队列最大容积
	int front;					//队首元素下标
	int rear;					//队尾元素的下一个下标
};

void InitQueue(SqQueue &sq){
	int size;
	cin>>size;
	sq.maxSize=size+1;
	cin>>sq.front;
	cin>>sq.rear;
	sq.array=new ElemType[sq.maxSize];
	for(int i=sq.front;;i++){
		if((i%sq.maxSize)==sq.rear){
			break;				//到达队尾
		}
		int n;
		cin>>sq.array[i];
	}
}
void push(SqQueue &sq,ElemType it){
	if(sq.front==sq.rear){		//数组满了
		cout<<"SqStack is full!"<<endl;
	}
	else{
		sq.array[sq.rear]=it;
		sq.rear=(sq.rear+1)%sq.maxSize;
	}
}
void pop(SqQueue &sq){
	if(sq.front==sq.rear){
		cout<<"SqStack is empty!"<<endl;
	}
	else{
		sq.front=(sq.front+1)%sq.maxSize;
	}
}
ElemType frontValue(SqQueue sq){
	//使用前需判断非空
	return sq.array[sq.front];
}
ElemType rearValue(SqQueue sq){
	//使用前需判断非空
	return sq.array[(sq.front-1+sq.maxSize)%sq.maxSize];
}
int size(SqQueue sq){
	int len;
	if(sq.front<sq.rear){
		len=sq.rear-sq.front;
	}
	else{
		len=sq.rear-sq.front+sq.maxSize;
	}
	return len;
}

int main(){
	SqQueue sq;
	InitQueue(sq);
	push(sq,527);
	pop(sq);
	cout<<frontValue(sq)<<endl;
	cout<<rearValue(sq)<<endl;
	cout<<size(sq)<<endl;
	for(int i=sq.front;;i++){
		if((i%sq.maxSize)==sq.rear){
			break;
		}
		cout<<sq.array[i]<<" ";
	}


	return 0;
}