#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tab.h"

int main() {
    srand(time(NULL)); 
    int pileTab[NMAX];
    int *tasTab = malloc(sizeof(int) * NMAX);

    PrintMem();
    InitTab(pileTab, NMAX);
    PrintMem();
    //PrintTab(pileTab, NMAX);
    int min;
    printf("Sum: %d\n", MinSumTab(&min, pileTab, NMAX));
    printf("Min: %d\n", min);

    printf("\n== = ==\n\n");
    PrintMem();
    InitTab(tasTab, NMAX);
    PrintMem();
    //PrintTab(tasTab, NMAX);
    int min2;
    printf("Sum: %d\n", MinSumTab(&min2, tasTab, NMAX));
    printf("Min: %d\n", min2);

}