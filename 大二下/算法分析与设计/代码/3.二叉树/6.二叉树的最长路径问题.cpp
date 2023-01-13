/*二叉树的最长路径问题：
题目：如果把二叉树看着无向图，可以求出任意两个节点间的路径长度，与路径中经过的边数量相等。这里的路
    径指的是简单路径，即同一个节点不会在路径上出现两次以上。求二叉树中所有节点之间的路径长度的最大
    值。
函数接口定义：
template <typename E>
int LongestPathInBinaryTree(BinNode<E>* root, int& max_dist);
    其中root指向二叉树的根（初始值），max_dist用来记录二叉树的最长路径长度。
思路：要求相距最远的两个节点，有两种情况，一种是经过根节点，在左右子树中各一部分；另一种是不经过根
    节点，在左/右子树中。实际两种情况可以归一，即该二叉树中最长路径等于 某一结点 的左子树深度+右子
    树深度。采用递归，函数返回左右子树较大的深度，同时函数内部通过比较max_dist与左右子树各自的深度
    之和，不断更新max_dist。递归结束后max_dist即为所有节点之间的路径长度的最大值
*/
#include <iostream>
using namespace std;

template <typename E>
class BinNode{                              //二叉树节点
    public:
        virtual ~BinNode() {}
        virtual BinNode* left() const = 0;  //返回左子树的根位置
        virtual BinNode* right() const = 0; //返回右子树的根位置
        virtual bool isLeaf() = 0;
}; 

template <typename E>
BinNode<E>* constructBinTree(const int N);
//生成N个节点的二叉树，返回根位置（过程省略）

template <typename E>
int LongestPathInBinaryTree(BinNode<E>* root, int& max_dist){
    //若写成root->isLeaf(),则有可能是该节点有左子无右子，下面调用root->right()时会出现段错误
    if(root==NULL){
        return -1;                  //访问了空结点，即root的父节点没有这个子节点，因此返回-1
    }
    int LeftDepth=LongestPathInBinaryTree(root->left(),max_dist)+1;
    int RightDepth=LongestPathInBinaryTree(root->right(),max_dist)+1;
    int distance=LeftDepth+RightDepth;                  //当前节点的最长路径
    max_dist=max_dist>distance ? max_dist:distance;     //更新最长路径
    return LeftDepth>RightDepth ? LeftDepth:RightDepth;
}

int main(){
    int N; //节点数量
    //...
    BinNode<int> root = constructBinTree<int>(N);

    int max_dist = 0;    //最长路径长度的初始值
    LongestPathInBinaryTree<int>(root, max_dist);  //寻找最长路径
    cout << max_dist << endl;      //输出最长路径的长度
    //...
    return 0;
}
