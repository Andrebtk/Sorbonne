#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sched.h>

#define LONGTIME 8E8
void ProcLong(int *);
void ProcCourt(int *);

// Exemple de processus long (une simple bouble),
// Chaque processus long cr�e a son tour 4 processus courts
//
void ProcLong(int *pid) {
  long i;
  static int cpt = 0;

  for (i=0;i<LONGTIME;i++) {
    if (i%(long)(LONGTIME/4) == 0)  {
      int *tcpt = (int *) malloc(sizeof(int));
      *tcpt = cpt;
      CreateProc((function_t)ProcCourt,(void *)tcpt, 10);
      cpt++;
    }
    if (i%(long)(LONGTIME/100) == 0)
      printf("Proc. Long %d - %ld\n",*pid, i);
  }
  printf("############ FIN LONG %d\n\n", *pid );
}


// Processus court
void ProcCourt(int *pid) {
  long i;

  for (i=0;i<LONGTIME/10;i++)
    if (i%(long)(LONGTIME/100) == 0)
      printf("Proc. Court %d - %ld\n",*pid, i);
  printf("############ FIN COURT %d\n\n", *pid );
}




// Exemples de primitive d'election definie par l'utilisateur
// Remarques : les primitives d'election sont appel�es directement
//             depuis la librairie. Elles ne sont app�l�es que si au
//             moins un processus est � l'etat pret (RUN)
//             Ces primitives manipulent la table globale des processus
//             d�finie dans sched.h


// Election al�atoire
int RandomElect(void) {
  int i;

  printf("RANDOM Election !\n");

  do {
    i = (int) ((float)MAXPROC*rand()/(RAND_MAX+1.0));
  } while (Tproc[i].flag != RUN);

  return i;
}


// Election de SJF "Shortest Job Fisrt"
int SJFElect(void) {
	int p = -1;
	double p_duration = 1.0e+34;  // initialisation à une valeur très grande

	printf("SJFElect Election !\n");


	// Parcours de tous les processus pour trouver celui avec la durée la plus courte
	for(int i=0; i<MAXPROC; i++) {
		if( (Tproc[i].flag == RUN) && (Tproc[i].duration < p_duration)) {
			p = i;
			p_duration = Tproc[i].duration;
		}
	}

	return p; // retourne l’indice du processus élu
}

/*
int ApproxSJF(void) {
	int p = -1;
	double min_cpu = 1.0e+34;

	printf("ApproxSJF Election !\n");

	// Élection du processus RUN ayant le ncpu le plus bas
	for(int i=0; i<MAXPROC; i++) {
		if((Tproc[i].flag == RUN) && (Tproc[i].ncpu < min_cpu)) {
			p = i;
			min_cpu = Tproc[i].ncpu;
		}
	}

	return p;
}
*/

// Approximation SJF
int ApproxSJF(void) {
	int p = -1;
	double best_prio = MINPRIO -1;
	
	printf("ApproxSJF Election !\n");

	// Élection du processus RUN ayant la priorité la plus élevée
	for(int i=0; i<MAXPROC; i++) {
		if((Tproc[i].flag == RUN) && (Tproc[i].prio > best_prio)) {
			p = i;
			best_prio = Tproc[i].prio;
		}
	}


	// Augmenete la priorité des processus non élus pour éviter la famine
	for(int i=0; i<MAXPROC; i++) {
		if(i != p && Tproc[i].prio<MAXPRIO){
			Tproc[i].prio++;
		}
	}

	// Diminue la priorité du processus elu
	if(p != -1 && Tproc[p].prio > MINPRIO) {
		Tproc[p].prio--;
	}
	

	return p;	
}



int main (int argc, char *argv[]) {
  int i;
  int *j;  

  // Cr�er les processus long
  for  (i = 0; i < 2; i++) {
    j = (int *) malloc(sizeof(int));
    *j= i;
    CreateProc((function_t)ProcLong,(void *)j, 80);
  }



  // Definir une nouvelle primitive d'election avec un quantum de 0.5 seconde
  SchedParam(NEW, 0.5, ApproxSJF);

  // Lancer l'ordonnanceur en mode non "verbeux"
  sched(0);     

  // Imprimer les statistiques
  PrintStat();

  return EXIT_SUCCESS;

}
