#include <ncurses.h>

//gameboard type

struct MovingObject_t{
    struct {
        int x;
        int y;
    } position;
    int height;
    int width;
    int velocity;
    chtype icon;
};



struct Board_t{
    WINDOW *board_win;
    int height;
    int width;
    int startRow;
    int startCol;
    bool isGood;
    int scaleX;
    int scaleY;
    int frogInitY;
    int frogInitX;
    chtype **board;
};

struct FrogGame_t 
{
    bool isFrogAlive;
    Board_t gameBoard;
    MovingObject_t frog;
};
