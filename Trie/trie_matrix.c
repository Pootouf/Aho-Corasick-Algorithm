#include "trie_matrix.h"

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

/**testParametersMatrix : teste les paramètres passés en entrée, échoue s'ils sont
 * 									nuls*/
void testParametersMatrix(Trie trie, unsigned char *w);

void testFunctionsMatrix(void);

/* ----------------------------------------------------------------------------
 *                                FONCTIONS
 *----------------------------------------------------------------------------*/

int main() {
	testFunctionsMatrix();
}

Trie createTrieMatrix(int maxNode) {
	if(maxNode < 1) {
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
  trie->transition = allocateAndInitializeMatrix(trie, maxNode);
  /*----------------------------Initialisation du tableau des états terminaux-*/
  char *finite = malloc((size_t) maxNode * sizeof(char));
  if (finite == NULL) {
    fprintf(stderr, "malloc error\n");
    freeAndTerminateMatrix(trie);
  }
  for (int i = 0; i < maxNode; i++) {
    finite[i] = '0';
  }
  trie->finite = finite;
  return trie;
}

void insertInTrieMatrix(Trie trie, unsigned char *w) {
  /*------------------------------------Tests---------------------------------*/
  testParametersMatrix(trie, w);
  /*-------------------------------Initialisation des variables---------------*/
  int currentLetterNb = 0;
  int currentNode = 0;
  /*-------------------------------Boucle sur le parcours du mot w------------*/
  while (w[currentLetterNb] != '\0') {
    int result = getNodeFromCharacter(trie, currentNode, w[currentLetterNb]);
    /*----------------------------Test d'existence du noeud-------------------*/
    if (result != -1) {
      currentNode = result;
    } else {
      if (trie->nextNode == trie->maxNode) {
        fprintf(stderr, "cannot insert, no place left\n");
        return;
      }
      createTransition(trie, currentNode, trie->nextNode, w[currentLetterNb]);
      currentNode = trie->nextNode;
      ++trie->nextNode;
    }
    ++currentLetterNb;
  }
  /*-------------------------------Mise à jour de l'état final----------------*/
  trie->finite[currentNode] = '1';
}

int isInTrieMatrix(Trie trie, unsigned char *w) {
	/*------------------------------------Tests---------------------------------*/
  testParametersMatrix(trie, w);
  /*------------------------------------Initialisation des variables----------*/
  int currentLetterNb = 0;
  int currentNode = 0;
  /*-------------------------------Boucle sur le parcours du mot w------------*/
  while (w[currentLetterNb] != '\0') {
    int result = getNodeFromCharacter(trie, currentNode, w[currentLetterNb]);
    /*----------------------------Test d'existence du mot---------------------*/
    if (result == -1) {
			return 0;
		}
		currentNode = result;
		++currentLetterNb;
	}
	return (trie->finite[currentNode] == '1') ? 1 : 0;
}


/* ----------------------------------------------------------------------------
 *                                 OUTILS
 *----------------------------------------------------------------------------*/
void freeAndTerminateMatrix(Trie trie) {
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
  return;
}

int **allocateAndInitializeMatrix(Trie trie, int maxNode) {
  int **arr = malloc((size_t) maxNode * sizeof(int *));
  if (arr == NULL) {
    fprintf(stderr, "malloc error\n");
    free(trie);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < maxNode; i++) {
    int *tab = malloc(ALPHABET_SIZE * sizeof(int));
    if (tab == NULL) {
      fprintf(stderr, "malloc error\n");
      freeAndTerminateMatrix(trie);
    }
    for (int j = 0; j < ALPHABET_SIZE; j++) {
      tab[j] = DEFAULT_VALUE;
    }
    arr[i] = tab;
  }
  return arr;
}

void printTrieMatrix(Trie trie) {
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
	return trie->transition[beginNode][c];
}

void createTransition(Trie trie, int startNode, int targetNode, unsigned char c) {
	trie->transition[startNode][c] = targetNode;
}





void testParametersMatrix(Trie trie, unsigned char *w) {
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

void testFunctionsMatrix(void) {
	Trie trie = createTrieMatrix(TRIE_HEIGHT);
  printTrieMatrix(trie);
  unsigned char word[] = "cat";
  insertInTrieMatrix(trie, word);
  printTrieMatrix(trie);
  printf("taille : %d", trie->maxNode);
  unsigned char word2[] = "cactus";
  insertInTrieMatrix(trie, word2);
  printTrieMatrix(trie);
  unsigned char word3[] = "chocolate";
  insertInTrieMatrix(trie, word3);
  int result1 = isInTrieMatrix(trie, word2);
  int result2 = isInTrieMatrix(trie, word3);
  printf("\n est dans le trie cactus ? %d", result1);
  printf("\n est dans le trie chocolate ? %d\n", result2);
  //printTrie(trie);
  freeAndTerminateMatrix(trie);
}
