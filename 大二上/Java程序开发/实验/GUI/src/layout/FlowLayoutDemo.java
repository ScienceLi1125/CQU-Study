/* 流布局：
 * 1.通过setLayout方法设置容器的布局管理器
 * 2.添加多个按钮到frame中
 * 3.设置最佳大小，pack() 
 */
package layout;
import java.awt.*;

public class FlowLayoutDemo {
	public static void main(String[] args) {
		Frame frame=new Frame("FlowLayoutDemo");
		
		//frame.setLayout(new FlowLayout(FlowLayout.LEFT,20,20));
		frame.setLayout(new FlowLayout(FlowLayout.CENTER,20,20));
		for(int i=1;i<=100;i++) {
			frame.add(new Button("Button"+i));
		}
		frame.pack();		//设置最佳大小
		
		frame.setVisible(true);
	}
}
