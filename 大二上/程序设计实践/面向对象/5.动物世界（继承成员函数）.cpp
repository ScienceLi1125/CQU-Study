#include <iostream>
using namespace std;

enum COLOR{ WHITE, RED, BROWN, BLACK, KHAKI };      //枚举类型

class Mammal
{
public:
    //constructors
    Mammal(){
        itsAge=0;
        itsWeight=0;
    };
    Mammal(int age){
        itsAge=age;
        itsWeight=0;
    };
    Mammal(int age,int weight){
        itsAge=age;
        itsWeight=weight;
    };

    //accessors
    int GetAge() const{
        return itsAge;
    };
    void SetAge(int age){
        itsAge=age;
    };
    int GetWeight() const{
        return itsWeight;
    };
    void SetWeight(int weight){
        itsWeight=weight;
    };

    //Other methods    
    void Speak() const{
        cout<<"Mammal is speaking..."<<endl;
    };
    void Sleep() const{
        cout<<"Mammal is sleeping..."<<endl;
    };

protected:
    int itsAge;
    int itsWeight;
};

class Dog:public Mammal
{
public:
    Dog(){};
    Dog(int age):Mammal(age){};     //继承时派生类的构造函数要重新定义,但需要调用基类的构造函数
    Dog(int age,int weight):Mammal(age,weight){};
    Dog(int age,int weight,COLOR color):Mammal(age,weight){
        itscolor=color;
    };
    ~Dog(){};

//基类的成员函数直接继承，不需要重新定义
    COLOR GetColor() const{
        return itscolor;
    };
    void SetColor(COLOR color){
        itscolor=color;
    };

    void WagTail(){
        cout<<"The dog is wagging its tail..."<<endl;
    }
    void BegForFood(){
        cout<<"The dog is begging for food..."<<endl;
    }

private:
    COLOR itscolor;
};

int main()
{
    Dog Fido;
    Dog Rover(5);
    Dog Buster(6, 8);
    Dog Yorkie(3, RED);
    Dog Dobbie(4, 20, KHAKI);
    Fido.Speak();
    Rover.WagTail();
    cout << "Yorkie is " << Yorkie.GetAge() << " years old." << endl;
    cout << "Dobbie weighs " << Dobbie.GetWeight() << " pounds." << endl;   
    return 0;
}
