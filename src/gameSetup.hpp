#pragma once

#include <ncurses.h>
#include <fstream>

#include "customTypes.hpp"
#include "windowFunctions.hpp"
#include "CONFIG.hpp"
#include "carFunctions.hpp"

using namespace std;

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
                case SEED_OBSTACLE_ICON:
                    seedIcon = OBSTACLE_ICON;
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



void initializeFrog(MovingObject_t *frog){
    frog->icon=FROG_ICON;
    frog->width=1;
    frog->height=1;
    frog->colorNumber=FROG_COLOR_NUMBER;
    frog->isAlive = true;
    frog->type = 'F';
    frog->direction = STAY;
    frog->moveTimer = 0;
}

void initializeGame(FrogGame_t *frogGame){
    if(!getDataFromSeed(frogGame)){
        frogGame->isSeedOkay = false;
        return;
    }
    frogGame->isSeedOkay=true;

    initializeBoard(&(frogGame->gameBoard));
    initializeFrog(&(frogGame->frog));

    frogGame->carsNumber = 5;
    frogGame->cars = new MovingObject_t*[frogGame->carsNumber];

    MovingObject_t *car = new MovingObject_t;
    car->colorNumber = 3;
    car->height = 1;
    car->icon = CAR_ICON;
    car->position.x = 5;
    car->position.y = 1;
    car->velocity=10;
    car->width = 3;
    car->type = 'B';
    car->direction = RIGHT;
    car->initialWidth = 3;

    frogGame->cars[0] = car;


    MovingObject_t *car1 = new MovingObject_t;
    initialRandomCar(car1,LEFT,8,frogGame->gameBoard.width/SCALE_X);
    frogGame->cars[1] = car1;

    MovingObject_t *car2 = new MovingObject_t;
    initialRandomCar(car2,RIGHT,5);
    frogGame->cars[2] = car2;

    MovingObject_t *car3 = new MovingObject_t;
    initialRandomCar(car3,RIGHT,4);
    frogGame->cars[3] = car3;

    MovingObject_t *car4 = new MovingObject_t;
    initialRandomCar(car4,LEFT,2,frogGame->gameBoard.width/SCALE_X);
    frogGame->cars[4] = car4;


}


