#include "hash.h"


//Fonction qui libere une structure de type HashEntry
void free_HashEntry(HashEntry *he) {
	if (he != NULL) {
		free(he->key);
		free(he->value);
		free(he);
	}
}

//Fonction qui libère la mémoire alloué par la table de hachage map
void free_HashMap(HashMap *hm) {
    if (hm != NULL) {
        for (int i = 0; i < hm->size; i++) {
			// Si une entrée existe et n'est pas marquée comme TOMBSTONE
			if(hm->table[i].key != NULL && hm->table[i].key != TOMBSTONE){
				free(hm->table[i].key);
			}

			// Si une valeur existe et n'est pas marquée comme TOMBSTONE
			if(hm->table[i].value != NULL && hm->table[i].value != TOMBSTONE){
				free(hm->table[i].value);
			}
		}
		free(hm->table); // Libère la table elle-même
		free(hm); // Libère la structure HashMap
	}
}

//Fonction pour affichier une structure Hashmap
void afficher_hashmap(HashMap* hp){
	if (hp == NULL) return;
	printf("size : %d\n", hp->size);
	printf("current_mem : %d\n", hp->current_mem);

	// Affiche chaque entrée de la table
	for (int i = 0; i < hp->size; i++) {
		char *k = hp->table[i].key;
		void *v = hp->table[i].value;

		// Si la clé et la valeur ne sont pas NULL ou TOMBSTONE
		if (k && k != TOMBSTONE && v && v != TOMBSTONE) {
		  printf("table[%d] : key = %s, value = %d\n",
				 i, k, *(int*)v);
		}
	  }
}

//Fonction de hachage
unsigned long simple_hash(const char *str) {
	if(strcmp(str,"")==0) return 0;
	unsigned long res=0;
	
	// Additionne les valeurs ASCII de chaque caractère
	for(int i=0; str[i] != '\0';i++) {
		res += (int) (str[i]);
	}
	
	// Retourne l'indice modulo la taille de la tabl
	return res % TABLE_SIZE;
}

//Fonction de probing lineaire
int h(const char *str, int i) {
	return (int) (simple_hash(str) + i); // Applique un décalage basé sur i
}

//Fonction qui alloue et initialise une table de hachage
HashMap *hashmap_create() {
	HashMap *new = malloc(sizeof(HashMap));
	if(new == NULL){
		printf("ERROR: malloc HashMap\n");
		return NULL;
	}
	new->size = TABLE_SIZE;
	new->current_mem = 0; 

	// Alloue un tableau de HashEntry pour les éléments
	new->table = malloc(sizeof(HashEntry) * TABLE_SIZE );

	// Initialise chaque entrée de la table
	for (int i=0; i < TABLE_SIZE; i++) {
		new->table[i].value = NULL;
        new->table[i].key = NULL;
	}
	return new;
}

//Fonction qui insère un élément dans la table de hachage map
int hashmap_insert(HashMap *map, const char *key, void *value) {
	if(map == NULL) return -1;
	int i=0;
	unsigned long k = h(key,i);  // Calcule le hash avec la fonction de probing
	
	// Cherche un emplacement libre ou marqué comme TOMBSTONE
	while ((map->table[k].key != TOMBSTONE) && (map->table[k].key != NULL)) {
		i++; // Essaye la prochaine position
		k = (h(key,i) % map->size); // Calcule un nouvel indice
		if (i > map->size){ 
			return -1; // Si la table est pleine, échec de l'insertion
		}
	}

	// Insère la clé et la valeur
	map->table[k].key = strdup(key);
	map->table[k].value = value;
	return 0; //insertion réussi
}

//Fonction permettant de récupérer un élément à partir de sa clé
void *hashmap_get(HashMap *map, const char *key) {
	if(map == NULL) return NULL;
	
	int i=0;
	unsigned long k = h(key,i); // Calcule le hash avec la fonction de probing
	
	// Cherche la clé dans la table
	while (map->table[k].key != TOMBSTONE && map->table[k].key != NULL) {
		if(strcmp(map->table[k].key,key)==0) {
			return map->table[k].value; // Retourne la valeur associée à la clé
		}
		i++; // Essaye la prochaine position
		k = (h(key,i) % map->size);  // Calcule un nouvel indice
	}
	return NULL; // Si la clé n'est pas trouvée, retourne NULL
}

//Fonction qui supprime un élément dans la table de hachage map
int hashmap_remove(HashMap *map, const char *key) {
	if(map == NULL) return -1;
	
	int i = 0;
	unsigned long k = h(key, i); // Calcule le hash avec la fonction de probing


	// Cherche la clé dans la table
	while (map->table[k].key != NULL) {
		if (strcmp(map->table[k].key, key) == 0) {

			free(map->table[k].key);
			free(map->table[k].value);

			// Marque l'entrée comme supprimée
			map->table[k].key = TOMBSTONE;
			map->table[k].value = TOMBSTONE;

			return 0; //suppression réussi
		}

		i++; // Essaye la prochaine position
		k = (h(key, i) % map->size); // Calcule un nouvel indice
	}
	return -1; // Si la clé n'est pas trouvée, retourne une erreur
}

