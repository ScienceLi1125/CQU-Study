/*是否同一棵二叉搜索树：
题目：给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插
    入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。
    于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。
输入：包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和
    需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。随后L行，每行给出N个插入
    的元素，属于L个需要检查的序列。
    简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。
输出：对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输
    出“No”。
*/
#include <iostream>
using namespace std;

struct BTNode{
	int node;
	BTNode* left;
	BTNode* right;
};
BTNode* CreateTree(int n,BTNode* root){
    if(root==NULL){
        return new BTNode{n,NULL,NULL};
    }
    if(n<root->node){
        root->left=CreateTree(n,root->left);
    }
    else{
        root->right=CreateTree(n,root->right);
    }
    return root;
}
bool CompareTree(BTNode* root1,BTNode* root2){
    if(root1==NULL && root2==NULL){     //都是空结点
        return 1;
    }
    if(root1==NULL && root2!=NULL){     //只有一个为空
        return 0;
    }
    if(root1!=NULL && root2==NULL){
        return 0;
    }
    if(root1->node!=root2->node){       //都不是空结点
        return 0;
    }
    if(!CompareTree(root1->left,root2->left)){
        return 0;
    }
    return CompareTree(root1->right,root2->right);
}

int main(){
    int N,L;
    while(cin>>N && N!=0){          //若写成cin>>N>>L && N!=0，结束时只有N=0输入无法终止
        BTNode* root0=NULL;
        cin>>L;
        for(int i=0;i<N;i++){       //构建参照的二叉树
            int n;
            cin>>n;
            root0=CreateTree(n,root0);
        }
        for(int j=0;j<L;j++){       //与参照二叉树比较的二叉树
            BTNode* root=NULL;
            for(int i=0;i<N;i++){
                int n;
                cin>>n;
                root=CreateTree(n,root);
            }
            if(CompareTree(root0,root)){
                cout<<"Yes"<<endl;
            }
            else{
                cout<<"No"<<endl;
            }
        }
    }

    return 0;

}