/*模板类实现二叉树可以存储键值，功能更强大
*/
#include <iostream>
using namespace std;

template<typename E> class BinNode{         //抽象类
public:
    virtual ~BinNode(){}
    virtual E& element()=0;
    virtual void setElement(const E&)=0;
    virtual BinNode* left() const=0;
    virtual BinNode* right() const=0;
    virtual setLeft(BinNode*)=0;
    virtual setLeft(BinNode*)=0;
    virtual bool isLeaf()=0;
};

template<typename E>
void preorder(BinNode<E>* root){            //前序遍历
    if(root==NULL){
        return;
    }
    //按要求操作
    preorder(root->left());
    preorder(root->right());
}
template<typename E>
void inorder(BinNode<E>* root){            //中序遍历
    if(root==NULL){
        return;
    }
    inorder(root->left());
    //按要求操作
    inorder(root->right());
}
template<typename E>
void postorder(BinNode<E>* root){          //后序遍历
    if(root==NULL){
        return;
    }
    postorder(root->left());
    postorder(root->right());
    //按要求操作
}

template<typename E>
int count(BinNode<E>* root){                //计算节点个数
    if(root==NULL){
        return 0;
    }
    return 1+count(root->left())+count(root->right());
}

template<typename Key,typename E>
class BSTNode:public BinNode<E>{            //二叉树结点
private:
    Key k;
    E it;
    BSTNode* lc;
    BSTNode* rc;
public:
    BSTNode(){lc=rc=NULL;}
    BSTNode(Key K,E e,BSTNode* l=NULL,BSTNode* r=NULL){
        k=K;
        it=e;
        lc=l;
        rc=r;
    }
    ~BSTNode(){}

    E& element(){
        return it;
    }
    Key& key(){
        return k;
    }
    void setElement(const E& e){
        it=e;
    }
    void setKey(const Key& K){
        k=K;
    }

    inline BSTNode* left() const{
        return lc;
    }
    inline BSTNode* right() const{
        return rc;
    }
    void setLeft(BinNode<E>* b){
        lc=(BSTNode*)b;
    }
    void setRight(BinNode<E>* b){
        rc=(BSTNode*)b;
    }
    bool isLeaf(){
        return (lc==NULL)&&(rc==NULL);
    }
};

template<typename Key,typename E>
bool checkBST(BSTNode<Key,E>* root,Key low,Key high){   //判断是否是二叉搜索树
    if(root==NULL){
        return true;
    }
    Key rootkey=root->key();
    if((rootkey<low)||(rootkey>high)){
        return false;
    }
    if(!checkBST<Key,E>(root->left(),low,rootkey)){
        return false;
    }
    return checkBST<Key,E>(root->right(),rootkey,high);
}


int main(){
    

    return 0;

} 