#pragma once

#include <ncurses.h>

enum Direction{
    STAY,
    UP,
    DOWN ,
    LEFT,
    RIGHT,
};

struct MovingObject_t{
    bool isAlive;
    struct {
        int x;
        int y;
    } position;
    int height;
    int width;
    int initialWidth;
    int velocity;
    int colorNumber;
    int moveTimer;
    chtype icon;
    chtype type;
    Direction direction;
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
    bool isSeedOkay;
    Board_t gameBoard;
    MovingObject_t frog;
    int carsNumber;
    MovingObject_t **cars;
};

