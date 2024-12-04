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
    bool isGameEnded;
    int carsNumber;
    Board_t gameBoard;
    MovingObject_t frog;
    MovingObject_t **cars;
    WINDOW *stats_up_win;
    WINDOW *stats_bot_win;
    WINDOW *keyMenu;
};

struct Player_t{
    char nick[20];
    int points;
    int levelNumber;
};

struct RankingRecord_t{
    char name[20];
    int score;
};

struct Ranking_t{
    RankingRecord_t *rankingRecords;
    int numberOfRecords;
};

