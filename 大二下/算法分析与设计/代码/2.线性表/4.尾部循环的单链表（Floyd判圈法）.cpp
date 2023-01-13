/*尾部循环的单链表：
题目：有长度为N的单链表Node* head, 其尾部节点的next指针不为NULL，而是指向链表的某个节点，
    构成循环结构。本题要求查找尾部节点所指的循环节点，输出其位置。
    函数接口定义：int find_cycling_position ( Node* head );其中head不为空，指向单链表的头结点。
    单链表长度N (1≤N≤2000000)。函数返回循环节点位置K (1≤K≤N)，比如K=1，表示头结点为循环节点。
思路：Floyd判圈算法
    Floyd龟兔算法是一种指针算法。该算法仅使用移动速度不同的两个指针就能检测出是否有环。Floyd龟兔
    算法解决以下问题：1.检测是否有环 2.环的起点节点 3.环的长度。
    1.检测是否有环。
        想象在一个环形跑道上跑步，两个人同时出发，出发以后速度快的人终究会在某一点和速度慢的人相
        遇。一般这个时候相遇，速度快的人比速度慢的人至少多跑一圈。我们假设链表的开始节点是S，环
        上的起始节点是P，第一次相遇的节点是M。S和P的距离是p，从P和M的距离是m,从M到p的距离是n。
        指针t和h初始状态下都指向S。接着t每次只有1步，h每次走2步。只要二者没有相遇，就一直按着这
        个速度走下去。当h无法前进（到达队列末尾）的时候，可以判断没有环。如果t和h在某点再次相遇，
        则确定有环。
    2 计算环长度
        当t和h相遇在M点。因为相遇的点一定在环上。这时候保存h不动，t按之前的速度继续前进，直到和
        h再次相遇，这个过程中移动的步数就是环的长度。
    3 环的起始节点确定
        在确定是否有环的过程中，h走的距离是t走的距离的2倍。设c为环长。t走的距离s1=p+m+a*c，
        h走的距离是2*s1=p+m+b*c,两式子相减得到：s1=(b-a)*c，又s1=p+m+a*c,所以p+m=环的整数倍。
        为了找到环的起点，t回到起点，h在当前位置。以相同速度同时向前，他们再次相遇一定在P点。
        为什么呢？因为从S到P的距离是p，从P到M的距离是m，因为m+p是环长的整数倍，即p+m=kc，所以
        p=c-m+(k-1)c，所以当h走过距离p到达P的时候，t走过了(k-1)圈+c-m，也一定达到了P点。
*/
#include <iostream>
#include <string.h>
using namespace std;

class Node{
public:
    Node* next;    
    Node(Node* p=NULL){
        next = p;
    }
};

int find_cycling_position(Node* head){
    Node*rabbit,*turtle;
    int cnt=1;                          //记录结点位置
    rabbit=turtle=head;                 //从起点出发
    while(true) {
        rabbit=(rabbit->next)->next;    //兔子走两步 
        turtle=turtle->next;            //乌龟走一步 
        if(rabbit==turtle){
            break;                      //此时相遇
        }
    }
    /*//执行此代码可得环的长度
    rabbit=rabbit->next;
    int circle=1;
    while(rabbit!=turtle){
        rabbit=rabbit->next;
        circle+=1;
    }
    return circle;
    */
    rabbit=head;                        //兔子回到起点 
    while(rabbit!=turtle){
        rabbit=rabbit->next;            //这次速度相同 
        turtle=turtle->next;
        cnt++; 
    }
    return cnt; 
}

int main(int argc, const char * argv[]) {
    int N, K;
    cin >> N >> K;    
    Node* head = new Node();
    Node* tail = head;

    for(int n=1; n<N; n++){
        head = new Node(head);          //head后面不断加入新结点，head时刻处于链表头
    }
    Node* curr = head;
    for(int k=1; k<K; k++){
        curr = curr->next;              //curr不断从head向后移动，最终达到链表尾部
    }
    tail->next = curr;

    cout << find_cycling_position(head) << endl;

    return 0;
}
