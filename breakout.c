#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define PADDEL_SIZE 20
#define BLOCK_SYM '#'

void moveball();
void updateball();
void drawblocks(int rows);
void colorsetup();

int maxx, maxy;
int bally = 0, ballx = 0, balld = 5;
int blocks = 0;

int main() {

	int padx = 0;

	initscr();
	clear();
	colorsetup();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	curs_set(0);
	keypad(stdscr, TRUE);

	getmaxyx(stdscr, maxy, maxx);
	bally = maxy/2;

	attron(COLOR_PAIR(3));
	mvprintw(maxy-1, 0, "=");
	for (int i = 1; i < PADDEL_SIZE; ++i) {
		printw("=");
	}
	attroff(COLOR_PAIR(3));

	drawblocks(3);

	refresh();

	halfdelay(0);

	while(1) {
		int c = getch();

		switch(c) {
			
			case KEY_LEFT:
				if(padx > 0) {
					padx--;
					attron(COLOR_PAIR(3));
					mvprintw(maxy-1, padx, "=");
					attroff(COLOR_PAIR(3));
					mvprintw(maxy-1, padx+PADDEL_SIZE, " ");
				}
				break;
			case KEY_RIGHT:
				if(padx < (maxx - PADDEL_SIZE)) {
					padx++;
					mvprintw(maxy-1, padx-1, " ");
					attron(COLOR_PAIR(3));
					mvprintw(maxy-1, padx+PADDEL_SIZE-1, "=");
					attroff(COLOR_PAIR(3));
				}
				break;
			case -1:
				break;
			default:
				mvprintw(24, 0, "BAD DIREC: %3d '%c'", c, c);
				refresh();
				break;
		}
		updateball();
		moveball();
		refresh();
	}	
}


void moveball() {
	mvprintw(bally, ballx, " ");
	switch(balld) {
		case 12:
			bally -= 2;
			break;
		case 1:
			bally -= 2;
			ballx += 1;
			break;
		case 2:
			bally -= 1;
			ballx += 2;
			break;
		case 4:
			bally += 1;
			ballx += 2;
		case 5:
			bally += 2;
			ballx += 1;
			break;
		case 6:
			bally += 2;
			break;
		case 7:
			bally += 2;
			ballx -= 1;
			break;
		case 8:
			bally += 1;
			ballx -= 2;
			break;
		case 10:
			bally -= 1;
			ballx -= 2;
		case 11:
			bally -= 2;
			ballx -= 1;
			break;
	}
	attron(COLOR_PAIR(2));
	mvaddch(bally, ballx, 'o'| A_BOLD);
	attroff(COLOR_PAIR(2));
	mvprintw(maxy-2, 0, "MAX : y:%d x:%d", maxy, maxx);
	mvprintw(maxy-1, 0, "BALL: y:%d x:%d", bally, ballx);
	mvprintw(0, 0, "BLOCKS: %3d", blocks);
	//mvprintw(0, maxx - 10, "LINES: %2d", lives);
}

void updateball() {
	int x = ballx, y = bally;

	switch(balld) {
		case 12:
			y--;
			break;
		case 1:
			y--;
			x++;
			break;
		case 5:
			y++;
			x++;
			break;
		case 6:
			y++;
			break;
		case 7:
			y++;
			x--;
			break;
		case 11:
			y--;
			x--;
			break;
	}

	char in = mvinch(y, x);
	//mvprintw(maxy-1, 0, "READING: '%c'", in);
	if((in != ' ' && in != 0) || (ballx < 1) || (bally < 0) || (ballx >= (maxx-1)) || (bally >= (maxy-1))) {
		if(in == BLOCK_SYM) {
			mvprintw(y,x," ");
			blocks--;
		}
		switch(balld) {
			case 12:
				balld = 5;
				break;
			case 1:
				if(ballx >= (maxx-1)) {
					balld = 11;
				} else {
					balld = 5;
				}
				break;
			case 5:
				if(ballx >= (maxx-1)) {
					balld = 7;
				} else {
					balld = 1;
				}
				break;
			case 6:
				balld = 11;
				break;
			case 7:
				if(ballx < 1) {
					balld = 5;
				} else {
					balld = 11;
				}
				break;
			case 11:
				if(ballx < 1) {
					balld = 1;
				} else {
					balld = 7;
				}
				break;
		}
	}


}

int collisiondetection() {
	//TODO: actually fill this out
	return -1;
}

void drawblocks(int rows) {
	int at=1;
	attron(COLOR_PAIR(1));
	for (int i = 0; i < rows; ++i) {
		move(at, 0);
		at += 4;

		for (int j = 0; j < maxx; ++j) {
			addch(BLOCK_SYM);
			blocks++;
		}
	}
	attroff(COLOR_PAIR(1));

}

void colorsetup() {
	if(has_colors() == FALSE) {	
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);        //BLOCK
	init_pair(2, COLOR_WHITE, COLOR_BLACK);      //BALL
	init_pair(3, COLOR_CYAN, COLOR_BLACK);       //PADDEL
}
