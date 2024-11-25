#pragma once

#include "customTypes.hpp"

void moveFrog(MovingObject_t *frog, Direction frogDir, int boardHeight, int boardWidth){
    if(frogDir == STAY) return;
    switch(frogDir){
        case UP:
            if(frog->position.y > 0)frog->position.y -=1;
            break;
        case DOWN:
            if(frog->position.y <= boardHeight) frog->position.y +=1;
            break;
        case RIGHT:
            if(frog->position.x <= boardWidth)frog->position.x +=1;
            break;
        case LEFT:
            if(frog->position.x > 0)frog->position.x -=1;
            break;
        default:
            break;
        
    }

}