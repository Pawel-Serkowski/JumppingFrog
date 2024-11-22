#include <ncurses.h>

//gameboard type
struct Board_t 
{
    WINDOW *board_win;
    int height;
    int width;
    int startRow;
    int startCol;
    int scaleX;
    int scaleY;
    bool isGood;
    chtype **board;
};
