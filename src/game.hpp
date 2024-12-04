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
        moveCar(game->cars[c],realBoardwidth,game->gameBoard.board[game->cars[c]->position.y],game->frog);
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
    bool isAccFriendlyCar = false;
    int accCarY = -1;
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
            if(input == KEY_UP  || input == 'w'){
                if(frogGame->cars[c]->type == FRIENDLY_CAR_ICON && isCarAccepted(frogGame->cars[c],frogGame->frog)){
                    isAccFriendlyCar = true;
                    accCarY = frogGame->cars[c]->position.y;
                }
                else if(frogGame->cars[c]->position.y == accCarY){
                        isAccFriendlyCar = false;
                        mvaddch(0,0,'1');
                }

            }else if(input == ERR){
                isAccFriendlyCar = isAccFriendlyCar;
            }else{
                isAccFriendlyCar = false;
                accCarY = -1;
                mvaddch(0,0,'2');
            }
            
            if(isCollisionWithCar(frogGame->cars[c],frogGame->frog)){
                if(isAccFriendlyCar){
                    moveWithCar(&frogGame->frog,frogGame->cars[c],frogGame->gameBoard.width/SCALE_X);
                }else{
                    frogGame->isGameEnded = true;
                    frogGame->frog.isAlive = false;
                }

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

