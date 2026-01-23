all: test_ecosys ecosys

ecosys.o: ecosys.c
	gcc -c -o ecosys.o ecosys.c

main_ecosys.o: main_ecosys.c
	gcc -c -o main_ecosys.o main_ecosys.c

main_tests: main_tests.c
	gcc -c -p main_tests.o main_tests.c


test_ecosys: main_tests.o ecosys.o
	gcc -o test_ecosys main_tests.o ecosys.o

ecosys: main_ecosys.o ecosys.o
	gcc -o ecosys main_ecosys.o ecosys.o

clean:
	rm *.o 