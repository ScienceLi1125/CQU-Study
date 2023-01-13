/*题目：编写冒泡排序算法
1 把算法写成函数，返回排好序的数组
2 编写另一函数，生成30到50个个数不确定的随机数，每一个数在0到100之间，返回此数组
2 在main方法里
   调用随机数生成函数
   调用排序函数
   打印排好序的数，每行10个数，数之间用制表符来对齐
 */
package exercise;
import java.util.*;

public class J11_BubbleSort {
	public static int[] ProRan() {
		int len=new Random().nextInt(20)+30;	//生成30到50的任意数作为数组长度
		int res[]=new int[len];
		for(int i=0;i<len;i++) {
			int tmp=new Random().nextInt(100);
			res[i]=tmp;
		}
		return res;
	}
	public static int[] BubbleSort(int[] a) {
		for(int i=0;i<a.length-1;i++) {
			for(int j=0;j<a.length-1-i;j++) {
				if(a[j]>a[j+1]) {
					int tmp=a[j];
					a[j]=a[j+1];
					a[j+1]=tmp;
				}
			}
		}
		return a;
	}
	public static void main(String[] args) {
		int a[]=ProRan();					//a为随机数的数组
		int b[]=BubbleSort(a);				//b为排好序的数组
		for(int i=0;i<b.length;i++) {
			if(i!=0 && i%10==0) {
				System.out.println();
			}
			System.out.print(b[i]+"\t");
		}
	}

}
