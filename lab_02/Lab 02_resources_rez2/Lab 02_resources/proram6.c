#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int P = 2;
int a = 0;
pthread_mutex_t mutex;

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	for(int i = 0;i < 100;i++){
		pthread_mutex_lock(&mutex);
		a = a + 2;
		pthread_mutex_unlock(&mutex);
	}
	
}

int main(int argc, char **argv)
{
	int P = 4;
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

	return 0;
}
