/*输出学生成绩：
题目：本题要求编写程序，根据输入学生的成绩，统计并输出学生的平均成绩、最高成绩和最低成绩。
    建议使用动态内存分配来实现。
输入：第一行首先给出一个正整数N，表示学生的个数。接下来一行给出N个学生的成绩，数字间以空格分隔。
输出：按照以下格式：
    average = 平均成绩
    max = 最高成绩
    min = 最低成绩
*/
#include <iostream>
using namespace std;

int main(){
    int N;
    cin>>N;
    float *arr = (float*)malloc(N*sizeof(int));
    float *ptr = arr;
    float max=0.00,min=100.00,sum=0.00;
    for(int i=0;i<N;i++){
        int n;
        cin>>n;
        *ptr=n;
        sum+=*ptr;
        if(*ptr>max){
            max=*ptr;
        }
        if(*ptr<min){
            min=*ptr;
        }
        ptr++;
    }
    float average=sum/N;
    printf("average = %.2f\nmax = %.2f\nmin = %.2f\n",average,max,min);

    free(arr);
    arr=NULL;               //释放动态数组
    return 0;
}