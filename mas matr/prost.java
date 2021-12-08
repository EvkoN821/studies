package a;

public class prost {
	static public boolean pr(int x) {
		for(int i=2; i<x/2+1;i++)
			if (x%i==0) return false;
		return true;
	}
}
