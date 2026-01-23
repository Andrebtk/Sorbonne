#include <stdio.h>

int main(int argc, char **argv) {
    if (argc == 1) {
        printf ("Erreur personne a saluer \n");
        printf ("usage: %s <nom>\n", argv[0]);
        return -1;
    }
    
    for (int i=1; i<argc; i++) {
        printf("%s \n", argv[i]);
    }
}