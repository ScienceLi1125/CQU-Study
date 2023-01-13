#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;

bool cmp(pair<char,int>& lhs,pair<char,int>& rhs){
    //自定义map排序方式(但无法在map中排序,需要拷贝到vector)
    if(lhs.second<rhs.second){  //频率少(权重小)的在前
        return 1;
    }else if(lhs.second>rhs.second){
        return 0;
    }else{                      //频率相同时看ASCII码序
        if(lhs.first<rhs.first){
            return 1;
        }else{
            return 0;
        }
    }
};

int main(){
    string s;    
    cin>>s;
    map<char,int> mp;
    for(int j=0;j<s.length();j++){
        mp[s[j]]++;
    }
    // std::map<char,int,cmp>::iterator it; //cmp无法直接对map进行排序
    // for(it=mp.begin();it!=mp.end();it++){
    //     cout<<it->first<<" "<<it->second<<endl;
    // }
    vector<pair<char,int> > v(mp.begin(),mp.end());
    sort(v.begin(),v.end(),cmp);            //拷贝到vector中排序
    for(int i=0;i<v.size();i++){
        cout<<v[i].first<<" "<<v[i].second<<endl;
    }
    
    return 0;
}