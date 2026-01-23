#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void min_max_moy (int* listEntier, int longeur, int* moy, int* min, int* max) {
	if (longeur == 0) return;

	*min = listEntier[0];
	*max = listEntier[0];
	*moy = 0;
	int sum = 0;
	for (int i = 0; i<longeur; i++) {
		if (listEntier[i] < *min) *min = listEntier[i];
		if (listEntier[i] > *max) *max = listEntier[i];
		sum += listEntier[i];
	}

	*moy = sum/longeur;
}

void min_max_moy_intermediaire (int* listEntier, int longeur, int* moy, int* min, int* max) {
	if (longeur == 1) {
		*moy += listEntier[0];
		if (listEntier[0] < *min) *min = listEntier[0];
		if (listEntier[0] > *max) *max = listEntier[0];
		return;
	}

	int i = listEntier[longeur-1];
	*moy += i;
	if (i > *max) *max = i;
	if (i < *min) *min = i;

	min_max_moy_intermediaire ((listEntier), longeur-1, moy, min, max);
}

void min_max_moy_recursive (int* listEntier, int longeur, int* moy, int* min, int* max) {
	*min = listEntier[0];
	*max = listEntier[0];
	*moy = 0;

	min_max_moy_intermediaire (listEntier, longeur, moy, min, max); 

	*moy = *moy / longeur;
}

int compte_mots_chaine (char *chaine) {
	if (chaine == NULL || chaine[0] == '\0') return 0;
	int res = 1;
	for (int i = 0; chaine[i] != '\0'; i++) {
		if (chaine[i] == ' ') res++;
	}
	return res;
}

int compte_mots (char **listMots) {
	int res = 0;
	for (int i=0; listMots[i] != NULL; i++) {
		res++;
	}
	return res;
}

void detruit_tab_mots (char **ptab_mots) {
	for (int i=0; ptab_mots[i] != NULL; i++) {
		free (ptab_mots[i]);
	}
}

char **decompose_chaine (char *chaine) {
	int nb_mots = compte_mots_chaine (chaine);
	char **res = malloc (sizeof (char *) * (nb_mots + 1));

	int mot_start_index = 0;
	int mot_end_index = 0;
	int index_mot = 0;
	
	for (int i=0; chaine[i] != '\0'; i++) {
		if (chaine[i] == ' ' || chaine[i + 1] == '\0' ) {
			if (chaine[i + 1] == '\0') 	mot_end_index = i + 1; // Include the last character
			else 						mot_end_index = i;
		
			int longueur_mot = mot_end_index - mot_start_index;
			
			res[index_mot] = malloc((longueur_mot + 1) * sizeof(char));
			memcpy (res[index_mot], &chaine[mot_start_index], longueur_mot);

			res[index_mot][longueur_mot] = '\0'; // Null-terminate the word	

			mot_start_index = i + 1;
			index_mot++;
		}
	}
	res[index_mot] = NULL;

	return res;
}

int main () {
	/*
	int list[10] = {1,2,3,4,5,6,7,8,9};
	int moy, min, max;

	min_max_moy_recursive (list, 10, &moy, &min, &max);
	printf ("min: %d, max: %d, moy: %d \n", min, max, moy);
	*/
	/*
	int nb_char = 11;
	int nb_mots = 3;
	char *listeMot[] = {"mot1", "et", "mot2", "Hey", NULL};
	
	printf ("%d \n", compte_mots_chaine("Hel there"));
	printf ("%d \n", compte_mots (listeMot)); 
	*/
	//Q.6  char *text = malloc (sizeof(char) * nb_mots+1);
	
	char *text = malloc (sizeof(char) * 11);
	text = "hello th e";

	char **listeMot2 = decompose_chaine (text);


	for (int i = 0; listeMot2[i] != NULL; i++) {
		printf("Word %d: %s\n", i + 1, listeMot2[i]);
	}
}