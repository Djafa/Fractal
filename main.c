#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libfractal/fractal.h"

#define LENGTH_LINE 1000 // taille definie pour une ligne du fichier

int main (int argc, char *argv[]) {
	char line [LENGTH_LINE] = ""; // string servant a acceuillir la ligne lue
    FILE* file = NULL;
    file = fopen(argv[1], "r");
    
    if (file != NULL) {
		while (fgets(line, LENGTH_LINE, file) != NULL) {
			printf("%s", line);
		}
	}
	
	
    return EXIT_SUCCESS;
}
