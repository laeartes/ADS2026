#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAXN 30

int boardSize, maxQueensCount = 0                                            ;

int currentPlacement[MAXN]                                                   ;
int bestPlacement[MAXN]                                                      ;

bool usedColumn[MAXN]                                                        ;
bool usedDiag1[2 * MAXN]                                                     ;
bool usedDiag2[2 * MAXN]                                                     ;

enum Mode { FULL, FIRST, HEURISTIC } mode = FULL                             ;   

clock_t startTime                                                            ;
int timeoutMs = -1                                                           ;
long long nodesVisited = 0                                                   ;
bool timeoutReached = false                                                  ;            

FILE *input = NULL                                                           ;

// pagalba
void usage(const char *prog)                                                 {
    fprintf(stderr,
        "Usage: %s [-|input_file] "
        "[-mode fullSearch|firstMatchSearch|heuristic n] "
        "[-timeout milliseconds]\n",
        prog
    )                                                                        ;
                                                                             }

bool checkTimeout()                                                          {
    if (timeoutMs < 0) return false                                          ;

    clock_t now = clock()                                                    ;
    double elapsed = (double)(now - startTime) * 1000.0 / CLOCKS_PER_SEC     ;

    if (elapsed >= timeoutMs)                                                {
        timeoutReached = true                                                ;
        return true                                                          ;
                                                                             }
    return false                                                             ;
                                                                             }

// issaugoti
void saveBestSolution(int count)                                             {
    if (count > maxQueensCount)                                              {
        maxQueensCount = count                                               ;
        for (int i = 0; i < boardSize; i++)                                  {
            bestPlacement[i] = currentPlacement[i]                           ;
                                                                             }
                                                                             }
                                                                             }

// paieska
bool search(int row, int count)                                              {

    if (checkTimeout()) return false                                         ;

    nodesVisited++                                                           ;

    if (row == boardSize)                                                    {
        saveBestSolution(count)                                              ;
        if (mode == FIRST) return true                                       ;
        return false                                                         ;
                                                                             }

    for (int col = 0; col <= row; col++)                                     {
        if (!usedColumn[col] &&
            !usedDiag1[row - col + boardSize] &&
            !usedDiag2[row + col])                                           {

            usedColumn[col] = true                                           ;
            usedDiag1[row - col + boardSize] = true                          ;
            usedDiag2[row + col] = true                                      ;

            currentPlacement[row] = col                                      ;

            if (search(row + 1, count + 1))
                return true                                                  ;

            usedColumn[col] = false                                          ;
            usedDiag1[row - col + boardSize] = false                         ;
            usedDiag2[row + col] = false                                     ;
                                                                             }
                                                                             }

    currentPlacement[row] = -1                                               ;

    if (search(row + 1, count))
        return true                                                          ;

    return false                                                             ;
                                                                             }

// isvestis
void printBoard()                                                            {

    printf("=== RESULT ===\n")                                               ;
    printf("Board size: %d\n", boardSize)                                    ;
    printf("Max queens placed: %d\n", maxQueensCount)                        ;
    printf("Nodes visited: %lld\n", nodesVisited)                            ;

    if (timeoutReached)                                                      {
        printf("STATUS: TIMEOUT\n")                                          ;
        printf("Progress: unknown %%\n")                                     ;
                                                                             }
    else                                                                     {
        printf("STATUS: COMPLETED\n")                                        ;
                                                                             }

    printf("\nBoard:\n")                                                     ;

    for (int i = 0; i < boardSize; i++)                                      {
        for (int s = 0; s < boardSize - i - 1; s++)                          {
            printf(" ")                                                      ;
                                                                             }

        for (int j = 0; j <= i; j++)                                         {
            if (bestPlacement[i] == j) printf("Q ")                          ;
            else printf(". ")                                                ;
                                                                             }

        printf("\n")                                                         ;
                                                                             }
                                                                             }

// argumentai
void parseArgs(int argc, char *argv[])                                       {

    input = stdin                                                            ;

    for (int i = 1; i < argc; i++)                                           {

        if (strcmp(argv[i], "-") == 0)                                       {
            input = stdin                                                    ;
                                                                             }
        else if (argv[i][0] != '-')                                          {
            input = fopen(argv[i], "r")                                      ;
            if (!input)                                                      {
                perror("Failed to open file")                                ;
                exit(1)                                                      ;
                                                                             }
                                                                             } 
        else if (strcmp(argv[i], "-mode") == 0)                              {
            i++                                                              ;
            if (i >= argc) usage(argv[0])                                    ;

            if (strcmp(argv[i], "fullSearch") == 0)                          {
                mode = FULL                                                  ;
                                                                             }
            else if (strcmp(argv[i], "firstMatchSearch") == 0)               {
                mode = FIRST                                                 ;
                                                                             }
            else if (strcmp(argv[i], "heuristic") == 0)                      {
                printf("euristika dar nerealizuota\n")                       ;
                exit(0)                                                      ;
                                                                             }
            else                                                             {
                usage(argv[0])                                               ;
                exit(1)                                                      ;
                                                                             }
                                                                             }
        else if (strcmp(argv[i], "-timeout") == 0)                           {
            i++                                                              ;
            if (i >= argc) usage(argv[0])                                    ;
            timeoutMs = atoi(argv[i])                                        ;
                                                                             }
        else                                                                 {
            usage(argv[0])                                                   ;
            exit(1)                                                          ;
                                                                             }
                                                                             }
                                                                             }                 

int main(int argc, char *argv[])                                             {                 

    if (argc == 1)                                                           {
        usage(argv[0])                                                       ;
        return 1                                                             ;
                                                                             }

    parseArgs(argc, argv)                                                    ;

    if (fscanf(input, "%d", &boardSize) != 1)                                {
        fprintf(stderr, "Invalid input\n")                                   ;
        return 1                                                             ;
                                                                             }

    if (boardSize > MAXN)                                                    {
        fprintf(stderr, "Max N is %d\n", MAXN)                               ;
        return 1                                                             ;
                                                                             }

    for (int i = 0; i < MAXN; i++)                                           {
        currentPlacement[i] = -1                                             ;
        bestPlacement[i] = -1                                                ;
        usedColumn[i] = false                                                ;
                                                                             }

    for (int i = 0; i < 2 * MAXN; i++)                                       {
        usedDiag1[i] = false                                                 ;
        usedDiag2[i] = false                                                 ;
                                                                             }

    printf("=== INPUT ===\n")                                                ;
    printf("Board size: %d\n", boardSize)                                    ;
    printf("Mode: %s\n",
        mode == FULL ? "fullSearch" :
        mode == FIRST ? "firstMatchSearch" : "heuristic")                    ;
    printf("Timeout: %d ms\n\n", timeoutMs)                                  ;

    startTime = clock()                                                      ;

    search(0, 0)                                                             ;

    printBoard()                                                             ;                 

    return 0                                                                 ;
                                                                             }
