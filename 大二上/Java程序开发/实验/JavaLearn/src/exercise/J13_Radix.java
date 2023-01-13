/* 课本P168 T5
 * 给定一个整数-1234567，输出它的二进制、八进制和十六进制表示形式
 */
package exercise;

public class J13_Radix {
	public static void main(String[] args) {
		int num=-1234567;
		String sb=Integer.toString(num,2);			//含符号
		String usb=Integer.toBinaryString(num);		//不含符号
		String so=Integer.toString(num,8);
		String uso=Integer.toOctalString(num);
		String sh=Integer.toString(num,16);
		String ush=Integer.toHexString(num);
		System.out.println("二进制："+sb);
		System.out.println("八进制："+so);
		System.out.println("十六进制："+sh);
		System.out.println("无符号二进制："+usb);
		System.out.println("无符号八进制："+uso);
		System.out.println("无符号十六进制："+ush);
	}
}
