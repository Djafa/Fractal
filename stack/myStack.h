#ifndef _MYSTACK_H
#define _MYSTACK_H

//Structure de la liste
typedef struct node {
	struct fractal *f;
	struct node *next;
} node;

/* function push
 * -------------
 * Ajout la fractal dans la liste
 * @params : pointeur vers une fractal
 * @return : 0 en cas de réussite, -1 en cas d'échec
 */
int push(struct fractal*);

/* function pop
 * ------------
 * On retire une fractal de la pile, si la fractal est null,
 * le thread courant sera tué.
 */
struct fractal *pop();

/* function initStack
 * ------------------
 * Cette fonction initialise la pile et les noeuds tueurs
 * @param : la taille du buffer et le nombre de thread de calcul
 * @return : 0 en cas de succès sinon -1
 */
int initStack(int, int);

/* function kill
 * -------------
 * Il faut lancer cette fonction, lorsque les producteurs ont fini,
 * les consommateurs seront donc tués lorsque le buffer sera vide.
 * @params : le nombre de consommateurs
 */
void kill(int);

/* function destroy
 * ----------------
 * Destruction des mutexs et des sémaphores
 */
void destroy();
#endif