/*复制jpg格式的图片文件*/
package file_processing;
import java.io.File;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class CopyPicture {
	public static void main(String[] args) throws IOException{
		//文件不存在文件输入输出流可以自行创建
		FileInputStream fis=new FileInputStream(new File("D:/LKH/DerrickRose.jpg"));
		FileOutputStream fos=new FileOutputStream(new File("src/file_processing/demo.jpg"));
		byte[] bys=new byte[1024];
		int len;
		while((len=fis.read(bys))!=-1) {
			fos.write(bys,0,len);
		}
		fos.close();
		fis.close();
	}
}
