/*UDP接收数据的步骤：
	1.创建接收端Socket对象（DatagramSocket）
	2.创建数据包
	3.调用DatagramSocket对象的方法接收数据
	4.解析数据包，并把数据在控制台显示
	5.关闭发送端
	(运行时先启动接收端，后启动发送端)
*/
package learn;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class UDP_ReceiveMessage {
	public static void main(String[] args) throws IOException {
		//DatagramSocket(int port)构造数据报套接字(Socket)并将其绑定至本地主机上的指定端口
		DatagramSocket ds=new DatagramSocket(10086);
		
		byte[] bs=new byte[1024];
		
		//DatagramPacket(byte[] buf,int length)构造一个接收指定长度数据的数据包
		DatagramPacket dp=new DatagramPacket(bs,bs.length);
		
		ds.receive(dp);
		
		//byte[] getData()返回数据缓冲区
		byte[] datas=dp.getData();
		//int getLength()返回实际数据长度
		int len=dp.getLength();
		String dataString=new String(datas,0,len);
		System.out.println("数据是："+dataString);
		
		ds.close();
	}
}


