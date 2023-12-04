#include <stdlib.h>
/*-------------------------------------BIBLIOTHEQUES--------------------------*/
#include <stdio.h>
#include <time.h>
#include <string.h>

/*----------------------------------------CONSTANTES--------------------------*/

#define CHAR_START 33


/* ----------------------------------------------------------------------------
*                                DECLARATIONS FONCTIONS
*----------------------------------------------------------------------------*/

/**
 * generateWords : génère wordNumber mots de taille comprise entre wordSizeMin
 * 								 et wordSizeMax sur un alpbabet de taille alphabetSize.
 */
void generateWords(int wordNumber, int wordSizeMin, int wordSizeMax, int alphabetSize);

/* ----------------------------------------------------------------------------
*                                FONCTION PRINCIPALE
*----------------------------------------------------------------------------*/

int main(int argc, char* argv[]) {
	if(argc != 5) {
		fprintf(stderr, "Invalid number of argument\n");
	}
	
	int wordNumber = atoi(argv[1]);
	int wordSizeMin = atoi(argv[2]);
	int wordSizeMax = atoi(argv[3]);
	int alphabetSize = atoi(argv[4]);
	
	generateWords(wordNumber, wordSizeMin, wordSizeMax, alphabetSize);
	
}

/* ----------------------------------------------------------------------------
*                                FONCTIONS
*-----------------------------------------------------------------------------*/

void generateWords(int wordNumber, int wordSizeMin, int wordSizeMax, int alphabetSize) {
	for(unsigned int i = 0; i < (unsigned int)wordNumber; i++) {
        srand((unsigned int)time(NULL) * (i+2));
		int wordSize = (wordSizeMin + rand() % (wordSizeMax + 1 - wordSizeMin));
		for(int j = 0; j < wordSize; j++) {
			char character = (char) (CHAR_START + rand() % (alphabetSize));
			printf("%c", character);
		}
		printf("\n");
	}
}


