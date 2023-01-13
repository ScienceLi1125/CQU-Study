/*集合减法:
    给定两个非空集合A和B，集合的元素为30000以内的正整数，编写程序求A-B。

输入格式:
输入为三行。第1行为两个整数n和m，分别为集合A和B包含的元素个数，1≤n, m ≤10000。第2行表示集合A，为n个空格间隔的正整数，每个正整数不超过30000。第3行表示集合B，为m个空格间隔的正整数，每个正整数不超过30000。

输出格式:
输出为一行整数，表示A-B，每个整数后一个空格，各元素按递增顺序输出。若A-B为空集，则输出0，0后无空格。

输入样例:
5 5
1 2 3 4 5
3 4 5 6 7 
输出样例:
1 2
*/

/*集合减法复杂度为n*n，易超时
#include<iostream>
#include<vector>
#include<algorithm>>
using namespace std;

int main() {
    int n,m;
    cin>>n>>m;
    vector<int> va;
    vector<int> vb;
    vector<int> vc;
    bool flag1=0;
    for(int i=0;i<n;i++){
        int l;
        cin>>l;
        va.push_back(l);
    }
    for(int j=0;j<m;j++){
        int h;
        cin>>h;
        vb.push_back(h);
    }
    for(int i=0;i<n;i++){
        bool flag2=0;
        for(int j=0;j<m;j++){
            if(va[i]==vb[j]){
                flag2=1;
            }
        }
        if(flag2==0){
            vc.push_back(va[i]);
            flag1=1;
        }
    }
    sort(vc.begin(),vc.end());
    if(flag1==0){
        cout<<0;
    }
    else{
        for(int i=0;i<vc.size();i++){
            cout<<vc[i]<<" ";
        }
    }

    return 0;
}
*/
#include<iostream>
#include<set>
using namespace std;

int main() {
    int n,m;
    cin>>n>>m;
    set<int> a;
    set<int> b;
    for(int i=0;i<n;i++) {
        int x;
        cin>>x;
        a.insert(x);
    }
    for(int i=0;i<m;i++) {
        int y;
        cin>>y;
        b.insert(y);
        if(a.count(y)) {     //a.count(y)判断y在a中是否存在，若存在，返回1
            a.erase(y);
        }
    }
    if(a.empty()){
        cout<<0;
    }
    else{
        for(set<int>::iterator it=a.begin();it!=a.end();++it){
            cout<<*it<<' ';
    }
    cout<<endl;
    }
    
    return 0;
}

/*也可以用函数解决
# include <iostream>
# include <algorithm>
# include <vector>
int main()
{
    using namespace std;
    int A,B;
    cin>>A>>B;
    // int A_array[A],B_array[B];
    vector <int> A_v;
    vector <int> B_v;
    for(int i=0;i<A+B;i++)
    {
        int num;
        cin>>num;
        if(i<A)
        {
            A_v.push_back(num);
        }
        else
        {
            B_v.push_back(num);
        }
    }
    sort(A_v.begin(),A_v.end());
    vector <int> v(A);
    vector <int>::iterator it;
    it=std::set_difference (A_v.begin(),A_v.end(),B_v.begin(),B_v.end(), v.begin());                                           
    v.resize(it-v.begin());                   
    if(v.size()==0) cout<<0;
    else
    {
        for(vector <int>::iterator ij=v.begin();ij!=v.end();ij++)
        {
            cout<<(*ij)<<" ";
        }
    }
    return 0;
}
*/