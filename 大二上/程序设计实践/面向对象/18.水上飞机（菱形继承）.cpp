/*水上飞机
题目：请设计以下航行器、飞机、船、水上飞机4个类如下：
    CRAFT为航行器类，是公共基类，提供航行器的基本特性。
    PLANE为飞机类，以公有方式继承CRAFT类，在航行器类的基础上增加飞机的特性。
    SHIP为船类，以公有方式继承CRAFT类，在航行器类的基础上增加船的特性。
    SEAPLANE为水上飞机类，同时以公有方式继承PLANE类和SHIP类，兼具飞机和船的特性。
输入样例：583.6 48.2 3.8
输出样例：
创建航行器(速度: 583.6)
创建飞机(翼展: 48.2)
创建船(吃水: 3.8)
创建水上飞机
航行(速度: 583.6, 翼展: 48.2, 吃水: 3.8)
销毁水上飞机
销毁船(吃水: 3.8)
销毁飞机(翼展: 48.2)
销毁航行器(速度: 583.6)
*/
#include <iostream>
using namespace std;

class CRAFT{
public:
    CRAFT(double speed):Speed(speed){
        cout<<"创建航行器(速度: "<<Speed<<")"<<endl;
    };
    virtual ~CRAFT(){
        cout<<"销毁航行器(速度: "<<this->Speed<<")"<<endl;
    }
    virtual void Show() const{
        cout<<"航行(速度: "<<this->Speed<<")"<<endl;
    }
protected:
    double Speed;
};

class PLANE:virtual public CRAFT {
public:
    PLANE(double speed,double width):CRAFT(speed),Width(width){
        cout<<"创建飞机(翼展: "<<this->Width<<")"<<endl;
    };
    virtual ~PLANE(){
        cout<<"销毁飞机(翼展: "<<this->Width<<")"<<endl;
    }
    virtual void Show() const{
        cout<<"航行(速度: "<<this->Speed<<", 翼展: "<<this->Width<<")"<<endl;
    }
protected:
    double Width;
};
class SHIP:virtual public CRAFT {
public:
    SHIP(double speed,double depth):CRAFT(speed),Depth(depth){
        cout<<"创建船(吃水: "<<this->Depth<<")"<<endl;
    };
    virtual ~SHIP(){
        cout<<"销毁船(吃水: "<<this->Depth<<")"<<endl;
    }
    virtual void Show() const{
        cout<<"航行(速度: "<<this->Speed<<", 吃水: "<<this->Depth<<")"<<endl;
    }
protected:
    double Depth;
};

class SEAPLANE:public PLANE,public SHIP {
public:
    SEAPLANE(double speed,double width,double depth):CRAFT(speed),PLANE(speed,width),SHIP(speed,depth){
        cout<<"创建水上飞机"<<endl;
    };
    virtual ~SEAPLANE(){
        cout<<"销毁水上飞机"<<endl;
    }
    virtual void Show() const{
        cout<<"航行(速度: "<<Speed<<", 翼展: ";
        cout<<this->Width<<", 吃水: "<<this->Depth<<")"<<endl;
    }
};

int main(){
    double s, w, d;
    CRAFT *p;
    cin >> s >> w >> d;
    p = new SEAPLANE(s, w, d);
    p->Show();
    delete p;
    return 0;
}
