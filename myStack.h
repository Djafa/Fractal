#ifndef _MYSTACK_H
#define _MYSTACK_H

//Structure de la liste
typedef struct node {
	struct fractal *f;
	struct node *next;
} node;
void initStack(int);

int push(node **, struct fractal*);

struct fractal *pop(node **list);

#endif
