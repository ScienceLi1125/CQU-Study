package socket_UDP;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class SendMessage {

	public static void main(String[] args) throws IOException {
		DatagramSocket ds=new DatagramSocket();
		
		//封装键盘录入数据
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		String line;
		while((line=br.readLine())!=null) {
			if("886".equals(line)) {
				break;
			}
			byte[] bys=line.getBytes();
			InetAddress address=InetAddress.getByName("192.168.3.29");
			DatagramPacket dp=new DatagramPacket(bys,bys.length,address,12345);
			ds.send(dp);
		}
	
		ds.close();

	}

}
