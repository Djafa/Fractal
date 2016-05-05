all: main
	make clean
	./main

main: main.o stack/myStack.o
	cd libfractal && make
	gcc -Wall -o main main.o stack/myStack.o libfractal/libfractal.a -lSDL -lpthread

main.o: main.c
	gcc -Wall -c main.c -lpthread
	
myStack.o: stack/myStack.c
	gcc -Wall -c stack/myStack.c -lpthread
	
test:
	cd Test && make
	make clean
	
lib:
	cd libfractal && make
	make clean
	
clean:
	rm -rf *.o libfractal/*.o libfractal/*.a Test/*.o stack/*.o
	
.SILENT:
