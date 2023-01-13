#include <iostream>
#include <algorithm>
using namespace std;

//声明为全局变量便于函数中使用，避免函数中参数过多
//全局数组回溯，不必一次次调用vector，比较快
int tot=0;
int N;
int col[20]={0};    //col[]表示列的值

void dfs(int r)     //对行递归
{
    if (r==N)
        tot++;      //达到递归边界，方案数加一
    else
        for (int i=0;i<N;i++)           //对列判断
        {
            int flag=1;
            col[r]=i;                   //尝试把第r行皇后放在第i列
            for (int j=0;j<r;j++)       //检查是否和前面的皇后冲突
                if (col[r]==col[j] || r-col[r]==j-col[j] || r+col[r]==j+col[j]){
                    flag=0;
                    break;
                }
            if (flag)
                dfs(r+1);
        }
}

int main(){
    cin>>N;
    dfs(0);
    cout<<tot<<endl;

    return 0;
}