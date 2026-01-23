// Andre Bertok / Olivier Huang - Rendu 5, LU2IN011
#include <stdio.h>
#include <math.h>
#include <fenv.h>

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

void matHilbert (double *hil, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            *(hil + i*n + j) = 1/(i+j+1.);
        }
    }
}

double fact (int n) {
    if (n == 0) return 1;

    return n*fact(n-1);
}

void detHilbert (int n, double *det) {
    double up=1.0;
    double down=1.0;

    for (int i=1; i<n-1; i++) 
        up *= fact(i);

    up = pow (up, 4);

    for (int i =1; i<2*n-1; i++)
        down  *= fact(i);
    
    *det = up/down;
}

 
int main(){
    double res;
    double hil[11*11];

    fesetround(FE_TOWARDZERO);
    printf ("mode d'arrondi: zero \n");
    matHilbert (hil, 11);
    gauss_det (hil, 11, &res);
    printf("Determinant: %e \n", res);

    fesetround(FE_TONEAREST);
    printf ("mode d'arrondi: arr  \n");
    matHilbert (hil, 11);
    gauss_det (hil, 11, &res);
    printf("Determinant: %e \n", res);

    fesetround(FE_DOWNWARD);
    printf ("mode d'arrondi: moins inf  \n");
    matHilbert (hil, 11);
    gauss_det (hil, 11, &res);
    printf("Determinant: %e \n", res);

    fesetround(FE_UPWARD);
    printf ("mode d'arrondi: plus inf  \n");
    matHilbert (hil, 11);
    gauss_det (hil, 11, &res);
    printf("Determinant: %e \n", res);

    printf("\n\n\n");

    fesetround(FE_TOWARDZERO);
    printf ("mode d'arrondi: zero \n");
    detHilbert(11, &res);
    printf("Determinant: %e \n", res);

    fesetround(FE_TONEAREST);
    printf ("mode d'arrondi: arr  \n");
    detHilbert(11, &res);
    printf("Determinant: %e \n", res);

    fesetround(FE_DOWNWARD);
    printf ("mode d'arrondi: moins inf  \n");
    detHilbert(11, &res);
    printf("Determinant: %e \n", res);

    fesetround(FE_UPWARD);
    printf ("mode d'arrondi: plus inf  \n");
    detHilbert(11, &res);
    printf("Determinant: %e \n", res);

    /*
    Les déterminants obtenus sont très petits, surtout avec la méthode de Gauss
    La méthode des factorielles souffre d'erreurs d'arrondi a cause des très grandes valeurs des factorielles.
    Un calcul formel donne 3.0191e-65 pour une matrice d'ordre 11, et la méthode de Gauss s'en rapproche plus.
    */


}