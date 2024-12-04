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

void gameLoop(FrogGame_t *frogGame, Player_t *player){
    int time;
    int pointTime = POINT_DURATION;
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
        updateUpStats(frogGame->stats_up_win,frogGame->frog.isAlive, player->points);
        updateBotStats(frogGame->stats_bot_win,time/100,player->nick);

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

