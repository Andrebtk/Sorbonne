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
                *valeur=10;
                int *valeur2=malloc(sizeof(int));
                *valeur2=100;
                if(map==NULL){
                    printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
                    break;
                }else{
                    printf("Insertion de 'test1' et 'test2' (on choisira un int pour la valeur pour facilité)\n");
                    if(hashmap_insert(map, "test1", valeur)==-1){
                        printf("pas de place insertion raté\n");
                    }
                    if(hashmap_insert(map, "test2", valeur2)==-1){
                        printf("pas de place insertion raté\n");
                    }
                    
                    break;
                }
            }
            case 2: {
                if(map==NULL){
                    printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
                    break;
                }else{
                    printf("Suppression de 'test1\n");
                    hashmap_remove(map,"test1");
                    break;
                }
            }
            case 3: {
                if(map==NULL){
                    printf("\nVeuillez d'abord initialiser le gestionnaire de mémoire\n");
                    break;
                }else{
                    printf("recherche de la valeur associer a la cle: test2\n");
                    int *res = (int*) hashmap_get(map, "test2");
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

