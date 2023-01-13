/*	题目：e^x的级数展开式为(^表示上标)：e^x=1+x+x^2/2!+x^3/3!+...+x^n/n!+...
 *	要求：1.编写一个函数来计算相应的值 2.在main方法内生成一个随机数x，调用自己编写的函数求值
 */
package exercise;
import java.util.*;

public class J10_CalculateE {
	public static double CalculateE(int n) {
		//生成数的范围在0~10，由e^x的展开式，n取到20时余项已经非常小了
		double power[]=new double[20];		//用数组存储幂，减少重复运算
		double factorial[]=new double[20];	//用数组存储阶乘
		power[0]=1;
		factorial[0]=1;
		double res=1;
		for(int i=1;i<20;i++) {
			power[i]=power[i-1]*n;
			factorial[i]=factorial[i-1]*(i+1);
			res+=power[i]/factorial[i];
		}
		return res;
	}
	public static void main(String args[]) {
		int ran=new Random().nextInt(10);
		System.out.println("e^"+ran+"的值是"+CalculateE(ran));
	}
}
