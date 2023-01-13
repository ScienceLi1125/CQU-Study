#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    string s;
    getline(cin,s);
    string ans="";
    ans+=s[0];
    for(int i=1;i<s.length();i++){
        ans+=s[i];
        int cnt=0;
        if(ans[ans.length()-1]!='6'&&ans[ans.length()-2]=='6'){
            int j=ans.length()-2;
            for(;j>=0&&ans[j]=='6';j--){}
            cnt=ans.length()-2-j;
            if(cnt>9){
                ans.replace(j+1,cnt,"27");
            }
            else if(cnt>3){
                ans.replace(j+1,cnt,"9");
            }
        }
        else if(i==s.length()-1&&ans[ans.length()-1]=='6'){
            int j=ans.length()-1;
            for(;j>=0&&ans[j]=='6';j--){}
            cnt=ans.length()-1-j;
            if(cnt>9){
                ans.replace(j+1,cnt,"27");
            }
            else if(cnt>3){
                ans.replace(j+1,cnt,"9");
            }
        }
    }
    cout<<ans<<endl;

    return 0;
}