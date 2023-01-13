package socket_TCP3;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class Client {
	public static void main(String[] args) throws IOException {
		Socket s=new Socket("192.168.3.29",50000);
		BufferedReader br=new BufferedReader(new FileReader("D:\\JAVA\\eclipse-workspace\\MyNet\\src\\socket_TCP3\\read.txt"));
		BufferedWriter bw=new BufferedWriter(new OutputStreamWriter(s.getOutputStream()));
		
		String line;
		while((line=br.readLine())!=null) {
			bw.write(line);
			bw.newLine();
			bw.flush();
		}
		//Client读完txt文件后退出了while循环（但没有发送line=null），而Server的br一直在等待readLine无法退出
		
		//自定义结束标记
//		bw.write("886");
//		bw.newLine();
//		bw.flush();
		
		//void shutdownOutput()发送一个对应Socket输出结束的标记
		s.shutdownOutput();
		
		//接收服务器端反馈因此是s.getInputStream()
		BufferedReader brClient=new BufferedReader(new InputStreamReader(s.getInputStream()));
		String data=brClient.readLine();
		System.out.println("服务器反馈："+data);
		
		br.close();
		s.close();
	}
}
