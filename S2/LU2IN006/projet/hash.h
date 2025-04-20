#ifndef HASH
#define HASH

#define TOMBSTONE ((void*)-1)

#define TABLE_SIZE 128
 
typedef struct hashentry {
	char* key;
	void* value;
} HashEntry;

typedef struct hashmap {
	int size;
	int current_mem;
	HashEntry* table;
} HashMap;

void free_HashEntry(HashEntry *he);
void free_HashMap(HashMap *hm);
void afficher_hashmap(HashMap* hp);
unsigned long simple_hash(const char *str);
int h(const char *str, int i);
HashMap *hashmap_create();
int hashmap_insert(HashMap *map, const char *key, void *value);
void *hashmap_get(HashMap *map, const char *key);
int hashmap_remove(HashMap *map, const char *key);

#endif
