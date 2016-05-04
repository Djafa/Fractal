#include <stdlib.h>
#include "./libfractal/fractal.h"
#include "myStack.h"

//Permet d'ajouter une fractal dans la liste
int push(node **list, struct fractal *f){
	node *newNode = (node*)malloc(sizeof(node));
	if(newNode == NULL)
		return -1;
	newNode->f=f;
	newNode->next=*list;
	*list=newNode;
	return 0;
}

//Retire une fractal de la liste pointée
struct fractal *pop(node **list){
	struct fractal *f = (*list)->f;
	node *save = *list;
	*list = (*list)->next;
	free(save);
	return f;
}
