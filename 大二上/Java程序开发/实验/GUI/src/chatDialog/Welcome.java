package chatDialog;
import java.awt.*;

public class Welcome {
	public static void main(String[] args) {
		Panel p=new Panel();
		p.add(new Button("进入"),BorderLayout.CENTER);
		Frame frame=new Frame("聊天室");
		
		frame.add(new TextField("欢迎来到聊天室"),BorderLayout.NORTH);
		ScrollPane sp=new ScrollPane(ScrollPane.SCROLLBARS_ALWAYS);	//含参构造指定显示滚动条
		sp.add(new TextArea(""));
		frame.add(sp);
		frame.add(p,BorderLayout.SOUTH);
		
		frame.setBounds(100,50,500,300);
		frame.setVisible(true);

	}

}
