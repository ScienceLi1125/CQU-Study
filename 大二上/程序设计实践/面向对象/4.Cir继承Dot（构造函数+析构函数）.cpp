#include <iostream>
#include<iomanip>
using namespace std;
const double PI=3.14;

class Dot
{
public:
    Dot() {
        cout<<"Dot constructor called"<<endl;
    }
    ~Dot() {
        cout<<"Dot destructor called"<<endl;
    }
protected:
    float x,y;
};

class Cir: public Dot
{
public:
    Cir(float x,float y,float r) {
        this->r=r;              //此r非彼r，需要用this指针进行赋值
        cout<<"Cir constructor called"<<endl;
    }
    ~Cir(){
        cout<<"Cir destructor called"<<endl;
    }
    float getArea(){
        return PI*r*r;
    }

private:
    float r;
};

int main(){
    float x,y,r;
    cin>>x>>y>>r;
    Cir c(x,y,r);
    cout<<fixed<<setprecision(2)<<c.getArea()<<endl;
    return 0;
}
