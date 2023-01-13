/*普通FileIn/OutputStream复制文件内容时默认编码，当被复制文件与Java编译器编码方式冲突时(本机中txt
 * 文件编码为UTF-8，eclipse编码为GBK)，读取的中文会出现乱码
 * 改进方法：用字符流指定编码读取
 */
package file_processing;
import java.io.File;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;

public class CopyFileinChinese {
	public static void main(String[] args) throws IOException{
		File dir=new File("src/file_processing");
		File f3=new File(dir,"test3.txt");
		System.out.println(f3.createNewFile());
		String content="";			//文本内容
		FileInputStream fis=new FileInputStream(new File("D:/LKH/DerrickRose2.txt"));
		FileOutputStream fos=new FileOutputStream(new File("src/file_processing/test3.txt"));
		InputStreamReader isr=new InputStreamReader(fis,"UTF-8");	//指定编码
		BufferedReader br=new BufferedReader(isr);
		String line=null;			//每行内容
		while((line=br.readLine())!=null) {
			content+=line;
			content+="\r\n";
		}
		OutputStreamWriter osw=new OutputStreamWriter(fos,"GBK");
		osw.write(content);
		isr.close();
		osw.close();
		fos.close();
		fis.close();
	}
}
