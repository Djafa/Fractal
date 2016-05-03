main: main.o libfractal/fractal.o
	cd libfractal && make
	gcc -Wall -o main main.o libfractal/fractal.o libfractal/tools.o -lSDL -lpthread
	make clean

main.o: main.c libfractal/fractal.h
	gcc -Wall -c main.c -lpthread

clean:
	rm -rf *.o
	
.SILENT:
