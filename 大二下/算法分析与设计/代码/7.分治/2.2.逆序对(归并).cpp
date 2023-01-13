/*逆序对:
思路：采用分治思想计算逆序对，将数组分成两份，这样所有的逆序对由三部分组成：
    1.前半部分的逆序对；2.后半部分的逆序对；3.前后两部分之间的逆序对
*/
#include<iostream>
using namespace std;

int arr[100001]={0};      
int tmp[100001]={0};            //b[]为归并过程中用到的中间数组 
long long cnt;                  //记录逆序对数

/*求左右两个数组之间的逆序对：因为在归并的过程中会先计数后排序，所以在每个Merge函数开头，l~m、
m~r两个数组都是升序的，所以比较两个数组开头元素a，b，若为逆序则right数组开头下标后移，并且a后的
元素都与b构成逆序；若a、b不为逆序则a赋值为后一个元素
*/
void Merge(int l,int m,int r){
	int i=l;                    //左边数组初始点
	int j=m+1;                  //右边数组初始点
	int pos=l;                  //tmp初始下标位置
	while(i<=m && j<=r){
        if(arr[i]>arr[j]){      //构成逆序
    	    tmp[pos++]=arr[j++];
    	    cnt+=m-i+1;         //a后所有元素与b均构成逆序
        }
        else{
            tmp[pos++]=arr[i++];
        }
	}
	while(i<=m){
        tmp[pos++]=arr[i++];
    }
	while(j<=r){
        tmp[pos++]=arr[j++];
    }
	for(int i=l;i<=r;i++){       //更新arr为排序后的数组
        arr[i]=tmp[i];
    }
}
void ReverseOrderPair(int left,int right){
	if(left<right){
		int mid=(left+right)/2;
		ReverseOrderPair(left,mid);     //前半部分的逆序对
		ReverseOrderPair(mid+1,right);  //后半部分的逆序对
		Merge(left,mid,right);          //前后两部分之间的逆序对
	}
    return;
}

int main(){
	int N;
	cin>>N;
	for(int i=1;i<=N;i++){
		cin>>arr[i];
	}
	ReverseOrderPair(1,N);
	cout<<cnt<<endl;

	return 0;
}