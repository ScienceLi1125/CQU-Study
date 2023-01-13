/*二叉搜索树虽然快，但删除结点太过繁琐，不删除又大大影响效率，因此采用栈存储元素并不断判断并删除，
    既可以保证较高的插入和删除效率，又因为本题降序特点，有较高的搜索效率（即搜索不需要从头遍历，只
    需while循环判断栈顶元素即可）
*/
#include <iostream>
#include <stack>
using namespace std;

int main(){
    int N;
    cin>>N;
    int Pay=0;
    int Income=0;
    stack<int> s;
    for(int i=0;i<N-1;i++){             //最后一天不买股票
        int n;
        cin>>n;
        Pay+=n;
        while(!s.empty() && s.top()<n){
            Income+=n;
            s.pop();
        }
        s.push(n);
    }
    int priceN;
    cin>>priceN;
    Income+=priceN*s.size();
    cout<<Income-Pay<<endl;
    
    return 0;
}
