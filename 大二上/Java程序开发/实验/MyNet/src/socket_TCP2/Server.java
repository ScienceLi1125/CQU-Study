package socket_TCP2;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
	public static void main(String[] args) throws IOException {
		ServerSocket ss=new ServerSocket(50000);
		Socket s=ss.accept();
		
		BufferedReader br=new BufferedReader(new InputStreamReader(s.getInputStream()));
		BufferedWriter bw=new BufferedWriter(new FileWriter("D:\\JAVA\\eclipse-workspace\\MyNet\\src\\socket_TCP2\\write.txt"));	//将数据写入txt文件
		String line;
		while((line=br.readLine())!=null) {
			bw.write(line);
			bw.newLine();
			bw.flush();
		}
		
		bw.close();
		s.close();
		ss.close();
	}
}
