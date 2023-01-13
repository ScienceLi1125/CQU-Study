#include<iostream>
using namespace std;

class RESISTOR{
public:
    RESISTOR(double resistor):Resistor(resistor){
        cout<<"创建电阻"<<Resistor<<"欧"<<endl;
    }
    ~RESISTOR(){
        cout<<"销毁电阻"<<Resistor<<"欧"<<endl;
    }
    void Show() const {
        cout<<"电阻: "<<Resistor<<"欧"<<endl;
    }
private:
    double Resistor;
};
class INDUCTOR{
public:
    INDUCTOR(double inductor):Inductor(inductor){
        cout<<"创建电感"<<Inductor<<"亨"<<endl;
    }
    ~INDUCTOR(){
        cout<<"销毁电感"<<Inductor<<"亨"<<endl;
    }
    void Show() const {
        cout<<"电感: "<<Inductor<<"亨"<<endl;
    }
private:
    double Inductor;
};
class CAPACITOR{
public:
    CAPACITOR(double capacitor):Capacitor(capacitor){
        cout<<"创建电容"<<Capacitor<<"法"<<endl;
    }
    ~CAPACITOR(){
        cout<<"销毁电容"<<Capacitor<<"法"<<endl;
    }
    void Show() const {
        cout<<"电容: "<<Capacitor<<"法"<<endl;
    }
private:
    double Capacitor;
};
class CIRCUIT:public RESISTOR,public INDUCTOR,public CAPACITOR{
    public:                     //class CIRCUIT继承了前三个类，而不是菱形继承
    CIRCUIT(double resistor,double inductor,double capacitor):
        RESISTOR(resistor),INDUCTOR(inductor),CAPACITOR(capacitor){
        cout<<"创建电路"<<endl;
    }
    ~CIRCUIT(){
        cout<<"销毁电路"<<endl;
    }
    void Show() const {         //CIRCUIT的Show函数是展示继承的三个类，因此不必用多态
        RESISTOR::Show();       //直接作为成员函数，分别调用前三个类的Show函数
        INDUCTOR::Show();
        CAPACITOR::Show();
    }
};


int main()
{
    double r, i, c;
    cin >> r >> i >> c;
    CIRCUIT a(r, i, c);
    a.Show();

    return 0;
}
