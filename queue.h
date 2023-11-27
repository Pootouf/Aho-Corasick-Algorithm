#ifndef __AC_H
#define __AC_H
/*-------------------------------------BIBLIOTHEQUES--------------------------*/
#include <stdio.h>
#include <stdlib.h>
/*----------------------------------------CONSTANTES--------------------------*/

/*----------------------------------------STRUCTURES--------------------------*/

struct _queue {
	Cell *first;
	Cell *last;
}

typedef struct _queue *Queue;


/*-----------------------------------------FONCTIONS--------------------------*/
/**
 * create : crée une file.
 */
Queue create();

/**
 * add : enfile une valeur value dans la file queue.
 */
void add(int value, Queue queue);

/**
 * remove : défile la valeur en tête de queue et la renvoie.
 */
int remove(Queue queue);

/**
 * freeQueue : libère une file queue.
 */
void freeQueue(Queue queue);

#endif
