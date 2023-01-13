/*二叉树的叶节点与分支节点使用不同的类实现存储不同类型的数据。实例如表达式树。此时叶节点不再存储
    子节点的指针
*/
#include <iostream>
using namespace std;

class VarBinNode{
public:
    virtual ~VarBinNode(){}
    virtual bool isLeaf()=0;
    virtual void traverse()=0;              //遍历结点信息
};
class LeafNode:public VarBinNode{
private:
    int Operand;                            //操作数
public:
    LeafNode(const int& val){
        Operand=val;
    }
    bool isLeaf(){
        return true;
    }
    int value(){
        return Operand;
    }
    void traverse(){
        cout<<"Leaf:"<<value()<<endl;
    }
};
class IntlNode:public VarBinNode{
private:
    VarBinNode* lc;
    VarBinNode* rc;
    char Operator;                          //操作符
public:
    IntlNode(const char& op,VarBinNode* l,VarBinNode* r){
        Operator=op;
        lc=l;
        rc=r;
    }
    bool isLeaf(){
        return false;
    }
    VarBinNode* left(){
        return lc;
    }
    VarBinNode* right(){
        return rc;
    }
    char value(){
        return Operator;
    }
    void traverse(){
        cout<<"Internal:"<<value()<<endl;
        if(left()!=NULL){
            left()->traverse();
        }
        if(right()!=NULL){
            right()->traverse();
        }
    }
};

int main(){
    

    return 0;

}