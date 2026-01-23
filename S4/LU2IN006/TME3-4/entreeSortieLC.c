/*
 * Projet : Mini-Projet 2 : Gestion d’une bibliotheque
 * Auteurs : 
 *   - Andre Bertok (21204512)
 *   - Olivier Huang (21206369)
 */
#include "entreeSortieLC.h"

//Fonction qui permet de lire les n premières lignes du fichier "nomfic" (Liste chainée)
Biblio* charger_n_entrees(char* nomfic, int n) {
	FILE *f = fopen(nomfic, "r");

	if(f == NULL) {
		printf("Erreur: Impossible d'ouvrir le fichier %s\n", nomfic);
		return NULL;
	}

	char buffer[555];
	int num;
	char titre[255];
	char auteur[255];
	Biblio* new = creer_biblio();
	
	for(int i=0; i<n; i++){
	 	fgets(buffer, 555, f);
 		sscanf(buffer, "%d %s %s",&num, titre, auteur);
	 	inserer_en_tete(new, num, titre, auteur);
	}
	fclose(f);

	return new;
} 

//Fonction qui stock dans un fichier "nomfic" la bibliothèque b (Liste chainée)
void enregistrer_biblio(Biblio *b, char* nomfic) {
	FILE *f = fopen(nomfic, "w");

	if(f == NULL) {
		printf("Erreur: Impossible d'ouvrir le fichier %s\n", nomfic);
		return;
	}

	Livre* t = b->L;
	while(t) {
		fprintf(f,"%d %s %s\n",t->num, t->titre, t->auteur);
		t=t->suiv;
	}
	
	fclose(f);
}


