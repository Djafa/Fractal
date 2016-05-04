#include <stdlib.h>
#include "./libfractal/fractal.h"
#include "myStack.h"
#include <semaphore.h>
#include <pthread.h>

pthread_mutex_t mutex; 
sem_t empty; 
sem_t full;


void initStack(int taille){
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, taille);
	sem_init(&full, 0, 0);
}

//Permet d'ajouter une fractal dans la liste
int push(node **list, struct fractal *f){
	node *newNode = (node*)malloc(sizeof(node));
	if(newNode == NULL)
		return -1;
	newNode->f=f;
	//Critique
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	newNode->next=*list;
	*list=newNode;
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	return 0;
}

//Retire une fractal de la liste pointée
struct fractal *pop(node **list){
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	struct fractal *f = (*list)->f;
	node *save = *list;
	*list = (*list)->next;
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	free(save);
	return f;
}
