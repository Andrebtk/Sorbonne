#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void free_HashEntry(HashEntry *he) {
    if (he != NULL) {
        free(he->key);
        free(he->value);
        free(he);
    }
}

void free_HashMap(HashMap *hm) {
    if (hm != NULL) {
        for (int i = 0; i < hm->size; i++) {
            free(hm->table[i].key);
            free(hm->table[i].value);
        }
        free(hm->table);
        free(hm);
    }
}

void afficher_hashmap(HashMap* hp){
	if (hp == NULL) return;
	printf("size : %d\n", hp->size);
	printf("current_mem : %d\n", hp->current_mem);

	for (int i = 0; i < TABLE_SIZE; i++) {
		char *k = hp->table[i].key;
		void *v = hp->table[i].value;
		if (k && k != TOMBSTONE && v && v != TOMBSTONE) {
		  printf("table[%d] : key = %s, value = %d\n",
				 i, k, *(int*)v);
		}
	  }
}

unsigned long simple_hash(const char *str) {
	unsigned long res=0;
	
	for(int i=0; str[i] != '\0';i++) {
		res += (int) (str[i]);
	}
	
	return res % TABLE_SIZE;
}

int h(const char *str, int i) {
	return (int) (simple_hash(str) + i);
}


HashMap *hashmap_create() {
	HashMap *h = malloc(sizeof(HashMap));

	h->size = TABLE_SIZE;
    h->table = malloc(sizeof(HashEntry) * TABLE_SIZE);

	for (int i=0; i < TABLE_SIZE; i++) {
		h->table[i].value = NULL;
        h->table[i].key = NULL;
	}
	
	return h;
}

int hashmap_insert(HashMap *map, const char *key, void *value) {

	 
	int i=0;
	unsigned long k = h(key,i);
	
	while ((map->table[k].key != TOMBSTONE) && (map->table[k].key != NULL)) {
		i++;
		k = (h(key,i) % map->size); 	
	}


	if (map->table[k].key != NULL && map->table[k].key != TOMBSTONE) {
		free(map->table[k].key);
	}
	map->table[k].key = strdup(key);
	map->table[k].value = value;

	return k;
}


void *hashmap_get(HashMap *map, const char *key) {
	int i=0;
	unsigned long k = h(key,i);
	
	while (map->table[k].key != NULL) {
		if(strcmp(map->table[k].key,key)==0) {
			return map->table[k].value;
		}
		i++;
		k = (h(key,i) % map->size); 	
	}
	
	return NULL;
}


int hashmap_remove(HashMap *map, const char *key) {
	int i = 0;
	unsigned long k = h(key, i);

	while (map->table[k].key != NULL) {
		if (strcmp(map->table[k].key, key) == 0) {
			map->table[k].key = TOMBSTONE;
			map->table[k].value = TOMBSTONE;
			return 1;
		}
		i++;
		k = (h(key, i) % map->size);
	}

	return 0;
}

void hashmap_destroy(HashMap *map) {
    for (int i = 0; i < map->size; i++) {
        if (map->table[i].key != NULL && map->table[i].key != TOMBSTONE) {
            free(map->table[i].key);
			free(map->table[i].value);
        }
    }
    free(map->table);
    free(map);
}



/*parce que tu n'as pas de main.c
#include <stdio.h>
#include "hash.h"
#include "memory.h" 
#include "hash.c"
#include "memory.c" 

void print_free_list(MemoryHandler *handler) {
    Segment *current = handler->free_list;
    printf("free_list:\n");
    while (current != NULL) {
        printf("  Start: %d, Size: %d\n", current->start, current->size);
        current = current->next;
    }
}



int main() {
    // Initialisation du gestionnaire de mémoire
    MemoryHandler *handler= memory_init(1024);

    printf("\nCréation de segments mémoire\n");
    create_segment(handler, "test1", 100, 50);
    create_segment(handler, "test2", 200, 75);
    create_segment(handler, "test3", 500, 100);
    print_free_list(handler);
    printf("\n");
    printf("\nSuppression de test2\n");
    remove_segment(handler, "test2");
    print_free_list(handler);
    printf("\n");


    return 0;
}
}*/
