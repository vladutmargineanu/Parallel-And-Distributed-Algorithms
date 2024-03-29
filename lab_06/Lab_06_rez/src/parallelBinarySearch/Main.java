package parallelBinarySearch;

import java.util.concurrent.CyclicBarrier;

public class Main {
    public static void main(String[] args) {
        final int P         = 4;
        final int N         = 100000;
        final int element   = 4;
        int[] numbers       = new int[N];
        int position;

        CyclicBarrier barrier           = new CyclicBarrier(P);
        parallelBinarySearch.BinarySearchThread[] threads    = new parallelBinarySearch.BinarySearchThread[N];

        for (int i = 0; i < N; ++i) {
            numbers[i] = i << 1;
        }

        for (int i = 0; i < P; ++i) {
            threads[i] = new parallelBinarySearch.BinarySearchThread(numbers, N, P, barrier, i, element);
            threads[i].start();
        }

        for (int i = 0; i < P; ++i) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        position = parallelBinarySearch.BinarySearchThread.getPosition();

        if (position > -1) {
            System.out.println("Found element " + element + " on position " + position
                    + " (number at position is: " + numbers[position] + ").");
        } else {
            System.out.println("Not found!");
        }
    }
}