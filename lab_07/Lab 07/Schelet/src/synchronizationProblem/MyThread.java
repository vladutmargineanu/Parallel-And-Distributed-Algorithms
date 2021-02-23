package synchronizationProblem;

/**
 * @author cristian.chilipirea
 * 
 */
public class MyThread implements Runnable {
	int id;
	static int value = 0;

	MyThread(int id) {
		this.id = id;
	}

	@Override
	public void run() {
		if (id == 0) {
			for (int i = 0; i < Main.N; i++)
				value = value + 3;
		} else {
			for (int i = 0; i < Main.N; i++)
				value = value + 3;
		}
	}
}
