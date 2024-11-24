#pragma once

#include <ncurses.h>
#include <fstream>

#include "customTypes.hpp"
#include "CONFIG.hpp"

using namespace std;

void initColors(){
    init_pair(CASUAL_COLOR_NUMBER,CASUAL_COLOR,-1);
    init_pair(FROG_COLOR_NUMBER,FROG_COLOR,-1);
}

bool getDataFromSeed(FrogGame_t *frogGame){
    ifstream seedFile("./seeds/default.txt");
    Board_t board;
    MovingObject_t frog;

    if(!seedFile.is_open()){
        return false;
    }
    
    //getting board data
    seedFile >> board.height >> board.width;
    chtype **gameBoard;
    char seedIcon;

    gameBoard = new chtype*[board.height];
    for(int i = 0; i < board.height; i++){
        gameBoard[i] = new chtype[board.width];
        seedFile.get(seedIcon);
        for(int j =0; j < board.width; j++){
            seedFile.get(seedIcon);
            switch(seedIcon){
                case SEED_GRASS_ICON:
                    seedIcon = GRASS_ICON;
                    break;
                case SEED_ROAD_ICON:
                    seedIcon = ROAD_ICON;
                    break;
                case SEED_FROG_ICON:
                    seedIcon = GRASS_ICON;
                    frog.position.x = j;
                    frog.position.y = i;
                    break;
                default:
                    seedIcon = '?';
            }
            gameBoard[i][j] = seedIcon;
        }
    }

    board.board = gameBoard;
    frogGame->gameBoard = board;
    frogGame->frog = frog;

    seedFile.close();
    return true;
}

void initializeBoard(Board_t *gameBoard){
    gameBoard->height *= SCALE_Y;
    gameBoard->width *= SCALE_X;

    int xMax, yMax;
    getmaxyx(stdscr,yMax,xMax);
    gameBoard->startRow = ((yMax/2)-(gameBoard->height/2));
    gameBoard->startCol = ((xMax/2)-(gameBoard->width/2));

    gameBoard->board_win = newwin(gameBoard->height+(2*OFFSET),gameBoard->width+(2*OFFSET),gameBoard->startRow-1,gameBoard->startCol-1);
}

void initializeFrog(MovingObject_t *frog){
    frog->icon=FROG_ICON;
    frog->width=1;
    frog->height=1;
    frog->colorNumber=FROG_COLOR_NUMBER;
}

void initializeGame(FrogGame_t *frogGame){
    if(!getDataFromSeed(frogGame)){
        frogGame->isSeedOkay = false;
        return;
    }
    frogGame->isSeedOkay=true;
    initializeBoard(&(frogGame->gameBoard));
    initializeFrog(&(frogGame->frog));

}


