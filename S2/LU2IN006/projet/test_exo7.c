#include <stdio.h>
#include "cpu.h"


void menu() {
        printf("\n=== Menu Principal ===\n");
        printf("1. Initialiser du CPU \n");
        printf("2. PUSH une valeur sur la pile\n");
        printf("3. POP une valeur sur la pile\n");
        printf("4. Lire assembler3.txt\n");
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

                push_value(cpu, value);
                printf("la fonction push_value a ete executer avec succès avec %d \n", value);
                break;
            }

            case 3: {
                if (cpu == NULL) {
                    printf("Erreur: le CPU n'est pas initialisé\n");
                    break;
                }

                int addr;
                pop_value(cpu, &addr);
                printf("la fonction pop_value a ete executer avec succès et a retourner %d \n", addr);

                break;
            }

            case 4: {
                if (cpu == NULL) {
                    printf("Erreur: le CPU n'est pas initialisé\n");
                    break;
                }

                ParserResult *p = parse("assembler3.txt");
                if (p == NULL) {
                    printf("Erreur: impossible de parser le fichier assembler2.txt\n");
                    break;
                }  

                resolve_constants(p); 

                allocate_variables(cpu,  p->data_instructions, p->data_count);

                allocate_code_segment(cpu, p->code_instructions, p->code_count);
                
                
                run_program(cpu);

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

            case 8: {
                if (cpu != NULL) {
                    printf("Liberation du CPU...\n");
                    cpu_destroy(cpu);
                }
                break;
            }
        }
        
    } while(action != 8);

}