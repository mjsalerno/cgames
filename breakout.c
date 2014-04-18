#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define PADDEL_SIZE 20

void moveball();

int maxx, maxy;
int bally = 0, ballx = 0, balld = 5;

int main() {

	int padx = 0;

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	curs_set(0);
	keypad(stdscr, TRUE);

	getmaxyx(stdscr, maxy, maxx);


	mvprintw(maxy-1, 0, "=");
	for (int i = 1; i < PADDEL_SIZE; ++i) {
		printw("=");
	}


	refresh();

	halfdelay(2);

	while(1) {
		int c = getch();

		switch(c) {
			
			case KEY_LEFT:
				padx--;
				mvprintw(maxy-1, padx, "=");
				mvprintw(maxy-1, padx+PADDEL_SIZE, " ");
				break;
			case KEY_RIGHT:
				padx++;
				mvprintw(maxy-1, padx-1, " ");
				mvprintw(maxy-1, padx+PADDEL_SIZE-1, "=");
				break;
			case -1:
				break;
			default:
				mvprintw(24, 0, "BAD DIREC: %3d '%c'", c, c);
				refresh();
				break;
		}
		moveball();
		refresh();
	}	
}


void moveball() {
	mvprintw(bally, ballx, " ");
	switch(balld) {
		case 12:
			bally--;
			break;
		case 1:
			bally--;
			ballx++;
			break;
		case 5:
			bally++;
			ballx++;
			break;
		case 6:
			bally++;
			break;
		case 7:
			bally++;
			ballx--;
			break;
		case 11:
			bally--;
			ballx--;
			break;
	}
	mvprintw(bally, ballx, "o");
}
