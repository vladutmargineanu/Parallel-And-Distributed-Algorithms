package problemSortList;

import java.util.Collections;
import java.util.List;
import java.util.concurrent.Semaphore;

public class Sort extends Thread {
    private Semaphore sem;
    private List<Integer> buffer;

    Sort(Semaphore sem, List<Integer> buffer) {
        this.sem    = sem;
        this.buffer = buffer;
    }

    @Override
    public void run() {
        try {
            sem.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Collections.sort(buffer);
    }
}