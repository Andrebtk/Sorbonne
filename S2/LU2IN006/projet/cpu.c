#include "cpu.h"
#include <string.h>
#include <stdio.h>
CPU *cpu_init(int memory_size) {
    CPU *res = malloc(sizeof(CPU));
    res->memory_handler = memory_init(memory_size);
    res->context = hashmap_create();

    int *i1 = malloc(sizeof(int));
    int *i2 = malloc(sizeof(int));
    int *i3 = malloc(sizeof(int));
    int *i4 = malloc(sizeof(int));

	*i1=0;
    *i2=0;
    *i3=0;
    *i4=0;

    hashmap_insert(res->context, "AX", (void*) i1);
    hashmap_insert(res->context, "BX", (void*) i2);
    hashmap_insert(res->context, "CX", (void*) i3);
    hashmap_insert(res->context, "DX", (void*) i4);

    return res;
}

void cpu_destroy(CPU *cpu) {
    free_HashMap(cpu->context);
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