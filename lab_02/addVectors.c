#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

int NReps;
int printLevel;
int N;
int P;
int* a;
int* b;
int* c;

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N NReps printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	NReps = atoi(argv[2]);
	printLevel = atoi(argv[3]);
}

void init()
{
	P = (int) sysconf(_SC_NPROCESSORS_ONLN);
	a = malloc(sizeof(int) * N);
	b = malloc(sizeof(int) * N);
	c = malloc(sizeof(int) * N);
	if(a == NULL || b == NULL || c == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i;
	for(i = 0; i < N; i++) {
		a[i] = i%500;
		b[i] = i%500;
	}
}

void printPartial()
{
	int i;
	for(i = 0; i < 10; i++)
		printf("%i ", c[i]);
	printf("\n");
	for(i = 20; i < N; i+=N/10)
		printf("%i ", c[i]);
	printf("\n");
	for(i = N - 10; i < N; i++)
		printf("%i ", c[i]);
	printf("\n");
}

void printAll()
{
	int i;
	for(i = 0; i < N; i++)
		printf("%i ", c[i]);
	printf("\n");
}

void print()
{
	if(printLevel == 0)
		return;
	else if(printLevel == 1)
		printPartial();
	else
		printAll();
}

void* threadFunction(void *var) {
	int thread_id = *(int*)var;

	int q = N/P;
	int start, end;

	start = thread_id * q;
	end = fmin(N, q * (thread_id + 1));

	if(P - 1 == thread_id) {
		end = N;
	}
	printf("%d %d %d\n", thread_id, start, end);

	for(int j = 0; j < NReps; j++)
		for (int i = start; i < end; i++) {
			c[i] = a[i] + b[i];
			printf("Hello world from thread %i\n", thread_id);
		}
}

int main(int argc, char *argv[])
{
	int i, j;
	getArgs(argc, argv);
	init();

	for(j = 0; j < NReps; j++)
		for(i = 0; i < N; i++)
			c[i] = a[i] + b[i];

	print();

	return 0;
}
