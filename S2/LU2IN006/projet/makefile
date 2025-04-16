cpu: cpu_test.c cpu.o cpu.h parser.o memory.o
	gcc -o cpu cpu_test.c cpu.o hash.o memory.o parser.o

cpu.o: cpu.c cpu.h
	gcc -c cpu.c 

parser: parserTest.c parser.o parser.h
	gcc -o parser parserTest.c parser.o hash.o

parser.o: parser.c parser.h hash.o
	gcc -c parser.c

memory: test_mem.c memory.o hash.o parser.o
	gcc -o mem test_mem.c memory.o hash.o parser.o

memory.o: memory.c memory.h
	gcc -c memory.c

hash.o: hash.h hash.c
	gcc -c hash.c

clean:
	rm -f *.o main mem parser cpu
