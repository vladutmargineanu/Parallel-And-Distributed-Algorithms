package parallelTree;


import java.util.concurrent.CyclicBarrier;

/**
 * @author cristian.chilipirea
 *
 */
public class Main {
	private static final int N_ITERATIONS = 100;

	public static void main(String[] args) {
		Thread[] threads = new Thread[3];
		CyclicBarrier barrier;

		System.out.println("Parallel tree problem");

		for (int j = 0; j < N_ITERATIONS; j++) {
			TreeNode tree 	= new TreeNode(1);
			barrier 		= new CyclicBarrier(3);

			threads[0] = new Thread(new ReadTreePart(tree, "treePart1.txt", barrier));
			threads[1] = new Thread(new ReadTreePart(tree, "treePart2.txt", barrier));
			threads[2] = new Thread(new VerifyTree(tree, barrier));

			for (Thread thread : threads) {
				thread.start();
			}

			for (Thread thread : threads) {
				try {
					thread.join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
}