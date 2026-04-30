#include <stdio.h>
#include <stdbool.h>

#define MAXN 30

int boardSize, maxQueensCount = 0                           ;

int currentPlacement[MAXN]                                  ;
int bestPlacement[MAXN]                                     ;

bool usedColumn[MAXN]                                       ;
bool usedDiag1[2 * MAXN]                                    ;
bool usedDiag2[2 * MAXN]                                    ;

void saveBestSolution(int count)                            {
    if (count > maxQueensCount)                             {
        maxQueensCount = count                              ;
        for (int i = 0; i < boardSize; i++)                 {
            bestPlacement[i] = currentPlacement[i]          ;
                                                            }
                                                            }
                                                            }

void search(int row, int count)                             {
    if (row == boardSize)                                   {
        saveBestSolution(count)                             ;
        return                                              ;
                                                            }

    for (int col = 0; col <= row; col++)                    {
        if (!usedColumn[col] &&
            !usedDiag1[row - col + boardSize] &&
            !usedDiag2[row + col])                          {

            usedColumn[col] = true                          ;
            usedDiag1[row - col + boardSize] = true         ;
            usedDiag2[row + col] = true                     ;

            currentPlacement[row] = col                     ;

            search(row + 1, count + 1)                      ;

            usedColumn[col] = false                         ;
            usedDiag1[row - col + boardSize] = false        ;
            usedDiag2[row + col] = false                    ;
                                                            }
                                                            }

    currentPlacement[row] = -1                              ;
    search(row + 1, count)                                  ;
                                                            }

void printBoard()                                           {
    printf("%d\n", maxQueensCount)                          ;

    for (int i = 0; i < boardSize; i++)                     {
        for (int s = 0; s < boardSize - i - 1; s++)         {
            printf(" ")                                     ;
                                                            }

        for (int j = 0; j <= i; j++)                        {
            if (bestPlacement[i] == j) printf("Q ")         ;
            else printf(". ")                               ;
                                                            }

        printf("\n")                                        ;
                                                            }
                                                            }

int main()                                                  {
    scanf("%d", &boardSize)                                 ;

    for (int i = 0; i < MAXN; i++)                          {
        currentPlacement[i] = -1                            ;
        bestPlacement[i] = -1                               ;
                                                            }

    search(0, 0)                                            ;
    printBoard()                                            ;

    return 0                                                ;
                                                            }