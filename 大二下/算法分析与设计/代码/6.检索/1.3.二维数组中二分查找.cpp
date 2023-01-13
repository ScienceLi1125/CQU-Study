/*在矩阵中二分查找：
    题目：每行、列都升序排好的整数矩阵A，大小为n*n，在A中查找指定元素
    思路：从右上角开始搜索，(i,j)=(0,n-1)
        1）target=A[i][j] 找到
        2）target>A[i][j] i++
        3）target<A[i][j] j--
    每次搜索相当于删除一行/列
*/
#include <iostream>
#include <utility>
using namespace std; 

pair<int,int> find(int A[][4],int n,int target){
    int i=0,j=n-1;
    pair<int,int> p(-1,-1);
    while(i<n && j>=0){
        if(target==A[i][j]){
            p.first=i,
            p.second=j;
            return p;
        }
        else if(target<A[i][j]){
            j--;
        }
        else{
            i++;
        }
    }
    return p;
}

int main(){
    int A[4][4]={{0,1,2,5},{2,3,4,7},{4,4,4,8},{5,7,7,9}};
    pair<int,int> p;
    pair<int,int> p0(-1,-1);
    p=find(A,4,7);
    if(p!=p0){
        cout<<p.first<<" "<<p.second<<endl;
        return 0;
    }
    cout<<"not found!"<<endl;
    
    return 0;
}