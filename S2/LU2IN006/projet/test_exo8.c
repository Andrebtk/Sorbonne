#include <stdio.h>
#include "cpu.h"

void menu() {
	printf("\n=== Menu Principal ===\n");
	printf("1. Initialiser du CPU \n");
	printf("2. Crée le segment ES \n");
	printf("3. Tester segment_override_addressing\n");
	printf("4. Tester resolve_addressing\n");
	printf("5. Tester find_free_address_strategy\n");
	printf("6. Liberer le segment ES\n");
	printf("7. Tester handle_instruction avec ALLOC et FREE (assembler_exo8.txt) \n");
	printf("8. Afficher segment ES \n");
	printf("9. Quitter\n");
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
				printf("Entrer la valeur (int) pour la taille du segment ES (>5 minimum) et la strategie (separer par un espace)\n");
				int taille, strat;
				scanf("%d %d", &taille, &strat);

				int *ax = hashmap_get(cpu->context, "AX");
				int *bx = hashmap_get(cpu->context, "BX");
				*ax = taille; 
				*bx = strat;

				printf("AX = %d, BX (stratégie) = %d\n", *ax, *bx);
				alloc_es_segment(cpu);
				int *es = hashmap_get(cpu->context, "ES");
				printf("Après ALLOC, registre ES = %d\n", *es);

				break;
			}

			case 3: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				int *es = hashmap_get(cpu->context, "ES");
				if(*es == -1) {
					printf("Erreur: segment ES pas crée\n");
					break;
				}

				int *p = malloc(sizeof(int)); 
				*p = 42;
				store(cpu->memory_handler, "ES", 2, p);
				printf("Stocké 42 en ES[2]\n");

				int *ax = hashmap_get(cpu->context, "AX");
				*ax = 2;

				printf("Registre AX défini à %d\n", *ax);
				printf("Appel a segment_override_addressing avec \"[ES:AX]\"\n");
				void *r = segment_override_addressing(cpu,"[ES:AX]");
				
				if (r) {
					printf("Lecture segment_override_addressing: %d\n", *((int*)r));
				} else {
					printf("Erreur segment_override_addressing\n");
				} 

				break;
			}
			
			case 4: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				int *bx = hashmap_get(cpu->context, "BX");
				if (!bx) {
					printf("Erreur: registre BX non trouvé\n");
					break;
				}
				*bx = 5;
				printf("Registre BX mis à jour à %d\n", *bx);
				
				int *p = malloc(sizeof(int)); 
				*p = 12;
				store(cpu->memory_handler, "ES", 5, p);
				printf("Stocké 42 en position 5 dans ES\n");
				
			
				// 4) Lecture de vérification
				int *val = resolve_addressing(cpu, "[ES:BX]");
				if (!val) {
					printf("Erreur: lecture [ES:BX] impossible\n");
				} else {
					printf("Lecture mémoire [ES:BX] => %d\n", *val);
				}

				break;
			}
			
			case 5: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				printf("Création de segments de test :\n");
				printf("T1 @200, taille 50\n");
				create_segment(cpu->memory_handler, "T1", 200, 50);
				printf("T2 @300, taille 100\n");
				create_segment(cpu->memory_handler, "T2", 300, 100);
				printf("T3 @600, taille 30\n");
				create_segment(cpu->memory_handler, "T3", 600, 30);

				int req = 60;

				int addr0 = find_free_address_strategy(cpu->memory_handler, req, 0);
				printf("First-fit (stratégie 0) pour %d octets → adresse retournée : %d\n", req, addr0);

				// Best‑fit : on retourne la plus petite zone libre ≥ req
				int addr1 = find_free_address_strategy(cpu->memory_handler, req, 1);
				printf("Best-fit (stratégie 1) pour %d octets → adresse retournée : %d\n", req, addr1);

				// Worst‑fit : on retourne la plus grande zone libre ≥ req
				int addr2 = find_free_address_strategy(cpu->memory_handler, req, 2);
				printf("Worst-fit (stratégie 2) pour %d octets → adresse retournée : %d\n", req, addr2);
				
				remove_segment(cpu->memory_handler, "T1");
				remove_segment(cpu->memory_handler, "T2");
				remove_segment(cpu->memory_handler, "T3");
				
				break;
			}
			

			case 6: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}
			
				if (free_es_segment(cpu) == 0) {
					printf("Segment ES libéré avec succès\n");
				} else {
					printf("Erreur: segment ES non créé ou déjà libéré\n");
				}
			
				break;
			}


			case 7: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				const char *filename = "assembler_exo8.txt";
				ParserResult *p = parse(filename);

				resolve_constants(p); 
				
				allocate_variables(cpu,  p->data_instructions, p->data_count);

				allocate_code_segment(cpu, p->code_instructions, p->code_count);
				
				
				run_program(cpu);


				free_ParserResult(p);

				break;
			}

			case 8: {
				if (cpu == NULL) {
					printf("Erreur: le CPU n'est pas initialisé\n");
					break;
				}

				print_segment_data(cpu, "ES");
				break;
			}

			case 9: {
				if (cpu != NULL) {
					printf("Liberation du CPU...\n");
					cpu_destroy(cpu);
				}
				break;
			}
		}
	} while(action != 9);
}