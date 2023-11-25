CC = gcc
CFLAGS = -std=c18 \
  -Wall -Wconversion -Werror -Wextra -Wfatal-errors -Wpedantic -Wwrite-strings \
  -O2 -fstack-protector-all -D_XOPEN_SOURCE=500
LDFLAGS =
RM = rm

all: trie_matrix trie_hash

trie_matrix: trie_matrix.o
		$(CC) -o trie_matrix trie_matrix.o $(LDFLAGS)

trie_matrix.o: trie_matrix.c trie_matrix.h
	$(CC) -c trie_matrix.c $(CFLAGS)


trie_hash.o: trie_hash.c trie_hash.h
	$(CC) -c trie_hash.c $(CFLAGS)


clean:
	$(RM) *.o  trie
