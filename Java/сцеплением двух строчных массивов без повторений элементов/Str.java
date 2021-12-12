import java.util.*;
public class Str {
    String []el;
    String []elnewnew;
    String []elnew;
    Str(int n){
        el=new String[n];
        Scanner sc=new Scanner(System.in);
        System.out.println(" input first mas: ");
        for(int i=0;i<el.length;i++)
            el[i]=sc.nextLine();
    }

    String getStr(int x){
        return el[x];
    }

    void addmas(String []el1){
        int size=el1.length+el.length;
        elnew=new String[size];
        int sizenew=0;
        for(int i=0;i<el1.length;i++) elnew[i]=el1[i];
        for(int i=el1.length; i<size;i++) elnew[i]=el[i-el1.length];
        for(int i=0;i<elnew.length;i++) {
            boolean f=true;
            for (int j = i + 1; j< elnew.length; j++)
                if (elnew[i].equals(elnew[j])) f=false;
            if(f)sizenew++;
            f=true;
            }
        elnewnew=new String[sizenew];
        int index=0;
        for(int i=0;i<elnew.length;i++) {
            boolean f=true;
            for (int j = i + 1; j < elnew.length; j++)
                if (elnew[i].equals(elnew[j])) f=false;
            if(f)
                elnewnew[index++] = elnew[i];
            f=true;
        }
    }

    void printElement(int x){
        System.out.println(el[x]);
    }

    void print(){
        for(int i=0;i<el.length;i++)
            System.out.println("  " + el[i]);
    }

    void printElNew(){
        System.out.println(" new array:");
        for(int i=0;i<elnewnew.length;i++)
            System.out.println("  " + elnewnew[i]);
    }


}
