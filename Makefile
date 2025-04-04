compile: trie.c
	cc -Wall -Werror -Wextra -ggdb -o trie trie.c

run: trie
	./trie

svg: trie
	./trie > graph.dot
	dot -Tsvg graph.dot > graph.svg

clean: trie
	rm trie *.dot *.svg
