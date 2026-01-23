#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "abr.h"

int main(int argc, char **argv){
	if (argc != 3) {
		printf ("<usage> ./main_abr <mot a chercher> <nombre de repetitions>\n");
		return -1;
	}

	Lm_mot *list = lire_dico_Lmot("french_za");

	for (int i=0; i<atoi(argv[2]); i++) {
		Lm_mot *res = chercher_Lm_mot (list, argv[1]);
		printf("%s \n", res->mot);
	}
	return 0;
}
