/* 生产者消费者案例中的类：
 * 1.奶箱类Box：定义成员变量milk表示第x瓶奶，state表示是否有牛奶，成员函数存储和获取牛奶
 * 2.生产者类Producer：实现Runnable接口，重写run()方法，调用存储牛奶的操作
 * 3.消费者类Consumer：实现Runnable接口，重写run()方法，调用获取牛奶的操作
 * 4.测试类Test 
 * 注：wait()和notify()需要成对使用
 * 	  注意加synchronized关键字
 */
package producer_customer;

public class Test {

	public static void main(String[] args) {
		Box b=new Box();
		Producer p=new Producer(b);		//将奶箱对象传入生产者构造函数
		Consumer c=new Consumer(b);		//将奶箱对象传入消费者构造函数
		Thread t1=new Thread(p);		//生产者线程
		Thread t2=new Thread(c);		//消费者线程
		
		t1.start();
		t2.start();
	}

}
