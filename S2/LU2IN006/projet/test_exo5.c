#include <stdio.h>
#include "cpu.h"
#include "parser.h"

void menu() {
	printf("\nOption:\n");
	printf("0 - Initialiser le simulateur de CPU\n");
    printf("1 - Tester immediate_addressing\n");
    printf("2 - Tester register_addressing\n");
    printf("3 - Tester memory_direct_addressing\n");
    printf("4 - Tester register_indirect_addressing\n");
	printf("5 - Tester handle_MOV\n");
    printf("6 - Quitter\n");
}
int main() {

    CPU *cpu=NULL;
    int action;
    void *res=NULL;
    do{
        menu();
        printf("entrée une action:\n");
        scanf("%d",&action);
        printf("========================================\n");
		switch (action){
            case 0: {
                printf("Initialisation du simulateur à taille 1024");
                cpu=cpu_init(1024);
                
                int *bx = hashmap_get(cpu->context, "BX");
                *bx = 10;

                int *ax = hashmap_get(cpu->context, "AX");
                *ax = 5;

                create_segment(cpu->memory_handler, "DS", 128, 100);
                int *val_5 = malloc(sizeof(int)); *val_5 = 555;
                int *val_10 = malloc(sizeof(int)); *val_10 = 1010;

                store(cpu->memory_handler, "DS", 5, val_5);
                store(cpu->memory_handler, "DS", 10, val_10);
                break;
            }
            case 1: {
                if(cpu==NULL){
                    printf("Veuillez d'abord initialiser le CPU\n");
                    break;
                }else{
                    printf("Test avec '42'\n");
                    res = immediate_addressing(cpu,"42");
                    if (res) printf("Valeur trouvé : %d\n", *(int*)res);
                    else printf("Adresse invalide.\n");
                    break;
                }
            }
            case 2: {
                if(cpu==NULL){
                    printf("Veuillez d'abord initialiser le CPU\n");
                    break;
                }else{
                    printf("Test avec 'BX'\n");
                    res = register_addressing(cpu,"BX");
                    if (res) printf("Valeur trouvé : %d\n", *(int*)res);
                    else printf("valeur invalide.\n");
                    break;
                }
            }
            case 3: {
                if(cpu==NULL){
                    printf("Veuillez d'abord initialiser le CPU\n");
                    break;
                }else{
                    printf("Test avec '[5]'\n");
                    res = memory_direct_addressing(cpu,"[5]");
                    if (res) printf("Valeur résolue : %d\n", *(int*)res);
                    else printf("valeur invalide.\n");
                    break;
                }
            }
            case 4: {
                if(cpu==NULL){
                    printf("Veuillez d'abord initialiser le CPU\n");
                    break;
                }else{
                    printf("Test avec '[AX]'\n");
                    res = register_indirect_addressing(cpu, "[BX]");
                    if (res) printf("Valeur mémoire via registre : %d\n", *(int*)res);
                    else printf("valeur invalide.\n");
                    break;
                }
            }
            case 5 :{
                void* imediat = resolve_addressing(cpu, "42");
                void* registre = resolve_addressing(cpu, "AX");
                handle_MOV(cpu, imediat, registre);
                printf("Après MOV AX <- 42 : AX = %d\n", *(int*)registre);

                void* indirect_registre = resolve_addressing(cpu, "[BX]");
                void* registre2 = resolve_addressing(cpu, "CX");
                handle_MOV(cpu, indirect_registre, registre2);
                printf("Après MOV CX <- [BX] : CX = %d\n", *(int*)registre2);
                break;
            }
            case 6: {
                cpu_destroy(cpu);
                break;
            }
        }
    }while(action!=6);
    return 0;
}
