/*N皇后问题：
题目：N皇后问题是指在N*N的棋盘上放置N个皇后，使这N个皇后无法吃掉对方，
    即两两不在一行，不在一列，也不在对角线上（任意对角线，不限于主次对角线）。
思路：对行进行遍历，在确定一行的那个皇后应该摆在哪一列时，需判断该点是否合法。
    若合法，则递归，若不合法，则继续寻找可以摆放的位置。无处摆放时停止。
    判断合法的方法：
    (1)不同列
    (2)不在同一条45°斜线上（i+j为定值）
    (3)不在同一条135°斜线上（i-j为定值）
    存储方式：
    vector<int> v={2,4,6,1,3,5}
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool judge(int row,int col,vector<int> &tmp,int n){ //判断(row,col)能否放皇后
//不必判断行，因为tmp下标表示行数，不可能重合
    for(int i=0;i<tmp.size();i++){
        if(col==tmp[i]){
            return 0;
        }
        if((row+col)==i+1+tmp[i]){
            return 0;
        }
        if((row-col)==i+1-tmp[i]){
            return 0;
        }
    }
    return 1;
}

void place(vector<int> &tmp,vector<vector<int>> &ans,int n){
    if(tmp.size()==n){
        ans.push_back(tmp);
        return;
    }
    else if(tmp.size()<n){          //tmp.size()+1表示行的遍历
        for(int i=0;i<n;i++){       //i+1表示列的遍历
            if(judge(tmp.size()+1,i+1,tmp,n)){
                tmp.push_back(i+1);
                place(tmp,ans,n);
                tmp.pop_back();
            }
        }
    }
    return;
}

void PrintNQueen(vector<int> v){
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[i]-1;j++){
            cout<<0;
        }
        cout<<1;
        for(int j=v[i];j<v.size();j++){
            cout<<0;
        }
        cout<<endl;
    }
    cout<<"------------------"<<endl;
    return;
}

int main(){
    int N;
    cin>>N;
    vector<int> tmp;                //存储当前棋盘
    vector<vector<int>> ans;        //存储结果
    place(tmp,ans,N);

    cout<<ans.size()<<endl;;
    for(int i=0;i<ans.size();i++){
        PrintNQueen(ans[i]);
    }

    return 0;
}