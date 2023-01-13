#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ifstream ifs("test.txt");
    if(!ifs){
        cerr<<"文件打开失败"<<endl;
        return -1;
    }
    string buf;
    while(ifs>>buf){
        cout<<buf<<endl;
    }
    ifs.close();
    cout<<"文件读取结束"<<endl;

    return 0;
}