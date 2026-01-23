#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arbre_lexicographique.h"
#include "liste.h"
#include "abr.h"

int main(int argc, char **argv) {

	if (argc != 3) {
		printf ("<usage> ./comp_abr <mot a chercher> <nombre de repetitions> \n");
		return -1;
	}
	printf("Pour %d recherches:\n", atoi(argv[2]));


	PNoeud n = lire_dico("french_za");
	Lm_mot *list = lire_dico_Lmot("french_za");
	
	clock_t begin = clock();
	for (int i=0; i<atoi(argv[2]); i++) {
		Lm_mot *res = chercher_Lm_mot (list, argv[1]);
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\t-Temps pour arbre binaire de recherche: %.5f\n", time_spent);


	begin = clock();
	for (int i=0; i<atoi(argv[2]); i++) {
		int res = rechercher_mot(n, argv[1]);
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\t-Temps pour arbre lexicographique: %.5f\n", time_spent);



}
