/*思路：用vector数组存储相邻城市，用集合记录被攻占的城市，遍历所有城市，若有没被攻占的城市还有
    相邻的城市，则方案不可行*/
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main(){
    int N,M;
    cin>>N>>M;
    vector<int> v[N+1];
    for(int i=0;i<M;i++){
        int x,y;
        cin>>x>>y;
        v[x].push_back(y);
    }
    int K;
    cin>>K;
    for(int i=0;i<K;i++){
        bool isLonely=1;
        int Np;
        cin>>Np;
        set<int> s;                     //记录被攻占的城市
        for(int i=0;i<Np;i++){
            int tmp;
            cin>>tmp;
            s.insert(tmp);
        }
        for(int i=1;i<=N;i++){          //遍历所有城市
            if(s.find(i)==s.end()){     //还有没被攻占的城市
                for(int j=0;j<v[i].size();j++){     //遍历该城市的相邻城市
                    if(s.find(v[i][j])==s.end()){   //该城市的某个相邻城市没被攻占
                        isLonely=false;
                    }
                }
            }
        }
        if(isLonely){
            cout<<"YES"<< endl;
        }
        else{
            cout<<"NO"<< endl;
        }
    }
    return 0;
}