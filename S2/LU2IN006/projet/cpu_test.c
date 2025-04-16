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

    if(hashmap_get(cpu->memory_handler->allocated, "DS")) {
        create_segment(cpu->memory_handler, "DS", 0, 20);

        for(int i=0; i<2; i++) {
            int *value = (int*) malloc(sizeof(int));
            *value = i*10+5;
            store(cpu->memory_handler, "DS", i, value);
        }
    }

    printf("Test environment initialized \n");
    return cpu;
}


int main() {
    
    CPU *cpu = cpu_init(1024);
    HashMap *hp = hashmap_create();
    ParserResult *p = parse("test_data.txt");
    //afficher_ParserResult(p);

    allocate_variables(cpu, p->data_instructions, p->data_count);
    print_data_segment(cpu);
    //print_cpu(cpu);
    
    //cpu_destroy(cpu);
    free_ParserResult(p);
	free_HashMap(hp);
    

    //CPU* cpu = setup_test_environment();
    //print_data_segment(cpu);
    

}