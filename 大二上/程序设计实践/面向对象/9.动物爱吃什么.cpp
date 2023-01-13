#include <iostream>
using namespace std;
#define PI 3.14159f;

class Animal
{
public:
    Animal(int num,string name):Num(num),Name(name){}
    virtual void eat()=0;
    int getnum(){
        return Num;
    }
    string getname(){
        return Name;
    }
private:
    int Num;
    string Name;
};

class Dog:public Animal
{
public:
    Dog(int num,string name):Animal(num,name){}
    int num=getnum();       //Num为Animal中私有成员，无法直接访问，因此在Animal中定义public成员函数得到Num
    string name=getname();
    virtual void eat(){
        cout<<num<<"号"<<name<<"啃骨头"<<endl;
    }
};
class Cat:public Animal
{
public:
    Cat(int num,string name):Animal(num,name){}
    int num=getnum();
    string name=getname();
    virtual void eat(){
        cout<<num<<"号"<<name<<"吃小鱼"<<endl;
    }
};

int main(){
    int num1,num2;
    string name1,name2;
    cin>>num1>>name1>>num2>>name2;
    Animal *animal = new Dog(num1,name1);
    animal->eat();
    delete animal;
    animal = new Cat(num2,name2);
    animal->eat();
    delete animal;

    return 0;
}