/*
 * Projet : Mini-Projet 2 : Gestion d’une bibliotheque
 * Auteurs : 
 *   - Andre Bertok (21204512)
 *   - Olivier Huang (21206369)
 */
#ifndef BIBLIOLC
#define BIBLIOLC

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct livre {
	int num;
	char *titre;
	char *auteur;
	struct livre *suiv;
} Livre;

typedef struct {
	Livre *L;
} Biblio;

Livre* creer_livre(int num, char* titre, char* auteur);
void liberer_livre(Livre* l);
Biblio* creer_biblio();
void liberer_biblio(Biblio* b);
void inserer_en_tete (Biblio* b, int num, char* titre, char* auteur);
void afficher_livre(Livre* l);
void afficher_biblio(Biblio* b);

Livre* recherche_num(Livre *l, int num);
Livre* recherche_titre(Livre *l, char *titre);
Biblio* recherche_auteur(Biblio* b, char* auteur);
Biblio *fusion(Biblio *a, Biblio *b);
Biblio *recherche_meme_ouvrage(Biblio *a);

void supprimer(Biblio* b, int num, char* titre, char* auteur);

#endif
