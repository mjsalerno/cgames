C=gcc
CFLAGS=-Wall -Werror -std=c99 -g
LIBS=-lcurses

all:	snake breakout tetris

tetris: tetris.o
	$(CC) $(CFLAGS) tetris.o -o tetris $(LIBS)

tetris.o: tetris.c
	$(CC) $(CFLAGS) -c tetris.c

breakout: breakout.o
	$(CC) $(CFLAGS) breakout.o -o breakout $(LIBS)

breakout.o: breakout.c
	$(CC) $(CFLAGS) -c breakout.c

snake: snake.o
	$(CC) $(CFLAGS) snake.o -o snake $(LIBS)

snake.o: snake.c
	$(CC) $(CFLAGS) -c snake.c

clean:
	rm -rf snake.o snake breakout.o breakout tetris.o tetris

