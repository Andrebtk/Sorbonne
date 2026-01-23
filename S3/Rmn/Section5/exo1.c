// Andre Bertok / Olivier Huang - Rendu 5, LU2IN011
#include <stdio.h>

/* Ce problème peut être modélisé par un système matriciel, 
car il s'agit de déterminer la quantité de nourriture consommée 
par chaque type de créature. Cela revient à résoudre l'équation AX = B, 
où X représente les rations que nous cherchons à calculer. */
 
void gauss_jordan(float *a, float *b, int n) {
    int i, j, k;
    float aux;
 
    for (i = 0; i < n; i++) {
        aux = a[i * n + i];
        for (j = i + 1; j < n; j++){
            a[i * n + j] /= aux;
        }
        for (j = 0; j < n; j++){
            b[i * n + j] /= aux;
    }
        for (k = 0; k < n; k++) {
            if (k != i) {
                aux = a[k * n + i]; 
                for (j = i + 1; j < n; j++){
                    a[n * k + j] -= aux * a[i * n + j];
                }
                for (j = 0; j < n; j++){
                    b[n * k + j] -= aux * b[n * i + j];
                }
            }
        }
    }
}
 
void gauss_jordan_opt(float *a, float *b, int n) {
    int i, j, k;
    float aux;
 
    for (i = 0; i < n; i++) {
        aux = *(a + i * n + i);
        for (j = i + 1; j < n; j++){
            *(a + i * n + j) /= aux;
        }
        for (j = 0; j < n; j++){
            *(b + i * n + j) /= aux;
    }
        for (k = 0; k < n; k++) {
            if (k != i) {
                aux = *(a + k * n + i); 
                for (j = i + 1; j < n; j++){
                    *(a + n * k + j) -= aux * *(a + n * i + j);
                }
                for (j = 0; j < n; j++){
                    *(b + n * k + j) -= aux * *(b + n * i + j);
                }
            }
        }
    }
}

void affiche(float *mat, int n){
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
        printf("%.1f ",mat[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");
}
 
int main(){
    int n=4;
    float a[] = { 
        15, 34, 27, 2,
        8, 23, 10, 1, 
        11, 17, 9, 4, 
        8, 65, 45, 7
    };
 
    float b[] = {
        82.4, 130.5, 149.9, 95.6,
        43.1, 69.6, 81.5, 52, 
        74.1, 112.3, 102.8, 66.2,
        166.5, 248.5, 228.5, 152
    };
    
    gauss_jordan_opt(a,b,n);
    affiche(b,n);
}