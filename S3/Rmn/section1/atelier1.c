#include <stdio.h>
#include <stdint.h>

void representation (int a) {
    for (int i = 31; i>=0; i--) {
        int bit = (a >> i) & 1;
        printf ("%d", bit);

        if (i%4 == 0) {
            printf (" ");
        }
    }
    printf ("\n");
}

unsigned int factoriel (unsigned int nombre) {
    unsigned int res = 1;
    for (int i = 1; i<=nombre; i++) {
        res *= i;
    }
    return res;
}

void pgcd_bezout (int a, int b, int *u, int *v, int *pgcd) {
	int u1 = 1;
	int u2 = 0;
	int u3 = a;

	int v1 = 0;
	int v2 = 1;
	int v3 = b;

	while (v3 != 0) {
		int q = u3/v3;
		int t1 = u1 - q * v1;
		int t2 = u2 - q * v2;
		int t3 = u3 - q * v3;

		u1 = v1;
		u2 = v2;
		u3 = v3;

		v1 = t1;
		v2 = t2;
		v3 = t3;  
	}
	*u = u1;
	*v = u2;
	*pgcd = u3;
	//printf ("%d * %d + %d * %d = %d = pgcd(a,b) \n", u1, a, u2, b, u3);

}

int reste_chinois (int a[], int m[], int n) {
	int M = m[0];
	int x = a[0];

	int u = 0;
	int v = 0;
	int pgcd = 0;

	for (int i = 0; i<n; i++) {
		int mi = m[i];
		int ai = a[i];

		pgcd_bezout (mi, M, &u, &v, &pgcd);
		if ((u*mi + v*M) == 1) {
			x = u * mi * x + v * M * ai;
			M = mi * M;
			x = x % M;
		}
	}
	//if (x<0) return -x;
	return x;
}


int main () {
    /*
    representation (2957);
    // 0000 0000 0000 0000 0000 1011 1000 1101 
    
    representation (-2957);
    // 1111 1111 1111 1111 1111 0100 0111 0011 

    On obtient la négation d'un entier signé en inversant chaque bit de sa représentation positive
    */

    /*
    for (int i = 1; i <= 20; i++) {
        representation (factoriel (i));
    }
    // On observe qu'à partir d'un certain nombre la représentation sur 32 bits n'est plus suffisante par conséquent leur representation sur 32 est faussée 
    */

	/*
	// U va correspondre au nombre de litre du récipient A et V va correspondre au nombre de litre du récipient B et le plus petit volume d'eau possible en utilisant A et B c'est le PGCD(A,B)

 	pgcd_bezout (26433, 7865);
	*/

	/*
	18 Joueur
	x = 3 mod 17
	x = 4 mod 11
	x = 5 mod 6
	*/

	int m[3] = {17, 11, 6};
	int a[3] = {3, 4, 5};

	//int m[4] = {2, 3, 5, 7};
	//int a[4] = {1, 2, 4, 0};
	printf("%d \n", reste_chinois (a, m, 4));



}