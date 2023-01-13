/* 课本P168 T4
 * 编写一个程序，用Map实现学生成绩单的存储和查询，并对成绩进行排序后存储到TreeSet中
 */
package exercise;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.Iterator;
import java.util.Map;

public class J16_SchoolReport {
	public static void main(String[] args) {
		HashMap hm=new HashMap();
		hm.put("Tom", 97);
		hm.put("Jack", 88);
		hm.put("Lily", 92);
		hm.put("Mike", 82);
		hm.put("Helen", 72);
		hm.put("Vivi", 46);
		TreeSet ts=new TreeSet();
		Iterator it=hm.entrySet().iterator();	//HashMap自身无迭代器
		while(it.hasNext()) {
			Map.Entry pair=(Map.Entry)it.next();
			ts.add(pair.getValue());
		}
		System.out.println("成绩："+ts);
	}

}
