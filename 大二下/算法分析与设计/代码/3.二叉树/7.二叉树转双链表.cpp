/*二叉树转双链表：
题目：（微软面试题）将二叉树转换为双向链表，直接使用二叉树节点作为双向链表的节点，只需改变各节点中
    left和right指针的值，使其分别指向链表中的左边（前序）节点和右边（后继）节点。转换后，从双向链
    表最左 (右) 端的节点出发，沿right (left) 指针遍历出的值序列与二叉树中序遍历 (的反转) 结果必
    须一致。
函数接口定义：
    template <typename E>
    BinNode<E>* transformBinTreeToDLList(BinNode<E>* root);
    将二叉树转换为双向链表，返回链表最左端节点的位置。开始时，指针root指向二叉树的根节点。
思路：中序遍历存入vector，然后再构造双链表
*/
#include <iostream>
#include<vector>

template <typename E>
class BinNode{
public:
    virtual ~BinNode() {}
    virtual BinNode* left() const = 0; //返回left指针值
    virtual BinNode* right() const = 0; //返回right指针值
    virtual void setLeft(BinNode* ) = 0; //设置left指针
    virtual void setRight(BinNode* ) = 0; //设置right指针
    virtual bool isLeaf() = 0;
};
template <typename E>
BinNode<E>* constructBinTree(const int N);
//构建二叉树，生成中序遍历序列，返回根节点位置（过程省略）

template <typename E>
void visit(vector<BinNode<E>*> &data,BinNode<E>*root) {
    if(root==NULL){
        return;
    }
    visit(data,root->left());
    data.push_back(root);
    visit(data,root->right());
}

template <typename E>
BinNode<E>* transformBinTreeToDLList(BinNode<E>* root) {
    vector<BinNode<E>* > res;
    visit(res,root);
    
    for(int i=1;i<res.size()-1;i++){
        res[i]->setLeft(res[i-1]);
        res[i]->setRight(res[i+1]);
    }
    res[0]->setLeft(NULL);
    res[0]->setRight(res[1]);
    res[res.size()-1]->setLeft(res[res.size()-2]);
    res[res.size()-1]->setRight(NULL);
    
    return res[0];
}

int main(){
    int N;
    //...
    BinNode<int>* root = constructBinTree<int>(N);
    root = transformBinTreeToDLList<int>(root);
    //...
    /*遍历双向链表，并与二叉树中序遍历序列比较，如果匹配成功，
    输出"correct", 否则输出"wrong"。（过程省略）
    ...
    */
  return 0;

}