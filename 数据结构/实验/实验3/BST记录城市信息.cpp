/*BST的应用：
题目：1.利用BST实现一个城市数据库：每个数据库结点包括城市名称和以整数x与y表示的城市坐标。根据
    城市名称组织该BST；
    2.在该数据库上实现按城市名称进行的插入、删除和检索；
    3.打印出以指定字母打头的所有城市记录；
    4.打印出与指定点的距离在给定值之内的所有城市记录；
    5.最后提交完整的实验报告和源程序
输入：第1行：有1个整数m，表示接下来要插入的m条记录。
    第2行到第1+m行：每行表示一个插入记录。包括一个字符串cityName，两个整数x，y。分别表示城市
名称和坐标。
    接下来n行：为不定行数的插入和删除操作。首数字为0代表删除，首数字为1代表插入，首数字为2代表
结束插入、删除操作。
    接下来1行：1个字符，表示要进行检索的指定字母。
    最后1行：3个整数。x，y，d。x，y表示指定点的坐标，d表示距离。
输出：完成插入和删除操作之后中序遍历BST并打印，每条记录包括一行，包括：城市名字
    打以指定字母打头的所有城市记录，每条记录包括一行，包括：城市名字，x和y坐标
    打印与指定点的距离在给定值之内的所有城市记录，每条记录包括一行，包括：城市名字，x和y坐标
注意：自定义类型没有自动转换成NULL(long long int)的功能，因此在类中加入null()函数，需要时可以
    代替NULL，不过需要对象实体(即 E e)才能调用
测试样例：
Input：
4
chongqing 1 1
chengdu 1 2
shenyang 2 2
changchun 2 3
1 shanghai 2 3
0 changchun
0 shenyang
1 beijing 2 2
2
c
0 0 3
Output：
beijing
chengdu
chongqing
shanghai
chengdu 1 2
chongqing 1 1
beijing 2 2
chengdu 1 2
chongqing 1 1
*/
#include <iostream>
#include <sstream>
using namespace std;

class city{
public:
    string cityName;
    int x;
    int y;
    city(string s=" ",int a=0,int b=0){
        cityName=s;
        x=a;
        y=b;
    }
    city null(){                     //若不加static，无法直接调用E::null()
        city c("",0,0);
        return c;
    }
    string information(){
        stringstream ss;
        string s2;
        string s3;
        ss<<x;
        ss>>s2;
        ss.clear();
        ss<<y;
        ss>>s3;
        string s="";
        s+=cityName;
        s+=" ";
        s+=s2;
        s+=" ";
        s+=s3;
        return s;
    }
    char firstletter(){
        return cityName[0];
    }
    bool distance(int a,int b,int d){
        if(((a-x)*(a-x)+(b-y)*(b-y))<=d*d){     //根据提交结果发现挂等号才对
            return 1;
        }
        else{
            return 0;
        }
    }
    // bool operator>(const city&c){       //不需要重载操作符>/<
    //     return cityName>c.cityName;
    // }
    // bool operator<(const city&c){
    //     return cityName<c.cityName;
    // }
    bool operator!=(const city&c){          //需要重载操作符！=
        if(cityName!=c.cityName)    return 1;
        else if(x!=c.x)     return 1;
        else if(y!=c.y)     return 1;
        else                return 0;
    }
};

// bool cmp1(city c1,city c2){          //表示c1<c2
//     return c1.cityName<c2.cityName;
// }
// bool cmp2(city c1,city c2){          //表示c1<c2
//     return c1.cityName>c2.cityName;
// }

template<typename Key,typename E>
class BSTNode{
private:
    Key k;
    E it;
    BSTNode* lc;
    BSTNode* rc;
public:
    BSTNode(){lc=rc=NULL;}
    BSTNode(Key K,E e,BSTNode* l=NULL,BSTNode* r=NULL){
        k=K;
        it=e;
        lc=l;
        rc=r;
    }
    ~BSTNode(){}

    E& element(){
        return it;
    }
    Key& key(){
        return k;
    }
    void setElement(const E& e){
        it=e;
    }
    void setKey(const Key& K){
        k=K;
    }

    inline BSTNode* left() const{
        return lc;
    }
    inline BSTNode* right() const{
        return rc;
    }
    void setLeft(BSTNode<Key,E>* b){
        lc=b;
    }
    void setRight(BSTNode<Key,E>* b){
        rc=b;
    }
    bool isLeaf(){
        return (lc==NULL)&&(rc==NULL);
    }
};

template<typename Key,typename E>
class BST{
private:
    BSTNode<Key,E>* root;
    int nodecount;

    //辅助函数
    void clearhelp(BSTNode<Key,E>*);
    BSTNode<Key,E>* inserthelp(BSTNode<Key,E>*,const Key&,const E&);
    BSTNode<Key,E>* deletemin(BSTNode<Key,E>*);
    BSTNode<Key,E>* getmin(BSTNode<Key,E>*);
    BSTNode<Key,E>* removehelp(BSTNode<Key,E>*,const Key&);
    E findhelp(BSTNode<Key,E>*,const Key&) const;;
    void printhelp(BSTNode<Key,E>*,int) const;
    void printhelp2(BSTNode<Key,E>*,char) const;       //打印以给定字符开头的城市信息
    void printhelp3(BSTNode<Key,E>*,int,int,int) const;//打印在距离范围内的城市信息

public:
    BST(){
        root=NULL;
        nodecount=0;
    }
    ~BST(){
        clearhelp(root);
    }
    void insert(const Key& k,const E& e){
    //函数需要用递归，但nodedcount++只执行一次，因此调用辅助函数，递归由辅助函数实现
        root=inserthelp(root,k,e);
        nodecount++;
    }
    E remove(const Key& k){                 //删除指定结点（键为k的结点）
        E e;
        E tmp=findhelp(root,k);
        if(tmp!=e.null()){
            root=removehelp(root,k);
            nodecount--;
        }
        return tmp;
    }
    E removeAny(){                          //删除调用该函数的结点（即根节点）
        if(root!=NULL){
            E tmp=root->element();
            root=removehelp(root,root->key());
            nodecount--;
            return tmp;
        }
        else{                               //否则自定义类型没有转换到int的功能
            E e;
            return e.null();
        }              
    }
    E find(const Key& k) const{
        return findhelp(root,k);
    }
    int size(){
        return nodecount;
    }
    void print() const{             //中序遍历打印城市信息
        if(root==NULL){
            cout<<"The BST is empty."<<endl;
        }
        else{
            printhelp(root,0);
        }
    }
    void printchar(char c) const{       //中序遍历打印以给定字符开头的城市信息
        if(root==NULL){
            cout<<"The BST is empty."<<endl;
        }
        else{
            printhelp2(root,c);
        }
    }
    void printdistance(int a,int b,int d) const{    //中序遍历打印距离内的城市信息
        if(root==NULL){
            cout<<"The BST is empty."<<endl;
        }
        else{
            printhelp3(root,a,b,d);
        }
    }
};
//辅助函数
template<typename Key,typename E>
E BST<Key,E>::findhelp(BSTNode<Key,E>* root,const Key& k) const{
    E e;                        //无对象无法调用函数
    if(root==NULL){
        return e.null();
    }
    if(k<root->key()){
        return findhelp(root->left(),k);
    }
    else if(k>root->key()){
        return findhelp(root->right(),k);
    }
    else return root->element();
}
template<typename Key,typename E>
BSTNode<Key,E>* BST<Key,E>::inserthelp(BSTNode<Key,E>* root,const Key& k,const E& it){
    if(root==NULL){
        return new BSTNode<Key,E>(k,it,NULL,NULL);
    }
    if(k<root->key()){
        root->setLeft(inserthelp(root->left(),k,it));
    }
    else{
        root->setRight(inserthelp(root->right(),k,it));
    }
    return root;
}
//此处的deletemin直接将指向最小节点的指针指向其右子节点
template<typename Key,typename E>
BSTNode<Key,E>* BST<Key,E>::deletemin(BSTNode<Key,E>* rt){
    if(rt->left()==NULL){
        return rt->right();
    }
    else{
        rt->setLeft(deletemin(rt->left()));
        return rt;
    }
}
template<typename Key,typename E>
BSTNode<Key,E>* BST<Key,E>::getmin(BSTNode<Key,E>* rt){
    if(rt->left()==NULL){
        return rt;
    }
    else{
        return getmin(rt->left());
    }
}
template<typename Key,typename E>
BSTNode<Key,E>* BST<Key,E>::removehelp(BSTNode<Key,E>* rt,const Key &k){
    if(rt==NULL){
        return NULL;
        //return E::null();         //只对返回值为E的函数，此处返回值为指针
    }
    else if(k<rt->key()){
        rt->setLeft(removehelp(rt->left(),k));
    }
    else if(k>rt->key()){
        rt->setRight(removehelp(rt->right(),k));
    }
    else{
        BSTNode<Key,E>* tmp=rt;
        if(rt->left()==NULL){
            rt=rt->right();
            delete tmp;
        }
        else if(rt->right()==NULL){
            rt=rt->left();
            delete tmp;
        }
        else{
            tmp=getmin(rt->right());
            rt->setElement(tmp->element());
            rt->setKey(tmp->key());
            rt->setRight(deletemin(rt->right()));
            delete tmp;
        }
    }
    return rt;
}
template<typename Key,typename E>
void BST<Key,E>::clearhelp(BSTNode<Key,E>* rt){
    if(rt->left()==NULL){
        return;
    }
    clearhelp(rt->left());
    clearhelp(rt->right());
    delete rt;
}
template<typename Key,typename E>
void BST<Key,E>::printhelp(BSTNode<Key,E>* rt,int level) const{
    if(rt==NULL)    return;
    printhelp(rt->left(),level+1);
    cout<<rt->key()<<endl;
    printhelp(rt->right(),level+1);
    delete rt;
}
template<typename Key,typename E>
void BST<Key,E>::printhelp2(BSTNode<Key,E>* rt,char c) const{
    if(rt==NULL)    return;
    printhelp2(rt->left(),c);
    //不建议直接使用(rt->key())[0]这种写法，容易编译失败。采用E e代替
    E e=rt->element();
    if(e.firstletter()==c){
        cout<<e.information()<<endl;
    }
    printhelp2(rt->right(),c);
    delete rt;
}
template<typename Key,typename E>
void BST<Key,E>::printhelp3(BSTNode<Key,E>* rt,int a,int b,int d) const{
    if(rt==NULL)    return;
    printhelp3(rt->left(),a,b,d);
    E e=rt->element();
    if(e.distance(a,b,d)){
        cout<<e.information()<<endl;
    }
    printhelp3(rt->right(),a,b,d);
    delete rt;
}

int main(){
    int m;
    cin>>m;
    BST<string,city> bst;
    for(int i=0;i<m;i++){
        int x,y;
        string s;
        cin>>s>>x>>y;
        city c{s,x,y};
        bst.insert(s,c);
    }
    //bst.remove("changchun");
    
    string line;
    while(getline(cin,line)){
        if(line=="2"){
            break;
        }
        else if(line[0]=='0'){
            string s="";
            for(int i=2;i<line.length();i++){
                s+=line[i];
            }
            bst.remove(s);
        }
        else if(line[0]=='1'){
            string s="";
            bool flag=0;
            int x;
            int y;
            s+=line[2];
            for(int i=3;i<line.length();i++){
                if(line[i-1]==' '){
                    if(!flag){
                        x=line[i]-'0';
                        flag=1;
                        continue;       //空格后的不是城市名，不加入s
                    }
                    else{
                        y=line[i]-'0';
                        continue;
                    }
                }
                if(!flag&&line[i]!=' '){
                    s+=line[i];
                }
            }
            city c{s,x,y};
            bst.insert(s,c);
        }
    }

    char letter;
    cin>>letter;

    int a,b,d;
    cin>>a>>b>>d;

    bst.print();
    bst.printchar(letter);
    bst.printdistance(a,b,d);

    return 0;
} 