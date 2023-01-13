/* void sleep(long millis)的用法
 * 为避免相互抢占线程，每个线程每执行一次循环都休眠1s，足够其他线程完成该次循环
 * 发现："Finished!"在最开始输出
 */
package learn;

public class ThreadSleep {

	public static void main(String[] args) {
		SleepThread st1=new SleepThread();
		SleepThread st2=new SleepThread();
		SleepThread st3=new SleepThread();
		st1.setName("曹操");
		st2.setName("刘备");
		st3.setName("孙权");
		st1.start();
		st2.start();
		st3.start();
		System.out.println("Finished!");
	}
	static class SleepThread extends Thread{
		public void run() {
			for(int i=0;i<10;i++) {
				System.out.println(getName()+":"+i);
				try {
					Thread.sleep(1000);		//sleep 1000ms
				}catch(InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
}
