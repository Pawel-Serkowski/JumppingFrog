#pragma once

#include "CONFIG.hpp"
#include "customTypes.hpp"

void initializeStork(MovingObject_t *stork, int boardHeight){
    stork->position.x = 0;
    stork->position.y = boardHeight+1;
    stork->icon = STORK_ICON;
    stork->colorNumber = STORK_COLOR_NUMBER;
    stork->velocity = STORK_SPEED;
    stork->moveTimer = 4*stork->velocity;
    stork->direction = STAY;
    stork->width = 1;
    stork->height = 1;
    stork->isAlive = true;
}

void moveStork(MovingObject_t *stork, MovingObject_t frog){
    if(stork->moveTimer >0)
    {
        stork->moveTimer--;
        return;
    }            
    int addX = 0;
    int addY = 0;

    if(frog.position.y > stork->position.y)addY++;
    else if(frog.position.y < stork->position.y)addY--;

    if(frog.position.x > stork->position.x)addX++;
    else if(frog.position.x < stork->position.x)addX--;

    stork->position.x += addX;
    stork->position.y += addY;

    stork->moveTimer = stork->velocity;
}

bool isFrogEaten(MovingObject_t stork, MovingObject_t frog){
    return (stork.position.x == frog.position.x)&&(stork.position.y == frog.position.y);
}