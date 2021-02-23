#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

int P = 2;
int a = 0;
pthread_barrier_t barrier;
	
void* threadFunction1(void *var)
{
	int thread_id = *(int*)var;
	printf("1");
	pthread_barrier_wait(&barrier);
	pthread_barrier_wait(&barrier);
}

void* threadFunction2(void *var)
{
	int thread_id = *(int*)var;
	pthread_barrier_wait(&barrier);
	printf("2");
	pthread_barrier_wait(&barrier);
}

int main(int argc, char **argv)
{
	
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0; i < P; i++)
		thread_id[i] = i;

	
	int num_threads = 2;
	pthread_barrier_init(&barrier, NULL, num_threads);
	

		pthread_create(&(tid[0]), NULL, threadFunction1, &(thread_id[0]));

		pthread_create(&(tid[1]), NULL, threadFunction2, &(thread_id[1]));
	

	
		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);

	pthread_barrier_destroy(&barrier);
	
	return 0;
}
