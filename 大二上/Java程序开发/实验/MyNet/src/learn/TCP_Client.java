/* TCP使用Socket对象代表两端的通信端口，并通过Socket产生IO流来进行网络通信。
 * 客户端Socket发送数据和服务器端ServerSocket接收数据
   TCP发送数据步骤：
  	1.创建客户端Socket对象
  	2.获取输出流，写数据
  	3.释放资源
   TCP只运行客户端会报错，因为没有跟服务器进行三次握手，连接被拒绝了
   端口号尽量写50000以上，以下容易被占用
 */
package learn;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class TCP_Client {
	public static void main(String[] args) throws UnknownHostException, IOException {
		//Socket(InetAddress address,int port)创建Socket并将其连接到指定IP地址的指定端口
		//Socket s=new Socket(InetAddress.getByName("192.168.3.29"),50000);
		//Socket(String host,int port)创建Socket并将其连接到指定主机的指定端口，功能同上
		Socket s=new Socket("192.168.3.29",50000);
		
		//OutputStream getOutputStream()返回Socket的输出流
		OutputStream os=s.getOutputStream();
		os.write("hello,tcp,我来了".getBytes());
		
		s.close();
	}

}
