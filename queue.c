#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define QUEUE_SIZE  32

typedef struct queue {
    int front;
    int rear;
    char * arr[QUEUE_SIZE];
} queue_t;

char * peek(queue_t *q) {
    return q->arr[q->front];
}

bool is_empty(queue_t *q) {
    if (q->front == q->rear)
	return 1;
    return 0;
}

bool is_full(queue_t * q) {
    if ((q->rear +1 >= QUEUE_SIZE) && (q->front == 0))
	return 1;

    if (q->rear + 1 == q->front)
	return 1;

    return 0;
}

void enqueue(queue_t *q, char* element) {
    if (!is_full(q)) {
	q->arr[q->rear] = element;
	q->rear++;
	if(q->rear >= QUEUE_SIZE) {
	    q->rear = 0;
	}
    }
    else {
	printf("Queue is full\n");
    }
}

char* dequeue(queue_t *q) {
    char * element = NULL;
    if (!is_empty(q)) {
	element = q->arr[q->front];
	q->front++;
	if (q->front >= QUEUE_SIZE) {
	    q->front = 0;
	}
    }
    else {
	printf("Queue is empty\n");
    }
    return element;
}

int main(int argc, char ** argv) {
    int i,j;
    char lock[5] = {'0','0','0','0','\0'};
    char* lock_state;
    char* lock_state_queue;
    int count = 0;

    queue_t *q = malloc(sizeof(queue_t));
    
    if (q==NULL) {
	printf("No mem\n");
	return -1;
    }

    q->front = 0;
    q->rear = 0;
    
    for(i = 0; i <10; i++) {
	for(j=0;j<4;j++) {
	    lock[j] = lock[j] + 1;
	    if (lock[j] > '9')
		lock[j] = '0';

//	    printf("lock is %s\n",lock);
	    lock_state = malloc(5);
	    strcpy(lock_state,lock);
	    if (!is_full(q)) {
		count++;
		printf("%02d: lock is %s\n",count,lock_state);
		enqueue(q,lock_state);
	    }
	    else
		break;
	}
    }
#if 1
    while (!is_empty(q)) {
	lock_state_queue = dequeue(q);
	printf( "%02d: From queue: %s\n", count,lock_state_queue);
	free(lock_state_queue);
	count--;
    }
#endif
}
