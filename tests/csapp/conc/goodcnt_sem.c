#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

volatile long cnt = 0;
sem_t *mutex;

void *thread(void *vargp)
{
	long i;
	long niters = *((long *)vargp);

	for (i = 0; i < niters; i++)
	{
		sem_wait(mutex);
		cnt++;
		sem_post(mutex);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	long niters;
	pthread_t tid1, tid2;

	mutex = sem_open("/mutex", O_CREAT, 0644, 1);
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
