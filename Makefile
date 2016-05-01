main: main.o libfractal/fractal.o
	gcc -Wall -o main main.o libfractal/fractal.o libfractal/tools.o -lSDL
	make clean

main.o: main.c libfractal/fractal.h
	gcc -Wall -c main.c

clean:
	rm -rf *.o
