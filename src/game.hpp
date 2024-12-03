#pragma once

#include <ncurses.h>
#include <unistd.h>

#include "frogFunctions.hpp"
#include "carFunctions.hpp"
#include "customTypes.hpp"
#include "CONFIG.hpp"
#include "windowFunctions.hpp"
#include "drawGame.hpp"

void doLogic(FrogGame_t *game){
    int realBoardHeight = (game->gameBoard.height)/SCALE_Y - 2*OFFSET;
    int realBoardwidth = (game->gameBoard.width)/SCALE_X - 2*OFFSET;

    moveFrog(&(game->frog),&(game->frog.direction), realBoardHeight, realBoardwidth, game->gameBoard.board);

    for(int c = 0; c < game->carsNumber; c++){
        moveCar(game->cars[c],realBoardwidth,game->gameBoard.board[game->cars[c]->position.y]);
    }
}

bool isFrogOnFinishLine(MovingObject_t frog){
    return frog.position.y == 0;
}

void gameLoop(FrogGame_t *frogGame){
    timeout(0);
    drawGame(*frogGame);
    while(true){
        chtype input = getch();
        if(input == 'q')break;
        if(frogGame->frog.moveTimer ==0){
            processInput(input,&(frogGame->frog.direction));
            if(input != ERR){
                frogGame->frog.moveTimer = FROG_JUMP_SPEED;
            }
        }

        doLogic(frogGame);

        if(frogGame->frog.moveTimer > 0){
            frogGame->frog.moveTimer -= 1;
        }
        for(int c = 0; c < frogGame->carsNumber;  c++){
            if(frogGame->cars[c]->moveTimer > 0){
                frogGame->cars[c]->moveTimer -= 1;
            }
        }


        drawGame(*frogGame);
        refreshWindow(frogGame->gameBoard.board_win);

        if(isFrogOnFinishLine(frogGame->frog)){
            frogGame->isGameEnded = true;
        }
        for(int c = 0; c < frogGame->carsNumber;  c++){
            if(isCollisionWithCar(frogGame->cars[c],frogGame->frog)){
                frogGame->isGameEnded = true;
                frogGame->frog.isAlive = false;
            }
        }
        if(frogGame->isGameEnded)break;

        usleep(TICK_DURATION*1000);
    }
}

