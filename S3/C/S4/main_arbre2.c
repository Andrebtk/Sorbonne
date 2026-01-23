#include <stdio.h>
#include <stdlib.h>
#include "arbre_lexicographique.h"

int main(int argc, char **argv){
	
	if (argc != 3) {
		printf ("<usage> ./main_arbre2.c <mot a chercher> <nombre de repetitions> \n");
		return -1;
	}


	PNoeud n = lire_dico("french_za");
	
	
	for (int i=0; i<atoi(argv[2]); i++) {
		int res = rechercher_mot(n, argv[1]);
		printf("Trouver %d \n", res);
	}
	return 0;
}
