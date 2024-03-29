package problemSortList;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class Inserter extends Thread {
    private final int id;
    private Semaphore sem;
    private List<Integer> buffer;

    Inserter(int id, Semaphore sem, List<Integer> buffer) {
        this. id    = id;
        this.sem    = sem;
        this.buffer = buffer;
    }

    @Override
    public void run() {
        try {
            Scanner scanner = new Scanner(new File("elemente" + id + ".txt"));

            while (scanner.hasNextInt()) {
                buffer.add(scanner.nextInt());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        sem.release();
    }
}