#include <unistd.h>


int main() {

    long long N = 50000000;

    for(long long i=0; i < N; i++){
        getpid();
    }

}




/*
real    0m4,099s
user    0m1,219s
sys     0m2,879s
*/