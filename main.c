#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libfractal/fractal.h"

#define LENGTH_LINE 1000 // taille definie pour une ligne du fichier

int main (int argc, char *argv[]) {
	char line [LENGTH_LINE] = ""; // string servant a acceuillir la ligne lue
    FILE* file = NULL;
    file = fopen(argv[1], "r");
    
    if (file != NULL) {
		while (fgets(line, LENGTH_LINE, file) != NULL) {
			printf("%s", line);
		}
		fclose(file);
	}

	//Test des calculs
	const char *name = "projet";
	struct fractal *f = fractal_new(name, 800, 800, 0.5, 0.5);
	int w = fractal_get_width(f);
	int h = fractal_get_height(f);
	printf("Valeur de w : %d \nValeur de h : %d \n",w,h);

	//Calcule de chaque pixel
	for(int x =0; x<w; x++)
	{
		for(int y =0; y<h ;y++)
		{
			fractal_compute_value(f,x,y);
			printf("Valeur actuelle %d \n", fractal_get_value(f,x,y));
		}
	}
	//On écrit la fractale
	int err = write_bitmap_sdl(f, fractal_get_name(f));
	printf("%d \n",err);
    return EXIT_SUCCESS;
}