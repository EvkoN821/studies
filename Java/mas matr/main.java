package a;
import java.util.*;
public class main {
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		int n=sc.nextInt();
		int m=sc.nextInt();
		matr a=new matr(n,m);
		int s=a.sumk();
		a.print();
		System.out.print("\n"+"sum: "+s+"\n");
		a.change();
		a.print();
		
	}

}
