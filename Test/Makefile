testFrac : testFrac.o ../libfractal/fractal.o
	gcc -Wall -lcunit -o testFrac ../libfractal/fractal.o testFrac.o -L$(HOME)/local/lib
	make clean
	./testFrac
	
testFrac.o: testFrac.c  ../libfractal/fractal.h
	gcc -Wall -c testFrac.c -I$(HOME)/local/include

clean:
	rm -rf *.o
