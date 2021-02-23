#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define MASTER      (0)
#define MAX_NUM     (1000)

int main (int argc, char* argv[])
{
    int i, rank, numProc, step, nextProc, prevProc;
    int recvSum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    srand(time(NULL) + rank);

    int* v  = NULL;
    int sum = rand() % MAX_NUM;

    printf("Initially, process %d has number %d.\n", rank, sum);

    for (step = 1; step < numProc; step <<= 1)
    {
        nextProc = rank + step;
        prevProc = rank - step;

        if (nextProc < numProc)
        {
            MPI_Send(&sum, 1, MPI_INT, nextProc, MPI_TAG_UB, MPI_COMM_WORLD);
        }

        if (prevProc >= 0)
        {
            MPI_Recv(
                &recvSum,
                1,
                MPI_INT,
                prevProc,
                MPI_ANY_TAG,
                MPI_COMM_WORLD,
                MPI_STATUS_IGNORE
            );

            sum += recvSum;
        }
    }

    printf("Finally, process %d has sum %d.\n", rank, sum);

    MPI_Finalize();

    return 0;
}









/* Se calculeaza sumele partiale ale unui vector. Se face pe dos fata
de Reduce: procesele trimit sumele lor la dreapta in loc de stanga si
fiecare proces retine suma elementelor de pana la el, inclusiv.

Logica dupa care se face trimitera sumelor partiale de la un proces 
la altul este similara celei din Reduce.*/