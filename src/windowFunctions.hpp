#pragma once

#include <ncurses.h>

void addBorder(WINDOW *board_win){
    box(board_win,0,0);
}

void refreshWindow(WINDOW *board_win){
    wrefresh(board_win);
}

void destroyGame(chtype**gameBoard){
    delete gameBoard;
}