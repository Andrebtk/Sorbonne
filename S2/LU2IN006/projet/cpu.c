#include "cpu.h"
#include <string.h>
#include <stdio.h>
#include <regex.h>


//Fonction d'affichage d'une structure de type CPU
void print_cpu(CPU* cpu){
	if(cpu == NULL) {
		printf("CPU est NULL\n");
		return;
	}

	print_memory(cpu->memory_handler);


	printf("\nTable de hachage \"context\"\n");
	afficher_hashmap(cpu->context);

	printf("\nTable de hachage \"constant_pool\"\n");
	afficher_hashmap(cpu->constant_pool);


	print_segment_data(cpu, "DS");

	
	void *check = hashmap_get(cpu->memory_handler->allocated, "ES");
	
	
	if (check == NULL) {
		printf("\nSegment ES not found.\n");
	} else {
		print_segment_data(cpu, "ES");
	}
	
}

//Fonction qui alloue et initialise une structure de type CPU
CPU *cpu_init(int memory_size) {
	CPU *res = malloc(sizeof(CPU));

	if(res == NULL){
		printf("ERROR: malloc CPU dans cpu_init\n");
		return NULL;
	}

	res->memory_handler = memory_init(memory_size);
	res->context = hashmap_create();
	res->constant_pool = hashmap_create();

	//Creation du segment 'ss'
	create_segment(res->memory_handler, "SS", 0, 128);

	int *AX = malloc(sizeof(int));
	if(AX == NULL){ printf("ERROR: malloc int dans cpu_init\n"); return NULL; }

	int *BX = malloc(sizeof(int));
	if(BX == NULL){ printf("ERROR: malloc int dans cpu_init\n"); return NULL; }

	int *CX = malloc(sizeof(int));
	if(CX == NULL){ printf("ERROR: malloc int dans cpu_init\n"); return NULL; }
	
	int *DS = malloc(sizeof(int));
	if(DS == NULL){ printf("ERROR: malloc int dans cpu_init\n"); return NULL; }

	int *IP = malloc(sizeof(int));
	if(IP == NULL){ printf("ERROR: malloc int dans cpu_init\n"); return NULL; }

	int *ZF = malloc(sizeof(int));
	if(ZF == NULL){ printf("ERROR: malloc int dans cpu_init\n"); return NULL; }
	
	int *SF = malloc(sizeof(int));
	if(SF == NULL){ printf("ERROR: malloc int dans cpu_init\n"); return NULL; }

	int *SP = malloc(sizeof(int));
	if(SP == NULL){ printf("ERROR: malloc int dans cpu_init\n"); return NULL; }

	int *BP = malloc(sizeof(int));
	if(BP == NULL){ printf("ERROR: malloc int dans cpu_init\n"); return NULL; }

	int *ES = malloc(sizeof(int));
	if(ES == NULL){ printf("ERROR: malloc int dans cpu_init\n"); return NULL; }


	*AX=0;
	*BX=0;
	*CX=0;
	*DS=0;
	*IP=0;
	*ZF=0;
	*SF=0;
	*ES=-1;



	Segment* ss = hashmap_get(res->memory_handler->allocated, "SS");
	if(ss == NULL){
		printf("ERROR: hashmap_get est NULL dans cpu_init\n");
		return NULL;
	}

	*SP=ss->size;
	*BP=ss->size;


	if(hashmap_insert(res->context, "AX", (void*) AX) == -1) { printf("Error: hashmap_insert dans cpu_init\n"); return NULL; }
	if(hashmap_insert(res->context, "BX", (void*) BX) == -1) { printf("ERROR: hashmap_insert dans cpu_init\n"); return NULL; }
	if(hashmap_insert(res->context, "CX", (void*) CX) == -1) { printf("ERROR: hashmap_insert dans cpu_init\n"); return NULL; }
	if(hashmap_insert(res->context, "DX", (void*) DS) == -1) { printf("ERROR: hashmap_insert dans cpu_init\n"); return NULL; }
	if(hashmap_insert(res->context, "IP", (void*) IP) == -1) { printf("ERROR: hashmap_insert dans cpu_init\n"); return NULL; }
	if(hashmap_insert(res->context, "ZF", (void*) ZF) == -1) { printf("ERROR: hashmap_insert dans cpu_init\n"); return NULL; }
	if(hashmap_insert(res->context, "SF", (void*) SF) == -1) { printf("ERROR: hashmap_insert dans cpu_init\n"); return NULL; }
	if(hashmap_insert(res->context, "SP", (void*) SP) == -1) { printf("ERROR: hashmap_insert dans cpu_init\n"); return NULL; }
	if(hashmap_insert(res->context, "BP", (void*) BP) == -1) { printf("ERROR: hashmap_insert dans cpu_init\n"); return NULL; }
	if(hashmap_insert(res->context, "ES", (void*) ES) == -1) { printf("ERROR: hashmap_insert dans cpu_init\n"); return NULL; }

	return res;
}


int matches ( const char * pattern , const char * string ) {
	regex_t regex ;
	int result = regcomp (&regex , pattern, REG_EXTENDED) ;
	if (result) {
		fprintf (stderr, "Regex compilation failed for patern : %s \n" , pattern ) ;
		return 0;
	}
	result = regexec (&regex, string, 0, NULL, 0) ;
	regfree (&regex) ;
	return result == 0;
}


//Fonction qui libère la mémoire d'une structure de type cpu
void cpu_destroy(CPU *cpu) {
	if(cpu != NULL) {
		free_HashMap(cpu->context);
		free_HashMap(cpu->constant_pool);
		free_memoryHandler(cpu->memory_handler);
		free(cpu);
	}
	
}

//Fonction qui stock un void* a la position pos de segment_name
void* store(MemoryHandler *handler, const char *segment_name, int pos, void *data) {
	if(handler == NULL) return NULL;
	
	// Récupère le segment désigné par son nom
	Segment* seg=hashmap_get(handler->allocated, segment_name);

	//Verification que segment_name existe
	if(seg == NULL) return NULL; 

	int addr = seg->start + pos; // Calcule l’adresse absolue dans la mémoire

	// Si une donnée existait déjà à cette adresse, on la libère
	void *old_data = handler->memory[addr];
	if (old_data != NULL) {
		free(old_data);
	}

	 // Stocke la nouvelle donnée si la position est valide
	if(pos < seg->size){
		handler->memory[seg->start + pos] = data;
		return data; // Indique le succès
	}

	return NULL; // Position hors limites du segment
}


//Fonction qui récupere la donnée stocker a la position pos
void* load(MemoryHandler *handler, const char *segment_name, int pos) {
	if(handler == NULL) return NULL;

	// Récupère le segment via son nom dans la table des segments alloués
	Segment* seg=hashmap_get(handler->allocated, segment_name);
	if (seg != NULL) {
		// Calcule l’adresse absolue et renvoie la donnée à cet emplacement
		return handler->memory[seg->start + pos];
	}
	return NULL; // Segment introuvable ou position invalide
}

//Fonction qui alloue un segment de données en fonction de data_instructions
void allocate_variables(CPU *cpu, Instruction** data_instructions, int data_count) {
	if(cpu == NULL) { printf("ERROR: cpu est NULL dans allocate_variables"); return; }
	if(data_instructions == NULL) { printf("ERROR: data_instructions est NULL dans allocate_variables"); return; }
	


	//Calculer le nombre total d'éléments à allouer (séparés par des virgules)
	int size_new_seg = 0;
	for(int i=0; i<data_count; i++) {
		char *temp = strdup(data_instructions[i]->operand2);
		char *tok = strtok(temp, ",");
		while (tok) {
			size_new_seg++;
			tok = strtok(NULL, ",");
		}
		free(temp);
	}
	
	//Trouver un segment libre assez grand et créer "DS"
	Segment *current = cpu->memory_handler->free_list;
	while (current) {
		if (current->size >= size_new_seg) {
			create_segment(cpu->memory_handler, "DS", current->start, size_new_seg); //Pour avoir le start dynamiquement
			break;
		}
		current = current->next;
	}

	

	//Vérifier que le segment "DS" existe bien
	Segment* ds=hashmap_get(cpu->memory_handler->allocated, "DS");
	if(ds == NULL) {
		printf("ERROR: ds est NULL dans allocate_variables");
		return ;
	}


	//Remplir "DS" avec les valeurs extraites des instructions .DATA
	int mem_adr=0;
	for(int i=0; i<data_count; i++) {
		
		char *data = strdup(data_instructions[i]->operand2);  // copie

		 // Cas multiple valeurs séparées par des virgules
		if (strchr(data, ',')) {
			char *token = strtok(data, ",");
			while (token != NULL) {
				int *val = malloc(sizeof(int));
				
				if(val == NULL){
					printf("ERROR: malloc int dans allocate_variables\n");
					return;
				}

				sscanf(token, "%d", val); //convertir en int
				store(cpu->memory_handler, "DS", mem_adr++, val);
				token = strtok(NULL, ",");
			}
		
		} 
		 // Cas unique
		else {
		
			int *val = malloc(sizeof(int));

			if(val == NULL){
				printf("ERROR: malloc int dans allocate_variables\n");
				return;
			}

			sscanf(data, "%d", val); //convert char* to int
			store(cpu->memory_handler, "DS", mem_adr++, val);
		}

		free(data);// libérer la copie de la chaîne
	}
}

//Fonction pour afficher le contenu du segment de données 'DS'
void print_segment_data(CPU *cpu, const char *segment_name) {
	if(cpu == NULL) return;

	// Récupère le segment alloué correspondant au nom
	Segment* seg = hashmap_get(cpu->memory_handler->allocated, segment_name);

	if (seg == NULL) {
		printf("ERROR: Segment %s \n", segment_name);
		return;
	}

	printf("\n%s Segment\n\n", segment_name);
	// Parcourt le segment et affiche chaque case mémoire
	for (int i = 0; i < seg->size; i++) {
		int* val = load(cpu->memory_handler, segment_name, i);
		if (val != NULL) {
			printf("%d: %d\n", i, *val); // affiche la valeur si elle existe
		} else {
			printf("%d: (NULL)\n", i); // sinon affiche NULL
		}
	}
}

//Fonction dédiée à l'affichage du segment de données "DS"
void print_data_segment(CPU *cpu) {
	print_segment_data(cpu, "DS");
}

//Fonction pour vérifie si l'opérand correspond a un adressage imédiat
void *immediate_addressing(CPU *cpu, const char *operand){

	// Vérifie que l'opérande est valide et que le CPU est valide
	if (matches("^[0-9]+$", operand) && (cpu != NULL)) {

		// Si la constante n'est pas déjà dans le pool, on l'ajoute
		if(hashmap_get(cpu->constant_pool, operand) == NULL) {
			int *val = malloc(sizeof(int));

			if(val == NULL){
				printf("ERROR: malloc int dans immediate_addressing\n");
				return NULL;
			}

			*val=atoi(operand); //Conversion chaîne -> entier
			hashmap_insert(cpu->constant_pool, operand, val); //Stocke dans la table de constantes
			return (void *) val;
		} else {
			// Si déjà présente, on la retourne directement
			return hashmap_get(cpu->constant_pool, operand);
		}
	}

	// Si l'opérande ne correspond pas à une constante, retourne NULL
	return NULL;
}

//Fonction pour vérifie si l'opérand correspond a un adressage par registre
void *register_addressing(CPU *cpu, const char *operand) {

	//Si l'opérande correspond à un registre valide et que le CPU est non nul
	if (matches("^(AX|BX|CX|DX)$",operand) && (cpu != NULL)) {
		//Retourne la valeur associée au registre dans le contexte du CPU
		return hashmap_get(cpu->context, operand);
	}

	return NULL;
}

//Fonction pour vérifie si l'opérand correspond a un adressage direct
void *memory_direct_addressing(CPU *cpu, const char *operand) {

	// Vérifie que l'opérande est bien sous forme [nombre] et que cpu n'est pas NULL
	if (matches("^\\[([0-9]+)\\]$", operand) && (cpu != NULL)) {
		int address = atoi(operand + 1);	//Convertit l'adresse sous forme de chaîne en entier
											//On saute le premier caractère '[' avec operand + 1

		//Récupère le segment de données "DS"
		Segment* ds=hashmap_get(cpu->memory_handler->allocated, "DS");

		//Vérifie que le segment existe et que l'adresse est valide
		if (ds == NULL || address >= ds->size) {
			return NULL;  //Adresse invalide ou hors des limites du segment
		}

		//Retourne la donnée à l'adresse spécifiée dans le segment DS
		return load(cpu->memory_handler, "DS", address);
	}

	//Si ce n'est pas un adressage direct valide, retourne NULL
	return NULL;
}

//Fonction pour vérifie si l'opérand correspond a un adressage indirect par registre
void *register_indirect_addressing(CPU *cpu, const char *operand) {

	//Vérifie si l'opérande est du type [AX], [BX], [CX] ou [DX]
	if(matches("^\\[(AX|BX|CX|DX)\\]$", operand) && (cpu != NULL)){
		//On extrait le nom du registre (entre les crochets)
		//Exemple : operand = "[AX]" -> reg_name = "AX"
		char reg_name[3];
		reg_name[0] = operand[1];
		reg_name[1] = operand[2];
		reg_name[2] = '\0';

		// On récupère la valeur contenue dans le registre 
		int* val = (int*) hashmap_get(cpu->context, reg_name);
		if(val == NULL) return NULL;


		// On utilise cette adresse pour accéder à une donnée dans le segment DS
		int addr = *val;
		return load(cpu->memory_handler, "DS", addr);
	}

	return NULL;
}

// Fonction pour déterminer automatiquement le type d'adressage utilisé par l'opérande
void *resolve_addressing(CPU *cpu, const char *operand) {
	if(cpu == NULL) return NULL;

	//Vérifie si l'opérande est une valeur immédiate (ex: "5")
	void* t = immediate_addressing(cpu, operand);
	if(t != NULL) { return t; }


	//Vérifie si c'est un registre (ex: "AX")
	t = register_addressing(cpu, operand);
	if(t != NULL) { return t; }

	//Vérifie si c'est une adresse directe en mémoire (ex: "[4]")
	t = memory_direct_addressing(cpu, operand);
	if(t != NULL) { return t; }

	//Vérifie si c'est un adressage indirect via registre (ex: "[AX]")
	t = register_indirect_addressing(cpu, operand);
	if(t != NULL) { return t; }

	//Vérifie si c'est un adressage avec override de segment (ex: "ES:[5]")
	t = segment_override_addressing(cpu, operand);
	if(t != NULL) { return t; }

	// Si aucun type d'adressage ne correspond
	return NULL;
}

//Fonction qui simule l'instruction MOV (copie la valeur de la source vers la destination)
void handle_MOV(CPU* cpu, void* src, void* dest){
	if(src == NULL || dest == NULL) return;
	
	// On copie la valeur pointée par src dans la zone mémoire pointée par dest
	*((int*)dest) = *((int*)src);
}


char *trim(char *str) {
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r') str++;

	char *end = str + strlen(str) - 1;
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

    // Iterate through all keys in the hashmap
    for (int i = 0; i < values->size; i++) {
        if (values->table[i].key && values->table[i].key != (void *)-1) {
            char *key = values->table[i].key;
            int value = (int)(long)values->table[i].value;

            // Find potential substring match
            char *substr = strstr(input, key);
            while (substr) {
                // Construct replacement buffer
                char replacement[64];
                snprintf(replacement, sizeof(replacement), "%d", value);

                // Calculate lengths
                int key_len = strlen(key);
                int repl_len = strlen(replacement);
                int remain_len = strlen(substr + key_len);

                // Create new string
                char *new_str = (char *)malloc(strlen(input) - key_len + repl_len + 1);
                if (!new_str) return 0;  // Handle allocation failure

                // Copy part before the key
                strncpy(new_str, input, substr - input);
                new_str[substr - input] = '\0';

                // Append replacement value
                strcat(new_str, replacement);

                // Append the part after the key
                strcat(new_str, substr + key_len);

                // Free and update original string
                free(input);
                *str = new_str;
                input = new_str;

                replaced = 1;

                // Look for the next occurrence of the same key in the string
                substr = strstr(input, key);
            }
        }
    }

    // Trim the final string
    if (replaced) {
        char *trimmed = trim(input);
        if (trimmed != input) {
            memmove(input, trimmed, strlen(trimmed) + 1);
        }
    }

    return replaced;
}



//Remplace les labels (ex: "loop" → "1")
void replace_label(Instruction *instr, HashMap *labels) {
	if ((instr == NULL) || (labels == NULL)) return;

	// Remplacement sur operand1
	if (instr->operand1) {
		int *p = hashmap_get(labels, instr->operand1);
		if (p) {
			char buf[32];
			snprintf(buf, sizeof(buf), "%d", *p); //écrit la valeur entière pointée par p dans le buffer 'buf' sous forme de chaîne
			free(instr->operand1);
			instr->operand1 = strdup(buf);
		}
	}

	// Remplacement sur operand2
	if (instr->operand2) {
		int *p = hashmap_get(labels, instr->operand2);
		if (p) {
			char buf[32];
			snprintf(buf, sizeof(buf), "%d", *p); //écrit la valeur entière pointée par p dans le buffer 'buf' sous forme de chaîne
			free(instr->operand2);
			instr->operand2 = strdup(buf);
		}
	}
}

//Remplace les variables mémoire entre crochets (ex: "[X]" → "[0]")
void replace_memvar(Instruction *instr, HashMap *memloc) {
	if ((instr == NULL) || (memloc == NULL)) return;

	for (int k = 0; k < 2; k++) {
		// Sélectionne operand1 puis operand2
		char **op = (k == 0 ? &instr->operand1 : &instr->operand2);
		
		if (!*op || strlen(*op) < 3) continue; 
		
		size_t len = strlen(*op);

		// Vérifie la forme minimale "[X]"
		if (len >= 3 && (*op)[0] == '[' && (*op)[len-1] == ']') {
			// on extrait le nom sans les crochets
			char name[64] = {0}; 
			memcpy(name, *op + 1, len - 2);
			name[len-2] = '\0';

			// Recherche l'adresse mémoire dans la table
			int *p = hashmap_get(memloc, name);
			if (p) {
				// Reconstruit l'operand avec l'adresse "[adresse]"
				char buf[32];
				snprintf(buf, sizeof(buf), "[%d]", *p); //écrit la valeur entière pointée par p dans le buffer 'buf' sous forme de chaîne
				free(*op);
				*op = strdup(buf);
			}
		}
	}
}

// Applique les remplacements de labels et variables mémoire à toutes les instructions du code
int resolve_constants(ParserResult *result) {
	if (result == NULL) return -1;

	// Parcours toutes les instructions du code
	for (int i = 0; i < result->code_count; i++) {
		Instruction *instr = result->code_instructions[i];
		// 1) labels
		replace_label(instr, result->labels);
		// 2) variables mémoire
		replace_memvar(instr, result->memory_locations);
	}
	return 0;
}

//Fonction qui alloue et initialise le segment de code 'CS' et le registre IP
void allocate_code_segment(CPU *cpu, Instruction **code_instructions, int code_count) {
	if(cpu == NULL || code_instructions == NULL) return;


	// Parcours la liste des segments libres pour trouver un segment de taille suffisante
	Segment *current = cpu->memory_handler->free_list;
	while (current) {
		if (current->size >= code_count) {
			create_segment(cpu->memory_handler, "CS", current->start, code_count); //Crée un segment de code (CS)
		}
		current = current->next;
	}
	

	// Récupère le segment 'CS'
	Segment* cs = hashmap_get(cpu->memory_handler->allocated, "CS");
	if(cs == NULL) return ;

	// Place les instructions dans le segment de code 'CS'
	for(int i=0; i<code_count; i++) {
		cpu->memory_handler->memory[cs->start + i] = code_instructions[i];
		code_instructions[i] = NULL;
	}

	 // Récupère et initialise le registre 'IP' à 0
	int* ip = hashmap_get(cpu->context,"IP");
	if(ip != NULL)
		*ip = 0;
}

//Fonction qui identifie l'instruction et l'execute
int handle_instruction(CPU *cpu, Instruction *instr, void *dst, void *src) {
	if(cpu == NULL || instr == NULL) return -1;

	// Si l'instruction est "MOV"
	if (strcmp(instr->mnemonic, "MOV") == 0) {
		// MOV dst, src : Copie la valeur de src dans dst
		*((int*)dst) = *((int*)src);
	}
	 // Si l'instruction est "ADD"
	else if (strcmp(instr->mnemonic, "ADD") == 0) {
		// ADD dst, src : Additionne les valeurs de dst et src, puis stocke le résultat dans dst
		int *d = dst, *s = src;
		*d = *d + *s;
	}
	// Si l'instruction est "CMP" 
	else if (strcmp(instr->mnemonic, "CMP") == 0) {
		// CMP dst, src : Effectue une soustraction logique (dst - src), et met à jour les drapeaux ZF et SF
		int d = *((int*)dst), s = *((int*)src);
		int *zf = hashmap_get(cpu->context, "ZF");
		int *sf = hashmap_get(cpu->context, "SF");
		*zf = (d == s);
		*sf = (d < s);
	}
	 // Si l'instruction est "JMP" 
	else if (strcmp(instr->mnemonic, "JMP") == 0) {
		// JMP address : Met à jour le registre IP avec l'adresse spécifiée
		int *ip = hashmap_get(cpu->context, "IP");
		*ip = *((int*)src);
	}
	// Si l'instruction est "JZ"
	else if (strcmp(instr->mnemonic, "JZ") == 0) {
		// JZ address : Saut à l'adresse spécifiée si ZF == 1
		int *ip = hashmap_get(cpu->context, "IP");
		int *zf = hashmap_get(cpu->context, "ZF");
		if (*zf) *ip = *((int*)src);
	}
	// Si l'instruction est "JNZ" (saut conditionnel si ZF == 0)
	else if (strcmp(instr->mnemonic, "JNZ") == 0) {
		// JNZ address : Saut à l'adresse spécifiée si ZF == 0
		int *ip = hashmap_get(cpu->context, "IP");
		int *zf = hashmap_get(cpu->context, "ZF");
		if (!*zf) *ip = *((int*)src);
	}
	// Si l'instruction est "HALT"
	else if (strcmp(instr->mnemonic, "HALT") == 0) {
		// HALT : Met à jour le registre IP pour arrêter l'exécution
		Segment *cs = hashmap_get(cpu->memory_handler->allocated, "CS");
		int *ip = hashmap_get(cpu->context, "IP");
		*ip = cs->size;
	} 
	// Si l'instruction est "PUSH" 
	else if (strcmp(instr->mnemonic, "PUSH")==0) {
		// PUSH src : Empile la valeur de src (ou de AX si src est NULL) sur la pile
		int *s = (src == NULL) ? hashmap_get(cpu->context, "AX") : src;
		push_value(cpu, *s);
	}
	// Si l'instruction est "POP"
	else if (strcmp(instr->mnemonic, "POP")==0) {
		// POP dst : Dépile une valeur de la pile et la stocke dans dst (ou dans AX si dst est NULL)
		int *d = (dst == NULL) ? hashmap_get(cpu->context, "AX") : dst;
		pop_value(cpu, d);
	}
	// Si l'instruction est "ALLOC"
	else if (strcmp(instr->mnemonic, "ALLOC")==0){
		// ALLOC : Alloue un segment ES
		alloc_es_segment(cpu);
	}
	// Si l'instruction est "FREE"
	else if(strcmp(instr->mnemonic, "FREE")==0){
		// FREE : Libère un segment ES
		free_es_segment(cpu);
	}

	return 0;
}

//Fonction qui execute l'instruction
int execute_instruction(CPU *cpu, Instruction *instr) {
	if (instr == NULL) { printf("[ERROR]Instruciton is NULL\n"); return -1; }
	if (cpu == NULL) { printf("[ERROR]CPU is NULL\n"); return -1; }

	void *src = NULL, *dst = NULL;
	
	// Cas pour l'instruction PUSH :
	if (strcmp(instr->mnemonic, "PUSH") == 0) {
		// Résolution de l'opérande source (l'adresse de la valeur à empiler)
		int *src = resolve_addressing(cpu, instr->operand1);
		if (!src) return -1;
		return push_value(cpu, *src);
	}

	// Cas pour l'instruction POP :
	if (strcmp(instr->mnemonic, "POP") == 0) {
		// Résolution de l'opérande destination (l'adresse où stocker la valeur dépilée)
		int *dst = resolve_addressing(cpu, instr->operand1);
		if (!dst) return -1;
		return pop_value(cpu, dst);
	}

	// Cas pour les instructions avec deux opérandes : MOV, ADD, CMP
	if (strcmp(instr->mnemonic, "MOV") == 0
		|| strcmp(instr->mnemonic, "ADD") == 0
		|| strcmp(instr->mnemonic, "CMP") == 0 ){

		// Résolution des deux opérandes (source et destination)
		dst = resolve_addressing(cpu, instr->operand1);
		src = resolve_addressing(cpu, instr->operand2);

		if(dst == NULL || src == NULL) return -1; 

		return handle_instruction(cpu, instr, dst, src); 
	}

	// Cas pour les instructions avec un seul opérande : JMP, JZ, JNZ
	if (strcmp(instr->mnemonic, "JMP") == 0
		|| strcmp(instr->mnemonic, "JZ")  == 0
		|| strcmp(instr->mnemonic, "JNZ") == 0) {

		// Résolution de l'opérande source (adresse vers laquelle sauter)
		src = resolve_addressing(cpu, instr->operand1);

		if(src == NULL) return -1; 
		
		return handle_instruction(cpu, instr, NULL, src); 
	}



	// Cas pour les instructions sans opérandes : HALT, ALLOC, FREE
	if (strcmp(instr->mnemonic, "HALT") == 0
		|| strcmp(instr->mnemonic, "ALLOC") == 0
		|| strcmp(instr->mnemonic, "FREE") == 0) {

		return handle_instruction(cpu, instr, NULL, NULL);
	}


	return 0;
}

//Fonction qui récupère la prochaine instruction à exécuter
Instruction* fetch_next_instruction(CPU *cpu) {
	if(cpu == NULL) return NULL;

	// Récupère le segment de code 'CS' (Code Segment)
	Segment* CS = hashmap_get(cpu->memory_handler->allocated, "CS");

	// Récupère le registre d'instruction pointer 'IP'
	int* IP = hashmap_get(cpu->context,"IP");

	// Vérifie que le registre IP et le segment CS sont valides, et que l'IP est inférieur à la taille du segment CS
	if(( IP != NULL) && (CS != NULL) && (*IP < CS->size)) { 
		// Charge l'instruction située à l'adresse indiquée par IP dans le segment 'CS'
		Instruction* instr = load(cpu->memory_handler, "CS", *IP);
		(*IP)++;
		return instr; // Retourne l'instruction chargée
	}

	return NULL;
}

//Fonction qui exécute le programme et affiche l'état final du CPU
int run_program(CPU *cpu) {
	if(cpu == NULL) return -1;

	char q = 'd';
	printf("\n=== État initial du CPU ===\n");
	print_cpu(cpu);

	// Récupère le segment de code (CS) à partir de la mémoire du CPU
	Segment* CS = hashmap_get(cpu->memory_handler->allocated, "CS");
	if(CS == NULL){ printf("ERROR: CS est NULL dans run_program\n"); return -1; }


	// Boucle infinie pour simuler l'exécution du programme
	while (1){

		// Récupère l'instruction suivante à exécuter
		Instruction* instr = fetch_next_instruction(cpu);
		

		// Si l'instruction est NULL, cela signifie que le programme a atteint la fin (IP hors limites)
		if(instr == NULL){
			printf("\nFin du programme (IP hors limites)\n");
			break;
		}
		
		// Affiche l'instruction en cours d'exécution
		printf("\nExécution de : %s %s %s\n", 
			instr->mnemonic, 
			instr->operand1 ? instr->operand1 : "",
			instr->operand2 ? instr->operand2 : "");
		
		// Exécute l'instruction
		execute_instruction(cpu, instr);
		
		// Récupère le segment "SS" pour l'affichage de la pile
		Segment* ss = hashmap_get(cpu->memory_handler->allocated, "SS");
		
		// Si le segment SS est introuvable, afficher une erreur et continuer avec la boucle
		if(ss == NULL) {
			printf("ERROR: SS est NULL dans run_program\n");
			continue;
		}

		// Affiche les valeurs de la pile à partir de l'index 120 jusqu'à la fin du segment "SS"
		for(int i=120; i<ss->size; i++){	
			int* v = load(cpu->memory_handler, "SS", i); // Charge la valeur à l'adresse i du segment SS
			if(v == NULL) {
				printf("%d => %p \n", i, v);
			} else {
				printf("%d => %d \n", i, *v);
			}
						
		}
		
		// Demande à l'utilisateur de continuer ou de quitter
		printf("\nAppuyez sur Entrée pour continuer (q pour quitter)...");
		scanf("%c", &q);
		if(q=='q') break;
	}

	printf("\n=== État final du CPU ===\n");
	print_cpu(cpu);

	return 0;
}

//Fonction pour récuperer le segment 'ss'
int push_value(CPU *cpu, int value) {

	// Récupère le segment de pile 'SS' dans la mémoire du CPU
	Segment *ss = hashmap_get(cpu->memory_handler->allocated, "SS");

	// Récupère le pointeur de pile 'SP' dans le contexte du CPU
	int *sp = hashmap_get(cpu->context, "SP");
	
	// Si le segment de pile ou le pointeur de pile est NULL, on retourne une erreur
	if((ss==NULL) || (sp == NULL)) {
		printf("ERROR: ss ou sp est vide dans push_value\n");
		return -1;
	}

	(*sp)--;

	// Si le pointeur de pile devient plus petit que l'adresse de début du segment SS, on retourne une erreur
	if (*sp <= ss->start) return -1;

	int *cell = malloc(sizeof(int));
	
	if(cell == NULL) {
		printf("ERROR: cell est vide dans push_value\n");
		return -1;
	}
	// Place la valeur dans la cellule allouée
	*cell = value;

	// Place la cellule dans la mémoire du CPU à l'adresse pointée par SP
	cpu->memory_handler->memory[*sp] = cell;

	return 0;
}

//Fonction pour lire la valeur pointée par memory[SP], la copie et libere la memoire
int pop_value(CPU *cpu, int *dest) {
	// Récupère le segment de pile 'SS' et le pointeur de pile 'SP'
	Segment *ss = hashmap_get(cpu->memory_handler->allocated, "SS");
	int *sp = hashmap_get(cpu->context, "SP");

	// Si le segment de pile ou le pointeur de pile est NULL, on retourne une erreur
	if((ss==NULL) || (sp == NULL)) {
		printf("ERROR: ss ou sp est vide dans pop_value\n");
		return -1;
	}

	// Si le pointeur de pile dépasse la fin de la pile, on retourne une erreur
	if (*sp >= ss->start + ss->size) return -1;

	// Récupère la valeur à dépiler
	int *cell = cpu->memory_handler->memory[*sp];
	if (!cell) return -1;

	// Copie la valeur dans la variable 'dest'
	*dest = *cell;

	// Libère la mémoire allouée pour la valeur
	free(cell);
	cpu->memory_handler->memory[*sp] = NULL;
	
	// Incrémente le pointeur de pile
	(*sp)++;
	
	return 0;
}


//Fonction qui vérifie si l'operande correspond a ce type d'adressage
void* segment_override_addressing(CPU* cpu, const char* operand){
	if (cpu == NULL) return NULL;

	// Le motif attendu pour l'opérande : [XX:YY]
	const char* pattern = "\\[[A-Z]{2}:[A-Z]{2}\\]";


	// Si l'opérande ne correspond pas au motif, retourner NULL
	if (!matches(pattern, operand)){
		return NULL;
	}
	
	// Variables pour stocker le segment et le registre extraits
	char seg[3];
	char reg[3];
	
	// Extraction du segment et du registre à partir de l'opérande
	sscanf(operand, "[%2[^:]:%2[^]]]", seg, reg);
	
	seg[2] = '\0';
	reg[2] = '\0';

	// Récupération de la valeur du registre
	int* reg_value = hashmap_get(cpu->context, reg);
	if (!reg_value) return NULL;

	// Récupération du segment
	Segment* segment = hashmap_get(cpu->memory_handler->allocated, seg);
	if (!segment || *reg_value < 0 || *reg_value >= segment->size) {
		printf("[ERROR] OUT OF BOUND\n");
		return NULL;
	}

	// Retourne la valeur de la mémoire à l'adresse indiquée par le registre
	return load(cpu->memory_handler, seg, *reg_value);
}

//Fonction qui trouve un segment libre selon la strategie utilisé
int find_free_address_strategy(MemoryHandler *handler, int size, int strategy){
	if(handler == NULL) return -1;

	Segment *selected = NULL;
	Segment *current = handler->free_list;

	// Parcours des segments libres
	while(current != NULL) {
		if(current->size > size) { // Si le segment est assez grand

			// Stratégie 0 : Première adresse libre
			if(strategy == 0) {
				return current->start;
			} 
			// Stratégie 1 : Chercher le plus petit segment suffisant
			else if(strategy == 1) {
				if(!selected || (current->size < selected->size)) {
					selected = current;
				}
			} 
			// Stratégie 2 : Chercher le plus grand segment suffisant
			else if(strategy == 2) {
				if(!selected || (current->size > selected->size)) {
					selected = current;
				}
			}
		}
		current = current->next;
	}

	// Si un segment a été sélectionné, on retourne son adresse de départ
	return (selected)? selected->start: -1;
}

//Fonction qui alloue le segment 'ES'
int alloc_es_segment(CPU *cpu){
	if(cpu == NULL) return -1;

	// Si le segment 'ES' existe déjà, on le libère
	if (hashmap_get(cpu->memory_handler->allocated, "ES") != NULL) {
		free_es_segment(cpu);
	}


	// Récupère les valeurs des registres nécessaires
	int *AX = hashmap_get(cpu->context, "AX");
	int *BX = hashmap_get(cpu->context, "BX");
	int *ZF = hashmap_get(cpu->context, "ZF");
	int *ES = hashmap_get(cpu->context, "ES");

	// Si l'un des registres est NULL, on retourne une erreur
	if((AX == NULL) || (BX == NULL) || (ZF == NULL) || (ES == NULL)) {
		printf("ERROR: AX ou BX ou ZF ou ES est NULL dans alloc_es_segment\n");
		return -1;
	}
	
	// Recherche d'une adresse libre pour allouer le segment
	int addr = find_free_address_strategy(cpu->memory_handler, *AX, *BX);
	if(addr == -1) {
		*ZF=1; // Erreur : aucun espace libre
		return -1;
	}
	
	// Création du segment 'ES'
	if (create_segment(cpu->memory_handler, "ES", addr, *AX) == -1) {
		*ZF = 1;  // Échec de la création
		return -1;
	}

	// Initialisation de la mémoire du segment 'ES'
	for(int i=0; i<*AX; i++) {
		int* v = malloc(sizeof(int));
		if(v == NULL){
			printf("ERROR: malloc int est NULL dans alloc_es_segment\n");
			return -1;
		}

		*v = 0;
		cpu->memory_handler->memory[addr + i] = (void *) v; 
	}
	
	// Mise à jour des registres
	*ZF=0;
	*ES=addr;
	
	return 0;
}

//Fonction pour liberer la memoire du segment 'ES'
int free_es_segment(CPU *cpu) {
	if(cpu == NULL) return -1;

	// Vérifie si le segment ES a déjà été libéré
	int *ES_reg = hashmap_get(cpu->context, "ES");
	if (*ES_reg == -1) return -1; //Deja liberer


	// Récupère le segment ES
	Segment *es_seg = hashmap_get(cpu->memory_handler->allocated, "ES");
	if (es_seg == NULL) {
		printf("ERROR: segment ES est NULL\n");
		return -1;
	}


	// Libérer chaque donnée stockée dans le segment ES
	for (int i = 0; i < es_seg->size; i++) {
		void *data = load(cpu->memory_handler, "ES", i);
		if (data != NULL) {
			store(cpu->memory_handler, "ES", i, NULL);  // Reset mémoire
		}
	}

	// Supprimer le segment et mettre à jour le registre ES
	if (remove_segment(cpu->memory_handler, "ES") == 0) {
		int *es_reg = hashmap_get(cpu->context, "ES");
		if (es_reg) *es_reg = -1;
		return 0;
	}

	return -1;
}
