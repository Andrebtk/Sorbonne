#include "fat.h"
#include <string.h>
#include <stdio.h>

int file_found (char * file ) {
  int i;
  struct ent_dir * pt = pt_DIR;

  for (i=0; i< NB_DIR; i++) {
    if ((pt->del_flag) && (!strcmp (pt->name, file))) 
      return 0;
    pt++;
  }
  /* finchier n'existe pas */
  return 1;
}


void list_fat () {
  int i;
  short *pt = pt_FAT;
  for (i=0; i < NB_ENT_FAT; i++) {
    if (*pt)
      printf ("%d ",i);
    pt++;
  }
  printf ("\n");
}




// TME
void list_dir ( ) {
	// Pointe vers le début du répertoire
	struct ent_dir * pt = pt_DIR;
	int count = 0;

	for (int i=0; i<NB_DIR; i++) {
		if(pt->del_flag == 1) {
			printf("Fichier de nom: \'%s\', de taille: %d octets \n", pt->name, pt->size);

			count++;
		}
		pt++;
	}
	printf("Nombre total de fichiers : %d\n", count);
}

void list_dir2(char *file) {
	struct ent_dir * pt = pt_DIR;
	int count = 0;
	int afficher_tout = (strcmp(file, "*") == 0); // 1 si on veut tout afficher, 0 sinon

	for (int i = 0; i < NB_DIR; i++) {

		if (pt->del_flag == 1 && (afficher_tout || strcmp(pt->name, file) == 0)) {
			
			count++;
			printf("Fichier: '%s', taille: %d octets\n", pt->name, pt->size);


			short *pt_fat = pt_FAT;
			int bloc_suiv = pt->first_bloc;
			
			while(bloc_suiv != -1) {
				printf(" -> bloc %d\n", bloc_suiv);
				bloc_suiv = *(pt_fat + bloc_suiv);
			}
		}
		pt++;
	}

	printf("Nombre total de fichiers trouves : %d\n", count);
}


// TME
int cat_file (char* file) {
	if (file_found(file) == 1) return -1;

	char buffer[128];
	
	struct ent_dir * pt = pt_DIR;
	for (int i=0; i<NB_DIR; i++) {
		if((pt->del_flag == 1)  && (strcmp(pt->name, file)==0)) {
			

			short bloc_actuel = pt->first_bloc;
			int taille_restante = pt->size;

			while(bloc_actuel != FIN_FICHIER) {

				// Lecture du bloc
				if (read_sector(bloc_actuel, buffer) != 0) { return -1; }


				int octets_a_lire = (taille_restante < SIZE_SECTOR) ? taille_restante : SIZE_SECTOR;

				
				for (int k = 0; k < octets_a_lire; k++) {
					printf("%c", buffer[k]);
				}

				// Mise à jour pour la suite
				taille_restante -= octets_a_lire;
				bloc_actuel = pt_FAT[bloc_actuel];

			}
			printf("\n");
			return 0;
			
		}

		pt++;
	}

}

// TME
int mv_file (char *file1, char *file2) {

	if (file_found(file1) == 1) return -1;

	struct ent_dir * pt = pt_DIR;

	for (int i=0; i<NB_DIR; i++) {
		if ((pt->del_flag ==1) && (strcmp(pt->name, file1)==0)){
			strcpy(pt->name, file2);
			break;
		}
		pt++;
	}

	if (write_DIR_FAT_sectors() == -1) {
		return -1;
	}
	return 0;

}

// TME
int delete_file (char* file) {
	
	if (file_found(file) == 1) return -1;

	struct ent_dir * pt = pt_DIR;
	
	for (int i=0; i<NB_DIR; i++) {
		if ((pt->del_flag ==1) && (strcmp(pt->name, file)==0)){
			
			short *pt_fat = pt_FAT;
			int bloc_suiv = pt->first_bloc;

			while(bloc_suiv != -1) {
				int tmp = *(bloc_suiv + pt_fat);
				*(bloc_suiv + pt_fat) = 0;
				bloc_suiv = tmp;
			}


			pt->del_flag = 0;
			pt->name[0] = '\0';
			pt->first_bloc = 0;
			pt->last_bloc = 0;
			pt->size = 0;
			
			break;
		}
		pt++;
	}

	if (write_DIR_FAT_sectors() == -1) {
		return -1;
	}
	return 0;
}

int create_file (char *file) {

	if (file_found(file) == 0) { return -1; }

	// Trouver une entrée libre
	struct ent_dir * pt = pt_DIR;
	int index_libre = -1;

	for (int i = 0; i < NB_DIR; i++) {
		if (pt->del_flag == 0) {
			index_libre = i;
			break; 
		}
		pt++;
	}

	// Pas de place dans le répertoire
	if (index_libre == -1) return -1;

	// Initialisation
	pt->del_flag = 1;
	strcpy(pt->name, file);
	pt->size = 0;
	pt->first_bloc = FIN_FICHIER;
	pt->last_bloc = FIN_FICHIER;


	if (write_DIR_FAT_sectors() != 0) return -1;

	return 0;
}

// TME
short alloc_bloc () {  
	short *pt = pt_FAT;

	for (int i=0; i < NB_ENT_FAT; i++) {
		if (pt[i] == 0) {
			pt[i] = FIN_FICHIER;
			return i;
		}
	}

	return -1;
}


/*


int append_file (char* file, char *buffer, short size) { 
	
	struct ent_dir * pt = pt_DIR;
	int found = 0;

	// On cherche le fichier
	for (int i = 0; i < NB_DIR; i++) {
		if ((pt->del_flag == 1) && (strcmp(pt->name, file) == 0)) {
			found = 1;
			break; 
		}
		pt++;
	}

	// Si le fichier n'existe pas
	if (!found) return -1;

	int nb_blocs_a_ajouter = size / SIZE_SECTOR;
	int offset_buffer = 0;

	// Boucle d'ajout des blocs
	for (int i = 0; i < nb_blocs_a_ajouter; i++) {

		short new_bloc = alloc_bloc();
		if (new_bloc == -1) { return -1; }
		if (write_sector(new_bloc, buffer + offset_buffer) != 0) { return -1; }

		
		if (pt->first_bloc == FIN_FICHIER) {
			pt->first_bloc = new_bloc;
		} else {
			pt_FAT[pt->last_bloc] = new_bloc;
		}


		pt->last_bloc = new_bloc;
		offset_buffer += SIZE_SECTOR;
	}

	pt->size += size;

	if (write_DIR_FAT_sectors() != 0) {
		return -1;
	}

	return 0; 
}

*/

/*
TME
*/
int append_file (char* file, char *buffer, short size) { 
	
	struct ent_dir * pt = pt_DIR;
	int found = 0;
	//Recherche du fichier dans le répertoire
	for (int i = 0; i < NB_DIR; i++) {
		if ((pt->del_flag == 1) && (strcmp(pt->name, file) == 0)) {
			found = 1;
			break;
		}
		pt++;
	}

	if (!found) return -1;


	int octets_restants_a_ecrire = size;
	int offset_buffer = 0;
	char temp_sector[SIZE_SECTOR];

	
	int offset_dans_bloc = pt->size % SIZE_SECTOR;

	// Complétion du dernier bloc existant (si nécessaire)
	if (pt->first_bloc != FIN_FICHIER && offset_dans_bloc > 0) {
		
		
		if (read_sector(pt->last_bloc, temp_sector) != 0) return -1;

		
		int espace_libre = SIZE_SECTOR - offset_dans_bloc;
		int a_copier = (octets_restants_a_ecrire < espace_libre) ? octets_restants_a_ecrire : espace_libre;


		memcpy(temp_sector + offset_dans_bloc, buffer + offset_buffer, a_copier);
		if (write_sector(pt->last_bloc, temp_sector) != 0) return -1;

		// Mise à jour des compteurs après écriture partielle
		octets_restants_a_ecrire -= a_copier;
		offset_buffer += a_copier;
		pt->size += a_copier;
	}

	// Allocation et écriture de nouveaux blocs
	while (octets_restants_a_ecrire > 0) {
		
		short new_bloc = alloc_bloc();
		if (new_bloc == -1) return -1;


		int a_copier = (octets_restants_a_ecrire > SIZE_SECTOR) ? SIZE_SECTOR : octets_restants_a_ecrire;
		

		memset(temp_sector, 0, SIZE_SECTOR);
		memcpy(temp_sector, buffer + offset_buffer, a_copier);

		if (write_sector(new_bloc, temp_sector) != 0) return -1;

		// Mise à jour du chaînage FAT
		if (pt->first_bloc == FIN_FICHIER) {
			pt->first_bloc = new_bloc;
		} else {
			pt_FAT[pt->last_bloc] = new_bloc;
		}
		pt->last_bloc = new_bloc;


		octets_restants_a_ecrire -= a_copier;
		offset_buffer += a_copier;
		pt->size += a_copier;
	}


	if (write_DIR_FAT_sectors() != 0) return -1;


	return 0; 
}

struct ent_dir*  read_dir (struct ent_dir *pt_ent ) {
	struct ent_dir* fin_dir = pt_DIR + NB_DIR;


	if (pt_ent != NULL && (pt_ent < pt_DIR || pt_ent >= fin_dir)) {
		return NULL;
	}

	if (pt_ent == NULL || pt_ent == (fin_dir - 1)) {
		return pt_DIR;
	}


	return pt_ent + 1;
}


struct ent_dir* open_file (char *file) {
	struct ent_dir * pt = pt_DIR;

	for (int i = 0; i < NB_DIR; i++) {
		if ((pt->del_flag == 1) && (strcmp(pt->name, file) == 0)) {
			return pt; // Renvoie le pointeur vers l'entrée trouvée
		}
		pt++;
	}
	 // Fichier non trouvé
	return NULL;
}

void close_file (struct ent_dir* file) {
	write_DIR_FAT_sectors();
}