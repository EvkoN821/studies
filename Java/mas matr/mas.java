package a;
import java.util.*;
public class mas {
	int []a;
	mas(int n){
		a = new int [n];
		Random r = new Random();
		for (int i=0;i<a.length;i++ )
			a[i]=r.nextInt(20);
	}
	double sred() {
		int s=0, count=0;
		for (int i=0;i<a.length;i++) 
			if(!prost.pr(a[i])) {
				s+=a[i];
				count++;
			}
		return s/count;
	}
	void change() {
		for (int i=0;i<a.length;i++) 
			if(a[i]%3!=0) a[i]*=a[i];
	}
	boolean yb() {
		for (int i=0;i<a.length-1;i++)
			if (a[i]<=a[i+1]) return false;
		return true;
	}
	void print() {
		for(int i=0;i<a.length; i++)
			System.out.print(a[i]+", ");
	}
}
