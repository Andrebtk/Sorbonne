#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 100
#define P 3

int *alloue_tableau1(int n) {
	int *res = malloc(sizeof(int)*n);
	return res;
}

void alloue_tableau2(int **T, int n){
	*T = malloc(sizeof(int)*n);
}

void desalloue_tableau (int *tab) {
	free(tab);
}

void remplir_tableau(int *tab, int n, int v){
	for (int i=0; i<n; i++) {
		tab[i] = rand() % v;
	}
}

void affichageTableau(int* tab, int n){
	printf("[ ");	
	for (int i=0;i<n;i++){
		printf("%d ",tab[i]);	
	}
	printf("]\n");
}


int diff(int *tab, int n) {
	int res = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			res += pow((tab[i] - tab[j]),2);
		}
	}
	return res;
}

int diff2(int *tab, int n) {
	int res=0;
	int tmp=0;
	for (int i=0; i<n; i++) {
		res += n*pow(tab[i],2);
		tmp += tab[i];
	}
	return 2*(res - pow(tmp, 2));
}






int **alloue_matrice(int n){
	int **res = malloc(sizeof(int*)*n);
	for (int i=0; i<n; i++){
		res[i] = malloc(sizeof(int)*n);
	}
	return res;
}

void desalloue_matrice (int **tab, int n) {
	for (int i=0; i<n; i++) {
		free(tab[i]);
	}
	free(tab);
}

void remplir_matrice (int **tab, int n, int v) {
	for (int i = 0; i<n; i++) {
		for (int j=0; j<n; j++) {
			tab[i][j] = rand() % v;
		}
	}
}

void afficher_matrice (int **tab, int n) {
	printf("[\n");
	for (int i = 0; i<n; i++) {
		for (int j=0; j<n; j++) {
			printf("%d ",tab[i][j]);
		}
		printf("\n");
	}
	printf("]\n");
}



int all_diff(int **mat, int n){
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
		
			for (int i2=0; i2<n; i2++){
				for (int j2=0; j2<n; j2++){
						if (mat[i][j] == mat[i2][j2] && !(i==i2 && j==j2)) {
							return 1;
						}		
					}
			}
			
		}
	}
	return 0;
}


int all_diff2(int **mat, int n, int v){
	int tab[v];
	int u=0;
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			for (int m=0; m<u; m++){
				if(tab[m] == mat[i][j]) return 1;
			}
			tab[u] = mat[i][j];
			u++;
		}
	}
	return 0;
}

int** prod(int **a, int **b, int n) {
	int **t = alloue_matrice(n);
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			t[i][j] = 0;
			for (int k=0; k<n; k++) {
				t[i][j] += a[i][k] * b[k][j];
			}			
		}
	}
	return t;
}

int **prodOpti(int **a, int **b, int n) {
	int **t = alloue_matrice(n);
	for (int i=0; i<n; i++) {
		for (int j=i; j<n; j++) {
			t[i][j] = 0;
			for (int k=i; k<=j; k++){
				t[i][j] = a[i][k] * b[k][j];
			}
		}
	}
	return t;
}


clock_t init;
clock_t final;
double temps_cpu;


int main() {
 	srand(time(NULL));
 	/*
	int *tab = alloue_tableau1(N);
	alloue_tableau2(&tab, N);
	remplir_tableau(tab,N,10);
	affichageTableau(tab, N);
	
	
	init = clock();
	diff(tab, N);
	final = clock();
	temps_cpu = ((double)(final - init))/CLOCKS_PER_SEC;
	printf ("diff1 -> %d %f\n", N, temps_cpu ); 
	
	
	init = clock();
	diff2(tab, N);
	final = clock();
	temps_cpu = ((double)(final - init))/CLOCKS_PER_SEC;
	printf ("diff2 -> %d %f\n", N, temps_cpu );
	
	
	desalloue_tableau(tab);	
	*/
	
	int **t1 = alloue_matrice(P);
	remplir_matrice(t1, P, 10);
	
	int **t2 = alloue_matrice(P);
	remplir_matrice(t2, P, 10);
	
	afficher_matrice(t1, P);
	afficher_matrice(t2, P);
	

	
	
	/*
	int **res1 = prod(q1 ,q2, P);
	//afficher_matrice(res1, P);
	
	int **res2 = prodOpti(q1 ,q2, P);
	//afficher_matrice(res2, P);
	*/
	/*
	init = clock();
	all_diff(t, P);
	final = clock();
	temps_cpu = ((double)(final - init))/CLOCKS_PER_SEC;
	printf ("all_diff1 -> %d %f\n", 500, temps_cpu ); 
	
	
	init = clock();
	all_diff2(t, P, 500);
	final = clock();
	temps_cpu = ((double)(final - init))/CLOCKS_PER_SEC;
	printf ("all_diff2 -> %d %f\n", 500, temps_cpu );
	*/
	
	desalloue_matrice(t1, P);
	desalloue_matrice(t2, P);
	
	return 0;
	
	
}
