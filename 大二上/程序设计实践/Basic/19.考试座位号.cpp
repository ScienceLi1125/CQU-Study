/*考试座位号：
题目：每个PAT考生在参加考试时都会被分配两个座位号，一个是试机座位，一个是考试座位。正常情况下，考生在入场时先得到试机座位号码，入座进入试机状态后，系统会显示该考生的考试座位号码，考试时考生需要换到考试座位就座。但有些考生迟到了，试机已经结束，他们只能拿着领到的试机座位号码求助于你，从后台查出他们的考试座位号码。
输入：第一行给出一个正整数 N（≤1000），随后N行，每行给出一个考生的信息：准考证号 试机座位号 考试座位号。其中准考证号由16位数字组成，座位从1到N编号。输入保证每个人的准考证号都不同，并且任何时候都不会把两个人分配到同一个座位上。考生信息之后，给出一个正整数M（≤N），随后一行中给出M个待查询的试机座位号码，以空格分隔。
输出：对应每个需要查询的试机座位号码，在一行中输出对应考生的准考证号和考试座位号码，中间用1个空格分隔。
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Student{
    string iden;        	//准考证号identity，试机号pilot，考试号exam
    int pil,exa;        	//用整形方便后面比较
};

int main(){
    int N;
    cin>>N;
    Student S[1000];
    for(int i=0;i<N;i++){
        cin>>S[i].iden;
        cin>>S[i].pil;
        cin>>S[i].exa;
    }
    int M;
    cin>>M;
    for(int i=0;i<M;i++){
        int n;               	//n为待查询考生座位号
        cin>>n;
        for(int j=0;j<N;j++){ //不能直接sort后输出S[n]因为给出样例有可能试机号不连续
            if(S[j].pil==n){
                cout<<S[j].iden<<" "<<S[j].exa<<endl;
            }
        }

    }
    
    return 0;
}