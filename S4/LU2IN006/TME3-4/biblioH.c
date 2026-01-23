/*
 * Projet : Mini-Projet 2 : Gestion d’une bibliotheque
 * Auteurs : 
 *   - Andre Bertok (21204512)
 *   - Olivier Huang (21206369)
 */
#include "biblioH.h"

//Fonction qui calcul la clé associée à un auteur
int fonctionClef(char* auteur) {
	int cle = 0;

	for(int i=0; auteur[i] != '\0'; i++) {
		cle += (int) auteur[i];
	}

	return cle;
}

//Fonction qui créer un livre en format livreH
LivreH* creer_livreH(int num, char* titre, char* auteur) {
	LivreH* new = malloc(sizeof(LivreH));

	if (new == NULL) {
        printf("Erreur: Allocation mémoire échouée\n");
        return NULL;
    }

	new->num = num;
	new->titre = strdup(titre);
	new->auteur = strdup(auteur);
	new->suivant = NULL;

	return new;
}

//Fonction qui libère UN seul livre
void liberer_livreH(LivreH *l){
	if (l==NULL) return;
	free(l->titre);
	free(l->auteur);
	free(l);
}


//Fonction qui créer une bibliothèque vide
BiblioH* creer_biblioH (int m) {
	BiblioH* new = malloc(sizeof(BiblioH));

	if (new == NULL) {
        printf("Erreur: Allocation mémoire échouée\n");
        return NULL;
    }

	new->ne=0;
	new->m = m;
	new->T = malloc(sizeof(LivreH*)*m);

	if (new->T == NULL) {
		printf("Erreur: Allocation mémoire échouée\n");
        return NULL;
	}

	for (int i=0; i<m; i++){
		new->T[i] = NULL;
	}
	
	return new;
}

//Fonction qui libère toute la bibliothèque b
void liberer_biblioH(BiblioH* b) {
	if (b) {
		for (int i = 0; i < b->m; i++) {
			LivreH* courant = b->T[i];
			while (courant) {
				LivreH* tmp = courant->suivant;
				liberer_livreH(courant);
				courant = tmp;
			}
		}
		free(b->T);
		free(b);
	}
}

//Fonction qui calcul la valeur entière utiliser pour la table de hachage
int fonctionHachage(int cle, int m) {
	double A = (sqrt(5)-1)/2;
	return (int) (m*(cle*A - (int) (cle*A) ));
}

//Fonction qui insère en tête le livreH dont les valeures sont passées en arguments
void insererH(BiblioH* b, int num, char* titre, char* auteur) {
	if (b == NULL) return;
	int cle1 = fonctionClef(auteur);
	int cleHachage = fonctionHachage(cle1, b->m);

	LivreH* new =  creer_livreH(num, titre, auteur);

	new->suivant = b->T[cleHachage];
	b->T[cleHachage] = new;
	b->ne++;
	
}

//Fonction qui afficher le livreH l
void afficher_livreH(LivreH* l) {
	if(l) {
		printf("%d %s %s\n", l->num, l->titre, l->auteur);
		afficher_livreH(l->suivant);
	}
}

//Fonction qui affiche tous les ouvrages de la bibliothèque b
void afficher_biblioH(BiblioH *b) {
	if (b==NULL) return;
	for (int i=0; i<b->m; i++) {
		if(b->T[i] != NULL) {
			printf("indice %d: \n", i);
			afficher_livreH(b->T[i]);
			printf("\n\n");
		}
	}
}
//Fonction qui renvoie un BiblioH dont le numero est num
LivreH *recherche_numH(BiblioH *b, int num){
	if (b==NULL) return NULL;
	LivreH* tmp;
	for (int i=0; i<b->m; i++) {
		tmp = b->T[i];
		while (tmp) {
			if (tmp->num == num) 
				return tmp;
			tmp = tmp->suivant;
		}

	}
	return NULL;
}

//Fonction qui renvoie un BiblioH dont le titre est titre
LivreH *recherche_titreH(BiblioH *b, char *titre){
	if (b==NULL) return NULL;
	LivreH* tmp;
	for (int i=0; i<b->m; i++) {
		tmp = b->T[i];
		while (tmp) {
			if (strcmp(tmp->titre, titre)==0) 
				return tmp;
			tmp = tmp->suivant;
		}

	}
	return NULL;
}

//Fonction qui renvoie un BiblioH dont l'auteur est auteur
BiblioH *recherche_auteurH(BiblioH *b, char* auteur) {
	if(b==NULL) return NULL;
	BiblioH* res = creer_biblioH (b->m);
	int cleHachage = fonctionHachage(fonctionClef(auteur), b->m);

	LivreH* tmp = b->T[cleHachage];

	while(tmp) {
		if (strcmp(auteur, tmp->auteur)==0) {
			insererH(res, tmp->num, tmp->titre, tmp->auteur);
		}

		tmp = tmp->suivant;
	}
	return res;
}

//Fonction qui supprime l'ouvrage dont les valeurs sont passées en argument
BiblioH *supprimerH(BiblioH *b, int num, char *titre, char* auteur) {
	if (b==NULL) return NULL;

	int cleHachage = fonctionHachage(fonctionClef(auteur), b->m);
	LivreH* tmp = b->T[cleHachage];
	LivreH* prec = NULL;

	while(tmp) {
		if ((tmp->num==num) && (strcmp(tmp->titre,titre)==0) && (strcmp(tmp->auteur,auteur)==0)) {
			
			if (prec == NULL) {
				b->T[cleHachage] = tmp->suivant;
			} else {
				prec->suivant=tmp->suivant;
			}

			liberer_livreH(tmp);

			b->ne--;
			return b;
		}
		prec = tmp;
		tmp=tmp->suivant;
	}
	return b;
} 
//Fonction qui fusionne deux BiblioH 
BiblioH *fusionH(BiblioH *a, BiblioH *b) {
	if (a==NULL) return NULL;
	if (b==NULL) return a;

	LivreH *tmp;

	for (int i=0; i<b->m; i++) {
		if(b->T[i] != NULL) {
			tmp = b->T[i];
			while(tmp) {
				insererH(a, tmp->num, tmp->titre, tmp->auteur);
				tmp = tmp->suivant;
			}
		}
	}
	liberer_biblioH(b);

	return a;
}

//Fonction qui recherche les ouvrages qui sont en plusieurs exemplaires dans a
BiblioH *recherche_meme_ouvrageH(BiblioH *a) {
	BiblioH* res = creer_biblioH (a->m);
	LivreH* cour;
	LivreH* tmp;
	int count = 0;

	for (int i=0; i<a->m; i++) {
		cour = a->T[i];
		while(cour) {
			tmp=a->T[i];

			while(tmp) {
				if ((strcmp(cour->titre, tmp->titre)==0) && (strcmp(cour->auteur, tmp->auteur)==0) && (tmp != cour)) {
					count=1;
					break;
				}
				tmp = tmp->suivant;
			}

			if(count > 0){
				insererH(res, cour->num, cour->titre, cour->auteur);
				count = 0;
			}

			cour = cour->suivant;
		}
	}
	return res;
}


/*

KEZXDU - xdrwv → Numéros : 3, 544, 2261, 4211
RATCRMEHGJAEKJNQ - udlmeszkllz → Numéros : 9022, 14777, 14855
UBBMLGFHSLOPGS - wmninq → Numéros : 36181, 36247
MGGEGRKHEESIX - ufrlkzmi → Numéros : 99472, 99538, 99662
TLQC - gnesn → Numéros : 99717, 99769
OBUFHP - jbevej → Numéros : 99811, 99846
DJGEYOPXIUHLPPMBKU - joaobakcv → Numéros : 99872, 99906


*/