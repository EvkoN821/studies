import java.util.*;
import java.util.LinkedList;
public class MyList {
    LinkedList <Integer> list;
    MyList(){
        list = new LinkedList<Integer>();
    }

    void createlist(){
        int x;
        Scanner sc=new Scanner(System.in);
        x=sc.nextInt();
        while(x!=-1){
            list.addLast(x);
            x=sc.nextInt();
        }
    }

    void print(){
        ListIterator<Integer> it=list.listIterator();
        while(it.hasNext())
            System.out.println(it.next());
    }

    void addel(int x){
        list.addLast(x);
    }

    void delel(int x){
        ListIterator<Integer> it=list.listIterator();
        while(it.hasNext())
            if(it.next().equals(x))
                it.remove();
    }

    int max(){
        ListIterator<Integer> it=list.listIterator();
        int x=it.next();
        while(it.hasNext()) {
            int a=it.next();
            if (a > x) x = a;
        }
        return x;
    }

    boolean sym(){
        ListIterator<Integer> it=list.listIterator();
        ListIterator<Integer> it1=list.listIterator(list.size());
        boolean f=true;
        while(it.hasNext())
            if(!(it.next().equals(it1.previous())))
                f=false;
        return f;
    }

    void delpervskon(int x){
        ListIterator<Integer> it=list.listIterator(list.size());
        while(it.hasPrevious())
            if(it.previous().equals(x)){
                it.remove();
                break;
        }
    }

    double sredznpol(){
        ListIterator<Integer> it=list.listIterator();
        int s=0, count=0;
        while(it.hasNext()) {
            int a=it.next();
            if (a > 0) {
                s += a;
                count++;
            }
        }
        return (double)s/count;
    }


}
