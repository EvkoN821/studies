class Stack implements Data {
    private int mSize; //mSize - максимальный размер
    private int[] stackArray;
    private int top;

    public Stack(int m) {
        this.mSize = m;
        stackArray = new int[mSize];
        top = -1;
    }
    @Override public void pushFront(int element) {
        stackArray[++top] = element;
    }
    @Override public int popFront() {
        return stackArray[top--];
    }
    @Override public void pushBack(int element) {}
    @Override public int popBack() {return 0;}
    @Override public boolean isEmpty() {
        return (top == -1);
    }
}