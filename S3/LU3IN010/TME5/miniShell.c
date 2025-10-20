#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <unistd.h>

#define NBARGS 20

void getInput(char rep[], int *w);
void get_arguments(char* input, char* separateur, char *list_arg[]);
void print_list(char *list_arg[], int n);

int main(int argc, char *argv[]) {

	
	char input[50];
	struct rusage r;
	int w;
	int times_actif;

	for(;;) {
		int w = 1;
		times_actif = 0;

		printf("$> ");
		getInput(input, &w);
		

		char* separateur = " ";
		char *list_arg[NBARGS];
		get_arguments(input, separateur, list_arg);
		if (list_arg[0] == NULL) continue;
		

		/*
			// Si la commande commence par "times", activer la mesure du temps et 
			supprimer "times" du tableau des arguments pour exécuter la commande réelle
		*/
		if( strcmp(list_arg[0], "times")==0 ){
			times_actif = 1;

			int i = 0;
			while(list_arg[i+1] != NULL) {
				list_arg[i] = list_arg[i+1];
				i++;
			}
			list_arg[i] = NULL;
		}


		char com[100] = "/bin/";
		int lenght_input = strlen(list_arg[0]);
		strncat(com, list_arg[0], lenght_input);

		int p = fork();
		if(p==0) {
			int err = execv(com, list_arg);
			perror("Erreur commande");
			exit(1);
		}

		if(times_actif == 1) {
			wait3(NULL, 0, &r);
			printf("Temps Util. : %f\n", r.ru_utime.tv_sec + 1E-6*r.ru_utime.tv_usec);
			printf("Temps Sys. : %f\n\n", r.ru_stime.tv_sec + 1E-6*r.ru_stime.tv_usec);
		} else if(w == 1) {
			wait(NULL);
		} else {
			printf("[Processus en arrière-plan]\n");
		}

	}

}



void get_arguments(char* input, char* separateur, char *list_arg[]) {
	int i = 0;
	char *strToken = strtok(input, separateur);
	while (strToken != NULL) {
		list_arg[i++] = strdup(strToken);
		strToken = strtok(NULL, separateur);
	}
	list_arg[i] = NULL;
}



void getInput(char *input, int *w) {

	fgets(input, 25, stdin);

	if(strncmp(input, "quit", 4)==0) {
		exit(0);
	}

	int len = strlen(input);
	if(len > 0 && input[len-1] == '\n') input[len-1] = '\0'; // retire \n

	if(len > 1 && input[len-2] == '&'){
		*w = 0;
		input[len-2] = '\0'; // retire &
	} else {
		*w = 1;
	}
}


void print_list(char *list_arg[], int n) {
	for(int i=0; i<n; i++){
		printf("t[%d]=%s\n", i, list_arg[i]);
	}
}