#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if(argc<2) return-1;

	int niveau = atoi(argv[1]);

	if(niveau != 0) {
		for(int i=0; i<2; i++) {
			int p = fork();
			if(p==0) {
				char next[5];
				sprintf(next, "%d", niveau - 1);	
				int err = execl("./arbre", "arbre", next, NULL);
				perror("Erreur exec");
				exit(1);
			}
				
		}
	}

	sleep(30); 
	exit(1);
}