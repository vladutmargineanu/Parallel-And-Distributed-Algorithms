public class Main {
	public static final int N = 3;
	public static final int P = 5;
	public static int[][] a = new int[N][N];
	public static int[][] b = new int[N][N];
	public static int[][] c = new int[N][N];
	public static int[][] res = new int[N][N];

	public static void main(String[] args) {
		System.out.println("Matrix multiplication problem.");

		for (int i = 0; i < N * N; ++i) {
				a[i / N][i % N] = i;
				b[i / N][i % N] = i;
		}

		System.out.println("Matricea a:");
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				System.out.print(a[i][j] + " ");
			}
			System.out.println("");
		}
		System.out.println("\nMatricea b:");
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				System.out.print(b[i][j] + " ");
			}
			System.out.println("");
		}


		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				int tmp = 0;

				for (int k = 0; k < N; k++) {
					tmp += a[i][k] * b[k][j];
				}

				c[i][j] = tmp;
			}
		}
		System.out.println("\nRezultat asteptat:");
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				System.out.print(c[i][j] + " ");
			}
			System.out.println("");
		}


		Thread threads[] = new Thread[P];
		for (int i = 0; i < P; ++i) {
			threads[i] = new Thread(new Multiply(i, N, P, a, b, res));
		}

		for (int i = 0; i < P; ++i)
			threads[i].start();
		for (int i = 0; i < P; ++i) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();

			}
		}


		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (res[i][j] != c[i][j]) {
					System.out.println("FAILED " + i + j + "   " + res[i][j]);
					System.exit(0);
				}
			}
		}
		System.out.println("CORRECT");
	}
}
/* DO NOT MODIFY */
