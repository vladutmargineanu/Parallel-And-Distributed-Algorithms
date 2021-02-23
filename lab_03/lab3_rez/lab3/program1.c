#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_mutex_t mutex;
int a = 2;

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;
	for(int i = 0;i < 100;i++){
	a = a+2;
}
}


int main(int argc, char **argv)
{
	int P = 2;
	int i;

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
	printf("%d\n",a );
	return 0;
}
