/* 课本P167 T2
 * 找出两个字符串共同的字符
 * 思路：将第一个字符串的字符放入HashSet，对第二个每位字符遍历，判断是否在HashSet里
 */
package exercise;
import java.util.HashSet;

public class J15_CommonChar {
	public static void main(String[] args) {
		HashSet hs=new HashSet();
		String s1="AhdgSUhSYhdLn";
		String s2="KIOnmwefvhc KLogp";
		for(int i=0;i<s1.length();i++) {
			hs.add(s1.charAt(i));
		}
		System.out.println("Common char:");
		for(int i=0;i<s2.length();i++) {
			if(hs.contains(s2.charAt(i))) {
				System.out.print(s2.charAt(i)+" ");
			}
		}
	}
}
