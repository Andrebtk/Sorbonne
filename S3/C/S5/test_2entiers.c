#include <stdlib.h>
#include "liste.h"
#include "devel.h"
#include "fonctions_2entiers.h"

int main(void) {
	Liste* l = malloc(sizeof(Liste));
	
	l->dupliquer = dupliquer_2int;
}
