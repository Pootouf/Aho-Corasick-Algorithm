#include "trie.h"

/*----------------------------------------CONSTANTES--------------------------*/

#define ALPHABET_SIZE UCHAR_MAX
#define TRIE_HEIGHT 8

#define NO_NODE (-1)
#define MIN_NODE_NUMBER 1
#define FIRST_NODE_NUMBER 1

#define NOT_FINAL '0'
#define FINAL '1'

/*----------------------------------------STRUCTURES--------------------------*/

struct _trie {
    int maxNode; /* Nombre maximal de noeuds du trie */
    int nextNode; /* Indice du prochain noeud disponible */
    int **transition; /* matrice de transition */
    char *finite; /* etats terminaux */
};


/* ----------------------------------------------------------------------------
 *                                DECLARATIONS FONCTIONS
 *----------------------------------------------------------------------------*/

/**allocateAndInitializeMatrix : alloue et initialise la matrice de taille
 *                     maxNode x UCHAR_MAX dans la structure pointée par trie */
int **allocateAndInitializeMatrix(Trie trie, int maxNode);

/**isValidTrieAndWord : teste les paramètres passés en entrée, échoue s'ils sont
 * 									nuls*/
void isValidTrieAndWord(Trie trie, const unsigned char *word);

/**
 * testFunctionsMatrix : Teste l'exécution du programme
 */
void testFunctionsMatrix(void);

/* ----------------------------------------------------------------------------
 *                                FONCTIONS
 *----------------------------------------------------------------------------*/

int main(void) {
	testFunctionsMatrix();
}

Trie createTrie(int maxNode) {
    if(maxNode < MIN_NODE_NUMBER) {
        fprintf(stderr, "Node number insufficient\n");
        exit(EXIT_FAILURE);
    }

    Trie trie = malloc(sizeof(struct _trie));
    if (trie == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }

    trie->maxNode = maxNode;
    trie->nextNode = FIRST_NODE_NUMBER;
    trie->transition = allocateAndInitializeMatrix(trie, maxNode);

    trie->finite = malloc((size_t) maxNode * sizeof(char));
    if (trie->finite == NULL) {
        fprintf(stderr, "malloc error\n");
        freeTrie(trie);
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
        int result = getNodeFromCharacter(trie, currentNode, word[currentLetterNb]);
        if (result != NO_NODE) {
            currentNode = result;
        } else {
            createTransition(trie, currentNode, trie->nextNode, word[currentLetterNb]);
            currentNode = getNodeFromCharacter(trie, currentNode, word[currentLetterNb]);
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
        int result = getNodeFromCharacter(trie, currentNode, word[currentLetterNb]);
        if (result == NO_NODE) {
            return 0;
        }
        currentNode = result;
        ++currentLetterNb;
    }
    return (trie->finite[currentNode] == FINAL) ? 1 : 0;
}


void printTrie(Trie trie) {
    if(trie == NULL) {
        fprintf(stderr, "Impossible d'utiliser un trie vide \n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    printf("Nombre maximal de noeuds du trie : %d\n", trie->maxNode);
    printf("Indice du prochain noeud disponible : %d\n", trie->nextNode);
    printf("Matrice de transition : \n");
    for (int i = 0; i < trie->maxNode; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            printf("%d ", trie->transition[i][j]);
        }
        printf("\n");
    }
    printf("Etats terminaux : \n");
    for (int i = 0; i < trie->maxNode; i++) {
        printf("Noeud n %d  %c\n", i, trie->finite[i]);
    }
}

int getNodeFromCharacter(Trie trie, int beginNode, unsigned char c) {
    if(trie == NULL) {
        fprintf(stderr, "Impossible d'utiliser un trie vide \n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    return trie->transition[beginNode][c];
}

void createTransition(Trie trie, int startNode, int targetNode, unsigned char letter) {
    if(trie == NULL) {
        fprintf(stderr, "Impossible d'utiliser un trie vide \n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    int isANewNode = !isNodeInTrie(trie, targetNode);
    if (isANewNode) {
        if(isTrieFull(trie)) {
            fprintf(stderr, "Impossible d'ajouter car l'arbre est plein\n");
            return;
        }
    }
    trie->transition[startNode][letter] = targetNode;
    if(isANewNode) {
        trie->nextNode++;
    }
}


void freeTrie(Trie trie) {
    int index = trie->maxNode;
    int **matrix = trie->transition;
    for (int i = 0; i < index; i++) {
        if(matrix[i] != NULL) {
            free(matrix[i]);
        }
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
    for(size_t i = 0; i < (size_t)trie->maxNode; i++) {
        for(unsigned char letter = 0; (int)letter < ALPHABET_SIZE; letter++) {
            if(trie->transition[i][letter] == node) {
                return 1;
            }
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


/* ----------------------------------------------------------------------------
 *                                 OUTILS
 *----------------------------------------------------------------------------*/

int **allocateAndInitializeMatrix(Trie trie, int maxNode) {
    int **arr = malloc((size_t) maxNode * sizeof(int *));
    if (arr == NULL) {
        fprintf(stderr, "malloc error\n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < maxNode; i++) {
        int *tab = malloc(ALPHABET_SIZE * sizeof(int));
        if (tab == NULL) {
            fprintf(stderr, "malloc error\n");
            freeTrie(trie);
        }
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            tab[j] = NO_NODE;
        }
        arr[i] = tab;
    }
    return arr;
}


void isValidTrieAndWord(Trie trie, const unsigned char *word) {
    if (trie == NULL) {
        fprintf(stderr, "trie is null\n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    if (word == NULL) {
        fprintf(stderr, "word is null\n");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
}


void testFunctionsMatrix(void) {
    Trie trie = createTrie(TRIE_HEIGHT);
    printTrie(trie);
    unsigned char word[] = "cat";
    insertInTrie(trie, word);
    printTrie(trie);
    printf("taille : %d", trie->maxNode);
    unsigned char word2[] = "cactus";
    insertInTrie(trie, word2);
    printTrie(trie);
    unsigned char word3[] = "chocolate";
    insertInTrie(trie, word3);
    int result1 = isInTrie(trie, word2);
    int result2 = isInTrie(trie, word3);
    printf("\n est dans le trie cactus ? %d", result1);
    printf("\n est dans le trie chocolate ? %d\n", result2);
    //printTrie(trie);
    freeTrie(trie);
}
