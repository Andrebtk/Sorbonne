#include "LRU.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int	initLRU(Swapper*);
void	referenceLRU(Swapper*,unsigned int frame);
unsigned int chooseLRU(Swapper*);
void	finalizeLRU(Swapper*);


/*
typedef int Page;
typedef struct Swapper {
	unsigned int frame_nb; 		// Nombre de cases de la mémoire physique
	Page * frame; 				// Tableau des cases en mémoire 
	void * private_data; 		// Donnée privée propre à chaque stratégie 
} Swapper;
*/

typedef struct {
	unsigned int clock;
	unsigned int* age;
} InfoLRU;

unsigned int global_clock = 0;

int initLRUSwapper(Swapper*swap,unsigned int frames){
	return	initSwapper(
					swap,	
					frames,				//Logical number of frames
					initLRU,			//Init for private data
					referenceLRU,		//Reference to keep stats
					chooseLRU,			//Choose function
					finalizeLRU			//Finalize function
				);
}

int	initLRU(Swapper*swap){
	swap->private_data = calloc(swap->frame_nb, sizeof(InfoLRU));

	if (swap->private_data == NULL) return -1;

	global_clock = 0;

	return 0;
}

/*
Fonction qui sera appelée lors d’un accès à la case mémoire numéro frame
*/
void referenceLRU(Swapper* swap, unsigned int frame){

	InfoLRU *info = (InfoLRU*) swap->private_data;

	// On incrémente l'horloge globale
	global_clock++;

	// On met à jour l'horloge de la frame spécifique
	info[frame].clock = global_clock;

}


/*
Fonction qui sera appelée lors d’un défaut de page. Elle doit retourner le numéro de la case
contenant la page victime.
*/
unsigned int chooseLRU(Swapper* swap){
	
	InfoLRU *info = (InfoLRU*) swap->private_data;

	unsigned int val_victim = info[0].clock;
	unsigned int victim = 0;


	for(unsigned int i=1; i < swap->frame_nb; i++) {
		if(info[i].clock < val_victim) {
			val_victim = info[i].clock;
			victim = i;
		}
	}

	return victim;
}

void finalizeLRU(Swapper* swap){
	free(swap->private_data);
}
