#include <ncurses.h>

#include "customTypes.hpp"
#include "CONFIG.hpp"

void drawAt(WINDOW *window, int y, int x, chtype icon, int colorPairNumber=CASUAL_COLOR_NUMBER){
    mvwaddch(window,y+OFFSET,x+OFFSET,icon | COLOR_PAIR(colorPairNumber));
}

void drawScaleIcon(WINDOW *window,int row, int col, chtype icon, int colorPairNumber = CASUAL_COLOR_NUMBER){
    int actualX, actualY;
    for(int sy = 0; sy < SCALE_Y; sy++){
        for(int sx = 0; sx < SCALE_X; sx++){
            actualY = (row * SCALE_Y) + sy;
            actualX = (col * SCALE_X) + sx;
            drawAt(window,actualY,actualX,icon,colorPairNumber);
        }
    }
}

void drawEntity(WINDOW *window, MovingObject_t entity){
    for(int i = 0; i < entity.height; i++){
        for(int j = 0; j < entity.width; j++){
            drawScaleIcon(window,entity.position.y-i, entity.position.x+j,entity.icon,entity.colorNumber);
        }
    }

}

void drawBoard(Board_t gameBoard){
    int normalHeight = gameBoard.height/SCALE_Y;
    int normalWidth = gameBoard.width/SCALE_X;


    //drawing terrain
    for(int row = 0; row < normalHeight; row++){
        for(int col = 0; col < normalWidth; col++){
            drawScaleIcon(gameBoard.board_win,row,col, gameBoard.board[row][col]);
        }
    }
}

void drawGame(FrogGame_t frogGame){
    drawBoard(frogGame.gameBoard);


    drawEntity(frogGame.gameBoard.board_win, frogGame.frog); //drawing Frog
}