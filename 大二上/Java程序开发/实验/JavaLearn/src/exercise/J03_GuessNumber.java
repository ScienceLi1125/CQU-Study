package exercise;

import java.util.Random;
import java.util.Scanner;

public class J03_GuessNumber {
	public static void main(String args[]) {
		int randomnum=new Random().nextInt(10);	//生成随机数
		System.out.println("-----请输入猜的数字-----");
		Scanner sc=new Scanner(System.in);		//从键盘接收数据
		int enternum=sc.nextInt();				//接收的数据赋给enternum
		while(enternum!=randomnum) {
			if(enternum>randomnum) {
				System.out.println("猜大了");
			}
			else {
				System.out.println("猜小了");
			}
			System.out.println("-----请输入猜的数字-----");
			enternum=sc.nextInt();	
		}
		System.out.println("恭喜你，答对了");
		sc.close();								//关闭输入端口
	}
}
