#include "cpu.h"
#include <stdio.h>

int main() {
    CPU *cpu = cpu_init(1024);
    HashMap *hp = hashmap_create();
    ParserResult *p = parse("test_data.txt");
    //afficher_ParserResult(p);

    allocate_variables(cpu, p->data_instructions, p->data_count);
    print_data_segment(cpu);

    //cpu_destroy(cpu);
    free_ParserResult(p);
	free_HashMap(hp);
}