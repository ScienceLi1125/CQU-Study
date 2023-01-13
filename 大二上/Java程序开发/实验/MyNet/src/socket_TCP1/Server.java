package socket_TCP1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
	public static void main(String[] args) throws IOException {
		ServerSocket ss=new ServerSocket(50000);
		Socket s=ss.accept();
		
		BufferedReader br=new BufferedReader(new InputStreamReader(s.getInputStream()));
		String line;
		while((line=br.readLine())!=null) {
			System.out.println("Êý¾ÝÊÇ£º"+line);
		}
		
		s.close();
		ss.close();
	}
}
