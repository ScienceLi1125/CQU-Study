/* void setDaemon(boolean on)的用法
 * 当运行线程只剩守护线程时，虚拟机退出
 * 但虚拟机退出需要时间，因此守护线程并非立即停止。程序中将主线程和守护线程循环次数设置较大差距即可看到
 */
package learn;

public class ThreadDaemon {
	public static void main(String[] args) throws InterruptedException {
		DaemonThread dt1=new DaemonThread();
		DaemonThread dt2=new DaemonThread();
		dt1.setName("关羽");
		dt2.setName("张飞");
		Thread.currentThread().setName("刘备");
		dt1.setDaemon(true);
		dt2.setDaemon(true);
		
		dt1.start();
		dt2.start();
		for(int i=0;i<5;i++) {
			System.out.println(Thread.currentThread().getName()+":"+i);
		}
	}
	static class DaemonThread extends Thread{
		public void run() {
			for(int i=0;i<20;i++) {
				System.out.println(getName()+":"+i);
			}
		}
	}

}
