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
                int *bx = hashmap_get(cpu->context, "BX");
                *bx = 10;

                int *ax = hashmap_get(cpu->context, "AX");
                *ax = 5;
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
                }else{
                    allocate_code_segment(cpu,res->code_instructions,res->code_count);
                    break;
                }
            }
            case 3: {
                if(cpu==NULL){
                    printf("Veuillez d'abord initialiser le CPU\n");
                    break;
                }else{
                    int *bx = hashmap_get(cpu->context, "BX");
                    int *ax = hashmap_get(cpu->context, "AX");
                    handle_instruction(cpu,fetch_next_instruction(cpu),ax,bx);
                    break;
                }

            }
            case 4: {
                if(cpu==NULL){
                    printf("Veuillez d'abord initialiser le CPU\n");
                    break;
                }else{
                    run_program(cpu);
                    break;
                }
            }
            case 5: {
                cpu_destroy(cpu);
                break;
            }
        }
    }while(action!=5);
}
