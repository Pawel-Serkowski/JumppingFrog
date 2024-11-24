#pragma once

#include <ncurses.h>

struct MovingObject_t{
    struct {
        int x;
        int y;
    } position;
    int height;
    int width;
    int velocity;
    int colorNumber;
    chtype icon;
};

struct Board_t{
    WINDOW *board_win;
    int height;
    int width;
    int startRow;
    int startCol;
    bool isGood;
    int frogInitY;
    int frogInitX;
    chtype **board;
};

struct FrogGame_t 
{
    bool isFrogAlive;
    bool isSeedOkay;
    Board_t gameBoard;
    MovingObject_t frog;
};
