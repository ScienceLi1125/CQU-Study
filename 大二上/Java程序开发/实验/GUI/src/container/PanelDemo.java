/* 窗口界面内嵌按钮与文本框：
 * 1.创建窗口对象（其他容器必须依附window存在，不能单独使用）
 * 2.创建一个Panel对象（内嵌容器）
 * 3.创建一个文本框TextField和一个按钮Button，并将其放入Panel容器中
 * 4.将Panel放入Window中
 * 5.指定窗口位置、大小
 * 6.设置窗口对象可见
 * 注：本例中Frame窗口容器容纳了一个Panel内嵌容器，而Panel中容纳了普通组件TextField文本框和Button按钮
 */
package container;
import java.awt.*;

public class PanelDemo {
	public static void main(String[] args) {
		Frame frame=new Frame("panel on window");
		
		Panel p=new Panel();
		p.add(new TextField("TextField"));
		p.add(new Button("Button"));
		frame.add(p);
		
		frame.setBounds(100,50,500,300);
		frame.setVisible(true);

	}

}
