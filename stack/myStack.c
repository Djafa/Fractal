#include <stdlib.h>
#include <stdio.h>
#include "../libfractal/fractal.h"
#include "myStack.h"
#include <semaphore.h>
#include <pthread.h>

static pthread_mutex_t mutex; 
static sem_t empty; 
static sem_t full;
static node *head = NULL;

//Ajoute la fractal dans le stack 
//Renvoi -1, si il y a une erreur sinon 0
int push(struct fractal *f){
	node *newNode = (node*)malloc(sizeof(node));
	if(newNode == NULL){
		printf("Erreur lors du push d'un élément -> malloc \n");
		return -1;
	}
	if(f == NULL){
		printf("Erreur dans push, la fractal est null \n");
		return -1;
	}
	newNode->f=f;
	//Critique
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	newNode->next=head;
	head=newNode;
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	//Critique fin
	return 0;
}

//Retire une fractal de la liste pointée
//Si la fractal est null, on kill le thread
struct fractal *pop(){
	//Section critique
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	struct fractal *f = head->f;
	node *save = head;
	if(head == NULL)
		printf("Head est NULL\n");
	head = head->next;
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	//Si la fractal est null, on kill le thread
	if(f == NULL){
		printf("THREAD EXIT \n");
		pthread_exit(NULL);
	}
	free(save);
	return f;
}

//Initialisation de la stack
//Renvoi -1, si il y a une erreur, sinon 0
int initStack(int taille, int maxThread){
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, taille);
	sem_init(&full, 0, 0);
	for(int i = 0; i<maxThread; i++){
		node *newNode = (node*)malloc(sizeof(node));
		if(newNode == NULL){
			printf("Erreur lors de malloc dans l'Initialisation");
			return -1;
		}
		newNode->f=NULL;
		//Critique
		pthread_mutex_lock(&mutex);
		newNode->next=head;
		head=newNode;
		pthread_mutex_unlock(&mutex);
	}
	return 0;
}

//Les consommateurs peuvent maintenant accèder aux nodes de kill
void kill(int maxThread){
	printf("Procédure de kill !\n");
	for(int i = 0; i<maxThread; i++){
		sem_post(&full);
	}
}

void destroy(){
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
}
