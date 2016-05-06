#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./libfractal/fractal.h"
#include "main.h"
#include "prodAndCons.h"

#define LENGTH_LINE 1000 // taille definie pour une ligne du fichier
#define BUFFER 20



int main (int argc, const char *argv[]) {

	int size1 = strlen("./fract_inputs/01input_testavg.txt")+1;
	char *str1 = (char *)malloc(sizeof(char)*(size1));
	if (str1 == NULL)
		printf("Erreur malloc STR1\n");
	strncpy(str1,"./fract_inputs/01input_testavg.txt", size1);
	int size2 = strlen("./fract_inputs/02input_fewbig.txt")+1;
	char *str2 = (char *)malloc(sizeof(char)*(size2));
	if(str2 == NULL)
		printf("Erreur malloc STR2\n");
	strncpy(str2,"./fract_inputs/02input_fewbig.txt", size2);
	int size3 = strlen("./fract_inputs/03input_manysmall.txt")+1;
	char *str3 = (char *)malloc(sizeof(char)*(size3));
	if(str3 == NULL)
		printf("Erreur malloc STR3\n");
	strncpy(str3,"./fract_inputs/03input_manysmall.txt", size3);

	int error; 

	
	error = initStack(BUFFER, nombreDeThread);
	if(error !=0)
		return EXIT_FAILURE;
	int nbrFile = 3;
	pthread_t threadsP[nbrFile];
	pthread_t threadsC[nombreDeThread];
	char *arg [nbrFile];
	arg [0] = str1;
	arg [1] = str2;
	arg [2] = str3;   

	printf("Il y a %d threads de calcul \n", nombreDeThread);
	printf("Il y a %d fichiers \n", nbrFile);

	//Création des threads de lecture (Producteurs)
	for(int i = 0;i<nbrFile ; i++){
		error = pthread_create(&(threadsP[i]), NULL, &producteur,arg[i]);
		if(error != 0)
			printf("%d \n", error);
		printf("Création du thread de lecture numéro %d \n", i);
	}

	//Création des threads de calcul
	for(int i = 0; i<nombreDeThread; i++){
		error = pthread_create(&(threadsC[i]), NULL, &consommateur,NULL);
		if(error != 0)
			printf("%d \n", error);
		printf("Création du thread de consommation numéro %d \n", i);
	}

	//Ce block permet d'attendre la fin de la lecture des fichiers
	for(int i = 0; i<nbrFile ; i++){
		error = pthread_join(threadsP[i], NULL);
		if(error != 0)
			printf("%d \n", error);
		printf("Le producteur numéro %d à fini \n", i);
	}

	//free(str1);
	//free(str2);
	//free(str3);

	//Ouverture du double fond 
	kill(nombreDeThread);

	//Join consommateur
	for(int i = 0; i<nombreDeThread ; i++){
		error = pthread_join(threadsC[i], NULL);
		if(error != 0)
			printf("%d \n", error);
		printf("Le consommateur numéro %d à fini \n", i);
	}

	//Destruction

	printf("Et le gagnant est : %s \n", fractal_get_name(maxF));
	write_bitmap_sdl(maxF, fractal_get_name(maxF));

	pthread_mutex_destroy(&best);
	fractal_free(maxF);
	return EXIT_SUCCESS;
}

int lectureConsole(int argc, const char *argv){
	const int nombreDeThread;
	int start = 1;

	//Configuration de la génération pour chaque fractale
	if(argc > 2 && strmcp(argv[1],'-d')){
		global_generation = 1;
		start ++;
	}
	else if(argc > 3 && strmcp(argv[2],'-d')){
		global_generation = 1;
		start ++;
	}
	else
		global_generation = 0;

	//Configuration du nombre de threads
	if(argc > 2 && strmcp(argv[1], "--maxthreads") == 0){
		nombreDeThread = atoi(argv[2]);
		start++;
	}
	else if (argc > 3 && strmcp(argv[3], "--maxthreads") == 0){
		nombreDeThread = atoi(argv[3]);
		start++;
	}
	else 
		nombreDeThread = 4;
}

