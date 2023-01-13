#include <iostream>
#include<vector>
using namespace std;

class MinStack
{
public:
    MinStack(){}

    void push(int n){
        v.push_back(n);
    }
    void pop(){
        v.pop_back();
    }
    int getmin(){
        int min=9999;
        for(int i=0;i<v.size();i++){
            if(min>=v[i]){
                min=v[i];
            }
        }
        return min;
    }
private:
    vector<int> v;
};

int main(){
    int N;
    cin>>N;
    MinStack minstack;
    for(int j=0;j<N;j++){
        string s;
        cin>>s;
        if(s=="push"){
            int m;
            cin>>m;
            minstack.push(m);
        }
        else if(s=="pop"){
            minstack.pop();
        }
        else{
            cout<<minstack.getmin()<<endl;
        }
    }
    
    return 0;
}

/*输入不规则时用if判断是否进入不同的输入
5
push 2
push 3
push 1
pop
getmin*/

/*本题也可以不设计类，而使用数组进行存储

#include<iostream>
#include<string.h>
using namespace std;

int main() {
    int N;
    int b[10];              //数组b存储栈的操作！！！数组
    cin>>N;
    int count=0,min=1;
    for(int i=1;i<=N;i++) {
        string s;
        cin>>s;
        if(s=="push") {  
            int e;
            cin>>e;
            b[count]=e;
            count++;
        }
        else if(s=="pop") {
            count--;
        }
        else {
            for(int j=0;j<count;j++) {
                if(b[min]>b[j]) {
                    min=j;
                }
            }
            cout<<b[min];
        }
    }
    return 0;
}
*/