/*挑选苹果：
题目：果园采摘了n个苹果，分别放在若干个篮筐中。现给出n个苹果所在篮筐的情况，请找出每个篮筐中重量
    最重的苹果。定义一个苹果类Apple，有编号（id）、重量（weight）、直径（diameter）成员变量。
输入：首先输入一个整型数n（1<=n<=999999），表示n个苹果。 紧跟着n行输入，每一行格式为：篮筐号，
    苹果编号（id），重量（weight），直径（diameter）。篮筐号为整数，取值区间为[1,999999]，id为
    字符串，weight、diameter为正整数。
输出：按篮筐号从小到大排序，输出每个篮筐中重量最重的苹果信息。题目保证每个篮筐中只有一个重量最重
    的苹果。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Apple
{
public:         //成员变量不可以封装成private，否则主函数内的对象无法访问其成员变量
    int No;     //篮筐号
    string Id;  //编号
    int Weight;
    int Diameter;
    Apple(int no=0,string id=" ",int weight=0,int diameter=0){  //默认构造函数
        this->No=no;
        this->Id=id;
        this->Weight=weight;
        this->Diameter=diameter;
    }
    void print(){
        cout<<No<<" "<<Id<<" "<<Weight<<" "<<Diameter<<endl;
    }
};

bool compare1(Apple a1,Apple a2){
    return a1.Weight>a2.Weight;
}
bool compare2(Apple a1,Apple a2){
    return a1.No<a2.No;
}

int main(){
    int n;
    cin>>n;
    Apple apple[100];                           //此处要求Apple类存在默认构造函数
    int basket[10]={0};                         //int型数组用来记各篮筐苹果情况
    vector<Apple> heavy;                        //Apple型动态数组用来存储每筐最重苹果
    int No;
    string Id;
    int Weight;
    int Diameter;
    for(int i=0;i<n;i++){
        cin>>No;
        cin>>Id;
        cin>>Weight;
        cin>>Diameter;
        apple[i]=Apple(No,Id,Weight,Diameter);  //向Apple型数组里加入Apple型元素
        basket[apple[i].No]=1;      //无苹果的篮筐记为0，有苹果的记为1，找到最重苹果的记为2
    }
    sort(apple,apple+n,compare1);               //此处只是按Weight排序，没有考虑篮筐
    for(int j=0;j<n;j++){
        if(basket[apple[j].No]==1){             //即该筐中有苹果且尚未找到最重苹果
            heavy.push_back(apple[j]);
            basket[apple[j].No]=2;
        }
    }
    sort(heavy.begin(),heavy.end(),compare2);
    for(int k=0;k<heavy.size();k++){
        heavy[k].print();
    }
    
    return 0;
}