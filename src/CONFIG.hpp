#pragma once

#include <ncurses.h>

#define ROAD_ICON ' '
#define GRASS_ICON '.'
#define FROG_ICON 'O'
#define CAR_ICON '#'
#define OBSTACLE_ICON 'L'

#define SEED_ROAD_ICON 'R'
#define SEED_GRASS_ICON 'G'
#define SEED_FROG_ICON 'F'
#define SEED_OBSTACLE_ICON 'L'

#define OFFSET 1 //distance beetween border and content
#define SCALE_X 2
#define SCALE_Y 2
#define FROG_JUMP_SPEED 10
#define TICK_DURATION 10

//car generate configurations
#define CAR_MAX_SPEED 5
#define CAR_MIN_SPEED 7
#define CAR_MIN_LENGTH 1
#define CAR_MAX_LENGTH 4

//game colors
#define CASUAL_COLOR_NUMBER 1 
#define CASUAL_COLOR COLOR_WHITE
#define FROG_COLOR_NUMBER 2
#define FROG_COLOR COLOR_GREEN
#define CAR_COLOR_NUMBER 3
#define CAR_COLOR COLOR_RED



