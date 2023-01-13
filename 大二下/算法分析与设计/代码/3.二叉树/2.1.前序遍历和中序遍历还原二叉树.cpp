/*前序遍历和中序遍历还原二叉树并输出后序遍历：
思路：
    1.根据前序遍历结果，第一个元素为二叉树的根结点；
    2.观察中序遍历结果，根结点左侧的为左子树，根结点右侧的为右子树；在左、右子树中重复操作1；
    若中序遍历中 子树根结点前（后）再无任何元素，则该子树的左（右）分支为空；
    3.上面的过程是递归的。先找到当前树的根结点，然后划分为左右子树，再分别进入左、右子树重复
    上面的过程，最终还原一棵树。
举例：二叉树（前序遍历为 GDA##FE#MH##Z##)，前序遍历为GDAFEMHZ，中序遍历为ADEFGHMZ，用上述思
路求解：
    1.G为中序遍历ADEFGHMZ的根结点，中序遍历ADEF为其左子树，HMZ为其右子树；
        1.1.D为中序遍历ADEF的根结点，中序遍历A为其左子树，EF为其右子树；
            1.1.1.A为中序遍历A的根结点，其前后无任何元素，则A的左右分支为空；
            1.1.2.F为中序遍历EF的根结点，中序遍历E为其左子树，F的右分支为空；
                1.1.2.1.E为中序遍历E的根结点，其前后无任何元素，则E的左右分支为空；
        1.2.M为中序遍历HMZ的根结点，中序遍历H为其左子树，Z为其右子树；
            1.2.1.H为中序遍历H的根结点，其前后无任何元素，则H的左右分支为空；
            1.2.2.Z为中序遍历Z的根结点，其前后无任何元素，则Z的左右分支为空；
    二叉树构建完成，后序遍历为AEFDHZMG。
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

typedef char BTDataType;
struct BTNode{
	BTDataType node;
	BTNode* left;
	BTNode* right;
};

void PostOrder(BTNode* root){
	if(root==NULL){
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%c",root->node);
}

BTNode* CreateTree(string str1,string str2,int* index){
    if(str2.empty()){
        return NULL;
    }
    int tmp=str2.find(str1[*index]);    //在中序遍历str2中找到根结点
    string subs1=str2.substr(0,tmp);    //截取str2根结点的左子树
    string subs2(str2,tmp+1);           //截取str2根结点的右子树
    BTNode* root=new BTNode[sizeof(BTNode)];
	root->node=str1[*index];            //初始化
    root->left=NULL;
    root->right=NULL;
    (*index)++;
    root->left=CreateTree(str1,subs1,index);
    root->right=CreateTree(str1,subs2,index);
    return root;
}
int main(){
    string str1,str2;
    getline(cin,str1);                  //前序遍历
    getline(cin,str2);                  //中序遍历
    int index=0;
    BTNode* root=CreateTree(str1,str2,&index);
    PostOrder(root);
    
    return 0;
}