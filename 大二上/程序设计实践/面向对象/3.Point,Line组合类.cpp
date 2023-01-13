#include <iostream>
#include <math.h>
using namespace std;

class Point
{
public:
    int getx(){             //返回x,y坐标
        return x;           //类的对象无法直接访问类的成员，因此写一个调用函数
    }
    int gety(){
        return y;
    }
    void print(){           //输出函数
        cout<<"P("<<Point::x<<","<<Point::y<<")"<<endl;
    }
    Point(int a,int b){     //构造函数
        Point::x=a;
        Point::y=b;
        cout<<"create Point:";
        Point::print();
    }
    Point(const Point &a){  //复制构造函数
        x=a.x;
        y=a.y;
    }

private:
    int x,y;
};

class Line
{
public:
    Line(Point c,Point d):a(c),b(d){
        cout<<"Create a new Line:"<<endl;
    }
    void GetPstart(){
        a.print();
    }
    void GetPend(){
        b.print();
    }
    int GetLen(){
        int x=a.getx()-b.getx();
        int y=a.gety()-b.gety();
        length=sqrt(x*x+y*y);
        return length;
    }

private:
    Point a,b;
    double length;
};


int main(){
    int x1,y1,x2,y2;
    cin>>x1>>y1;
    cin>>x2>>y2;
    Point myp1(x1,y1),myp2(x2,y2);      //建立Point类的对象
    Line L1(myp1,myp2);                 //建立Line类的对象
    cout<<"Line start Point is:";
    L1.GetPstart();
    cout<<"Line end Point is:";
    L1.GetPend();
    cout<<"Length of Line is:"<<L1.GetLen()<<endl;

    return 0;
}