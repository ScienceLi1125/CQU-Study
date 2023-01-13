/*哈夫曼编码
题目:要求针对给定的字符串,按照哈夫曼编码原理对其进行编码(即:转换为01串),并输出其对应的哈夫曼编码。
    注：字符串中的字符按照ASCII码给定序号,如vggba这个字符串中的字符序号分别为43321;构建哈夫曼树时
    则按照序号顺序排列字符,如权值最小的两个字符为a和b,而不是b和a。
输入:一个整数n,然后依次输入n个字符串。
输出:针对每个输入的字符串，输出其哈夫曼编码。
输入样例:
2
avvvdddeeeffffgggggjk
eeeffrnvjshvhssnn
输出样例:
11110110110110100100100101101101000000000101010101111111110
11011011001001010111111001010000111000110000111111
提示:
avvvdddeeeffffgggggjk
11110 110110110 100100100 101101101 00000000 0101010101 11111 1110
eeeffrnvjshvhssnn
110110110 010010 1011 111 100 1010 00 011 100 011 0000 111111
思路:字符权重为字符串中字符频率,权重相同时按ASCII码序(几个字符新合成的按码序和)
*/
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

class HuffNode{
public:
    virtual ~HuffNode(){}
    virtual int weight()=0;     //节点权重
    virtual int priority()=0;   //节点优先级(ASCII码和,prt小的优先级高)
    virtual bool isLeaf()=0;
    virtual HuffNode* merge(HuffNode* node)=0;
};
class IntlNode:public HuffNode{
private:
    HuffNode* lc;
    HuffNode* rc;
    int wgt;
    int prt;
public:
    IntlNode(HuffNode* l,HuffNode* r){
        lc=l;
        rc=r;
        wgt=l->weight()+r->weight();
        prt=l->priority()+r->priority();
    }
    int weight(){
        return wgt;
    }
    int priority(){
        return prt;
    }
    bool isLeaf(){
        return 0;
    }
    HuffNode* left() const{
        return lc;
    }
    HuffNode* right() const{
        return rc;
    }
    void setLeft(HuffNode* b){
        lc=(HuffNode*)b;
    }
    void setRight(HuffNode* b){ 
        rc=(HuffNode*)b;
    }
    HuffNode* merge(HuffNode* node){
        IntlNode* ans=new IntlNode(this,node);
        return ans;
    }
};
class LeafNode:public HuffNode{
private:
    char val;   //节点值
    int wgt;    //权重
    int prt;    //优先级
public:
    LeafNode(char v,int w,int p){
        val=v;
        wgt=w;
        prt=p;
    }
    char value(){
        return val;
    }
    int weight(){
        return wgt;
    }
    int priority(){
        return prt;
    }
    bool isLeaf(){
        return 1;
    }
    HuffNode* merge(HuffNode* node){
        IntlNode* ans=new IntlNode(this,node);
        return ans;
    }
};

map<char,string> dic;   //存储字符的哈夫曼编码
void Encode(HuffNode* root,string s){
    if(root->isLeaf()){
        LeafNode tmp=*(LeafNode*)root;
        dic[tmp.value()]=s;
        return;
    }
    IntlNode* temp=(IntlNode*)root;
    Encode(temp->left(),s+"0");
    Encode(temp->right(),s+"1");
    delete temp;
    return;
}

// class HuffTree{
// private:
//     HuffNode* root;
// public:
//     HuffTree()
// };

struct cmp{     //优先队列默认从大到小
    bool operator()(HuffNode* n1,HuffNode* n2){
        if(n1->weight()<n2->weight()){      //频率少(权重小)的在前
            return 0;
        }else if(n1->weight()>n2->weight()){
            return 1;
        }else{                              //频率相同时看ASCII码序
            if(n1->priority()<n2->priority()){
                return 0;
            }else{
                return 1;
            }
        }
    }
};

int main(){
    int n;
    cin>>n;
    string s;
    for(int i=0;i<n;i++){
        cin>>s;
        map<char,int> mp;                       //map存储节点
        for(int j=0;j<s.length();j++){
            mp[s[j]]++;
        }
        priority_queue<HuffNode*,vector<HuffNode*>,cmp> q;  //优先队列存储节点
        map<char,int,cmp>::iterator it;         //迭代获得字符顺序(map自动排序按key值排序)
        int cnt=1;
        for(it=mp.begin();it!=mp.end();it++){
            LeafNode* tmp=new LeafNode(it->first,it->second,cnt++);
            // cout<<tmp->value()<<" "<<tmp->weight()<<" "<<tmp->priority()<<endl;
            q.push(tmp);
        }
        while(q.size()>1){
            HuffNode* tmp1=q.top();
            q.pop();
            HuffNode* tmp2=q.top();
            q.pop();
            IntlNode* ans=(IntlNode*)tmp1->merge(tmp2);
            q.push(ans);
            // cout<<tmp1->weight()<<" "<<tmp2->weight()<<" "<<ans->weight()<<endl;
        }
        HuffNode* root=q.top();
        // cout<<root->weight()<<endl;
        Encode(root,"");
        // map<char,string>::iterator it2;
        // for(it2=dic.begin();it2!=dic.end();it2++){
        //     cout<<it2->first<<" "<<it2->second<<endl;
        // }
        for(int j=0;j<s.length();j++){
            cout<<dic[s[j]];
        }
        cout<<endl;
        dic.erase(dic.begin(),dic.end());
    }


    return 0;
}
