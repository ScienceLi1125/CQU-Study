/*双队列实现栈：
题目：设1,2,...,N依次入栈QStack<int>, 判断由这N个整数构成的整数序列<a1,a2,…,aN> 是否为有效的出栈
    顺序。同时我们限定栈中只能存储K个整数(0<K<=N)，即整数入栈必须满足stack.length()<K, 如果
    stack.length()==K, 只能从中弹出1个以上的整数后，下一个整数才能入栈。（注：栈的容量必须大于或
    等于K）
输入：第一行有三个正整数N、K、m：N表示入栈的最大整数，K为栈中存储的整数数量上限，m表示接下来有m行输
    入，每一行都有1到N的整数的一组序列（空格分开）。
输出：m行字符T或F, 第i行的字符T(F), 表示第i行序列为有效（无效）的出栈顺序 (1<=i<=m)
双队列实现栈的思路：两个队列容量相同，只有一个非空，push时压入非空队列，pop时交换QA,QB并弹出非空队
    列的最后一个元素
题目思路：彩虹瓶的逆运算，即
*/
#include <iostream>
using namespace std;

template <typename E>
class QStack{
private:
    int maxSize;    //栈的容量
    E* QA;
    E* QB;          //基于数组实现的队列
    int sizeA;
    int sizeB;
public:
    QStack(int size=0){
        maxSize = size;
        QA=new E[size];
        QB=new E[size];
        sizeA=0;
        sizeB=0;
    }
    ~QStack() {}
    void clear(){
        if(sizeA){
            for(int i=0;i<sizeA;i++){
                QA[i]=0;
            }
            sizeA=0;
        }
        else{
            for(int i=0;i<sizeB;i++){
                QB[i]=0;
            }
            sizeB=0;
        }
    }
    void push(const E& it){         //这样构造默认先压入QB
        if(sizeA){
            QA[sizeA]=it;
            sizeA++;
        }
        else{
            QB[sizeB]=it;
            sizeB++;
        }
    }
    E pop(){
        if(sizeA){
            E tmp=QA[sizeA-1];
            for(int i=0;i<sizeA-1;i++){
                QB[i]=QA[i];
                QA[i]=0;
            }
            sizeB=sizeA-1;
            sizeA=0;
            return tmp;
        }
        else if(sizeB){
            E tmp=QB[sizeB-1];
            for(int i=0;i<sizeB-1;i++){
                QA[i]=QB[i];
                QB[i]=0;
            }
            sizeA=sizeB-1;
            sizeB=0;
            return tmp;
        }
        else{               //都为空
            return NULL;
        }
    }
    const E& topValue() const {
        if(sizeA){
            return QA[sizeA-1];
        }
        else if(sizeB){
            return QB[sizeB-1];
        }
        else{
            return NULL;
        }
    }
    int length() const {
        if(sizeA){
            return sizeA;
        }
        else{
            return sizeB;
        }
    }
};

int main(){
    int N,K,m,n;
    cin>>N>>K>>m;
    for(int i=0;i<m;i++){
        int num=1;
        QStack<int> st(N);
        bool flag=1;
        for(int j=0;j<N;j++){
            cin>>n;
            if(n>=num){
                while(num<=n){
                    if(st.length()<K){
                        st.push(num);
                    }
                    else{
                        flag=0;
                    }
                    num++;
                }
                st.pop();
            }
            else{
                if(st.length()!=0 && st.topValue()==n){
                    st.pop();
                }
                else{
                    flag=0;
                }
            }
        }
        if(flag){
            cout<<"T"<<endl;
        }
        else{
            cout<<"F"<<endl;
        }
    }


    return 0;
}
