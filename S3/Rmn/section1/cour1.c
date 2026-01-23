#include <stdio.h>
#include <stdint.h>

unsigned int position(unsigned int n, unsigned int i)
{
	return (n >> i) & 1;
}

int compare(uint16_t n, uint16_t m)
{
	int i = 15, b1, b2;
	do    
	{ 
		b1 = (n << i);
		b2 = (m << i);
		i-=1;

	} while((b1 == b2) && ( i >= 0 ));

	return (b1 > b2) && (i != -1);
}

int pgcd (unsigned int  a, unsigned int  b) {
	unsigned int  u = a;
	unsigned int  v = b;

	while (v > 0) {
		if (v > u) {
			int t = v;
			v = u;
			u = t;
		}
		u-=v;
	}
	return u;
}

void euclideEtendu (int a, int b) {
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

	printf("%d * %d + %d * %d = %d = pgcd(%d,%d) \n", u1, a, u2, b, u3, a, b );

}


int main () {
	//printf("%d \n",compare(28,90));

	printf(" %d \n",pgcd(36,24));
	euclideEtendu (26433, 7865);
}

