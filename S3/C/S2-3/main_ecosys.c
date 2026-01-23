#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000

/*
30
50
*/

int main(void) {
	int monde[SIZE_X][SIZE_Y];

	FILE *res = fopen("Evol_Pop.txt", "w");

	for (int i=0; i < SIZE_X; i++) {
		for (int j=0; j < SIZE_Y; j++) {
			monde[i][j] = 0;
		}
	}
	
	Animal *tete_proies = NULL;
	Animal *tete_predateur = NULL;
	int energie = 30;

	for (int i=0; i<NB_PROIES; i++) {
		ajouter_animal (rand()%SIZE_X,rand()%SIZE_Y, energie, &tete_proies);
		
	}

	for (int i=0; i<NB_PREDATEURS; i++){
		ajouter_animal (rand()%SIZE_X,rand()%SIZE_Y, energie, &tete_predateur);
	}

	int i = 0;
	while ( (tete_proies != NULL || tete_predateur != NULL) && i < 500) {
		rafraichir_monde(monde);    //Rafraîchit les herbes dans le monde
		rafraichir_proies(&tete_proies, monde);     //Rafraîchis la liste des proies
		rafraichir_predateurs(&tete_predateur,&tete_proies);   //Rafraîchis la liste des prédateurs

		afficher_ecosys(tete_proies,tete_predateur);   //Affiche l'état de l'état de lécosystème
		usleep(T_WAIT);
		fprintf(res,"%d %d %d\n", i, compte_animal_it(tete_proies), compte_animal_it(tete_predateur)); //Écris les données de l'itération actuelle sur un fichier
		i++;
	}

	liberer_liste_animaux (tete_proies);
	liberer_liste_animaux (tete_predateur);


	return 0;
}


/*

set terminal pngcairo
set output 'plot.png'
plot "Evol_Pop.txt" using 1:2 with lines title "proies", \
     "Evol_Pop.txt" using 1:3 with lines title "predateurs"

*/