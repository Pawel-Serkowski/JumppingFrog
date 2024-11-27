#pragma once

#include <ncurses.h>
#include <iostream>

#include "CONFIG.hpp"

void initColors(){
    init_pair(CASUAL_COLOR_NUMBER,CASUAL_COLOR,-1);
    init_pair(FROG_COLOR_NUMBER,FROG_COLOR,-1);
}

void initializeGameWindow(){
    initscr();
    refresh();
    noecho(); 
    curs_set(0);
    start_color();
    use_default_colors();
    initColors();
    keypad(stdscr,true);
    timeout(0);
}

void destroyGameWindow(){
    getch();
    endwin();
    std::cout << "thanks for playing froggy game :)" << "\n";
    getch();
    exit(0);

}

void addBorder(WINDOW *board_win){
    box(board_win,0,0);
}

void refreshWindow(WINDOW *board_win){
    wrefresh(board_win);
}

void destroyGame(chtype**gameBoard){
    delete gameBoard;
}