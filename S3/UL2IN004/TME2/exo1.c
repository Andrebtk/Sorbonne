#include <stdio.h>

int main() {
    char t1_min = 0;
    char t1_max = 0;
    
    short t2_min = 0;
    short t2_max = 0;
    
    int t3_min = 0;
    int t3_max = 0;

    unsigned char t4_min = 0;
    unsigned char t4_max = 0;

    unsigned int t5_min = 0;
    unsigned int t5_max = 0;


    while(t1_min >= 0) {
        t1_max=t1_min;
        t1_min++;
    }

    while(t2_min >= 0) {
        t2_max=t2_min;
        t2_min++;
    }

    while(t3_min >= 0) {
        t3_max=t3_min;
        t3_min++;
    }

    t4_min++;
    while(t4_min > 0) {
        t4_max=t4_min;
        t4_min++;
    }

    t5_max++;
    while(t5_max >= t5_min) {
        t5_min=t5_max;
        t5_max++;
    }

    printf("char min: %d, max: %d\n", t1_min, t1_max);
    printf("short min: %d, max: %d\n", t2_min, t2_max);
    printf("int min: %d, max: %d\n", t3_min, t3_max);
    
    printf("unsigned char min: %d, max: %d\n", t4_min, t4_max);
    printf("unsigned int min: %d, max: %d\n", t5_min, t5_max);
}