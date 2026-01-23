#include "Fifo.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


/*
typedef int Page;
typedef struct Swapper {
	unsigned int frame_nb; 		// Nombre de cases de la mémoire physique
	Page * frame; 				// Tableau des cases en mémoire 
	void * private_data; 		// Donnée privée propre à chaque stratégie 
} Swapper;
*/


int initFifo(Swapper*);
unsigned int fifoChoose(Swapper*);
void fifoReference(Swapper*,unsigned int frame);
void finalizeFifo(Swapper*);

int initFifoSwapper(Swapper* swap, unsigned int frames){
	return	initSwapper(
					swap,
					frames,					// Logical number of frames
					initFifo,				// Init for private data
					NULL,					// Reference to keep stats
					fifoChoose,				// Choose function 
					finalizeFifo			// Finalize function
			);
}

int initFifo(Swapper* swap){
	swap->private_data = malloc(sizeof(int));
	if(swap->private_data == NULL) return -1;

	*(int*) (swap->private_data) = 0;
	return 0;
}


/*
Fonction qui sera appelée lors d’un défaut de page. Elle doit retourner le numéro de la case
contenant la page victime
*/
unsigned int fifoChoose(Swapper* swap){

	int *next_victime  = (int*)swap->private_data;
	unsigned int victime = *next_victime;
	*next_victime = (*next_victime + 1) % swap->frame_nb;

	return victime;
}

void finalizeFifo(Swapper* swap){
	free(swap->private_data);
	return;
}
