all: main 

main : main.o entreeSortieLC.o entreeSortieH.o biblioH.o biblioLC.o
	gcc -o main main.o biblioLC.o entreeSortieLC.o entreeSortieH.o biblioH.o

main.o: main.c biblioLC.h entreeSortieLC.h entreeSortieH.h biblioH.h
	gcc -c main.c

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h biblioLC.h 
	gcc -c entreeSortieLC.c
	
entreeSortieH.o : entreeSortieH.c entreeSortieH.h biblioH.h 
	gcc -c entreeSortieH.c
	
biblioLC.o : biblioLC.c biblioLC.h
	gcc -c biblioLC.c

biblioH.o : biblioH.c biblioH.h 
	gcc -c biblioH.c

clean:
	rm -f *.o main
