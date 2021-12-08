package ind1;
import java.util.*;
public class Main {

	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		System.out.println("input name: ");
		String name=sc.nextLine();
		System.out.println("input density: ");
		double density=sc.nextDouble();
		System.out.println("input concentration: ");
		double conc=sc.nextDouble();
		Acid a=new Acid(name,density,conc);
		System.out.print(a.print());
		System.out.println("\n input new density");
		double density1=sc.nextDouble();
		a.setDensity(density1);
		System.out.print(a.print());
	}

}
