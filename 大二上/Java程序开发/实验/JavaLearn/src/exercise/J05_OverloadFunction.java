package exercise;

public class J05_OverloadFunction {
	public static void main(String args[]) {
		System.out.println(Add(5.6,8));
	}
	public static int Add(int a,int b) {
		return a+b;
	}
	public static int Add(int a,int b,int c) {
		return a+b+c;
	}
	public static double Add(double a,double b) {
		return a+b;
	}
}
