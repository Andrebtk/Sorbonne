#ifndef PARSER
#define PARSER

#include "hash.h"


typedef struct {
	char *mnemonic;
	char *operand1;
	char *operand2;
} Instruction;

typedef struct {
	Instruction **data_instructions;
	int data_count;
	Instruction **code_instructions;
	int code_count;
	HashMap *labels;
	HashMap *memory_locations;
} ParserResult;


void free_Instruction(Instruction *i);
void free_ParserResult(ParserResult *pr);
void affiche_Instruction(Instruction* a);
void afficher_ParserResult(ParserResult* p);
Instruction *parse_data_instuction(const char *line, HashMap *memory_locations);
Instruction *parse_code_instruction(const char *line, HashMap *labels, int code_count);
ParserResult *parse(const char *filename);
int resolve_constants(ParserResult *result);

#endif
