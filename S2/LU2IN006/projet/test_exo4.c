#include <stdio.h>
#include "cpu.h"
#include "memory.h"
#include "parser.h"

void menu() {
    printf("\n=== Menu Principal ===\n");
        printf("1. Initialiser du CPU \n");
        printf("2. Liberer le CPU \n");
        printf("3. Stocker un valeur dans un segemnt\n");
        printf("4. Load une donnee stockee a un position donner d'un segment\n");
        printf("5. Allouer dynamiquement le segment de donnees en fonction du fichier assembler_exo3-4.txt \n");
        printf("6. Afficher le contenu du segment de donnees\n");
        printf("7. Afficher le segment TEST\n");
		printf("8. Quitter\n");
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
				printf("Ajout du segemtn Test de taille 50\n");
				create_segment(cpu->memory_handler, "TEST", 129, 50);

				printf("CPU initialisé avec succès\n");

				break;
			}

			case 2: {
				if (cpu != NULL) {
					printf("Liberation du CPU...\n");
					
					Segment* T = hashmap_get(cpu->memory_handler->allocated, "TEST");
					if(T) {
						for(int i=0; i<T->size; i++) {
							free(cpu->memory_handler->memory[T->start + i]);
						}
					}

					cpu_destroy(cpu);
					cpu = NULL;


				}
				break;
			}

			case 3: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}
				
				printf("Entrer la valeur (int) que vous voulez stocker dans le segment \"TEST\" et la postion dans le segment (entre 0 et 50) (separer par un espace)\n");
				int value, position;
				scanf("%d %d", &value, &position);
				
				if(position<0 || position>50) {
					printf("position non conforme\n");
					break;
				}

				Segment *test_segment = hashmap_get(cpu->memory_handler->allocated, "TEST");
				if (test_segment == NULL) {
					printf("Erreur: le segment TEST n'existe pas\n");
					break;
				}
				int *address = malloc(sizeof(int));
				*address = value;
				store(cpu->memory_handler, "TEST", position, address);
				printf("Valeur %d stockée à la position %d dans le segment TEST\n", value, position);
				
				break;
			}


			case 4: {
				if(cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				printf("Entrer la position dans le segment TEST (entre 0 et 50)\n");
				int position;
				scanf("%d", &position);
				Segment *test_segment = hashmap_get(cpu->memory_handler->allocated, "TEST");
				if (test_segment == NULL) {
					printf("Erreur: le segment TEST n'existe pas\n");
					break;
				}
				int *value = load(cpu->memory_handler, "TEST", position);
				if (value == NULL) {
					printf("Erreur: impossible de charger la valeur à la position %d dans le segment TEST\n", position);
				} else {
					printf("Valeur chargée à la position %d dans le segment TEST: %d\n", position, *value);
					//free(value);  // ?
				}
				break;
			}


			case 5: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				ParserResult *res = parse("assembler_exo3-4.txt");
				/*
				.DATA
				x DW 42
				arr DB 20,21,22,23
				y DB 10
				.CODE
				start: MOV AX,x
				loop: ADD AX,y
				JMP loop
				*/
				
				if (res == NULL) {
					printf("Erreur: impossible de parser le fichier assembler_exo3-4.txt\n");
					break;
				}

				allocate_variables(cpu, res->data_instructions, res->data_count);
				printf("Allocation dynamique du segment de données réussie\n");
				free_ParserResult(res);
				
				break;
			}

			case 6: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}
				print_cpu(cpu);
				break;
			}

			case 7: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}
				print_segment_data(cpu, "TEST");
				break;
			}

			case 8: {
				if (cpu != NULL) {
					printf("Liberation du CPU...\n");
					Segment* T = hashmap_get(cpu->memory_handler->allocated, "TEST");
					if(T) {
						for(int i=0; i<T->size; i++) {
							free(cpu->memory_handler->memory[T->start + i]);
						}
					}
					cpu_destroy(cpu);
				}
				
				break;
			}
		}

	}while (action != 8);

}