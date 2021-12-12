public abstract class Body{

    String name;
    double [][] coordinates;
    double [][] sections;

    abstract public void initSections();
    abstract public double getS();
    public String getName(){
        return name;
    }

    public double[][] getCoordinates(){
        return coordinates;
    }

    public double[][] getSections() {
        return sections;
    }

    public void assignNewCoordinates(double [][] new_coordinates){
        coordinates = new_coordinates;
        initSections();
    }


}
