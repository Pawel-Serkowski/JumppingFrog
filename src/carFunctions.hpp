#pragma once

#include <ncurses.h>

#include "CONFIG.hpp"
#include "customTypes.hpp"
#include "utils.hpp"

void initialDefaultValues(MovingObject_t *car,chtype carType='N'){
    car->colorNumber = carType == 'F' ? FRIENDLY_CAR_COLOR_NUMBER : CAR_COLOR_NUMBER;
    car->icon = carType == 'F' ? FRIENDLY_CAR_ICON : CAR_ICON;
    car->isAlive = true;
}

void initialBouncingCar(MovingObject_t *car, Direction carDirection, int height, int width, int posY, int posX, int velocity){
    initialDefaultValues(car);
    car->height = height;
    car->position.x = posX;
    car->position.y = posY;
    car->velocity=velocity;
    car->width = width;
    car->type = 'B';
    car->direction = carDirection;
    car->initialWidth = width;
}

void initialRandomCar(MovingObject_t *car, chtype carType ,Direction carDirection,int postionY, int initialPositionX=0){ 
    initialDefaultValues(car,carType);
    car->width = 0;
    car->velocity = getRandomNumber(CAR_MAX_SPEED,CAR_MIN_SPEED);
    car->moveTimer = getRandomNumber(1,2) *car->velocity; //zmienić potem na random
    car->position.x = initialPositionX;
    car->position.y = postionY;
    car->initialWidth = getRandomNumber(CAR_MIN_LENGTH,CAR_MAX_LENGTH);
    car->height = 1;
    car->type = carType;
    car->direction = carDirection;
}

void initialLastCar(MovingObject_t *car,int positionX = 0){
    car->isAlive = true;
    car->width = 0;
    car->velocity = getRandomNumber(CAR_MAX_SPEED,CAR_MIN_SPEED);
    car->moveTimer = getRandomNumber(1,2) *car->velocity; //zmienić potem na random
    car->position.x = positionX;
    car->initialWidth = getRandomNumber(CAR_MIN_LENGTH,CAR_MAX_LENGTH);
}

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


void moveNormalCar(MovingObject_t *car, int boardWidth, chtype *road){
    if(car->isAlive == false){
        initialLastCar(car, car->direction == RIGHT ? 0 : boardWidth+2);
        return;
    }
    int newX = car->position.x;
    if(car->direction == RIGHT){
        if(car->position.x+car->width-2 >= boardWidth){
            car->width -= (car->position.x+car->width) - boardWidth-1;
            if(car->width == 0)car->isAlive = false;
        }else if(car->initialWidth > car->width){
            car->width += 1;
            return;
        }
        newX += 1;
    }else{
        if(car->position.x - car->width <= 0 && car->position.x == 0){
            car->width -= 1;
            if(car->width == 0)car->isAlive = false;
            return;
        }else if(car->initialWidth > car->width){
            car->width += 1;
            
        }
        newX -= 1;
        
    }

    
    car->position.x = newX;
}

void moveStoppingCar(MovingObject_t *car,int boardWidth, chtype*road, MovingObject_t frog){
    if(car->direction == RIGHT && (frog.position.y == car->position.y+1 || frog.position.y == car->position.y) && frog.position.x == car->position.x+car->width){
        return;
    }else if(car->direction == LEFT && (frog.position.y == car->position.y+1 || frog.position.y == car->position.y) && frog.position.x == car->position.x-1){
        return;
    }

    moveNormalCar(car,boardWidth,road);
}

void moveFriendlyCar(MovingObject_t *car,int boardWidth, chtype*road, MovingObject_t frog){
    bool isFrogTouched = false;
    if(car->direction == RIGHT && frog.position.y == car->position.y && frog.position.x == car->position.x+car->width){
        isFrogTouched = true;
        if(car->position.x+car->width-1== boardWidth )return;
        
    }else if(car->direction == LEFT && frog.position.y == car->position.y && frog.position.x == car->position.x-1){
        isFrogTouched = true;
        if(car->position.x== 1 )return;
    }
    moveNormalCar(car,boardWidth,road);
}

void moveCar(MovingObject_t *car, int boardWidth, chtype *road, MovingObject_t frog){
    if(car->moveTimer != 0)return;
    switch(car->type){
        case 'B':
            moveBouncingCar(car,boardWidth,road);
            car->moveTimer = car->velocity;
            break;
        case 'N':
            moveNormalCar(car,boardWidth,road);
            break; 
        case 'S':
            moveStoppingCar(car, boardWidth, road, frog);
            break;
        case 'F':
            moveFriendlyCar(car,boardWidth,road,frog);
            break;
    }
    if(car->velocity >= car->moveTimer)car->moveTimer = car->velocity;
    
}

bool isCollisionWithCar(MovingObject_t *car, MovingObject_t frog){
    for(int h = 0; h <car->height; h++){
        for(int w = 0; w < car->width; w++){
            if(frog.position.x == (car->position.x+w) && frog.position.y == (car->position.y+h) )return true;
        }
    }
    return false;

}

bool isCarAccepted(MovingObject_t *car, MovingObject_t frog){
    if(car->position.y == frog.position.y && frog.position.x >= car->position.x && frog.position.x <= car->position.x+car->width){
        return true;
    } 
    return false;
}