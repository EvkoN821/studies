public class Figures<T extends Body> {

    T figure;

    Figures(T figure) {
        this.figure = figure;
    }

    public T getFigure() {
        return figure;
    }

    void print() {
        System.out.println("Figures: " + figure.getName());
        double[][] coordinates = figure.getCoordinates();
        double[][] sections = figure.getSections();
        System.out.print(" with coordinates: ");
        for (int i = 0; i < coordinates.length; i++) {
            System.out.println("(" + coordinates[i][0] + "," + coordinates[i][1] + ");");
        }
        System.out.println("With sections: ");
        for (int i = 0; i < sections.length; i++) {
            for (int j = 0; j < sections[i].length; j++) {
                System.out.print(sections[i][j]+" ");
            }
            System.out.println();
        }
    }

    void move(double x, double y) {
        double[][] coordinates = figure.getCoordinates();
        for (int i = 0; i < coordinates.length; i++) {
            coordinates[i][0] += x;
            coordinates[i][1] += y;
        }
        figure.assignNewCoordinates(coordinates);
        print();
    }
    int compare(T x, T y) {
        double s1 = x.getS();
        double s2 = y.getS();
        if (s1 > s2) return 1;
        else if (s2 > s1) return 0;
        else return -1;
    }
	/*
    boolean isIntersectSections(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
        double check = (y4 - y3) * (x1 - x2) - (x4 - x3) * (y1 - y2);
        if (check == 0) {
            return (x1 * y2 - x2 * y1) * (x4 - x3) - (x3 * y4 - x4 * y3) * (x2 - x1) == 0 && (x1 * y2 - x2 * y1) * (y4 - y3) - (x3 * y4 - x4 * y3) * (y2 - y1) == 0;
        } else {
            double a = (x4 - x2) * (y4 - y3) - (x4 - x3) * (y4 - y2);
            double b = (x1 - x2) * (y4 - y2) - (x4 - x2) * (y1 - y2);
            double Ua = (float) a / check;
            double Ub = (float) b / check;
            return Ua >= 0 && Ua <= 1 && Ub >= 0 && Ub <= 1;
        }
    }

    boolean isIntersect(Figures<T> second_figure) {
        double[][] sections1 = figure.getSections();
        T second = second_figure.getFigure();
        double[][] sections2 = second.getSections();
        double[] points = new double[8];
        int max_length;
        boolean flag;
        for (int i = 0; i < sections1.length; i++) {
            System.arraycopy(sections1[i], 0, points, 0, 4);
            for (int j = 0; j < sections2.length; j++) {
                System.arraycopy(sections2[j], 0, points, 4, 4);
                if (isIntersectSections(points[0], points[1], points[2], points[3], points[4], points[5], points[6], points[7])) {
                    return true;
                }
            }
        }
        return false;
    }
	*/
    }
