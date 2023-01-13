/* 卖票：
 * 3个窗口共同售卖100张票
 * 思路：创建3个线程共同处理1个资源，因此采用Runnable接口
 * 数据安全问题：多线程环境有多条语句操作共享数据
 * 解决办法：Lock锁:synchronized (obj)
 */
package sell_tickets;

public class SellTickets implements Runnable {
	private int tickets=100;
	private Object obj=new Object();
	public static void main(String[] args) {
		SellTickets st=new SellTickets();
		Thread t1=new Thread(st,"窗口1");
		Thread t2=new Thread(st,"窗口2");
		Thread t3=new Thread(st,"窗口3");
		t1.start();
		t2.start();
		t3.start();

	}
	@Override
	public void run() {
//无synchronized锁时，首尾会出现重复
//		while(tickets>0) {
//			try {
//				//Thread.sleep(1);		//与休眠时间无关
//				Thread.sleep(100);
//				//t1线程抢到CPU后休息100ms，此时t2抢到后开始执行，t3同理，因此会出现相同输出值
//			}catch (InterruptedException e) {
//				e.printStackTrace();
//			}
//			System.out.println(Thread.currentThread().getName()+"正在出售第"+(101-tickets)+"张票");
//			tickets--;
//		}

//synchronized锁锁错地方，导致一直是窗口一卖票
//		synchronized (obj) {
//			//t1线程抢到CPU后锁住执行程序，此时t2无法运行
//			while(tickets>0) {
//				try {
//					Thread.sleep(1);
//
//				}catch (InterruptedException e) {
//					e.printStackTrace();
//				}
//				System.out.println(Thread.currentThread().getName()+"正在出售第"+(101-tickets)+"张票");
//				tickets--;
//			}
//		}

		while(tickets>0) {
			synchronized (obj) {
			//t1线程抢到CPU后锁住执行程序，sleep时t2抢到CPU但无法运行，需要等到t1跳出锁后才有机会执行
				try {
					Thread.sleep(1);
				}catch (InterruptedException e) {
					e.printStackTrace();
				}
				System.out.println(Thread.currentThread().getName()+"正在出售第"+(101-tickets)+"张票");
				tickets--;
			}
		}
//		while(true) {
//			synchronized (obj) {
//				if(tickets>0){
//					try {
//						Thread.sleep(1);
//					}catch (InterruptedException e) {
//						e.printStackTrace();
//					}
//					System.out.println(Thread.currentThread().getName()+"正在出售第"+(101-tickets)+"张票");
//					tickets--;
//				}
//			}
//		}
	}
}
