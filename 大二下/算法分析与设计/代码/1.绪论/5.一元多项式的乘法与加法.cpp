/*一元多项式的乘法与加法运算
题目：设计函数分别求两个一元多项式的乘积与和。
输入：分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对
    值均为不超过1000的整数）。数字间以空格分隔。
输出：分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结
    尾不能有多余空格。零多项式应输出0 0。
输入样例:
4 3 4 -5 2  6 1  -2 0
3 5 20  -7 4  3 1
输出样例:
15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int a[2002]={0};
    int b[2002]={0};
    int sum[2002]={0};
    int product[4002]={0};
    int A,B;
    cin>>A;
    for(int i=0;i<A;i++){
        int ratio,index;            //系数和指数
        cin>>ratio>>index;
        a[1000+index]=ratio;        //防止负指数
    }
    cin>>B;
    for(int i=0;i<B;i++){
        int ratio,index;
        cin>>ratio>>index;
        b[1000+index]=ratio;
    }
    for(int i=0;i<2002;i++){
        sum[i]=a[i]+b[i];
    }
    for(int i=0;i<2002;i++){
        for(int j=0;j<2001;j++){
            product[i+j]+=a[i]*b[j];
        }
    }
    //finished
    bool flag1=0,flag2=0;
    for(int i=4001;i>=0;i--){
        if(product[i]!=0){
            if(flag1!=0){
                cout<<" ";
            }
            else{
                flag1=1;
            }
            cout<<product[i]<<" "<<i-2000;
        }
    }
    if(flag1==0){
        cout<<"0 0";
    }
    cout<<endl;
    for(int i=2001;i>=0;i--){
        if(sum[i]!=0){
            if(flag2!=0){
                cout<<" ";
            }
            else{
                flag2=1;
            }
            cout<<sum[i]<<" "<<i-1000;
        }
    }
    if(flag2==0){
        cout<<"0 0";
    }

    return 0;
}