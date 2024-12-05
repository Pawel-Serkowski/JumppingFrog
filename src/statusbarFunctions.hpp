#pragma once

#include <ncurses.h>

#include "CONFIG.hpp"
#include "windowFunctions.hpp"
#include "customTypes.hpp"
#include "drawGame.hpp"
#include "recorderFunctions.hpp"

void initializeStatsWindows(FrogGame_t *frogGame){
    frogGame->stats_up_win = newwin(STATS_WINDOW_HEIGHT+1,frogGame->gameBoard.width+(2*OFFSET),frogGame->gameBoard.startRow-STATS_WINDOW_HEIGHT-2, frogGame->gameBoard.startCol-OFFSET);

    frogGame->stats_bot_win = newwin(4*STATS_WINDOW_HEIGHT,frogGame->gameBoard.width+(2*OFFSET),frogGame->gameBoard.startRow+frogGame->gameBoard.height+1, frogGame->gameBoard.startCol-OFFSET);

    refreshWindow(frogGame->stats_up_win);
    refreshWindow(frogGame->stats_bot_win);
}


void updateUpStats(WINDOW * window, bool isAlive, int points, int level){
    int width;
    width = getmaxx(window);

    mvwprintw(window,1,0,"Points: %i ",points);

    wattron(window,COLOR_PAIR(isAlive ? FROG_COLOR_NUMBER : CAR_COLOR_NUMBER));
    mvwprintw(window,1,width-5,"%5s",(isAlive ? "Alive" : "Dead"));
    wattroff(window,COLOR_PAIR(isAlive ? FROG_COLOR_NUMBER : CAR_COLOR_NUMBER));
    mvwprintw(window,0,0,"level: %d",level);

    refreshWindow(window);
} 


void updateBotStats(WINDOW *window, int timeSeconds, char*nick){
    int width;
    width = getmaxx(window);

    mvwprintw(window,0,width-6,"%5ds",timeSeconds);
    mvwprintw(window,0,0,"%s",nick);

    wattron(window,COLOR_PAIR(FRIENDLY_CAR_COLOR_NUMBER));
    mvwprintw(window,2,0,"%s","Game made by s203389");
    mvwprintw(window,3,0,"%s","~ Pawel Serkowski");
    wattroff(window,COLOR_PAIR(FRIENDLY_CAR_COLOR_NUMBER));

    refreshWindow(window);
}


void updateStats(FrogGame_t *frogGame, Player_t *player, int time){
    updateUpStats(frogGame->stats_up_win,frogGame->frog.isAlive, player->points, player->levelNumber);
    updateBotStats(frogGame->stats_bot_win,time/100,player->nick);
    recordToFile(frogGame->gameBoard.board_win,frogGame->gameBoard.height,frogGame->gameBoard.width);
    frogGame->framesNumber++;
}