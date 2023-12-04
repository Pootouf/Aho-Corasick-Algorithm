#ifndef __AC_H
#define __AC_H
#define _GNU_SOURCE
/*-------------------------------------BIBLIOTHEQUES--------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "Trie/trie.h"
#include "queue.h"
#include "stackTransition.h"

/*----------------------------------------CONSTANTES--------------------------*/
#define MAX_NODE 500000

#define MAX_LINE_NUMBER 999

#define MAX_LINE_LENGTH 999
/*-----------------------------------------FONCTIONS--------------------------*/

/**
 * initAhoCorasick : pré-traitement de l'algorithme Aho-Corasick en prenant 
 * 									une liste de mots wordList de longueur numberOfWord
 * 									que l'on ajoute dans le trie.
 */
Trie initAhoCorasick(unsigned char** wordList, int numberOfWord, int *sup, int* numberOfOccurrencies);

/**
 * complete : prend un trie et y ajoute les flèches de suppléance.
 */
void complete(Trie trie, int *sup, int* numberOfOccurrencies);

/**
 * ahoCorasick : exécute l'algorithme d'Aho-Corasick.
 */
void ahoCorasick(unsigned char**wordList, int numberOfWord, 
									char* text, int textSize);
#endif
