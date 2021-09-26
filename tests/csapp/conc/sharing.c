#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N 2

char **ptr;

void *thread(void *vargp) {
	int myid = (int)vargp;
	static int cnt = 0;
	
	printf("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
	return NULL;
}

int main()
{
	int i;
	pthread_t tid;
	char *msgs[N] = {"Hello from foo", "Hello from bar"};

	ptr = msgs;
	for (i = 0; i < N; i++) {
		pthread_create(&tid, NULL, thread, (void *)i);
	}
	pthread_exit(NULL);
}
