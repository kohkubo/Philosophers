#include <libc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mutex;
int cnt;

void *thread_func(void *arg)
{
	int i = 100;
	printf("%s\n", (char *)arg);
	while (i--)
	{
		pthread_mutex_lock(&mutex);
		cnt++;
		pthread_mutex_unlock(&mutex);
		usleep(11000);
	}
	return NULL;
}

void *thread_func2(void *arg)
{
	int i = 100;
	printf("%s\n", (char *)arg);
	while (i--)
	{
		pthread_mutex_lock(&mutex);
		printf("cnt : %d\n", cnt);
		pthread_mutex_unlock(&mutex);
		usleep(11000);
	}
	return NULL;
}

int main()
{
	pthread_t thread[3];

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread[0], NULL, thread_func, "Hello");
	pthread_create(&thread[1], NULL, thread_func, "World");
	pthread_create(&thread[2], NULL, thread_func2, "read");
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
	printf("cnt : %d\n", cnt);
	return 0;
}
