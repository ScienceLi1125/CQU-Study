/*出租：
题目：int[] arr=new int[]{8,3,2,1,0};int[] index=new int[]{3,0,4,3,1,0,2,4,3,4,4};
    index数组就是arr数组的下标，index[0]=2对应arr[2]=1，index[1]=0对应arr[0]=8，
    index[2]=3 对应 arr[3]=0，以此类推…… 很容易得到电话号码是18013820100。
    本题要求你编写一个程序，为任何一个电话号码生成这段代码。
输入：一个由11位数字组成的手机号码。
输出：为输入的号码生成代码的前两行，其中arr中的数字必须按递减顺序给出。
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool cmp(int a,int b){
    return a>b;
}

int main(){
    string tel;
    getline(cin,tel);
    int num[10]={0};
    vector<int> v1;
    vector<int> v2;
    for(int i=0;i<tel.length();i++){
        num[tel[i]-'0']++;
        
    }
    for(int i=9;i>=0;i--){              //倒序压入节省了对v1的降序排列
        if(num[i]!=0){
            v1.push_back(i);
        }
    }
    for(int i=0;i<tel.length();i++){
        for(int j=0;j<v1.size();j++){
            if(v1[j]==tel[i]-'0'){      //tel各位是char，不能直接与v1[j]比较
                v2.push_back(j);
            }
        }
    }
    cout<<"int[] arr = new int[]{";
    for(int i=0;i<v1.size()-1;i++){
        cout<<v1[i]<<",";
    }
    cout<<v1[v1.size()-1]<<"};"<<endl;

    cout<<"int[] index = new int[]{";
    for(int i=0;i<v2.size()-1;i++){
        cout<<v2[i]<<",";
    }
    cout<<v2[v2.size()-1]<<"};"<<endl;
    
    return 0;
}