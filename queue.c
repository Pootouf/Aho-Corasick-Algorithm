#include "queue.h"
/*----------------------------------------STRUCTURES--------------------------*/

struct _cell {
	Cell *prev;
	Cell *next;
	int value;
}

typedef struct _cell *Cell;

/* ----------------------------------------------------------------------------
*                                DECLARATIONS FONCTIONS
*----------------------------------------------------------------------------*/

Cell createCell(int value);

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

void add(int value, Queue queue) {
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


/* ----------------------------------------------------------------------------
*                                 OUTILS
*----------------------------------------------------------------------------*/

Cell createCell(int value) {
	Cell cell = malloc(sizeof(struct _cell));
	if(cell == NULL) {
		fprintf(stderr, "Error while allocating\n");
		exit(EXIT_FAILURE);
	}
	cell.value = value;
	return cell;
}
