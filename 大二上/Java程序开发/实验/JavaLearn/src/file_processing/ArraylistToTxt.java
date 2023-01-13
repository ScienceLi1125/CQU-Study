/*将ArrayList作为数据库，将其中元素写入txt文件*/
package file_processing;

import java.util.ArrayList;
import java.io.*;

public class ArraylistToTxt {
	public static void main(String[] args) throws IOException{
		ArrayList<String> array=new ArrayList<String>();
		array.add("hello");
		array.add("world");
		array.add("java");
		array.add("C++");
		array.add("python");
		BufferedWriter bw=new BufferedWriter(new FileWriter("src/file_processing/TxtDemo.txt"));
		for(String s:array) {
			bw.write(s);
			bw.newLine();
			bw.flush();
		}
		bw.close();
	}
}
