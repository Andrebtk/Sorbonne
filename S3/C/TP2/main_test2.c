#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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

    enlever_animal(&liste_proie, liste_proie->suivant->suivant->suivant);
    enlever_animal(&liste_proie, liste_proie->suivant->suivant);


    enlever_animal(&liste_predateur, liste_predateur);
    enlever_animal(&liste_predateur, liste_predateur->suivant->suivant->suivant);
    enlever_animal(&liste_predateur, liste_predateur->suivant->suivant);
    

    int nbproie=compte_animal_it(liste_proie);
    int nbpred=compte_animal_it(liste_predateur);

    printf("Nb proies : %d\tNb predateurs : %d\n", nbproie, nbpred);

    liberer_liste_animaux(liste_predateur);
    liberer_liste_animaux(liste_proie);
}