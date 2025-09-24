#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>


void lance_commande(char *commande);
void lance_comande_stat(char* command);

int main(int argc, char* argv[]){
    for (int i=1; i<argc; i++) {
        lance_comande_stat(argv[i]);
    }
    
}

void lance_commande(char *commande) {

    struct timeval tv_before;
    struct timeval tv_after;

    gettimeofday(&tv_before, NULL);
    int res = system(commande);
    gettimeofday(&tv_after, NULL);

    if(res != 0) { printf("Erreur de la commande");}

    time_t diff_sec = tv_after.tv_sec - tv_before.tv_sec;
    time_t diff_ms = tv_after.tv_usec - tv_before.tv_usec;

    printf("\nTemps mis a l\'execution: %ds, %d\n", diff_sec, diff_ms);

    return;
}

void lance_comande_stat(char* command) {

    struct tms cpu_before;
    struct tms cpu_after;

    double tick_per_sec = sysconf(_SC_CLK_TCK);

    times(&cpu_before);
    int res = system(command);
    times(&cpu_after);

    if(res != 0) { printf("Erreur de la commande"); }
    
    
    double user_time = (cpu_after.tms_utime - cpu_before.tms_utime) / tick_per_sec;
    double sys_time = (cpu_after.tms_stime - cpu_before.tms_stime) / tick_per_sec;
    double user_fils_time = (cpu_after.tms_cutime - cpu_before.tms_cutime) / tick_per_sec;
    double sys_fils_time = (cpu_after.tms_cstime - cpu_before.tms_cstime) / tick_per_sec;
    double total = user_time + sys_time + user_fils_time + sys_fils_time;

    printf("\n=== Statistiques de \"%s\" ===\n", command);
    printf("Temps total : %.6fs\n", total);
    printf("Temps utilisateur : %.6fs\n", user_time);
    printf("Temps systeme : %.6fs \n", sys_time);
    printf("Temps utilisateur fils : %.6fs \n", user_fils_time);
    printf("Temps systeme fils : %.6fs \n\n", sys_fils_time);

    return;
}


/*
Pour ./times "sleep 5" ./loopcpu ./loopsys 
on a 

=== Statistiques de "sleep 5" ===
Temps total : 0.00s
Temps utilisateur : 0.00s
Temps systeme : 0.00s 
Temps utilisateur fils : 0.00s 
Temps systeme fils : 0.00s 


=== Statistiques de "./loopcpu" ===
Temps total : 10.96s
Temps utilisateur : 0.00s
Temps systeme : 0.00s 
Temps utilisateur fils : 10.96s 
Temps systeme fils : 0.00s 


=== Statistiques de "./loopsys" ===
Temps total : 5.71s
Temps utilisateur : 0.00s
Temps systeme : 0.00s 
Temps utilisateur fils : 1.86s 
Temps systeme fils : 3.85s 
*/