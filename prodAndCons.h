#ifndef _PRODANDCONS_H
#define _PRODANDCONS_H
extern struct fractal *maxF; //Contient la fractal qui possède la meilleur moyenne 
extern pthread_mutex_t best; 
extern const int global_generation;

void *producteur(void *);
struct fractal *lineToFractal(char *);
void *consommateur(void *);
double calculDeFractal(struct fractal *);

#endif
