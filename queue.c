#include "queue.h"
/*----------------------------------------STRUCTURES--------------------------*/

typedef struct _cell *Cell;

struct _cell {
    Cell prev;
    Cell next;
    int value;
};

struct _queue {
    Cell first;
    Cell last;
};

/* ----------------------------------------------------------------------------
*                                DECLARATIONS FONCTIONS
*----------------------------------------------------------------------------*/

/**
 * createCell : crée une cellule en l'allouant avec comme valeur value.
 */
Cell createCell(int value);

/**
 * removeAll : enlève toutes les cellules de la file en les libérant.
 */
void removeAll(Queue queue);

/* ----------------------------------------------------------------------------
*                                FONCTIONS
*----------------------------------------------------------------------------*/

Queue create() {
	Queue queue = malloc(sizeof(struct _queue));
	if(queue == NULL) {
		fprintf(stderr, "Error while allocating\n");
		exit(EXIT_FAILURE);
	}
	queue->first = NULL;
	queue->last = NULL;
	return queue;
}

void addValue(int value, Queue queue) {
	if(queue == NULL) {
		fprintf(stderr, "Queue not valid, cannot add value\n");
		exit(EXIT_FAILURE);
	}
	Cell cell = createCell(value);
	Cell lastCell = queue->last;
	if(lastCell == NULL) {
		queue->first = cell;
		queue->last = cell;
	} else {
		cell->prev = lastCell;
		cell->next = NULL;
		lastCell->next = cell;
		queue->last = cell;
	}
}

int removeValue(Queue queue) {
	if(queue == NULL) {
		fprintf(stderr, "Queue not valid, cannot add value\n");
		exit(EXIT_FAILURE);
	}
	Cell firstCell = queue->first;
	if(firstCell != NULL) {
		Cell nextCell = firstCell->next;
		if(nextCell != NULL) {
			nextCell->prev = NULL;
		}
		queue->first = nextCell;
		int result = firstCell->value;
		free(firstCell);
		return result;
	} else {
		exit(EXIT_FAILURE);
	}
}

int isQueueEmpty(Queue queue) {
	return queue->first == NULL;
}

void freeQueue(Queue queue) {
	removeAll(queue);
	free(queue);
}


/* ----------------------------------------------------------------------------
*                                 OUTILS
*----------------------------------------------------------------------------*/

Cell createCell(int value) {
	Cell cell = malloc(sizeof(struct _cell));
	if(cell == NULL) {
		fprintf(stderr, "Error while allocating\n");
		exit(EXIT_FAILURE);
	}
	cell->value = value;
	return cell;
}

void removeAll(Queue queue) {
	if(queue == NULL) {
		fprintf(stderr, "Queue not valid, cannot add value\n");
		exit(EXIT_FAILURE);
	}
	while(queue->first != NULL) {
		removeValue(queue);
	}
}


