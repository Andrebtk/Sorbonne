#include <stdio.h>
#include "cpu.h"


void menu() {
        printf("\n=== Menu Principal ===\n");
        printf("1. Initialiser du CPU \n");
        printf("2. PUSH une valeur sur la pile\n");
        printf("3. POP une valeur sur la pile\n");
        printf("4. Lire assembler_exo3.txt\n");
        printf("5. Afficher la pile \n");
		printf("6. Quitter\n");
        printf("Votre choix : ");
}


int main() {
	int action;
	CPU *cpu = NULL;
	do {
		menu();
		printf("entrée une action: ");
		scanf("%d",&action);

		switch(action) {
			case 1: {
				printf("Choisissez la taille de votre gestionnaire de mémoire (>200)\n");
				int taille;
				scanf("%d",&taille);
				cpu = cpu_init(taille);

				if (cpu == NULL) {
					printf("Erreur d'initialisation du CPU\n");
					return 1;
				}

				printf("CPU initialisé avec succès\n");
				break;
			}

			case 2: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				printf("Valeur (int) a PUSH sur la pile : ");
				int value;
				scanf("%d", &value);

				if(push_value(cpu, value)==0){
					printf("la fonction push_value a ete executer avec succès avec %d \n", value);
				} else {
					printf("La pile est remplie \n");
				}
				
				break;
			}

			case 3: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				int addr;
				if (pop_value(cpu, &addr)== 0){
					printf("la fonction pop_value a ete executer avec succès et a retourner %d \n", addr);
				}else {
					printf("Pile vide \n");
				}
				
				
				break;
			}

			case 4: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				/*
				5.DATA
				X DW 10
				Y DB 25
				Z DB 1
				.CODE
				MOV BX,[X]
				PUSH BX
				PUSH [Y]
				POP DX
				*/
				ParserResult *p = parse("assembler_exo7.txt");
				if (p == NULL) {
					printf("Erreur: impossible de parser le fichier assembler_exo7.txt\n");
					break;
				}  

				resolve_constants(p); 

				allocate_variables(cpu,  p->data_instructions, p->data_count);

				allocate_code_segment(cpu, p->code_instructions, p->code_count);
				
				
				run_program(cpu);

				free_ParserResult(p);

				break;

			}


			case 5: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				Segment* ss = hashmap_get(cpu->memory_handler->allocated, "SS");
				for(int i=120; i<ss->size; i++){	
					int* v = load(cpu->memory_handler, "SS", i);
					if(v == NULL) {
						printf("%d => %p \n", i, v);
					} else {
						printf("%d => %d \n", i, *v);
					}
								
				}
				
				break;
			}

			case 6: {
				if (cpu != NULL) {
					printf("Liberation du CPU...\n");
					cpu_destroy(cpu);
				}
				break;
			}
		}
		
	} while(action != 6);

}