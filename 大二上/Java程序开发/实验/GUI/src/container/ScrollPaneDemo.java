/* 含滚动条窗口界面：
 * 1.创建窗口对象，并添加关闭键
 * 2.创建一个ScrollPane对象（含滚动条的容器）
 * 3.向ScrollPane中添加内容
 * 4.将ScrollPane放入Frame中
 * 5.指定窗口位置、大小
 * 6.设置窗口对象可见
 * 注：本例中Frame容纳了一个ScrollPane含滚动条容器，而ScrollPane中容纳了TextField和Button
 * 	  ScrollPane无参构造时默认非必要时无滚动条：当内容可以容纳时，不显示滚动条，当内容超出window时，自动显示滚动条
 */
package container;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class ScrollPaneDemo {
	public static void main(String[] args) {
		Frame frame=new Frame("ScrollPaneDemo");
		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent arg0) {
				System.exit(0);
			}
		});
		
		//ScrollPane sp=new ScrollPane();		//无参构造默认无滚动条
		ScrollPane sp=new ScrollPane(ScrollPane.SCROLLBARS_ALWAYS);	//含参构造指定显示滚动条
		sp.add(new TextField("TextField"));
		sp.add(new Button("Button"));
		frame.add(sp);
		
		frame.setBounds(100,50,500,300);
		frame.setVisible(true);

	}

}
