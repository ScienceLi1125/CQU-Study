/*class前不加public修饰，则可以将CA,CB写入同一个class文件，但不是包含main函数的类*/
package object_oriented;
class CA{
	String s="class CA";
	void callme() {
		System.out.println("inside A");
	}
}
class CB extends CA{
	String s="class CB";
	void callme() {
		System.out.println("inside B");
	}
}

public class TestInheritance {
	public static void main(String args[]) {
		CA a=new CA();
		CB b=new CB();
		CA c=new CB();
		System.out.println(a.s);
		a.callme();
		System.out.println(b.s);
		b.callme();
		System.out.println(c.s);
		c.callme();
		/*成员变量和方法的调用方式不同，CA c=new CB()中c的类型是CA，但存储的是CB的实例，调用成员
		  变量时调用的是父类，调用方法时调用的是主类
		*/
	}
}
