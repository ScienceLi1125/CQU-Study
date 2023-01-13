#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ifstream ifs("test1.txt");      //需要"test1.txt"文件存在才能读取
    ofstream ofs("test2.txt");
    if(!ofs){
        cerr<<"输出文件无法打开"<<endl;
        return -1;
    }
    string word;
    while(ifs>>word){               //将"test1.txt"文件中字符串读取到word
        ofs<<word<<" ";             //将读取的内容写入"test2.txt"
    }
    ofs.close();
    ifs.close();
    cout<<"写文件结束"<<endl;
    
    return 0;
}