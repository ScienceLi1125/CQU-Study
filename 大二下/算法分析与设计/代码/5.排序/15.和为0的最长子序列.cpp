/*和为0的最长子序列：
题目：给定一个数组A[n]，输出其和为0的最长子序列
思路：
    法一：暴力搜索，O(n**2)
    法二：分治法，O(nlogn)
    选取数组最中间元素作为基准，递归该元素左边的和为0的最长子序列长度L，右边的和为0的最长子序列
长度R，再获得横跨中间元素的和为0的最长子序列长度M，比较L,M,R输出最大值即可
    因此获得横跨中间元素的和为0的最长子序列长度即为重点。可以用两个数组LS[],RS[]描述从中间到
两边的数组，下标表示子数组长度，值表示子数组的和，当LS[i]+RS[j]=0时即为一个解。但此时不能直接
搜索，否则复杂度还是O(n**2)。利用计数排序的思想，用数组B[]记录LS[]的反向数组，即和为i的左子序
列的长度为B[i]，再遍历右子序列（i从0到RS.length），如果B[-RS[i]]>0，则表示B[-RS[i]]+i为一
个解，和M大小比较即可。
注意：下标为负的下标可以整体平移
*/
#include <iostream>
using namespace std;

int max(int a,int b,int c){
    if(a>b){
        if(a>c) return a;
        else    return c;
    }
    else{
        if(b>c) return b;
        else    return c;
    }
}
int Middle(int A[],int l,int m,int r){
    int LS[100]={0};
    int RS[100]={0};
    for(int i=1;i<=m-l;i++){
        LS[i]=LS[i-1]+A[m-i+1];
    }
}

int LongestZeroSum(int A[],int l,int r){
    if(l==r){
        if(A[l]=0)  return 1;
        else        return 0;
    }
    int mid=(l+r)/2;
    int L=LongestZeroSum(A,l,mid);
    int R=LongestZeroSum(A,mid+1,r);
    int M=Middle(A,l,mid,r);

    return max(L,M,R);
}

int main(){
    
    
    return 0;
}
