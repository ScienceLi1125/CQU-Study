/*用四种方法复制视频文件并比较耗时
 * 1.基本字节流一次读一个字节
 * 2.基本字节流一次读一个字节数组
 * 3.字节缓冲流一次读一个字节
 * 4.字节缓冲流一次读一个字节数组
 */
package file_processing;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;

public class CopyVedio {
	public static void main(String[] args) throws IOException{
		long startTime=System.currentTimeMillis();
		method4();
		long endTime=System.currentTimeMillis();
		System.out.println("耗时："+(endTime-startTime)+"ms");
	}
//	public static void method1() throws IOException{
//		//D:\LKH\Video.mp4为复制过来的路径，不可以直接用，否则无法找到文件
//		FileInputStream fis=new FileInputStream("D:/LKH/Video.mp4");
//		FileOutputStream fos=new FileOutputStream("src/file_processing/Video.mp4");
//		int by;
//		while((by=fis.read())!=-1) {
//			fos.write(by);
//		}
//		fos.close();
//		fis.close();
//		//耗时：26684ms
//	}
//	public static void method2() throws IOException{
//		FileInputStream fis=new FileInputStream("D:/LKH/Video.mp4");
//		FileOutputStream fos=new FileOutputStream("src/file_processing/Video.mp4");
//		byte[] bys=new byte[1024];
//		int len;
//		while((len=fis.read(bys))!=-1) {
//			fos.write(bys,0,len);
//		}
//		fos.close();
//		fis.close();
//		//耗时：23ms
//	}
//	public static void method3() throws IOException{
//		BufferedInputStream bis=new BufferedInputStream(new FileInputStream("D:/LKH/Video.mp4"));
//		BufferedOutputStream bos=new BufferedOutputStream(new FileOutputStream("src/file_processing/Video.mp4"));
//		int by;
//		while((by=bis.read())!=-1) {
//			bos.write(by);
//		}
//		bos.close();
//		bis.close();
//		//耗时：140ms
//	}
	public static void method4() throws IOException{
		BufferedInputStream bis=new BufferedInputStream(new FileInputStream("D:/LKH/Video.mp4"));
		BufferedOutputStream bos=new BufferedOutputStream(new FileOutputStream("src/file_processing/Video.mp4"));
		byte[] bys=new byte[1024];
		int len;
		while((len=bis.read(bys))!=-1) {
			bos.write(bys,0,len);
		}
		bos.close();
		bis.close();
		//耗时：12ms
	}
}
