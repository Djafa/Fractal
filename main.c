#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "myStack.h"
#include "./libfractal/fractal.h"

#define LENGTH_LINE 1000 // taille definie pour une ligne du fichier


int main (int argc, char *argv[]) {
	char *str1 = (char *)malloc(sizeof(char)*(strlen("./fract_inputs/01input_testavg.txt")+1));
	strcpy(str1,"./fract_inputs/01input_testavg.txt");
	char *str2 = (char *)malloc(sizeof(char)*(strlen("./fract_inputs/02input_fewbig.txt")+1));
	strcpy(str2,"./fract_inputs/02input_fewbig.txt");
	/*char *str3 = (char *)malloc(sizeof(char)*(strlen("./fract_inputs/03input_manysmall.txt")+1));
	strcpy(str3,"./fract_inputs/03input_manysmall.txt");*/

	int nbrFile = 2;
	int err;
	pthread_t threads[nbrFile];
	char *arg [2];
	arg [0] = str1;
	arg [1] = str2;
	//arg [2] = str3;

	printf("Il y a %d threads \n", nbrFile);

	//Création des threads de lecture (Producteurs)
	for(int i = 0;i<nbrFile ; i++){
		err = pthread_create(&(threads[i]), NULL, &lecture,arg[i]);
		if(err != 0)
			printf("%d \n", err);
		printf("Création du thread de lecture numéro %d \n", i);
	}
	

	//Ce block permet d'attendre la fin de la lecture des fichiers
	for(int i = 0; i<nbrFile ; i++){
		err = pthread_join(threads[i], NULL);
		if(err != 0)
			printf("%d \n", err);
		printf("Le thread numéro %d à fini \n", i);
	}
    return EXIT_SUCCESS;
}

/*****************************************************************************************
 *																						 *
 *                          		PRODUCTEUR											 *	
 *																						 *
 * **************************************************************************************/

//Cette fonction prend en argument le nom d'un fihcier, i
//elle va le lire et rajouter chaque ligne dans le buffer
void *lecture(void *params){
	const char *fichier = (char*)params;
	char line [LENGTH_LINE] = ""; // string servant a acceuillir la ligne lue
    FILE* file = NULL;
    file = fopen(fichier, "r");
    
    if (file != NULL) {
		while (fgets(line, LENGTH_LINE, file) != NULL) {
			//Lecture de la ligne	
		}
		fclose(file);
	}
	free(params);
	pthread_exit(NULL);
}

struct fractal *lineToFractal(char line){
	char *token = strtok(line, " ");
	int count = 1;
	//Valeur à mettre dans la structure
	char *name;
	int w;
	int h;
	double a;
	double b;
	while( token != NULL){
		printf( " %s\n", token );
		if(count == 1){
			name = (char *)malloc(sizeof(char)*(strlen(token)+1));
			if(name == NULL)
				return NULL;
			strcpy(name,token);
		}
		else if (count == 2)
			w = atoi(token);
		else if (count == 3)
			h = atoi(token);
		else if (count == 4)
			a = atof(token);
		else if(count == 5)
			b = atof(token);
		count ++;
		token = strtok(NULL," ");
	}
	struct fractal *f =fractal_new(name, w, h, a, b);
	free(name);
	return f;
}



/*****************************************************************************************
 *																						 *
 *                          		CONSOMMATEUR										 *	
 *																						 *
 * **************************************************************************************/

//Calcul la fractal et renvoi la moyenne 
double calculDeFractal(struct fractal *f){
	double avg = 0;
	int w = fractal_get_width(f);
	int h = fractal_get_height(f);
	for(int x =0; x<w; x++){
		for(int y =0; y<h ;y++){
			fractal_compute_value(f,x,y);
			avg += fractal_get_value(f,x,y);
		}
	}
	return avg/(w*h);
}
