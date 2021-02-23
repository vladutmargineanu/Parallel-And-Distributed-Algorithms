#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

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
		}
		fclose(polFunctionFile);

		for(x=0; x<3; x+=1) {
			float sum = 0;
			float xPowI = 1;
			for(i=0;i<polynomialSize;i++) {
				sum += xPowI * a[i];
				xPowI *= x; // more efficient than pow(x,i);
			}
			printf("%f ", sum);
		}
	}

	MPI_Finalize();
	return 0;
}

















/* Se calculeaza un polinom folosind notiunea de pipeline.4
 Fiecare proces este responsabil de calcularea polinomului pana 
 la gradul reprezentat de rangul sau r si de calcularea lui x ^ r. 
 Apoi, procesul trimite suma sa urmatorului proces, care va adauga
 ar+1 * x ^ (r + 1) la respectiva suma s.a.m.d.

Pentru eficienta, fiecare proces cu rang r va trimite mai departe
 3 valori: x, x ^ r si suma pana la respectivul proces.

Ultimul proces afiseaza rezultatul calculului. */