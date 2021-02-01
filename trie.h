#include <stdbool.h>

// Number of different characters
#define CHAR_SIZE 26

// Represents a node in the trie
typedef struct Node {
	struct Node *children[CHAR_SIZE];
	bool end_of_word;
} Node;

// Prototypes
Node *create_node();
void add_word(Node *root, char *word);
Node *move_node(Node *root, char *word);
char *append(char* word, char character);
void print_all(Node *root, char *word);
void print_matching(Node *root, char *word);
void unload(Node *root);
