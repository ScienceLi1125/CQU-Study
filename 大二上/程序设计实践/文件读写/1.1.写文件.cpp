#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ofstream ofs;
    ofs.open("test1.txt",ios::out);
    ofs<<"写文件"<<endl;
	ofs<<"结束"<<endl;
    ofs.close();
    cout<<"写文件结束"<<endl;
    
    return 0;
}