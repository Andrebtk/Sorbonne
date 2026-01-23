#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int max = atoi(argv[1]);
    int num;
    for(int i=2; i<argc; i++){
        num = atoi(argv[i]);
        if(num > max) {
            max = num;
        }
    }

    printf("max: %d\n", max);
}