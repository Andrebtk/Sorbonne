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
    char name[100];
    do {
        menu();
        printf("entrée une action:\n");
        scanf("%d",&action);
        printf("========================================\n");
		switch (action){
            case 0: {
                printf("Choisissez la taille de votre gestionnaire de mémoire\n");
                int taille;
                scanf("%d",&taille);
                handler = memory_init(taille);
                break;
            }
            case 1: {
                int start,size;
                if(handler==NULL){
                    printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
                    break;
                }else{
                    printf("Veuillez choisir le nom, start et taille de votre segment(séparée par un espace)\n");
                    scanf(" %s %d %d", name, &start, &size);
                    create_segment(handler,name,start,size);
                    break;
                }
            }
            case 2: {
                if(handler==NULL){
                    printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
                    break;
                }else{
                    printf("Veuillez entrer le nom du segment\n");
                    scanf("%s",name);
                    remove_segment(handler, name);
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
