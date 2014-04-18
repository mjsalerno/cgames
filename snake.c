#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SNAKE_SIZE 256

typedef struct Body body;

void freesnake(body *head, int size);
void movesnake(body *bod, int size, int direc);
void drawsnake(body *bod, int size);
void clearsnake(body *bod, int size);
void redrawfood();
int checklose(body *head, int size);

struct Body {
   int row;
   int col;
   int direc;
};

int maxx, maxy;
int foodx = 0, foody = 0;

int main() {
	int c = KEY_RIGHT, newc;

	int row = 0, col = 0;		
	int size = 1;
	int lost = 0;

	body* snakebody = malloc(MAX_SNAKE_SIZE * sizeof(body));
	snakebody->row = 0;
	snakebody->col = 0;
	snakebody->direc = KEY_RIGHT;

	initscr();
	clear();

	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);


	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	curs_set(0);
	keypad(stdscr, TRUE);

	getmaxyx(stdscr, maxy, maxx);

	srand(time(NULL));
	redrawfood();

	mvprintw(row, col, "0");
	refresh();

	halfdelay(2);

	while(1) {
		newc = getch();

		if(newc != -1) {
			c = newc;
		}

		clearsnake(snakebody, size);
		movesnake(snakebody, size, c);
		lost = checklose(snakebody, size);

		if(lost) {
			clear();
			cbreak();
			mvprintw(maxy/2, (maxx/2) - 4, "FAIL  D:");
			refresh();
			getch();
			endwin();
			return 0;
		} else {
			drawsnake(snakebody, size);
		}

		mvprintw(maxy-2, 0, "Y| you: %2d  food: %2d", snakebody->row, foody);
		mvprintw(maxy-1, 0, "X| you: %2d  food: %2d", snakebody->col, foodx);

		if(foody == snakebody->row && foodx == snakebody->col) {

			
			(snakebody+size)->row = 0;
			(snakebody+size)->col = 0;
			(snakebody+size)->direc = KEY_RIGHT;
			size++;
			redrawfood();

			if(size == MAX_SNAKE_SIZE) {
				clear();
				cbreak();
				mvprintw(maxy/2, (maxx/2) - 3, "WIN :D");
				refresh();
				getch();
				endwin();
				//freesnake(snakebody, size);
				return 0;
			}
		}

		refresh();
	}	
}

void movesnake(body *bod, int size, int direc) {
	int i;
	for (i = size-1; i > 0; --i) {
		(bod+i)->row = (bod+i-1)->row;
		(bod+i)->col = (bod+i-1)->col;
		(bod+i)->direc = (bod+i-1)->direc;
	}

	switch(direc) {
		case KEY_UP:
			bod->row--;
			break;
		case KEY_DOWN:
			bod->row++;
			break;
		case KEY_LEFT:
			bod->col--;
			break;
		case KEY_RIGHT:
			bod->col++;
			break;
		default:
			mvprintw(24, 0, "BAD DIREC: %3d '%c'", direc, direc);
			refresh();
			break;
	}

}

void clearsnake(body *bod, int size) {
	int i;
	for (i = 0; i < size; ++i)	{
		mvprintw((bod+i)->row, (bod+i)->col, " ");
	}
}

void drawsnake(body *bod, int size) {
	int i;
	attron(COLOR_PAIR(1));
	for (i = 0; i < size; ++i)	{
		mvprintw((bod+i)->row, (bod+i)->col, "0");
	}
	attroff(COLOR_PAIR(1));
}

void freesnake(body *head, int size) {
	int i;
	for (i = 0; i < size; ++i) {
		free(head+i);
	}
}

void redrawfood() {

	foodx = rand() % maxx;
	foody = rand() % maxy;

	attron(COLOR_PAIR(2));
	mvprintw(foody, foodx, "#");
	attroff(COLOR_PAIR(2));

}

int checklose(body *head, int size) {
	int i;

	if(head->row >= maxy || head->col >= maxx 
	   || head->row < 0 || head->col < 0) {
		return 1;
	}

	for (i = 1; i < size; ++i) {
		if( (head->row == (head+i)->row && head->col == (head+i)->col) )  {
			return 1;
		}
	}

	return 0;
}