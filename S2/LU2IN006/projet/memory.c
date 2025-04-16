#include "memory.h"
#include "hash.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_memory(MemoryHandler *m) {
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

void print_segments(Segment* s) {
	if(s != NULL) {
		printf("\nSegment : \n\n");
		printf("start: %d \nsize: %d\n", s->start, s->size);
		print_segments(s->next);
	}
}

MemoryHandler *memory_init(int size) {
	MemoryHandler *new = malloc(sizeof(MemoryHandler));
	new->memory=malloc(size*sizeof(void*));

	
	for(int i=0; i< size; i++){
		new->memory[i]=NULL;
	}
	
	new->total_size=size;

	Segment *seg = malloc(sizeof(Segment));
	seg->start = 0;
	seg->size = size;
	seg->next = NULL;
	
	new->free_list = seg;
	new->allocated = hashmap_create();
	
	return new;
}

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
	
	return NULL;
}

int create_segment(MemoryHandler *handler, const char *name, int start, int size) {
	Segment *prev = NULL;
	Segment *n = find_free_segment(handler, start, size, &prev);
	
	if(n == NULL) {
        printf("Error: %s %d\n", name, size);
        return -1;
    }

	if(n != NULL) {
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

	}
	return 0;// ne sais pas quoi retourner
}




int remove_segment(MemoryHandler *handler, const char *name){
	Segment *new = hashmap_get(handler->allocated, name);
	hashmap_remove(handler->allocated,name);
	Segment *seg_free=handler->free_list;
	Segment *prec;

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

char *trim(char *str) {
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r') str++;
	char* end = str + strlen(str) -1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
		*end = '\0';
		end--;
	}

	return str;
}

int search_and_replace(char **str, HashMap *values) {
	if (!str || !*str || !values) return 0;

	int replaced = 0;
	char *input = *str;

	for(int i =0; i<values->size; i++) {
		if(values->table[i].key && values->table[i].key != (void *)-1) {
			char *key = values->table[i].key;
			int value = (int)(long) values->table[i].value;

			char *substr = strstr(input, key);
			if(substr){
				char replacement[64];
				snprintf(replacement, sizeof(replacement), "%d", value);

				int key_len = strlen(key);
				int repl_len = strlen(replacement);
				int remain_len = strlen(substr + key_len);

				char *new_str = (char*)malloc(strlen(input) - key_len + repl_len + 1);

				strncpy(new_str, input, substr-input);
				new_str[substr-input] = '\0';
				strcat(new_str, replacement);
				strcat(new_str, substr + key_len);

				free(input);
				*str = new_str;
				input = new_str;
				replaced = 1;
			}
		}
	}

	if(replaced) {
		char *trimmed = trim(input);
		if(trimmed != input) {
			memmove(input, trimmed, strlen(trimmed) + 1);
		}
	}

	return replaced;
}

int resolve_constants(ParserResult *result) {

	for(int i=0; i<result->data_count; i++) {
		if(hashmap_get(result->memory_locations, result->code_instructions[i]->operand2) != NULL) {
			search_and_replace(&(result->code_instructions[i]->operand2), result->memory_locations);
		} 
	}

	for(int i=0; i<result->code_count; i++) {

		if (hashmap_get(result->labels, result->code_instructions[i]->operand1) != NULL) {
			search_and_replace(&(result->code_instructions[i]->operand1), result->labels);
		}

	}

	return 0;
}