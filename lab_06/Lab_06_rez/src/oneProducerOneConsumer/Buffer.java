package oneProducerOneConsumer;
import java.util.concurrent.Semaphore;

/**
 * @author cristian.chilipirea
 *
 */
class Buffer {
	private int a;
	private Semaphore empty;
	private Semaphore full;

	Buffer() {
		a 		= -1;
		// Declaram doua semafoare
		empty 	= new Semaphore(1);
		full 	= new Semaphore(0);
	}

	void put(int value) {
		try {
			/*
			* Luarea unui semafor P()
			* (Decremenetează permits)
			* (Așteaptă dacă permits e 0)
			 */
			empty.acquire();
		} catch(InterruptedException e) {
			e.printStackTrace();
		}

		a = value;

		full.release();
	}

	int get() {
		try {
			full.acquire();
		} catch(InterruptedException e) {
			e.printStackTrace();
		}

		int copyA = a;
		/*
		* Se eliberează semaforul V()
		* (Crește numărul de permits)
		 */
		empty.release();

		return copyA;
	}
}
