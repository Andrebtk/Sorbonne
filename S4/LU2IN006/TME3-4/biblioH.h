/*
 * Projet : Mini-Projet 2 : Gestion d’une bibliotheque
 * Auteurs : 
 *   - Andre Bertok (21204512)
 *   - Olivier Huang (21206369)
 */
#ifndef BIBLIOH
#define BIBLIOH

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct livreh {
	int clef;
	int num;
	char *titre;
	char *auteur;
	struct livreh *suivant;
} LivreH;

typedef struct table {
	int ne; // nombre d’elements contenus dans la table de hachage 
	int m; // taille de la table de hachage
	LivreH** T; // table de hachage avec resolution des collisions par chainage 
} BiblioH;


int fonctionClef(char* auteur);
int fonctionHachage(int cle, int m);

LivreH* creer_livreH(int num, char* titre, char* auteur);
void liberer_livreH(LivreH* l);
BiblioH* creer_biblioH (int m);
void liberer_biblioH(BiblioH* b);
void insererH(BiblioH* b, int num, char* titre, char* auteur);
void afficher_livreH(LivreH* l);
void afficher_biblioH(BiblioH *b);
LivreH *recherche_numH(BiblioH *b, int num);
LivreH *recherche_titreH(BiblioH *b, char *titre);
BiblioH *recherche_auteurH(BiblioH *b, char* auteur);
BiblioH *supprimerH(BiblioH *b, int num, char *titre, char* auteur);
BiblioH *fusionH(BiblioH *a, BiblioH *b);
BiblioH *recherche_meme_ouvrageH(BiblioH *a);

#endif
