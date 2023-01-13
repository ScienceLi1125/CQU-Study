/*出生年：
题目：新浪微博中一奇葩贴：“我出生于1988年，直到25岁才遇到4个数字都不相同的年份。”也就是说，直到2013年才达到“4个数字都不相同”的要求。本题请你根据要求，自动填充“我出生于y年，直到x岁才遇到n个数字都不相同的年份”这句话。
输入：在一行中给出出生年份y和目标年份中不同数字的个数n，其中y在[1, 3000]之间，n可以是2、3、4。
    注意不足4位的年份要在前面补零，例如公元1年被认为是0001年，有2个不同的数字0和1。
输出格式：根据输入，输出x和能达到要求的年份。数字间以1个空格分隔，行首尾不得有多余空格。年份要按4位输出。
        注意：所谓“n个数字都不相同”是指不同的数字正好是n个。如“2013”被视为满足“4位数字都不同”的条件，但不被视为满足2位或3位数字不同的条件。
*/
#include <iostream>
#include <vector>
using namespace std;

int count(int m){               //定义函数计算数字中各位数字重复情况，m为年份
    int num[10]={0};
    for(int i=0;i<4;i++){       //指定循环4次，若不足前面自动补零！！！（如13则构造成0013）
		num[m%10]++;        //出生在0001年也满足2位数字不一样
		m/=10;
	}
    int p=0;                    //p用来记非零数位的个数
    for(int j=0;j<10;j++){      //直接记非零次数，不能只记出现最多的次数
        if(num[j]!=0)           //否则2200这种同时有两个最多次数会超出预期
            p++;
    }
    return p;
}

int main(){
    int y,n;
    cin >>y>>n;
    int tmp=0,result;           //tmp用来记出生到现在的年数,result表示现在的年份
    for(int i=y;i<3334;i++){    //题中y在0到3000之间，所以取3333作为终止条件
        if(count(i)==n){       
            result=i;           
            break;
        }
        tmp+=1;
    }
    printf("%d %04d",tmp,result);//妙用printf补零

    return 0;
}

/*也可以用setw和setfill巧妙补零
#include<iostream>
#include<set>
#include<sstream>
#include<iomanip>
using namespace std;

int judge(int y) {
    string year;
    stringstream ss;
    ss<<setw(4)<<setfill('0')<<y;
    ss>>year;
    set<char> number;
    for(int i=0;i<4;i++) {
        number.insert(year[i]);
    }
    return number.size();
}

int main() {
    int year,n;
    cin>>year>>n;
    int age=0;
    while(judge(year)!=n) {
        year++;
        age++;
    }
    cout<<age<<' ';
    printf("%04d",year);
    cout<<endl;
    return 0;
}
*/