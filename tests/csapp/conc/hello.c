#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// This is the function that each thread will execute.
// thread routine is defined 
void *thread(void *arg) {
	printf("Hello, world!");
	return NULL;
}

int main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, thread, NULL); // Create a new thread
	pthread_join(tid, NULL); // wait for thread to finish
	return 0;
}
