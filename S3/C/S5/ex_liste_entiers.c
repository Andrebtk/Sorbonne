
#include <stdlib.h>
#include "liste.h"
#include "devel.h"
#include "fonctions_entiers.h"

int main(void) {
	PListe p1 = malloc(sizeof(Liste));

	p1->elements = NULL;
	p1->dupliquer = dupliquer_int;
	p1->copier = copier_int;
	p1->detruire = detruire_int;
	p1->afficher = afficher_int;
	p1->comparer = comparer_int;
	p1->ecrire = ecrire_int;
	p1->lire = lire_int;

	int a = 12;
	int b = 15;
	int c = 30;

	inserer_debut(p1, (void *)&a);
	inserer_debut(p1, (void *)&b);
	inserer_debut(p1, (void *)&c);
	inserer_fin(p1,(void*)&c);

	afficher_liste(p1);
	detruire_liste(p1);
	

	
	return 0;
}
