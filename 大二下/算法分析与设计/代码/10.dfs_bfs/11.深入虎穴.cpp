/*深入虎穴:
题目：著名的王牌间谍007需要执行一次任务，获取敌方的机密情报。已知情报藏在一个地下迷宫里，迷宫只
    有一个入口，里面有很多条通路，每条路通向一扇门。每一扇门背后或者是一个房间，或者又有很多条
    路，同样是每条路通向一扇门......他的手里有一张表格，是其他间谍帮他收集到的情报，他们记下了
    每扇门的编号，以及这扇门背后的每一条通路所到达的门的编号。007 发现不存在两条路通向同一扇门。
    内线告诉他，情报就藏在迷宫的最深处。但是这个迷宫太大了，他需要你的帮助————请编程帮他找出距
    离入口最远的那扇门。
输入：首先在一行中给出正整数N（<100000），是门的数量。最后N行，第i行（1≤i≤N）按以下格式描述编
    号为 i 的那扇门背后能通向的门：K D[1] D[2] ... D[K]
    其中K是通道的数量，其后是每扇门的编号。
输出：在一行中输出距离入口最远的那扇门的编号。题目保证这样的结果是唯一的。
输入样例：
13
3 2 3 4
2 5 6
1 7
1 8
1 9
0
2 11 10
1 13
0
0
1 12
0
0
输出样例：
12
思路：与病毒溯源基本相同，vector<int>数组存储普通树的叶节点。但同样的写法本题有两个点超时了。
先特殊处理了一条链的情况，但还是无法解决“N/2单链表, 下端有N/2个叶子”的情况。后修改dfs函数，
使其在深搜时便记录下层数和最远的点
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> node[100010];       //存储树
bool visit[100010]={0};         //存储是否访问过
int maxdistance=0;
int ans;

void dfs(int root,int deep){
    if(node[root].size()==0){   //叶节点
        if(maxdistance<deep){
            maxdistance=deep;
            ans=root;
            return;
        }
    }
    else{
        visit[root]=1;
        for(int i=0;i<node[root].size();i++){
            dfs(node[root][i],deep+1);
        }
    }
}

int main(){
    int N;
    cin>>N;
    bool flag[100010]={0};       //判断根节点用
    // int ischain=0;
    for(int i=1;i<=N;i++){
        int K;
        cin>>K;
        // if(K!=1){
        //     ischain++;
        // }
        for(int j=0;j<K;j++){
            int num;
            cin>>num;
            node[i].push_back(num);
            flag[num]=1;
        }
    }
    int root;
    for(int i=1;i<=N;i++){
        if(flag[i]==0){         //没有节点的子节点是i
            root=i;
            break;
        }
    }
    // if(ischain==1){                //链的特殊情况
    //     while(node[root].size()){
    //         root=node[root][0];
    //     }
    //     cout<<root<<endl;
        
    //     return 0;
    // }
    ans=root;                   //对ans赋初值，否则N=1时ans没有值
    dfs(root,0);

    cout<<ans<<endl;

    return 0;
}