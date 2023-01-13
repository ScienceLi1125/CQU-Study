#include<iostream>
using namespace std;

class Point{
public:
    Point(double x,double y):X(x),Y(y){};
    /*
    Point operator+=(const Point &p2){
       X+=p2.X;
       Y+=p2.Y;
       return *this;            //不可以定义p3操作后返回p3，因为该函数的作用是改变当前对象的值
    }
    void operator-=(const Point &p2){   //两种写法都可以
       X-=p2.X;
       Y-=p2.Y;
    }
    */
    bool operator==(const Point &p2){
        if((this->X==p2.X)&&(this->Y==p2.Y)){
            return 1;
        }
        else{
            return 0;
        }
    }

    //算数操作符一般写成非成员形式
    friend Point operator+(const Point &p1,const Point &p2);
    friend Point operator-(const Point &p1,const Point &p2);
    friend Point operator+=(Point &p1,const Point &p2);
    friend Point operator-=(Point &p1,const Point &p2);
    friend ostream&operator<<(ostream&os,const Point &t);
private:
    double X;
    double Y;
};
Point operator+(const Point &p1,const Point &p2){
    Point p3(0,0);
    p3.X=p1.X+p2.X;
    p3.Y=p1.Y+p2.Y;
    return p3;
}
Point operator-(const Point &p1,const Point &p2){
    Point p3(0,0);
    p3.X=p1.X-p2.X;
    p3.Y=p1.Y-p2.Y;
    return p3;
}
Point operator+=(Point &p1,const Point &p2){    //函数需要修改p1，因此不加const关键字
    p1.X+=p2.X;                                 //外部函数调用的方式为f(a,b),因此需要返回值
    p1.Y+=p2.Y;
    return p1;
}
ostream&operator<<(ostream&os,const Point &t)
{
    os<<t.X<<","<<t.Y;
    return os;
}

int main() {
    Point p1(2,3);
    cout<<p1<<endl;
    Point p2(4,5);
    cout<<p2<<endl;
    Point p3 = p1+p2;    
    cout<<p3<<endl;
    p3 = p2-p1;
    cout<<p3<<endl;
    p1 += p2;
    cout<<p1<<endl;
    cout<<(p1==p2)<<endl;

    return 0;
}

