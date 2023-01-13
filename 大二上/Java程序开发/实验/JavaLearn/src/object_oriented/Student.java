/* 课本P125 T2
  	编写一个类Student,该类拥有属性:校名、学号、性别、出生日期。方法包含设置姓名和成绩(setName(),
  	setScore()),再编写Student类的子类Undergraduate(大学生)。Undergraduate类除拥有父类的
  	上述属性和方法外，还拥有附加的属性和方法:属性包括系(department)、专业(major);方法包含设置系别
  	和专业(setDepartment(),setMajor())。
  	注：用public修饰类后，只能将其写在不同的class文件里
 */
package object_oriented;

public class Student{
	protected String School;
	protected String Number;
	protected boolean Sex;		//性别sex：true为男，false为女
	protected String Birth;
	protected String Name;
	protected int Score;
	public Student() {}			//无参构造函数，不赋值的情况下都赋为各自类型的默认值
	
	public Student(String school,String number,boolean sex,String birth,String name,int score) {
		this.School=school;
		this.Number=number;
		this.Sex=sex;
		this.Birth=birth;
		this.Name=name;
		this.Score=score;
	}
	public void setName(String name) {
		this.Name=name;
	}
	public void setScore(int score) {
		this.Score=score;
	}
}