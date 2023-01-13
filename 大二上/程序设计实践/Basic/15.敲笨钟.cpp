/*敲笨钟：
题目：微博上有个自称“大笨钟V”的家伙，每天敲钟催促码农们爱惜身体早点睡觉。为了增加敲钟的趣味性，还会糟改几句古诗词。其糟改的方法为：去网上搜寻压“ong”韵的古诗词，把句尾的三个字换成“敲笨钟”。例如唐代诗人李贺有名句曰：“寻章摘句老雕虫，晓月当帘挂玉弓”，其中“虫”（chong）和“弓”（gong）都压了“ong”韵。于是这句诗就被糟改为“寻章摘句老雕虫，晓月当帘敲笨钟”。
    现在给你一大堆古诗词句，要求你写个程序自动将压“ong”韵的句子糟改成“敲笨钟”。
输入：输入首先在第一行给出一个不超过 20 的正整数 N。随后 N 行，每行用汉语拼音给出一句古诗词，分上下两半句，用逗号 , 分隔，句号 . 结尾。相邻两字的拼音之间用一个空格分隔。题目保证每个字
    的拼音不超过 6 个字符，每行字符的总长度不超过 100，并且下半句诗至少有 3 个字。
输出：对每一行诗句，判断其是否压“ong”韵。即上下两句末尾的字都是“ong”结尾。如果是压此韵的，就按题面方法糟改之后输出，输出格式同输入；否则输出 Skipped，即跳过此句。
*/
#include <iostream>
#include <string>
using namespace std;

void ong(string s){
    int tmp1;                        	//tmp1用来记录“，”出现位置
    for(int i=0;i<s.length();i++){
        if(s[i]==','){             		//字符串的每一位是字符，要用单引号，否则无法比较
            tmp1=i;                  
            break;
        }
    }

    string rythem1="";
    rythem1.push_back(s[tmp1-3]);
    rythem1.push_back(s[tmp1-2]);
    rythem1.push_back(s[tmp1-1]);
    string rythem2="";
    rythem2.push_back(s[s.length()-4]); 	//s末尾为s[s.length()-1]
    rythem2.push_back(s[s.length()-3]);
    rythem2.push_back(s[s.length()-2]);

    int tmp2;                       	//tmp2用来存储倒数第三个拼音位置
    int tmp3=0;                     	//tmp3用来计数下面循环“ ”出现次数
    for(int i=s.length()-1;i>0;i--){
        if(s[i]==' '){
            tmp3+=1;
        }
        if(tmp3==3){
            tmp2=i+1;
            break;
        }
    }

    if(rythem1=="ong"&&rythem2=="ong"){
        for(int i=0;i<tmp2;i++){
            cout<<s[i];
        }
        cout<<"qiao ben zhong."<<endl;
    }
    else{
        cout<<"Skipped"<<endl;
    }
}


int main()
{
    int N;
    cin>>N;
    getchar();                      	//吸收回车
    for(int i=0;i<N;i++){           	//54行的getline为读取整行
        string s;                   	//若无getchar，则第一个getline的是N
        getline(cin,s);             	//s中包含空格，不能直接cin
        ong(s);
    }

    return 0;
}
