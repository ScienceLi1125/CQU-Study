#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;


int main(){
    int T,n;
    cin>>T;
    for(int i=0;i<T;i++){
        cin>>n;
        map<string,int> m;
        for(int j=0;j<n;j++){
            string s;
            cin>>s;
            m[s]+=1;    //д╛хож╣н╙0
        }
        map<string,int>::iterator it=m.begin();
        for(;it!=m.end();it++){
            cout<<it->first<<" "<<it->second<<endl;
        }
    }

    return 0;
}