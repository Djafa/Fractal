all: main
	make clean

main: main.o stack/myStack.o prodAndCons/prodAndCons.o
	cd libfractal && make
	gcc -Wall -g -o main main.o stack/myStack.o libfractal/libfractal.a prodAndCons/prodAndCons.o -lSDL -lpthread

main.o: main.c
	gcc -Wall -g -c main.c -lpthread
	
myStack.o: stack/myStack.c
	gcc -Wall -g -c stack/myStack.c -lpthread
	
prodAndCons.o: prodAndCons/prodAndCons.c
	gcc -Wall -g -c prodAndCons/prodAndCons.c -lpthread
	
test:
	cd libfractal && make
	cd Test && make
	make clean
	
lib:
	cd libfractal && make
	make clean
	
clean:
	rm -rf *.o libfractal/*.o libfractal/*.a Test/*.o stack/*.o prodAndCons/*.o
	
.SILENT:
