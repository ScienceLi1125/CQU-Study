/*键盘录入5个学生信息（姓名，语文成绩，数学成绩，英语成绩）。将他们按总分高低排序存入TreeSet*/
package exercise;
import java.util.TreeSet;
import java.util.Scanner;
import java.util.Comparator;

public class J17_SchoolReport2 {
	 static class Student{
		String name;
		int Chinese;
		int Math;
		int English;
		Student(String n,int c,int m,int e){
			this.name=n;
			this.Chinese=c;
			this.Math=m;
			this.English=e;
		}
		int getSum() {
			return Chinese+Math+English;
		}
	}
	public static void main(String[] args) {
		/*TreeSet中自动排序的大小比较方式可以自定义，实现Comparator的接口，int compare(T o1,T o2)
		 * 函数必须实现，Boolean equals(Object obj)可以不实现。其中compare的比较机制为：返回值为负
		 * 数则o1排在o2后*/
		TreeSet<Student> ts=new TreeSet<Student>(new Comparator<Student>() {
			public int compare(Student s1,Student s2) {
				int num=s1.getSum()-s2.getSum();
				return num;
			}
		});
		for(int i=0;i<5;i++) {
			Scanner sc=new Scanner(System.in);
			System.out.println("请输入第"+(i+1)+"个学生的信息：");
			System.out.println("姓名：");
			String name=sc.nextLine();
			System.out.println("语文成绩：");
			int chinese=sc.nextInt();
			System.out.println("数学成绩：");
			int math=sc.nextInt();
			System.out.println("英语成绩：");
			int english=sc.nextInt();
			Student s=new Student(name,chinese,math,english);
			ts.add(s);
		}
		for(Student s:ts) {
			System.out.println("姓名："+s.name+" 语文成绩："+s.Chinese+" 数学成绩："+s.Math+" 英语成绩："+s.English+" 总分："+s.getSum());
		}
	}
}
