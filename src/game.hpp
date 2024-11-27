#pragma once

#include <ncurses.h>
#include <unistd.h>

#include "frogFunctions.hpp"
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
    int realBoardHeight = (game->gameBoard.height)/3 - 2*OFFSET;
    int realBoardwidth = (game->gameBoard.width)/3 - 2*OFFSET;
    moveFrog(&(game->frog),&(game->frogDirection), realBoardHeight, realBoardwidth);
}

void gameLoop(FrogGame_t *frogGame){
    int frog_timer = 0;

    drawGame(*frogGame);
    while(true){
        chtype input = getch();
        if(input == 'q')break;
        if(frog_timer ==0){
            processInput(input,&(frogGame->frogDirection));
            if(input != ERR){
                frog_timer = FROG_JUMP_SPEED;
            }
        }

        doLogic(frogGame);

        if(frog_timer > 0){
            frog_timer -= 1;
        }


        drawGame(*frogGame);
        refreshWindow(frogGame->gameBoard.board_win);

        usleep(TICK_DURATION*1000);
    }
}

