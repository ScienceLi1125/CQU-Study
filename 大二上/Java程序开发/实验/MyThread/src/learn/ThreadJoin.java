/* void join()的用法
 * 调用该函数的线程执行完毕后其他线程才可以执行(包括主线程)
 */
package learn;

public class ThreadJoin {

	public static void main(String[] args) throws InterruptedException {
		JoinThread jt1=new JoinThread();
		JoinThread jt2=new JoinThread();
		JoinThread jt3=new JoinThread();
		jt1.setName("曹操");
		jt2.setName("刘备");
		jt3.setName("孙权");
		jt1.start();
		jt1.join();
		System.out.println("break!");
		jt2.start();
		jt3.start();
	}
	static class JoinThread extends Thread{
		public void run() {
			for(int i=0;i<10;i++) {
				System.out.println(getName()+":"+i);
			}
		}
	}
}
