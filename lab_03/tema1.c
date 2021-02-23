#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int a = 0;

pthread_barrier_t bar;

void *adder(void *arg){
	for (int i = 0; i < 100; ++i)
	{
		a += 2;
	}
}

void *first_foo(){
	pthread_barrier_wait(&bar);
	a = 5;
	a += 7;
	pthread_barrier_wait(&bar);
}

void *second_foo(){
	a = 3;
	pthread_barrier_wait(&bar);
	pthread_barrier_wait(&bar);
	a += 2;
}

int main(int argc, char const *argv[])
{
	pthread_t tid[2];
	pthread_barrier_init(&bar, NULL, 2);

	for (int i = 0; i < 2; ++i)
	{
		pthread_create(&tid[i], NULL, adder, &i);
	}

	for (int i = 0; i < 2; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	printf("%d\n",a );

	pthread_create(&tid[0], NULL, first_foo, NULL);
	pthread_create(&tid[1], NULL, second_foo, NULL);

	for (int i = 0; i < 2; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	printf("%d\n",a );

	return 0;
}