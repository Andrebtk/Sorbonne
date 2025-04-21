#include "memory.h"
#include "hash.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fonction pour afficher la mémoire
void print_memory(MemoryHandler *m) {
	if(m == NULL) {
		printf("Gestionnaire de mémoire non initialisé\n");
		return;
	}
	
	printf("\nAffichage MemoryHandler \n");
	printf("taille total: %d\n", m->total_size);

	printf("\nTable de hachage \"allocated\"\n");
	afficher_hashmap(m->allocated);

	printf("\nListe chainee des segments de memoire libres \"free_list\"\n");
	print_segments(m->free_list);

	printf("\nTableau de pointeurs vers la memoire allouee \"*memory\"\n\n");
	int col = m->total_size/20;
	int local =0;
	for(int i=0; i<m->total_size; i++){
		if(local>col){
			printf("\n");
			local=0;
		}
		
		if(m->memory[i] != NULL) {
			printf("O ");
		}else {
			printf("N ");
		}

		local++;
	}
	printf("\n");
}

//Fonction pour afficher un segment
void print_segments(Segment* s) {
	if(s != NULL) {
		printf("\nSegment :\n");
		printf("start: %d \nsize: %d\n", s->start, s->size);
		print_segments(s->next);
	}
}

//Fonction qui alloue et initialise un gestionaire de mémoire de type MemoryHandler
MemoryHandler *memory_init(int size) {
	MemoryHandler *new = malloc(sizeof(MemoryHandler));
	new->memory=malloc(size*sizeof(void*));

	//Initialisation de memory
	for(int i=0; i<size; i++){
		new->memory[i]=NULL;
	}

	new->total_size=size;

	//Initialisation d'un segment unique qui couvre toute la memoire
	Segment *seg = malloc(sizeof(Segment));
	seg->start = 0;
	seg->size = size;
	seg->next = NULL;
	
	new->free_list = seg;
	new->allocated = hashmap_create(); //Création de la table de hachage 
	
	return new;
}

//Fonction qui cherche s'il existe un segment correspondant au prérequis mis en argument
Segment* find_free_segment(MemoryHandler* handler, int start, int size, Segment** prev) {
	Segment* tmp = handler->free_list;
	*prev = NULL;
	
	while(tmp) {
		if ((tmp->start <= start) && (tmp->start+tmp->size >= start+size)) {
			return tmp;
		}
		*prev = tmp;
		tmp = tmp->next;
	}
	return NULL; //aucun segment correspondant au prérequis trouvé
}

//Fonction qui alloue un segment 
int create_segment(MemoryHandler *handler, const char *name, int start, int size) {
	Segment *prev = NULL;
	Segment *n = find_free_segment(handler, start, size, &prev); //Vérifier s'il y a de la place
	
	if(n == NULL) {
        printf("Error: %s %d\n", name, size);
        return -1; //pas de place trouvé
    }

	Segment *new_seg = malloc(sizeof(Segment));
	new_seg->start = start;
	new_seg->size = size;
	new_seg->next = NULL;
	hashmap_insert(handler->allocated, name, (void*) new_seg);

	if (n->start == new_seg->start && n->size == new_seg->size) { //tout
		if (prev) {
			prev->next = n->next;
		} else {
			handler->free_list = n->next;
		}
		free(n);
	}else if(n->start == new_seg->start){ //debut
		n->start +=new_seg->size;
		n->size -= new_seg->size;
	}else if(n->start + n->size == new_seg->size){//fin
		n->size -= new_seg->size;
	}else { //cas general
		Segment *free2=malloc(sizeof(Segment));
		free2->start = start+size;
		free2->size = n->start + n->size - (start+size);
		free2->next = n->next;
		
		n->size = start - n->start;
		n->next = free2;
	}
	return 0;
}

//Fonction qui libere un segment et fusionne si nécessaire
int remove_segment(MemoryHandler *handler, const char *name){
	Segment *new = hashmap_get(handler->allocated, name);
	if(new == NULL){
		printf("Error segment non existant\n");
		return -1;
	}

	hashmap_remove(handler->allocated,name);
	Segment *seg_free=handler->free_list;
	Segment *prec = NULL;

	while (seg_free && seg_free->start < new->start) {
		prec = seg_free;
		seg_free = seg_free->next;
	}

	if (prec && prec->start + prec->size == new->start) {
		prec->size +=new->size;
		free(new);
		new = prec;
	} else {
		new->next = seg_free;
		if (prec) prec->next = new;
		else handler->free_list = new;
	}

	if (seg_free && new->start + new->size == seg_free->start) {
		new->size += seg_free->size;
		new->next =seg_free->next;
		free(seg_free);
	}
	return 0;
}


//Fonction pour libérer un segment
void free_segments(Segment* seg) {
	if(seg != NULL) {
		free_segments(seg->next);
		free(seg);
	}
}

//Fonction qui liberer toute la memoire alloué par un gestionnaire de memoire
void free_memoryHandler(MemoryHandler *m) {
	Segment* DS = hashmap_get(m->allocated, "DS");
	if(DS) {
		for(int i=0; i<DS->size; i++) {
			free(m->memory[DS->start + i]);
		}
	}

	Segment* CS = hashmap_get(m->allocated, "CS");
	if(CS) {
		for(int i=0; i<CS->size; i++){
			free_Instruction(m->memory[CS->start + i]);
		}
	}

	Segment* ES = hashmap_get(m->allocated, "ES");
	if (ES) {
		for (int i = 0; i < ES->size; i++) {
			free(m->memory[ES->start + i]);
		}
	}

	free(m->memory);
	free_HashMap(m->allocated);
	free_segments(m->free_list);
	free(m);
}
