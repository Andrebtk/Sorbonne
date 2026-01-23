// Andre Bertok / Olivier Huang - Rendu 5, LU2IN011
#include <stdio.h>

void gauss_det(double *a, int n, double *det) {
    int i, j, k;
    double aux, aux2;
    *det = 1;
 
    for (i = 0; i < n - 1; i++){
        aux = *(a + i * n + i);
 
        *det *= aux;
        for (k = i + 1; k < n; k++){
            *(a + i * n + k) /= aux;
        }
 
        for (k = i + 1; k < n; k++){
            aux2 = *(a + k * n + i);
            for (j = i + 1; j < n; j++){
                *(a + k * n + j) -= aux2 * *(a + i * n + j);
            }
        }
    }
 
    *det *= *(a + n * n - 1);
}

int main(){
    int n=4;
    double det[] = {
        10, 0, -5, 15,
        -2, 7, 3, 0,
        8, 14, 1, 2,
        0, -21, 1, -1
    };

    double res;
    gauss_det (det, n, &res);
    printf("Determinant: %lf \n", res);
}