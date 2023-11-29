#ifndef __QUEUE_H
#define __QUEUE_H
/*-------------------------------------BIBLIOTHEQUES--------------------------*/
#include <stdio.h>
#include <stdlib.h>
/*----------------------------------------CONSTANTES--------------------------*/

/*----------------------------------------STRUCTURES--------------------------*/

typedef struct _queue *Queue;


/*-----------------------------------------FONCTIONS--------------------------*/
/**
 * create : crée une file.
 */
Queue create();

/**
 * add : enfile une valeur value dans la file queue.
 */
void addValue(int value, Queue queue);

/**
 * remove : défile la valeur en tête de queue et la renvoie.
 */
int removeValue(Queue queue);

/**
 * isQueueEmpty : indique si la file est vide.
 */
int isQueueEmpty(Queue queue);

/**
 * freeQueue : libère une file queue.
 */
void freeQueue(Queue queue);

#endif
