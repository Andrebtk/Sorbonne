#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"

float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
  assert (x>=0 && x<SIZE_X);
  assert (y>=0 && y<SIZE_Y);

  Animal *elem = creer_animal(x,y,energie);
  
  elem->suivant = *liste_animal;
  *liste_animal=elem;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
	if (animal == NULL || *liste == NULL) return;


	if (*liste == animal) {
		Animal *tmp = *liste;
		*liste = (*liste)->suivant;
		tmp->suivant = NULL;
		free(tmp);
		return;
	}


	Animal *current = *liste;
	while (current != NULL && current->suivant != animal) {
		current = current->suivant;
	}

	if (current != NULL && current->suivant == animal) {
		Animal *tmp = current->suivant;
		current->suivant = tmp->suivant;
		tmp->suivant = NULL; 
		free(tmp);
	}

	return;
}


/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
	Animal* tmp;
	while(liste) {
		tmp = liste->suivant;
		free(liste);
		liste=tmp;
	}

	return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}


/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; i++) {
    for (j = 0; j < SIZE_Y; j++) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; j++) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; i++) {
    printf("|");
    for (j = 0; j < SIZE_Y; j++) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; j++) {
    printf("-");
  }
  printf("+\n");

  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);

  printf("Nb proies : %d\tNb predateurs : %d\n", nbproie, nbpred);
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    while(la) {
		if((rand()/(float)RAND_MAX)<p_ch_dir){
			la->dir[0] = rand()%3-1;
			la->dir[1] = rand()%3-1;
		}
		la->x = (SIZE_X + la->x + la->dir[0]) % SIZE_X;
		la->y = (SIZE_Y + la->y + la->dir[1]) % SIZE_Y;
		la = la->suivant;
	}

}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
	Animal *tmp = *liste_animal;
	while (tmp) {
		if ( (rand() / (float)RAND_MAX) <= p_reproduce) {
			ajouter_animal(tmp->x, tmp->y, tmp->energie/2.0, liste_animal);
			tmp->energie = (tmp->energie) / 2.0;
		}
		tmp=tmp->suivant;
	}
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
	if (*liste_proie == NULL) return;

	Animal *tmp = *liste_proie;

	bouger_animaux (tmp);


	while (tmp) {
		tmp->energie -= 1;

		if (monde[tmp->x][tmp->y] > 0) {
			tmp->energie = tmp->energie + monde[tmp->x][tmp->y];
			monde[tmp->x][tmp->y] = temps_repousse_herbe;
		}

		if (tmp->energie <= 0) {
			Animal *to_remove = tmp;
			tmp = tmp->suivant;
			enlever_animal(liste_proie, to_remove);
		} else {
			tmp = tmp->suivant;
		}
	}
	
	reproduce (liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
	while (l != NULL) {
		
		if ( (l->x==x) && (l->y==y)) {
			return l;
		}
		l= l->suivant;
	}
	return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
	if (*liste_predateur == NULL) return;
	
	Animal *tmp_predateur = *liste_predateur;
	Animal *tmp_proie = *liste_proie;
	Animal *predator_remove = NULL;

	bouger_animaux (*liste_predateur);
	
	while (tmp_predateur) {
		tmp_predateur->energie -= 1;
		
		Animal *manger = animal_en_XY (*liste_proie, tmp_predateur->x, tmp_predateur->y);
		
		while (manger != NULL) {
            tmp_predateur->energie += manger->energie;
            enlever_animal(liste_proie, manger);

            // After removing the prey, set manger to NULL or fetch the next prey
            manger = animal_en_XY(*liste_proie, tmp_predateur->x, tmp_predateur->y);
        }
		

		if (tmp_predateur->energie < 0){ //Le prédateur meurt si son énergie est inférieur à 0.
			Animal* tmp = tmp_predateur;
			tmp_predateur = tmp_predateur->suivant;
			enlever_animal(liste_predateur, tmp);
		}else{
			tmp_predateur = tmp_predateur->suivant;
		}
	}

	reproduce (liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
	for (int i=0; i < SIZE_X; i++) {
		for (int j=0; j < SIZE_Y; j++) {
			monde[i][j]++;
		}
	}
}

void ecrire_ecosys (const char *mon_fichier, Animal *liste_predateur, Animal *liste_proie) {
	FILE *f = fopen(mon_fichier, "w");
	fprintf(f, "<proies>\n");
	Animal *tmp = liste_proie;

	while (tmp) {
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n", tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
		tmp = tmp->suivant;
	}
	fprintf(f,"</proies>\n");
	fprintf(f, "<predateurs>\n");

	tmp = liste_predateur;
	while (tmp) {
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n", tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
		tmp = tmp->suivant;
	}
	fprintf(f, "</predateurs>\n");
	fclose(f);
}

void lire_ecosys (const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie) {
	FILE *f = fopen (nom_fichier, "r");
	
	char longeur[256];
	int x,y;
	float energie;
	int dir[2];
	int proie=0;
	int predateur=0;
	
	while (fgets(longeur, 256,f)){
		if (strcmp(longeur, "<proies>\n") ==0) proie=1;
		if (strcmp(longeur, "</proies>\n")==0) proie=0;

		if (strcmp(longeur, "<predateurs>\n")==0) predateur=1;
		if (strcmp(longeur, "</predateurs>\n")==0) predateur=0;

		if (proie==1 || predateur ==1) {
			sscanf(longeur, "x=%d y=%d dir =[%d %d] e=%f", &x, &y, &dir[0], &dir[1], &energie);
			Animal *na = malloc(sizeof(Animal));
			na->x =x;
			na->y = y;
			na->energie = energie;
			na->dir[0] = dir[0];
			na->dir[1] = dir[1];
			na->suivant = NULL;

			if (predateur == 1) {
				na->suivant = *liste_predateur;
				(*liste_predateur) = na;
			} else {
				na->suivant = *liste_proie;
				(*liste_proie) = na;
			}
		}
	}
	fclose(f);
}

