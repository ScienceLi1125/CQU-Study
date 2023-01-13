/*大小写字母转换
 * 课本P167 T1
 * 题目：将一个字符串中小写字母转换成大写字母，大写字母转换成小写字母
 */
package exercise;
import java.util.Scanner;

public class J12_ConvertUpperLower {
	public static char Convert(char a) {
		char c=a;						//若不是大小写字母则原样输出
		if(a>='a'&&a<='z') {
			c=(char)(a-'a'+'A');
		}
		if(a>='A'&&a<='Z') {
			c=(char)(a-'A'+'a');
		}
		return c;
	}
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		String sin=sc.next();
		StringBuffer sout=new StringBuffer();
		for(int i=0;i<sin.length();i++) {
			char a=sin.charAt(i);		//Java中字符串不支持下标访问，因此采用charAt函数
			sout.append(Convert(a));
		}
		System.out.println(sout);
		sc.close();
	}

}
