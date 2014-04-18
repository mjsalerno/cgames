C=gcc
CFLAGS=-Wall -Werror -std=c99 -g
LIBS=-lcurses

all:	snake

snake: snake.o
		$(CC) $(CFLAGS) $(LIBS) snake.o -o snake 

snake.o: snake.c
		$(CC) $(CFLAGS) -c snake.c

clean:
		rm -rf snake.o snake
