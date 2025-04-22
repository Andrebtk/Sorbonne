#include "parser.h"
#include <stdio.h>

int main() {
	int choice;
	
	do {
		printf("\n=== Menu Principal ===\n");
		printf("1. Tester le parsing de données\n");
		printf("2. Analyser un fichier assembleur\n");
		printf("3. Quitter\n");
		printf("Votre choix : ");
		scanf("%d", &choice);

		switch(choice) {
			case 1: {
				// Option 1 : Test de la table de hachage et du parsing .DATA
				HashMap *hp = hashmap_create();
				printf("L'instruction: arr DB 5,6,7,8\n");
				Instruction* a = parse_data_instuction("arr DB 5,6,7,8", hp);
				printf("L'instruction: z DB 9\n\n");
				Instruction* b = parse_data_instuction("z DB 9", hp);
				
				printf("\n=== Contenu de la table de hachage ===\n");
				afficher_hashmap(hp);
				
				printf("\n=== Instructions extraites ===\n");
				affiche_Instruction(a);
				affiche_Instruction(b);
				
				free_HashMap(hp);
				free_Instruction(a);
				free_Instruction(b);
				
				break;
			}
			case 2: {
				// Option 2 : Analyse d'un fichier assembleur
				ParserResult *p = parse("assembler_exo3-4.txt");
				printf("\n=== Résultat de l'analyse ===\n");
				afficher_ParserResult(p);
				free_ParserResult(p);
				break;
			}
			case 3:
				printf("Exit !\n");
				break;
			default:
				printf("Choix invalide. Réessayez.\n");
		}
	} while(choice != 3);

	return 0;
}