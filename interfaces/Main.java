package ind2;
import java.util.*;
public class Main {

	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		Root []f;
		System.out.println("input number of equations: ");
		int k=sc.nextInt();
		f=new Root[k];
		for(int i=0;i<k;i++) {
			System.out.println("choose 1 - Linear, 2-Square: ");
			int g=sc.nextInt();
			if(g==1) {
				System.out.print("ax+b=0. input a,b");
				double a=sc.nextDouble();
				double b=sc.nextDouble();
				Linear l=new Linear(a,b);
				f[i]=l;			
			}
			if(g==2) {
				System.out.print("ax^2+bx+c=0. input a,b,c");
				double a=sc.nextDouble();
				double b=sc.nextDouble();
				double c=sc.nextDouble();
				Square s=new Square(a,b,c);
				f[i]=s;
			}
		}
		for(int i=0;i<k;i++) {
			System.out.println("root of "+(i+1)+" equation: ");
			f[i].print();
		}
	}
}
