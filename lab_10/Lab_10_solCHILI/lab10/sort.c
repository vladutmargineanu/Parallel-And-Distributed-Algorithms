#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 4

/**
 * @author cristian.chilipirea
 *
 */


void compareVectors(int * a, int * b) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		if(a[i]!=b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int * v) {
	// DO NOT MODIFY
	int i;
	int displayWidth = 2 + log10(v[N-1]);
	for(i = 0; i < N; i++) {
		printf("%*i", displayWidth, v[i]);
	}
	printf("\n");
}

int cmp(const void *a, const void *b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A-B;
}
 
int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	if(rank==0) { // This code is run by a single process
		int sorted = 0;
		int aux;
		int *v = (int*)malloc(sizeof(int)*N);
		int *vQSort = (int*)malloc(sizeof(int)*N);
		int i, val;

		// generate the vector v with random values
		// DO NOT MODIFY
		srand(42);
		for(i = 0; i < N; i++)
			v[i] = rand()%N;
		displayVector(v);

		// make copy to check it against qsort
		// DO NOT MODIFY
		for(i = 0; i < N; i++)
			vQSort[i] = v[i];
		qsort(vQSort, N, sizeof(int), cmp);

		// sort the vector v
		// REPLACE THIS WITH YOUR SORT
		for (i = 1; i < nProcesses; i++) {
			MPI_Send(&v[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}

		for (i = 0; i < nProcesses; i++) {
			MPI_Send(&v[0], 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
			MPI_Recv(&val, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, NULL);

			if (val < v[0])
				v[0] = val;
		}

		for (i = 1; i < nProcesses; i++) {
			MPI_Recv(&v[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, NULL);
		}

		displayVector(v);
		compareVectors(v, vQSort);
	} else {
		int initial, new, i;
		MPI_Recv(&initial, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, NULL);

		printf("Process %d has initial value %d\n", rank, initial);

		for (i = 0; i < nProcesses; i++) {
			MPI_Send(&initial, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
			MPI_Recv(&new, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, NULL);

			printf("Process %d has received value %d from the left\n", rank, new);

			if (new > initial) {
				printf("Process %d will change its value from %d to %d\n", rank, initial, new);
				initial = new;
			}

			if (rank < nProcesses - 1) {
				MPI_Send(&initial, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
				MPI_Recv(&new, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, NULL);

				printf("Process %d has value %d, sends it to the right, and receives %d\n", rank, initial, new);

				if (new < initial) {
					initial = new;
				}
			}
		}

		MPI_Send(&initial, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}
