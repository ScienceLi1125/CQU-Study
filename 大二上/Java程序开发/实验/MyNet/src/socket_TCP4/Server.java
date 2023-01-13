package socket_TCP4;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
	public static void main(String[] args) throws IOException {
		ServerSocket ss=new ServerSocket(50000);
		
		while(true) {
			Socket s=ss.accept();
			new Thread(new ServerThread(s)).start();
		}
	}
}
