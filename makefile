all: viewer

viewer: viewer.o
	gcc -lSDL2 -lSDL2_image -o viewer viewer.o

viewer.o: viewer.c
	gcc -c viewer.c

clean:
	rm viewer viewer.o
