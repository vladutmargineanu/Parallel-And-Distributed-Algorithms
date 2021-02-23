import static java.lang.Math.ceil;
import static java.lang.Math.min;

public class Multiply implements Runnable {
	int tid;
	int N;
	int P;
	int[][] a;
	int[][] b;
	int[][] res;

	Multiply(int id, int N, int P, int[][] a, int[][] b, int[][] res) {
		tid = id;
		this.N = N;
		this.P = P;
		this.a = a;
		this.b = b;
		this.res = res;
	}

	@Override
	public void run() {
		int start = tid * (int)ceil((double)N / P);
		int end   = min((int)N, (tid + 1) * (int)ceil((double)N / P));

		int i, j, k, t, tmp;

		for (i = start; i < end; ++i) {
			for (j = 0; j < N; ++j) {
				tmp = 0;

				for (k = 0; k < N; ++k) {
					tmp += a[i][k] * b[k][j];
				}

				res[i][j] = tmp;
			}
		}
	}

}
/* DO NOT MODIFY */
