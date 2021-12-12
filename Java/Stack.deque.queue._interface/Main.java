public class Main {
    public static void main(String[] args) {
        Stack mStack = new Stack(10);

        mStack.pushFront(79);
        mStack.pushFront(59);
        mStack.pushFront(35);
        mStack.pushFront(24);

        mStack.popFront();

        System.out.print("Стек: ");
        while (!mStack.isEmpty()) {
            int value = mStack.popFront();
            System.out.print(value);
            System.out.print(" ");
        }
        System.out.println("");
    }
}
