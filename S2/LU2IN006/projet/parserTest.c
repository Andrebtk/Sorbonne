#include "parser.h"
#include <stdio.h>



int main() {
	HashMap *hp = hashmap_create();
	/*
	parse_data_instuction("X DW 3", hp);
	parse_data_instuction("Y DB 4", hp);
	Instruction* a = parse_data_instuction("arr DB 5,6,7,8", hp);
	parse_data_instuction("z DB 9", hp);

	afficher_hashmap(hp);
	affiche_Instruction(a);
	*/
	/*
	parse_code_instruction("loop : MOV AX,6", hp, 0);
	parse_code_instruction("ADD BX,10", hp, 1);
	parse_code_instruction("end : JMP loop", hp, 2);

	afficher_hashmap(hp);
	*/

	ParserResult *p = parse("assembler.txt");
	//afficher_ParserResult(p);
	free_ParserResult(p);
	free_HashMap(hp);
}