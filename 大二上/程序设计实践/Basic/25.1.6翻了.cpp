/*6翻了：
题目：“666”是一种网络用语，大概是表示某人很厉害、我们很佩服的意思。最近又衍生出另一个数字“9”，意思是“6翻了”，实在太厉害的意思。如果你以为这就是厉害的最高境界，那就错啦————目前的最高境界是数字“27”，因为这是 3 个 “9”！
    本题就请你编写程序，将那些过时的、只会用一连串“6666……6”表达仰慕的句子，翻译成最新的高级表达。
输入：在一行中给出一句话，即一个非空字符串，由不超过 1000 个英文字母、数字和空格组成，以回车结束。
输出：从左到右扫描输入的句子：如果句子中有超过 3 个连续的 6，则将这串连续的 6 替换成 9；但如果有超过 9 个连续的 6，则将这串连续的 6 替换成 27。其他内容不受影响，原样输出。
*/
// #include <iostream>
// #include <string>
// using namespace std;

// int main(){
//     string s;
//     int i=0;                    //i用来记输出次数，即表示前面是否有输出
//     while(cin>>s){
//         if(i!=0){
//             cout<<" ";          //巧妙解决空格问题
//         }
//         bool flag=true;         //flag用来存储每个单词是否为6的叠加
//         int tmp=0;              //tmp用来存储6的数量
//         for(int i=0;i<s.length();i++){
//             if(s[i]=='6'){
//                 tmp+=1;
//             }
//             else{
//                 flag=false;
//                 break;
//             }
//         }
//         if(!flag||tmp<=3){
//             cout<<s;
//         }
//         else if(tmp>3&&tmp<=9){
//             cout<<9;
//         }
//         else{
//             cout<<27;
//         }
//         i+=1;
//     }
    
//     return 0;
// }
//上述方法较为简单，思路可取，适用于规范输出，每个单词间只空一格
//可是一旦输入一句话中包含不规则空格，便会出现格式错误

#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    getline(cin,s);
    int cnt=0;                      //计数6的个数
    for(int i=0;i<s.length();i++){
        if(i==s.length()-1){          //结束前不好判断，单独拿出
            if(s[i]=='6'){
                cnt++;
                if(cnt>0&&cnt<=3){
                    for(int j=0;j<cnt;j++){
                        cout<<6;  
                    }
                    cnt=0;
                }    
                else if(cnt>3&&cnt<=9){
                    cout<<9;
                    cnt=0;
                }
                else if(cnt>9){
                    cout<<27;
                    cnt=0;
                }
            }
            else{
                cout<<s[i];
            }
            break;                  //执行到最后一个，结束即可break
        }
        if(s[i]=='6'){
            cnt++;
        }
        else{                       //隐含判断s[i]!='6'，计数中断
            if(cnt>0&&cnt<=3){      //存在6
                for(int j=0;j<cnt;j++){
                    cout<<6;        
                }
                cnt=0;              //要待上一个循环结束才可以归零
            }    
            else if(cnt>3&&cnt<=9){
                cout<<9;
                cnt=0;              //输出后cnt要归零
            }
            else if(cnt>9){
                cout<<27;
                cnt=0;
            }
            cout<<s[i];             //先输完666......再输当前单词
        }
    }

    return 0;
}