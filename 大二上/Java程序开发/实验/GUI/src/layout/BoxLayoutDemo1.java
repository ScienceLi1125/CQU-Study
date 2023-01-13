/* 盒子布局：在水平、垂直两个方向上摆放组件(Swing引入的新的布局管理器)
 * 1.创建BoxLayout对象，该对象存放组件是垂直存放
 * 2.将BoxLayout对象设置给Frame
 * 3.向Frame中添加两个按钮组件
 */
package layout;
import javax.swing.*;
import java.awt.*;

public class BoxLayoutDemo1 {
	public static void main(String[] args) {
		Frame frame=new Frame("BoxLayout");
		
		//BoxLayout boxlayout=new BoxLayout(frame,BoxLayout.Y_AXIS);	//纵向布局
		BoxLayout boxlayout=new BoxLayout(frame,BoxLayout.X_AXIS);		//横向布局
		frame.setLayout(boxlayout);
		frame.add(new Button("Button1"));
		frame.add(new Button("Button2"));
		
		frame.pack();
		frame.setVisible(true);
	}

}
