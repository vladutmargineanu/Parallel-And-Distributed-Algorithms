#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, n, val, i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n);

	if (rank == 0) {
		val = 42;
	}

	for (i = 1; i < n; i *= 2) {
		if (rank < i && rank + i < n) {
			MPI_Send(&val, 1, MPI_INT, rank + i, i, MPI_COMM_WORLD);
		} else if (rank >= i && rank < i * 2) {
			MPI_Recv(&val, 1, MPI_INT, MPI_ANY_SOURCE, i, MPI_COMM_WORLD, NULL);
		}
	}

	printf("%d ---> %d\n", rank, val);

	MPI_Finalize();

	return 0;
}
