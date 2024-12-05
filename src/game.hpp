#pragma once

#include <ncurses.h>
#include <unistd.h>

#include "customTypes.hpp"
#include "CONFIG.hpp"
#include "drawGame.hpp"

#include "frogFunctions.hpp"
#include "carFunctions.hpp"
#include "windowFunctions.hpp"
#include "statusbarFunctions.hpp"
#include "storkFunctions.hpp"

void doLogic(FrogGame_t *game){
    int realBoardHeight = (game->gameBoard.height)/SCALE_Y - 2*OFFSET;
    int realBoardwidth = (game->gameBoard.width)/SCALE_X - 2*OFFSET;

    moveFrog(&(game->frog),&(game->frog.direction), realBoardHeight, realBoardwidth, game->gameBoard.board);

    for(int c = 0; c < game->carsNumber; c++){
        moveCar(game->cars[c],realBoardwidth,game->gameBoard.board[game->cars[c]->position.y],game->frog);
    }
}


void isFrogOnFinishLine(FrogGame_t *frogGame){
    if(frogGame->frog.position.y == 0)
        frogGame->isGameEnded = true;
}


void moveFrogAndCarsTimer(FrogGame_t *frogGame){
    if(frogGame->frog.moveTimer > 0){
        frogGame->frog.moveTimer -= 1;
    }
    
    for(int c = 0; c < frogGame->carsNumber;  c++){
        if(frogGame->cars[c]->moveTimer > 0){
           frogGame->cars[c]->moveTimer -= 1;
        }
    }
}


void gameLoop(FrogGame_t *frogGame, Player_t *player){
    int time;
    int pointTime = POINT_DURATION;
    timeout(0);
    drawGame(*frogGame);
    bool isAccFriendlyCar = false;
    int accCarY = -1;
    while(true){
        chtype input = getch();
        if(input == 'q'){
            frogGame->frog.isAlive = false;
            frogGame->isGameEnded = false;
            player->points = -1;
            break;
        }
        if(frogGame->frog.moveTimer ==0){
            processInput(input,&(frogGame->frog.direction));
            if(input != ERR){
                frogGame->frog.moveTimer = FROG_JUMP_SPEED;
            }
        }

        doLogic(frogGame);

        moveFrogAndCarsTimer(frogGame);

        moveStork(&frogGame->stork,frogGame->frog);

        drawGame(*frogGame);
        refreshWindow(frogGame->gameBoard.board_win);

        isFrogOnFinishLine(frogGame);
        checkingCarsCollisions(frogGame,input,&accCarY,&isAccFriendlyCar,player);
        isFrogEaten(frogGame->stork,frogGame, player);

        updateStats(frogGame, player,time);

        if(frogGame->isGameEnded)break;
        if(pointTime == 0){
            player->points --;
            pointTime = POINT_DURATION;
        }
        time++;
        pointTime--;
        usleep(TICK_DURATION*1000);
    }
    timeout(-1);
}

