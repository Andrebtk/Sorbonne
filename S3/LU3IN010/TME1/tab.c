#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void InitTab(int *tab, int size) {
    for (int i=0; i<size; i++) {
        tab[i] = rand() % (10);
    }
}

void PrintTab(int* tab, int size) {
    for (int i=0; i<size; i++) {
        printf("tab[%d]: %d \n", i, tab[i]);
    }
    printf("\n");
}

int SumTab(int *tab, int size) {
    int res = 0;
    for (int i=0; i<size; i++) {
        res += tab[i];
    }
    return res;
}

int MinSumTab(int *min, int *tab, int size) {

    int m = tab[0];

    for (int i=1; i<size; i++) {
        if(tab[i] < m) {
            m = tab[i];
        }
    }
    *min = m;

    return SumTab(tab, size);
}

void PrintMem() {
    struct rusage usage;

    getrusage(RUSAGE_SELF, &usage);

    printf("ru_maxrss: %ld\n", usage.ru_maxrss);
}