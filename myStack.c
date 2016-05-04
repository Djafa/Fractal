#include <stdlib.h>
#include <stdio.h>
#include "./libfractal/fractal.h"
#include "myStack.h"
#include <semaphore.h>
#include <pthread.h>

pthread_mutex_t mutex; 
sem_t empty; 
sem_t full;

node *head = NULL;

//Permet d'ajouter une fractal dans la liste
int push(struct fractal *f){
	node *newNode = (node*)malloc(sizeof(node));
	if(newNode == NULL)
		return -1;
	newNode->f=f;
	//Critique
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	newNode->next=head;
	head=newNode;
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	printf("buffer + 1 \n");
	return 0;
}

//Retire une fractal de la liste pointée
struct fractal *pop(){
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	struct fractal *f = head->f;
	node *save = head;
	head = head->next;
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	//Kill thread
	if(f == NULL)
		pthread_exit(NULL);
	free(save);
	printf("buffer -1 \n");
	return f;
}

//Initialisation de la stack
void initStack(int taille, int maxThread){
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, taille);
	sem_init(&full, 0, 0);
	for(int i = 0; i<maxThread; i++){
		push(NULL);
	}
}

//Les consommateurs peuvent maintenant accèder aux nodes de kill
void kill(int maxThread){
	for(int i = 0; i<maxThread; i++){
		sem_post(&full);
	}
}
