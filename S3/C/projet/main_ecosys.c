#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


int main(void) {
  int energie=30;
  int monde[SIZE_X][SIZE_Y];
/*Création du monde représentant l'état des herbes de l'écosytème*/
  for(int i=0; i<SIZE_X; i++){
    for(int j=0; j<SIZE_Y; j++)
      monde[i][j] = 0;
  }

  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;

  srand(time(NULL));
/*Création de NB_PROIES dans liste_proie et de NB_PREDATEURS dans liste_predateur*/
  for(int i = 0; i<NB_PROIES; i++){
      ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);
  }
    for(int i = 0; i<NB_PREDATEURS; i++){
      ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
  }

  FILE* evol = fopen("Evol_Pop.txt","w");   //Ouvre un fichier pour enregistrer les données de l'évolution
  if(evol == NULL){
    printf("Erreur ouverture %s\n","Evole_Pop.txt");
    return 1;
  }

  int i =0;
  while((liste_proie || liste_predateur) && i<500){
    rafraichir_monde(monde);    //Rafraîchit les herbes dans le monde
    rafraichir_proies(&liste_proie, monde);     //Rafraîchis la liste des proies
    rafraichir_predateurs(&liste_predateur,&liste_proie);   //Rafraîchis la liste des prédateurs
    afficher_ecosys(liste_proie,liste_predateur);   //Affiche l'état de l'état de lécosystème
    usleep(T_WAIT);
    fprintf(evol,"%d %d %d\n", i, compte_animal_it(liste_proie), compte_animal_it(liste_predateur)); //Écris les données de l'itération actuelle sur un fichier
    i++;
  }
  fclose(evol);
  liste_predateur = liberer_liste_animaux(liste_predateur);
  liste_proie = liberer_liste_animaux(liste_proie);
  return 0;
  //gnuplot  puis 'plot "Evol_Pop.txt" using 1:2 with lines title "proies"' et 'replot "Evol_Pop.txt" using 1:3 with lines title "predateurs"'
}

