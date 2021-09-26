#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

volatile long cnt = 0;
pthread_mutex_t lock;

void *thread(void *vargp)
{
	long i;
	long niters = *((long *)vargp);

	for (i = 0; i < niters; i++)
	{
		pthread_mutex_lock(&lock);
		cnt++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	long niters;
	pthread_t tid1, tid2;

	pthread_mutex_init(&lock, NULL);
	if (argc != 2) {
		printf("Usage: %s <niters>\n", argv[0]);
		exit(0);
	}
	niters = atoi(argv[1]);
	pthread_create(&tid1, NULL, thread, (void *)&niters);
	pthread_create(&tid2, NULL, thread, (void *)&niters);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	if (cnt != niters * 2)
		printf("BOOM! cnt = %ld\n", cnt);
	else
		printf("OK cnt=%ld\n", cnt);
	return 0;
}
