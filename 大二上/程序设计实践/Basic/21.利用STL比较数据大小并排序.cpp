/*利用STL比较数据大小并排序：
题目：要求读入n个整数（输入数字个数根据输入时随机确定，以输入一个非数字的值作为输入结束标志），利用STL比较数据大小并排序（由小到大升序），然后输出排序后的数据。
输入：在一行中依次输入整数值，每个数字之间用空格分隔，输入数字个数根据输入时随机确定，以输入一个非数字的值作为输入结束标志。
输出：先输出一段提示“从标准设备读入数据，直到输入是非整型数据为止”，在输入一组数字后，输出排序后的数字，在一行中由小到大依次输出所有值，数字之间用空格分隔。
*/
#include <iostream>
#include <vector>
#include <algorithm>    //sort函数的文件头
using namespace std;

int main(){
    int n;
    vector<int> v1;
    while(cin>>n){      //遇到非int型直接停止输入(输入样例：10 3 -2 8 20 -9 e)
        v1.push_back(n);
    }
    sort(v1.begin(),v1.end());
    cout<<"从标准设备读入数据，直到输入是非整型数据为止"<<endl;
    for(int i=0;i<v1.size();i++){
        cout<<" "<<v1[i];
    }


    return 0;
}