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

/* function push
 * -------------
 * Ajout la fractal dans la liste
 * @params : pointeur vers une fractal
 * @return : 0 en cas de réussite, -1 en cas d'échec
 */
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
	//Début de la zone critique
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	newNode->next=head;
	head=newNode;
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	//Fin de la zone critique
	return 0;
}

/* function pop
 * ------------
 * On retire une fractal de la pile, si la fractal est null,
 * le thread courant sera tué.
 */
struct fractal *pop(){
	//Début de la zone critique
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	struct fractal *f = head->f;
	node *save = head;
	head = head->next;
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	//Fin de la zone critique
	//Si la fractal est null, on kill le thread
	if(f == NULL){
		printf("Fin du thread courant !\n");
		pthread_exit(NULL);
	}
	free(save);
	return f;
}

/* function initStack
 * ------------------
 * Cette fonction initialise la pile et les noeuds tueurs
 * @param : la taille du buffer et le nombre de thread de calcul
 * @return : 0 en cas de succès sinon -1
 */
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

/* function kill
 * -------------
 * Il faut lancer cette fonction, lorsque les producteurs ont fini,
 * les consommateurs seront donc tués lorsque le buffer sera vide.
 * @params : le nombre de consommateurs
 */
void kill(int maxThread){
	printf("Procédure de kill !\n");
	for(int i = 0; i<maxThread; i++){
		sem_post(&full);
	}
}

/* function destroy
 * ----------------
 * Destruction des mutexs et des sémaphores
 */
void destroy(){
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
}