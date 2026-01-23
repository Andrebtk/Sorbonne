all: hello_world.c hello_world2.c
	gcc -Wall -o hello_world hello_world.c
	gcc -Wall -o hello_world2 hello_world2.c

clean: 
	rm hello_world
	rm hello_world2
	rm image

hello_world: hello_world.c
	gcc -Wall -o hello_world hello_world.c

hello_world2: hello_world2.c
	gcc -Wall -o hello_world2 hello_world2.c

image: image.c
	gcc -Wall -o image image.c