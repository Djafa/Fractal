#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "./libfractal/fractal.h"

#define LENGTH_LINE 1000 // taille definie pour une ligne du fichier

//Cette fonction prend en argument le nom d'un fihcier, i
//elle va le lire et rajouter chaque ligne dans le buffer
void *lecture(void *params){
	const char *fichier = (char*)params;
	char line [LENGTH_LINE] = ""; // string servant a acceuillir la ligne lue
    FILE* file = NULL;
    file = fopen(fichier, "r");
    
    if (file != NULL) {
		while (fgets(line, LENGTH_LINE, file) != NULL) {
			printf("%s", line);
		}
		fclose(file);
	}
	free(params);
	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
	char *str1 = (char *)malloc(sizeof(char)*(strlen("./fract_inputs/01input_testavg.txt")+1));
	strcpy(str1,"./fract_inputs/01input_testavg.txt");
	char *str2 = (char *)malloc(sizeof(char)*(strlen("./fract_inputs/02input_fewbig.txt")+1));
	strcpy(str2,"./fract_inputs/02input_fewbig.txt");
	char *str3 = (char *)malloc(sizeof(char)*(strlen("./fract_inputs/03input_manysmall.txt")+1));
	strcpy(str3,"./fract_inputs/03input_manysmall.txt");
	

	//Les threads
	int err;
	pthread_t first; 
	pthread_t second;
	pthread_t third ; 

	err = pthread_create(&first, NULL, &lecture, str1);
	if(err != 0)
		printf("%d \n", err);
	err = pthread_create(&second, NULL, &lecture, str2);
	if(err != 0)
		printf("%d \n", err);
	err = pthread_create(&third, NULL, &lecture, str3);
	if(err != 0)
		printf("%d \n", err);

	err = pthread_join(first, NULL);
	if(err != 0)
		printf("%d \n", err);
	err = pthread_join(second, NULL);
	if(err != 0)
		printf("%d \n", err);
	err = pthread_join(third, NULL);
	if(err != 0)
		printf("%d \n", err);





	//Test des calculs
	const char *name = "projet1";
	struct fractal *f = fractal_new(name, 800, 800, 0.5, 0.5);
	int w = fractal_get_width(f);
	int h = fractal_get_height(f);

	//Calcule de chaque pixel
	for(int x =0; x<w; x++){
		for(int y =0; y<h ;y++){
			fractal_compute_value(f,x,y);
		}
	}

	//On écrit la fractale
	write_bitmap_sdl(f, fractal_get_name(f));
    return EXIT_SUCCESS;
}

