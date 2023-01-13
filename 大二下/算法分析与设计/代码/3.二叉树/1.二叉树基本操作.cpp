/*结构体定义的二叉树只能完成简单的操作，节点也只能存储单值，用处有限但比较简单
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

//链式二叉树的结点类型
typedef char BTDataType;        //结点中存储的元素类型（以char为例）

//链式二叉树的结构（Binary Tree Node二叉树结点）
/*结构体二叉树包含3个成员，结点、左子、右子，左右子用指针定义便于向下搜寻其自身左右子树，并且
	可以赋为空，即NULL
*/
struct BTNode{
	BTDataType node;            //结点
	BTNode* left;               //左指针（指向左孩子）
	BTNode* right;              //右指针（指向右孩子）
};

//二叉树相关函数声明
void PrevOrder(BTNode* root);				//前序遍历
void InOrder(BTNode* root);					//中序遍历
void PostOrder(BTNode* root);				//后序遍历
void LevelOrder(BTNode* root);				//层序遍历
int BTSize(BTNode* root);					//结点的个数
int BTKLevelSize(BTNode* root,int k);		//第k层结点的个数
int BTMaxDepth(BTNode* root);				//树的最大深度
BTNode* invertTree(BTNode* root);			//翻转二叉树
void BTDestroy(BTNode* root);				//二叉树的销毁
BTNode* CreateTree(string str,int* index);	//创建树

//打印二叉树
//前序遍历，遍历顺序：根->左子树->右子树
void PrevOrder(BTNode* root){
	if(root==NULL){             //即树为空
		cout<<"#";
		return;
	}
	//根->左子树->右子树
	printf("%c",root->node);
	PrevOrder(root->left);
	PrevOrder(root->right);
}
//中序遍历，遍历顺序：左子树->根->右子树
void InOrder(BTNode* root){
	if(root==NULL){
		cout<<"#";
		return;
	}
	//左子树->根->右子树
	InOrder(root->left);
	printf("%c",root->node);
	InOrder(root->right);
}
//后序遍历，遍历顺序：左子树->右子树->根
void PostOrder(BTNode* root){
	if(root==NULL){
		cout<<"#";
		return;
	}
	//左子树->右子树->根
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%c",root->node);
}
//层序遍历，遍历顺序：自上而下，从左往右逐层访问
/*思路：
	1.先把根入队列，然后开始从队头出数据。
	2.出队头的数据，把它的左孩子和右孩子依次从队尾入队列（NULL不入队列）。
	3.重复进行步骤2，直到队列为空为止。
*/
void LevelOrder(BTNode* root){
	queue<BTNode*> q;			//初始化队列
	if (root!=NULL)
		q.push(root);
	while(!q.empty()){			//当队列不为空时，循环继续
		BTNode* front=q.front();//读取队头元素
		q.pop();				//删除队头元素
		printf("%c ",front->node);
		if (front->left){		//左子非空
			q.push(front->left);//出队元素的左子入队列
		}
		if (front->right){
			q.push(front->right);//出队元素的右子入队列
		}
	}
}

//结点的个数（递归）
/*求解树的结点总数时，可以将问题拆解成子问题递归：
	1.若为空，则结点个数为0。
	2.若不为空，则结点个数=左子树结点个数+右子树结点个数+1（自己）
*/
int BTSize(BTNode* root){	
	//结点个数=左子树的结点个数+右子树的结点个数+自己
	return root==NULL ? 0 : BTSize(root->left)+BTSize(root->right)+1;
}
//第k层结点的个数（递归）
/*相对于根结点的第k层结点的个数=相对于以根结点左子为根的第k-1层结点的个数+相对于以根结点右子
	为根的第k-1层结点的个数。
*/
int BTKLevelSize(BTNode* root,int k){
	if(k<1 || root==NULL){      //空树或输入k值不合法
		return 0;
    }
	if (k==1){                	//第一层结点个数
		return 1;
    }
	return BTKLevelSize(root->left,k-1)+BTKLevelSize(root->right,k-1);
}

//树的最大深度
/*子问题：
	1.若为空，则深度为0。
	2.若不为空，则树的最大深度 = 左右子树中深度较大的值 + 1
*/
int BTMaxDepth(BTNode* root){
	if (root==NULL)				//空树，深度为0
		return 0;
	//树的最大深度 = 左右子树中深度较大的值 + 1
	return max(BTMaxDepth(root->left), BTMaxDepth(root->right)) + 1;
}

//翻转二叉树
/*步骤：
    1.翻转左子树。
    2.翻转右子树。
    3.交换左右子树的位置。
*/
BTNode* invertTree(BTNode* root){
	if(root==NULL){             //根为空，直接返回
		return NULL;
    }
	BTNode* left=invertTree(root->left);
	BTNode* right=invertTree(root->right);
	//左右子树位置交换
	root->left=right;
	root->right=left;
	return root;
}

//二叉树的销毁
/*二叉树的销毁，与其他数据结构的销毁类似，都是一边遍历一边销毁。但是二叉树需要注意销毁结点的顺序，
    遍历时我们应该选用后序遍历，也就是说，销毁顺序应该为：左子树->右子树->根。我们必须先将左右子
    树销毁，最后再销毁根结点，若先销毁根结点，那么其左右子树就无法找到，也就无法销毁了。
*/
void BTDestroy(BTNode* root){
	if (root == NULL){
        return;
    }
	BTDestroy(root->left);      //销毁左子树
	BTDestroy(root->right);     //销毁右子树
	free(root);                 //释放根结点
}

//接口：创建树
/*题目：编一个程序，读入一串先序遍历字符串，根据此字符串建立一个二叉树（以指针方式存储）。
	例如如下的先序遍历字符串：ABC##DE#G##F### 其中“#”表示的是空格，空格字符代表空树。
	建立起此二叉树以后，再对二叉树进行中序遍历，输出遍历结果。
输入：包括1行字符串，长度不超过100。
输出：将输入字符串建立二叉树后输出中序遍历的序列，每个字符后面都有一个空格。每个输出结果占一行。
思路：依次从字符串读取字符：
	1.若该字符不是#，则我们先构建该值的结点，然后递归构建其左子树和右子树。
	2.若该字符是#，则说明该位置之下不能再构建结点了，返回即可。
	构建完树后，使用中序遍历打印二叉树的数据即可。
*/
BTNode* CreateTree(string str,int* index){
    if(str[*index]=='#'){
        (*index)++;
        return NULL;
    }
    //不是NULL，构建结点
	//必须要动态分配内存，否则会被回收，无法实现全局变量构造二叉树
    BTNode* root=new BTNode[sizeof(BTNode)];
	root->node=str[*index];		//初始化
    root->left=NULL;
    root->right=NULL;
    (*index)++;
    //递归构建左子树
    root->left=CreateTree(str, index);
    //递归构建右子树
    root->right=CreateTree(str, index);
    return root;
}

int main(){
    string str;					//输入前序遍历字符串
    getline(cin,str);
    int index=0;
    BTNode* root=CreateTree(str,&index);
    InOrder(root);				//输出中序遍历字符串
    
    return 0;
}