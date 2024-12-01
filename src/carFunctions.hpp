#pragma once

#include "CONFIG.hpp"
#include "customTypes.hpp"

void moveBouncingCar(MovingObject_t *car, int boardWidth, chtype *road){
    int newX = car->position.x;
    if(car->direction == RIGHT){
        newX += 1;
        if(car->position.x+car->width-1== boardWidth || road[newX+car->width] == OBSTACLE_ICON ){
            car->direction = LEFT;
        }
        
        car->position.x = newX;
        return;
    }
    newX -= 1;
    if(newX < 0){
        car->position.x = 1;
        return;
    }
    if(newX == 0 || road[newX-1] == OBSTACLE_ICON){
        car->direction = RIGHT;
    }
    car->position.x = newX;
}

void moveCar(MovingObject_t *car, int boardWidth, chtype *road){
    if(car->moveTimer != 0)return;
    switch(car->type){
        case 'B':
            moveBouncingCar(car,boardWidth,road);
        default:
            car->moveTimer = car->velocity;
    }
}