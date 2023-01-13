/* 边框布局：
 * 1.通过setLayout方法设置容器的布局管理器
 * 2.向frame指定区域添加组件
 * 3.设置最佳大小，pack() 
 */
package layout;
import java.awt.*;

public class BorderLayoutDemo2 {
	public static void main(String[] args) {
		Frame frame=new Frame("FlowLayoutDemo");
		
		frame.setLayout(new BorderLayout(30,10));
		frame.add(new Button("North"),BorderLayout.NORTH);
		frame.add(new Button("South"),BorderLayout.SOUTH);
		frame.add(new Button("Center"),BorderLayout.CENTER);
//		frame.add(new Button("East"),BorderLayout.EAST);
//		frame.add(new Button("West"),BorderLayout.WEST);	//没有创建的部位会被覆盖
		Panel p=new Panel();
		p.add(new Button("Center Button"));
		p.add(new TextField("TextField"));
		frame.add(p);
		
		frame.pack();
		frame.setVisible(true);

	}

}
