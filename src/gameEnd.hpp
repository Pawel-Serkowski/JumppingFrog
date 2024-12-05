#pragma once

#include <ncurses.h>

#include "customTypes.hpp"
#include "CONFIG.hpp"
#include "recorderFunctions.hpp"

void destroyBoard(Board_t *board){
    for(int i = 0; i < board->height; i++){
        delete board->board[i];
    }
    delete []board->board;

    delwin(board->board_win);
}


void destroyCars(MovingObject_t **cars, int numberOfCars){
    for(int i = 0; i < numberOfCars; i++){
        delete cars[i];
    }
    delete []cars;
}


void destroyGame(FrogGame_t *frogGame){
    delwin(frogGame->stats_up_win);
    delwin(frogGame->stats_bot_win);
    destroyBoard(&frogGame->gameBoard);
    destroyCars(frogGame->cars,frogGame->carsNumber);
}


void endLoseWindow(FrogGame_t *frogGame, Ranking_t *ranking){
    char message[] = "You are dead\0";
        int textLength = sizeof(message)/sizeof(char);
        char option = endWindow(frogGame->gameBoard.board_win,frogGame->gameBoard.width, frogGame->gameBoard.height, message, textLength,false,0);
        if(option == 'r'){
            char text1[] ={"press any key"} ;
            char text2[] ={"to leave the game"} ;
        showRecorderHandler(*frogGame, CAR_COLOR_NUMBER, text1, text2 );
    }
    destroyGame(frogGame);
}


char endWinWindow(FrogGame_t frogGame, Player_t player, int levelsNumber){
    char message[] = "You passed the level\0";
    int textLength = sizeof(message)/sizeof(char);
    char option = endWindow(frogGame.gameBoard.board_win,frogGame.gameBoard.width, frogGame.gameBoard.height, message, textLength,levelsNumber-player.levelNumber,player.points);
    return option;
}