compile: trie.c
	cc -Wall -Werror -std=c11 -pedantic -ggdb -o trie trie.c

run: trie
	./trie

clean: trie
	rm trie
