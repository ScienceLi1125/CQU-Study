package socket_UDP;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class ReceiveMessage {

	public static void main(String[] args) throws IOException {
		DatagramSocket ds=new DatagramSocket(12345);
		
		while(true) {
			byte[] bs=new byte[1024];
			DatagramPacket dp=new DatagramPacket(bs,bs.length);
			ds.receive(dp);
			
			byte[] datas=dp.getData();
			int len=dp.getLength();
			String dataString=new String(datas,0,len);
			System.out.println("数据是："+dataString);
		}
		
		//ds.close();	//一直接收因此不需要关闭
	}

}
