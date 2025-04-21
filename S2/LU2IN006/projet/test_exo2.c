#include <stdio.h>
#include "hash.h"
#include "memory.h" 


void menu() {
	printf("\nOption:\n");
	printf("0 - Initialiser la mémoire\n");
	printf("1 - Créer un segment \n");
	printf("2 - Supprimer un segment \n");
    printf("3 - Afficher le gestionnaire de mémoire\n");
	printf("4 - Quitter\n");
}

int main() {
    MemoryHandler *handler=NULL;
    int action;
    do {
        menu();
        printf("entrée une action:\n");
        scanf("%d",&action);
        printf("========================================\n");
		switch (action){
            case 0: {
                printf("Mémoire initialisé à une taille de 1O24\n");
                handler = memory_init(1024);
                break;
            }
            case 1: {
                int start,size;
                if(handler==NULL){
                    printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
                    break;
                }else{
                    printf("Création de 3 segments\n");
                    create_segment(handler, "test1", 100, 50);
                    create_segment(handler, "test2", 200, 75);
                    create_segment(handler, "test3", 500, 100);
                    break;
                }
            }
            case 2: {
                if(handler==NULL){
                    printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
                    break;
                }else{
                    printf("Suppression du segment 'test2'\n");
                    remove_segment(handler, "test2");
                    break;
                }
            }
            case 3:{ 
                print_memory(handler);
                break;
            }
            case 4: {
                if(handler){
                    free_memoryHandler(handler);
                }
            }
        }

    } while(action!=4);
    
    return 0;
}
