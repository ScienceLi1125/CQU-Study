/*寻找鞍点：
题目：本题要求找出3行4列矩阵中的鞍点，即该位置上的元素在该行上最大、在该列上最小。注意，有可
    能没有鞍点。（本题假定所有数据均不一样，因此只会有一个鞍点）
输入：输入3行4列的矩阵，以空格分隔。
输出：如果有鞍点，则输出鞍点值及其位置；如果无，则输出不存在鞍点。
*/
// #include <iostream>
// #include <vector>
// using namespace std;

// int main(){
//     int arr[3][4];
//     for(int i=0;i<3;i++){
//         for(int j=0;j<4;j++){
//             cin>>arr[i][j];
//         }
//     }
//     vector<int> rvec;       //存储每行最大数位置
//     for(int i=0;i<3;i++){
//         int rmax=-99999;
//         int c;
//         for(int j=0;j<4;j++){
//             if(rmax<arr[i][j]){
//                 rmax=arr[i][j];
//                 c=j;        //最大数列下标
//             }
//         }
//         rvec.push_back(c);
//     }
//     vector<int> cvec;       //存储每列最小数位置
//     for(int j=0;j<4;j++){
//         int cmin=99999;
//         int r;              //最小数行下标
//         for(int i=0;i<3;i++){
//             if(cmin>arr[i][j]){
//                 cmin=arr[i][j];
//                 r=i;
//             }
//         }
//         cout<<r<<" ";
//         cvec.push_back(r);
//     }
//     bool flag=0;
//     for(int i=0;i<3;i++){
//         if(cvec[rvec[i]]==i){
//             cout<<"鞍点是"<<arr[cvec[i]][rvec[i]]<<",位于"<<cvec[i]<<"行"<<rvec[i]<<"列"<<endl;
//             flag=1;
//         }
        
//     }
//     if(flag==0){
//         cout<<"不存在鞍点"<<endl;
//     }

//     return 0;
// }
//存储较为复杂，不如直接打印
#include<iostream>
#include<vector>
using namespace std;

int main() {
    int a[3][4];
    bool flag=0;
    int x,y;  //x为行坐标,y为列坐标

    for(int i=0;i<3;i++) {
        for(int j=0;j<4;j++) {
            cin>>a[i][j];
        }
    }

    for(int i=0;i<3;i++) {
        int max=-999999,min=999999;
        for(int j=0;j<4;j++) {
            if(a[i][j]>max) { 
            max=a[i][j];
            y=j;
            }               //寻找行上最大值
        }
        for(int k=0;k<3;k++) {
            if(a[k][y]<min) {
                min=a[k][y];
                x=k;        //寻找该行最大值所在列上的最小值
            }
        }
        if(i==x) {          //判断该行最大值所在列上的最小值是否与行下标相同
            cout<<"鞍点是"<<a[x][y]<<','<<"位于"<<x<<"行"<<y<<"列";
            flag=1;
            break;
            }
    }
    if(flag==0) cout<<"不存在鞍点";
    
    return 0;
}

