/*
 * Projet : Mini-Projet 2 : Gestion d’une bibliotheque
 * Auteurs : 
 *   - Andre Bertok (21204512)
 *   - Olivier Huang (21206369)
 */
#include "biblioLC.h"
#include "biblioH.h"
#include "entreeSortieLC.h"
#include "entreeSortieH.h"


#include <stdlib.h>
#include <time.h>

void menu() {
	printf("Option:\n");
	printf("0 - Sortie du programme\n");
	printf("1 - Affichage \n");
	printf("2 - Inserer ouvrage \n");
	printf("3 - Supprimer Ouvrage\n");
	printf("4 - Recherche Auteur\n");
	printf("5 - Enregistrer Biblio\n");
	printf("6 - Recherche ouvrages en plusieurs exemplaires\n");
}

// Fonction pour trouver le titre d'un livre de manière aléatoire en parcourant la liste
char* trouver_titre_alea(int n, Livre* a){
	char* rep = "";	
	while (a && n>0) {
		a=a->suiv;
		n--;
	}
	return a->titre;
}

// Fonction pour trouver l'auteur d'un livre de manière aléatoire en parcourant la liste
char* trouver_auteur_alea(int n, Livre* a){
	char* rep = "";	
	while (a && n>0) {
		a=a->suiv;
		n--;
	}
	
	return a->auteur;
}


// Fonction qui exécute plusieurs tests de recherche sur une bibliothèque sous forme 
// de liste chaînée et de table de hachage. Elle mesure le temps d'exécution des 
// recherches par numéro, titre et auteur, et compare les performances des deux structures.
void main_run(Biblio* listC, BiblioH* hash, int randomN, char* titre, char* auteur){
	clock_t start_time;
	clock_t end_time;
	double cpu_time;
	
	start_time = clock();
	for (int i = 0; i < 150; i++) {
		recherche_num(listC->L, randomN);
	}
	end_time = clock();
	cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	printf("Liste chainée: recherche par numéro - %f \n", cpu_time);

	start_time = clock();
	for (int i = 0; i < 150; i++) {
		recherche_numH(hash, randomN);
	}
	end_time = clock();
	cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	printf("Table de hachage: recherche par numéro - %f \n", cpu_time);

	start_time = clock();
	for (int i = 0; i < 150; i++) {
		recherche_titre(listC->L, titre);
	}
	end_time = clock();
	cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	printf("Liste chainée: recherche par titre - %f \n", cpu_time);

	start_time = clock();
	for (int i = 0; i < 150; i++) {
		recherche_titreH(hash, titre);
	}
	end_time = clock();
	cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	printf("Table de hachage: recherche par titre - %f \n", cpu_time);

	start_time = clock();
	for (int i = 0; i < 300; i++) {
		Biblio* res = recherche_auteur(listC, auteur); //Nom d'auteur qui n'est pas dans la liste
		liberer_biblio(res);
	}
	end_time = clock();
	cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	printf("Liste chainée: recherche auteur - %f \n", cpu_time);

	start_time = clock();
	for (int i = 0; i < 300; i++) {
		BiblioH* res = recherche_auteurH(hash, auteur);
		liberer_biblioH(res);
	}
	end_time = clock();
	cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	printf("Table de hachage: recherche auteur - %f \n", cpu_time);
}

// Fonction principale de test qui charge une bibliothèque depuis un fichier et 
// exécute des recherches en appelant main_run. Elle effectue des tests avec 
// un livre existant et un livre inexistant pour comparer les performances.
void TimeTest(char* nomfic, int taille_lc, int taille_H) {
	Biblio* listC = charger_n_entrees(nomfic, taille_lc);
	BiblioH* hash = charger_n_entreesH(nomfic, taille_H);

	printf("\n\n----------------------\n");
	printf("Livre trouvable: \n");
	printf("----------------------\n\n");
	int randomN = rand() % taille_lc;
	char* auteur = trouver_auteur_alea(randomN, listC->L);
	char* titre = trouver_titre_alea(randomN,listC->L);
	main_run(listC, hash, randomN, titre, auteur);
	printf("\n\n----------------------\n");
	printf("Livre introuvable: \n");
	printf("----------------------\n\n");
	main_run(listC, hash, taille_lc*2, "123456", "123456");
	
	liberer_biblio(listC);
	liberer_biblioH(hash);
}


int main(int argc, char** argv) {
	// Vérification du nombre d'arguments
	if(argc != 3){
		printf("Erreur : nombre d'arguments incorrect.\n");
        printf("Utilisation : %s <nom_fichier> <taille>\n", argv[0]);
		return -1;
	}

	char buffer[256];
	int choix = -1;

	// Sélection de la partie à exécuter (quel question)
	while (choix != 1 && choix != 3) {
		printf("Choisissez une partie (1 ou 3) : ");
		char choix_str[10];
		fgets(choix_str, sizeof(choix_str), stdin);
		choix = atoi(choix_str);
	}

	//Partie 1 et 2
	if(choix == 1) {
		Biblio *test = charger_n_entrees(argv[1],atoi(argv[2]));
		int action;
		int num;
		char titre[256];
		char auteur[256];

		do{
			menu();
			printf("entrée une action:\n");
			char action_str[10];
			fgets(action_str, sizeof(action_str), stdin);
			action = atoi(action_str);

			switch (action){
				case 1:
					printf("Affichage de la bibliothèque :\n");
					afficher_biblio(test);
					printf("\n");
					break;
				case 2:
					printf("Insertion d'un ouvrage\n\n");
					printf("Indiquez le Numéro, Titre et Auteur: \n");
					fgets(buffer, sizeof(buffer), stdin);
					if(sscanf(buffer, "%d %s %s", &num, titre, auteur) == 3){
						inserer_en_tete(test, num, titre, auteur);
						printf("Ajout réussi\n\n");
					} else {
						printf("Erreur de format\n");
					}
					break;

				case 3:
					printf("Suppression d'un ouvrage\n\n");
					printf("Indiquez le Numéro, Titre et Auteur:\n");
					fgets(buffer, sizeof(buffer), stdin);
					if(sscanf(buffer, "%d %s %s", &num, titre, auteur) == 3){
						supprimer(test,num,titre,auteur);
						printf("Suppression réussi\n\n");
					} else {
						printf("Erreur de format\n");
					}
					break;
				case 4:
					printf("Recherche d'ouvrages par auteur\n\n");
					printf("Indiquez le nom de l'auteur recherché:\n");
					fgets(auteur, sizeof(auteur), stdin);
					auteur[strcspn(auteur, "\n")] = 0;   //on enleve le caractère \n car la touche entrée ajoute un \n si le buffer n'est pas entierement utilisé
					Biblio *res = recherche_auteur(test, auteur);

					if(res->L == NULL){
						printf("\nAucun ouvrage trouvé pour cet auteur\n");
					} else{
						printf("\nOuvrages disponibles pour cet auteur :\n\n");
						afficher_biblio(res);
						printf("\n");
					}
					liberer_biblio(res);
					break;

				case 5:
					printf("Enregistrement de la bibliothèque\n\n");
					printf("Indiquez le nom du fichier :\n");
					fgets(buffer, sizeof(buffer), stdin);
					buffer[strcspn(buffer, "\n")] = 0;  // Supprime le retour à la ligne

					enregistrer_biblio(test, buffer);
					printf("Bibliothèque enregistrée dans '%s'\n\n", buffer);
					break;
				case 6:
					printf("Recherche des ouvrages en plusieurs exemplaires...\n");
					Biblio *duplicates = recherche_meme_ouvrage(test);
					if (duplicates->L == NULL) {
						printf("\nAucun ouvrage en double trouvé.\n");
					} else {
						printf("\nListe des ouvrages ayant plusieurs exemplaires :\n");
						afficher_biblio(duplicates);
						printf("\n");
					}
					liberer_biblio(duplicates);
					break;
			}
		}while(action);

		printf("Sortie du programme \n");
		liberer_biblio(test);

	} else { // Partie 3 : Exécution des tests de performance

		clock_t temps_init;
		clock_t temps_final;
		double temps_cpu;
		
		int choix;
		do{
			choix = -1;
			while (choix !=0 && choix != 1 && choix != 2 && choix != 3 && choix != 4) {
				printf("\n\nOption:\n");
				printf("0 - Sortie du programme\n");
				printf("1 - Q1 \n");
				printf("2 - Q2 \n");
				printf("3 - Q3-Q4 \n");
				printf("4 - Recherche ouvrages en plusieurs exemplaires\n");
				char choix_str[10];
				fgets(choix_str, sizeof(choix_str), stdin);
				choix = atoi(choix_str);
			}

			switch (choix) {
				case 1: 
					TimeTest(argv[1], atoi(argv[2]), atoi(argv[2]));

					
					
					
					printf("\n\n==================\n");
                    printf("Observations :\n");
                    printf("- La recherche par numéro est plus rapide avec la table de hachage car elle évite de parcourir tous les éléments, contrairement à la liste chaînée\n");
                    printf("- Liste chaînée plus efficace pour la recherche par titre et auteur");
                    printf("- Quand l'ouvrage est introuvable, la différence est moins marquée, avec parfois un léger avantage pour la liste chaînée\n");
                    printf("==================\n");
					
					break;

				case 2: { 
					int tailles[] = {100, 500, 1000, 5000, 10000, 50000};
					
					for (int i = 0; i < 6; i++) {
						printf("\n\n==================\n");
						printf("\nTaille list: %d, taille table de hachage: %d\n\n", atoi(argv[2]), tailles[i]);
						printf("==================\n");
						TimeTest(argv[1], atoi(argv[2]), tailles[i]);
					}
					printf("\n\n==================\n");
					printf("Analyse des performances :\n");
					printf("==================\n\n");

					
					printf("- Recherche par numéro : La table de hachage est très rapide pour une petite taille (100-1000) mais devient inefficace au-delà de 10 000 entrées.\n");
					printf("- Recherche par titre et auteur : La liste chaînée est plus stable, tandis que la table de hachage souffre des collisions et se dégrade avec la taille.\n");
					printf("- Livre introuvable : La table de hachage est rapide au début, mais inefficace avec une grande taille en raison des entrées vides et des collisions.\n\n");

					printf("Conclusion : La table de hachage n'est efficace que pour une petite taille. La liste chaînée est plus fiable.\n");
					printf("==================\n\n");

				}
				break;

				case 3: { 
						FILE *f = fopen("data.csv", "w");
						fprintf(f,"Taille,Temps_Liste,Temps_Hash\n");

						for (int n=10; n<=75000; n=n*2){
							Biblio* LinkedList = charger_n_entrees(argv[1],n);
							BiblioH* hash = charger_n_entreesH(argv[1], n/2);

							double temps_cpuL;
							double temps_cpuH;

							temps_init = clock();
							Biblio* temp1 = recherche_meme_ouvrage(LinkedList);
							temps_final=clock();
							temps_cpuL = ((double)(temps_final - temps_init)) / CLOCKS_PER_SEC;


							temps_init = clock();
							BiblioH* temp2 = recherche_meme_ouvrageH(hash);
							temps_final=clock();
							temps_cpuH = ((double)(temps_final - temps_init)) / CLOCKS_PER_SEC;

							fprintf(f,"%d,%f,%f\n",n, temps_cpuL, temps_cpuH);
							printf("%d, Temps liste chainee: %f, Temps: table de hachage %f\n",n, temps_cpuL, temps_cpuH);
							

							liberer_biblio(temp1);
							liberer_biblioH(temp2);

							liberer_biblio(LinkedList);
							liberer_biblioH(hash);
						}

						fclose(f);
					}

					printf("Complexité :\n");
					printf("- La complexité en O(n) de la liste chaînée est bien confirmée : plus la bibliothèque grandit, plus le temps de recherche augmente linéairement.\n");
					printf("- La table de hachage, en théorie 𝑂(1), reste rapide tant qu'elle est bien dimensionnée. Toutefois, des collisions excessives pourraient la ralentir.\n");
				break;

				case 4:
					printf("\nRecherche des ouvrages en plusieurs exemplaires...\n");
					BiblioH* biblio = charger_n_entreesH(argv[1], atoi(argv[2]));

					if (biblio == NULL) {
						printf("Erreur : Impossible de charger la bibliothèque.\n");
						break;
					}

					// Rechercher les ouvrages en plusieurs exemplaires
					BiblioH* doublons = recherche_meme_ouvrageH(biblio);

					int has_duplicates = 0;
					for (int i = 0; i < doublons->m; i++) {
						if (doublons->T[i] != NULL) { 
							has_duplicates = 1;
							break;
						}
					}

					 if (!has_duplicates) {
						printf("\nAucun ouvrage avec plusieurs exemplaires trouvé.\n");
					} else {
						printf("\nListe des ouvrages ayant plusieurs exemplaires :\n");
						afficher_biblioH(doublons);
						printf("\n");
					}

					// Libération de la mémoire
					liberer_biblioH(doublons);
					liberer_biblioH(biblio);
					break;

			}
		}while(choix);
	}

	return 0;
}


