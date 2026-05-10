# 1-as lab. darbas

## Eilė realizuota dinaminiu masyvu

## Galimos operacijos
* QueueCircular *initializeQueue(int size) - inicializuoja eilę. Jei grazina NULL - nepavyko alokuoti atminties. 
* int queueIsEmpty(QueueCircular *q) - patikrina, ar eilė tuščia. 1 - tuščia, 0 - netuščia, -1 - neegzistuoja. 
* int queueIsFull(QueueCircular *q) - patikrina, ar eilė pilna. 1 - pilna, 0 - nepilna, -1 - neegzistuoja. 
* int enqueue(QueueCircular *q, int val); - įdeda į eilę elementą. Grąžina klaidos kodą: -1 - klaida, 0 - nėra klaidų.
* int dequeue(QueueCircular *q) - išima eilėje pirmą elementą ir grąžina jį per parametrą. Grąžina klaidos kodą: -1 - klaida, 0 - nėra klaidų.
* int dequeueSimple(QueueCircular *q) - išima eilėje pirmą elementą. Grąžina klaidos kodą: -1 - klaida, 0 - nėra klaidų.
* int queuePeek(QueueCircular *q, int *val) - per parametrą grąžina eilėje pirmą elementą. Grąžina klaidos kodą: -1 - klaida, 0 - nėra klaidų.
* int queueGetCount(QueueCircular *q, int *val) - per parametrą grąžina skaičių elementų. Grąžina klaidos kodą: -1 - klaida, 0 - nėra klaidų.
* QueueCircular *queueCopy(QueueCircular *original) - grąžina rodyklę į kopiją eilės. NULL - jei įvyko klaida. 
* int queueMakeEmpty(QueueCircular *q) - išvalo eilę ir padaro ją tuščia. 
* void queueDestroy(QueueCircular **q) - atlaisvina atmintį, kuri buvo skirta eilei. 

## Naudojimas
1. Darbinėje direktorijoje turėti atsisiuntus`queue.c` bei `queue.h`failus. 
2. Į darbo aplinką duomenų struktūrą įtraukti eilute `#include "queue.h"`.
3. Eilė inicializuojama funkcija initializeQueue() pvz.: `QueueCircular *queue = initializeQueue(10);`. 
4. Eilė sunaikinama funkcija queueDestroy(). 