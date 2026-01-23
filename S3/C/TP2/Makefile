#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -g -Wno-unused-parameter 
CC = gcc

PROGRAMS =   tests_ecosys ecosys main_test2

.PHONY:	all clean

all: $(PROGRAMS)

tests_ecosys: ecosys.o main_tests.o
	$(CC) -o $@ $(CFLAGS) $^


ecosys: ecosys.o main_ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

ecosys.o: ecosys.c
	gcc $(CFLAGS) -c ecosys.c

main_tests.o: main_tests.c ecosys.o
	gcc $(CFLAGS) -c main_tests.c

main_ecosys.o: main_ecosys.c ecosys.o
	gcc $(CFLAGS) -c main_ecosys.c

main_test2: main_test2.c ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -f *.o *~ $(PROGRAMS)
