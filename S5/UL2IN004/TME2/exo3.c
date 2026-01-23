#include <stdio.h>

float u[128];

int main() {
    u[0] = 1;
    for(int n=1; n<128; n++) {
        u[n] = 2*u[n-1]+1;
        printf("n:%d -> %f\n", n, u[n]);
    }


}