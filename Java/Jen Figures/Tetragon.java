public class Tetragon extends Body{

    Tetragon(String name, double [][] coordinates)  {
        this.name = name;
        this.coordinates = coordinates.clone();
        sections = new double[4][4];
    }


    public void initSections(){
        for(int i=0; i<3; i++){
            for(int j=0; j<2; j++){
                sections[i][j]=coordinates[i][j];
                sections[i][j+2]=coordinates[i+1][j];
            }
        }
        for(int i=3; i<4; i++){
            for(int j=0; j<2; j++){
                sections[i][j]=coordinates[i][j];
                sections[i][j+2]=coordinates[i-3][j];
            }
        }
    }
    public double getS(){
        //coordinates[0][0]*coordinates[1][1]+coordinates[1][0]*coordinates[2][1]+coordinates[2][0]*coordinates[3][1]+coordinates[3][0]*coordinates[0][1]-coordinates[1][0]*coordinates[0][1]-coordinates[2][0]*coordinates[1][1]-coordinates[3][0]*coordinates[2][1]-coordinates[0][0]*coordinates[3][1]
        //return (double) 0.5*Math.abs(x1*y2+x2*y3+x3*y4+x4*y1-x2*y1-x3*y2-x4*y3-x1*y4);
        return (double) 0.5*Math.abs(coordinates[0][0]*coordinates[1][1]+coordinates[1][0]*coordinates[2][1]+coordinates[2][0]*coordinates[3][1]+coordinates[3][0]*coordinates[0][1]-coordinates[1][0]*coordinates[0][1]-coordinates[2][0]*coordinates[1][1]-coordinates[3][0]*coordinates[2][1]-coordinates[0][0]*coordinates[3][1]);
    }


}
