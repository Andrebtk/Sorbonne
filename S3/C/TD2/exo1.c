#include <stdio.h>
#include <stdlib.h>

#define DIM1 5
#define DIM2 6


void initTab (char tab[DIM1][DIM2]) {
    for (int i=0; i<DIM1; i++) {
        for (int j=0; j<DIM2; j++) {
            tab[i][j] = 0;
        }
    }
}

void initTab2 (char *tab) {
     for (int i=0; i<DIM1; i++) {
        for (int j=0; j<DIM2; j++) {
            tab[i*DIM2 + j] = 0;
        }
    }
}

int main () {
    char tab2D[DIM1][DIM2];

    char *tab = malloc(sizeof(char) * (DIM1 * DIM2));
    initTab (tab2D);
    initTab2 (tab);
    
    free (tab);
    return 0;
}