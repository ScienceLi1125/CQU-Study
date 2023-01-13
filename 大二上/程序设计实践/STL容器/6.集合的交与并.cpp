#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;


int main(){
    int n,m;
    cin>>n>>m;
    set<int> s1;
    set<int> s2;
    if(n>0){
        for(int i=0;i<n;i++){
            int a;
            cin>>a;
            s1.insert(a);
        }
    }
    if(m>0){
        for(int i=0;i<m;i++){
            int a;
            cin>>a;
            s2.insert(a);
        }
    }
    vector<int> itsv(n+m);
    vector<int> unv(n+m);
    vector<int>::iterator it1;      //求交集
    it1=std::set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),itsv.begin());
    itsv.resize(it1-itsv.begin());
    vector<int>::iterator it2;      //求并集
    it2=std::set_union(s1.begin(),s1.end(),s2.begin(),s2.end(),unv.begin());
    unv.resize(it2-unv.begin());
    //因为是集合自动排序，所以存入vector中默认升序
    if(!itsv.empty()){
        cout<<itsv.size();
        for(int i=0;i<itsv.size();i++){
            cout<<" "<<itsv[i];
        }
        cout<<endl;
    }
    else{
        cout<<0<<endl;
    }
    if(!unv.empty()){
        cout<<unv.size();
        for(int i=0;i<unv.size();i++){
            cout<<" "<<unv[i];
        }
        cout<<endl;
    }
    else{
        cout<<0<<endl;
    }

    return 0;
}