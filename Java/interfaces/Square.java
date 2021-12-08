package ind2;

public class Square implements Root {
	double a,b,c;
	Square(double a, double b,double c){
		this.a=a;
		this.b=b;
		this.c=c;
	}
	public double x1() {
		double d=Math.sqrt(b*b-4*a*c);
		return (-b+d)/(2*a);
	}
	public double x2() {
		double d=Math.sqrt(b*b-4*a*c);
		return (-b-d)/(2*a);
	}
	public void print() {
		if(x1()!=x2() && !(Double.isNaN(x1()))) 
			System.out.println("root1 = "+x1()+"\nroot2 = "+x2());
		if(Double.isNaN(x1()))
			System.out.println("no real roots");
		if(x1()==x2())
			System.out.println("root = "+x1());
	}
}
