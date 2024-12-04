#pragma once

#include <ncurses.h>

#define ROAD_ICON ' '
#define GRASS_ICON '.'
#define FROG_ICON 'O'
#define CAR_ICON '#'
#define FRIENDLY_CAR_ICON 'F'
#define OBSTACLE_ICON 'L'

#define SEED_ROAD_ICON 'R'
#define SEED_GRASS_ICON 'G'
#define SEED_FROG_ICON 'F'
#define SEED_OBSTACLE_ICON 'L'

//size definition
#define OFFSET 1 //distance beetween border and content
#define SCALE_X 2
#define SCALE_Y 2
#define STATS_WINDOW_HEIGHT 1

//time definition
#define FROG_JUMP_SPEED 10
#define TICK_DURATION 10
#define POINT_DURATION 10

//car generate configurations
#define CAR_MAX_SPEED 5
#define CAR_MIN_SPEED 7
#define CAR_MIN_LENGTH 1
#define CAR_MAX_LENGTH 5

//game colors
#define CASUAL_COLOR_NUMBER 1 
#define CASUAL_COLOR COLOR_WHITE
#define FROG_COLOR_NUMBER 2
#define FROG_COLOR COLOR_GREEN
#define CAR_COLOR_NUMBER 3
#define CAR_COLOR COLOR_RED
#define FINISH_LINE_BLACK_COLOR_NUMBER 4
#define FINISH_LINE_BLACK_COLOR COLOR_BLACK
#define FINISH_LINE_WHITE_COLOR_NUMBER 5
//---
#define FRIENDLY_CAR_COLOR_NUMBER 6
#define FRIENDLY_CAR_COLOR COLOR_MAGENTA
