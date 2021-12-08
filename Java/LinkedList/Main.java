public class Main {
    public static void main (String []args){
        MyList l=new MyList();
        l.createlist();

        System.out.println("list= ");
        l.print();
        System.out.println();
        System.out.println("\n");
        l.delpervskon(21);
        l.print();
        System.out.println();
        System.out.println("\n");
        l.addel(-999);
        l.print();
        System.out.println();
        System.out.println("\n");
        System.out.println("max= ");
        System.out.println(l.max());
        System.out.println("\n");
        System.out.println("sr= ");
        System.out.println(l.sredznpol());
        System.out.println("\n");
        System.out.println("sym= ");
        System.out.println(l.sym());
    }
}
