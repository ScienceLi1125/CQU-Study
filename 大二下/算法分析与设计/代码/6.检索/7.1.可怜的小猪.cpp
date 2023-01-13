/*可怜的小猪1：
题目：有n桶水，其中有且只有一桶中有毒药，其余都是水。小猪喝水后会在15min后死去。现给你15分钟时间，
    问最少需要多少只猪才能测出有毒药的桶
思路：设需要m头猪，每头猪都有生/死两种状态，共计2**m种状态（0~2**m-1）。n桶水用二进制标号，0表示
    小猪不喝该桶水，1表示喝（如：第13桶水1101，则0、2、3号猪要喝该桶水），最后用毒死的小猪组成二
    进制数则表示有毒水的桶号
*/
#include <iostream>
#include <cmath>
using namespace std; 

int main(){
    int n;
    cin>>n;
    float p=log(n)/log(2);
    int m=log(n)/log(2);
    if(p!=m){
        m++;
    }
    cout<<m;
    
    return 0;
}
