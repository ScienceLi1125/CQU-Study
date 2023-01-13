/*组织星期信息：
题目：输入一个正整数repeat (0<repeat<10)，做repeat次下列运算：
    定义一个指针数组将下面的星期信息组织起来，输入一个字符串，在表中查找，若存在，输出该字符串
    在表中的序号，否则输出-1。
    Sunday Monday Tuesday Wednesday Thursday Friday Saturday
*/
#include <iostream>
using namespace std;

int main(){
    char *Week[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    int repeat;                 //char*可视为字符串指针
    cin>>repeat;
    for(int i=0;i<repeat;i++){
        string day;
        cin>>day;
        bool flag=false;
        for(int j=0;j<7;j++){
            if(Week[j]==day){   //Week[j]表示字符串,*Week[j]表示指针(字符),&Week[j]表示地址）
                flag=true;
                cout<<j+1<<endl;
            }
        }
        if(!flag){
            cout<<-1<<endl;
        }

    }


    return 0;
}