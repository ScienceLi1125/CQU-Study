#include<iostream>
#include<set>
using namespace std;

int main(){
    int N;
    cin>>N;
    set<int> s;
    for(int i=0;i<N;i++){
        int m;
        cin>>m;
        if(s.upper_bound(m)!=s.end()){		//即在集合中可以找到比m大的元素
            s.erase(s.upper_bound(m)); 		//把比m大的清除（因为唯一，所以只用操作一次）
		}
        s.insert(m);
    }
    cout<<s.size()<<endl;
    return 0;
}
