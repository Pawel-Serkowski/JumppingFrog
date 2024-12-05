#pragma once

#include <ncurses.h>
#include <stdlib.h>

#include "customTypes.hpp"
#include "CONFIG.hpp"

#include "carFunctions.hpp"
#include "frogFunctions.hpp"
#include "windowFunctions.hpp"
#include "boardFunctions.hpp"
#include "statusbarFunctions.hpp"
#include "storkFunctions.hpp"
#include "recorderFunctions.hpp"

void getCarsFromSeed(FILE * seedFile,MovingObject_t **cars, int carsNumber,int boardWidth){
    for(int c = 0; c < carsNumber; c++){
        fseek(seedFile,SEEK_CUR,1);
        char carType;
        fscanf(seedFile,"%c",&carType);
        fseek( seedFile,SEEK_CUR,1);
        if(carType == 'B'){
            int height;
            int width;
            int posY;
            int posX;
            int velocity;
            char direction;

            fscanf(seedFile, "%d %d %d %d %d %c", &height, &width, &posY, &posX, &velocity, &direction);

            cars[c] = new MovingObject_t;
            initialBouncingCar(cars[c],(direction == 'R' ? RIGHT : LEFT),height,width,posY,posX,velocity);
            
            continue;
        }
        char direction;
        int posY;
        fscanf(seedFile,"%c",&direction);
        fscanf(seedFile,"%d",&posY);

        cars[c] = new MovingObject_t;
        initialRandomCar(cars[c],carType,(direction == 'R' ? RIGHT : LEFT),posY,(direction == 'R' ? 0 : boardWidth));
    }
}
bool getDataFromSeed(FrogGame_t *frogGame, char*filePath){
    FILE * seedFile = fopen(filePath,"r");
    Board_t board;
    MovingObject_t frog;

    if(seedFile == NULL){
        return false;
    }
    //getting board data
    fscanf(seedFile, "%d", &board.height);
    fscanf(seedFile, "%d", &board.width);
    chtype **gameBoard;
    char seedIcon;

    gameBoard = new chtype*[board.height];
    gameBoard[0] = new chtype[board.width];
    seedIcon = getc(seedFile);
    for(int j = 0;j < board.width;j++){
        seedIcon = getc(seedFile);
        if(seedIcon == SEED_GRASS_ICON){
            seedIcon = ROAD_ICON;
        }else{
            seedIcon = OBSTACLE_ICON;
        }
        gameBoard[0][j] = seedIcon;
    }
    for(int i = 1; i < board.height; i++){
        gameBoard[i] = new chtype[board.width];
        seedIcon = getc(seedFile);

        for(int j =0; j < board.width; j++){
            seedIcon = getc(seedFile);
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

    int carsNumber;
    fscanf(seedFile, " %d",&carsNumber);
    MovingObject_t **cars;
    cars = new MovingObject_t*[carsNumber];
    getCarsFromSeed(seedFile,cars,carsNumber,board.width);

    board.board = gameBoard;
    frogGame->gameBoard = board;
    frogGame->frog = frog;
    frogGame->cars = cars;
    frogGame->carsNumber = carsNumber;

    fclose(seedFile);
    return true;
}

void initializeGame(FrogGame_t *frogGame, char* seedPath){
    if(!getDataFromSeed(frogGame,seedPath)){
        frogGame->isSeedOkay = false;
        return;
    }
    frogGame->isSeedOkay=true;
    frogGame->isGameEnded = false;


    initializeBoard(&(frogGame->gameBoard));
    initializeStatsWindows(frogGame);
    initializeFrog(&(frogGame->frog));
    initializeStork(&(frogGame->stork),frogGame->gameBoard.height/SCALE_Y);
    initializeRecorder(frogGame->gameBoard.height,frogGame->gameBoard.width);
    frogGame->framesNumber = 0;
}


