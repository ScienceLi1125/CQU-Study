/* 卡片布局：按时间管理组件，只有最上面的组件(最早添加)可见
 * 1.创建一个Panel p1，用来存储多张卡片
 * 2.创建CardLayout对象，并将该对象设置给p1容器
 * 3.向p1容器中存储多个组件
 * 4.把p1放到Frame中间区域
 * 5.创建另一个Panel p2，用来存储多个按钮
 * 6.创建5个按钮组件
 * 7.创建一个事件监听器，，监听各个按钮的点击动作
 * 8.将当前的事件监听器和多个按钮绑定
 * 9.将按钮添加到p2中
 * 10.将p2放到Frame中
 */
package layout;
import java.awt.*;
import java.awt.event.*;

public class CardLayoutDemo {
	public static void main(String[] args) {
		Frame frame=new Frame("CardLayout");
		
		Panel p1=new Panel();				//存储多张卡片
		CardLayout cardlayout=new CardLayout();
		p1.setLayout(cardlayout);
		String[] cards= {"1st","2nd","3rd","4th","5th"};
		//画面中点击first显示的界面与"1st"命名无关，只与添加顺序有关
		for(int i=0;i<cards.length;i++) {
			p1.add(cards[i],new Button(cards[i]));	//第一个参数为组件名，第二个参数为组件
		}
		//frame.add(p1,BorderLayout.NORTH);
		frame.add(p1);		//window容器全都默认BorderLayout布局，不写哪一部分则占满没被使用的部分
		
		Panel p2=new Panel();				//存储多个按钮
		Button b1=new Button("previous");
		Button b2=new Button("next");
		Button b3=new Button("first");
		Button b4=new Button("last");
		Button b5=new Button("3rd");
		
		ActionListener listener=new ActionListener() {		//事件监听器，监听每个动作
			@Override
			public void actionPerformed(ActionEvent e) {
				String actionCommand=e.getActionCommand();	//该字符串即为按钮上文字
				switch(actionCommand) {
					case "previous":
						cardlayout.previous(p1);
						break;
					case "next":
						cardlayout.next(p1);
						break;
					case "first":
						cardlayout.first(p1);
						break;
					case "last":
						cardlayout.last(p1);
						break;
					case "3rd":
						cardlayout.show(p1,"3rd");
						break;
				}
			}
		};
		
		b1.addActionListener(listener);
		b2.addActionListener(listener);
		b3.addActionListener(listener);
		b4.addActionListener(listener);
		b5.addActionListener(listener);
		
		p2.add(b1);
		p2.add(b2);
		p2.add(b3);
		p2.add(b4);
		p2.add(b5);
		
		frame.add(p2,BorderLayout.SOUTH);
		
		frame.pack();
		frame.setVisible(true);
	}
}
