#include "trie.h"

/* ----------------------------------------------------------------------------
 *                                DECLARATIONS FONCTIONS
 *----------------------------------------------------------------------------*/

/**freeAndTerminate : libère l'espace alloué pour la structure trie
*/
void freeAndTerminate(Trie trie);

/**allocateAndInitializeMatrix : alloue et initialise la matrice de taille
 *                     maxNode x UCHAR_MAX dans la structure pointée par trie */
int **allocateAndInitializeMatrix(Trie trie, int maxNode);

/**testParameters : teste les paramètres passés en entrée, échoue s'ils sont
 * 									nuls*/
void testParameters(Trie trie, unsigned char *w);

/**testFunctions : teste les fonctions de création, insertion, présence dans un
 * 								trie et l'affiche
 */
void testFunctions();


/**copy : copie une chaine de caractères src dans une chaine de caractères
 * 				dest.
 */
void copy(unsigned char *src, unsigned char *dest);

/**sumNFistNumber : renvoie la somme des n premiers entiers
 */
int sumNFirstNumber(int length);

/*-------------------------------Variables globales---------------------------*/

/*
 * -1 : aucune option n'a été sélectionnée
 * 1  : option hash
 * 0  : option matrix
 */
int implementation = -1;

/* ----------------------------------------------------------------------------
 *                                FONCTION PRINCIPALE
 *----------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
	int opt;
	while((opt = getopt(argc, argv, "hm")) != -1) {
		switch(opt) {
			case 'h':
				if (implementation != -1) {
					fprintf(stderr, "Cannot apply 2 options at the same time\n");
					exit(EXIT_FAILURE);
				}
				implementation = 1;
				break;
			case 'm':
				if(implementation != -1) {
					fprintf(stderr, "Cannot apply 2 options at the same time\n");
					exit(EXIT_FAILURE);
				}
				implementation = 0;
				break;
			default:
				fprintf(stderr, "Please select -h for hash implementation or -m for matrix implementation\n");
				exit(EXIT_FAILURE);
		}
	}
	#if 0
	testFunctions();
  #else
  char w[] = "cactus";
  createPrefix((unsigned char*)w);
  createSuffix((unsigned char*)w);
  createFactor((unsigned char*)w);
  printf("%s\n", w);
  #endif
  return EXIT_SUCCESS;
}

/* ----------------------------------------------------------------------------
 *                                FONCTIONS
 *----------------------------------------------------------------------------*/
Trie createTrie(int maxNode) {
	switch(implementation) {
		case 1:
			return createTrieHash(maxNode);
		case 0:
			return createTrieMatrix(maxNode);
		default:
			fprintf(stderr, "Not a valid implementation type\n");
			return NULL;
	}
}

void insertInTrie(Trie trie, unsigned char *w) {
	if(trie == NULL) {
		fprintf(stderr, "Not a valid trie\n");
		return;
	}
	switch(implementation) {
		case 1:
			insertInTrieHash(trie, w);
			return;
		case 0:
			insertInTrieMatrix(trie, w);
			return;
		default:
			fprintf(stderr, "Not a valid implementation type\n");
			return;
	}
}

int isInTrie(Trie trie, unsigned char *w) {
	if(trie == NULL) {
		fprintf(stderr, "Not a valid trie\n");
		return -1;
	}
	switch(implementation) {
		case 1:
			return isInTrieHash(trie, w);
		case 0:
			return isInTrieMatrix(trie, w);
		default:
			fprintf(stderr, "Not a valid implementation type\n");
			return -1;
	}
}

void printTrie(Trie trie) {
	if(trie == NULL) {
		fprintf(stderr, "Not a valid trie\n");
		return;
	}
	switch(implementation) {
		case 1:
			printTrieHash(trie);
			return;
		case 0:
			printTrieMatrix(trie);
			return;
		default:
			fprintf(stderr, "Not a valid implementation type\n");
			return;
	}
}

void freeAndTerminate(Trie trie) {
	if(trie == NULL) {
		fprintf(stderr, "Not a valid trie\n");
		return;
	}
	switch(implementation) {
		case 1:
			freeAndTerminateHash(trie);
			return;
		case 0:
			freeAndTerminateMatrix(trie);
			return;
		default:
			fprintf(stderr, "Not a valid implementation type\n");
			return;
	}
}


void testFunctions() {
	switch(implementation) {
		case 1:
			testFunctionsHash();
			return;
		case 0:
			testFunctionsMatrix();
			return;
		default:
			fprintf(stderr, "Not a valid implementation type\n");
			return;
	}
}

void createPrefix(unsigned char *w) {
	Trie trie = createTrie(TRIE_HEIGHT);
	int currentLetterNb = 0;
	size_t length = strlen((char *)w);
	unsigned char truncWord [length];
	copy(w, truncWord);
	while(w[currentLetterNb] != '\0') {
		truncWord[(int)length - currentLetterNb] = '\0';
		insertInTrie(trie, truncWord);
		++currentLetterNb;
	}
	truncWord[(int)length - currentLetterNb] = '\0';
	insertInTrie(trie, truncWord);
	printTrie(trie);
}

void createSuffix(unsigned char *w) {
	size_t length = strlen((char *)w);
	Trie trie = createTrie(1 + sumNFirstNumber((int)length));
	int currentLetterNb = 0;
	
	unsigned char truncWord [length];
	copy(w, truncWord);
	while(w[currentLetterNb] != '\0') {
		insertInTrie(trie, truncWord+currentLetterNb);
		++currentLetterNb;
	}
	insertInTrie(trie, truncWord+currentLetterNb);
	printTrie(trie);
}

void createFactor(unsigned char *w) {
	size_t length = strlen((char *)w);
	Trie trie = createTrie(1 + sumNFirstNumber((int)length));
	int currentLetterNb = 0;
	unsigned char truncWord [length];
	copy(w, truncWord);
	while(w[currentLetterNb] != '\0') {
		unsigned char suffix [length];
		copy(truncWord+currentLetterNb, suffix);
		int suffixLetterNb = 0;
		size_t suffLength = strlen((char *)suffix);
		while(truncWord[suffixLetterNb + currentLetterNb] != '\0') {
			suffix[(int)suffLength - suffixLetterNb] = '\0';
			insertInTrie(trie, suffix);
			++suffixLetterNb;
		}
		suffix[(int)suffLength - suffixLetterNb] = '\0';
		insertInTrie(trie, suffix);
		++currentLetterNb;
	}
	insertInTrie(trie, truncWord+currentLetterNb);
	printTrie(trie);
	freeAndTerminate(trie);
}

void copy(unsigned char *src, unsigned char *dest) {
	size_t length = strlen((char *)src);
	for(size_t i = 0; i <= length; i++) {
		dest[i] = src[i];
	}
}

int sumNFirstNumber(int length) {
	return length * (length + 1) / 2;
}
