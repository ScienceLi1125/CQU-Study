/*建立二叉搜索树时，每放入一个节点都需要从根节点遍历，当节点数较多时容易超时。14.1代码中将其余函数
    都注释掉，只保留inserthelp函数都有两个测试点运行超时。因此上述建树方法不可取。
方法优化：采用层序建树可以大大降低时间复杂度。由二叉搜索树前序pre和中序in可得二叉搜索树层序遍历，
    前序遍历即为输入，中序遍历即为输入后升序排列
    同时为了减小查找复杂度，isintree的功能用map来实现，map[node]!=0代表节点在树中
*/
#include <iostream>
#include <map>
#include <algorithm>
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
/*用前序遍历和中序遍历构建二叉搜索树：在中序遍历中找到前序遍历的第一个元素，中序遍历中该元素左边为
左子树，右边为右子树，分别对子树再递归，由此实现层序建树
*/
BSTNode* BuildTree(int cnt,int* pre,int* in){   //第一个参数约束数组结束位置（int*+i只能限制数组起始位置）
    if(cnt<1){
        return NULL;                            //空树
    }
    BSTNode* root=new BSTNode();
    root->value=pre[0];
    int i=0;
    for(;i<cnt;i++){
        if(pre[0]==in[i]){
            break;
        }
    }
    //用指针传数组巧妙实现数组的截取
    root->lc=BuildTree(i,pre+1,in);             //0~i为前序遍历左子树
    root->rc=BuildTree(cnt-i-1,pre+i+1,in+i+1); //cnt-i-1~cnt为右子树
    return root;
}

int LCA(BSTNode* root,int U,int V){
    if(root==NULL){
        return NULL;
    }
    // if(root->value==U){
    //     return U;
    // }
    // if(root->value==V){
    //     return V;
    // }
    // if((isintree(root->lc,U)&&isintree(root->rc,V))||(isintree(root->lc,V)&&isintree(root->rc,U))){
    //     return root->value;
    // }
    //上述三种情况可以由一种情况代替
    // if(isintree(root->lc,U)&&isintree(root->lc,V)){
    //     return LCA(root->lc,U,V);
    // }
    // else{
    //     return LCA(root->rc,U,V);
    // }
    //isintree(root->lc,U)等价于U<root->value，大大减小时间复杂度
    if(U>root->value&&V>root->value){
        return LCA(root->rc,U,V);
    }
    if(U<root->value&&V<root->value){
        return LCA(root->lc,U,V);
    }
    else{
        return root->value;
    }
}


int main(){
    int M,N;
    cin>>M>>N;
    int n;                      //节点值
    int* pre=new int[N];        //前序遍历
    int* in=new int[N];         //中序遍历
    map<int,int> mp;            //判断节点是否在树中
    BSTNode* rt=NULL;
    for(int i=0;i<N;i++){
        cin>>n;
        mp[n]=1;
        pre[i]=n;
        in[i]=n;
    }
    sort(in,in+N);
    rt=BuildTree(n,pre,in);
    for(int i=0;i<M;i++){
        int U,V;
        cin>>U>>V;
        if(!mp[U]&&!mp[V]){
            cout<<"ERROR: "<<U<<" and "<<V<<" are not found."<<endl;
        }
        else if(!mp[U]){
            cout<<"ERROR: "<<U<<" is not found."<<endl;
        }
        else if(!mp[V]){
            cout<<"ERROR: "<<V<<" is not found."<<endl;
        }
        else{
            int lca=LCA(rt,U,V);                //多次递归消耗时间
            if(lca==U){
                cout<<U<<" is an ancestor of "<<V<<"."<<endl;
            }
            else if(lca==V){
                cout<<V<<" is an ancestor of "<<U<<"."<<endl;
            }
            else{
                cout<<"LCA of "<<U<<" and "<<V<<" is "<<lca<<"."<<endl;
            }
        }
    }
    

    return 0;
} 