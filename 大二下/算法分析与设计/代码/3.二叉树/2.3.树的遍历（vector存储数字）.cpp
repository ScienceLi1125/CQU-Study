/*树的遍历：
题目：给定一棵二叉树的后序遍历和中序遍历，请你输出其层序遍历的序列。这里假设键值都是互不相等
	的正整数。
输入：第一行给出一个正整数N（≤30），是二叉树中结点的个数。第二行给出其后序遍历序列。第三行给
	出其中序遍历序列。数字间以空格分隔。
输出：在一行中输出该树的层序遍历的序列。数字间以1个空格分隔，行首尾不得有多余空格。
思路：与之前字符不同，本题数字可能为两位，字符串不再适用，因此改为vector<int>
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

BTNode* CreateTree(vector<int> Postv,vector<int> Inv,int* index){
    if(Inv.empty()){
        return NULL;
    }
    int tmp=find(Inv,Postv[*index]);    //在中序遍历Inv中找到根结点
	vector<int> subv1;					//截取Inv根结点的左子树
	vector<int> subv2;					//截取Inv根结点的右子树
    subv1.assign(Inv.begin(),Inv.begin()+tmp);
    subv2.assign(Inv.begin()+tmp+1,Inv.end());
    BTNode* root=new BTNode[sizeof(BTNode)];
	root->node=Postv[*index];            //初始化
    root->right=NULL;
    root->left=NULL;
    (*index)--;
    root->right=CreateTree(Postv,subv2,index);
    root->left=CreateTree(Postv,subv1,index);
    return root;
}
int main(){
	int N;
	cin>>N;
	vector<int> Postv;
	vector<int> Inv;
	for(int i=0;i<N;i++){
		int m;
		cin>>m;
		Postv.push_back(m);
	}
	for(int i=0;i<N;i++){
		int m;
		cin>>m;
		Inv.push_back(m);
	}
    int index=Inv.size()-1;
    BTNode* root=CreateTree(Postv,Inv,&index);
    LevelOrder(root);
	for(int i=0;i<N-1;i++){
		cout<<Levelv[i]<<" ";
	}
	cout<<Levelv[N-1];
    
    return 0;
}