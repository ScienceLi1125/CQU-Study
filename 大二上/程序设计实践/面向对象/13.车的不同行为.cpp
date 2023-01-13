#include <iostream>
using namespace std;

class Vehicle{};
class Bicycle:public Vehicle{};
class Motorcar:public Vehicle{};
    
void run(Vehicle &veh){
    cout<<"Vehicle run"<<endl;
}
void run(Bicycle &bic){
    cout<<"Bicycle run"<<endl;
}
void run(Motorcar &mot){
    cout<<"Motorcar run"<<endl;
}

int main(){
    Vehicle veh;
    Bicycle bic;
    Motorcar mot;
    run(veh);       //题目给定接口形式直接写成函数，不过重载时需要定义类
    run(bic);
    run(mot);

    return 0;
}