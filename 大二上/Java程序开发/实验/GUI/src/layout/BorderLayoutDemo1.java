/* 边框布局：
 * 1.通过setLayout方法设置容器的布局管理器
 * 2.向frame指定区域添加组件
 * 3.设置最佳大小，pack() 
 */
package layout;
import java.awt.*;

public class BorderLayoutDemo1 {
	public static void main(String[] args) {
		Frame frame=new Frame("FlowLayoutDemo");
		
		frame.setLayout(new BorderLayout(10,10));
		frame.add(new Button("North"),BorderLayout.NORTH);
		frame.add(new Button("South"),BorderLayout.SOUTH);
		frame.add(new Button("Center"),BorderLayout.CENTER);
		frame.add(new Button("East"),BorderLayout.EAST);
		frame.add(new Button("West"),BorderLayout.WEST);
		
		frame.pack();
		frame.setVisible(true);

	}

}
