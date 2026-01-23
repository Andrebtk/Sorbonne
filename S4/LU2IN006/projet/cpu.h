#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "hash.h"
#include "parser.h"
#include <stdlib.h>

typedef struct cpu{
	MemoryHandler* memory_handler;  // Gestionnaire de memoire
	HashMap* context;               // Registres (AX, BX, CX, DX)
	HashMap *constant_pool;         // Table de hachage pour stocker les valeurs immdiates
} CPU;

CPU *cpu_init(int memory_size);
void cpu_destroy(CPU *cpu);
void* store(MemoryHandler *handler, const char *segment_name, int pos, void *data);
void* load(MemoryHandler *handler, const char *segment_name, int pos);
void allocate_variables(CPU *cpu, Instruction** data_instructions, int data_count);
void print_segment_data(CPU *cpu, const char *segment_name);
void print_data_segment(CPU *cpu);
void print_cpu(CPU* cpu);

void *immediate_addressing(CPU *cpu, const char *operand);
void *register_addressing(CPU *cpu, const char *operand);
void *memory_direct_addressing(CPU *cpu, const char *operand);
void *register_indirect_addressing(CPU *cpu, const char *operand);
void *resolve_addressing(CPU *cpu, const char *operand);
void handle_MOV(CPU* cpu, void* src, void* dest);


int resolve_constants(ParserResult *result);
void allocate_code_segment(CPU *cpu, Instruction **code_instructions, int code_count);
int handle_instruction(CPU *cpu, Instruction *instr, void* src, void *dest);
int execute_instruction(CPU *cpu, Instruction *instr);
Instruction* fetch_next_instruction(CPU *cpu);
int run_program(CPU *cpu);


int push_value(CPU *cpu, int value);
int pop_value(CPU *cpu, int *dest);


void* segment_override_addressing(CPU* cpu, const char* operand);
int find_free_address_strategy(MemoryHandler *handler, int size, int strategy);
int alloc_es_segment(CPU *cpu);
int free_es_segment(CPU *cpu);

#endif
