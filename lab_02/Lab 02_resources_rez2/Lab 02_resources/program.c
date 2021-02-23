#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void* threadFunction(void *var)
{
	int i,j;
	int x;
	for(i = 0;i < 1000000;i++){
		x = sqrt(i);
		for(j = 0;j < 1000000;j++){
			x = sqrt(i);
}
}
	for(i = 0;i < 100000;i++){
		x = sqrt(i);
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

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
