package a;
import java.util.*;
public class matr {
	int [][]a;
	matr(int n, int m){
		a=new int [n][m];
		Random r = new Random();
		for (int i=0;i<a.length;i++)
			for (int j=0;j<a[i].length; j++)
				a[i][j]=r.nextInt(20);
	}
	int sumk() {
		int s=0;
		for (int i=0;i<a.length;i++)
			for (int j=0;j<a[i].length; j++)
				if((i+j)%2==0 && a[i][j]%3==0) s+=a[i][j];
		return s;
	}
	void change() {
		for (int i=0;i<a.length;i++)
			for (int j=i+1;j<a[i].length; j++)
				a[i][j]=0;
	}
	void print() {
		for (int i=0;i<a.length;i++) {
			System.out.print("\n");
			for (int j=0;j<a[i].length; j++)
				System.out.print(a[i][j]+" ");
		}
	}
}
