#include "trie.h"

/*----------------------------------------CONSTANTES--------------------------*/

/**Taille du tableau = 4/3 * nombre de noeuds
 * Constante maintenant le taux de remplissage de la table de hachage inférieure
 * ou égale à 0.75*/
#define FILL_RATE (4/3)

#define TRIE_HEIGHT 8

#define MIN_NODE_NUMBER 1

#define FIRST_NEXT_NODE_NUMBER (FIRST_NODE + 1)


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

/**
 * getValueFromHashFunction : Fonction de hachage renvoyant un entier correspondant à une
 *                clé de la table de hachage, dépendamment du state et letter
 *                passés en argument, ainsi que la taille de la table size
 */
int getValueFromHashFunction(int state, unsigned char letter, int size);

/**
 * allocateAndInitializeList : alloue un élément de List à partir des paramètres et le renvoie
 */
List allocateAndInitializeList(int startNode, int targetNode, unsigned char letter);

/**
 * isValidTrieAndWord : teste si trie et word sont valides (différent de NULL)
 */
void isValidTrieAndWord(Trie trie, const unsigned char* word);

/**
 * testFunctionsHash : teste le programme
 */
void testFunctionsHash(void);

/**
 * getHashtableSizeFromTrie : renvoie la taille du tableau de hachage de Trie
 */
size_t getHashtableSizeFromTrie(Trie trie);

/**
 * appendListInTableOfList : ajoute la liste list dans table à l'indice key
 */
void appendListInTableOfList(List* table, List list, int key);


/* ----------------------------------------------------------------------------
*                                FONCTIONS
*----------------------------------------------------------------------------*/

Trie createTrie(int maxNode) {
    if (maxNode < MIN_NODE_NUMBER) {
        fprintf(stderr, "Node number insufficient\n");
        exit(EXIT_FAILURE);
    }


    Trie trie = malloc(sizeof(struct _trie));
    if (trie == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }


    trie->maxNode = maxNode;
    trie->nextNode = FIRST_NEXT_NODE_NUMBER;


    size_t tableSize = getHashtableSizeFromTrie(trie);
    trie->transition = malloc(tableSize * sizeof(List));
    if (trie->transition == NULL) {
        fprintf(stderr, "malloc error\n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    for(size_t i = 0; i < tableSize; i++) {
        trie->transition[i] = NULL;
    }


    trie->finite = malloc((size_t) maxNode * sizeof(char));
    if (trie->finite == NULL) {
        fprintf(stderr, "malloc error\n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < maxNode; i++) {
        trie->finite[i] = NOT_FINAL;
    }


    return trie;
}

void insertInTrie(Trie trie, unsigned char *word) {
    isValidTrieAndWord(trie, word);
    int currentLetterNb = 0;
    int currentNode = 0;
    while (word[currentLetterNb] != '\0') {
        int nextNode = getNodeFromCharacter(trie, currentNode, word[currentLetterNb]);
        if (nextNode == NO_NODE) {
            createTransitionInTrie(trie, currentNode, trie->nextNode, word[currentLetterNb]);
            currentNode = trie->nextNode;
            trie->nextNode++;
        } else {
            currentNode = nextNode;
        }
        if(currentNode == NO_NODE) {
            return;
        }
        ++currentLetterNb;
    }
    trie->finite[currentNode] = FINAL;
}

int isInTrie(Trie trie, unsigned char *word) {
    isValidTrieAndWord(trie, word);
    int currentLetterNb = 0;
    int currentNode = 0;
    while (word[currentLetterNb] != '\0') {
        int nextNode = getNodeFromCharacter(trie, currentNode, word[currentLetterNb]);
        if(nextNode == NO_NODE) {
            return 0;
        } else {
            currentNode = nextNode;
        }
        currentLetterNb++;
    }
    return trie->finite[currentNode] == FINAL;
}

int getNodeFromCharacter(Trie trie, int beginNode, unsigned char letter) {
    if(trie == NULL) {
        fprintf(stderr, "Impossible d'utiliser un trie vide \n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
	int hashValue = getValueFromHashFunction(beginNode, letter, trie->maxNode * FILL_RATE);
	List list = trie->transition[hashValue];
	while(list != NULL && (list->startNode != beginNode || list->letter != letter)) {
		list = list->next;
	}
	if(list == NULL) {
		return NO_NODE;
	}
    return list->targetNode;
}

void createTransitionInTrie(Trie trie, int startNode, int targetNode, unsigned char letter) {
    if(trie == NULL) {
        fprintf(stderr, "Impossible d'ajouter une transition dans un trie vide \n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }

    int nextNode = getNodeFromCharacter(trie, startNode, letter);
    if (nextNode == targetNode) {
        return;
    }
    if (isTrieFull(trie)) {
        fprintf(stderr, "Impossible d'ajouter car l'arbre est plein\n");
        return;
    }
    List result = allocateAndInitializeList(startNode, targetNode, letter);
    if (result == NULL) {
                freeTrie(trie);
                exit(EXIT_FAILURE);
    }
    int key = getValueFromHashFunction(startNode, letter, trie->maxNode * FILL_RATE);
    appendListInTableOfList(trie->transition, result, key);
}

void freeTrie(Trie trie) {
    int tableSize = FILL_RATE * trie->maxNode;
    for (int i = 0; i < tableSize; i++) {
        if (trie->transition[i] != NULL) {
            List list = trie->transition[i];
            while (list->next != NULL) {
                List acc = list->next;
                free(list);
                list = acc;
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
}

int isNodeInTrie(Trie trie, int node) {
    if(trie == NULL) {
        fprintf(stderr, "Impossible d'utiliser un trie vide \n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    size_t tableSize = getHashtableSizeFromTrie(trie);
    for(size_t i = 0; i < tableSize; i++) {
        List list = trie->transition[i];
        while(list != NULL) {
            if (list->targetNode == node || list->startNode == node) {
                return 1;
            }
            list = list->next;
        }
    }
    return 0;
}

int isTrieFull(Trie trie) {
    if(trie == NULL) {
        fprintf(stderr, "Impossible d'utiliser un trie vide \n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    return trie->maxNode <= trie->nextNode;
}

void printTrie(Trie trie) {
    if(trie == NULL) {
        fprintf(stderr, "Impossible d'afficher un trie vide \n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    printf("Nombre maximal de noeuds du trie : %d\n", trie->maxNode);
    printf("Indice du prochain noeud disponible : %d\n", trie->nextNode);
    printf("Listes d'adjacence : \n");
    size_t tableSize = getHashtableSizeFromTrie(trie);
    for (size_t i = 0; i < tableSize; i++) {
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


void setNodeFinal(Trie trie, int node) {
    trie->finite[node] = FINAL;
}

char isNodeFinal(Trie trie, int node) {
    return trie->finite[node];
}

int getLastNode(Trie trie) {
    return trie->nextNode - 1;
}


/* ----------------------------------------------------------------------------
*                                 OUTILS
*----------------------------------------------------------------------------*/

int getValueFromHashFunction(int state, unsigned char letter, int size) {
  return (17 * letter + state * 53) % size;
}

size_t getHashtableSizeFromTrie(Trie trie) {
    return (size_t) (FILL_RATE * trie->maxNode);
}

void appendListInTableOfList(List* table, List list, int key) {
    List oldList = table[key];
    if(oldList == NULL) {
        table[key] = list;
    } else {
        while(oldList->next != NULL) {
            oldList = oldList->next;
        }
        oldList->next = list;
    }
}

void isValidTrieAndWord(Trie trie, const unsigned char* word) {
    if (trie == NULL) {
        fprintf(stderr, "Cannot insert if trie is null\n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    if (word == NULL) {
        fprintf(stderr, "Cannot add a null word\n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
}


List allocateAndInitializeList(int startNode, int targetNode, unsigned char letter) {
  List list = malloc(sizeof(struct _list));
  if (list == NULL) {
    fprintf(stderr, "error malloc\n");
    return NULL;
  }
  list->startNode = startNode;
  list->targetNode = targetNode;
  list->letter = letter;
  list->next = NULL;
  return list;
}


void testFunctionsHash(void) {
    Trie trie = createTrie(TRIE_HEIGHT);
    printTrie(trie);
    unsigned char word[] = "cat";
    insertInTrie(trie, word);
    printTrie(trie);
    printf("taille : %d\n", trie->maxNode);
    unsigned char word2[] = "cactus";
    insertInTrie(trie, word2);
    printTrie(trie);
    unsigned char word3[] = "chocolate";
    insertInTrie(trie, word3);
    int result1 = isInTrie(trie, word2);
    int result2 = isInTrie(trie, word3);
    printf("\n est dans le trie cactus ? %d", result1);
    printf("\n est dans le trie chocolate ? %d\n", result2);
    printTrie(trie);
    freeTrie(trie);
}

