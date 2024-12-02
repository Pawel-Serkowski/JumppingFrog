#pragma once

#include <ncurses.h>
#include <unistd.h>

#include "frogFunctions.hpp"
#include "carFunctions.hpp"
#include "customTypes.hpp"
#include "CONFIG.hpp"
#include "windowFunctions.hpp"
#include "drawGame.hpp"

void processInput(chtype input, Direction *frogDirection){
    if(input == KEY_UP || input == 'w'){
        *frogDirection = UP;
    }else if(input == KEY_DOWN || input == 's'){
        *frogDirection = DOWN;  
    }else if(input == KEY_RIGHT || input == 'd'){
        *frogDirection = RIGHT;
    }
    else if(input == KEY_LEFT || input =='a'){
        *frogDirection = LEFT;
    }
}

void doLogic(FrogGame_t *game){
    int realBoardHeight = (game->gameBoard.height)/SCALE_Y - 2*OFFSET;
    int realBoardwidth = (game->gameBoard.width)/SCALE_X - 2*OFFSET;

    moveFrog(&(game->frog),&(game->frog.direction), realBoardHeight, realBoardwidth);

    for(int c = 0; c < game->carsNumber; c++){
        moveCar(game->cars[c],realBoardwidth,game->gameBoard.board[game->cars[c]->position.y]);
    }
}

void gameLoop(FrogGame_t *frogGame){
    MovingObject_t frog = frogGame->frog;

    drawGame(*frogGame);
    while(true){
        chtype input = getch();
        if(input == 'q')break;
        if(frog.moveTimer ==0){
            processInput(input,&(frogGame->frog.direction));
            if(input != ERR){
                frog.moveTimer = FROG_JUMP_SPEED;
            }
        }

        doLogic(frogGame);

        if(frog.moveTimer > 0){
            frog.moveTimer -= 1;
        }
        for(int c = 0; c < frogGame->carsNumber;  c++){
            if(frogGame->cars[c]->moveTimer > 0){
                frogGame->cars[c]->moveTimer -= 1;
            }
        }


        drawGame(*frogGame);
        refreshWindow(frogGame->gameBoard.board_win);

        usleep(TICK_DURATION*1000);
    }
}

