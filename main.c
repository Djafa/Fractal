#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./libfractal/fractal.h"
#include "./stack/myStack.h"
#include "main.h"
#include "./prodAndCons/prodAndCons.h"

int genAll;

 
int main (int argc, const char *argv[]) {
	printf("%d \n", argc);
	int start = 1;
	int nombreDeThread;
	int consoleInput = 0; 

	//Configuration de la génération
	if(argc > 2 && strcmp(argv[1],"-d") == 0){
		genAll = 1;
		start++;
	}
	else if(argc > 3 && strcmp(argv[2],"-d") == 0){
		genAll = 1;
		start++;
	}
	else 
		genAll = 0;

	//Configuration du nombre de threads
	if(argc > 2 && strcmp(argv[1],"--maxthreads") == 0){
		if(atoi(argv[2])>1){
			nombreDeThread = atoi(argv[2]);
			start += 2;
		}
	}
	else if(argc > 3 && strcmp(argv[2],"--maxthreads") == 0){
		if(atoi(argv[3])>1){
			nombreDeThread = atoi(argv[3]);
			start += 2;
		}
	}
	else 
		nombreDeThread = 4;

	//On check si il y a un - en argument
	for(int i = start; i<argc-1; i++){
		if(i>= start && strcmp(argv[i],"-") == 0)
			consoleInput = 1 ;
	}

	int nombreDeFichier = argc -1 - start - consoleInput;
	char *tab[nombreDeFichier];
	int j = 0;
	for(int i = start; j<nombreDeFichier; i++, j++){
		if(strcmp(argv[i],"-") == 0)
			i++;
		int size = strlen(argv[i])+1;
		tab[j] = (char *)malloc(sizeof(char)*(size));
		if(tab[j] == NULL)
			printf("Erreur malloc \n");
		strncpy(tab[j],argv[i], size);
	}

	int error = initStack(BUFFER, nombreDeThread);
	if(error !=0)
		return EXIT_FAILURE;

	//Création des threads
	pthread_t threadsP[nombreDeFichier];
	pthread_t threadsC[nombreDeThread]; 

	printf("Il y a %d threads de calcul \n", nombreDeThread);
	printf("Il y a %d fichiers \n", nombreDeFichier);

	//Création des threads de lecture (Producteurs)
	for(int i = 0;i<nombreDeFichier ; i++){
		error = pthread_create(&(threadsP[i]), NULL, &producteur,tab[i]);
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

	char ​*buffer = (char *​)malloc(sizeof(char)*65);
	while(consoleInput){
		unsigned int len;
		int read = getline(&buffer, &len, stdin);
		if(read != 0){
			printf("error \n");
			consoleInput = 0;
		}
		push(lineToFractal(buffer));
		printf("Entrez stop ou juste enter pour entrer une fractal\n");
		if(strcmp(buffer,'stop')
			consoleInput = 0
	}
	free(buffer);


	//Ce block permet d'attendre la fin de la lecture des fichiers
	for(int i = 0; i<nombreDeFichier ; i++){
		error = pthread_join(threadsP[i], NULL);
		if(error != 0)
			printf("%d \n", error);
		printf("Le producteur numéro %d à fini \n", i);
	}

	//On peut kill les consommateurs
	kill(nombreDeThread);

	//On attend la fin des consommateurs
	for(int i = 0; i<nombreDeThread ; i++){
		error = pthread_join(threadsC[i], NULL);
		if(error != 0)
			printf("%d \n", error);
		printf("Le consommateur numéro %d à fini \n", i);
	}

	//Destruction
	if(genAll == 0){
		printf("Et le gagnant est : %s \n", fractal_get_name(maxF));
		int sizeOfResult = strlen(argv[argc-1]);
		char *result = (char*)malloc(sizeof(char)*(sizeOfResult+5));
		strncpy(result,argv[argc-1],sizeOfResult+1);
		write_bitmap_sdl(maxF, strcat(result, ".bmp"));
		free(result);
	}
	destroy();
	pthread_mutex_destroy(&best);
	fractal_free(maxF);
	return EXIT_SUCCESS;
}

