#include <stdio.h>
#include <stdlib.h>
#include "arbre_lexicographique.h"


int main (int argc, char **argv) {

	PNoeud racine = creer_noeud('.');

	// Level 1: Root's children ('a' and 'b')
	racine->fils = creer_noeud('a');
	racine->fils->frere_suivant = creer_noeud('b');

	// Level 2: Children of 'a': 'r' -> 'v'
	PNoeud node_a = racine->fils;
	node_a->fils = creer_noeud('r');
	node_a->fils->frere_suivant = creer_noeud('v');

	// Level 2: Children of 'b': 'a'
	PNoeud node_b = racine->fils->frere_suivant; // 'b'
	node_b->fils = creer_noeud('a');

	// Level 3: Children of 'r': 'b' -> 'i' -> 'l'
	PNoeud node_r = node_a->fils; // 'r'
	node_r->fils = creer_noeud('b');  // 'b' under 'r'
	node_r->fils->frere_suivant = creer_noeud('i'); // 'i' under 'r'
	node_r->fils->frere_suivant->frere_suivant = creer_noeud('l'); // 'l' under 'r'

	// Level 4: Children of 'b' (under 'r'): 'r'
	PNoeud node_b2 = node_r->fils; // 'b'
	node_b2->fils = creer_noeud('r');
	node_b2->fils->fils = creer_noeud('e');
	node_b2->fils->fils->fin_de_mot = fin; // "arbre"

	// Level 4: Children of 'i' (under 'r'): 't'
	PNoeud node_i = node_r->fils->frere_suivant; // 'i'
	node_i->fils = creer_noeud('t');
	node_i->fils->fils = creer_noeud('r');
	node_i->fils->fils->fils = creer_noeud('e');
	node_i->fils->fils->fils->fin_de_mot = fin; // "arbitre"

	// Level 4: Children of 'l' (under 'r'): 'è'
	PNoeud node_l = node_r->fils->frere_suivant->frere_suivant; // 'l'
	node_l->fils = creer_noeud('e');
	node_l->fils->fils = creer_noeud('t');
	node_l->fils->fils->fils = creer_noeud('e');
	node_l->fils->fils->fils->fin_de_mot = fin; // "arbalète"

	// Level 3: Children of 'v': 'i'
	PNoeud node_v = node_a->fils->frere_suivant; // 'v'
	node_v->fils = creer_noeud('i');
	node_v->fils->fils = creer_noeud('a');
	node_v->fils->fils->fils = creer_noeud('t');
	node_v->fils->fils->fils->fils = creer_noeud('e');
	node_v->fils->fils->fils->fils->fils = creer_noeud('u');
	node_v->fils->fils->fils->fils->fils->fin_de_mot = fin; // "aviateur"

	// Level 3: Children of 'a' (under 'b'): 't'
	PNoeud node_a2 = node_b->fils; // 'a' under 'b'
	node_a2->fils = creer_noeud('t');
	node_a2->fils->fils = creer_noeud('e');
	node_a2->fils->fils->fils = creer_noeud('a');
	node_a2->fils->fils->fils->fils = creer_noeud('u');
	node_a2->fils->fils->fils->fils->fin_de_mot = fin; // "bateau"

	// You can now traverse the tree or display the words
	printf("Tree created successfully!\n");


	afficher_dico(racine);


	PNoeud n2 = lire_dico("french_za");
	afficher_dico(n2);

	detruire_dico(racine);
	detruire_dico(n2);
	return 0;
}
