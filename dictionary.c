// Author: Muhammed Ali Dilek (xemeds)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "trie.h"

// Length of the longest word
#define LONGEST_WORD 31

// Gets keyboard input
int get_input() {
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	char input = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return input;
}

// Clears the screen
void clear() {
	system("clear");
}

// Prints the start message
void start_message() {
	// Clear the screen
	clear();

	// Print the start message
	printf("Type the word below (Press ESCAPE to quit)\n");
}

// Adds the keyboard input to the word
void add_input(char *word, char input) {
	// If the input is not a valid letter or a backspace
	if (!(input >= 'A' && input <= 'Z') && !(input >= 'a' && input <= 'z') && (input != 127)) {
		// Return
		return;
	}

	// If the input is a uppercase letter
	if (input >= 'A' && input <= 'Z') {
		// Convert it into lowercase
		input += 32;
	}

	// Get the last empty index of the word
	int last_index = strlen(word);

	// If the input is a backspace and not the first input
	if (input == 127 && last_index != 0) {
		// Set the previous character of the word to null
		word[last_index - 1] = '\0';
	}
	// Else if the last index is smaller than the longest word and the input is not a backspace
	else if ((last_index < LONGEST_WORD) && (input != 127)) {
		// Set the last empty index of the word to the input
		word[last_index] = input;
	}
}

int main() {
	// Create the root node of the trie
	Node *root = create_node();

	// Open the dictionary file
	FILE *dictionary = fopen("dictionary.txt", "r");

	// If the file pointer is null
	if (dictionary == NULL) {
		// Print error message
		printf("Error while opening the dictionary file.\n");

		// Exit
		return 0;
	}

	// Initialize the word string
	char word[LONGEST_WORD + 1];

	// Read each word from the dictionary until EOF
	while (fscanf(dictionary, "%s", word) != EOF) {
		// Add each word to the trie
		add_word(root, word);
	}

	// Close the dictionary file
	fclose(dictionary);

	// Iterate over each character in the word
	for (int i = 0; i < LONGEST_WORD + 1; i++) {
		// Set it to the null character
		word[i] = '\0';
	}

	// Print the start message
	start_message();

	// Main loop
	while (1) {
		// Print the word
		printf("> %s", word);

		// Get the keyboard input
		char input = get_input();

		// Clear the screen
		clear();

		// If the input is the escape key
		if (input == 27) {
			// Break the loop
			break;
		}
		
		// Add the input to the word
		add_input(word, input);

		// If the word is empty
		if (word[0] == '\0') {
			// Print the start message
			start_message();

			// Go back to get the keyboard input
			continue;
		}

		// Print the matching words
		print_matching(root, word);
	}

	// Unload the trie from memory
	unload(root);

	// Clear the screen
	clear();

	// Exit
	return 1;
}
