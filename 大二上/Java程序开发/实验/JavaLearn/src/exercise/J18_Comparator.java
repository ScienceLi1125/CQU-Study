package exercise;
import java.util.Comparator;
import java.util.Arrays;
public class J18_Comparator {
	public static void main(String args[]) {
		Integer a[]= {1,6,5,3,4,9,5};
		Arrays.sort(a,new Comparator<Integer>() {
			public int compare(Integer x,Integer y) {
				if(x<y)	return 1;
				else	return -1;
			}
		});
		for(int i=0;i<a.length;i++) {
			System.out.print(a[i]+" ");
		}
	}
}
