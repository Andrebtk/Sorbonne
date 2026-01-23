#include "libmem.h"
#include "Random.h"
#include "LRU.h"
#include "LFU.h"
#include "Fifo.h"

int main(int argc,char*argv[]){
	unsigned int frame_nb;
	Swapper	bobby;	
	
	scanf("%i", &frame_nb); /* Nombre de cases de la mémoire physique */

	/* Initialisation du Swapper de la strat�gie LFU */
	
	initFifoSwapper(&bobby, frame_nb);

	if(swapSimulation(&bobby, stdin)<0){
		printf("Error during swap simulation !!!\n");
		return -1;
	}
	
	return 0;
}
