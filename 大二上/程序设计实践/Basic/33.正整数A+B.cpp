/*正整数A+B:
题目：求两个正整数A和B的和，其中A和B都在区间[1,1000]。稍微有点麻烦的是，输入并不保证是两个正整数。
输入：在一行给出A和B，其间以空格分开。问题是A和B不一定是满足要求的正整数，有时候可能是超出范围的数字、负数、带小数点的实数、甚至是一堆乱码。
    注意：我们把输入中出现的第1个空格认为是A和B的分隔。题目保证至少存在一个空格，并且B不是一个空字符串。
输出：如果输入的确是两个正整数，则按格式 A + B = 和 输出。如果某个输入不合要求，则在相应位置输出?，显然此时和也是?。
*/
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

int main(){
    string A="",B="";
    int nA,nB;
    char AB[100];
    cin.get(AB,100);
    bool flagA=1,flagB=1;
    stringstream ss;
    int l=strlen(AB);
    int l0;                     //用来存储第一个空格的位置
    for(int i=0;i<l;i++){
        if(AB[i]==' '){         //题目保证至少存在一个空格
            l0=i;
            break;
        }
    }
    for(int i=0;i<l0;i++){
        A+=AB[i];
        if(AB[i]<'0' || AB[i]>'9'){
            flagA=0;
        }
    }
    if(A.length()==0){
        flagA=0;                //题目保证B不是一个空字符串，但A可能为空
    }
    for(int i=l0+1;i<l;i++){
        B+=AB[i];
        if(AB[i]<'0' || AB[i]>'9'){
            flagB=0;
        }
    }

    if(flagA){                  //此处flagA只判断了都是整数
        ss<<A;
        ss>>nA;
        ss.clear();
        if(nA>=1&&nA<=1000){
            cout<<nA;
        }
        else{
            cout<<"?";
            flagA=0;            //别忘了改flagA
        }
    }
    else{
        cout<<"?";
    }
    cout<<" + ";
    
    if(flagB){
        ss<<B;
        ss>>nB;
        if(nB>=1&&nB<=1000){
            cout<<nB;
        }
        else{
            cout<<"?";
            flagB=0;
        }
    }
    else{
        cout<<"?";
    }
    
    cout<<" = ";
    if(flagA&&flagB){
        cout<<nA+nB;
    }
    else{
        cout<<"?";
    }

    return 0;
}

/*刚开始处理输入的思路的是string A,char B[100],但当A为空时会发生错误
同时还要注意cin>>A,cin.get(B,100)中用getchar()吃掉空格
*/