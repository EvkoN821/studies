package ind1;

class Acid extends Liquid {
	private double conc;
	Acid(String name, double density, double conc){
		super(name,density);
		this.conc=conc;
	}
	void setConc(double cons) {this.conc=conc;}
	public String print() {
		return super.print()+"\n concentration: "+conc;
	}
}
