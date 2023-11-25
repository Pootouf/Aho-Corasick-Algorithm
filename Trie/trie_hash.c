#include "trie_hash.h"

/*----------------------------------------STRUCTURES--------------------------*/

struct _list {
int startNode, /* etat de depart de la transition */
targetNode; /* cible de la transition */
unsigned char letter; /* etiquette de la transition */
struct _list *next; /* maillon suivant */
};

typedef struct _list *List;

struct _trie {
int maxNode; /* Nombre maximal de noeuds du trie */
int nextNode; /* Indice du prochain noeud disponible */
List *transition; /* listes d’adjacence */
char *finite; /* etats terminaux */
};


/* ----------------------------------------------------------------------------
*                                DECLARATIONS FONCTIONS
*----------------------------------------------------------------------------*/

/**hashFunction : Fonction de hachage renvoyant un entier correspondant à une
 *                clé de la table de hachage, dépendamment du state et letter
 *                passés en argument, ainsi que la taille de la table size*/
int hashFunction(int state, unsigned char letter, int size);

/**allocateAndInitializeList : alloue et initialise une liste de transition d'un
 *                 état à un autre en passant par une étiquette*/
List allocateAndInitializeList(Trie trie, int startNode, int targetNode,
    unsigned char letter);

/**testParametersHash : teste les paramètres passés en entrée, échoue s'ils sont
 *                  nuls*/
void testParametersHash(Trie trie, unsigned char *w);


/* ----------------------------------------------------------------------------
*                                FONCTIONS
*----------------------------------------------------------------------------*/

Trie createTrieHash(int maxNode) {
  if (maxNode < 1) {
    fprintf(stderr, "Node number insufficient\n");
    exit(EXIT_FAILURE);
  }
  /*------------------------------Allocation de la structure------------------*/
  Trie trie = malloc(sizeof(struct _trie));
  if (trie == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(EXIT_FAILURE);
  }
  /*-----------------------------Affectations---------------------------------*/
  trie->maxNode = maxNode;
  trie->nextNode = 1;
  /*----------------------------Initialisation et allocation de la matrice----*/
  size_t tableSize = (size_t) (FILL_RATE * maxNode);
  trie->transition = malloc(tableSize * sizeof(List));
  if (trie->transition == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(EXIT_FAILURE);
  }
  /*----------------------------Initialisation du tableau des états terminaux-*/
  char *finite = malloc((size_t) maxNode * sizeof(char));
  if (finite == NULL) {
    fprintf(stderr, "malloc error\n");
    freeHash(trie);
  }
  for (int i = 0; i < maxNode; i++) {
    finite[i] = '0';
  }
  trie->finite = finite;
  return trie;
}

void insertInTrieHash(Trie trie, unsigned char *w) {
  /*------------------------------------Tests---------------------------------*/
  testParametersHash(trie, w);
  /*-------------------------------Initialisation des variables---------------*/
  int currentLetterNb = 0;
  int currentNode = 0;
  /*-------------------------------Boucle sur le parcours du mot w------------*/
  while (w[currentLetterNb] != '\0') {
    /*----------------------------Variables locales---------------------------*/
    unsigned char letter = w[currentLetterNb];
    int tableSize = FILL_RATE * trie->maxNode;
    int key = hashFunction(currentNode, letter, tableSize);
    List *listsTab = trie->transition;
    /*----------------------------Vérification de lettre et ajout-------------*/
    if (listsTab[key] != NULL) {
      List list = listsTab[key];
      /*S'il existe une liste à la clé calculée dans le tableau
       * et tant que l'on n'est pas à la fin du parcours*/
      while (list != NULL) {
        /*Si l'on trouve la même transition*/
        if (list->startNode == currentNode && list->letter == letter) {
          /*On passe à la prochaine lettre et transition du mot*/
          currentNode = list->targetNode;
          break;
        }
        /*En revanche, si l'on n'est pas encore arrivé à la fin du
         * parcours, on contunue*/
        if (list->next != NULL) {
          list = list->next;
          /*Sinon, on crée notre transition en bout de liste*/
        } else {
					if(trie->maxNode == trie->nextNode) {
						fprintf(stderr, "Cannot insert, no place left\n");
						return;
					}
          List result = allocateAndInitializeList(trie, currentNode,
              trie->nextNode, letter);
          if (result == NULL) {
            return;
          }
          list->next = result;
          currentNode = result->targetNode;
          break;
        }
      }
      /*Si la liste n'est pas nulle, et donc que la transition existe déjà
       * on continue*/
      if (list != NULL) {
        ++currentLetterNb;
        continue;
      }
      /*S'il n'y a pas de liste à la clé calculée dans le tableau
       * on en crée une*/
    } else {
			if(trie->maxNode == trie->nextNode) {
				fprintf(stderr, "Cannot insert, no place left\n");
				return;
			}
      List result = allocateAndInitializeList(trie, currentNode, trie->nextNode,
          letter);
      if (result == NULL) {
        return;
      }
      trie->transition[key] = result;
      currentNode = result->targetNode;
    }
    ++currentLetterNb;
  }
  trie->finite[currentNode] = '1';
}

int isInTrieHash(Trie trie, unsigned char *w) {
  /*------------------------------------Tests---------------------------------*/
  testParametersHash(trie, w);
  /*-------------------------------Initialisation des variables---------------*/
  int currentLetterNb = 0;
  int currentNode = 0;
  /*-------------------------------Boucle sur le parcours du mot w------------*/
  while (w[currentLetterNb] != '\0') {
    /*----------------------------Variables locales---------------------------*/
    unsigned char letter = w[currentLetterNb];
    int tableSize = FILL_RATE * trie->maxNode;
    int key = hashFunction(currentNode, letter, tableSize);
    List *listsTab = trie->transition;
    /*----------------------------Vérification de lettre ---------------------*/
    if (listsTab[key] != NULL) {
      List list = listsTab[key];
      /*S'il existe une liste à la clé calculée dans le tableau
       * et tant que l'on n'est pas à la fin du parcours*/
      while (list != NULL) {
        /*Si l'on trouve la même transition*/
        if (list->startNode == currentNode && list->letter == letter) {
          /*On passe à la prochaine lettre et transition du mot*/
          currentNode = list->targetNode;
          break;
        }
        /*En revanche, si l'on n'est pas encore arrivé à la fin du
         * parcours, on contunue*/
        if (list->next != NULL) {
          list = list->next;
        } else {
          return 0;
        }
      }
      /*Si la liste n'est pas nulle, et donc que la transition existe déjà
       * on continue*/
      if (list != NULL) {
        ++currentLetterNb;
        continue;
      }
    } else {
      return 0;
    }
    ++currentLetterNb;
  }
  return trie->finite[currentNode] == '1';
}

/* A REVOIR
* 
* int getNodeFromCharacter(Trie trie, int beginNode, char c) {
	return trie->transition[beginNode][c];
}
* */

/* ----------------------------------------------------------------------------
*                                 OUTILS
*----------------------------------------------------------------------------*/
int hashFunction(int state, unsigned char letter, int size) {
  return (17 * letter + state * 53) % size;
}

void printTrieHash(Trie trie) {
  printf("Nombre maximal de noeuds du trie : %d\n", trie->maxNode);
  printf("Indice du prochain noeud disponible : %d\n", trie->nextNode);
  printf("Listes d'adjacence : \n");
  int tableSize = FILL_RATE * trie->maxNode;
  for (int i = 0; i < tableSize; i++) {
    List list = trie->transition[i];
    while (list != NULL) {
      printf("Etat de départ de la transition : %d\n", list->startNode);
      printf("Cible de la transition : %d\n", list->targetNode);
      printf("Etiquette de la transition : %c\n", list->letter);
      printf("\n");
      list = list->next;
    }
    printf("\n");
  }
  printf("\n");
  printf("Etats terminaux : \n");
  for (int i = 0; i < trie->maxNode; i++) {
    printf("Noeud n %d  %c\n", i, trie->finite[i]);
  }
}

List allocateAndInitializeList(Trie trie, int startNode, int targetNode,
    unsigned char letter) {
  if (trie->nextNode == trie->maxNode) {
    fprintf(stderr, "error not enough place\n");
    return NULL;
  }
  List list = malloc(sizeof(struct _list));
  if (list == NULL) {
    fprintf(stderr, "error malloc\n");
    return NULL;
  }
  list->startNode = startNode;
  list->targetNode = targetNode;
  list->letter = letter;
  ++trie->nextNode;
  return list;
}

void freeHash(Trie trie) {
  int tableSize = FILL_RATE * trie->maxNode;
  for (int i = 0; i < tableSize; i++) {
    if (trie->transition[i] != NULL) {
      List list = trie->transition[i];
      List next = list->next;
      while (next != NULL) {
        List acc = next->next;
        free(next);
        next = acc;
      }
      free(list);
    }
  }
  if (trie->transition != NULL) {
    free(trie->transition);
  }
  if (trie->finite != NULL) {
    free(trie->finite);
  }
  free(trie);
  return;
}

void testParametersHash(Trie trie, unsigned char *w) {
  /*------------------------------------Tests---------------------------------*/
  if (trie == NULL) {
    fprintf(stderr, "trie is null\n");
    exit(EXIT_FAILURE);
  }
  if (w == NULL) {
    fprintf(stderr, "word is null\n");
    exit(EXIT_FAILURE);
  }
}

void testFunctionsHash(void) {
	Trie trie = createTrieHash(TRIE_HEIGHT);
  printTrieHash(trie);
  unsigned char word[] = "cat";
  insertInTrieHash(trie, word);
  printTrieHash(trie);
  printf("taille : %d", trie->maxNode);
  unsigned char word2[] = "cactus";
  insertInTrieHash(trie, word2);
  printTrieHash(trie);
  unsigned char word3[] = "chocolate";
  insertInTrieHash(trie, word3);
  int result1 = isInTrieHash(trie, word2);
  int result2 = isInTrieHash(trie, word3);
  printf("\n est dans le trie cactus ? %d", result1);
  printf("\n est dans le trie chocolate ? %d\n", result2);
  //printTrieHash(trie);
  freeHash(trie);
}

