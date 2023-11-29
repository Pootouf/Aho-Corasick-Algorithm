#ifndef __AC_H
#define __AC_H

/*-------------------------------------BIBLIOTHEQUES--------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "Trie/trie.h"
#include "queue.h"

/*----------------------------------------CONSTANTES--------------------------*/
#define MAX_NODE 999

/*-----------------------------------------FONCTIONS--------------------------*/

Trie initAhoCorasick(unsigned char** wordList, int numberOfWord);

void complete(Trie trie);

void ahoCorasick(unsigned char**worldList, int numberOfWord, char* text, int textSize);

#endif
