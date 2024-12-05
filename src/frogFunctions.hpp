#pragma once

#include "customTypes.hpp"

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


void moveWithCar(MovingObject_t *frog, MovingObject_t *car, int boardWidth){
    if(car->direction == RIGHT && frog->position.x < boardWidth&& car->position.x > +  car->width - 3< boardWidth) frog->position.x = car->position.x + car->width;
    else if(car->direction == LEFT && frog->position.x >0 && car->position.x > 0) frog->position.x = car->position.x -1;
}


void moveFrog(MovingObject_t *frog, Direction *frogDir, int boardHeight, int boardWidth, chtype **board){
    if(*frogDir == STAY) return;
    switch(*frogDir){
        case UP:
            if(frog->position.y > 0 && board[frog->position.y-1][frog->position.x]!= 'L')frog->position.y -=1;
            break;
        case DOWN:
            if(frog->position.y <= boardHeight  && board[frog->position.y+1][frog->position.x]!= 'L') frog->position.y +=1;
            break;
        case RIGHT:
            if(frog->position.x <= boardWidth  && board[frog->position.y][frog->position.x+1]!= 'L')frog->position.x +=1;
            break;
        case LEFT:
            if(frog->position.x > 0  && board[frog->position.y][frog->position.x-1] != 'L')frog->position.x -=1;
            break;
        default:
            break;
        
    }
    *frogDir = STAY;
}

