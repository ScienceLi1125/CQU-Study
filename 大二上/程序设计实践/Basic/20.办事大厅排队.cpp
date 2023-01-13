/*办事大厅排队：
题目：在郑州大学综合办事大厅，每天陆陆续续有很多人来排队办事。现在你能否写程序帮助老师时刻了解当前办理业务的情况。
输入:第一行一个数字N，表示排队信息或者查询信息条目的数量。以下N行，每行的内容有以下3种情况：
    (1)in name 表示名字为name的人员新来到办事大厅，排在队伍的最后。（in和name间存在一个空格，name是名字对应字符串，长度不超过10）。
    (2)out 表示当前排在最前面的人已经办理完业务，离开了。
    (3)q 表示一次查询，请输出当前正在办理业务的人，也就是队伍的第1个人。如果当前无人办理业务，则输出“NULL”，不包括引号。
输出:请根据以上信息，每次遇到查询时，对应一行输出。如果这时队伍有人，则输出第一个人的姓名，否则
    输出NULL。
*/
#include <iostream>
#include <list>
using namespace std;

int main(){
    int N;
    cin>>N;
    string s;
    string name;
    list<string> ls;
    for(int i=0;i<N;i++){
        cin>>s; 
        if(s=="in"){        //若s为“in A”，利用cin无法读取空格自动分割
            cin>>name;      //不整体读取
            ls.push_back(name);
        }
        else if(s=="out"){
            ls.pop_front();
        }
        else if(s=="q"){
            if(!ls.empty()){
                cout<<ls.front()<<endl;
            }
            else{
                cout<<"NULL"<<endl;
            }
        }
        
    }


    return 0;
}