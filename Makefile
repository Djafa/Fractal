main: main.o libfractal/fractal.o
	make lib
	gcc -Wall -o main main.o libfractal/fractal.o libfractal/tools.o -lSDL -lpthread
	make clean

main.o: main.c libfractal/fractal.h
	gcc -Wall -c main.c -lpthread

clean:
	rm -rf *.o libfractal/*.o libfractal/*.a
	
test:
	cd Test && make
	
lib:
	@cd libfractal && make
	
.SILENT:
