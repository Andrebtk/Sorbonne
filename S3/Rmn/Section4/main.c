#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

void gauss_sp (float *a, float *b, int n) {
    int i, j, k;
    float aux, aux2;

    for (i=0; i<n-1; i++) {
        aux = *(a +i*n + i);
        for (k=i+1; k<n; k++) 
            *(a+i*n+k) /=aux;
        *(b+i) /= aux ;

        for (k=i+1;k<n;k++) {
            aux2 = *(a + k*n +i);
            for (j=i+1; j<n; j++) 
                *(a + k*n + j) -= aux2 * *(a + i*n +j);
            *(b + k) -= aux2 * *(b+i);
        }
    }
    *(b + n-1) /= *(a + n*n -1);
    for (i=n-2; i>=0; i--) {
        aux= *(b + i);
        for (k=i+1; k<n; k++)
            aux -= *(a + i*n + k) * *(b + k);
        *(b + i) = aux;
    }
}
//Matrice float
void afficheFloat (float *a, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%.2f ", *(a + i*n+j));
        }
        printf("\n");
    }
}

void afficheVect (float *a, int n) {
    printf("[");
    for (int i=0; i<n; i++) {
        printf("%.3f", *(a + i));
        if (i!=n-1) printf("\n");
    }
    printf("]\n");
}


void gauss_ap (float *a, float *b, int n) {
    int i, j, k, il;
    float aux, aux2;

    for (i=0; i<n-1; i++) {

        aux = fabs(*(a + i*n +i));
        il = i;
        for (k=i+1; k<n; k++) {
            if (aux< fabs(*(a + k*n + i))) {
                aux = fabs(*(a +k*n +i));
                il = k;
            }
        }
        if (il != i) {
            for (j=i; j<n; j++) {
                aux = *(a + il*n +j);
                *(a + il*n + j) =*(a + i*n + j);
                *(a + i*n +j) = aux;
            }
            aux = *(b+il);
            *(b + il) = *(b + i);
            *(b+i) = aux;
        }

        aux = *(a +i*n + i);
        for (k=i+1; k<n; k++) 
            *(a+i*n+k) /=aux;
        *(b+i) /= aux ;

        for (k=i+1;k<n;k++) {
            aux2 = *(a + k*n +i);
            for (j=i+1; j<n; j++) 
                *(a + k*n + j) -= aux2 * *(a + i*n +j);
            *(b + k) -= aux2 * *(b+i);
        }
    }
    *(b + n-1) /= *(a + n*n -1);
    for (i=n-2; i>=0; i--) {
        aux= *(b + i);
        for (k=i+1; k<n; k++)
            aux -= *(a + i*n + k) * *(b + k);
        *(b + i) = aux;
    }
}

void rand_a_b (float *a, float *b , int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            *(a + i*n + j) = (rand() % 200) -100;
        }
    }

    for (int i=0; i<n; i++) {
        *(a + i) = i;
    }


    
}



int main() {

    /*
    float a[] = {
        2.5, 1.5, 1.7, 2.5,
        1.7, 1.8, 2.2, 1.8,
        2.0, 1.2, 2.5, 3.0,
        2.1, 1.2, 2.2, 1.5
    };

    float b[] = {
        11.11,
        10.67,
        12.41,
        10.52
    };

    gauss_sp (a, b, 4);

    afficheVect(b, 4);
    

    float a1[] = {
        21.0, 130.0, 0.0, 2.1,
        13.0, 80.0, 4.74, 752.0,
        0.0, -0.4, 3.9816, 4.2,
        0.0, 0.0, 1.7, 0.9
    };

    float b1[] = {
        153.1,
        849.74,
        7.7816,
        2.6
    };

    printf("Gauss sans recherche partielle \n");
    fesetround(FE_TOWARDZERO);
    printf ("mode d'arrondi: zero \n");
    gauss_sp (a1, b1, 4);
    afficheVect(b1, 4);
    printf("\n");

    float b2[] = {
        153.1,
        849.74,
        7.7816,
        2.6
    };

    fesetround(FE_TONEAREST);
    printf ("mode d'arrondi: arr  \n");
    gauss_sp (a1, b2, 4);
    afficheVect(b2, 4);
    printf("\n");

    float b3[] = {
        153.1,
        849.74,
        7.7816,
        2.6
    };

    fesetround(FE_DOWNWARD);
    printf ("mode d'arrondi: moins inf  \n");
    gauss_sp (a1, b3, 4);
    afficheVect(b3, 4);
    printf("\n");

    float b4[] = {
        153.1,
        849.74,
        7.7816,
        2.6
    };

    fesetround(FE_UPWARD);
    printf ("mode d'arrondi: plus inf  \n");
    gauss_sp (a1, b4, 4);
    afficheVect(b4, 4);
    printf("\n");


    printf("Gauss avec recherche partielle \n");
    float b11[] = {
        153.1,
        849.74,
        7.7816,
        2.6
    };
    
    fesetround(FE_TOWARDZERO);
    printf ("mode d'arrondi: zero \n");
    gauss_ap (a1, b11, 4);
    afficheVect(b11, 4);
    printf("\n");

    float b21[] = {
        153.1,
        849.74,
        7.7816,
        2.6
    };

    fesetround(FE_TONEAREST);
    printf ("mode d'arrondi: arr  \n");
    gauss_ap (a1, b21, 4);
    afficheVect(b21, 4);
    printf("\n");

    float b31[] = {
        153.1,
        849.74,
        7.7816,
        2.6
    };

    fesetround(FE_DOWNWARD);
    printf ("mode d'arrondi: moins inf  \n");
    gauss_ap (a1, b31, 4);
    afficheVect(b31, 4);
    printf("\n");

    float b41[] = {
        153.1,
        849.74,
        7.7816,
        2.6
    };

    fesetround(FE_UPWARD);
    printf ("mode d'arrondi: plus inf  \n");
    gauss_ap (a1, b41, 4);
    afficheVect(b41, 4);
    printf("\n");
    */
    
    // La methode avec recherche partielle de pivot a moins d'erreur
    // d'arrondi et par consequent quand on change le mode d'arrondi 
    // les resultat sont plus proche
    
    
    int n = 1000;
    float *a = malloc (sizeof(float) * n*n);
    float *b = malloc (sizeof(float) * n);

    
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            *(a + i*n + j) = (float) (rand() % 200) -100.0;
        }
    }
    
    for (int i=0; i<n; i++) {
        *(b + i) = i;
    }

    clock_t begin = clock(); 
    gauss_sp (a, b, n);
    clock_t end = clock();
    unsigned long millis = (end -  begin);
    printf( "Finished in %ld with gauss_sp \n", millis );

    for (int i=0; i<n; i++) {
        *(b + i) = i;
    }

    begin = clock(); 
    gauss_ap (a, b, n);
    end = clock();
    millis = (end -  begin);
    printf( "Finished in %ld with gauss_ap \n", millis );


    free (a);
    free (b);
    


    return 0;
}