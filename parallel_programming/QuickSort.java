import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;
public class Sorter {
    private static final int N_THREADS = Runtime.getRuntime().availableProcessors();
    private static final int FALLBACK = 2;

    private static Executor pool = Executors.newFixedThreadPool(N_THREADS);
    public static <T extends Comparable<T>> void quicksort(T[] input) {
        final AtomicInteger count = new AtomicInteger(1);
        pool.execute(new QuicksortRunnable<T>(input, 0, input.length - 1, count));
        try {
            synchronized (count) {
                count.wait();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    private static class QuicksortRunnable<T extends Comparable<T>> implements Runnable {
        private final T[] values;
        private final int left;
        private final int right;
        private final AtomicInteger count;
        public QuicksortRunnable(T[] values, int left, int right, AtomicInteger count) {
            this.values = values;
            this.left = left;
            this.right = right;
            this.count = count;
        }
        @Override
        public void run() {
            quicksort(left, right);
            synchronized (count) {
                if (count.getAndDecrement() == 1)
                    count.notify();
            }
        }

        /**
         * Method which actually does the sorting. Falls back on recursion if there are a certain number of queued /
         * running tasks.
         *
         * @param pLeft  The left index of the sub array to sort.
         * @param pRight The right index of the sub array to sort.
         */
        private void quicksort(int pLeft, int pRight) {
            if (pLeft < pRight) {
                int storeIndex = partition(pLeft, pRight);
                if (count.get() >= FALLBACK * N_THREADS) {
                    quicksort(pLeft, storeIndex - 1);
                    quicksort(storeIndex + 1, pRight);
                } else {
                    count.getAndAdd(2);
                    pool.execute(new QuicksortRunnable<T>(values, pLeft, storeIndex - 1, count));
                    pool.execute(new QuicksortRunnable<T>(values, storeIndex + 1, pRight, count));
                }
            }
        }

        /**
         * Partitions the portion of the array between indexes left and right, inclusively, by moving all elements less
         * than values[pivotIndex] before the pivot, and the equal or greater elements after it.
         *
         * @param pLeft
         * @param pRight
         * @return The final index of the pivot value.
         */
        private int partition(int pLeft, int pRight) {
            T pivotValue = values[pRight];
            int storeIndex = pLeft;
            for (int i = pLeft; i < pRight; i++) {
                if (values[i].compareTo(pivotValue) < 0) {
                    swap(i, storeIndex);
                    storeIndex++;
                }
            }
            swap(storeIndex, pRight);
            return storeIndex;
        }
        private void swap(int left, int right) {
            T temp = values[left];
            values[left] = values[right];
            values[right] = temp;
        }
    }
}