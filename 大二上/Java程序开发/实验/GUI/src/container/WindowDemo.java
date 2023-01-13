/* 窗口界面：
 * 1.创建窗口对象
 * 2.指定窗口位置、大小
 * 3.设置窗口对象可见
 * 注：此处创建成的窗口界面可以拉伸、最小化和最大化，但无法叉掉，只能在终端手动结束
 */
package container;
import java.awt.*;
public class WindowDemo {
	public static void main(String[] args) {
		Frame frame=new Frame("WindowDemo");
//		frame.setLocation(100,50);			//此处单位为像素
//		frame.setSize(500,300);
		frame.setBounds(100,50,500,300);	//可以取代上面两行
		frame.setVisible(true);				//别忘了设置
	}

}
