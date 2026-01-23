#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "devel.h"

void *dupliquer_str(const void *src) {
	char* tmp = (char*)(src);
	char* res = strdup(tmp);
	
	return (void *) res;
}

void copier_str(const void *src, void *dst) {
	dst = strdup((char*) src);
}

void detruire_str(void *data) {
 	free(data);
}

void afficher_str(const void *data) {
	printf("%s", (char*)data);
}

int comparer_str(const void *a, const void *b) {
	return strcmp(a, b); // pour que cela compile
}

int ecrire_str(const void *data, FILE *f) {
	fprintf(f, "data: %s \n", (char*)data);
	return 0;
}

void *lire_str(FILE *f) {
	char* tmp = NULL;
	
	fscanf(f, "data: %s ", tmp);
	printf("debug %s \n",tmp);
	return dupliquer_str(tmp); 
}
