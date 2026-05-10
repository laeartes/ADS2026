#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

QueueCircular *initializeQueue(int size)
{
    if (size <= 0)
    {
        return NULL;
    }

    QueueCircular *q = (QueueCircular *)malloc(sizeof(QueueCircular));
    if (q == NULL)
    {
        return NULL;
    }

    q->arr = (int *)malloc(sizeof(int) * size);
    if (q->arr == NULL)
    {
        free(q);
        return NULL;
    }

    q->size = size;
    q->front = 0;
    q->rear = 0;
    q->quantity = 0;
    return q;
}

int queueIsEmpty(QueueCircular *q)
{
    if (q == NULL) // eile nesukurta, tai grazina -1 klaidos koda
    {
        return -1;
    }
    return q->quantity == 0;
}

int queueIsFull(QueueCircular *q)
{
    if (q == NULL)
    {
        return -1; // eile nesukurta, tai grazina -1 klaidos koda
    }
    return q->quantity == q->size;
}

int enqueue(QueueCircular *q, int val)
{
    if (q == NULL || queueIsFull(q))
    {
        return -1;
    }

    q->arr[q->rear] = val;
    q->rear = (q->rear + 1) % q->size;
    q->quantity++;
    return 0;
}

int dequeue(QueueCircular *q, int *val)
{
    if (q == NULL || queueIsEmpty(q) || val == NULL)
    {
        return -1;
    }
    *val = q->arr[q->front];
    q->front = (q->front + 1) % q->size;
    q->quantity--;
    return 0;
}

int dequeueSimple(QueueCircular *q)
{
    if (q == NULL || queueIsEmpty(q))
    {
        return -1;
    }
    q->front = (q->front + 1) % q->size;
    q->quantity--;
    return 0;
}


int queuePeek(QueueCircular *q, int *val)
{
    if (q == NULL || queueIsEmpty(q) || val == NULL)
    {
        return -1;
    }

    *val = q->arr[q->front];
    return 0;
}

int queueGetCount(QueueCircular *q, int *val)
{
    if (q == NULL || val == NULL)
    {
        return -1;
    }

    *val = q->quantity;
    return 0;
}

int queueToString(QueueCircular *q, char **content)
{
    if (q == NULL || content == NULL)
    {
        return -1;
    }

    int memory_needed = 0;

    for (int i = 0; i < q->quantity; ++i)
    {
        int num = q->arr[(q->front + i) % q->size];
        if (num < 0)
        {
            memory_needed++; // sign "-"
        }

        do
        {
            memory_needed++;
            num /= 10;
        } while (num != 0);

        if (i != q->quantity - 1)
        {
            memory_needed += 2; // comma and space ", "
        }
    }

    *content = malloc((memory_needed + 1));
    if (*content == NULL)
    {
        return -1;
    }

    if (q->quantity == 0)
    {
        sprintf(*content, "");
        return 0;
    }

    int index = 0;
    for (int i = 0; i < q->quantity; ++i)
    {
        int num = q->arr[(q->front + i) % q->size];

        if (i == q->quantity - 1)
        {
            sprintf(*content + index, "%d", num);
        }
        else
        {
            index += sprintf(*content + index, "%d, ", num);
        }
    }
    return 0;
}

QueueCircular *queueCopy(QueueCircular *original)
{
    if (original == NULL)
    {
        return NULL;
    }

    QueueCircular *copy = initializeQueue(original->size);
    if (copy == NULL)
    {
        return NULL;
    }

    copy->front = original->front;
    copy->quantity = original->quantity;
    copy->rear = original->rear;
    copy->arr = malloc(sizeof(int) * original->size);

    for (int i = 0; i < original->size; ++i)
    {
        copy->arr[i] = original->arr[i];
    }
    return copy;
}

int queueMakeEmpty(QueueCircular *q)
{
    if (q == NULL)
    {
        return -1;
    }

    while(!queueIsEmpty(q))
    {
        dequeueSimple(q);
    }
}

void queueDestroy(QueueCircular **q)
{
    if (q == NULL || *q == NULL)
    {
        return;
    }

    free((*q)->arr);
    free(*q);
    *q = NULL;
}