all: main

main: main.o myStack.o
	cd libfractal && make
	gcc -Wall -o main main.o myStack.o libfractal/libfractal.a -lSDL -lpthread
	make clean

main.o: main.c
	gcc -Wall -c main.c -lpthread
	
myStack.o: myStack.c
	gcc -Wall -c myStack.c -lpthread
	
test:
	cd Test && make
	make clean
	
lib:
	cd libfractal && make
	make clean
	
clean:
	rm -rf *.o libfractal/*.o libfractal/*.a Test/*.o
	
.SILENT:
