class Deque implements Data {
    int size;
    int head; //голова
    int tail; //хвост
    int[] data;
    Deque(int size) {
        data = new int[this.size = size];
    }
    @Override public void pushBack(int value){ //добавление в конец очереди
        if (++tail == size)
            tail = 0;
        data[tail] = value;
    }
    @Override public int popBack(){ //выборка с конца очереди
        int ret = data[tail];
        if (--tail < 0)
            tail = size - 1;
        return ret;
    }
    @Override public void pushFront(int value){ //добавление в начало очереди
        data[head] = value;
        if (--head < 0)
            head = size - 1;
    }
    @Override public int popFront(){ // выборка с начала очереди
        if (++head == size)
            head = 0;
        return data[head];
    }
    @Override public boolean isEmpty() {
        return tail == 0;
    }
}
