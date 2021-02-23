package philosophersProblem;

/**
 * @author cristian.chilipirea
 * 
 */
public class Philosopher implements Runnable {
	private final Object leftFork, rightFork;
	private final int id;

	 Philosopher(int id, Object leftFork, Object rightFork) {
		this.leftFork = leftFork;
		this.rightFork = rightFork;
		this.id = id;
	}

	private void sleep() {
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void run() {
		/* Sincronizarea:
		 * asigură excluderea mutuală – un singur fir poate executa la un
		 * moment dat o metodă (secvență de cod) sincronizată: secțiune critică
		 */
		if (id == 0) {
			synchronized (rightFork) {
				sleep(); // delay added to make sure the dead-lock is visible
				synchronized (leftFork) {
					System.out.println("Philosopher " + id + " is eating");
				}
			}
		} else {
			synchronized (leftFork) {
				sleep(); // delay added to make sure the dead-lock is visible
				synchronized (leftFork)
				 {
					System.out.println("Philosopher " + id + " is eating");
				}
			}
		}
	}
}
/*
 * In timp ce ceilalti filosofi dau lock mai intai pe stanga si apoi pe
 * dreapta, unul dintre acestia functioneaza invers, reusind sa termine
 * de mancat si eliberandu-si lockurile.
 * In continuare, ceilalti filosofi vor proceda ca la incput, acum fiind
 * destule resurse disponibile pentru toti.
 */