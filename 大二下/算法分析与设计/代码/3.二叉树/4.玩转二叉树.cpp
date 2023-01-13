/*玩转二叉树：
题目：给定一棵二叉树的中序遍历和前序遍历，请你先将树做个镜面反转，再输出反转后的层序遍历的序列。
    所谓镜面反转，是指将所有非叶结点的左右孩子对换。这里假设键值都是互不相等的正整数。
输入：第一行给出一个正整数N（≤30），是二叉树中结点的个数。第二行给出其中序遍历序列。第三行给出
    其前序遍历序列。数字间以空格分隔。
输出：在一行中输出该树反转后的层序遍历的序列。数字间以1个空格分隔，行首尾不得有多余空格。
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

//存储数字可能出现两位，字符串不再适用，因此改用vector<int>
typedef int BTDataType;
struct BTNode{
	BTDataType node;
	BTNode* left;
	BTNode* right;
};

vector<int> Levelv;
void LevelOrder(BTNode* root){
	queue<BTNode*> q;
	if (root!=NULL)
		q.push(root);
	while(!q.empty()){
		BTNode* front=q.front();
		q.pop();
		Levelv.push_back(front->node);
		if (front->left){
			q.push(front->left);
		}
		if (front->right){
			q.push(front->right);
		}
	}
}

int find(vector<int> v,int n){
	for(int i=0;i<v.size();i++){
		if(v[i]==n){
			return i;
		}
	}
	return -1;
} 

BTNode* invertTree(BTNode* root){
	if(root==NULL){
		return NULL;
    }
	BTNode* left=invertTree(root->left);
	BTNode* right=invertTree(root->right);
	root->left=right;
	root->right=left;
	return root;
}

BTNode* CreateTree(vector<int> Prev,vector<int> Inv,int* index){
    if(Inv.empty()){
        return NULL;
    }
    int tmp=find(Inv,Prev[*index]);     //在中序遍历Inv中找到根结点
	vector<int> subv1;					//截取Inv根结点的左子树
	vector<int> subv2;					//截取Inv根结点的右子树
    subv1.assign(Inv.begin(),Inv.begin()+tmp);
    subv2.assign(Inv.begin()+tmp+1,Inv.end());
    BTNode* root=new BTNode[sizeof(BTNode)];
	root->node=Prev[*index];            //初始化
    root->left=NULL;
    root->right=NULL;
    (*index)++;
    root->left=CreateTree(Prev,subv1,index);
    root->right=CreateTree(Prev,subv2,index);
    return root;
}
int main(){
	int N;
	cin>>N;
	vector<int> Prev;
	vector<int> Inv;
	for(int i=0;i<N;i++){               //先输入中序遍历，再输入前序遍历，注意顺序
		int m;
		cin>>m;
		Inv.push_back(m);
	}
	for(int i=0;i<N;i++){
		int m;
		cin>>m;
		Prev.push_back(m);
	}
    int index=0;
    BTNode* root=CreateTree(Prev,Inv,&index);
    invertTree(root);
    LevelOrder(root);
	for(int i=0;i<N-1;i++){
		cout<<Levelv[i]<<" ";
	}
	cout<<Levelv[N-1];
    
    return 0;
}