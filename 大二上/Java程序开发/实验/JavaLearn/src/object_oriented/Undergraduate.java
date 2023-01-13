/*继承自父类Student*/
package object_oriented;

public class Undergraduate extends Student{
	public String Department;		//如果声明为private，则无法在main函数里访问
	public String Major;
	public Undergraduate(String school,String number,boolean sex,String birth,String name,int score,String department,String major) {
		super(school,number,sex,birth,name,score);
		this.Department=department;
		this.Major=major;
	}
	public void setDepartment(String department) {
		this.Department=department;
	}
	public void setName(String major) {
		this.Major=major;
	}
	
	public static void main(String[] args) {
		Student s1=new Student();
		Student s2=new Student("CQU","4165",true,"1125","lkh",98);
		//若声明为Student s3，则访问成员变量时会返回父类的成员
		Undergraduate s3=new Undergraduate("CQU","4165",false,"0204","xql",99,"Computer","CS");
		System.out.println("s1.Birth:"+s1.Birth);
		System.out.println("s2.Number:"+s2.Number);
		System.out.println("s3.Major:"+s3.Major);
	}
}
