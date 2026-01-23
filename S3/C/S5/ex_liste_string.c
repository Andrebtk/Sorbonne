#include <string.h>
#include <stdlib.h>
#include "liste.h"
#include "devel.h"
#include "fonctions_string.h"


int main(void) {
	Liste* pl = malloc(sizeof(Liste));

	pl->elements = NULL;
	pl->dupliquer=dupliquer_str;
	pl->copier=copier_str;
	pl->detruire=detruire_str;
	pl->afficher=afficher_str;
	pl->comparer=comparer_str;
	pl->ecrire=ecrire_str;
	pl->lire=lire_str;

	char *text1 = "Hello there";
	char *text2 = "Bonjour";
	char *text3 = "Toujour un texte";
	char *t = "Avec chance";

	inserer_debut(pl, (void *)text1);
	inserer_fin(pl, (void *)text2);
	inserer_fin(pl, (void *)text3);
	inserer_place(pl, (void *)t);


	const char* file = "test.txt";
	ecrire_liste(pl, file);
	afficher_liste(pl);
	detruire_liste(pl);

  return 0;
}
