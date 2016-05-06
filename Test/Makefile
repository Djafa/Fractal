all: testFrac
	./testFrac

testFrac: testFrac.o ../prodAndCons/prodAndCons.o ../stack/myStack.o ../libfractal/tools.o ../libfractal/fractal.o
	gcc -Wall -lcunit -o testFrac ../libfractal/fractal.o testFrac.o ../prodAndCons/prodAndCons.o ../stack/myStack.o ../libfractal/tools.o -lSDL -L$(HOME)/local/lib -lpthread
	
testFrac.o: testFrac.c
	gcc -Wall -c testFrac.c -I$(HOME)/local/include
