package ind2;

public class Linear implements Root {
	double a,b;
	Linear(double a, double b){
		this.a=a;
		this.b=b;
	}
	public double x1() {
		return -b/a;
	}
	public void print() {
		System.out.println("root = "+x1());
	}
	
}
