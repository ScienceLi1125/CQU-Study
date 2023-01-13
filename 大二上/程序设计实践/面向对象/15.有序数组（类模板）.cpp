#include <iostream>
using namespace std;

template <class T>
class MyArray{
private:
    T *data;
    int size;
public:
    MyArray(int size){                  //构造函数
        this->size = size;
        data = new T[size];

        for(int i=0;i<size;i++)
            cin>>*(data+i);             //类定义要求初始化时输入元素
    };
    void sort(){
        T temp;
        for(int i=0;i<size-1;i++)       //冒泡
            for(int j=0;j<size-1;j++){
                if(*(data+j)>*(data+j+1)){
                    temp=*(data+j);
                    *(data+j)=*(data+j+1);
                    *(data+j+1)=temp;
                }
            }
    };
    void display()                      //输出函数
    {
        for(int i(0); i < size - 1; i++)
            cout << *(data + i) << " ";

        cout << *(data + size - 1) << endl;
    };
    ~MyArray();
    bool check();
};
template<class T>
MyArray<T>::~MyArray(){ delete[] data;}

template<class T>
bool MyArray<T>::check(){
    int i;
    for(i=0;i<size-1;i++){
        if(data[i]>data[i+1]){
            cout<<"ERROR!"<<endl;
            return false;
        }
    }
    return true;
}
int main( )
{
/*每行输入的第一个数字为0，1，2或3:
为0时表示输入结束；为1时表示将输入整数;为2时表示将输入有一位小数的浮点数;为3时表示输入字符。
如果第一个数字非0，则接下来将输入一个正整数，表示即将输入的数据的数量。
从每行第三个输入开始，依次输入指定类型的数据。
*/
    MyArray<int> *pI;
    MyArray<float> *pF;
    MyArray<char> *pC;
    int ty, size;
    cin>>ty;
    while(ty>0){
        cin>>size;
        switch(ty){
            case 1: pI = new MyArray<int>(size);   pI->sort(); pI->check(); pI->display(); delete pI; break;
            case 2: pF = new MyArray<float>(size); pF->sort(); pF->check(); pF->display(); delete pF; break;
            case 3: pC = new MyArray<char>(size);  pC->sort(); pC->check(); pC->display(); delete pC; break;
        }
        cin>>ty;
    }
    return 0;
}
