#include <stdio.h>
#include "hash.h"



void menu() {
	printf("\nOption:\n");
	printf("0 - Initialiser la table de hachage\n");
	printf("1 - Insérer un élément dans la table de hachage \n");
	printf("2 - Supprimer un élément dans la table de hachage \n");
    printf("3 - récupérer la valeur associé à une clé\n");
    printf("4 - Afficher la table de hachage\n");
	printf("5 - Quitter\n");
}

int main() {
    HashMap *map =NULL;
    int action;
    char cle[100];
    do{
        menu();
        printf("entrée une action:\n");
        scanf("%d",&action);
        printf("========================================\n");
		switch (action){
            case 0: {
                map=hashmap_create();
                if(map==NULL){
                    printf("Initialisation raté\n");
                    break;
                }else{
                    printf("Initialisation réussi\n");
                    break;
                }
            }
            case 1: {
                int *valeur=malloc(sizeof(int));
                if(map==NULL){
                    printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
                    break;
                }else{
                    printf("Veuillez choisir la clé et la valeur associé (on choisira un int pour la valeur pour facilité)\n");
                    scanf("%s %d",cle, valeur);
                    hashmap_insert(map, cle, valeur);
                    break;
                }
            }
            case 2: {
                if(map==NULL){
                    printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
                    break;
                }else{
                    printf("Veuillez choisir la clé de l'élément a supprimer\n");
                    scanf("%s",cle);
                    hashmap_remove(map,cle);
                    break;
                }
            }
            case 3: {
                if(map==NULL){
                    printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
                    break;
                }else{
                    printf("Veuillez choisir la clé à rechercher\n");
                    scanf("%s",cle);
                    int *res = (int*) hashmap_get(map, cle);
                    if (res != NULL) {
                        printf("Valeur trouvée : %d\n", *res);
                        break;
                    } else {
                        printf("Clé non trouvée.\n");
                        break;
                    }
                    break;
                }
            }
            case 4: {
				if(map==NULL){
					printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
					break;
				}
                afficher_hashmap(map);
                break;
            }
            case 5:{
                free_HashMap(map);
                break;
            }
        }
    }while(action != 5);

	return 0;

}

