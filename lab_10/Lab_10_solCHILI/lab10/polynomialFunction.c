#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/**
 * @author cristian.chilipirea
 *
 */

int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	if(rank==0) { // This code is run by a single process
		int polynomialSize;
		int n;
		int i;
		int j;
		float x;

		FILE * polFunctionFile = fopen("a1.txt","rt");
		fscanf(polFunctionFile, "%i", &polynomialSize);
		float * a = malloc(sizeof(float)*polynomialSize);
		for(i=0;i<polynomialSize;i++) {
			fscanf(polFunctionFile, "%f", a+i);
			printf("Read value %f\n", a[i]);

			if (i > 0) {
				printf("Sending %f\n", a[i]);
				MPI_Send(&a[i], 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
			}
		}
		fclose(polFunctionFile);

		for(x=0; x<3; x+=1) {
			//float xPowI = 1;
			//for(i=0;i<polynomialSize;i++) {
			//	sum += xPowI * a[i];
			//	xPowI *= x; // more efficient than pow(x,i);
			//}
			//printf("%f ", sum);
			MPI_Send(&x, 1, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD);
			MPI_Send(&a[0], 1, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD);
		}
	} else {
		float val = 0;
		float x, sum;
		int i;

		MPI_Recv(&val, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, NULL);
		printf("Process %d received value %f\n", rank, val);

		for (i = 0; i < 3; i++) {
			MPI_Recv(&x, 1, MPI_FLOAT, rank - 1, 0, MPI_COMM_WORLD, NULL);
			MPI_Recv(&sum, 1, MPI_FLOAT, rank - 1, 0, MPI_COMM_WORLD, NULL);
			printf("Received x=%f and sum=%d\n", x, sum);
			sum += val * pow(x, rank);

			if (rank == nProcesses - 1) {
				printf("Polynom value is %f\n", sum);
			} else {
				MPI_Send(&x, 1, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD);
				MPI_Send(&sum, 1, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD);
			}
		}
	}

	MPI_Finalize();
	return 0;
}
