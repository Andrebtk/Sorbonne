cpu: cpu_test.c cpu.o cpu.h parser.o memory.o
	gcc -g -o cpu -g cpu_test.c cpu.o hash.o memory.o parser.o

test_exo8: test_exo8.c cpu.o memory.o hash.o parser.o
	gcc -o test_exo8 test_exo8.c cpu.o memory.o hash.o parser.o

test_exo7: test_exo7.c cpu.o memory.o hash.o parser.o
	gcc -o test_exo7 test_exo7.c cpu.o memory.o hash.o parser.o

test_exo6: test_exo6.c cpu.o memory.o hash.o parser.o
	gcc -o test_exo6 test_exo6.c cpu.o memory.o hash.o parser.o

test_exo5: test_exo5.c cpu.o memory.o hash.o parser.o
	gcc -o test_exo5 test_exo5.c cpu.o memory.o hash.o parser.o

test_exo4: test_exo4.c cpu.o memory.o hash.o parser.o
	gcc -o test_exo4 test_exo4.c cpu.o memory.o hash.o parser.o

test_exo3: test_exo3.c parser.o parser.o
	gcc -o test_exo3 test_exo3.c parser.o hash.o

test_exo2: test_exo2.c memory.o hash.o parser.o
	gcc -o test_exo2 test_exo2.c memory.o hash.o parser.o

test_exo1: test_exo1.c hash.o
	gcc -o test_exo1 test_exo1.c hash.o

cpu.o: cpu.c cpu.h
	gcc -c cpu.c 

parser.o: parser.c parser.h hash.o
	gcc -c parser.c

memory.o: memory.c memory.h
	gcc -c memory.c

hash.o: hash.h hash.c
	gcc -c hash.c

clean:
	rm -f *.o main parser cpu test_exo[1-8]
