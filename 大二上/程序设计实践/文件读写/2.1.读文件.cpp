#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ifstream ifs;
    ifs.open("test.txt",ios::in);
    if(!ifs.is_open()){
        cerr<<"文件打开失败"<<endl;
        return -1;
    }
    string buf;
    while(getline(ifs,buf)){
        cout<<buf<<endl;
    }
    ifs.close();
    cout<<"文件读取结束"<<endl;
    
    return 0;
}