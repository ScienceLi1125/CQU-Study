/*测试多线程的执行顺序，发现两个不同线程并发执行，一个线程内顺序执行。通过输出可以看到，两个并发执行的
 * 线程先开始的也可能后结束
 */
package learn;

public class SequenceDemo {
	public static void main(String[] args) {
		Thread sum=new SumThread();
		Thread squaresum=new SquareSumThread();
		squaresum.start();
		sum.start();
	}
	static class SumThread extends Thread{
		public void run() {
			int sum=0;
			for(int i=1;i<20;i++) {
				System.out.println("sum:"+i);
				sum+=i;
			}
			System.out.println("Sum="+sum);
		}
	}
	static class SquareSumThread extends Thread{
		public void run() {
			int sum=0;
			for(int i=1;i<20;i++) {
				System.out.println("squaresum:"+i*i);
				sum+=i*i;
			}
			System.out.println("SquareSum="+sum);
		}
	}
}
