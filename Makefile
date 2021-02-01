CC=gcc

TARGET=dictionary
COMMAND=dictionary.c trie.c -o $(TARGET)

all:
	$(CC) $(COMMAND)

clean:
	rm $(TARGET)
