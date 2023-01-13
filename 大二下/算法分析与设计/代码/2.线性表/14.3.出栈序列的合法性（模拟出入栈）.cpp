/*法二：模拟入栈出栈过程
    即将输入存储在队列中，从1到N遍历，将数值从队列中压入栈中。其中若栈顶元素和队首元素相等则同时
弹出直至不同
*/
#include<iostream>
#include<stack>
#include<queue>
using namespace std;

int main(){
    int M,N,K;
    cin>>M>>N>>K;
    for(int i=0;i<K;i++){
        queue<int> a;
        stack<int> b;
        int p;
        for(int k=0;k<N;k++){
            cin>>p;
            a.push(p);
        }
        for(int j=1;j<=N;j++){
            if(b.size()==M)
                break;
            else
                b.push(j);
            while(!b.empty()&&!a.empty()&&a.front()==b.top()){
                a.pop();
                b.pop();
            }
        }
        if(a.empty())
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    return 0;
}