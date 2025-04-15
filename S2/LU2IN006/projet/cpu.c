#include "cpu.h"
#include <string.h>
#include <stdio.h>
#include <regex.h>

CPU *cpu_init(int memory_size) {
    CPU *res = malloc(sizeof(CPU));
    res->memory_handler = memory_init(memory_size);
    res->context = hashmap_create();
    res->constant_pool = hashmap_create();

    int *AX = malloc(sizeof(int));
    int *BX = malloc(sizeof(int));
    int *CX = malloc(sizeof(int));
    int *DS = malloc(sizeof(int));
    int *IP = malloc(sizeof(int));
    int *ZF = malloc(sizeof(int));
    int *SF = malloc(sizeof(int));
    
    
    int *SP = malloc(sizeof(int));
    int *BP = malloc(sizeof(int));
    
    create_segment(res->memory_handler, "SS", 0, 128);


	*AX=0;
    *BX=0;
    *CX=0;
    *DS=0;
    *IP = 0;
    *ZF = 0;
    *SF = 0;
    


    void* ss = hashmap_get(res->memory_handler->allocated, "SS");
    SP=ss;
    BP=ss;


    hashmap_insert(res->context, "AX", (void*) AX);
    hashmap_insert(res->context, "BX", (void*) BX);
    hashmap_insert(res->context, "CX", (void*) CX);
    hashmap_insert(res->context, "DX", (void*) DS);

    hashmap_insert(res->context, "IP", (void*) IP);
    hashmap_insert(res->context, "ZF", (void*) ZF);
    hashmap_insert(res->context, "SF", (void*) SF);

    hashmap_insert(res->context, "SP", (void*) SP);
    hashmap_insert(res->context, "BP", (void*) BP);

    return res;
}


//REGARDER allocate_code_segment qui est similaire
int push_value(CPU *cpu, int value) { //refaire et verifier
    Segment* ss = hashmap_get(res->memory_handler->allocated, "SS");
    
    int cpt=0;
    while(ss->next != NULL) {
        ss = ss->next;
        cpt++;
    }

    if(cpt >= ss->size){
        return -1;
    }

    Segment *new_seg = malloc(sizeof(Segment));
    new_seg->start = ss->start; //potientiel erreur
    new_seg->size = ss->size;
    new_seg->next = NULL;
    ss->next = new_seg;
    cpu->memory_handler->memory[new_seg->start + new_seg->size] = value; //Pas sur 

    Segment* sp = hashmap_get(cpu->context, "SP");
    *sp=*new_seg;

    return 0;
}

int pop_value(CPU *cpu, int *dest) {
    Segment* ss = hashmap_get(res->memory_handler->allocated, "SS");
    if(ss==NULL){
        return -1;
    }

    while(ss->next != NULL) {
        ss = ss->next;
    }

    *dest = cpu->memory_handler->memory[ss->start + ss->size];
    Segment* sp = hashmap_get(cpu->context, "SP");
    sp=ss;
    return 0;
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
    //free_memoryHandler(cpu->memory_handler);
    free(cpu);
}


void* store(MemoryHandler *handler, const char *segment_name, int pos, void *data) {
    
    Segment* seg=hashmap_get(handler->allocated, segment_name);
    if((seg != NULL) && (pos <= seg->size)){
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

    printf("%d \n", size_new_seg); //FONCITONE ICI

    create_segment(cpu->memory_handler, "DS", 0, size_new_seg);


    int mem_adr=0;
    for(int i=0; i<data_count; i++) {
        if(strchr(data_instructions[i]->operand2,',')){
            char *token = strtok(data_instructions[i]->operand2, ",");
            while (token != NULL) {
                int *dat = malloc(sizeof(int));

                sscanf(token, "%d", dat); //convert char* to int
                store(cpu->memory_handler, "DS", mem_adr,(void*) dat);

                mem_adr++;
                token = strtok(NULL, ",");
            }
        } else {
            int *dat = malloc(sizeof(int));

            sscanf(data_instructions[i]->operand2, "%d", dat); //convert char* to int


            store(cpu->memory_handler, "DS", mem_adr,(void*) dat);
        }
    }
}


void print_data_segment(CPU *cpu) {
    Segment* ds=hashmap_get(cpu->memory_handler->allocated, "DS");
    for (int i=0; i< ds->size; i++) {
        int* a = load(cpu->memory_handler, "DS", i);
        if (a != NULL) {
            printf("%d: %d\n", i, *a);
        }
        
    }
    
}

void *immediate_addressing(CPU *cpu, const char *operand){
    if (matches("^[0-9]+$",operand)==0) {
        if(hashmap_get(cpu->constant_pool, operand) == NULL) {
            int *i = malloc(sizeof(int));
	        *i=atoi(operand);
            hashmap_insert(cpu->constant_pool, operand,i);
            return (void*)i;
        }
    }
    return NULL;
}


void *register_addressing(CPU *cpu, const char *operand) {
    if (matches("^(AX|BX|CX|DX)$",operand)==0) {
        if(hashmap_get(cpu->context, operand)!=NULL) {
            return hashmap_get(cpu->context, operand);
        }
    }
    return NULL;
}

void *memory_direct_addressing(CPU *cpu, const char *operand) {
    if (matches("^\[[0-9]+$", operand)==0) {
        char addr[50];
        sscanf(operand, "[%[^]]", addr);
        // A finir
    }
}

void *register_indirect_addressing(CPU *cpu, const char *operand) {

}


void* segment_override_addressing(CPU* cpu, const char* operand){
    char SEGMENT[100];
	char REGISTRE[100];
    if (matches("\[[a-zA-Z]{2}:[a-zA-Z]{2}\]$",operand)==0) {
        sscanf(operand, "[%[^:]:%s]", SEGMENT, REGISTRE);
        //recherche dans cpu de SEGMENT et renvoie l'addresse dans memory
    }
}


/*
void handle_MOV(CPU* cpu, void* src, void* dest){
    
}
*/

CPU* setup_test_environment() {
    CPU* cpu = cpu_init(1024);
    if(!cpu)  {
        printf("Error: CPU initialization failed \n");
        return NULL;
    }

    int *ax = (int*) hashmap_get(cpu->context, "AX");
    int *bx = (int*) hashmap_get(cpu->context, "BX");
    int *cx = (int*) hashmap_get(cpu->context, "CX");
    int *dx = (int*) hashmap_get(cpu->context, "DX");

    *ax = 3;
    *bx = 6;
    *cx = 100;
    *dx = 0;

    if(hashmap_get(cpu->memory_handler->allocated, "DS")) {
        create_segment(cpu->memory_handler, "DS", 0, 20);

        for(int i=0; i<10; i++) {
            int *value = (int*) malloc(sizeof(int));
            *value = i*10+5;
            store(cpu->memory_handler, "DS", i, value);
        }
    }

    printf("Test environment initialized \n");
    return cpu;
}

void allocate_code_segment(CPU *cpu, Instruction **code_instructions, int code_count) {
    create_segment(cpu->memory_handler, "CS", 0, code_count);
    Segment* cs = hashmap_get(cpu->memory_handler->allocated, "CS");
    
    
    for(int i=0; i<code_count; i++) {
        cpu->memory_handler[cs->start + i] = code_instructions[i];
    }

    int* ip = hashmap_get(cpu->context,"IP");
    *ip = cs->start;
}

int handle_instruction(CPU *cpu, Instruction *instr, void* src, void *dest) {
    if(strcmp(instr->mnemonic, "MOV")) {
         *dest = *str;
    } else if (strcmp(instr->mnemonic, "ADD")) {
        int *a = src;
        int *b = dest;
        *b = *a + *b;
    } else if (strcmp(instr->mnemonic, "CMP")) {
        int sr = *src;
        int des = *dest;
        int c = des - sr;
        if (sr == des) {
            //UDPATE ZF
            int* zf = (int*) hashmap_get(cpu->context,"ZF")
            *zf = 1;
        } else if(des < sr) {
            //UPDATE SF
            int* sf = (int*) hashmap_get(cpu->context,"SF");
            *sf = 1;
        }
    } else if (strcmp(instr->mnemonic, "JMP")) {
        int* ip = (int*) hashmap_get(cpu->context,"IP");
        *ip = atoi(inst->operand1);
    } else if (strcmp(instr->mnemonic, "JZ")) {
        
        if(hashmap_get(cpu->context, "ZF") != NULL) {
            int* ip = (int*) hashmap_get(cpu->context,"IP");
            *ip = atoi(inst->operand1);
        }
    } else if (strcmp(instr->mnemonic, "JNZ")) {
        if(hashmap_get(cpu->context, "ZF") == NULL) {
            int* ip = (int*) hashmap_get(cpu->context,"IP");
            *ip = atoi(inst->operand1);
        }
    } else if (strcmp(instr->mnemonic, "HALT")) {
        Segment* cs = hashmap_get(cpu->memory_handler->allocated, "CS");
        int* ip = (int*) hashmap_get(cpu->context,"IP");
        *ip = cs->start + cs->size;
    } else if (strcmp(instr->mnemonic, "PUSH")){
        //TO DO
    } else if (strcmp(instr->mnemonic, "POP")) {
        //TO DO
    }
}

Instruction* fetch_next_instruction(CPU *cpu) {
    //FINISH WITH BETTER IF
    if(hashmap_get(cpu->context,"IP") != NULL && hashmap_get(cpu->memory_handler->allocated, "CS") != NULL) {

    }

    return NULL;
}

