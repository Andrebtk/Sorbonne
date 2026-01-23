/* Diffusion tampon N case */

  #include <stdio.h> 
  #include <unistd.h> 
  #include <signal.h> 
  #include <libipc.h>

/************************************************************/

/* definition des parametres */ 

  #define NE          2     /*  Nombre d'emetteurs         */ 
  #define NR          5     /*  Nombre de recepteurs       */ 
  #define NMAX        3     /*  Taille du tampon           */ 

/************************************************************/

/* definition des semaphores */ 
#define EM_CASE_VIDE			0
#define EM_MUTEX 				1
#define SEM_PLEIN				2
#define SEM_MUTEX_CASES 		(SEM_PLEIN + NMAX)


/************************************************************/

/* definition de la memoire partagee */ 
typedef struct {
	int data[NMAX];
	int ind_tete;
	int nb_lecture[NMAX];
} t_segpart;

t_segpart *sp; 
// A completer

/************************************************************/

/* variables globales */ 
int emet_pid[NE], recep_pid[NR]; 

/************************************************************/

/* traitement de Ctrl-C */ 

  void handle_sigint(int sig) 
  { int i;
  	for (i = 0; i < NE; i++) kill(emet_pid[i], SIGKILL); 
	for (i = 0; i < NR; i++) kill(recep_pid[i], SIGKILL); 
	det_sem(); 
	det_shm((char *)sp); 
 
  } 

/************************************************************/

/* fonction EMETTEUR */ 
void EMETTEUR(int i) {
	for(;;) {
		P(EM_CASE_VIDE);

		P(EM_MUTEX);
		int ind = sp->ind_tete;
		sp->ind_tete = (ind + 1) % (NMAX);
		V(EM_MUTEX);

		sp->data[ind] = rand() % 101;
		printf("Emeteur %d a ecrit %d en case %d\n", i, sp->data[ind], ind);

		for(int k=0; k<NR; k++) {
			V(ind+SEM_PLEIN);
		}
	}
}

/************************************************************/

/* fonction RECEPTEUR */ 
void RECEPTEUR(int i) {
	int ind_local = 0;
	for(;;) {
		P(SEM_PLEIN+ind_local);
		

		P(SEM_MUTEX_CASES + ind_local);
		sp->nb_lecture[ind_local] = sp->nb_lecture[ind_local] + 1;
		printf("Le recepteur %d a lu la valeur du tampon[%d]\n", i, ind_local);
		
		if(sp->nb_lecture[ind_local] == NR) {
			printf("Tout les recepteur on lue la valeur de tampon[%d]\n", ind_local);
			sp->nb_lecture[ind_local] = 0;
			V(EM_CASE_VIDE);
		}

		V(SEM_MUTEX_CASES + ind_local);

		ind_local = (ind_local + 1) % (NMAX);
	}
}

/************************************************************/

int main() { 
    struct sigaction action;
	int semid;
    /* autres variables (a completer) */
    
    setbuf(stdout, NULL);

/* Creation du segment de memoire partagee */
if ( (sp = (t_segpart *)init_shm(sizeof(t_segpart)))== NULL) {
	perror("init_shm");
	exit(1);
}	
sp->ind_tete = 0;

/* creation des semaphores */ 
if((semid = creer_sem(2*NMAX + 2))==-1) {
	perror("creer_sem");
	exit(1);
}

/* initialisation des semaphores */ 
init_un_sem(EM_CASE_VIDE, NMAX);			
init_un_sem(EM_MUTEX, 1);					
for(int i=0; i<NMAX; i++) {
	init_un_sem(SEM_PLEIN + i, 0);
}


for(int i=0; i<NMAX; i++) {
	init_un_sem(SEM_MUTEX_CASES + i, 1);
}

//
for (int i=0; i<NMAX; i++){
	sp->nb_lecture[i] = 0;
}


  

/* creation des processus emetteurs */ 
for(int i=0; i<NE; i++) { 
	printf("Creation Emetteur[%d]\n", i);
	
	int pid;
	if((pid = fork()) ==0) {
		EMETTEUR(i);
		return 0;
	}
	emet_pid[i] = pid;
}


/* creation des processus recepteurs */ 
for(int i=0; i<NR; i++) {
	printf("Creation Recepteurs[%d]\n", i);
	
	int pid;
	if((pid = fork())==0){
		RECEPTEUR(i);
		return 0;
	}
	recep_pid[i] = pid;
}
    
/* redefinition du traitement de Ctrl-C pour arreter le programme */ 
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handle_sigint;
    sigaction(SIGINT, &action, 0); 

    pause();                     /* attente du Ctrl-C */
    return EXIT_SUCCESS;
} 
