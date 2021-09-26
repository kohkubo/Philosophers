#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

typedef struct {
	int *buf; // Buffer array
	int n; // Maximum number of slots
	int front; // buf[(front+1)%n] is first item
	int rear; // buf[rear%n] is last item
	sem_t *mutex; // Protects accesses to buf
	sem_t *slots; // Counts available slots
	sem_t *items; // Counts available items
} sbuf_t;

/* Create an empty bounded, shared FIFO buffer with n slots */
void sbuf_init(sbuf_t *sp, int n)
{
	sp->buf = (int *)malloc(n * sizeof(int));
	sp->n = n;
	sp->front = sp->rear = 0;
	sp->mutex = sem_open("/mutex", O_CREAT, 0644, 1);
	sp->slots = sem_open("/slots", O_CREAT, 0644, n);
	sp->items = sem_open("/items", O_CREAT, 0644, 0);
}

/* Clean up buffer sp */
void sbuf_deinit(sbuf_t *sp)
{
	free(sp->buf);
	sem_close(sp->mutex);
	sem_close(sp->slots);
	sem_close(sp->items);
}

/* Insert item onto the rear of shared buffer sp */
void sbuf_insert(sbuf_t *sp, int item)
{
	sem_wait(sp->slots);
	sem_wait(sp->mutex);
	sp->buf[(++sp->rear) % (sp->n)] = item;
	sem_post(sp->mutex);
	sem_post(sp->items);
}

/* Remove and return the first item from the buffer sp */
int sbuf_remove(sbuf_t *sp)
{
	int item;
	sem_wait(sp->items);
	sem_wait(sp->mutex);
	item = sp->buf[(++sp->front) % (sp->n)];
	sem_post(sp->mutex);
	sem_post(sp->slots);
	return item;
}


int readcnt;
sem_t mutex, w;

void reader(void) {
	while (1) {
		sem_wait(&mutex);
		readcnt++;
		if (readcnt == 1)
			sem_wait(&w);
		sem_post(&mutex);

		/* Critical section */
		/* Reading happens */

		sem_wait(&mutex);
		readcnt--;
		if (readcnt == 0)
			sem_post(&w);
		sem_post(&mutex);
	}
}

void writer(void) {
	while (1) {
		sem_wait(&w);
		/* Critical section */
		/* Writing happens */
		sem_post(&w);
	}
}

/*
特定のセマフォの実装が、それぞれのセマフォに対してLIFOスタックを使っていると仮定する。
スレッドがP操作でセマフォをブロックしたとき、そのIDがスタック上にプッシュされる。
同様にV操作でスタックの一番上のIDがポップされ、そのIDのスレッドが再スタートされる。
このスタック実装が与えられたとき、クリティカルセクションにいる敵対的なライターが、
セマフォを解放する前に、セマフォでブロックしてきている別のライターを単に待つ可能性がある。

このシナリオでは、2つのライターの間で、制御が行ったり来たりしているので、待っているリーダは永久に待たされるかもしれない。

LIFOsタックより、FIFOキューを使うほうが直感的に見えるかもしれないが、そのようなスタックを使うことは間違っていないし、PおよびV操作のセマンティックに違反するものではない。

*/
