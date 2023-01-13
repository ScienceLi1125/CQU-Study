/*整型关键字的散列映射：
题目：给定一系列整型关键字和素数P，用除留余数法定义的散列函数H(Key)=Key将关键字映射到长度为P的散
    列表中。用线性探测法解决冲突。
输入：第一行首先给出两个正整数N（≤1000）和P（≥N的最小素数），分别为待插入的关键字总数、以及散列表
    的长度。第二行给出N个整型关键字。数字间以空格分隔。
输出：在一行内输出每个整型关键字在散列表中的位置。数字间以空格分隔，但行末尾不得有多余空格。
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int N,P;
    cin>>N>>P;
    int key[1010];          //P为≥N的最小素数，当N为1000时，P=1009，因此数组要开到1009
    for(int i=0;i<1010;i++){//（测试点3）
        key[i]=-1;          //初始化key数组
    }
    vector<int> v;          //存储N个数的下标
    for(int i=0;i<N;i++){
        int a;
        cin>>a;
        int index=a%P;
        if(key[index]==-1){
            key[index]=a;
            v.push_back(index);
            continue;
        }
        else if(key[index]==a){     //相同关键值只写入一遍（测试点1）
            v.push_back(index);     //但是要输出两遍（测试点2）
            continue;
        }
        for(int j=index+1;;j++){    //终止条件为查找到合适位置，必然存在，否则本题无解
            if(key[j%P]==-1){
                key[j%P]=a;
                v.push_back(j%P);
                break;
            }
            else if(key[j%P]==a){
                v.push_back(j%P);
                break;
            }
        }
    }
    cout<<v[0];
    for(int i=1;i<v.size();i++){
        cout<<" "<<v[i];
    }
    
    return 0;
}
