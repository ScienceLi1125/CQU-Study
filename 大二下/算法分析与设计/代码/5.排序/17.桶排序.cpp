#include <iostream>
#include <cmath>
using namespace std;

void inssort(int A[],int n){
    for(int i=1;i<n;i++){
        for(int j=i;j>0;j--){
            if(A[j]<A[j-1]){
            	int tmp=A[j];
            	A[j]=A[j-1];
            	A[j-1]=tmp;
            }
            else{
                break;
            }
        }
    }
}

void bucketSort(int A[],int n,int numBuckets){
    //创建桶
    int buckets[numBuckets][n]; 	//二维数组，每行表示一个桶
    int bucketSizes[numBuckets]; 	//每个桶中元素的数量
    //初始化桶的大小
    for(int i=0;i<numBuckets;i++){
        bucketSizes[i]=0;
    }
    //确定数组元素范围
	int maxA=-999,minA=999;
	for(int i=0;i<n;i++){
		if(A[i]>maxA)	maxA=A[i];
		if(A[i]<minA)	minA=A[i];
	} 
    //将元素放入桶中
    for(int i=0;i<n;i++){
    	int bucketGap=ceil((maxA-minA)/(float)numBuckets);
        int bucketIndex=(A[i]-minA)/bucketGap;
        buckets[bucketIndex][bucketSizes[bucketIndex]++]=A[i];
    }
    //对每个桶中的元素进行插入排序
    for(int i=0;i<numBuckets;i++){
        inssort(buckets[i],bucketSizes[i]);
    }
    // 合并桶中的元素
    int index=0;
    for(int i=0;i<numBuckets;i++){
        for(int j=0;j<bucketSizes[i];j++){
            A[index++]=buckets[i][j];
        }
    }
}

int main() {
    int A[]={29,25,3,49,9,37,21,43};
    int n=sizeof(A)/sizeof(A[0]);
    int numBuckets=5;
    bucketSort(A, n, numBuckets);

    printf("Sorted array: ");
    for(int i=0;i<n;i++){
        printf("%d ",A[i]);
    }

    return 0;
}

