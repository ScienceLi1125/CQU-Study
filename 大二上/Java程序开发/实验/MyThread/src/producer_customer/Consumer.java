package producer_customer;

public class Consumer implements Runnable{
	private Box b;
	public Consumer(Box b) {
		this.b=b;
	}
	@Override
	public void run() {
		while(true) {		//运行结束后需要在终端手动终止
			b.get();
		}
	}
}
