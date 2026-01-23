#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _chaine Animal;
struct _chaine {
    int x;
    int y;
    float energie;
    int dir[2];

    Animal *suivant;
};


Animal *creer_animal (int x, int y, float energie) {
    Animal *new = malloc(sizeof(Animal));
    assert (new != NULL);

    new->x = x;
    new->y = y;
    new->energie = energie;
    new->dir[0] = (rand() % 2) -1;
    new->dir[1] = (rand() % 2) -1;

    return new;
}

unsigned int compte_animal_rec (Animal *la) {
    if (la == NULL) {
        return 0;
    }
    return 1 + compte_animal_rec (la->suivant);
}

unsigned int compte_animal_it (Animal *la) {
    unsigned int res = 0;

    while (la != NULL) {
        res++;
        la=la->suivant;
    }
    return res;
}

Animal *ajouter_en_tete_animal (Animal *list, Animal *animal) {
    assert (animal != NULL);

    animal->suivant = list;
    return animal;
}

void affichage (Animal *listProies, Animal *listPredateurs, int tailleX, int tailleY) {
    char jeux[tailleX*tailleY];

    for (int i = 0; i<tailleX; i++) {
        for (int j =0; j<tailleY; j++) {
            jeux[i*tailleY + j] = ' ';
        }
    }
    
    printf ("Nb Proies (*): \t\t %d \n", compte_animal_rec(listProies));
    printf ("Nb predateurs (O): \t %d \n", compte_animal_rec(listPredateurs));


    // Proies
    while (listProies != NULL) {
        jeux[listProies->x*tailleY + listProies->y] = '*';
        listProies=listProies->suivant;
    }

    // Predateur
    while (listPredateurs != NULL) {
        jeux[listPredateurs->x*tailleY + listPredateurs->y] = 'O';
        listPredateurs=listPredateurs->suivant;
    }

    printf ("+");
    for (int i=0; i<tailleY; i++) {
        printf ("-");
    }
    printf ("+\n");

    for (int i = 0; i<tailleX; i++) {
        printf ("|");
        for (int j = 0; j<tailleY; j++) {
            int val = i*tailleY +j;
            printf("%c", jeux[val]);
        }
        printf ("|\n");
    }

    printf ("+");
    for (int i=0; i<tailleY; i++) {
        printf ("-");
    }
    printf ("+\n");
}

int main () {
    Animal *a1 = creer_animal (1,2,1);
    Animal *a2 = creer_animal (2,2,0);
    Animal *a3 = creer_animal (4,2,1);
    Animal *a4 = creer_animal (3,5,-1);
    Animal *a5 = creer_animal (0,3,1);
    
    //Proies
    a5->suivant = a4;
    a4->suivant = NULL;
    
    // Predateur
    a3->suivant = a2;
    a2->suivant = a1;
    a1->suivant = NULL;

    affichage (a5, a3, 5, 10);

}