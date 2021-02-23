#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, n, val, i, new;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n);

	val = rank;

	for (i = 1; i < n; i *= 2) {
		if (rank + i < n)
			MPI_Send(&val, 1, MPI_INT, rank + i, i, MPI_COMM_WORLD);

		if (rank >= i) {
			MPI_Recv(&new, 1, MPI_INT, rank - i, i, MPI_COMM_WORLD, NULL);
			val += new;
		}
	}

	printf("%d ---> %d\n", rank, val);

	MPI_Finalize();

	return 0;
}
