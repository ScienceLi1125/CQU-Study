#include <iostream>
using namespace std;

float &cut(float &a,float &b){  //float &表示返回值类型为一个浮点数的引用
    return (a<b?a:b);
}

int main(){
    float a,b;
    cin>>a>>b;
    cut(a,b)=0;                 //给定主函数中对函数返回值赋值，因此不能直接返回数值
    cout<<"to pay:"<<a+b<<endl;    
    return 0;
}