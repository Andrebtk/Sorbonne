#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    if (argc < 3) {
        printf ("Erreur pas assez d'argument \n");
        printf ("usage: %s <n1> <n2>\n", argv[0]);
        return -1;
    }
    int res = 0;
    for (int i=0; i<argc; i++) {
        res += atoi(argv[i]);
    }
    printf("resultat: %d \n", res);
}