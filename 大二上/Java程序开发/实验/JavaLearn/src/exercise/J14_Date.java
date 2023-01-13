/*日期计算(云班课)
功能1 计算下个月第二周星期二的日期，用2021-10-14这样的格式显示。先把功能写成函数，再用主函数来调用。
功能2 把现在的时间换成美国和日本的时间，再以ISO格式显示。
 */
package exercise;
import java.util.Date;
import java.util.Calendar;

public class J14_Date {
	public static void NextMonth2ndTue(Calendar c) {
		int CurrMonth=c.get(Calendar.MONTH);
		int NextMonth=(CurrMonth+1)%12;				//考虑12月
		while(c.get(Calendar.MONTH)!=NextMonth) {	//循环结束的条件：进入下个月
			c.add(Calendar.DATE,1);
		}
		c.add(Calendar.DATE,7);						//进入第二周
		while(c.get(Calendar.DAY_OF_WEEK)!=3) {		//循环结束的条件：周二（Calendar.DAY_OF_WEEK中为3）
			c.add(Calendar.DATE,1);
		}
		FormatPrint(c);
		CHNTime(c);			//中国时间
		USATime(c);			//美国时间
		JAPTime(c);			//日本时间
	}
	
	public static void FormatPrint(Calendar c) {	//格式化输出日期(月份从0开始)
		System.out.print(c.get(Calendar.YEAR)+"-"+(c.get(Calendar.MONTH)+1)+"-");
		System.out.println(c.get(Calendar.DATE));
	}
	
	public static void CHNTime(Calendar c) {
		System.out.print(c.get(Calendar.YEAR)+"-"+(c.get(Calendar.MONTH)+1)+"-");
		System.out.print(c.get(Calendar.DATE)+" T ");
		System.out.print(c.get(Calendar.HOUR_OF_DAY)+":");
		System.out.print(c.get(Calendar.MINUTE)+":"+c.get(Calendar.SECOND));
		System.out.println(" +08");
	}
	public static void USATime(Calendar c) {
		c.add(Calendar.HOUR_OF_DAY,-13);			//中国比美国快13h，加负数即可
		System.out.print(c.get(Calendar.YEAR)+"-"+(c.get(Calendar.MONTH)+1)+"-");
		System.out.print(c.get(Calendar.DATE)+" T ");
		System.out.print(c.get(Calendar.HOUR_OF_DAY)+":");
		System.out.print(c.get(Calendar.MINUTE)+":"+c.get(Calendar.SECOND));
		System.out.println(" -05");
	}
	public static void JAPTime(Calendar c) {
		c.add(Calendar.HOUR_OF_DAY,1);
		System.out.print(c.get(Calendar.YEAR)+"-"+(c.get(Calendar.MONTH)+1)+"-");
		System.out.print(c.get(Calendar.DATE)+" T ");
		System.out.print(c.get(Calendar.HOUR_OF_DAY)+":");
		System.out.print(c.get(Calendar.MINUTE)+":"+c.get(Calendar.SECOND));
		System.out.println(" +09");
	}
	
	public static void main(String[] args) {
		Calendar c1=Calendar.getInstance();
		NextMonth2ndTue(c1);
	}

}
