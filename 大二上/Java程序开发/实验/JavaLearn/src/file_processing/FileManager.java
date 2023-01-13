/*基于命令行的文件管理器（云班课）
实验内容：
1）实现文件夹创建、删除、进入；
2）实现当前文件夹下的内容罗列；
3）实现文件拷贝和文件夹拷贝（文件夹拷贝指深度拷贝，包括所有子目录和文件）；
4）实现指定文件的加密和解密。
 */
package file_processing;
import java.io.File;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class FileManager {
	public static void main(String[] args) throws IOException{
		//因为文件管理器需要在任何电脑上通用，因此不能使用本机的绝对路径
		File dir=new File("src/file_processing");		//当前java文件所在目录
		File f1=new File(dir,"test1.txt");
		File f2=new File(dir,"test2.txt");
		File subdir=new File(dir,"subdir");
		f1.createNewFile();								//创建文件
		f2.createNewFile();
		subdir.mkdir();									//创建文件夹
		System.out.println(f1.exists());
		System.out.println("列出目录"+dir+"中的子文件夹：");	//列出文件夹下的子文件夹
		File[] fileArray=dir.listFiles();
		for(File f:fileArray) {
			if(f.isDirectory()) {
				System.out.println("文件夹："+f.getName());
			}
		}
		System.out.println("列出目录"+dir+"中的文件：");		//列出文件夹下的子文件
		for(File f:fileArray) {
			if(f.isFile()) {
				System.out.println("文件："+f.getName());
			}
		}
		FileInputStream  fis=new FileInputStream(new File("D:/LKH/DerrickRose.txt"));	//被复制文本
		FileOutputStream  fos=new FileOutputStream(new File("src/file_processing/test1.txt"));	//复制文本
		//文件复制
		int by;
		while((by=fis.read())!=-1) {
			fos.write(by);
		}
		fos.close();
		fis.close();
	}
}

