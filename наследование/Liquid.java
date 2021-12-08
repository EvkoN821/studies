package ind1;

public class Liquid {
	private String name;
	private double density;
	Liquid(String name, double density){
		this.name=name;
		this.density=density;
	}
	String getName() {return name;}
	double getDensity() {return density;}
	
	void setName(String name) {this.name=name;}
	void setDensity(double density) {this.density=density;}
	
	public String print() {
		return "name: "+name+"\n density: "+density;
	}
}
