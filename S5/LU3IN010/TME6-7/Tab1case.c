/* Diffusion tampon 1 case */

  #include <stdio.h> 
  #include <unistd.h> 
  #include <stdlib.h> 
  #include <signal.h> 
  #include <libipc.h>

  #define NBSHEM        2
  



/************************************************************/

/* definition des parametres */ 

  #define NE          2     /*  Nombre d'emetteurs         */ 
  #define NR          5     /*  Nombre de recepteurs       */ 

/************************************************************/

/* definition des semaphores */ 
	#define MUTEXNBREC    0
	#define EMET          1
	#define RECEP         2
	// A completer (?)
        
/************************************************************/

/* definition de la memoire partagee */ 
	typedef struct {
		int nb_recepteurs;
		int donnes;
	} t_segpart;

	t_segpart *sp; 
	// A completer (?)

/************************************************************/

/* variables globales */ 
    int emet_pid[NE], recep_pid[NR]; 

/************************************************************/

/* traitement de Ctrl-C */ 

  void handle_sigint(int sig) { 
      int i;
      for (i = 0; i < NE; i++) kill(emet_pid[i], SIGKILL); 
      for (i = 0; i < NR; i++) kill(recep_pid[i], SIGKILL); 
      det_sem(); 
      det_shm((char *)sp); 
  } 

/************************************************************/

/* fonction EMETTEUR */ 
  	void EMETTEUR() {
		while(1) {

			P(EMET);
			sp->donnes = rand() % 101;
			printf("EMETTEUR: donnes: %d\n", sp->donnes);
			
			for(int i=0; i<NR; i++) {
				V(RECEP + i);
			}
		}
	}


	// A completer - contient les instructions executees
	// par un emetteur

/************************************************************/

/* fonction RECEPTEUR */ 

	void RECEPTEUR(int i) {
		
		while(1) {
			int donnes;
			
			P(RECEP + i);
			donnes = sp->donnes;
			printf("RECEPTEUR donnes: %d\n", donnes);

			P(MUTEXNBREC);
			sp->nb_recepteurs++;
			if(sp->nb_recepteurs == NR) {
				printf("Tout les RECEPTEUR on lue la donnnes\n");
				sp->nb_recepteurs = 0;
				V(EMET);
			}
			V(MUTEXNBREC);
			
		}

/************************************************************/

int main() { 
    struct sigaction action;
    int semid;
	/* autres variables (a completer) */
    
    setbuf(stdout, NULL);

/* Creation du segment de memoire partagee */

	if ( (sp = (t_segpart *)init_shm(sizeof(t_segpart) ))== NULL) {
		perror("init_shm");
		exit(1);
	}


/* creation des semaphores */ 
	if((semid = creer_sem(NBSHEM + NR))==-1) {
		perror("creer_sem");
		exit(1);
	}


/* initialisation des semaphores */ 
	init_un_sem(MUTEXNBREC, 1); 
	init_un_sem(EMET, 1);       

	for(int i=0; i<NR; i++) {
		init_un_sem(i+RECEP, 0);
	}
	sp->nb_recepteurs = 0;

/* creation des processus emetteurs */ 
	for(int i = 0; i<NE; i++) {
		printf("Creation Emetteur[%d]\n", i);
		
		int pid = fork();
		if(pid==0) {
			EMETTEUR();
		}

		emet_pid[i]=pid;
	}
	// A completer - les pid des processus crees doivent
        // etre stockes dans le tableau emet_pid (?)

/* creation des processus recepteurs */ 
	for(int i = 0; i<NR; i++) {
		printf("Creation Recepteurs[%d]\n", i);

		int pid = fork();
		if(pid==0) {
			RECEPTEUR(i);
		}

		recep_pid[i]=pid;
	}
	// A completer - les pid des processus crees doivent
        // etre stockes dans le tableau recep_pid (?)

/* redefinition du traitement de Ctrl-C pour arreter le programme */ 

    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handle_sigint;
    sigaction(SIGINT, &action, 0); 
    
    pause();                    /* attente du Ctrl-C  */
    return EXIT_SUCCESS;
} 
