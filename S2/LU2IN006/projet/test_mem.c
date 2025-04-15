#include "memory.h"
#include "parser.h"
#include <stdio.h>


int main() {
    HashMap *hp = hashmap_create();
    ParserResult *p = parse("assembler.txt");

    
    resolve_constants(p);
    //afficher_ParserResult(p);


    free_ParserResult(p);
	free_HashMap(hp);
}