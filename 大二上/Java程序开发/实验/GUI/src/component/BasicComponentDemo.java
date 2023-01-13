/* 测试基本组件中包括：文本域(TextArea)、下拉选择框(Choice)、单复选框(Checkbox+CheckBoxGroup)、
 * 单行文本框(TextField)、按钮(Button)、列表框(List)等基本组件。
 */
package component;
import java.awt.*;

import javax.swing.Box;

public class BasicComponentDemo {
	Frame frame=new Frame("BasicComponent");
	
	TextArea ta=new TextArea(5,20);		//5行20列的文本框
	
	Choice colorChooser=new Choice();	//下拉选择框
//	colorChooser.add("red");
//	colorChooser.add("blue");
//	colorChooser.add("green");			//必须在函数中才能对对象进行操作，函数外只能定义对象
	
	
	CheckboxGroup cbg=new CheckboxGroup();				//容纳单选框的复选框(只可以选择其中一个选项)
	Checkbox male=new Checkbox("male",cbg,true);		//单选框，选中
	Checkbox female=new Checkbox("female",cbg,false);	//没选中
	
	Checkbox Marriage=new Checkbox("Married");			//单选框
	
	TextField tf=new TextField(50);		//50列的单行文本框
	Button ok=new Button("ok");
	
	List colorlist=new List(6);			//列表框默认第二个参数为false表示单选
	//List colorlist=new List(6,true);	//多选
	
	public void init() {				//组装组件进行布局
		//组装下部分
		Box bottom=Box.createHorizontalBox();
		bottom.add(tf);
		bottom.add(ok);
		frame.add(bottom,BorderLayout.SOUTH);
		
		//组装左下部分
		Box leftbottom=Box.createHorizontalBox();
		colorChooser.add("red");
		colorChooser.add("blue");
		colorChooser.add("green");
		leftbottom.add(colorChooser);
		leftbottom.add(male);
		leftbottom.add(female);
		leftbottom.add(Marriage);
		
		//组装左下与左上部分
		Box topleft=Box.createVerticalBox();
		topleft.add(ta);
		topleft.add(leftbottom);
		
		//组装左右两部分
		Box top=Box.createHorizontalBox();
		colorlist.add("red");
		colorlist.add("blue");
		colorlist.add("green");
		top.add(topleft);
		top.add(colorlist);
		
		frame.add(top);
		frame.pack();
		frame.setVisible(true);
	}
	
	public static void main(String[] args) {
		new BasicComponentDemo().init();

	}

}
