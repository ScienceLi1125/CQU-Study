/*课本P126 T3
 *现有以下接口的声明:
	pub1ic interface CalcArea{
		double getArea();
	}
1.定义圆类Cirele并实现接口CalcArea,圆类的主要成员变量为半径，构造方法的参数用于初始化半径。
2.定义矩形类Rectangle并实现接口CalcArea,矩形类的主要成员变量包括长和宽，构造方法的参数用于初始化长
  和宽。
3.现有类TestArea,其功能是求存储在一个数组中的多个图形的面积之和。
 */
package object_oriented;

interface CalcArea{
	double getArea();
}
class Circle implements CalcArea{
	private double r;
	private final static double PI=3.14;
	public Circle(double r) {
		this.r=r;
	}
	public double getArea() {
		return (PI*r*r);
	}
}
class Rectangle implements CalcArea{
	private double a;
	private double b;
	public Rectangle(double a,double b) {
		this.a=a;
		this.b=b;
	}
	public double getArea() {
		return (a*b);
	}
}

public class TestArea {
	//CalcArea shapes[]不加static关键字无法传入sumArea()函数
	static CalcArea shapes[]= {new Circle(1.0),new Rectangle(3.0,4.0),new Circle(8.0)};
	public static void main(String args[]) {
		System.out.println("total area="+sumArea(shapes));
	}
	public static double sumArea(CalcArea[] shapes) {
		double areas=0;
		for(int i=0;i<shapes.length;i++) {
			areas+=shapes[i].getArea();
		}
		return areas;
	}
}
