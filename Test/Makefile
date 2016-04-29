testFrac : testFrac.o
	gcc -Wall -lcunit -o Test testFrac.o -L$(HOME)/local/lib
	make clean
	
testFrac.o: testFrac.c  ../libfractal/fractal.h
	gcc -Wall -c testFrac.c -I$(HOME)/local/include

clean:
	rm -rf *.o
