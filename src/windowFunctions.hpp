#pragma once

#include <ncurses.h>
#include <iostream>

#include "CONFIG.hpp"

void initColors(){
    init_pair(CASUAL_COLOR_NUMBER,CASUAL_COLOR,-1);
    init_pair(FROG_COLOR_NUMBER,FROG_COLOR,-1);
    init_pair(CAR_COLOR_NUMBER,CAR_COLOR,-1);
    init_pair(FINISH_LINE_BLACK_COLOR_NUMBER,CASUAL_COLOR,FINISH_LINE_BLACK_COLOR);
    init_pair(FINISH_LINE_WHITE_COLOR_NUMBER,FINISH_LINE_BLACK_COLOR,CASUAL_COLOR);
    init_pair(FRIENDLY_CAR_COLOR_NUMBER,FRIENDLY_CAR_COLOR,-1);
    init_pair(STORK_COLOR_NUMBER,STORK_COLOR,-1);
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
}

void destroyGameWindow(){
    endwin();
    std::cout << "thanks for playing froggy game :)" << "\n";
    exit(0);

}

void addBorder(WINDOW *board_win){
    box(board_win,0,0);
}

void refreshWindow(WINDOW *win){
    wrefresh(win);
}

char endWindow(WINDOW *win, int width, int height, char* endText, int textLength, bool moreLevel, int points){
    wclear(win);
    int startY = height / 2;     
    int startX = (width - textLength) / 2;
    
    mvwprintw(win,startY,startX,"%s",endText);
    if(points > 0)mvwprintw(win,startY+2,startX,"Your points: %d", points);
    mvwprintw(win,startY+3,startX,"%s", "q - quit game");
    mvwprintw(win,startY+4,startX,"%s", "r - replay");
    if(moreLevel)mvwprintw(win,startY+5,startX,"%s", "press any key to continue");

    addBorder(win);
    wrefresh(win);
    timeout(-1);
    return getch();
}