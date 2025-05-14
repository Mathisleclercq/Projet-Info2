CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = tetris
SRC = tetris.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
