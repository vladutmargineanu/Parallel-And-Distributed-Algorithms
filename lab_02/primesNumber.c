#include<stdio.h>
#include<pthread.h>

#define N 1000000
#define MAX_THREADS 4

int prime_arr[N] = {0};

void *printprime(void *ptr)
{
  int  j, flag;
  int i=(int)(long long int) ptr;
  for(i = 2; i < N; i++){
     flag = 0;
     for(j = 2;j <= i/2; j++)
       {
        if(i % j == 0)
          {
           flag = 1;
           break;
          }
       }

     if(flag == 0)
     {
       prime_arr[i] = 1;
     }
  }
}

int main()
{
 pthread_t tid[MAX_THREADS];
 int count = 0;
 for(count = 0; count < MAX_THREADS; count++)
 {
   printf("\r\n CREATING THREADS %d", count);
   pthread_create(&tid[count], NULL, printprime, &(count));
 }
 printf("\n");
 for(count = 0; count < MAX_THREADS; count++)
 {
   pthread_join(tid[count], NULL);
 }

 int c = 0;
 for(count = 0; count < N; count++)
   if(prime_arr[count] == 1)
       printf("%d ", count);

 return 0;
 }