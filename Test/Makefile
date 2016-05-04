all: testFrac testConsoProd
	./testFrac

testFrac: testFrac.o ../libfractal/fractal.o
	gcc -Wall -lcunit -o testFrac ../libfractal/fractal.o testFrac.o -L$(HOME)/local/lib
	
testFrac.o: testFrac.c  ../libfractal/fractal.h
	gcc -Wall -c testFrac.c -I$(HOME)/local/include
	
testConsoProd: testConsoProd.o
	gcc -Wall -lcunit -o testConsoProd ../libfractal/fractal.o testConsoProd.o -L$(HOME)/local/lib
	
testConsoProd.o: testConsoProd.c ../main.c ../libfractal/fractal.h
	gcc -Wall -c testConsoProd.c -I$(HOME)/local/include
