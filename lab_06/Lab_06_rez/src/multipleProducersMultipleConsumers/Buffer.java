package multipleProducersMultipleConsumers;
import java.util.concurrent.Semaphore;

/**
 * @author cristian.chilipirea
 *
 */
class Buffer {
	private static int BUFFER_CAPACITY = 5;
	private int[] v;
	private Semaphore empty;
	private Semaphore full;
	private int pos;

	Buffer() {
		v       = new int[BUFFER_CAPACITY];
		pos     = 0;
		// Creeam doua semafoare
		empty   = new Semaphore(BUFFER_CAPACITY);
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

		synchronized (Main.class) {
			pos     = (pos + 1) % BUFFER_CAPACITY;
			v[pos]  = value;
		}

		full.release();
	}

	int get() {
		try {
			full.acquire();
		} catch(InterruptedException e) {
			e.printStackTrace();
		}

		int val;

		synchronized (Main.class) {
			val = v[pos];  // COPIE

			pos = pos - 1;
			if (pos < 0) {
				pos = BUFFER_CAPACITY - 1;
			}
		}
		/*
		 * Se eliberează semaforul V()
		 * (Crește numărul de permits)
		 */
		empty.release();

		return val;
	}
}

/*
	Se implementeaza patternul Producer - Consumer atat pentru un consumator si
	 un producator cat si pentru consumatori si producatori multipli.

	Se folosesc semafoare pentru a se respecta constrangerile problemei:

	nu se fac citiri si scrieri in buffer in acelasi timp;
	nu se fac citiri concomitent;
	nu se fac scrieri concomitent
 */