//随机点名器
package exercise;
import java.util.Random;
import java.util.Scanner;
public class J08_RandomRollCall {
	public static void main(String[] args) {
		String student[]=new String[5];
		Scanner sc=new Scanner(System.in);
		for(int i=1;i<=student.length;i++) {
			System.out.println("请输入第"+i+"个同学姓名:");
			student[i-1]=sc.next();
		}
		int index=new Random().nextInt(student.length);
		System.out.print("----随机点名器----\n被点到名的同学是："+student[index]);
		sc.close();
	}
}
