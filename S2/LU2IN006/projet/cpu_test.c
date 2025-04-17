#include "cpu.h"
#include <stdio.h>


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


	if(!hashmap_get(cpu->memory_handler->allocated, "DS")) {
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


int main() {
	/*
	// EXO 4 TEST
	CPU *cpu = cpu_init(1024);
	HashMap *hp = hashmap_create();
	ParserResult *p = parse("test_data.txt");
	//afficher_ParserResult(p);

	allocate_variables(cpu, p->data_instructions, p->data_count);
	//print_data_segment(cpu);
	//print_cpu(cpu);

	//cpu_destroy(cpu);
	free_ParserResult(p);
	free_HashMap(hp);
	*/

	/*
	// EXO 5 TEST
	CPU* cpu = setup_test_environment();

	printf("\n===== [TEST: Adressage Immédiat] =====\n");
	int* immediate1 = immediate_addressing(cpu, "42");
	int* immediate2 = immediate_addressing(cpu, "42");

	printf("Valeur immédiate 1 (42) : %d (adresse : %p)\n", *immediate1, (void*)immediate1);
	printf("Valeur immédiate 2 (42) : %d (adresse : %p)\n", *immediate2, (void*)immediate2);
	printf(">> Les deux pointeurs sont %s\n", (immediate1 == immediate2) ? "identiques (partagée)" : "différents (dupliqués)");



	printf("\n===== [TEST: Adressage par Registre] =====\n");
	int* DX = register_addressing(cpu, "DX");
	printf("Avant MOV, registre DX = %d\n", *DX);
	handle_MOV(cpu, immediate1, DX);
	printf("Après MOV, registre DX = %d\n", *DX);



	printf("\n===== [TEST: Adressage Direct Mémoire] =====\n");
	int* direct1 = memory_direct_addressing(cpu, "[4]");
	int* BX = register_addressing(cpu, "BX");

	printf("Avant MOV, mémoire à [4] = %d\n", *direct1);
	printf("Registre BX = %d\n", *BX);
	handle_MOV(cpu, BX, direct1);
	printf("Après MOV, mémoire à [4] = %d\n", *direct1);



	printf("\n===== [TEST: Adressage Indirect par Registre] =====\n");
	int* indirect1 = register_indirect_addressing(cpu, "[AX]");  // AX = 3
	int* CX = register_addressing(cpu, "CX");

	printf("Avant MOV, mémoire à [AX] (AX = 3) = %d\n", *indirect1);
	printf("Registre CX = %d\n", *CX);
	handle_MOV(cpu, CX, indirect1);
	printf("Après MOV, mémoire à [AX] (AX = 3) = %d\n", *indirect1);



	//printf("\n== Registres finaux ==\n");
	//print_cpu(cpu);

	printf("\n== Segment DS ==\n");
	print_data_segment(cpu);
	*/

	
	//EXO 6 
	CPU *cpu = cpu_init(1024);
	//print_cpu(cpu);
	
	ParserResult *p = parse("assembler2.txt");

	resolve_constants(p); //NOT WORKING YET
	//afficher_ParserResult(p);
	
	allocate_variables(cpu,  p->data_instructions, p->data_count);
	
	allocate_code_segment(cpu, p->code_instructions, p->code_count);
	
	
	//print_cpu(cpu);
	run_program(cpu);
	
	//afficher_ParserResult(p);
}