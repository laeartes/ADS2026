#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "deque.h"
#include "queue.h"

char *formatTime(int minutes)
{
    int hours = minutes / 60;
    int mins = minutes % 60;
    char *buffer = malloc(20);
    snprintf(buffer, 20, "%d val. %d min.", hours, mins);
    return buffer;
}

typedef struct
{
    int dirbtosMinutes;
    int totalMinutes;
    int tvarkymoGreitis;
    bool tvarkoDokumentus;
    bool priimaStudenta;
} Darbuotoja;

void simulate(int darbuotoja1Greitis,
              int darbuotoja2Greitis,
              double atvykimoTikimybe,
              int priemimoLaikas,
              int simuliacijosLaikas)
{
    int seed = time(NULL);
    srand(seed);
    printf("Simuliacija pradedama su sėklyte: %d\n", seed);

    Darbuotoja darbuotoja1 = {0, 0, darbuotoja1Greitis, false, false};
    Darbuotoja darbuotoja2 = {0, 0, darbuotoja2Greitis, false, false};

    Deque *dekas = createDeque(simuliacijosLaikas);
    QueueCircular *queue = initializeQueue(simuliacijosLaikas);
    for (int i = 0; i < simuliacijosLaikas; i++)
    {
        if ((double)rand() / RAND_MAX < atvykimoTikimybe)
        {
            enqueue(queue, priemimoLaikas);
        }

        if (darbuotoja1.priimaStudenta)
        {
            darbuotoja1.dirbtosMinutes++;
            if (darbuotoja1.dirbtosMinutes >= priemimoLaikas)
            {
                darbuotoja1.priimaStudenta = false;
                darbuotoja1.totalMinutes += darbuotoja1.dirbtosMinutes;
                insertBack(dekas, 0);
                darbuotoja1.dirbtosMinutes = 0;
            }
        }
        else if (!queueIsEmpty(queue))
        {
            dequeueSimple(queue);
            darbuotoja1.priimaStudenta = true;
        }
        else if (darbuotoja1.tvarkoDokumentus)
        {
            darbuotoja1.dirbtosMinutes++;
            if (darbuotoja1.dirbtosMinutes >= darbuotoja1.tvarkymoGreitis)
            {
                darbuotoja1.tvarkoDokumentus = false;
                darbuotoja1.totalMinutes += darbuotoja1.dirbtosMinutes;
                darbuotoja1.dirbtosMinutes = 0;
            }
        }
        else if (!isEmpty(dekas))
        {
            removeFront(dekas);
            darbuotoja1.tvarkoDokumentus = true;
        }

        if (darbuotoja2.priimaStudenta)
        {
            darbuotoja2.dirbtosMinutes++;
            if (darbuotoja2.dirbtosMinutes >= priemimoLaikas)
            {
                darbuotoja2.priimaStudenta = false;
                darbuotoja2.totalMinutes += darbuotoja2.dirbtosMinutes;
                insertBack(dekas, 0);
                darbuotoja2.dirbtosMinutes = 0;
            }
        }
        else if (!queueIsEmpty(queue))
        {
            dequeueSimple(queue);
            darbuotoja2.priimaStudenta = true;
        }
        else if (darbuotoja2.tvarkoDokumentus)
        {
            darbuotoja2.dirbtosMinutes++;
            if (darbuotoja2.dirbtosMinutes >= darbuotoja2.tvarkymoGreitis)
            {
                darbuotoja2.tvarkoDokumentus = false;
                darbuotoja2.totalMinutes += darbuotoja2.dirbtosMinutes;
                darbuotoja2.dirbtosMinutes = 0;
            }
        }
        else if (!isEmpty(dekas))
        {
            removeFront(dekas);
            darbuotoja2.tvarkoDokumentus = true;
        }
    }

    printf("Darbuotoja 1 užimtumas: %.2f%%\n", (double)darbuotoja1.totalMinutes / simuliacijosLaikas * 100);
    printf("Darbuotoja 2 užimtumas: %.2f%%\n", (double)darbuotoja2.totalMinutes / simuliacijosLaikas * 100);

    int papildomasLaikas = 0;
    for (int i = 0; i < getCount(dekas); i++)
    {
        if (darbuotoja1.tvarkoDokumentus)
        {
            darbuotoja1.dirbtosMinutes++;
            if (darbuotoja1.dirbtosMinutes >= darbuotoja1.tvarkymoGreitis)
            {
                darbuotoja1.tvarkoDokumentus = false;
                papildomasLaikas += darbuotoja1.dirbtosMinutes;
                darbuotoja1.dirbtosMinutes = 0;
            }
        }
        else if (!isEmpty(dekas))
        {
            removeFront(dekas);
            darbuotoja1.tvarkoDokumentus = true;
        }

        if (darbuotoja2.priimaStudenta)
        {
            darbuotoja2.dirbtosMinutes++;
            if (darbuotoja2.dirbtosMinutes >= priemimoLaikas)
            {
                darbuotoja2.priimaStudenta = false;
                darbuotoja2.totalMinutes += darbuotoja2.dirbtosMinutes;
                insertBack(dekas, 0);
                darbuotoja2.dirbtosMinutes = 0;
            }
        }
        else if (!queueIsEmpty(queue))
        {
            dequeueSimple(queue);
            darbuotoja2.priimaStudenta = true;
        }
        else if (darbuotoja2.tvarkoDokumentus)
        {
            darbuotoja2.dirbtosMinutes++;
            if (darbuotoja2.dirbtosMinutes >= darbuotoja2.tvarkymoGreitis)
            {
                darbuotoja2.tvarkoDokumentus = false;
                papildomasLaikas += darbuotoja2.dirbtosMinutes;
                darbuotoja2.dirbtosMinutes = 0;
            }
        }
        else if (!isEmpty(dekas))
        {
            removeFront(dekas);
            darbuotoja2.tvarkoDokumentus = true;
        }
    }

    char *formattedTime = formatTime(papildomasLaikas);

    printf("Papildomas laikas prašymų tvarkymui: %s\n", formattedTime);
    free(formattedTime);
}