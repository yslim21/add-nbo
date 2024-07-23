CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: add-nbo

add-nbo: add-nbo.o
	$(CC) $(CFLAGS) -o add-nbo add-nbo.o

add-nbo.o: add-nbo.c
	$(CC) $(CFLAGS) -c add-nbo.c

clean:
	rm -f add-nbo add-nbo.o


