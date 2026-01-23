#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"


float p_ch_dir=0.5; 
float p_reproduce_proie=0.3; 
float p_reproduce_predateur=0.35; 
int temps_repousse_herbe=-10;


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

/*A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert( (x >= 0 && y >= 0) && (x < SIZE_X && y < SIZE_Y) );
  *liste_animal = ajouter_en_tete_animal(*liste_animal, creer_animal(x,y,energie));
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  if(*liste == NULL)    //Condition si liste vide, sorti direct
    return;
  
  if (*liste == animal){    //Condition si tête de liste == animal, supprime la tête de liste
    Animal* tmp = *liste;
    *liste=(*liste)->suivant;
    free(tmp);
    return;
}

  Animal* lcpy = *liste; 
  while(lcpy->suivant && lcpy->suivant != animal){  //Boucle pour trouver si animal est dans liste et on a crée lcpy pour ne pas perdre la tête de liste
    lcpy = lcpy->suivant;
  }

  if(lcpy->suivant==animal){    //Cas si lcpy->suivant == animal, supprime l'élément.
    Animal* tmp = lcpy->suivant;
    lcpy->suivant = lcpy->suivant->suivant;
    free(tmp);
  }

  return ;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
  Animal* tmp;
  while(liste){ //Boucle parcourant chaque élément de la liste et le libère.
    tmp=liste;
    liste=liste->suivant;
    free(tmp);
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
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
  while(la){    //Boucle parcourant la liste la
    if( (float)rand()/RAND_MAX < p_ch_dir){ //Probabilité p_ch_dir de modifier la direction de déplacement de l'animal
      la->dir[0]=(rand()%3)-1;
      la->dir[1]=(rand()%3)-1;
    }
    //Modifie la position de l'animal (x,y) en fonction de la direction dir tel que 0 <= x < SIZE_X et 0 <= y < SIZE_Y
    la->x=(la->x + la->dir[0] + SIZE_X)%SIZE_X;
    la->y=(la->y + la->dir[1] + SIZE_Y)%SIZE_Y;
    la=la->suivant;
  }

}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  assert(liste_animal); //Fin du programme si liste_animal == NULL
  Animal* ani = *liste_animal;
  while(ani){   //Parcours la liste d'animal. Probabilité à chaque tour de boucle d'ajouter un nouvel animal dans la liste possédant la moitié de l'énergie de l'animal courant puis divise l'énergie de ce dernier par 2
    if((float)rand()/RAND_MAX < p_reproduce){   //Probabilité p_reproduce que l'animal se reproduit
        ajouter_animal(ani->x, ani->y, (ani->energie)/2.0, liste_animal);
        ani->energie /= 2.0;
    }
  ani = ani->suivant;
  }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  bouger_animaux(*liste_proie); //On commence par déplacer tous les animaux de la liste.
  Animal* ani = *liste_proie; //Création de ani pour ne pas perdre la tête de la liste.
  while(ani){   //Parcours la liste.
    ani->energie -= 1;  //Réduit l'énergie de l'animal de 1
    if(monde[ani->x][ani->y] > 0){     //Fait manger les herbes d'une case de monde à la proie se trouvant sur la case correspondante. Récupère de l'energie en fonction du nombre d'herbe disponible, 0 compris. Si une case est consomée, sa valeur passe à temps_repousse_herbe.
      ani->energie += monde[ani->x][ani->y];
      monde[ani->x][ani->y] = temps_repousse_herbe;
    }
    if (ani->energie <= 0){  //La proie meurt si son énergie est inférieur ou égal à 0.
      Animal* tmp = ani;
      ani = ani->suivant;
      enlever_animal(liste_proie, tmp);
    }else{
        ani = ani->suivant;
    }
  }
  reproduce(liste_proie, p_reproduce_proie);    //Faire reproduire les proies.
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    while(l){   //Boucle parcourant la liste l. Vérifie si un animal de la liste se trouve aux coordonnées (x,y) puis retourne cet animal.
      if(l->x == x && l->y == y)
        return l;
      l = l->suivant;
    }
  return NULL; //Si aucun animal se trouve aux coordonnées (x,y).
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur); //On commence par déplacer tous les animaux de la liste.
  Animal* ani = *liste_predateur;   //Création de ani pour ne pas perdre la tête de la liste.
  while(ani){ //Parcours la liste.
    ani->energie -= 1; //Réduit l'énergie de l'animal de 1
    Animal* proie = animal_en_XY(*liste_proie, ani->x, ani->y);
    if (proie){ //le prédateur courant mange la proie (si elle existe) se trouvant sur la même case que lui. Le prédateur courant récupère l'énergie de la proie puis la proie est libéré de sa liste.
      ani->energie += proie->energie;
      enlever_animal(liste_proie, proie);
    }
    if (ani->energie <= 0){ //Le prédateur meurt si son énergie est inférieur ou égal à 0.
      Animal* tmp = ani;
      ani = ani->suivant;
      enlever_animal(liste_predateur, tmp);
    }else{
    ani = ani->suivant;
    }
  }
  reproduce(liste_predateur, p_reproduce_predateur); //Faire reproduire les prédateurs.
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){   //Rajoute de l'herbe sur toutes les cases du monde.
    for(int i=0; i<SIZE_X; i++){
      for(int j=0; j<SIZE_Y; j++)
        monde[i][j] += 1;
  }
}

/*Fonction de chargement de l'écosytème*/
void ecrire_ecosys(const char* nom_fichier, Animal* liste_predateur, Animal* liste_proie){
  FILE* f=fopen(nom_fichier,"w");
  if(f == NULL){
    printf("Erreur ouverture %s\n",nom_fichier);
    return;
  }

  fprintf(f,"<proies>\n");
  Animal* tmp = liste_proie;
  while(tmp){
    fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n",tmp->x,tmp->y,tmp->dir[0],tmp->dir[1],tmp->energie);
    tmp=tmp->suivant;
  }
  fprintf(f,"</proies>\n");

  fprintf(f,"<predateurs>\n");
  tmp = liste_predateur;
  while(tmp){
    fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n",tmp->x,tmp->y,tmp->dir[0],tmp->dir[1],tmp->energie);
    tmp=tmp->suivant;
  }
  fprintf(f,"</predateurs>\n");

  fclose(f);
}

/*Fonction de sauvegarde de l'écosytème*/
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

