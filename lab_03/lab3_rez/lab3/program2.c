#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_barrier_t mybarrier;
pthread_mutex_t mutex;
int a = 0;

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;
	if(thread_id == 0){
		a = 3;
		pthread_barrier_wait(&mybarrier);
		pthread_barrier_wait(&mybarrier);
		a += 2;
	}
	if(thread_id == 1){
		pthread_barrier_wait(&mybarrier);
		a = 5;
		a += 7;
		pthread_barrier_wait(&mybarrier);
	}
}
	int main(int argc, char **argv)
{
	int P = 2;
	int i;
	pthread_barrier_init(&mybarrier,NULL,2);
	pthread_t tid[P];
	int thread_id[P];

	for(i = 0;i < P; i++)
		thread_id[i] = i;


	pthread_mutex_init(&mutex, NULL);
	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	printf("%d\n",a);

	return 0;
}

