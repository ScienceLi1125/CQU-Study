/*小明打字:
    小明正使用Microsoft Word打一篇文档，文档只包含a-z的小写字母和空格，在打字过程中可能会一次或多次按下Home键、End键、←方向键、→方向键、Insert键、Backspace键。请编写程序，给定小明在键盘上按键的序列，输出小明屏幕上最终显示的文本。
提示：Home键会将当前光标移至文本开始位置，End键当前光标移至文本尾，←键和→键会使当前光标左移或右移一个位置（如果光标在文档头则无法左移，光标在文档尾则无法右移），Insert键会在插入和替换文本间切换（默认是插入状态），Backspace键会删除当前光标前的一个字符。

输入格式:
输入为不超过50000个字符，表示小明的按键序列。包含a-z的小写字母、空格以及字符[、]、{、}、-、=。其中字符“[”表示Home键，“]”表示End键，“{”表示←键，“}”表示→键，“-”表示Insert键，“=”表示Backspace键。
输出格式:
输出为在小明屏幕上最终显示的文本。最后一个字母后没有回车或换行。

输入样例1:
jilin[i lofe{{-v-} ] universiti=y
输出样例1:
i love jilin university
输入样例2:
abcd[c-de
输出样例2:
cdecd
输入样例3:
[[]][][]happy=birthday
输出样例3:
happbirthday
输入样例4:
efg[bbb}}=}}}}=[{{{{a
输出样例4:
abbbe
*/

#include <iostream>
#include <list>
using namespace std;

//对list操作后迭代器会发生紊乱，不可以直接加减，要善用返回值

int main(){
    list<char> l;
    list<char>::iterator i=l.begin();
    char a;
    bool flag=1;                //用来存储insert‘-’键切换功能，flag为真表示插入，为假表示替换
    while(scanf("%c",&a)&&a!='\n'){         //cin无法读取空格&&注意终止条件
        if(a=='-'){             //flag初值为0，遇到则切换，插入与替换的状态贯穿所有操作
            if(flag==0) flag=1;             //功能切换
            else flag=0;
        }
        else if(a=='['){
            i=l.begin();
        }
        else if(a==']'){
            i=l.end();
        }
        else if(a=='{'&&i!=l.begin()){      //如果光标在文档头则无法左移
            i--;                            //没有与i-=1匹配的运算
        }
        else if(a=='}'&&i!=l.end()){
            i++;
        }
        else if(a=='='){
            if(i!=l.begin()&&!l.empty()){
                i--;
                i=l.erase(i);    //Backspace删除的是迭代器指向元素的上一个元素，因此先自减 
            } 
        }
        else if(flag){          //此时flag为真，表示插入
            i=l.insert(i,a);    //insert返回值指向插入第一个元素的迭代器
            i++;                //想在后面插入，需要将迭代器后移
        }
        else{                   //此时flag为假，表示替换
            i=l.erase(i);
            i=l.insert(i,a);
            i++;
        }
    }

    for(list<char>::iterator j=l.begin();j!=l.end();j++){
        cout<<char(*j);
    }
    
    return 0;
}