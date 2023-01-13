/* 二叉搜索树的最近公共祖先：
题目：给定一棵二叉搜索树的先序遍历序列，要求你找出任意两结点的最近公共祖先结点（简称 LCA）。
输入：第一行给出两个正整数：待查询的结点对数 M（≤ 1 000）和二叉搜索树中结点个数 N（≤ 10 000）。
    随后一行给出N个不同的整数，为二叉搜索树的先序遍历序列。最后M行，每行给出一对整数键值U和V。所有
    键值都在整型int范围内。
输出：对每一对给定的U和V，如果找到A是它们的最近公共祖先结点的键值，则在一行中输出“LCA of U and V 
    is A.”。但如果U和V中的一个结点是另一个结点的祖先，则在一行中输出“X is an ancestor of Y.”，
    其中X是那个祖先结点的键值，Y是另一个键值。如果二叉搜索树中找不到以U或V为键值的结点，则输出
    “ERROR: U is not found.”或者“ERROR: V is not found.”，或者“ERROR: U and V are not found.”。
思路：当U V分别在某一结点左右子树中时，该节点即为公共祖先
    细节处理：祖先的情况判断根节点的值
    （此方法存在两个超时点）
*/
#include <iostream>
using namespace std;

class BSTNode{
public:
    int value;
    BSTNode* lc;
    BSTNode* rc;

    BSTNode(){lc=rc=NULL;}
    BSTNode(int v,BSTNode* l=NULL,BSTNode* r=NULL){
        value=v;
        lc=l;
        rc=r;
    }
    ~BSTNode(){}
};
BSTNode* inserthelp(BSTNode* root,const int& it){
    if(root==NULL){
        return new BSTNode(it,NULL,NULL);
    }
    if(it<root->value){
        root->lc=(inserthelp(root->lc,it));
    }
    else{
        root->rc=(inserthelp(root->rc,it));
    }
    return root;
}
bool isintree(BSTNode* root,int a){
    if(root==NULL){
        return 0;
    }
    if(root->value==a){
        return 1;
    }
    else if(root->value>a){
        return isintree(root->lc,a);
    }
    else{
        return isintree(root->rc,a);
    }
}
int LCA(BSTNode* root,int U,int V){
    if(root==NULL){
        return NULL;
    }
    if(root->value==U){
        return U;
    }
    if(root->value==V){
        return V;
    }
    if((isintree(root->lc,U)&&isintree(root->rc,V))||(isintree(root->lc,V)&&isintree(root->rc,U))){
        return root->value;
    }
    if(isintree(root->lc,U)&&isintree(root->lc,V)){
        return LCA(root->lc,U,V);
    }
    else{
        return LCA(root->rc,U,V);
    }
}

int main(){
    int M,N;
    cin>>M>>N;
    int n;
    cin>>n;
    BSTNode root(n,NULL,NULL);          //二叉树无头结点，因此根节点必须单独建立
    BSTNode* rt=&root;
    for(int i=1;i<N;i++){
        cin>>n;
        rt=inserthelp(rt,n);
    }
    for(int i=0;i<M;i++){
        int U,V;
        cin>>U>>V;
        if(!isintree(rt,U)&&!isintree(rt,V)){
            cout<<"ERROR: "<<U<<" and "<<V<<" are not found."<<endl;
        }
        else if(!isintree(rt,U)){
            cout<<"ERROR: "<<U<<" is not found."<<endl;
        }
        else if(!isintree(rt,V)){
            cout<<"ERROR: "<<V<<" is not found."<<endl;
        }
        else{
            if(LCA(rt,U,V)==U&&U==V){
                cout<<U<<" is an ancestor of "<<V<<"."<<endl;   //题意表达不清，发现测试点2答案错误后改写
            }
            else if(LCA(rt,U,V)==U){
                cout<<U<<" is an ancestor of "<<V<<"."<<endl;
            }
            else if(LCA(rt,U,V)==V){
                cout<<V<<" is an ancestor of "<<U<<"."<<endl;
            }
            else{
                cout<<"LCA of "<<U<<" and "<<V<<" is "<<LCA(rt,U,V)<<"."<<endl;
            }
        }
    }
    

    return 0;

} 