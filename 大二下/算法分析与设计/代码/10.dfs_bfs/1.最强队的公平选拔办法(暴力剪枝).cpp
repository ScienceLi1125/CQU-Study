/*最强队公平的选择办法
题目：程序设计竞赛的参赛队伍通常由3人组成。G队长从PTA下载了计算机专业全体学生的刷题成绩，想从中选
    出三名学生组成一支最强队伍。成绩单只列出了每位学生的学号和成绩，按学号从小到大排列。显然，最简
    单的方法是直接找出成绩排名前三的学生，但选出的学生可能集中在个别班级里，对其他班级有失公平；较
    公平的方法是先从每个班选成绩最好的，再从中筛选三人，但必须知道分班的情况。队长思索了半响，突然
    想到虽然每个班级的学生人数有出入，但上限是固定的，并且同一个教学班的学生其学号是连续编号的，由
    此设计出一个既公平（每个班最多选1人）又便利（不用分班）的最强队伍选择方法。
输入：两行数据，第一行给出两个正整数N和K，表示学生总人数和班级人数上限，满足2K<N≤100000(至少有三个
    班）。接下来一行给出N个正整数，用空格分开，依次表示从学号0到学号N-1的学生成绩。末尾的成绩后面
    没有空格。所有成绩值都在区间[1,100000]以内。
输出：两行数据。第一行给出选出的最强队伍的总成绩；第二行给出组队的三名学生的学号a b c，满足 b-a≥K
    ∧c-b≥K。数值间用空格分开，末尾不留空格。如果最强队伍有多组，输出学号序列字典序最小的队伍。
思路：暴力搜索
注意：score数组开到100000，否则段错误
      回溯+剪枝，否则超时
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N,K;
int Max=0;                          //score中最大值
int Point=0;
int score[100000];
vector<int> stu;
vector<int> best;

void dfs(int tmp){
    if(stu.size()==3){
        int n1=0;
        for(int i=0;i<3;i++){
            n1+=score[stu[i]];
        }
        if(n1>Point){               //stu>best
            best.assign(stu.begin(),stu.end());
            Point=n1;
        }
        return;
    }
    for(int i=tmp;i<N;i++){
        stu.push_back(i);
        int n2=0;
        for(int j=0;j<stu.size();j++){
            n2+=score[stu[j]];
        }
        //剪枝核心步骤
        if(n2+Max*(3-stu.size())>Point){    //最乐观情况也无法满足的话，则放弃搜索，不再递归
            dfs(i+K);
        }
        stu.pop_back();
    }
    return;
}
void VecPrint(vector<int> &v){
    cout<<v[0];
    for(int i=1;i<v.size();i++){
        cout<<" "<<v[i];
    }
    cout<<endl;
}

int main(){
    cin>>N>>K;
    for(int i=0;i<N;i++){
        cin>>score[i];
        if(Max<score[i]){
            Max=score[i];
        }
    }
    dfs(0);
    cout<<Point<<endl;
    VecPrint(best);

    return 0;
}
