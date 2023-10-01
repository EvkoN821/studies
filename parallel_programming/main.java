public class main{
    public static void main(String[] args) {
        Integer[] arr = new Integer[100];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = ((int)(Math.random() * 12));
            System.out.println(arr[i]);
        }
        System.out.println("sorted mas=");
        Sorter.quicksort(arr);
        for (int i = 0; i < arr.length; i++) {
            System.out.println(arr[i]);
        }
    }
}