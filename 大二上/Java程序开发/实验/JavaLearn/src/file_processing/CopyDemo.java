/*复制java文件
 *为了使用InputStreamReader和OutputStreamWriter，更简洁方式见书上P206 FileReader和FileWriter
 */
package file_processing;
import java.io.*;

public class CopyDemo {
	public static void main(String[] args) throws IOException{
		InputStreamReader isr=new InputStreamReader(new FileInputStream("src/file_processing/CopyDemo.java"));
		OutputStreamWriter osw=new OutputStreamWriter(new FileOutputStream("src/file_processing/CopiedDemo.java"));
		int ch;
		while((ch=isr.read())!=-1) {
			osw.write(ch);
		}
		osw.close();
		isr.close();
	}
}
