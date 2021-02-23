package ProblemQueens;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    static final int N = 10;

    public static void main(String[] args) {
        ExecutorService tpe     = Executors.newFixedThreadPool(4);
        int[] queenPositions    = new int[N];

        tpe.submit(new PutQueen(tpe, queenPositions, 0));
    }
}