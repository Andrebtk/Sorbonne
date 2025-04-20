#include "cpu.h"
#include <string.h>
#include <stdio.h>
#include <regex.h>



void print_cpu(CPU* cpu){
	if(cpu == NULL) {
		printf("CPU is NULL\n");
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


CPU *cpu_init(int memory_size) {
    CPU *res = malloc(sizeof(CPU));
    res->memory_handler = memory_init(memory_size);
    res->context = hashmap_create();
    res->constant_pool = hashmap_create();

	create_segment(res->memory_handler, "SS", 0, 128);

    int *AX = malloc(sizeof(int));
    int *BX = malloc(sizeof(int));
    int *CX = malloc(sizeof(int));
    int *DS = malloc(sizeof(int));
    int *IP = malloc(sizeof(int));
    int *ZF = malloc(sizeof(int));
    int *SF = malloc(sizeof(int));
    int *SP = malloc(sizeof(int));
    int *BP = malloc(sizeof(int));
	int *ES = malloc(sizeof(int));
    


	*AX=0;
    *BX=0;
    *CX=0;
    *DS=0;
    *IP=0;
    *ZF=0;
    *SF=0;
	*ES=-1;
    


    Segment* ss = hashmap_get(res->memory_handler->allocated, "SS");
    *SP=ss->size;
    *BP=ss->size;


    hashmap_insert(res->context, "AX", (void*) AX);
    hashmap_insert(res->context, "BX", (void*) BX);
    hashmap_insert(res->context, "CX", (void*) CX);
    hashmap_insert(res->context, "DX", (void*) DS);

    hashmap_insert(res->context, "IP", (void*) IP);
    hashmap_insert(res->context, "ZF", (void*) ZF);
    hashmap_insert(res->context, "SF", (void*) SF);

    hashmap_insert(res->context, "SP", (void*) SP);
    hashmap_insert(res->context, "BP", (void*) BP);

	hashmap_insert(res->context, "ES", (void*) ES);

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



void cpu_destroy(CPU *cpu) {
    free_HashMap(cpu->context);
    free_HashMap(cpu->constant_pool);
    free_memoryHandler(cpu->memory_handler);
    free(cpu);
}


void* store(MemoryHandler *handler, const char *segment_name, int pos, void *data) {
	Segment* seg=hashmap_get(handler->allocated, segment_name);
	if((seg != NULL) && (pos < seg->size)){
		handler->memory[seg->start + pos] = data;
	}

	return NULL;
}

void* load(MemoryHandler *handler, const char *segment_name, int pos) {
    Segment* seg=hashmap_get(handler->allocated, segment_name);
    if (seg != NULL) {
        return handler->memory[seg->start + pos];
    }
    return NULL;
}

void allocate_variables(CPU *cpu, Instruction** data_instructions, int data_count) {
	int size_new_seg = 0;

	for(int i=0; i<data_count; i++) {
		if(strchr(data_instructions[i]->operand2,',')) {
			char *token = strtok(data_instructions[i]->operand2, ",");
			while (token != NULL) {
				size_new_seg++;
				token = strtok(NULL, ",");
			}
		} else {
			size_new_seg++;
		}
	}
	
	
	Segment *current = cpu->memory_handler->free_list;

	while (current) {
		if (current->size >= size_new_seg) {
			create_segment(cpu->memory_handler, "DS", current->start, size_new_seg); //Pour avoir le start dynamiquement
		}
		current = current->next;
	}

	int mem_adr=0;

	Segment* ds=hashmap_get(cpu->memory_handler->allocated, "DS");


	for(int i=0; i<data_count; i++) {
		
		char *data = strdup(data_instructions[i]->operand2);

		if (strchr(data, ',')) {
			char *token = strtok(data, ",");
			while (token != NULL) {
				int *val = malloc(sizeof(int));
				sscanf(token, "%d", val); //convert char* to int
				store(cpu->memory_handler, "DS", mem_adr++, val);
				token = strtok(NULL, ",");
			}
		
		} else {
		
			int *val = malloc(sizeof(int));
			sscanf(data, "%d", val); //convert char* to int
			store(cpu->memory_handler, "DS", mem_adr++, val);
		}
		free(data);
	}
}


void print_segment_data(CPU *cpu, const char *segment_name) {
	Segment* seg = hashmap_get(cpu->memory_handler->allocated, segment_name);
	if (seg == NULL) {
		printf("Segment %s not found\n", segment_name);
		return;
	}
	printf("\n%s Segment\n\n", segment_name);
	for (int i = 0; i < seg->size; i++) {
		int* val = load(cpu->memory_handler, segment_name, i);
		if (val != NULL) {
			printf("%d: %d\n", i, *val);
		} else {
			printf("%d: (nil)\n", i);
		}
	}
}

void print_data_segment(CPU *cpu) {
	print_segment_data(cpu, "DS");
}


void *immediate_addressing(CPU *cpu, const char *operand){

	if (matches("^[0-9]+$", operand)) {
		if(hashmap_get(cpu->constant_pool, operand) == NULL) {
			int *val = malloc(sizeof(int));
			*val=atoi(operand);
			hashmap_insert(cpu->constant_pool, operand, val);
			return (void *) val;
		} else {
			return hashmap_get(cpu->constant_pool, operand);
		}
	}

	return NULL;
}

void *register_addressing(CPU *cpu, const char *operand) {

	if (matches("^(AX|BX|CX|DX)$",operand)) {
		return hashmap_get(cpu->context, operand);
	}
	return NULL;
}

void *memory_direct_addressing(CPU *cpu, const char *operand) {
	if (matches("^\\[([0-9]+)\\]$", operand)) {
		int address = atoi(operand + 1);
		Segment* ds=hashmap_get(cpu->memory_handler->allocated, "DS");

		if (ds == NULL || address >= ds->size) {
			return NULL;  // Si le segment est invalide ou l'adresse est hors limites
		}

		return load(cpu->memory_handler, "DS", address);
	}

	return NULL;
}

void *register_indirect_addressing(CPU *cpu, const char *operand) {
	if(matches("^\\[(AX|BX|CX|DX)\\]$", operand)){
		char reg_name[3];
		reg_name[0] = operand[1];
		reg_name[1] = operand[2];
		reg_name[2] = '\0';

		int* val = (int*) hashmap_get(cpu->context, reg_name);
		if(val == NULL) {
			return NULL;
		}

		int addr = *val;
		return load(cpu->memory_handler, "DS", addr);
	}

	return NULL;
}

void *resolve_addressing(CPU *cpu, const char *operand) {

	void* t = immediate_addressing(cpu, operand);
	if(t != NULL) { return t; }

	t = register_addressing(cpu, operand);
	if(t != NULL) { return t; }

	t = memory_direct_addressing(cpu, operand);
	if(t != NULL) { return t; }

	t = register_indirect_addressing(cpu, operand);
	if(t != NULL) { return t; }

	t = segment_override_addressing(cpu, operand);
	
	if(t != NULL) { return t; }

	return NULL;
}

void handle_MOV(CPU* cpu, void* src, void* dest){
	if(src == NULL || dest == NULL){
		return;
	}
	
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



// 1) Remplace les labels (ex: "loop" → "1")
void replace_label(Instruction *instr, HashMap *labels) {
    // operand1
    if (instr->operand1) {
        int *p = hashmap_get(labels, instr->operand1);
        if (p) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%d", *p);
            free(instr->operand1);
            instr->operand1 = strdup(buf);
        }
    }
    // operand2
    if (instr->operand2) {
        int *p = hashmap_get(labels, instr->operand2);
        if (p) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%d", *p);
            free(instr->operand2);
            instr->operand2 = strdup(buf);
        }
    }
}

// 2) Remplace les variables mémoire entre crochets (ex: "[X]" → "[0]")
void replace_memvar(Instruction *instr, HashMap *memloc) {
    for (int k = 0; k < 2; k++) {
        char **op = (k == 0 ? &instr->operand1 : &instr->operand2);
		if (!*op || strlen(*op) < 3) continue; // Add length check
        size_t len = strlen(*op);
        if (len >= 3 && (*op)[0] == '[' && (*op)[len-1] == ']') {
            // on extrait le nom sans les crochets
            char name[64] = {0}; 
            memcpy(name, *op + 1, len - 2);
            name[len-2] = '\0';
            int *p = hashmap_get(memloc, name);
            if (p) {
                char buf[32];
                snprintf(buf, sizeof(buf), "[%d]", *p);
                free(*op);
                *op = strdup(buf);
            }
        }
    }
}

int resolve_constants(ParserResult *result) {
    if (!result) return -1;

    for (int i = 0; i < result->code_count; i++) {
        Instruction *instr = result->code_instructions[i];
        // 1) labels
        replace_label(instr, result->labels);
        // 2) variables mémoire
        replace_memvar(instr, result->memory_locations);
    }
    return 0;
}


void allocate_code_segment(CPU *cpu, Instruction **code_instructions, int code_count) {


	Segment *current = cpu->memory_handler->free_list;

	while (current) {
		if (current->size >= code_count) {
			create_segment(cpu->memory_handler, "CS", current->start, code_count); //Pour avoir le start dynamiquement
		}
		current = current->next;
	}
	
	Segment* cs = hashmap_get(cpu->memory_handler->allocated, "CS");
	if(cs == NULL) return ;

	for(int i=0; i<code_count; i++) {
		cpu->memory_handler->memory[cs->start + i] = code_instructions[i];
		code_instructions[i] = NULL;
	}

	int* ip = hashmap_get(cpu->context,"IP");
	if(ip != NULL){
		*ip = 0;
	}
}

int handle_instruction(CPU *cpu, Instruction *instr, void *dst, void *src) {
	if (strcmp(instr->mnemonic, "MOV") == 0) {
		// MOV dst, src
		*((int*)dst) = *((int*)src);
	}
	else if (strcmp(instr->mnemonic, "ADD") == 0) {
		// ADD dst, src
		int *d = dst, *s = src;
		*d = *d + *s;
	}
	else if (strcmp(instr->mnemonic, "CMP") == 0) {
		// CMP dst, src
		int d = *((int*)dst), s = *((int*)src);
		int *zf = hashmap_get(cpu->context, "ZF");
		int *sf = hashmap_get(cpu->context, "SF");
		*zf = (d == s);
		*sf = (d < s);
	}
	else if (strcmp(instr->mnemonic, "JMP") == 0) {
		// JMP address
		int *ip = hashmap_get(cpu->context, "IP");
		*ip = *((int*)src);
	}
	else if (strcmp(instr->mnemonic, "JZ") == 0) {
		int *ip = hashmap_get(cpu->context, "IP");
		int *zf = hashmap_get(cpu->context, "ZF");
		if (*zf) *ip = *((int*)src);
	}
	else if (strcmp(instr->mnemonic, "JNZ") == 0) {
		int *ip = hashmap_get(cpu->context, "IP");
		int *zf = hashmap_get(cpu->context, "ZF");
		if (!*zf) *ip = *((int*)src);
	}
	else if (strcmp(instr->mnemonic, "HALT") == 0) {
		Segment *cs = hashmap_get(cpu->memory_handler->allocated, "CS");
		int *ip = hashmap_get(cpu->context, "IP");
		// on considère que CS démarre à 0
		*ip = cs->size;
	} 
	else if (strcmp(instr->mnemonic, "PUSH")==0) {
		int *s = (src == NULL) ? hashmap_get(cpu->context, "AX") : src;
		push_value(cpu, *s);
		
	}
	else if (strcmp(instr->mnemonic, "POP")==0) {
		int *d = (dst == NULL) ? hashmap_get(cpu->context, "AX") : dst;
		pop_value(cpu, d);
	}else if (strcmp(instr->mnemonic, "ALLOC")==0){
		alloc_es_segment(cpu);
	}else if(strcmp(instr->mnemonic, "FREE")==0){
		free_es_segment(cpu);
	}



	return 0;
}


int execute_instruction(CPU *cpu, Instruction *instr) {
    void *src = NULL, *dst = NULL;
	if (instr == NULL) {
		printf("[ERROR]Instruciton is NULL\n");
		return -1;
	}
	
	// Deux opérandes
	if (strcmp(instr->mnemonic, "MOV") == 0
		|| strcmp(instr->mnemonic, "ADD") == 0
		|| strcmp(instr->mnemonic, "CMP") == 0
		|| strcmp(instr->mnemonic, "PUSH")==0
		|| strcmp(instr->mnemonic, "POP")==0 ){
		dst = resolve_addressing(cpu, instr->operand1);
		src = resolve_addressing(cpu, instr->operand2);

		if(dst == NULL || src == NULL) return -1; 

		return handle_instruction(cpu, instr, dst, src);
	}

	// Un seul opérande (la cible)
	if (strcmp(instr->mnemonic, "JMP") == 0
		|| strcmp(instr->mnemonic, "JZ")  == 0
		|| strcmp(instr->mnemonic, "JNZ") == 0) {
		src = resolve_addressing(cpu, instr->operand1);

		if(src == NULL) return -1; 
		
		return handle_instruction(cpu, instr, NULL, src);
	}

	// Pas d'opérandes, handle_instruction s'en charge
	if (strcmp(instr->mnemonic, "HALT") == 0
		|| strcmp(instr->mnemonic, "ALLOC") == 0
		|| strcmp(instr->mnemonic, "FREE") == 0) {

		return handle_instruction(cpu, instr, NULL, NULL);
	}

	
	return 0;
}

Instruction* fetch_next_instruction(CPU *cpu) {
	Segment* CS = hashmap_get(cpu->memory_handler->allocated, "CS");
	int* IP = hashmap_get(cpu->context,"IP");
	if(( IP != NULL) && (CS != NULL) && (*IP < CS->size)) { 

		Instruction* instr = load(cpu->memory_handler, "CS", *IP);
		
		(*IP)++;
		return instr;
	}

	return NULL;
}

int run_program(CPU *cpu) {

	char q = 'd';
	printf("\n=== État initial du CPU ===\n");
	print_cpu(cpu);


	Segment* CS = hashmap_get(cpu->memory_handler->allocated, "CS");

	while (1){
		
		Instruction* instr = fetch_next_instruction(cpu);
		
		if(instr == NULL){
			printf("\nFin du programme (IP hors limites)\n");
			break;
		}

		printf("\nExécution de : %s %s %s\n", 
			instr->mnemonic, 
			instr->operand1 ? instr->operand1 : "",
			instr->operand2 ? instr->operand2 : "");
		
		

		
		execute_instruction(cpu, instr);
		
		Segment* ss = hashmap_get(cpu->memory_handler->allocated, "SS");
		for(int i=120; i<ss->size; i++){
			printf("%d => %p \n", i, load(cpu->memory_handler, "SS", i));
		}

		printf("\nAppuyez sur Entrée pour continuer (q pour quitter)...");
		scanf("%c", &q);
		if(q=='q') break;

	}

	printf("\n=== État final du CPU ===\n");
	print_cpu(cpu);

	return 0;
}


int push_value(CPU *cpu, int value) {
    Segment *ss = hashmap_get(cpu->memory_handler->allocated, "SS");
    int *sp = hashmap_get(cpu->context, "SP");

	(*sp)--;


    if (*sp < ss->start) return -1;

	int *cell = malloc(sizeof(int));
    *cell = value;
    cpu->memory_handler->memory[*sp] = cell;

    return 0;
}

int pop_value(CPU *cpu, int *dest) {
	Segment *ss = hashmap_get(cpu->memory_handler->allocated, "SS");
	int *sp = hashmap_get(cpu->context, "SP");

	if (*sp >= ss->start + ss->size - 1) return -1;

	int *cell = cpu->memory_handler->memory[*sp];
	if (!cell) return -1;

	*dest = *cell;

	free(cell);
	cpu->memory_handler->memory[*sp] = NULL;
	
	(*sp)++;
	
	return 0;
}

void* segment_override_addressing(CPU* cpu, const char* operand){
	
	const char* pattern = "\\[[A-Z]{2}:[A-Z]{2}\\]";

	if (!matches(pattern, operand)){
		return NULL;
	}
	

	char seg[3];
	char reg[3];
	
	sscanf(operand, "[%2[^:]:%2[^]]]", seg, reg);
	
	seg[2] = '\0';
	reg[2] = '\0';

	int* reg_value = hashmap_get(cpu->context, reg);
	if (!reg_value) return NULL;

	Segment* segment = hashmap_get(cpu->memory_handler->allocated, seg);
	if (!segment || *reg_value < 0 || *reg_value >= segment->size) {
		printf("[ERROR] OUT OF BOUND\n");
		return NULL;
	}

	return load(cpu->memory_handler, seg, *reg_value);
}

int find_free_address_strategy(MemoryHandler *handler, int size, int strategy){
	Segment *selected = NULL;
	Segment *current = handler->free_list;


	while(current != NULL) {

		if(current->size > size) {
			if(strategy == 0) {
				return current->start;
			} else if(strategy == 1) {
				if(!selected || (current->size < selected->size)) {
					selected = current;
				}
			} else if(strategy == 2) {
				if(!selected || (current->size > selected->size)) {
					selected = current;
				}
			}

		}
		current = current->next;
	}

	return (selected)? selected->start: -1;
}


int alloc_es_segment(CPU *cpu){
	int *AX = hashmap_get(cpu->context, "AX");
	int *BX = hashmap_get(cpu->context, "BX");
	int *ZF = hashmap_get(cpu->context, "ZF");
	int *ES = hashmap_get(cpu->context, "ES");
	
	int addr = find_free_address_strategy(cpu->memory_handler, *AX, *BX);

	if(addr == -1) {
		*ZF=1;
		return 0;
	}
	
	create_segment(cpu->memory_handler, "ES", addr, *AX);

	for(int i=0; i<*AX; i++) {
		int* v = malloc(sizeof(int));
		*v = 0;

		cpu->memory_handler->memory[addr + i] = (void *) v; 
	}
	
	*ZF=0;
	*ES=addr;
	
	return 0;
}

int free_es_segment(CPU *cpu) {
	int *ES_reg = hashmap_get(cpu->context, "ES");
	if (*ES_reg == -1) return -1; // Already freed

	// Free ES memory cells
	Segment* ES_seg = hashmap_get(cpu->memory_handler->allocated, "ES");
	if (ES_seg) {
		for (int i = 0; i < ES_seg->size; i++) {
			free(cpu->memory_handler->memory[ES_seg->start + i]);
		}
	}

	// Remove from allocated and add to free list
	remove_segment(cpu->memory_handler, "ES");
	*ES_reg = -1;

	return 0;
}