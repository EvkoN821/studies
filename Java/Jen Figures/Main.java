import java.util.Scanner;

public class Main {

    public static void main(String []args){
        Scanner sc = new Scanner(System.in);

        try {
            System.out.println("Input the name of your Triangle");
            String name = sc.nextLine();
            System.out.println("Input coords");
            double [][] coordinates = new double[3][2];
            for(int j=0; j<3; j++){
                for(int k=0; k<2; k++){
                    System.out.print("a["+j+"]["+k+"]:");
                    coordinates[j][k]= sc.nextDouble();
                }
            }
            Triangle triangle = new Triangle(name, coordinates);
            triangle.initSections();
            Figures<Body> triangleFigure = new Figures<>(triangle);

            String q=sc.nextLine();

            System.out.println("Input the name of your Tetragon");
            name = sc.nextLine();
            System.out.println("Input coords");
            coordinates = new double[4][2];
            for(int j=0; j<4; j++){
                for(int k=0; k<2; k++){
                    System.out.print("a["+j+"]["+k+"]:");
                    coordinates[j][k]= sc.nextDouble();
                }
            }
            Tetragon tetragon = new Tetragon(name, coordinates);
            tetragon.initSections();
            Figures<Body> tetragonFigure = new Figures<>(tetragon);

            System.out.println("Input x");
            double x = sc.nextDouble();
            System.out.println("Input y");
            double y = sc.nextDouble();

            triangleFigure.print();
            tetragonFigure.print();

            triangleFigure.move(x,y);
            tetragonFigure.move(x,y);

            int com= tetragonFigure.compare(tetragon, triangle);
            if(com==1) System.out.println("\n tetragon biggest");
            else if(com==0) System.out.println("\n triangle biggest");
            else if (com==-1)System.out.println("\n they are equal");
            /*
            if(triangleFigure.isIntersect(tetragonFigure)){
                System.out.println("They are intersecting");
            } else {
                System.out.println("They aren't intersecting");
            }

            if(tetragonFigure.isIntersect(triangleFigure)){
                System.out.println("They are intersecting");
            } else {
                System.out.println("They aren't intersecting");
            }
            */


        }
        catch (NegativeArraySizeException | ArrayStoreException | ArrayIndexOutOfBoundsException exception){
            System.out.println(exception.getMessage());
        }
        }


    }

