C=gcc
CFLAGS=-Wall -Werror -std=c99 -g
LIBS=-lcurses

all:	snake breakout

breakout: breakout.o
	$(CC) $(CFLAGS) $(LIBS) breakout.o -o breakout

breakout.o: breakout.c
	$(CC) $(CFLAGS) $(LIBS) -c breakout.c

snake: snake.o
	$(CC) $(CFLAGS) $(LIBS) snake.o -o snake 

snake.o: snake.c
	$(CC) $(CFLAGS) -c snake.c

clean:
	rm -rf snake.o snake breakout.o breakout

