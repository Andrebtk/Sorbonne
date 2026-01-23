#include <stdio.h>
#include "cpu.h"
#include "parser.h"

void menu() {
	printf("\nOption:\n");
	printf("0 - Initialiser le simulateur de CPU\n");
    printf("1 - Parsing du fichier exo6_assembler.txt\n");
    printf("2 - Initialiser le segment 'CS'\n");
    printf("3 - Handle instruction\n");
	printf("4 - Run Program\n");
    printf("5 - Quitter\n");
}
int main() {

	CPU *cpu=NULL;
	int action;
	ParserResult *res=NULL;
	do{
		menu();
		printf("entrée une action:\n");
		scanf("%d",&action);
		printf("========================================\n");
		switch (action){
			case 0:{
				printf("Choisissez la taille de votre CPU\n");
				int taille;
				scanf("%d",&taille);
				cpu = cpu_init(taille);
				break;
			}
			case 1: {
				res = parse("exo6_assembler.txt");
				printf("=== Instructions AVANT resolve_constants ===\n");
				for (int i = 0; i < res->code_count; i++) {
					affiche_Instruction(res->code_instructions[i]);
					printf("========================================\n");
				}

				resolve_constants(res);

				printf("\n=== Instructions APRÈS resolve_constants ===\n");
				for (int i = 0; i < res->code_count; i++) {
					affiche_Instruction(res->code_instructions[i]);
					printf("========================================\n");
				}



				break;
			}
			case 2: {
				if(cpu==NULL){
					printf("Veuillez d'abord initialiser le CPU\n");
					break;
				}
				if (res == NULL) {
					printf("Veuillez d'abord parser le fichier (Action 1)\n");
					break;
				}

				allocate_variables(cpu, res->data_instructions, res->data_count);
				printf("Segment DS (données) initialisé avec %d cellules.\n", res->data_count);

				allocate_code_segment(cpu,res->code_instructions,res->code_count);
				printf("Segment CS (code) initialisé avec %d instructions.\n", res->code_count);
				
				printf("Segment CS initialisé avec succès.\n");
				break;
				
			}
			case 3: {
				if(cpu==NULL){
					printf("Veuillez d'abord initialiser le CPU\n");
					break;
				}

				if (res == NULL) {
					printf("Veuillez d'abord parser le fichier (Action 1)\n");
					break;
				}

				Instruction *instr = fetch_next_instruction(cpu);
				if (!instr) {
					printf("Plus d'instructions à exécuter.\n");
					break;
				}
				printf("Instruction à exécuter : %s %s %s\n",
					instr->mnemonic,
					instr->operand1 ? instr->operand1 : "",
					instr->operand2 ? instr->operand2 : "");

				// 1) On récupère dst et src via resolve_addressing
				void *dst = resolve_addressing(cpu, instr->operand1);
				void *src = resolve_addressing(cpu, instr->operand2);
				if (!dst || !src) {
					printf("Erreur de résolution d'opérandes\n");
					break;
				}

				// 2) On exécute
				handle_instruction(cpu, instr, dst, src);

				// 3) On affiche le nouveau AX
				int *ax = hashmap_get(cpu->context, "AX");
				printf("Après exécution, AX = %d\n", *ax);
				break;
			}

			
			case 4: {
				if(cpu==NULL){
					printf("Veuillez d'abord initialiser le CPU\n");
					break;
				}

				if (res == NULL) {
					printf("Veuillez d'abord parser le fichier (Action 1)\n");
					break;
				}


				run_program(cpu);
				printf("Si aucune commande n\'a ete executer: Initialiser le segemnt CS (Action 2)");
				break;
			}


			case 5: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}
				cpu_destroy(cpu);
				free_ParserResult(res);
				break;
			}
		}
	}while(action!=5);
}
