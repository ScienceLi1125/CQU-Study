/*中序遍历和后序遍历还原二叉树并输出前序遍历：
思路：
    1.根据后序遍历结果，最后一个元素为二叉树的根结点；
    2.观察中序遍历结果，根结点右侧的为右子树，根结点左侧的为左子树；在右、左子树中重复操作1；
    若中序遍历中 子树根结点后（前）再无任何元素，则该子树的右（左）分支为空；
    3.上面的过程是递归的。先找到当前树的根结点，然后划分为左右子树，再分别进入右、左子树重复
    上面的过程，最终还原一棵树。
举例：二叉树（前序遍历为 GDA##FE#MH##Z##)，后序遍历为AEFDHZMG，中序遍历为ADEFGHMZ，用上述思
路求解：
    1.G为中序遍历ADEFGHMZ的根结点，中序遍历HMZ为其右子树，ADEF为其左子树；
        1.1.M为中序遍历HMZ的根结点，中序遍历Z为其右子树，H为其左子树；
            1.1.1.Z为中序遍历H的根结点，其前后无任何元素，则Z的左右分支为空；
            1.1.2.H为中序遍历Z的根结点，其前后无任何元素，则H的左右分支为空；
        1.2.D为中序遍历ADEF的根结点，中序遍历EF为其右子树，A为其左子树；
            1.2.1.F为中序遍历EF的根结点，F的右分支为空，中序遍历E为其左子树；
                1.2.1.1.E为中序遍历E的根结点，其前后无任何元素，则E的左右分支为空；
            1.2.2.A为中序遍历A的根结点，其前后无任何元素，则A的左右分支为空；
    二叉树构建完成，前序遍历为GDAFEMHZ
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

void PrevOrder(BTNode* root){
	if(root==NULL){
		return;
	}
	printf("%c",root->node);
	PrevOrder(root->left);
	PrevOrder(root->right);
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
    (*index)--;
    root->right=CreateTree(str1,subs2,index);
    root->left=CreateTree(str1,subs1,index);
    return root;
}
int main(){
    string str1,str2;
    getline(cin,str1);                  //后序遍历
    getline(cin,str2);                  //中序遍历
    int index=str2.length()-1;
    BTNode* root=CreateTree(str1,str2,&index);
    PrevOrder(root);
    
    return 0;
}