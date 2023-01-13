/* UDP发送和接收数据的Socket对象是DatagramSocket的实例化对象
 * UDP发送数据的步骤：
 	1.创建发送端Socket对象（DatagramSocket）
 	2.创建数据并将其打包
 	3.调用DatagramSocket对象的方法发送数据
 	4.关闭发送端
 */
package learn;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDP_SendMessage {
	public static void main(String[] args) throws IOException {
		//DatagramSocket()构造数据报套接字(Socket)并将其绑定至本地主机上的任意端口
		DatagramSocket ds=new DatagramSocket();
		
		byte[] bs="hello,udp,我来了".getBytes();
		InetAddress address=InetAddress.getByName("192.168.3.29");
		
		//DatagramPacket(byte[] buf,int length,InetAddress address,int port)
		//构造一个数据包，发送指定长度的数据包到指定主机上的指定端口号
		DatagramPacket dp=new DatagramPacket(bs,bs.length,address,10086);
		
		ds.send(dp);
		
		ds.close();
	}

}
