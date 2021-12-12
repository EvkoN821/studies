class Queue implements Data {
    private int[] queue;
    private int maxSize; // максимальное количество элементов в очереди
    private int nElem;  // текущее количество элементов в очереди
    private int front;
    private int rear;
    public Queue(int maxSize) {
        this.maxSize = maxSize;
        queue = new int[maxSize];
        rear = -1;
        front = 0;
        nElem = 0;
    }
    @Override  public void pushBack(int elem) {
        if (rear == maxSize - 1) {  // циклический перенос
            rear = -1;
        }
        queue[++rear] = elem;  //увеличение Rear и вставка
        nElem++;  // увеличение количества элементов в очереди
    }
    @Override public int popFront() {
        int temp = queue[front++]; // получаем первый элемент из очереди
        if (front == maxSize) { // циклический перенос
            front = 0;
        }
        nElem--; // уменьшаем количество элементов в очереди
        return temp;
    }
    @Override public int popBack(){return 0;}
    @Override public void pushFront(int elem){}
    @Override public boolean isEmpty() {
        return (nElem == 0);
    }
}
