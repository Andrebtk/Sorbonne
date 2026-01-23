#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

int bitcommun (double x, double y) {
    return -log10 (fabs ((2*(x-y))/(x+y)));
}

int bitcommun_opt (double x, double y) {
    int res=0;

    uint64_t a = (uint64_t)(x * 10000000000);
    uint64_t b = (uint64_t)(y * 10000000000);

    uint64_t a2 = *((uint64_t*)&x);
    uint64_t b2 = *((uint64_t*)&y);
 
    for (int i = 63; i >= 0; i-=8) {
        if (( (a2 >> i) & 255) == ((b2 >> i) & 255)) {
            res++;
        } else {
            break;
        }
    }
    return res;
}



int main () {
    double x=1.41421356;
    double y=1.41427845;
    printf("noraml: %d \n", bitcommun(x,y));
    printf("opti: %d \n", bitcommun_opt(x,y));


    x=9.87452334;
    y=9.87901342;
    printf("noraml: %d \n", bitcommun(x,y));
    printf("opti: %d \n", bitcommun_opt(x,y));

    x=10.07452334;
    y=10.07901342;
    printf("noraml: %d \n", bitcommun(x,y));
    printf("opti: %d \n", bitcommun_opt(x,y));

    x=-2.69998756;
    y=-2.70001234;
    printf("noraml: %d \n", bitcommun(x,y));
    printf("opti: %d \n", bitcommun_opt(x,y));

}
