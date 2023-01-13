/*买股票问题时间优化：
    计算Income时二重循环显然大大增加了时间复杂度，现用二叉搜索树代替数组搜索
    对卖出的股票将其节点值标记为0（删除可以提高搜索效率，但删除本身比较耗时）
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
int Income=0;
int price0;                             //最后一天股票价格
void search(BTNode* root,int n){        //用来遍历n节点前面<n的节点
    if(root==NULL){
        return;
    }
    if(root->node!=0 && root->node<n){  //卖出股票
        Income+=n;
        root->node=0;
    }
    search(root->left,n);
    if(root->node<n){                   //简化搜索
        search(root->right,n);
    }
}
void search(BTNode* root){              //重载函数，遍历没卖出的股票
    if(root==NULL){
        return;
    }
    if(root->node!=0){                  //没卖出的股票
        Income+=price0;
    }
    search(root->left);
    search(root->right);
}
int main(){
    int N;
    cin>>N;
    BTNode* root=NULL;
    int Pay=0;
    for(int i=0;i<N-1;i++){             //最后一天不买
        int n;
        cin>>n;       
        Pay+=n;
        root=CreateTree(n,root);
        /*二叉搜索树构建过程中，此时树上的节点相较于n均为之前的价格，因此此时便可以比较前面几日
        节点是否可以卖掉。卖掉的节点值标记为0。
        */
        search(root,n);
    }
    cin>>price0;
    search(root); 
    cout<<Income-Pay<<endl;

    return 0;

}