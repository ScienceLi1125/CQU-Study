/*树的同构
题目：给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。
现给定两棵树，请你判断它们是否是同构的。
输入：给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N(≤10)，即该树的结点数（此时
    假设结点从0到N?1编号）；随后N行，第i行对应编号第i个结点，给出该结点中存储的1个英文大写字母、
    其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用
    一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。
输出：如果两棵树是同构的，输出“Yes”，否则输出“No”。
输入样例1：
8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -
输出样例1:
Yes
输入样例2：
8
B 5 7
F - -
A 0 3
C 6 -
H - -
D - -
G 4 -
E 1 -
8
D 6 -
B 5 -
E - -
H - -
C 0 2
G - 3
F - -
A 1 4
输出样例2:
No
思路：本题看似为树形结构，但int存储子节点的结构可用线性存储。但所给树形并不能直接看出根节点，因此
    需要FindRoot
*/
#include <iostream>
#include <vector>
using namespace std;

struct Node{
    char value;
    int left;
    int right;
};
int FindRoot(vector<Node> &tree){
    bool flag[tree.size()]={0};
    for(int i=0;i<tree.size();i++){
        if(tree[i].left!=-1){
            flag[tree[i].left]=1;
        }
        if(tree[i].right!=-1){
            flag[tree[i].right]=1;
        }
    }
    for(int i=0;i<tree.size();i++){
        if(flag[i]==0)  return i;
    }
    return -1;
}
bool compare(vector<Node> &tree1,vector<Node> &tree2,int root1,int root2){
    //cout<<tree1[root1].value<<" "<<tree2[root2].value<<endl;
    if(tree1[root1].value!=tree2[root2].value){
        //cout<<tree1[root1].value<<"!="<<tree2[root2].value<<endl;
        return false;
    }
    int left1=tree1[root1].left;
    int right1=tree1[root1].right;
    int left2=tree2[root2].left;
    int right2=tree2[root2].right;
    //cout<<tree1[left1].value<<tree1[right1].value<<tree2[left2].value<<tree2[right2].value<<endl;
    //不同非空子节点情况对应不同递归函数
    //4个都为空
    //if(left1==left2==right1==right2==-1){if(left1==left2==right1==right2==-1){     //不能连等，否则left1==left2返回0/1和后面比较会判0
    if(left1==-1&&left2==-1&&right1==-1&&right2==-1){
        //cout<<1<<endl;
        return true;
    }
    //2个为空
    //else if(tree1[left1].value==-1 && tree2[left2].value==-1 && tree1[right1].value==tree2[right2].value){
    //空的子节点不能用value判断
    else if(left1==-1 && left2==-1 && tree1[right1].value==tree2[right2].value){
        //cout<<2<<endl;
        return compare(tree1,tree2,right1,right2);
    }
    else if(tree1[left1].value==tree2[left2].value && right1==-1 && right2==-1){
        //cout<<3<<endl;
        return compare(tree1,tree2,left1,left2);
    }
    else if(left1==-1 && right2==-1 && tree1[right1].value==tree2[left2].value){
        //cout<<4<<endl;
        return compare(tree1,tree2,right1,left2);
    }
    else if(tree1[left1].value==tree2[right2].value && right1==-1 && left2==-1){
        //cout<<5<<endl;
        return compare(tree1,tree2,left1,right2);
    }
    //都不为空
    if(tree1[left1].value==tree2[left2].value && tree1[right1].value==tree2[right2].value){
        //cout<<6<<endl;
        return compare(tree1,tree2,left1,left2)&&compare(tree1,tree2,right1,right2);
    }
    else if(tree1[left1].value==tree2[right2].value && tree1[right1].value==tree2[left2].value){
        //cout<<7<<endl;
        return compare(tree1,tree2,left1,right2)&&compare(tree1,tree2,right1,left2);
    }
    //cout<<8<<endl;
    return false;
}

int main(){
    int N1,N2;
    cin>>N1;
    vector<Node> tree1(N1);
    for(int i=0;i<N1;i++){
        char c,l,r;
        cin>>c>>l>>r;
        getchar();
        tree1[i].value=c;
        if(l=='-'){
            tree1[i].left=-1;
        }
        else{
            tree1[i].left=l-'0';
        }
        if(r=='-'){
            tree1[i].right=-1;
        }
        else{
            tree1[i].right=r-'0';
        }
    }
    cin>>N2;
    vector<Node> tree2(N2);
    for(int i=0;i<N2;i++){
        char c,l,r;
        cin>>c>>l>>r;
        getchar();
        tree2[i].value=c;
        if(l=='-'){
            tree2[i].left=-1;
        }
        else{
            tree2[i].left=l-'0';
        }
        if(r=='-'){
            tree2[i].right=-1;
        }
        else{
            tree2[i].right=r-'0';
        }
    }
    int root1=FindRoot(tree1);
    int root2=FindRoot(tree2);
    if(N1!=N2){
        cout<<"No"<<endl;
    }
    else if(N1==0){             //空树
        cout<<"Yes"<<endl;
    }
    else{
        if(compare(tree1,tree2,root1,root2)){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }

    return 0;
} 