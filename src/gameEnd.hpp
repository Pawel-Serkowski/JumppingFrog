#pragma once

#include <ncurses.h>

#include "customTypes.hpp"
#include "CONFIG.hpp"

void destroyBoard(Board_t *board){
    for(int i = 0; i < board->height; i++){
        delete board->board[i];
    }
    delete board->board;

    delwin(board->board_win);
}

void destroyCars(MovingObject_t **cars, int numberOfCars){
    for(int i = 0; i < numberOfCars; i++){
        delete cars[i];
    }
    delete cars;
}


void destroyGame(FrogGame_t *frogGame){
    delwin(frogGame->stats_up_win);
    delwin(frogGame->stats_bot_win);
    destroyBoard(&frogGame->gameBoard);
    destroyCars(frogGame->cars,frogGame->carsNumber);
}