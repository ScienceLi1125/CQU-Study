/*队列模拟:
    设从键盘输入一整数序列a1，a2，...an，试编程实现：当ai>0 时，ai 进队，当ai<0 时，将队首元素出队，当ai=0 时，表示输入结束。要求将队列处理成环形队列，使用环形队列算法库中定义的数据类型及算法，程序中只包括一个函数（main 函数），入队和出队等操作直接在main 函数中调用即可。当进队出队异常（如队满）时，要打印出错信息。

输入格式:
输入一系列整数，以0结束。环形队列最多可存储10个元素。

输出格式:
输出最后队列中的元素。如果队列满，则显示“队列已满”,如果出队列时无元素可出，显示“wrong”

输入样例1:
1 2 3 -4 -5  6 7 -8 0
输出样例1:
The Queue is:6 7 
输入样例2:
1 2 -4 -5  -6 7 -8 0
输出样例2:
wrong
输入样例3:
1 2 3 4 5  6 7 8 9 10 11 12 0
输出样例3:
Queue is full!
The Queue is:1 2 3 4 5 6 7 8 9 10 
*/

#include <iostream>
#include <queue>
using namespace std;

int main(){
    queue<int> q;
    int a;
    bool flag=0;
    while(cin>>a&&a!=0){
        if(a>0){
            if(q.size()<10){
                q.push(a);
            }
            else{
                cout<<"Queue is full!"<<endl;
                cout<<"The Queue is:";
                while(!q.empty()){
                    cout<<q.front()<<" ";
                    q.pop();
                }
                flag=1;
                break;
            }
        }
        else if(a<0){
            if(q.size()>0){
                q.pop();
            }
            else{
                cout<<"wrong"<<endl;
                flag=1;
                break;
            }
        }
    }
    if(flag==0){
        cout<<"The Queue is:";
        while(!q.empty()){
            cout<<q.front()<<" ";
            q.pop();
        }
    }

    return 0;
}