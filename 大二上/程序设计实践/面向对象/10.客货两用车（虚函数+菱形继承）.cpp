#include <iostream>
using namespace std;

class CAR{
public:
    CAR(double speed):Speed(speed){
        cout<<"创建汽车("<<Speed<<"公里/小时)"<<endl;
    };
    virtual ~CAR(){                     //虚成员函数要用虚析构函数
        cout<<"销毁汽车("<<this->Speed<<"公里/小时)"<<endl;
    }
    virtual void Show() const{          //测试函数中是const常量
        cout<<"汽车: "<<this->Speed<<"公里/小时"<<endl;
    }
protected:
    double Speed;
};

class BUS:virtual public CAR {          //虚继承解决菱形继承问题
public:
    BUS(double speed,int seat):CAR(speed),Seat(seat){   //继承下的构造函数
        cout<<"创建客车("<<this->Seat<<"人)"<<endl;
    };
    virtual ~BUS(){
        cout<<"销毁客车("<<this->Seat<<"人)"<<endl;
    }
    virtual void Show() const{          //虚函数实现多态
        cout<<"客车: "<<this->Speed<<"公里/小时, "<<this->Seat<<"人"<<endl;
    }
protected:
    int Seat;
};
class TRUCK:virtual public CAR {
public:
    TRUCK(double speed,double load):CAR(speed),Load(load){
        cout<<"创建货车("<<this->Load<<"吨)"<<endl;
    };
    virtual ~TRUCK(){
        cout<<"销毁货车("<<this->Load<<"吨)"<<endl;
    }
    virtual void Show() const{
        cout<<"货车: "<<this->Speed<<"公里/小时, "<<this->Load<<"吨"<<endl;
    }
protected:
    double Load;
};

class VAN:public BUS,public TRUCK {
//VAN继承自BUS和TRUCK，因此不用写CAR，否则构造函数无法识别用基类的CAR还是BUS和TRUCK继承的CAR
public:
    VAN(double speed,int seat,double load):CAR(speed),BUS(speed,seat),TRUCK(speed,load){
        cout<<"创建客货两用车"<<endl;        //构造函数里仍要写CAR
    }
    virtual ~VAN(){
        cout<<"销毁客货两用车"<<endl;
    }
    virtual void Show() const{
        cout<<"客货两用车: "<<this->TRUCK::Speed<<"公里/小时, ";
        cout<<this->Seat<<"人, "<<this->Load<<"吨"<<endl;
    }
};

void Test(const CAR &x)             //参数为基类对象的函数也可以传入派生类对象
{
    x.Show();
}

int main(){
    CAR a(108.5);
    Test(a);
    BUS b(58.5, 45);
    Test(b);
    TRUCK c(208.5, 350.8);
    Test(c);
    VAN d(125.6, 5, 2.5);
    Test(d);
    CAR *p;
    double s,t,w;
    cin>>s>>t>>w;
    p = new VAN(s, t, w);
    p->Show();
    delete p;
    
    return 0;
}