#ifndef __TRIE_H
#define __TRIE_H
/*-------------------------------------BIBLIOTHEQUES--------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "trie_hash.h"
#include "trie_matrix.h"

/*----------------------------------------CONSTANTES--------------------------*/

#define DEFAULT_VALUE -1
#define ALPHABET_SIZE UCHAR_MAX
#define TRIE_HEIGHT 8

/*-----------------------------------------FONCTIONS--------------------------*/

/**createTrie : crée un trie en prenant en entrée le nombre maximal de noeuds*/
Trie createTrie(int maxNode);

/**insertInTrie : insère un mot w dans un trie*/
void insertInTrie(Trie trie, unsigned char *w);

/**isInTrie : teste si un mot w est contenu dans un trie*/
int isInTrie(Trie trie, unsigned char *w);

/**printTrie : affiche les données dans la structure pointée par trie       */
void printTrie(Trie trie);

/**freeAndTerminate : libère l'espace alloué à la structure passée en paramètre
 *           renvoie une erreur */
void freeAndTerminate(Trie trie);

/**createPrefix : crée un trie contenant tous les préfixes d'un mot
 */
void createPrefix(unsigned char *w);

/**createSuffix : crée un trie contenant tous les suffixes d'un mot
 */
void createSuffix(unsigned char *w);

/**createFactor : crée un trie contenant tous les facteurs d'un mot
 */
void createFactor(unsigned char *w);

/*
 * Ajouter les méthodes getNode et createTransition
 */

#endif
