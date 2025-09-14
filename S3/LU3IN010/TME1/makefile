main: tab.o maintab.c
	gcc -o main tab.o maintab.c


tab.o: tab.c tab.h
	gcc -c tab.c tab.h

clean:
	rm tab.o main