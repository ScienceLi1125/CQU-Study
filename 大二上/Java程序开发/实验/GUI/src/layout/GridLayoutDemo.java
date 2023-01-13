/* 网格布局：将容器分割成纵横线分割的网格，每个网格大小相同。添加组件时默认从左到右、从上到下且每个组件自动填充满所在区域
 * 本例用GridLayout创建一个计算器页面
 * 1.创建Panel1对象存放TextField组件
 * 2.将Panel1容器添加到Frame的NORTH区域（Panel默认FlowLayout布局）
 * 3.创建Panel2对象，设置布局管理器为GridLayout
 * 4.向Panel2中添加内容
 * 5.将Panel2添加到Frame中
 */
package layout;

import java.awt.*;

public class GridLayoutDemo {
	public static void main(String[] args) {
		Frame frame=new Frame("Calculator");
		
		Panel p1=new Panel();
		p1.add(new TextField(30));
		frame.add(p1,BorderLayout.NORTH);
		
		Panel p2=new Panel();
		//p2.setLayout(new GridLayout(3,5,4,4));	//版本不支持
		
		for(int i=0;i<10;i++) {
			p2.add(new Button(i+""));	//i+""将int转化为String
		}
		p2.add(new Button("+"));
		p2.add(new Button("-"));
		p2.add(new Button("*"));
		p2.add(new Button("/"));
		p2.add(new Button("."));
		frame.add(p2);
		
		frame.pack();
		frame.setVisible(true);
	}

}
