#include <iostream>
using namespace std;

class Rectangle
{
public:
    Rectangle(){            //无参构造函数

    }
    Rectangle(float a=1,float b=1){     //默认值构造函数
        width=a;
        height=b;
    }
    float getArea(){
        return width*height;
    }
    float getPerimeter(){
        return 2*(width+height);
    }

private:
    double width;
    double height;
};



int main(){
    float m,n;
    cin>>m>>n;
    Rectangle rectangle(m,n);
    float area=rectangle.getArea();
    float perimeter=rectangle.getPerimeter();
    cout << area << endl;
    cout << perimeter << endl;

    return 0;
}