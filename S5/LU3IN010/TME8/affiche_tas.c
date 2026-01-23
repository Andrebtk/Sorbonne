#include <stdio.h>
#include "affiche_tas.h"
#include <ctype.h>

void afficher_tas(){
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 16; j++) { 
	        printf("%4d", j + 16*i);
        }
        printf("\n");
        for (j = 0; j < 16; j++) { 
	        printf("%4d", tas[j + 16*i]);
        }
        printf("\n");
        for (j = 0; j < 16; j++) { 
            if (isalnum(tas[j + 16*i])) {
                printf("%4c", tas[j + 16*i]);
            } else {
                printf("    ");
            }
        }
        printf("\n\n");
    }
    printf("---------------------------------------------------------------\n\n");
}

void tas_init(){
  libre = 0;
  tas[0] = TAILTAS;
  tas[1] = -1;
}

int first_fit(int taille, int* pred) {
	// Taille donnée + 1 octet pour stocker la taille
	int taille_req = taille + 1;
	int courant = libre;

	*pred = -1;

	// Tant qu'on est sur un bloc valide (indice != -1)
	while(courant != -1) {
		if( tas[courant] >= taille_req ) {
			return courant;
		}

		// Si la place n'est pas suffisante
		*pred = courant;
		courant = tas[courant+1];
	}

	return -1;
}


char *tas_malloc(unsigned int taille) {
	if(taille == 0) return NULL;

	int pred;
	int bloc_trouver = first_fit(taille, &pred);
	if( bloc_trouver == -1) return NULL;

	int bloc_libre_suivant = tas[bloc_trouver + 1];

	int taille_bloc_courant = tas[bloc_trouver];
	int taille_zone_alloue = taille + 1;
	
	int taille_restante = taille_bloc_courant - taille_zone_alloue;
	int nouveau_bloc = bloc_trouver + taille_zone_alloue;

	// On ne coupe que si le reste suffit pour faire un nouveau bloc libre (min 2 octets)
	if(taille_restante > TAILMIN -1) {
		tas[nouveau_bloc] = taille_restante;
		tas[nouveau_bloc + 1] = bloc_libre_suivant;

		// Mise a jour du chaînag
		if(pred == -1) {
			// Le bloc alloue etait le premier
			libre = nouveau_bloc;
		} 
		else {
			tas[pred+1] = nouveau_bloc;
		}

		tas[bloc_trouver] = taille;

		return &tas[bloc_trouver+1];
	} 
	// On utilise tout le bloc
	else {
		//Mise a jour du chaînag
		if( pred == -1) {
			libre = bloc_libre_suivant;
		}
		else {
			tas[pred + 1] = bloc_libre_suivant;
		}

		tas[bloc_trouver] = taille;
		return &tas[bloc_trouver + 1];
	}
}

// fusion
// plus de place
// mettre a jour le chanage
// mettre a jour libre si c'est avant ou rien si c'est apres
int tas_free(char *ptr){

	// Retrouve l'indice de l'entête (juste avant la donnée pointée par ptr)
	int index = ptr - tas - 1;

	if (index < 0 || index >= TAILTAS) {
		return -1;
	}

	int taille = tas[index];

	for(int i=0; i<taille; i++) {
		tas[index+1+i] = 0;
	}

	// Le nouveau bloc pointe vers l'ancien premier
	tas[index] = taille;

	// La tête de liste pointe vers le nouveau bloc
	tas[index+1] = libre;
	
	libre = index;

	return 0;
}
