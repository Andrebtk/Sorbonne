#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAILLE 6


int compte_mots(char **ptab_mots);

int compte_mots_chaine(char *chaine) {
  int nb_mot = 0;

  while (*chaine != '\0') {
    if (*chaine == ' ') {
      chaine++;
      continue;
    }
    nb_mot++;
    while ( (*chaine != ' ') && (*chaine != '\0')) chaine++;
  }
  return nb_mot;
}

char **decompose_chaine(char *chaine)
{

  /* Fonction vue en TD, exercice 2, question 7 */

  char *pc= chaine;
  int nb_mots=0;
  char **ptab;
  char *psrc_mot;
  int ind_mot=0;

  //comptages des mots
  nb_mots=compte_mots_chaine(chaine);
	
  if (nb_mots == 0)
    return NULL;
  // allocation du tableau

  ptab = malloc((nb_mots + 1) * sizeof(char *));
  ptab[nb_mots] = NULL;
	
  // copie des mots
	
  pc=chaine;
  while (*pc)
    {
      if(*pc == ' ')
        {
          pc++;
          continue;
        }

      psrc_mot = pc;

      while((*pc != ' ') && (*pc)) pc++;

      //allocation du mot
      ptab[ind_mot] = malloc((pc - psrc_mot + 1)* sizeof(char));
      //copie du mot
      memcpy(ptab[ind_mot], psrc_mot, pc - psrc_mot);
      //insertion du marqueur de fin de chaine
      *(ptab[ind_mot] + (pc - psrc_mot)) = '\0';

      ind_mot++;
    }
	

  return ptab;
}

char *compose_chaine(char **ptab_mots)
{
  int nb_mots_chaine = compte_mots(ptab_mots);
  int tailleMot = 0;

  for (int i=0; ptab_mots[i] != NULL; i++){
    for (int j=0; ptab_mots[i][j] != '\0'; j++){
      tailleMot++;
    }
  }

  tailleMot += nb_mots_chaine; //Pour les espaces

  char *res = malloc(sizeof(char) * (tailleMot+1));
  char *temp = res;
  for (int i=0; ptab_mots[i] != NULL; i++) {
    int j;
    for (j=0; ptab_mots[i][j] != '\0'; j++) continue;

    memcpy (temp, ptab_mots[i], j);

    temp+=j;
    
    if (ptab_mots[i+1] != NULL){
      *temp += ' ';
      temp++;
    }
  }
  *res += '\0';
  return res;
}
		
void detruit_tab_mots(char **ptab_mots)
{

  /* Fonction vue en TD, exercice 2, question 5 */

  int i=0;

  if (ptab_mots)
    while(ptab_mots[i])
      free(ptab_mots[i++]);

  free(ptab_mots);
}

int compte_mots(char **ptab_mots)
{
  if (ptab_mots == NULL) return 0;

  int res;
  for (res = 0; ptab_mots[res] != NULL; res++) {
   continue;
  }
  return res;
}

void affiche_tab_mots(char **ptab_mots)
{
  for (int i = 0; ptab_mots[i] != NULL; i++) {
    printf("%s ", ptab_mots[i]);
  }
}

char **reduit_tab_mots(char **ptab_mots) {
	if (ptab_mots == NULL) return NULL;

	int i, j;
	for (i = 0; ptab_mots[i] != NULL; i++) {
		for (j = 0; ptab_mots[j] != NULL; j++) {
			if (i != j && strcmp(ptab_mots[i], ptab_mots[j]) == 0) {
				ptab_mots[i] = ptab_mots[j];
				break;
			}
		}
	}

	return ptab_mots;
}

void detruit_tab_mots2(char **ptab_mots)
{
	if (ptab_mots != NULL) {
		for (int i = 0; ptab_mots[i] != NULL; i++) {
			if (ptab_mots[i] != NULL) {
				free(ptab_mots[i]);
				ptab_mots[i] = NULL;
			}
		}
	}
	free(ptab_mots);
}


int main() {
	char *mot = "b dd e ";
	printf("%d \n", compte_mots_chaine(mot));


	char *tab[TAILLE+1] = {"mot1", "et", "hell", "mot2", "et", "mot3", NULL};
	
	for (int i=0; tab[i] != NULL; i++) {
		printf ("mot: %s, adress: %p \n", tab[i], &tab[i]);
	}

	//affiche_tab_mots(tab);
	printf("\n%d \n", compte_mots (tab));

	char* res = compose_chaine(tab);
	printf ("chaine compose: %s \n", res);



	char *tab2[] = {"mot1", "et", "hell", "mot2", "et", "mot3", NULL};
	reduit_tab_mots(tab2);

	for (int i = 0; tab2[i] != NULL; i++) {
		printf("%s (address: %p)\n", tab2[i], tab2[i]);
	}

	/*
	Exercice 4.2 : Si on libère "et" une première fois, lorsque l'on arrivera dessus une deuxième fois, le pointeur pointera sur NULL.
	Voir la fonction void detruit_tab_mots2(char **ptab_mots);
	*/

	free(res);
	return 1;
}


