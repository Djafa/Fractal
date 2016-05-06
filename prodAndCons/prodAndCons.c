#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libfractal/fractal.h"
#include "../stack/myStack.h"
#include "prodAndCons.h"
#include "../main.h"

#define LENGTH_LINE 1000

//Variable de classe
static double max_avg = 0; //Contient la meilleur moyenne
struct fractal *maxF = NULL;
pthread_mutex_t best;

/******************** Méthode pour les producteurs ********************/

/* function producteur
 * -------------------
 * La fonction va lire le fichier et placer les fractales dans le buffer,
 * les lignes commencent par un espace ou un # sont ignorées.
 * @params : prend comme agrument un pointeur vers le nom du fichier à lire.
 */
void *producteur(void *params){
	const char *fichier = (char*)params;
	char *line = (char *)malloc(sizeof(char)*LENGTH_LINE); 
	if(line == NULL)
		printf("Erreur malloc nom du fichier ! \n");
    FILE* file = NULL;
    file = fopen(fichier, "r");
    
    if (file != NULL) {
		while (fgets(line, LENGTH_LINE, file) != NULL) {
			//Si la ligne commence par un espace ou un #, elle sera ignorée
			if(*line != ' ' && *line != '#')
				push(lineToFractal(line));
		}
		fclose(file);
	}
	free(line);
	free(params);
	pthread_exit(NULL);
}

/* function lineToFractal
 * ----------------------
 * Cette fonction converti une ligne en fractal
 * @params : la ligne à convertir en fractal
 * @return : si il y a une erreur renvoi null, sinon la fractal
 */
struct fractal *lineToFractal(char *line){
	int w, h;
	double a, b;
	char *name = (char *)malloc(sizeof(char)*65);
	if(name == NULL)
		printf("Erreur lors de l'allocation du nom dans lineToFractal \n");
	int err = sscanf(line, "%s %d %d %lf %lf", name, &w, &h, &a, &b);
	if(err != 5)
		return NULL;
	struct fractal *f =fractal_new(name, w, h, a, b);
  	free(name);
 	return f;
}

/******************* Méthode pour les consommateurs ********************/

/* function consommateur 
 * ---------------------
 * On calcul les fractals dans le buffer, si sa moyenne est supérieur
 * on l'enregistre, sinon on l'a free
 */
void *consommateur(void *params){
	while(1){
		struct fractal *f= pop();
		double current_avg = calculDeFractal(f);
		//Critique
		if(genAll == 0){
			pthread_mutex_lock(&best);
			if(current_avg > max_avg){
				printf("Nouveau maximum avec %lf ! \n", current_avg);
				free(maxF);
				max_avg = current_avg;
				maxF = f;
			}
			else
				fractal_free(f);
			pthread_mutex_unlock(&best);
		}
		else {
			int sizeOfResult = 65;
			char *result = (char*)malloc(sizeof(char)*(sizeOfResult+4));
			strncpy(result,fractal_get_name(f),65);
			write_bitmap_sdl(maxF, strcat(result,".bmp"));
			free(result);
		}

	}
}

/* function calculDeFractal
 * ------------------------
 * On calcul la fractal et on renvoi ça moyenne 
 * @params : pointeur de la fractal à calculer
 * @return : la moyenne de la fractal
 */
double calculDeFractal(struct fractal *f){
	double sum = 0;
	int w = fractal_get_width(f);
	int h = fractal_get_height(f);
	for(int x =0; x<w; x++){
		for(int y =0; y<h ;y++){
			fractal_compute_value(f,x,y);
			sum += fractal_get_value(f,x,y);
		}
	}
	return sum/(w*h);//Calcul de la moyenne 
}
