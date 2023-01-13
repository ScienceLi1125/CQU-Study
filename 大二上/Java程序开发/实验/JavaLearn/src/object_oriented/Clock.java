/*课本P83 T2
  定义一个时钟类：
	1.存储时钟的时hour(0~23)、分minute(0~ 59)、秒second(0~59)
	2.创建新对象时默认为0时0分0秒。
	3.设置时钟为指定的时间
	4.使时钟前进1秒钟的方法incSecond()。
	5.以“时:分:秒”的形式输出时钟的时间。
 */
package object_oriented;

public class Clock {
	public int hour=0;
	public int minute=0;
	public int second=0;
	Clock(int h,int m,int s){
		this.hour=h;
		this.minute=m;
		this.second=s;
	}
	public void incSecond() {
		if(second<59) {
			second++;
		}
		else if(minute<59) {
			second=0;
			minute++;
		}
		else if(hour<23) {
			minute=0;
			hour++;
		}
		else {
			hour=0;
		}
	}
	public void PrintClock() {
		String ho=String.format("%02d",hour);
		String mi=String.format("%02d",minute);
		String se=String.format("%02d",second);
		System.out.printf("当前时间："+ho+":"+mi+":"+se);
	}
	public static void main(String args[]) {
		Clock clock=new Clock(12,58,59);
		clock.incSecond();
		clock.PrintClock();
	}
}
