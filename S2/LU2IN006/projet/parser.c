#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define Length 100

//Fonction qui libère la mémoire allouée pour une instruction
void free_Instruction(Instruction *i) {
	if (i != NULL) {
		free(i->mnemonic);
		free(i->operand1);
		free(i->operand2);
		free(i);
	}
}

//Fonction qui libère toute la mémoire utilisée par le ParserResult
void free_ParserResult(ParserResult *pr) {
	if (pr != NULL) {
		free_HashMap(pr->labels);
		free_HashMap(pr->memory_locations);
		
		// Libération des instructions de la section .DATA
		for (int i=0; i<pr->data_count; i++) {
			free_Instruction(pr->data_instructions[i]);
		}
		free(pr->data_instructions);
		
		// Libération des instructions de la section .CODE
		for (int i=0; i<pr->code_count; i++) {
			free_Instruction(pr->code_instructions[i]);
		}
		free(pr->code_instructions);

		free(pr);
	}
	
}

//Fonction pour affiche une instruction
void affiche_Instruction(Instruction* a) {
	if (a==NULL) { printf("Affichage NULL"); return; }
	printf("mnemonic: %s\n",a->mnemonic);
	printf("operand1: %s\n",a->operand1);
	printf("operand2: %s\n",a->operand2);
}

//Fonction pour afficher une structure de type ParserResult
void afficher_ParserResult(ParserResult* p) {
	if (p==NULL) { printf("Affichage NULL"); return; }

	printf("data_count: %d \n",p->data_count);

	for (int i=0; i<p->data_count; i++) {
		printf("%d : \n",i);
		affiche_Instruction(p->data_instructions[i]);
	}
	
	printf("\ncode_count: %d \n",p->code_count);
	
	for (int i=0; i<p->code_count; i++) {
		printf("%d : \n",i);
		affiche_Instruction(p->code_instructions[i]);
	}
	
	printf("\n");
	afficher_hashmap(p->labels);
	afficher_hashmap(p->memory_locations);
	
}

//Fonction qui analyse et stock une ligne de la section .DATA
Instruction *parse_data_instuction(const char *line, HashMap *memory_locations){
	if(memory_locations == NULL) return NULL;

	char nom[Length];
	char type[Length];
	char valeur[Length];
	int size=0;
	
	// Création de l'instruction
	sscanf(line, "%s %s %s",nom, type, valeur);
	Instruction *res = malloc(sizeof(Instruction));
	
	if(res == NULL){
		printf("ERROR: malloc Instruction dans parse_data_instuction\n");
		return NULL;
	}

	res->mnemonic = strdup(nom);
	res->operand1 = strdup(type);
	res->operand2 = strdup(valeur);
	

	// Calcul de la taille (nombre d'éléments séparés par des virgules)
	char *val_copy = strdup(valeur);
	char *token = strtok(val_copy, ",");
	while (token != NULL) {
		size++;
		token = strtok(NULL, ",");
	}

	free(val_copy);

	// Allouer l'adresse mémoire et insérer dans le hashmap
	int *i = malloc(sizeof(int));
	if(i == NULL){
		printf("ERROR: malloc int dans parse_data_instuction\n");
		return NULL;
	}

	*i=memory_locations->current_mem;
	hashmap_insert(memory_locations, nom, (void*) i);
	memory_locations->current_mem+= size;
	
	return res;
}

//Fonction qui analyse et stock une ligne de la section .CODE
Instruction *parse_code_instruction(const char *line, HashMap *labels, int code_count){
	if(labels == NULL) return NULL;

	// Variables pour stocker l'étiquette, le nom de l'instruction et ses opérandes
	char etiquette[Length] = {0};
	char nom[Length] = {0};
	char op1[Length] = {0};
	char op2[Length] = {0};


	 // Allocation de la structure Instruction
	Instruction *res = malloc(sizeof(Instruction));
	if(res == NULL){
		printf("ERROR: malloc Instruction dans parse_code_instruction\n");
		return NULL;
	}

	 // Variable pour savoir si la ligne contient une étiquette
	int is_etiquette=0;
	
	// Vérifie si la ligne contient un ':', indiquant potentiellement une étiquette
	if(strchr(line,':')){
		char *colon_ptr = strchr(line, ':');
		char *space_ptr = strchr(line, ' ');

		// Si ':' apparaît avant le premier espace, on considère que c'est une étiquette
		if (colon_ptr && (!space_ptr || colon_ptr < space_ptr)) {
			is_etiquette = 1;
			
			// Si une virgule est présente, la ligne contient deux opérandes
			if (strchr(line, ',')) {
				sscanf(line, "%[^:]: %s %[^,],%s", etiquette, nom, op1, op2);
			} else {
				sscanf(line, "%[^:]: %s %s", etiquette, nom, op1);
				op2[0] = '\0'; // Si seulement un opérande, l'autre est vide
			}
		}else{
			// Sinon, la ligne est analysée normalement sans étiquette
			if (strchr(line, ',')) {
				sscanf(line, "%s %[^,],%s", nom, op1, op2);
			} else {
				int n = sscanf(line, "%s %s", nom, op1);
				if (n < 2) {
					op1[0] = '\0';
				}
				op2[0] = '\0';
			}
		
			etiquette[0] = '\0'; // Pas d'étiquette
		}

	} else {
		// Si pas d'étiquette, on analyse directement la ligne
		if(strchr(line,',')){
			sscanf(line, "%s %[^,],%s", nom, op1, op2);
		} else {
			int n = sscanf(line, "%s %s", nom, op1);
			if (n < 2) {
				op1[0] = '\0';
			}
			op2[0] = '\0';
		}
		etiquette[0]='\0';
	}

	// Si une étiquette a été trouvée, on l'ajoute à la table de hachage
	if (is_etiquette==1) {
		int *i = malloc(sizeof(int));

		if(i == NULL){
			printf("ERROR: malloc int dans parse_code_instruction\n");
			return NULL;
		}

		*i = code_count;
		hashmap_insert(labels, etiquette, i);
	}

	// Remplissage de la structure Instruction
	res->mnemonic = strdup(nom);
	res->operand1 = strdup(op1);
	res->operand2 = strdup(op2[0] ? op2 : "");


	return res;
}

//Fonction de parsing qui construie la structure ParserResult à partir d'un ficher
ParserResult *parse(const char *filename) {
	// Ouverture du fichier en lecture
	FILE *f = fopen(filename,"r");
	if(f == NULL){
		printf("Error: fopen dans parse\n");
		return NULL;
	}

	// Allocation de la structure ParserResult
	ParserResult *res = malloc(sizeof(ParserResult));
	if(res == NULL){
		printf("ERROR: malloc ParserResult dans parse\n");
		return NULL;
	}

	// Buffer pour stocker une ligne du fichier
	char buffer[555];
	int Data = 1; // Variable pour distinguer les sections .DATA et .CODE
	
	// Initialisation de la structure ParserResult
	res->code_count = 0;
	res->data_count = 0;

	// Allocation des tableaux pour stocker les instructions
	res->data_instructions = malloc(100*sizeof(Instruction*));
	if(res->data_instructions == NULL){
		printf("ERROR: malloc Instruction* dans parse\n");
		return NULL;
	}

	res->code_instructions = malloc(100*sizeof(Instruction*));
	if(res->code_instructions == NULL){
		printf("ERROR: malloc Instruction* dans parse\n");
		return NULL;
	}

	// Création des tables de hachage pour les labels et les emplacements mémoire
	res->labels = hashmap_create();;
	res->memory_locations = hashmap_create();

	// Variable pour suivre la ligne dans la section .CODE
	int ligne=0;
	
	// Lecture du fichier ligne par ligne
	while(fgets(buffer, 555, f)) {
		// Si la ligne est ".DATA", on continue (on est déjà dans la section .DATA)
		if(strcmp(buffer,".DATA\n")==0) continue;
		
		// Si la ligne est ".CODE", on passe à la section .CODE
		if (strcmp(buffer, ".CODE\n")==0){
			Data = 0;
			continue;
		}
		
		// Si on est dans la section .DATA
		if(Data == 1) {
			 // Analyser l'instruction de données
			Instruction *a = parse_data_instuction(buffer, res->memory_locations);
			res->data_instructions[res->data_count] = a;
			res->data_count++;
			
		} else {
			// Si on est dans la section .CODE, analyser l'instruction de code
			Instruction *b = parse_code_instruction(buffer, res->labels, ligne);
			res->code_instructions[res->code_count] = b;
			res->code_count++;
			ligne++; // Incrémenter le compteur de lignes de code
		}
		
	}

	fclose(f);  // Fermeture du fichier après le traitement

	return res;
}
