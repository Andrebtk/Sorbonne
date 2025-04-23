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
	
	// Affiche la mémoire sous forme de cases "O" (occupée) ou "N" (libre)
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

//Affiche récursivement les segments d'une liste chaînée.
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

	if(new == NULL){
		printf("ERROR: malloc MemoryHandler dans memory_init\n");
		return NULL;
	}

	// Allocation du tableau de mémoire
	new->memory=malloc(size*sizeof(void*));
	for(int i=0; i<size; i++){
		new->memory[i]=NULL;  // Initialise chaque case à NULL
	}

	new->total_size=size;

	// Création du premier segment libre qui couvre toute la mémoire
	Segment *seg = malloc(sizeof(Segment));

	if(seg == NULL){
		printf("ERROR: malloc Segment dans memory_init\n");
		return NULL;
	}

	seg->start = 0;
	seg->size = size;
	seg->next = NULL;
	
	new->free_list = seg;
	new->allocated = hashmap_create(); // Initialisation de la hashmap
	
	return new;
}

//Recherche un segment libre contenant l’espace nécessaire à une position donnée
Segment* find_free_segment(MemoryHandler* handler, int start, int size, Segment** prev) {
	if(handler == NULL) return NULL;

	Segment* tmp = handler->free_list;
	*prev = NULL;

	// Parcours de la liste chaînée pour trouver un segment suffisant
	while(tmp) {
		if ((tmp->start <= start) && (tmp->start+tmp->size >= start+size)) {
			return tmp;
		}
		*prev = tmp;
		tmp = tmp->next;
	}
	return NULL; //aucun segment correspondant au prérequis trouvé
}

//Alloue un nouveau segment de mémoire en modifiant la liste des segments libres si nécessaire.
int create_segment(MemoryHandler *handler, const char *name, int start, int size) {
	if(handler == NULL) return -1;

	Segment *prev = NULL;
	Segment *n = find_free_segment(handler, start, size, &prev); // Recherche d’un segment libre
	
	if(n == NULL) {
		printf("Error: %s %d\n", name, size);
		return -1; // Pas de segment libre adapté
	}

	Segment *new_seg = malloc(sizeof(Segment));
	if(new_seg == NULL){
		printf("ERROR: malloc Segment dans create_segment\n");
		return -1; 
	}

	new_seg->start = start;
	new_seg->size = size;
	new_seg->next = NULL;
	hashmap_insert(handler->allocated, name, (void*) new_seg);  // Ajout à la hashmap


	// Mise à jour de la free_list selon la position
	if (n->start == new_seg->start && n->size == new_seg->size) { // Segment entièrement utilisé
		if (prev) {
			prev->next = n->next;
		} else {
			handler->free_list = n->next;
		}
		free(n);
	}else if(n->start == new_seg->start){  // Début utilisé
		n->start +=new_seg->size;
		n->size -= new_seg->size;
	}else if(n->start + n->size == new_seg->size){ // Fin utilisée
		n->size -= new_seg->size;
	}else { // Découpage du segment (milieu utilisé)
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
int remove_segment(MemoryHandler *handler, const char *name) {
	if(handler == NULL) return -1;

	// Récupération du segment
	Segment *old = hashmap_get(handler->allocated, name);
	if (!old) {
		printf("Error: segment \"%s\" non existant\n", name);
		return -1;
	}


	int start = old->start;
	int size  = old->size;

	// Suppression de la hashmap
	if(hashmap_remove(handler->allocated, name)==-1){
		printf("ERROR: hashmap_remove dans remove_segment\n");
		return -1;
	}


	// Création d’un nouveau segment
	Segment *node = malloc(sizeof *node);
	if(node == NULL){
		printf("ERROR: malloc Segment dans remove_segment\n");
		return -1;
	}

	node->start = start;
	node->size  = size;
	node->next  = NULL;

	// Insertion triée
	Segment *cur  = handler->free_list;
	Segment *prev = NULL;
	while (cur && cur->start < node->start) {
		prev = cur;
		cur  = cur->next;
	}
	node->next = cur;
	if (prev) prev->next = node;
	else       handler->free_list = node;

	// Fusion avec le segment précédent
	if (prev && prev->start + prev->size == node->start) {
		prev->size  += node->size;
		prev->next   = node->next;
		free(node);
		node = prev;
	}

	// Fusion avec le suivant
	if (node->next && node->start + node->size == node->next->start) {
		Segment *to_free = node->next;
		node->size += to_free->size;
		node->next = to_free->next;
		free(to_free);
	}

	return 0;
}


//Libère récursivement tous les segments d’une liste chaînée.
void free_segments(Segment* seg) {
	if(seg != NULL) {
		free_segments(seg->next);
		free(seg);
	}
}

//Fonction qui liberer toute la memoire alloué par un gestionnaire de memoire
void free_memoryHandler(MemoryHandler *m) {
	if(m == NULL) return;
	
	// Libération de la Data Segment (DS)
	Segment* DS = hashmap_get(m->allocated, "DS");
	if(DS) {
		for(int i=0; i<DS->size; i++) {
			free(m->memory[DS->start + i]);
		}
	}

	// Libération du Code Segment (CS)
	Segment* CS = hashmap_get(m->allocated, "CS");
	if(CS) {
		for(int i=0; i<CS->size; i++){
			free_Instruction(m->memory[CS->start + i]); // Fonction spécifique pour libérer une instruction
		}
	}

	// Libération de l’Extra Segment (ES)
	Segment* ES = hashmap_get(m->allocated, "ES");
	if (ES) {
		for (int i = 0; i < ES->size; i++) {
			free(m->memory[ES->start + i]);
		}
	}

	// Libération du Stack Segment (SS)
	Segment* SS = hashmap_get(m->allocated, "SS");
	if (SS) {
		for (int i = 0; i < SS->size; i++) {
			free(m->memory[SS->start + i]);
		}
	}

	// Libération des structures de gestion de la mémoire
	free(m->memory);
	free_HashMap(m->allocated);
	free_segments(m->free_list);
	free(m);
}
