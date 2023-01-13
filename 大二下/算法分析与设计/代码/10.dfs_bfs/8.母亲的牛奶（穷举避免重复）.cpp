/*母亲的牛奶:
题目：农民约翰有三个容量分别是A,B,C升的桶，A,B,C分别是三个从1到20的整数。
    最初，A和B桶都是空的，而C桶是装满牛奶的。农民可以把牛奶从一个桶倒到另一个桶中，直到被灌桶装满或原桶空了。
    当然每一次灌注都是完全的。由于节约，牛奶不会有丢失。 
    写一个程序去帮助农民找出当A桶是空的时候，C桶中牛奶所剩量的所有可能性。
输入：A,B,C
输出：升序地列出当A桶是空的时候，C桶牛奶所剩量的所有可能性。
思路：枚举所有情况，每步只有6种倒法，深搜即可
    关键在于判断深搜是否重复，避免无限循环操作
*/
#include <iostream>
#include <vector>
using namespace std;

int A,B,C;
bool ans[100]={0};              //ans[i]=true表示C中所有可能的结果
bool vis[100][100][100]={0};    //存储(a,b,c)的存储情况，避免重复搜索

void dfs(int a,int b,int c){    //A，B，C3个杯中当前的牛奶量
	if(vis[a][b][c]){           //已经搜索过(a,b,c)，直接返回上一级
		return;
	}
	vis[a][b][c] = true;        //标记搜索过(a,b,c)
	
	if(a==0 && !ans[c]){
		ans[c] = true;          //找到结果
	}
//A向B倒	
	if(a >= B-b){               //B被倒满，A倒不完 
		dfs(a-B+b,B,c);
	}else{                      //A中的牛奶可以全部倒进B中
		dfs(0,b+a,c);
	}
//B向A倒
	if(b >= A-a){
		dfs(A,b-A+a,c); 
	}else{
		dfs(a+b,0,c); 
	}
//A向C倒
	if(a >= C-c){
		dfs(a-C+c,b,C);
	}else{
		dfs(0,b,a+c);
	}
//C向A倒
	if(c >= A-a){
		dfs(A,b,c-A+a); 
	}else{
		dfs(a+c,b,0); 
	}
//B向C倒
	if(b >= C-c){
		dfs(a,b-C+c,C);
	}else{
		dfs(a,0,b+c);
	}
//C向B倒
	if(c >= B-b){
		dfs(a,B,c-B+b); 
	}else{
		dfs(a,b+c,0); 
	}
	return;
}


int main(){
    cin>>A>>B>>C;
    dfs(0,0,C);                 //初值状态A和B桶都是空的，C桶是满的
    for(int i=1;i<=C;i++){      //C桶的牛奶量不会超过其容量
    	if(ans[i]){
    		cout<<i<<" ";       //实现升序输出
    	}
    }
    
    return 0;
}