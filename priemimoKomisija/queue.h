#ifndef QUEUE_H
#define QUEUE_H

typedef struct
{
    int *arr;
    int size, front, rear, quantity;    
} QueueCircular;

QueueCircular *initializeQueue(int size);
int queueIsEmpty(QueueCircular *q);
int queueIsFull(QueueCircular *q);
int enqueue(QueueCircular *q, int val);
int dequeue(QueueCircular *q, int *val);
int dequeueSimple(QueueCircular *q);
int queuePeek(QueueCircular *q, int *val);
int queueGetCount(QueueCircular *q, int *val);
int queueToString(QueueCircular *q, char **content);
void queueDestroy(QueueCircular **q);
int queueMakeEmpty(QueueCircular *q);
QueueCircular *queueCopy(QueueCircular *original);

#endif
