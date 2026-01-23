#ifndef MEMORY
#define MEMORY

#include "hash.h"


typedef struct segment {
	int start;
	int size;
	struct segment *next;
} Segment;

typedef struct memoryHandler {
	void **memory; // Tableau de pointeurs vers la memoire allouee
	int total_size; // Taille totale de la memoire geree
	Segment *free_list; // Liste chainee des segments de memoire libres
	HashMap *allocated; // Table de hachage (nom, segment)
}MemoryHandler;

MemoryHandler *memory_init(int size);
Segment* find_free_segment(MemoryHandler* handler, int start, int size, Segment** prev);
int create_segment(MemoryHandler *handler, const char *name, int start, int size);
int remove_segment(MemoryHandler *handler, const char *name);
char *trim(char *str);
int search_and_replace(char **str, HashMap *values);
void print_memory(MemoryHandler *m);
void print_segments(Segment* s);
void free_segments(Segment* seg);
void free_memoryHandler(MemoryHandler *m);
#endif
