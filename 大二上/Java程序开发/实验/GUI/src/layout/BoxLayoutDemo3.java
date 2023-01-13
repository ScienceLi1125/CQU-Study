/* 盒子容器默认盒子布局(Swing引入的新的容器)
 * 1.创建一个水平排列组件的Box容器hbox
 * 2.向hbox中添加按钮，并在多个按钮之间添加分割
 * 3.创建一个垂直排列组件的Box容器vbox
 * 4.向vbox中添加按钮，并在多个按钮之间添加分割
 * 5.将两个Box容器添加到Frame中展示
 */
package layout;
import javax.swing.*;
import java.awt.*;

public class BoxLayoutDemo3 {
	public static void main(String[] args) {
		Frame frame=new Frame("BoxLayout");
		
		Box hbox=Box.createHorizontalBox();
		hbox.add(new Button("hbutton1"));
		//按添加顺序从左到右，因此hbutton1添加完后先添加分隔再添加button2
		hbox.add(Box.createHorizontalGlue());
		//Box.createHorizontalGlue()创建的分隔可以在两个方向上拉伸
		hbox.add(new Button("hbutton2"));
		hbox.add(Box.createHorizontalStrut(30));
		//Box.createHorizontalStrut(30)创建的分隔指定宽度，因此只能在垂直方向上拉伸
		hbox.add(new Button("hbutton3"));
		
		Box vbox=Box.createVerticalBox();
		vbox.add(new Button("vbutton1"));
		vbox.add(Box.createVerticalGlue());
		//Box.createVerticalGlue()创建的分隔可以在两个方向上拉伸
		vbox.add(new Button("vbutton2"));
		vbox.add(Box.createVerticalStrut(50));
		//Box.createVerticalStrut(30)创建的分隔指定高度，因此只能在水平方向上拉伸
		vbox.add(new Button("vbutton3"));
		
		frame.add(hbox,BorderLayout.NORTH);
		frame.add(vbox);
		
		frame.pack();
		frame.setVisible(true);
	}

}
