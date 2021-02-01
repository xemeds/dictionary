#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

// Creates and returns a new empty node
Node *create_node() {
	// Allocate space for the node
	Node *node = malloc(sizeof(Node));

	// Set its end of word value to false
	node->end_of_word = false;

	// Iterate over each child node
	for (int i = 0; i < CHAR_SIZE; i++) {
		// Set each child node to null
		node->children[i] = NULL;
	}

	// Return the node
	return node;
}

// Adds a word to the trie
void add_word(Node *root, char *word) {
	// Iterate over each character
	for (int i = 0; word[i] != '\0'; i++) {
		// If the child node at the characters index is null
		if (root->children[word[i] - 97] == NULL) {
			// Set it to a new node
			root->children[word[i] - 97] = create_node();
		}
		
		// Move the root node to the node at the characters index
		root = root->children[word[i] - 97];

		// If the next character is null (current character is the last)
		if (word[i + 1] == '\0') {
			// Set the nodes end of word value to true
			root->end_of_word = true;
		}
	}
}

// Moves through the trie using the word and returns the last node or returns null if it cant move there
Node *move_node(Node *root, char *word) {
	// Iterate over each character of the word
	for (int i = 0; word[i] != '\0'; i++) {
		// If the child node at the characters index is null
		if (root->children[word[i] - 97] == NULL) {
			// Return null
			return NULL;
		}
		
		// Move the root node to the node at the characters index
		root = root->children[word[i] - 97];
	}

	// Return the last node
	return root;
}

// Appends a char to the word and returns it
char *append(char* word, char character) {
	// Get the length of the word
	int len = strlen(word);

	// Initialize the new word
	char new_word[len + 2];

	// Copy the word to the new word
	strcpy(new_word, word);

	// Append the character
	new_word[len] = character;

	// Set the null character
	new_word[len + 1] = '\0';

	// Return a pointer to the new word
	return strdup(new_word);
}

// Prints all the possible words from the given node
void print_all(Node *root, char *word) {
	// If the node is already null
	if (root == NULL) {
		// Return
		return;
	}

	// If the node is the end of a word
	if (root->end_of_word) {
		// Print the word
		printf("%s\n", word);
	}

	// Iterate over each child node
	for (int i = 0; i < CHAR_SIZE; i++) {
		// Convert the child nodes index to a char and append it to the word
		char *new_word = append(word, i + 'a');

		// Print all the possible words starting from that node
		print_all(root->children[i], new_word);
	}
}

// Prints all the matching words
void print_matching(Node *root, char *word) {
	// Move the root node to the last node of the word
	root = move_node(root, word);

	// If the node is null
	if (root == NULL) {
		// Print message
		printf("No matching words!\n");

		// Return
		return;
	}
	// Else
	else {
		// Print all the possible words from that node
		print_all(root, word);
	}
}

// Unloads the trie from memory
void unload(Node *root) {
	// If the node is already null
	if (root == NULL) {
		// Return
		return;
	}

	// Iterate over each child node
	for (int i = 0; i < CHAR_SIZE; i++) {
		// Unload the trie starting from that node
		unload(root->children[i]);
	}

	// Free the node
	free(root);
}
