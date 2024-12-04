#pragma once

#include <ncurses.h>
#include "customTypes.hpp"
#include "CONFIG.hpp"
#include "windowFunctions.hpp"

void initializeBoardWindow(WINDOW *board_win){
    addBorder(board_win);
}

void initializeBoard(Board_t *gameBoard){
    gameBoard->height *= SCALE_Y;
    gameBoard->width *= SCALE_X;

    int xMax, yMax;
    getmaxyx(stdscr,yMax,xMax);
    gameBoard->startRow = ((yMax/2)-(gameBoard->height/2));
    gameBoard->startCol = ((xMax/2)-(gameBoard->width/2));

    gameBoard->board_win = newwin(gameBoard->height+(2*OFFSET),gameBoard->width+(2*OFFSET),gameBoard->startRow-1,gameBoard->startCol-1);

    initializeBoardWindow(gameBoard->board_win);
    refreshWindow(gameBoard->board_win);
}
