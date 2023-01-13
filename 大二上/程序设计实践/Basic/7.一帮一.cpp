/*一帮一：
题目：“一帮一学习小组”是中小学中常见的学习组织方式，老师把学习成绩靠前的学生跟学习成绩靠后的学生排在一组。本题就请你编写程序帮助老师自动完成这个分配工作，即在得到全班学生的排名后，在当前尚未分组的学生中，将名次最靠前的学生与名次最靠后的异性学生分为一组。
输入：第一行给出正偶数N（≤50），即全班学生的人数。此后N行，按照名次从高到低的顺序给出每个学生的性别（0代表女生，1代表男生）和姓名（不超过8个英文字母的非空字符串），其间以1个空格分隔。
	这里保证本班男女比例是1:1，并且没有并列名次。
输出：每行输出一组两个学生的姓名，其间以1个空格分隔。名次高的学生在前，名次低的学生在后。小组的输出顺序按照前面学生的名次从高到低排列。
*/
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N;
	cin >> N;
	vector<string> boy;			//vector内可以存储string，注意与后面填入数据类型一致
	vector<string> girl;
	vector<string> student;
	for(int i=0;i<N;i++){
		int num;
		string name;
		cin >> num >> name;
		student.push_back(name);	//student为了记输入顺序
		if(num==1){
			boy.push_back(name);
		}
		else{
			girl.push_back(name);
		}
	}
	int num1=N/2-1,num2=N/2-1;		//num1,num2用来记boy,girl倒序坐标					
	for(int i=0;i<N/2;i++){			//(为避免N/2中男女人数不对等)
		bool flag=false;			//用bool值判断
		for(int j=0;j<N/2;j++){
			if(student[i]==boy[j]){	//判断该学生性别
				flag=true;
				break;
			}
		}
		cout<<student[i]<<" ";
		if(flag){
			cout<<girl[num2]<<endl;
			num2-=1;			//每输出一位下标前移
		}
		else{
			cout<<boy[num1]<<endl;
			num1-=1;
		}
	}


	return 0;
}