#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define Length 100

void free_Instruction(Instruction *i) {
	if (i != NULL) {
		free(i->mnemonic);
		free(i->operand1);
		free(i->operand2);
		free(i);
	}
}


void free_ParserResult(ParserResult *pr) {
	if (pr != NULL) {
		free_HashMap(pr->labels);
		free_HashMap(pr->memory_locations);
		

		for (int i=0; i<pr->data_count; i++) {
			free_Instruction(pr->data_instructions[i]);
		}
		free(pr->data_instructions);

		for (int i=0; i<pr->code_count; i++) {
			free_Instruction(pr->code_instructions[i]);
		}
		free(pr->code_instructions);

		free(pr);
	}
	
}

void affiche_Instruction(Instruction* a) {
	printf("mnemonic: %s\n",a->mnemonic);
	printf("operand1: %s\n",a->operand1);
	printf("operand2: %s\n",a->operand2);
}

void afficher_ParserResult(ParserResult* p) {
	if (p==NULL) { printf("Affichage NULL"); return; };
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

Instruction *parse_data_instuction(const char *line, HashMap *memory_locations){
	char nom[Length];
	char type[Length];
	char valeur[Length];
	int size=0;
	
	
	sscanf(line, "%s %s %s",nom, type, valeur);
	Instruction *res = malloc(sizeof(Instruction));
	res->mnemonic = strdup(nom);
	res->operand1 = strdup(type);
	res->operand2 = strdup(valeur);
	
	char *token = strtok(valeur, ",");
	while (token != NULL) {
        size++;
        token = strtok(NULL, ",");
    }

	int *i = malloc(sizeof(int));
	*i=memory_locations->current_mem;
	hashmap_insert(memory_locations, nom, (void*) i);
	memory_locations->current_mem+= size;
	
	return res;
}

Instruction *parse_code_instruction(const char *line, HashMap *labels, int code_count){
	char etiquette[Length];
	char nom[Length];
	char op1[Length];
	char op2[Length];
	Instruction *res = malloc(sizeof(Instruction));

	int is_etiquette=0;
	if(strchr(line,':')){
		is_etiquette=1;

		if(strchr(line,',')) {
			sscanf(line, "%[^:]: %s %[^,],%s", etiquette, nom, op1, op2);
		} else {
			sscanf(line, "%[^:]: %s %s", etiquette, nom, op1);
			op2[0]='\0';
		}
	} else {
		if(strchr(line,',')){
			sscanf(line, "%s %[^,],%s", nom, op1, op2);
		} else {
			sscanf(line, "%s %s", nom, op1);
			op2[0] = '\0';
		}
		
		etiquette[0]='\0';
	}
	
	if (is_etiquette==1) {
		int *i = malloc(sizeof(int));
		*i = code_count;
		hashmap_insert(labels, etiquette, i);
	}


	res->mnemonic = strdup(nom);
	res->operand1 = strdup(op1);
	res->operand2 = strdup(op2);

	return res;
}



ParserResult *parse(const char *filename) {
	FILE *f = fopen(filename,"r");
	
	ParserResult *res = malloc(sizeof(ParserResult));
	char buffer[555];
	int Data = 1;
	

	res->code_count = 0;
	res->data_count = 0;
	res->data_instructions = malloc(100*sizeof(Instruction*));
	res->code_instructions = malloc(100*sizeof(Instruction*));
	res->labels = hashmap_create();;
	res->memory_locations = hashmap_create();

	int ligne=0;
	while(fgets(buffer, 555, f)) {
		if(strcmp(buffer,".DATA\n")==0) continue;
		
		if (strcmp(buffer, ".CODE\n")==0){
			Data = 0;
			continue;
		}
		
		if(Data == 1) {
			//printf("In .DATA: %s \n",buffer);
			Instruction *a = parse_data_instuction(buffer, res->memory_locations);
			res->data_instructions[res->data_count] = a;
			res->data_count++;
			
		} else {
			//printf("In .CODE: %s \n",buffer);
			Instruction *b = parse_code_instruction(buffer, res->labels, ligne);
			
			res->code_instructions[res->code_count] = b;
			res->code_count++;
			ligne++;
		}
		
	}

	fclose(f);
	return res;
	
}
