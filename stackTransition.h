#ifndef TP3_STACKTRANSITION_H
#define TP3_STACKTRANSITION_H

/*-------------------------------------BIBLIOTHEQUES--------------------------*/

#include <stdio.h>
#include <stdlib.h>


/*----------------------------------------STRUCTURES--------------------------*/

typedef struct _transition *Transition;

typedef struct _stack *Stack;


/*-----------------------------------------FONCTIONS--------------------------*/

/**
 * createStack : renvoie une pile vide
 */
Stack createStack();

/**
 * push : ajoute à la pile stack une transition de startNode vers targetNode en character
 */
void push(Stack stack, int startNode, char character, int targetNode);

/**
 * pop : retire et renvoie la valeur du haut de la pile
 */
Transition pop(Stack stack);

/**
 * freeStack : libère la pile de la mémoire
 */
void freeStack(Stack stack);

/**
 * getStartNodeFromTransition : renvoie le noeud de départ d'une transition
 */
int getStartNodeFromTransition(Transition transition);

/**
 * getCharacterFromTransition : renvoie le caractère d'une transition
 */
char getCharacterFromTransition(Transition transition);

/**
 * getTargetNodeFromTransition : renvoie le noeud d'arrivée d'une transition
 */
int getTargetNodeFromTransition(Transition transition);

/**
 * freeTransition : libère la transition en mémoire
 */
void freeTransition(Transition transition);

#endif