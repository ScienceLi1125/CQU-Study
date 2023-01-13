/*图深度优先遍历
    But!递归实现dfs超限，下采用栈来实现，利用栈实现dfs的思路如下：
    1.输出初始点并标记访问，将初始点入栈
    2.取栈顶元素w（此时不出栈也不打印！不出栈因为等到其所有相邻节点都被访问过才出栈，不打印因为入
    栈时已经打印过了），查找w第一个未被访问过的相邻节点
        若不存在没被访问过的相邻节点，则出栈（dfs到头了）
        若存在则压入栈中，标记访问，输出该节点
    3.若栈非空，则重复2
*/
#include <iostream>
#include <stack>
using namespace std;

int n,e;
int matrix[20001][20001]={{0}};
bool visit[20001]={0};

int nearby(int v){      //v为被访问过的相邻节点
    for(int i=0;i<n;i++){
        if(matrix[v][i]>0 && visit[i]==0)  return i;
    }
    return n;           //没找到相邻点
}

int main(){
    cin>>n>>e;
    for(int i=0;i<e;i++){
        int a,b;
        cin>>a>>b;
        matrix[a][b]=1;
    }
    stack<int> st;
    for(int i=0;i<n;i++){
        if(visit[i]==0){
            st.push(i);
            visit[i]=1;
            cout<<i<<" ";
            while(!st.empty()){
                int top=st.top();
                int next=nearby(top);
                if(next!=n){
                    st.push(next);
                    cout<<next<<" ";
                    visit[next]=1;
                }else{
                    st.pop();
                }
            }
        }
    }

    return 0;
}
