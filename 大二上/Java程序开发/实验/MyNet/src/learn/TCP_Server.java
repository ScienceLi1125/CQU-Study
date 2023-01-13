/*TCP接收数据步骤：
  	1.创建服务端ServerSocket对象
  	2.获取输入流，读数据，并把数据显示在控制台
  	3.释放资源
 */
package learn;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class TCP_Server {
	public static void main(String[] args) throws IOException {
		ServerSocket ss=new ServerSocket(50000);
		
		//Socket accept()用于监听ss，一旦有连接便生成Socket对象并且接受
		Socket s=ss.accept();
		
		InputStream is=s.getInputStream();
		byte[] bys=new byte[1024];
		int len=is.read(bys);
		String data=new String(bys,0,len);
		System.out.println("数据是："+data);
		
		s.close();
		ss.close();
	}

}
