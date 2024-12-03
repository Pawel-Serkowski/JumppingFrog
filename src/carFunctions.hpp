#pragma once

#include "CONFIG.hpp"
#include "customTypes.hpp"
#include "utils.hpp"

void initialDefaultValues(MovingObject_t *car){
    car->colorNumber = CAR_COLOR_NUMBER;
    car->icon = CAR_ICON;
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

void initialRandomCar(MovingObject_t *car,Direction carDirection,int postionY, int initialPositionX=0 ){ 
    initialDefaultValues(car);
    car->width = 0;
    car->velocity = getRandomNumber(CAR_MAX_SPEED,CAR_MIN_SPEED);
    car->moveTimer = getRandomNumber(1,2) *car->velocity; //zmienić potem na random
    car->position.x = initialPositionX;
    car->position.y = postionY;
    car->initialWidth = getRandomNumber(CAR_MIN_LENGTH,CAR_MAX_LENGTH);
    car->height = 1;
    car->type = 'N'; //potem zrobić losowanie, na typy aut, ktre nie są bouncing
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
        }//dodanie warunku na to, zeby auto wyjedzało z lewej strony.
        newX += 1;
    }else{
        if(car->position.x - car->width == -1){
            car->width -= 1;
            if(car->width == 0)car->isAlive = false;
        }else if(car->initialWidth > car->width){
            car->width += 1;
        }
        newX -= 1;
    }

    
    car->position.x = newX;
    
}

void moveCar(MovingObject_t *car, int boardWidth, chtype *road){
    if(car->moveTimer != 0)return;
    switch(car->type){
        case 'B':
            moveBouncingCar(car,boardWidth,road);
            car->moveTimer = car->velocity;
            break;
        case 'N':
            moveNormalCar(car,boardWidth,road);
            break; 
    }
    if(car->velocity >= car->moveTimer)car->moveTimer = car->velocity;
    
}