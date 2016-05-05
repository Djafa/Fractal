all: testFrac
	./testFrac

testFrac: testFrac.o ../libfractal/fractal.o
	gcc -Wall -lcunit -o testFrac ../libfractal/fractal.o testFrac.o -L$(HOME)/local/lib
	
testFrac.o: testFrac.c  ../libfractal/fractal.h ../main.c
	gcc -Wall -c testFrac.c -I$(HOME)/local/include
