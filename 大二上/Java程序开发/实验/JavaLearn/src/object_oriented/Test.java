package object_oriented;

public class Test {
	static class A{
		int a=1;
		void call() {
			System.out.println("inside A");
		}
	}
	static class B extends A{
		int a=2;
		void call() {
			System.out.println("inside B");
		}
	}
	public static void main(String args[]) {
		A a=new A();
		A b=new B();
		System.out.println(a.a);
		System.out.println(b.a);
		a.call();
		b.call();
	}
}
