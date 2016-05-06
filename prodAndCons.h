#ifndef _PRODANDCONS_H
#define _PRODANDCONS_H

void *producteur(void *);
struct fractal *lineToFractal(char *);
void *consommateur(void *);
double calculDeFractal(struct fractal *);

#endif