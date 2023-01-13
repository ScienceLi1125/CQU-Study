/*给定一个路径，递归遍历该目录下所有内容 */
package file_processing;
import java.io.File;

public class TraverseDirectory {

	public static void main(String[] args) {
		File scrfile=new File("D:\\JAVA\\eclipse-workspace\\JavaLearn\\src\\file_processing");
		getAllFilePath(scrfile);
	}
	public static void getAllFilePath(File scrfile) {
		File[] fileArray=scrfile.listFiles();
		if(fileArray!=null) {
			for(File file:fileArray) {
				if(file.isDirectory()) {
					getAllFilePath(file);		//递归调用
				}
				else {
					System.out.println(file.getAbsolutePath());
				}
			}
		}
	}
}
