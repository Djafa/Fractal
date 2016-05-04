#ifndef _MYSTACK_H
#define _MYSTACK_H

//Structure de la liste
typedef struct node {
	fractal *f;
	struct node *next;
} node;

int push(node **, fractal*);

fractal *pop(node **list);

#endif
