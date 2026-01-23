#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


int main() {
    int i;
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    int energie=10;
    
    for (int i=0; i<20; i++) {
        ajouter_animal((rand()%SIZE_X), (rand()%SIZE_Y), energie, &liste_proie);
    }

    for (int i=0; i<20; i++) {
        ajouter_animal((rand()%SIZE_X), (rand()%SIZE_Y), energie, &liste_predateur);
    }

    int nbproie=compte_animal_it(liste_proie);
    int nbpred=compte_animal_it(liste_predateur);

    printf("Nb proies : %d\tNb predateurs : %d\n", nbproie, nbpred);

    ecrire_ecosys ("data.txt", liste_predateur, liste_proie);

    Animal *liste_proie2 = NULL;
    Animal *liste_predateur2 = NULL;

    lire_ecosys("data.txt", &liste_predateur2, &liste_proie2);

    printf("%d %d \n",compte_animal_it(liste_proie2), compte_animal_it(liste_predateur2) );

    liberer_liste_animaux(liste_predateur);
    liberer_liste_animaux(liste_proie);

    liberer_liste_animaux(liste_predateur2);
    liberer_liste_animaux(liste_proie2);
}