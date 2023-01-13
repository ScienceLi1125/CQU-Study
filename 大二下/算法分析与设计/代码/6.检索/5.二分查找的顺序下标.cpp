//顺序输出二分查找的下标序列
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

vector<int> v;
void binary_search(int N){
    queue<pair<int,int> >q;
    pair<int,int> p(0,N-1);
    q.push(p);
    while(!q.empty()){
        p=q.front();
        q.pop();
        v.push_back((p.first+p.second)/2);
        pair<int,int> p1(p.first,(p.first+p.second)/2-1);
        pair<int,int> p2((p.first+p.second)/2+1,p.second);
        if(p1.first<=p1.second){
            q.push(p1);
        }
        if(p2.first<=p2.second){
            q.push(p2);
        }
    }
}

int main(){
    binary_search(21);
    cout<<v.size()<<":"<<endl;
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    
    return 0;
}
