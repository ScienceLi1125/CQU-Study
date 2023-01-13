//实现log(N)取整形式的值的输出，cmath头文件下的log以e为底
#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n;
    cin>>n;
    //cout<<log(exp(n+1));
    float p=log(n)/log(2);
    int q=log(n)/log(2);
    if(p!=q){
        q++;
    }
    // if(log(n) % log(2)!=0){      //取模运算只针对整数
    //     p++;
    // }
    cout<<q;
    
    return 0;
}
