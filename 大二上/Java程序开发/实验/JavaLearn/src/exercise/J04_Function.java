package exercise;

public class J04_Function {
	public static void main(String args[]) {
		printRectangle(5,3);
		System.out.println(getArea(6,8));
	}
	public static void printRectangle(int length,int width) {
		for(int i=0;i<width;i++) {
			for(int j=0;j<length;j++) {
				System.out.print("*");
			}
			System.out.print("\n");
		}
	}
	public static int getArea(int x,int y) {
		return x*y;
	}
}
