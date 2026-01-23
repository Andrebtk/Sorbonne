#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>


void f (int L) {
    if(L > 0) {
        for(int j=0; j<3;j++){
            if(fork()==0){
                if(j !=1) {
                    printf("...");
                    exit(0);
                } else {
                    f(L-1);
                    printf("...");
                    exit(1);
                }
            }
        }
        for(int i=0; i<3; i++) {
            wait(NULL)
        }
    }
}

int main(int argc, char *argv[]) {
	f(5);
}




