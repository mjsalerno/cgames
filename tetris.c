#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#define BLOCK ((char) 0x2588)

typedef struct Tetpiece Piece;

struct Tetpiece {
    int xone;
    int xtwo;
    int xthree;
    int xfour;

    int yone;
    int ytwo;
    int ythree;
    int yfour;
};


Piece *buildpiece(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void drawpiece(int startx, int starty, Piece *p);

int main() {

    Piece *one = buildpiece(0,0,0,1,1,0,1,1);
    Piece *two = buildpiece(0,0,0,1,0,2,1,1);

    initscr();

    drawpiece(0,0,one);
    drawpiece(0,3,two);

    refresh();
    getch();
    endwin();

    return 0;
}

Piece *buildpiece(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4) {
    Piece * p = malloc(sizeof(Piece));
    p->xone = x1;
    p->yone = y1;
    p->xtwo = x2;
    p->ytwo = y2;
    p->xthree = x3;
    p->ythree = y3;
    p->xfour = x4;
    p->yfour = y4;

    return p;
}

void drawpiece(int startx, int starty, Piece *p) {
    mvaddch(p->xone   + startx, p->yone   + starty, BLOCK);
    mvaddch(p->xtwo   + startx, p->ytwo   + starty, BLOCK);
    mvaddch(p->xthree + startx, p->ythree + starty, BLOCK);
    mvaddch(p->xfour  + startx, p->yfour  + starty, BLOCK);
}