#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "myStack.h"
#include "main.h"
#include "./libfractal/fractal.h"

#define LENGTH_LINE 1000 // taille definie pour une ligne du fichier

//Variable de classe
double max = 0;
struct fractal *maxF = NULL;
pthread_mutex_t best; 

int main (int argc, char *argv[]) {
	
	char *str1 = (char *)malloc(sizeof(char)*(strlen("./fract_inputs/01input_testavg.txt")+1));
	strcpy(str1,"./fract_inputs/01input_testavg.txt");
	char *str2 = (char *)malloc(sizeof(char)*(strlen("./fract_inputs/02input_fewbig.txt")+1));
	strcpy(str2,"./fract_inputs/02input_fewbig.txt");
	/*char *str3 = (char *)malloc(sizeof(char)*(strlen("./fract_inputs/03input_manysmall.txt")+1));
	strcpy(str3,"./fract_inputs/03input_manysmall.txt");*/

	int nombreDeThread = 4;
	initStack(8, nombreDeThread);
	int nbrFile = 2;
	int err;
	pthread_t threadsP[nbrFile];
	pthread_t threadsC[nombreDeThread];
	char *arg [2];
	arg [0] = str1;
	arg [1] = str2;
	//arg [2] = str3;

	printf("Il y a %d threads \n", nbrFile);

	//Création des threads de lecture (Producteurs)
	for(int i = 0;i<nbrFile ; i++){
		err = pthread_create(&(threadsP[i]), NULL, &producteur,arg[i]);
		if(err != 0)
			printf("%d \n", err);
		printf("Création du thread de lecture numéro %d \n", i);
	}

	for(int i = 0; i<nombreDeThread; i++){
		err = pthread_create(&(threadsC[i]), NULL, &consommateur,NULL);
		if(err != 0)
			printf("%d \n", err);
		printf("Création du thread de consommation numéro %d \n", i);
	}

	//Ce block permet d'attendre la fin de la lecture des fichiers
	for(int i = 0; i<nbrFile ; i++){
		err = pthread_join(threadsP[i], NULL);
		if(err != 0)
			printf("%d \n", err);
		printf("Le producteur numéro %d à fini \n", i);
	}

	//Ouverture du double fond 
	kill(nombreDeThread);

	//Join consommateur
	for(int i = 0; i<nombreDeThread ; i++){
		err = pthread_join(threadsC[i], NULL);
		if(err != 0)
			printf("%d \n", err);
		printf("Le consommateur numéro %d à fini \n", i);
	}

	write_bitmap_sdl(maxF, fractal_get_name(maxF));

	return EXIT_SUCCESS;
}

/*****************************************************************************************
 *																						 *
 *                          		PRODUCTEUR											 *	
 *																						 *
 * **************************************************************************************/

//Cette fonction prend en argument le nom d'un fihcier, i
//elle va le lire et rajouter chaque ligne dans le buffer
void *producteur(void *params){
	const char *fichier = (char*)params;
	char line [LENGTH_LINE] = ""; // string servant a acceuillir la ligne lue
    FILE* file = NULL;
    file = fopen(fichier, "r");
    
    if (file != NULL) {
		while (fgets(line, LENGTH_LINE, file) != NULL) {
			//Lecture de la ligne	
			push(lineToFractal(line));
		}
		fclose(file);
	}
	free(params);
	pthread_exit(NULL);
}

struct fractal *lineToFractal(char *line){
	const char *delim = " ";
 	char *token = strtok(line, delim);
 	if(token == NULL)
 		return NULL;
 	char *name  = (char *)malloc(sizeof(char)*(strlen(token)+1));
 	strcpy(name, token);
 	int w = atoi(strtok(NULL, delim));
 	int h = atoi(strtok(NULL, delim));
 	double a = atof(strtok(NULL, delim));
 	double b = atof(strtok(NULL, delim));
 	printf("Création de la fractale");
 	struct fractal *f =fractal_new(name, w, h, a, b);
  	free(name);
 	printf("on return");
 	return f;
}



/*****************************************************************************************
 *																						 *
 *                          		CONSOMMATEUR										 *	
 *																						 *
 * **************************************************************************************/

void *consommateur(void *params){
	while(true){
		struct fractal *f= pop();
		double avg = calculDeFractal(f);
		//Critique
		pthread_mutex_lock(&best);
		if(avg > max){
			max = avg;
			maxF = f;
		}
		else
			fractal_free(f);
		pthread_mutex_unlock(&best);
	}
}

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
