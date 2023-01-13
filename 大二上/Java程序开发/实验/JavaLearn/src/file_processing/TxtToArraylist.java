/*将txt文件中内容读入ArrayList */
package file_processing;

import java.util.ArrayList;
import java.io.*;

public class TxtToArraylist {
	public static void main(String[] args) throws IOException{
		ArrayList<String> array=new ArrayList<String>();
		BufferedReader br=new BufferedReader(new FileReader("src/file_processing/TxtDemo.txt"));
		String line;
		while((line=br.readLine())!=null) {
			array.add(line);
		}
		br.close();
		for(String s:array) {
			System.out.println(s);
		}
	}
}
