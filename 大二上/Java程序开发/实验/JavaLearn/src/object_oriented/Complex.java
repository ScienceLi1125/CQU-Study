/*课本P83 T3
  编写复数类Complex验证两个复数1+2i和3+4i相加产生1个新的复数4+6i。要求如下：
	1.复数类Complex的属性有:
	  RealPart:int型,代表复数的实数部分
	  ImaginPart:int型，代表复数的虚数部分
	2.复数类Complex的方法有:
	  Complex():构造函数，将复数的实部和虚部都置0。
	  Complex(int r,int i):构造函数,形参r为实部的初值,i为虚部的初值。
	  Complex complexAdd(Complex a):将当前复数对象与形参复数对象相加，所得的结果仍是一个复数值,返回给此方法的调用者。
  	  String ToString():把当前复数对象的实部、虚部组合成a+bi的字符串形式，其中a和b分别为实部和虚部的数据。
*/
package object_oriented;

public class Complex {
	int RealPart;
	int ImaginPart;
	public Complex(){
		this.RealPart=0;
		this.ImaginPart=0;
	}
	public Complex(int r,int i){
		this.RealPart=r;
		this.ImaginPart=i;
	}
	public void complexAdd(Complex a) {
		RealPart+=a.RealPart;
		ImaginPart+=a.ImaginPart;
	}
	String Tostring() {
		String s=RealPart+"+"+ImaginPart+"i";
		return s;
	}
	public static void main(String[] args) {
		Complex a=new Complex(5,2);
		Complex b=new Complex(3,1);
		a.complexAdd(b);
		System.out.println(a.Tostring());
	}

}
