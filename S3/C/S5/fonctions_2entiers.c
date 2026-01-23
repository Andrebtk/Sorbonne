#include <stdlib.h>
#include <stdio.h>
#include "devel.h"

#include "fonctions_2entiers.h"

void *dupliquer_2int(const void *src) {
	Double_int* res = malloc(sizeof(Double_int));
	Double_int* s = (Double_int*)src;
	res->a = s->a;
	res->b = s->b;
	return res; 
}

void copier_2int(const void *src, void *dst) {
	Double_int* s = (Double_int*)src;
	Double_int* d = (Double_int*) dst;
	d = malloc(sizeof(Double_int));
	d->a = s->a;
	d->b = s->b;
	
	dst = (void*) d;
}

void detruire_2int(void *data) {
  /* a completer. Exercice 6, question 1 */
}

void afficher_2int(const void *data) {
  /* a completer. Exercice 6, question 1 */
}

int comparer_2int(const void *a, const void *b) {
  /* a completer. Exercice 6, question 1 */
  return 0; // pour que cela compile
}

int ecrire_2int(const void *data, FILE *f) {
  /* a completer. Exercice 6, question 1 */
  return 0; // pour que cela compile
}

void * lire_2int(FILE *f) {
  /* a completer. Exercice 6, question 1 */
  return NULL; // pour que cela compile
}
