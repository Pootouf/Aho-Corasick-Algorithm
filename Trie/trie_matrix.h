#ifndef __TRIE_MATRIX_H
#define __TRIE_MATRIX_H
/*-------------------------------------BIBLIOTHEQUES--------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/*----------------------------------------CONSTANTES--------------------------*/

#define DEFAULT_VALUE -1
#define ALPHABET_SIZE UCHAR_MAX
#define TRIE_HEIGHT 8
/*----------------------------------------STRUCTURES--------------------------*/

typedef struct _trie *Trie;

/*-----------------------------------------FONCTIONS--------------------------*/

/**createTrie : crée un trie en prenant en entrée le nombre maximal de noeuds*/
Trie createTrieMatrix(int maxNode);

/**insertInTrie : insère un mot w dans un trie*/
void insertInTrieMatrix(Trie trie, unsigned char *w);

/**isInTrie : teste si un mot w est contenu dans un trie*/
int isInTrieMatrix(Trie trie, unsigned char *w);

/**printTrie : affiche les données dans la structure pointée par trie       */
void printTrieMatrix(Trie trie);

/**freeAndTerminate : libère l'espace alloué à la structure passée en paramètre
 *           renvoie une erreur */
void freeAndTerminateMatrix(Trie trie);

int getNodeFromCharacter(Trie trie, int beginNode, unsigned char c);

void createTransition(Trie trie, int startNode, int targetNode, unsigned char c);
#endif
