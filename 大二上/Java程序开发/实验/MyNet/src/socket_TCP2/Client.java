package socket_TCP2;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class Client {
	public static void main(String[] args) throws IOException {
		Socket s=new Socket("192.168.3.29",50000);
		BufferedReader br=new BufferedReader(new FileReader("D:\\JAVA\\eclipse-workspace\\MyNet\\src\\socket_TCP2\\read.txt"));
		BufferedWriter bw=new BufferedWriter(new OutputStreamWriter(s.getOutputStream()));
		
		String line;
		while((line=br.readLine())!=null) {
			bw.write(line);
			bw.newLine();
			bw.flush();
		}
		
		br.close();
		s.close();
	}
}
