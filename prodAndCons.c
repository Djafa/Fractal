#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libfractal/fractal.h"
#include "./stack/myStack.h"
#include "prodAndCons.h"


//Variable de classe
static double max_avg = 0; //Contient la meilleur moyenne
static struct fractal *maxF = NULL; //Contient la fractal qui possède la meilleur moyenne 
static pthread_mutex_t best; 
static const int global_generation;

/*****************************************************************************************
 *																						 *
 *                          		PRODUCTEUR											 *	
 *																						 *
 * **************************************************************************************/


//Cette fonction prend en argument le nom d'un fihcier, i
//elle va le lire et rajouter chaque ligne dans le buffer
void *producteur(void *params){
	const char *fichier = (char*)params;
	char *line = (char *)malloc(sizeof(char)*LENGTH_LINE); // string servant a acceuillir la ligne lue
	if(line == NULL)
		printf("Erreur malloc nom du fichier ! \n");
    FILE* file = NULL;
	printf("Le nom du ficher est : %s \n", fichier);
    file = fopen(fichier, "r");
    
    if (file != NULL) {
		while (fgets(line, LENGTH_LINE, file) != NULL) {
			//Lecture de la ligne
			if(*line != ' ' && *line != '#')// On ignore les lignes vides et les commentaires
				push(lineToFractal(line));
		}
		fclose(file);
	}
	free(line);
	free(params);
	pthread_exit(NULL);
}

struct fractal *lineToFractal(char *line){
	int w, h;
	double a, b;
	char *name = (char *)malloc(sizeof(char)*65);
	if(name == NULL)
		printf("Erreur lors de l'allocation du nom dans lineToFractal \n");
	sscanf(line, "%s %d %d %lf %lf", name, &w, &h, &a, &b);
	struct fractal *f =fractal_new(name, w, h, a, b);
  	free(name);
 	return f;
}



/*****************************************************************************************
 *																						 *
 *                          		CONSOMMATEUR										 *	
 *																						 *
 * **************************************************************************************/

void *consommateur(void *params){
	while(1){
		struct fractal *f= pop();
		double current_avg = calculDeFractal(f);
		//Critique
		pthread_mutex_lock(&best);
		if(current_avg > max_avg){
			printf("Nouveau maximum avec %lf ! \n", avg);
			free(maxF);
			max_avg = current_avg;
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
