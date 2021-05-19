#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void like_factorial(int n)
{
pthread_mutex_lock(&mutex);
if (n > 1)
{
printf("n = %d\n", n);
like_factorial(n-1);
}
else
{
printf("Done!");
}
pthread_mutex_unlock(&mutex);
}

int main()
{
pthread_t thread;
pthread_create(&thread, NULL, (void* )like_factorial, (void* )5);
pthread_join(thread,NULL);
return 0;
}