#ifndef _PRODANDCONS_H
#define _PRODANDCONS_H

//Variables globales
extern struct fractal *maxF; //Fractal avec la meilleur moyenne
extern pthread_mutex_t best; 
extern const int global_generation; // 0 si il faut générer que la meilleur

/* function producteur
 * -------------------
 * La fonction va lire le fichier et placer les fractales dans le buffer,
 * les lignes commencent par un espace ou un # sont ignorées.
 * @params : prend comme agrument un pointeur vers le nom du fichier à lire.
 */
void *producteur(void *);

/* function lineToFractal
 * ----------------------
 * Cette fonction converti une ligne en fractal
 * @params : la ligne à convertir en fractal
 * @return : si il y a une erreur renvoi null, sinon la fractal
 */
struct fractal *lineToFractal(char *);

/* function consommateur 
 * ---------------------
 * On calcul les fractals dans le buffer, si sa moyenne est supérieur
 * on l'enregistre, sinon on l'a free
 */
void *consommateur(void *);

/* function calculDeFractal
 * ------------------------
 * On calcul la fractal et on renvoi ça moyenne 
 * @params : pointeur de la fractal à calculer
 * @return : la moyenne de la fractal
 */
double calculDeFractal(struct fractal *);

#endif
