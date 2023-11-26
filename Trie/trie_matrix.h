#ifndef __TRIE_MATRIX_H
#define __TRIE_MATRIX_H
/*-------------------------------------BIBLIOTHEQUES--------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/*----------------------------------------CONSTANTES--------------------------*/

#define ALPHABET_SIZE UCHAR_MAX
#define TRIE_HEIGHT 8

#define NO_NODE (-1)
#define MIN_NODE_NUMBER 1
#define FIRST_NODE_NUMBER 1

#define NOT_FINAL '0'
#define FINAL '1'
/*----------------------------------------STRUCTURES--------------------------*/

typedef struct _trie *Trie;

/*-----------------------------------------FONCTIONS--------------------------*/

/**
 * createTrie : crée un Trie de taille maximum maxNode
 * @pre maxNode > MIN_NODE_NUMBER
 * @param maxNode
 * @return Trie
 */
Trie createTrie(int maxNode);

/**
 * insertInTrie : ajoute le mot word dans le langage reconnu par Trie
 *                ecrit une erreur sur la sortie erreur si trie est plein
 */
void insertInTrie(Trie trie, unsigned char *word);

/**
 * isInTrie : indique si le mot word est reconnu par trie
 */
int isInTrie(Trie trie, unsigned char *word);

/**
 * printTrie : affiche sur la sortie standard la description complète de trie
 */
void printTrie(Trie trie);

/**
 * freeTrie : libère l'espace alloué pour la construction de trie
 */
void freeTrie(Trie trie);

/**
 * getNodeFromCharacter : renvoie le noeud de trie correspondant à la transition de beginNode
 *                        vers ce noeud en letter
 */
int getNodeFromCharacter(Trie trie, int beginNode, unsigned char letter);

/**
 * createTransition : rajoute une transition dans trie allant de startNode vers
 *                    beginNode en letter
 */
void createTransition(Trie trie, int startNode, int targetNode, unsigned char letter);

/**
 * isTrieFull : indique si trie est plein
 */
int isTrieFull(Trie trie);

/**
 * isNodeInTrie : indique si node est un noeud de trie
 */
int isNodeInTrie(Trie trie, int node);

#endif