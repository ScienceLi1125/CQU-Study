#include <iostream>
using namespace std;
#define PI 3.14159f;

class Shape
{
public:
    Shape(){}
    virtual double Area() = 0;          //纯虚函数
};

class Circle:public Shape
{
public:
    Circle(double r):r(r){}
    double r;
    virtual double Area(){
        return r*r*PI;                  //编译器误将PI*r*r中*认为是指针解引用
    }
};
class Square:public Shape
{
public:
    Square(double a1):a1(a1){}
    double a1;
    virtual double Area(){
        return a1*a1;
    }
};
class Rectangle:public Shape
{
public:
    Rectangle(double a2,double b2):a2(a2),b2(b2){}
    double a2,b2;
    virtual double Area(){
        return a2*b2;
    }
};
class Trapezoid:public Shape
{
public:
    Trapezoid(double a3,double b3,double h3):a3(a3),b3(b3),h3(h3) {}
    double a3,b3,h3;
    virtual double Area(){
        return (a3+b3)*h3/2;
    }
};
class Triangle:public Shape
{
public:
    Triangle(double a4,double h4):a4(a4),h4(h4){}
    double a4,h4;
    virtual double Area(){
        return a4*h4/2;
    }
};

int main(){
    double r,a1,a2,b2,a3,b3,h3,a4,h4;   //分别对应圆的半径，正方形的边长，矩形的宽和高，梯形的上底、下底和高，三角形的底和高
    cin>>r>>a1>>a2>>b2>>a3>>b3>>h3>>a4>>h4;
    Shape *shape = new Circle(r);       //将基类对象的地址赋给派生类指针
    double Area1=shape->Area();
    delete shape;
    shape = new Square(a1);
    double Area2=shape->Area();
    delete shape;
    shape = new Rectangle(a2,b2);
    double Area3=shape->Area();
    delete shape;
    shape = new Trapezoid(a3,b3,h3);
    double Area4=shape->Area();
    delete shape;
    shape = new Triangle(a4,h4);
    double Area5=shape->Area();
    delete shape;
    printf("%.3f",Area1+Area2+Area3+Area4+Area5);

    return 0;
}