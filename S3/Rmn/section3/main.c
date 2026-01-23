/*
Voici le fichier pour le code de l'atelier 3 au lieu du rendu 3, 
car nous avons complété l'atelier comme convenu. 
Merci encore de nous permettre de rendre l'atelier au lieu du rendu

Andre Bertok, Oliver Huang
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void prodmatmat (double *a, double *b, double *p, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            p[i * n + j] = 0;
            for (int k=0; k<n; k++) {
                p[i*n+j] += *(a+i*n+k) * *(b+k*n+j);
            }
        }
    }
}

void affiche (char* nom, double *a, int n) {
    printf("Matrice : %s \n", nom);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%lf ", a[i*n+j]);
        }
        printf("\n");
    }
}

void afficheFloat (char* nom, float *a, int n) {
    printf("\n\nMatrice : %s \n", nom);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%f ", a[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");
}


void prodmatmatOtpi(double *a, double *b, double *p, int n) {
    double *pa, *pb, *res;

    for (res=p; res<p+n; res++){
        *res = 0;   
    }

    for (int i=0; i<n; i++) {
        for (int j =0; j<n; j++){
            res = p+i*n+j;
            pa = a+i*n;
            pb = b+j;
            for (int k=0; k<n; k++) {
                *res+= (*pa) * (*pb);
                pa++;
                pb+=n;
            }
        }
    }
}



void strassen_2 (float *a, float *b, float *res) {
    float m1 = (*a + *(a + 3)) * (*b + *(b + 3));
    float m2 = (*(a + 2) + *(a + 3)) * (*b);
    float m3 = (*a) * ( *(b + 1) - *(b + 3));
    float m4 = (*(a + 3) * ( *(b + 2) - (*b)));
    float m5 = (*a + *(a+1)) * (*(b + 3));
    float m6 = (*(a + 2) - (*a)) * ((*b) + *(b + 1));
    float m7 = ( *(a + 1) - *(a + 3)) * (*(b + 2) + *(b + 3));

    *res = m1 + m4 - m5 + m7;
    *(res + 1) = m3 + m5;
    *(res + 2) = m2 + m4;
    *(res + 3) = m1 - m2 + m3 + m6;
}

void somme_matrice (float *a, float *b, float *res, int taille) {
    for (int i = 0; i < taille * taille; i++) {
        *(res + i) = *(a + i) + *(b + i);
    }
}

void diff_matrice (float *a, float *b, float *res, int taille) {
    for (int i = 0; i < taille * taille; i++) {
        *(res + i) = *(a + i) - *(b + i);
    }
}

void produit_elementaire_2 (float *a, float *b, float *res) {
    *res     = (*a) * (*b) + (*(a+1)) * (*(b+2));
    *(res+1) = (*a) * (*(b+1)) + (*(a+1)) * ( *(b+3));
    *(res+2) = (*(a+2) * (*b)) + (*(a+3) * (*(b+2)));
    *(res+3) = (*(a+2) * (*(b+1))) + (*(a+3) * (*(b+3))); 

}


void strassen (float *a, float *b, float *res, int k ) {
    //cas de base
    if (k <= 2) {
        produit_elementaire_2 (a, b, res);
        return;
    }
    
    int half = k / 2;
    int t = half * half;

    float *a12 =  (float *)malloc(t * sizeof(float));
    float *a21 =  (float *)malloc(t * sizeof(float));
    float *a11 =  (float *)malloc(t * sizeof(float));
    float *a22 =  (float *)malloc(t * sizeof(float));
    float *b11 =  (float *)malloc(t * sizeof(float));
    float *b12 =  (float *)malloc(t * sizeof(float));
    float *b21 =  (float *)malloc(t * sizeof(float));
    float *b22 =  (float *)malloc(t * sizeof(float));
    float *c11 =  (float *)malloc(t * sizeof(float));
    float *c12 =  (float *)malloc(t * sizeof(float));
    float *c21 =  (float *)malloc(t * sizeof(float));
    float *c22 =  (float *)malloc(t * sizeof(float));
    float *M1 =   (float *)malloc(t * sizeof(float));
    float *M2 =   (float *)malloc(t * sizeof(float));
    float *M3 =   (float *)malloc(t * sizeof(float));
    float *M4 =   (float *)malloc(t * sizeof(float));
    float *M5 =   (float *)malloc(t * sizeof(float));
    float *M6 =   (float *)malloc(t * sizeof(float));
    float *M7 =   (float *)malloc(t * sizeof(float));
    float *temp1= (float *)malloc(t * sizeof(float));
    float *temp2= (float *)malloc(t * sizeof(float));

    //On decoupe a et b en 4 sous matrice
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int idx = i * half + j;
            a11[idx] = a[i * t + j];
            a12[idx] = a[i * t + (j + half)];
            a21[idx] = a[(i + half) * t + j];
            a22[idx] = a[(i + half) * t + (j + half)];
 
            b11[idx] = b[i * k + j];
            b12[idx] = b[i * k + (j + half)];
            b21[idx] = b[(i + half) * k + j];
            b22[idx] = b[(i + half) * k + (j + half)];
        }
    }

    //M1
    somme_matrice(a11, a22, temp1, half);  
    somme_matrice(b11, b22, temp2, half); 
    strassen(temp1, temp2, M1, half);    

    // M2 = (A21 + A22) * B11
    somme_matrice(a21, a22, temp1, half);  
    strassen(temp1, b11, M2, half);       
    
    // M3 = A11 * (B12 - B22)
    diff_matrice(b12, b22, temp2, half); 
    strassen(a11, temp2, M3, half);            
    
    // M4 = A22 * (B21 - B11)
    diff_matrice(b21, b11, temp2, half);  
    strassen(a22, temp2, M4, half);            
    
    // M5 = (A11 + A12) * B22
    somme_matrice(a11, a12, temp1, half);       
    strassen(temp1, b22, M5, half);            
    
    // M6 = (A21 - A11) * (B11 + B12)
    diff_matrice(a21, a11, temp1, half);  
    somme_matrice(b11, b12, temp2, half);       
    strassen(temp1, temp2, M6, half);          
    
    // M7 = (A12 - A22) * (B21 + B22)
    diff_matrice(a12, a22, temp1, half);  
    somme_matrice(b21, b22, temp2, half);       
    strassen(temp1, temp2, M7, half);         



    //Calcule de la matrice C

    // C11 = temp2 + M7
    somme_matrice(M1, M4, temp1, half);        
    diff_matrice(temp1, M5, temp2, half); 
    somme_matrice(temp2, M7, c11, half);       
    
    // C12 = M3 + M5A
    somme_matrice(M3, M5, c12, half);       
    
    // C21 = M2 + M4   
    somme_matrice(M2, M4, c21, half);   

    // C22 = temp2 + M6
    diff_matrice(M1, M2, temp1, half);
    somme_matrice(temp1, M3, temp2, half);
    somme_matrice(temp2, M6, c22, half);         

    afficheFloat ("c11", c11, 2);
    afficheFloat ("c12", c12, 2);
    afficheFloat ("c21", c21, 2);
    afficheFloat ("c22", c22, 2);
    
    //On assemble C
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int idx = i * half + j;
            res[i * k + j] = c11[idx];
            res[i * k + (j + half)] = c12[idx];
            res[(i + half) * k + j] = c21[idx];
            res[(i + half) * k + (j + half)] = c22[idx];
        }
    }


    free(a11); free(a12); free(a21); free(a22);
    free(b11); free(b12); free(b21); free(b22);
    free(c11); free(c12); free(c21); free(c22);
    free(M1); free(M2); free(M3); free(M4);
    free(M5); free(M6); free(M7);
    free(temp1); free(temp2);
}




int main () {

    int n = 4;
    double a[16] = {
        15, 34, 27, 2, 
        8, 23, 10, 1, 
        11, 17, 9, 4, 
        8, 65, 45, 7 
    };

    double b[16] = {
        1, 2, 2.5, 2,
        0.7, 1, 1.5, 1,
        0.6, 1.1, 1.2, 0.8,
        10, 15, 7, 5
    };

    double p[16];
    /*Ce problème conduit a un produit matriciel car on veut calculer le nombre d'une certaine ration de
    nourriture par armée ce qui revient a faire la somme des multiplication des lignes de la premiere matrice
    aux colonnes de la deuxieme matrice*/
    /*
    prodmatmatOtpi (a, b, p, 4);
    
    affiche ("result", p, 4);

    printf("\n\nExo 2: \n\n");

    int input;
    printf("Dimension: ");
    scanf ("%d", &input);

    double *x = malloc(sizeof(double) * (input*input));
    double *y = malloc(sizeof(double) * (input*input));
    double *z = malloc(sizeof(double) * (input*input));


    for (int i=0; i<input; i++) {
        for (int j=0; j<input; j++) {
            *(x + i*input + j) = (rand()/ (double)RAND_MAX)*2 -1;
            *(y + i*input + j) = (rand()/ (double)RAND_MAX)*2 -1;
        }
    }

    int iter[3] =  {10, 100, 500};

   
    for (int i = 0; i<3; i++) {
        clock_t begin = clock();
        for (int j = 0; j < iter[i]; j++){
            prodmatmat(x, y, z, input);
        }
        clock_t end = clock();
        unsigned long millis = (end -  begin);
        printf( "Finished in %ld \n", millis );  
    }

    printf("\n\n");

    for (int i = 0; i<3; i++) {
        clock_t begin = clock();
        for (int j = 0; j < iter[i]; j++){
            prodmatmatOtpi(x, y, z, input);
        }
        clock_t end = clock();
        unsigned long millis = (end -  begin);
        printf( "Finished in %ld \n", millis );  
    }

    //On voit que la version optimisée est plus rapide en moyenne
    free (x);
    free (y);
    free (z);
    */
    printf("\n\nExo 3: \n\n");

    float u[4] = {
        2, -3,
        -8, 4
    };

    float v[4] = {
        5, 2,
        11, 5
    };

    float res[4] = {
        0, 0,
        0, 0
    };

    
    /*
    afficheFloat ("u", u, 2);
    afficheFloat ("v", v, 2);

    strassen (u, v, res, 2);
    
    afficheFloat ("result", res, 2);
    */

    float a2[16] = {
        15, 34, 27, 2, 
        8, 23, 10, 1, 
        11, 17, 9, 4, 
        8, 65, 45, 7 
    };

    float b2[16] = {
        1, 2, 2.5, 2,
        0.7, 1, 1.5, 1,
        0.6, 1.1, 1.2, 0.8,
        10, 15, 7, 5
    };

    float p2[16];

    afficheFloat ("a", a2, n);
    afficheFloat ("b", b2, n);

    strassen(a2, b2, p2, n);

    afficheFloat("result", p2, n);
}
