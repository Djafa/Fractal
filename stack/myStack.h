#ifndef _MYSTACK_H
#define _MYSTACK_H

//Structure de la liste
typedef struct node {
	struct fractal *f;
	struct node *next;
} node;

//Permet l'initialisation du stack
int initStack(int, int);

//Ajouter une fractale dans le stack
int push(struct fractal*);

//Retirer une fractale du stack
struct fractal *pop();

//Permet de kill les threads
void kill(int);

void destroy();
#endif