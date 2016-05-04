#ifndef _MYSTACK_H
#define _MYSTACK_H

//Structure de la liste
typedef struct node {
	struct fractal *f;
	struct node *next;
} node;
void initStack(int, int);

int push(struct fractal*);

void kill(int);

struct fractal *pop();

#endif
