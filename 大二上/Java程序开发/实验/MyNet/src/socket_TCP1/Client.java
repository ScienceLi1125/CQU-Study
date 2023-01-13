package socket_TCP1;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client {
	public static void main(String[] args) throws UnknownHostException, IOException {
		Socket s=new Socket("192.168.3.29",50000);
		//获取键盘输入
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		//将字节流转化为字符流，和BufferedReader配套使用
		BufferedWriter bw=new BufferedWriter(new OutputStreamWriter(s.getOutputStream()));
		String line;
		while((line=br.readLine())!=null) {
			if("886".equals(line)) {
				break;
			}
			bw.write(line);		//一次写一个字符串
			bw.newLine();
			bw.flush();
		}
	
		s.close();
	}
}
