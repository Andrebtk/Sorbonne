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

	for (int i=0; i<NB_DIR; i++) {
		if(pt->del_flag == 1) {
			printf("Fichier de nom: \'%s\', de taille: %d octets \n", pt->name, pt->size);

			//Affiche les bloc de données
			short *pt_fat = pt_FAT;
			
			int bloc_suiv = pt->first_bloc;

			while(bloc_suiv != -1) {
				printf("bloc num: %d\n", bloc_suiv);
				bloc_suiv = *(pt_fat + bloc_suiv);
			}
		}
		pt++;
	}

}

// TME
int cat_file (char* file) {
	if (file_found(file) == 1) return -1;

	char buffer[128];
	
	struct ent_dir * pt = pt_DIR;
	for (int i=0; i<NB_DIR; i++) {
		if((pt->del_flag == 1)  && (strcmp(pt->name, file)==0)) {
			

			//Affiche les bloc de données
			short *pt_fat = pt_FAT;
			
			int bloc_suiv = pt->first_bloc;

			read_sector(bloc_suiv, buffer);

			while(bloc_suiv != -1) {
				printf("%s \n", buffer);
				bloc_suiv = *(pt_fat + bloc_suiv);
				read_sector(bloc_suiv, buffer);
			}
			
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



	// maybe just -> return write_DIR_FAT_sectors()
	if (write_DIR_FAT_sectors() == -1) {
		return -1;
	}
	return 0;
}

int create_file (char *file) {
  /* A COMPLETER */  
}

// TME
short alloc_bloc () {  
	short *pt = pt_FAT;

	for (int i=0; i < NB_ENT_FAT; i++) {
		if ( *pt == 0) {
			*pt = FIN_FICHIER;
			return i;
		}
		pt++;
	}

	return -1;

}
 	
// TME
int append_file  (char*file, char *buffer, short size) { 
	


	// maybe just -> return write_DIR_FAT_sectors()
	if (write_DIR_FAT_sectors() == -1) {
		return -1;
	}
	return 0;
}

struct ent_dir*  read_dir (struct ent_dir *pt_ent ) {
  /* A COMPLETER */  
}
