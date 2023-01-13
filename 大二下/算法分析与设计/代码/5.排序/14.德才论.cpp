/*德才论：
题目：宋代史学家司马光在《资治通鉴》中有一段著名的“德才论”：“是故才德全尽谓之圣人，才德兼亡谓之
    愚人，德胜才谓之君子，才胜德谓之小人。凡取人之术，苟不得圣人，君子而与之，与其得小人，不若
    得愚人。” 现给出一批考生的德才分数，请根据司马光的理论给出录取排名。
输入：第一行给出 3 个正整数，分别为：考生总数N（≤100000）；录取最低分数线L（≥60），即德分和才
    分均不低于L的考生才有资格被考虑录取；优先录取线H（<100），即德分和才分均不低于此线的被定义
    为“才德全尽”，此类考生按德才总分从高到低排序；才分不到但德分到线的一类考生属于“德胜才”，也
    按总分排序，但排在第一类考生之后；德才分均低于 H，但是德分不低于才分的考生属于“才德兼亡”但
    尚有“德胜才”者，按总分排序，但排在第二类考生之后；其他达到最低线L的考生也按总分排序，但排
    在第三类考生之后。
    随后N行，每行给出一位考生的信息，包括：准考证号、德分、才分，其中准考证号为8位整数，德才分
    为区间 [0, 100] 内的整数。数字间以空格分隔。
输出：第一行首先给出达到最低分数线的考生人数M，随后M行，每行按照输入格式输出一位考生的信息，考
    生按输入中说明的规则从高到低排序。当某类考生中有多人总分相同时，按其德分降序排列；若德分也
    并列，则按准考证号的升序输出。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int L,H;

class student{
private:
    string NO;
    int morality;
    int talent;
public:
    student(string no,int m,int t){
        NO=no;
        morality=m;
        talent=t;
    }
    int rank(){
        if(morality<L || talent<L){
            return 0;
        }
        else if(morality>=H && talent>=H){
            return 1;
        }
        else if(morality>=H && talent<H){
            return 2;
        }
        //else if(morality<H && talent<H && morality>talent){   //漏等号导致3个测试点错误
        else if(morality<H && talent<H && morality>=talent){
            return 3;
        }
        else{
            return 4;
        }
    }
    int scores(){
        return morality+talent;
    }
    int getmorality(){
        return morality;
    }
    string getNO(){
        return NO;
    }
    void print(){
        cout<<NO<<" "<<morality<<" "<<talent<<endl;
    }
};
bool cmp(student s1,student s2){
    if(s1.scores()!=s2.scores()){
        return s1.scores()>s2.scores();
    }
    else if(s1.getmorality()!=s2.getmorality()){
        return s1.getmorality()>s2.getmorality();
    }
    else{
        return s1.getNO()<s2.getNO();
    }
}

int main(){
    int N;
    cin>>N>>L>>H;
    int M=N;
    vector<student> v1;
    vector<student> v2;
    vector<student> v3;
    vector<student> v4;
    for(int i=0;i<N;i++){
        string no;
        int mor;
        int tal;
        cin>>no>>mor>>tal;
        student s(no,mor,tal);
        if(s.rank()==0){
            M--;
        }
        else if(s.rank()==1){
            v1.push_back(s);
        }
        else if(s.rank()==2){
            v2.push_back(s);
        }
        else if(s.rank()==3){
            v3.push_back(s);
        }
        else if(s.rank()==4){
            v4.push_back(s);
        }
    }
    sort(v1.begin(),v1.end(),cmp);
    sort(v2.begin(),v2.end(),cmp);
    sort(v3.begin(),v3.end(),cmp);
    sort(v4.begin(),v4.end(),cmp);

    cout<<M<<endl;
    for(int i=0;i<v1.size();i++){
        v1[i].print();
    }
    for(int i=0;i<v2.size();i++){
        v2[i].print();
    }
    for(int i=0;i<v3.size();i++){
        v3[i].print();
    }
    for(int i=0;i<v4.size();i++){
        v4[i].print();
    }

    return 0;

} 