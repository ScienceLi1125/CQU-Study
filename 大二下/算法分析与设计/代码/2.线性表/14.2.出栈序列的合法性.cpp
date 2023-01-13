/*出栈序列的合法性:
题目：给定一个最大容量为M的堆栈，将N个数字按1,2,3,...,N的顺序入栈，允许按任何顺序出栈，则哪些
    数字序列是不可能得到的？例如给定M=5、N=7，则我们有可能得到{1,2,3,4,5,6,7}，但不可能得到
    {3,2,1,7,5,6,4}。
输入：第一行给出3个不超过1000的正整数：M（堆栈最大容量）、N（入栈元素个数）、K（待检查的出栈序
    列个数）。最后K行，每行给出N个数字的出栈序列。所有同行数字以空格间隔。
输出：对每一行出栈序列，如果其的确是有可能得到的合法序列，就在一行中输出YES，否则输出NO。
输入样例：
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2
输出样例：
YES
NO
NO
YES
NO
思路：用最直接的人脑解决的办法，输入n，若n还没压入栈，则压入直到n的元素；否则判断出栈是否合理
*/
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main(){
    int M,N,K;
    cin>>M>>N>>K;
    for(int i=0;i<K;i++){
        vector<int> v;
        stack<int> st;
        bool flag=1;
        int index=0;        //已经入栈元素
        for(int j=0;j<N;j++){
            int n;
            cin>>n;
            if(n>index){
                for(int k=index+1;k<=n;k++){
                    st.push(k);
                    if(st.size()>M){
                        flag=0;
                    }
                }
                index=n;
                v.push_back(st.top());
                st.pop();
            }
            else if(n<index){
                if(n==st.top()){
                    v.push_back(st.top());
                    st.pop();
                }
                else{
                    flag=0;
                }
            }
            else{
                flag=0;
            }
        }
        if(v.size()!=N){
            flag=0;
        }
        if(flag==0){
            cout<<"NO"<<endl;
        }
        else{
            cout<<"YES"<<endl;
        }
    }

    return 0;
}