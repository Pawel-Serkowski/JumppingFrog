#pragma once

#include <ncurses.h>

#include "CONFIG.hpp"
#include "windowFunctions.hpp"
#include "customTypes.hpp"
#include "drawGame.hpp"

void initializeStatsWindows(FrogGame_t *frogGame){
    frogGame->stats_up_win = newwin(STATS_WINDOW_HEIGHT,frogGame->gameBoard.width+(2*OFFSET),frogGame->gameBoard.startRow-STATS_WINDOW_HEIGHT-1, frogGame->gameBoard.startCol-OFFSET);

    frogGame->stats_bot_win = newwin(3*STATS_WINDOW_HEIGHT,frogGame->gameBoard.width+(2*OFFSET),frogGame->gameBoard.startRow+frogGame->gameBoard.height+1, frogGame->gameBoard.startCol-OFFSET);

    refreshWindow(frogGame->stats_up_win);
    refreshWindow(frogGame->stats_bot_win);
}


void updateUpStats(WINDOW * window, bool isAlive, int points){
    int width;
    width = getmaxx(window);

    mvwprintw(window,0,0,"Points: %d",points);

    wattron(window,COLOR_PAIR(isAlive ? FROG_COLOR_NUMBER : CAR_COLOR_NUMBER));
    mvwprintw(window,0,width-5,"%5s",(isAlive ? "Alive" : "Dead"));
    wattroff(window,COLOR_PAIR(isAlive ? FROG_COLOR_NUMBER : CAR_COLOR_NUMBER));

    refreshWindow(window);
} 

void updateBotStats(WINDOW *window, int timeSeconds, char*nick){
    int width;
    width = getmaxx(window);

    mvwprintw(window,0,width-6,"%5ds",timeSeconds);
    mvwprintw(window,0,0,"%s",nick);

    refreshWindow(window);
}