import java.util.*;
public class Main {
    public static void main(String []args){
        Scanner sc=new Scanner(System.in);

        System.out.println(" enter the size of the first array");
        int n=sc.nextInt();
        Str mas=new Str(n);

        System.out.println(" enter the size of the second array");
        int m=sc.nextInt();
        String []a=new String[m];
        System.out.println(" enter the sec array: ");
        String q=sc.nextLine();
        for(int i=0;i<a.length;i++)
            a[i] = sc.nextLine();

        mas.addmas(a);
        mas.printElNew();

    }
}
