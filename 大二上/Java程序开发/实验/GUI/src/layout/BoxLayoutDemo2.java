/* 盒子容器默认盒子布局(Swing引入的新的容器)
 * 1.创建一个水平排列组件的Box容器
 * 2.在当前容器中添加两个按钮
 * 3.创建一个垂直排列组件的Box容器
 * 4.在当前容器中添加两个按钮
 * 5.将两个Box容器添加到Frame中展示
 */
package layout;
import javax.swing.*;
import java.awt.*;

public class BoxLayoutDemo2 {
	public static void main(String[] args) {
		Frame frame=new Frame("BoxLayout");
		
		//Box本身就是容器
		Box hbox=Box.createHorizontalBox();
		hbox.add(new Button("hbutton1"));
		hbox.add(new Button("hbutton2"));
		
		Box vbox=Box.createVerticalBox();
		vbox.add(new Button("vbutton1"));
		vbox.add(new Button("vbutton2"));
		
		frame.add(hbox,BorderLayout.NORTH);
		frame.add(vbox);
		
		frame.pack();
		frame.setVisible(true);
	}

}
