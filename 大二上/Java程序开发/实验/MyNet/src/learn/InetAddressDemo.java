package learn;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class InetAddressDemo {

	public static void main(String[] args) throws UnknownHostException {
		InetAddress address=InetAddress.getByName("192.168.3.29");
		//InetAddress address=InetAddress.getByName("LAPTOP-ITUN5QJB");
		//确定主机名称的IP地址，输入的主机名称可以填机器名称或者IP地址
		
		String name=address.getHostName();
		String ip=address.getHostAddress();
		
		System.out.println("主机名："+name);
		System.out.println("IP地址："+ip);
	}

}
