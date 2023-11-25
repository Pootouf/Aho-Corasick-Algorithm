#ifndef __TRIE_HASH_H
#define __TRIE_HASH_H
/*-------------------------------------BIBLIOTHEQUES--------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*----------------------------------------CONSTANTES--------------------------*/
/**Taille du tableau = 4/3 * nombre de noeuds
 * Constante maintenant le taux de remplissage de la table de hachage inférieure
 * ou égale à 0.75*/
#define FILL_RATE (4/3)

/**Taille du trie*/
#define TRIE_HEIGHT 8
/*----------------------------------------STRUCTURES--------------------------*/

typedef struct _trie *Trie;

/*-----------------------------------------FONCTIONS--------------------------*/

/**createTrie : crée un trie en prenant en entrée le nombre maximal de noeuds*/
Trie createTrieHash(int maxNode);

/**insertInTrie : insère un mot w dans un trie*/
void insertInTrieHash(Trie trie, unsigned char *w);

/**isInTrie : teste si un mot w est contenu dans un trie*/
int isInTrieHash(Trie trie, unsigned char *w);

/**printTrie : affiche la table de hachage et les éléments de la structure
 *          présents dans trie */
void printTrieHash(Trie trie);

/**freeAndTerminate : libère l'espace alloué à la structure passée en paramètre
 *           renvoie une erreur */
void freeHash(Trie trie);


int getNodeFromCharacter(Trie trie, int beginNode, unsigned char c);

void createTransition(Trie trie, int startNode, int targetNode, unsigned char c);

#endif
