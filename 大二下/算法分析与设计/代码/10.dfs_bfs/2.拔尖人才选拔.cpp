/*拔尖人才选拔：
题目：“立德树人”、“品学兼优”、“德才兼备”等都把品格德行放在学识才智的前面，这是新时代拔尖人才的培养
    目标。因此，Z书记决定改变过去只看绩点的方法，采用先看品行再看成绩的机制选拔计科专业拔尖学生团
    队。具体方式如下：先由辅导员对每个学生的精神状态、生活态度、平时表现等打分，按得分从高到低排序；
    然后再根据学生的学习成绩选出最优秀的一组学生。
    那么如何评价两组学生中哪组更优秀呢？假设有N位学生，按照品行评分从高到低排序，他们的学习成绩依
    次为s1,s2,...,sN。从中选出两组学生I=<si1,si2,...,siK>和J=<sj1,sj2,...,sjK>，满足1≤i1<i2<
    ...<iK<...≤N，1≤j1<j2<...<jK≤N。如果以下条件成立，I组学生比J组学生优秀，即I>J：
        1.si1>sj1, 或者
        2.任意p∈[2,K] 任意q∈[1,p?1]: siq=sjq且sip>sjp。
    （评价标准即比较两组降序排列的数列第一个不同数字的大小）
    注：显然，这种选拔方法强调小组中品行好的学生的引领示范作用。
输入：两行数据。第一行给出两个正整数N和K，用空格隔开，表示学生的总数和要从中选拔的人才数量(1<K≤N≤1000000)。
    第二行有N个整数，第i∈[1,N]个数值表示第i位学生的总成绩分数，而i表示该生的品行排名。成绩分数都
    在区间[0,2**31)以内。
输出：在一行中输出K个数据，用空格分开，表示选出的最优秀学生组的成绩，按品行从高到低排列。最后的数值
    后面没有空格。
思路：暴力搜索所有可能的学生组合再一一比较。初始思路为将所有组合压入vector<vector<int> >，但当N较
    大时内存和时间均会有较大压力，因此在生成一组学生后就与当前最优组合比较并更新最优组合
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N,K;
int score[5000];
//vector<vector<int> >group;
vector<int> stu;
vector<int> best;

bool compare(vector<int> stu1,vector<int> stu2){
    for(int i=0;i<stu1.size();i++){
        if(stu1[i]>stu2[i]){
            return 1;
        }
        else if(stu1[i]<stu2[i]){
            return 0;
        }
    }
    return 0;
}
void dfs(int tmp){                  //暴力枚举所有学生组合
    if(stu.size()==K){
        if(compare(stu,best)){      //stu>best
            best.assign(stu.begin(),stu.end());
        }
        //group.push_back(stu);
        return;
    }
    for(int i=tmp;i<N;i++){
        stu.push_back(score[i]);
        dfs(i+1);
        stu.pop_back();
    }
    
    return;
}
void VecPrint(vector<int> v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

int main(){
    cin>>N>>K;
    for(int i=0;i<N;i++){
        cin>>score[i];
    }
    for(int i=0;i<K;i++){           //best初值全赋为0，用以初次比较
        best.push_back(0);
    }
    int tmp=0;
    dfs(tmp);
    // sort(group.begin(),group.end(),compare);
    // for(int i=0;i<group.size();i++){
    //     VecPrint(group[i]);
    // }
    VecPrint(best);

    return 0;
}