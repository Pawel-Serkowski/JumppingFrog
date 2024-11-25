#pragma once

#include <ncurses.h>

#include "frogFunctions.hpp"
#include "customTypes.hpp"
#include "CONFIG.hpp"
#include "windowFunctions.hpp"

void processInput(WINDOW * board_win, Direction *frogDir ){
    chtype input = wgetch(board_win);
    wtimeout(board_win, FROG_TIMEOUT);

    switch(input){
        case KEY_UP:
        case 'w':
            *frogDir = UP;
            break;
        case KEY_DOWN:
        case 's':
            *frogDir = DOWN;
            break;
        case KEY_RIGHT:
        case 'd':
            *frogDir = RIGHT;
            break;
        case KEY_LEFT:
        case 'a':
            *frogDir = LEFT;
            break;
        case 'e':
            destroyGameWindow();
            break;
        default:
            *frogDir = STAY;
    }
}

void doLogic(FrogGame_t *game){
    int realBoardHeight = (game->gameBoard.height)/3 - 2*OFFSET;
    int realBoardwidth = (game->gameBoard.width)/3 - 2*OFFSET;
    moveFrog(&(game->frog),game->frogDirection, realBoardHeight, realBoardwidth);
}