#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>


#define MAXFILS 3

void multiGrep(int argc, char **argv);
void multiGrepConstraint(int argc, char **argv);
void multiGrepStat(int argc, char **argv);
void zombie();

int main(int argc, char **argv) {
	multiGrepStat(argc, argv);
	//zombie();
}




void multiGrep(int argc, char **argv) {
	printf("Multi-grep sur \"%s\"\n", argv[1]);

    for(int i=2; i<argc; i++) {
        int p = fork();

		if(p==0){
			int err = execl("/bin/grep", "grep", argv[1], argv[i], NULL);
			perror("Erreur exec");
			exit(1);
		}

    }

	for(int i=0; i<argc-2; i++) {
		wait(NULL);
	}
}

void multiGrepConstraint(int argc, char **argv){
	printf("Multi-grep constraint sur \"%s\"\n", argv[1]);

	int num_proc_fils = 0;

	for(int i=2; i<argc; i++) {
		
		if (num_proc_fils >= MAXFILS) {
			wait(NULL);
			num_proc_fils--;
		}

		int p = fork();
		if(p==0){
			int err = execl("/bin/grep", "grep", argv[1], argv[i], NULL);
			perror("Erreur exec");
			exit(1);
		}
		num_proc_fils++;
	}

	for(int i =0; i<num_proc_fils; i++) {
		wait(NULL);
	}
}


void multiGrepStat(int argc, char **argv) {
	printf("Multi-grep sur \"%s\"\n", argv[1]);

	struct rusage r;

	for(int i=2; i<argc; i++) {
		int p = fork();

		if(p==0){
			int err = execl("/bin/grep", "grep", argv[1], argv[i], NULL);
			perror("Erreur exec");
			exit(1);
		}
	}

	for(int i=0; i<argc-2; i++) {
		wait3(NULL, 0, &r);
		printf("Temps Util. : %f\n", r.ru_utime.tv_sec + 1E-6*r.ru_utime.tv_usec);
		printf("Temps Sys. : %f\n\n", r.ru_stime.tv_sec + 1E-6*r.ru_stime.tv_usec);
	}
}


void zombie() {
	//Pere
	
	int p = fork();
	if(p==0) { // Fils 1
		exit(0);
	}

	p = fork();
	if(p==0) { // Fils 1
		exit(0);	
	}

	sleep(10);
	wait(NULL);
	wait(NULL);
}