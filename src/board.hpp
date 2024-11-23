#pragma once

#include <ncurses.h>
#include <fstream>

#include "customTypes.hpp"
#include "CONFIG.hpp"

using namespace std;

void addBorder(WINDOW *board_win){
    box(board_win,0,0);
}

void refreshWindow(WINDOW *board_win){
    wrefresh(board_win);
}

void destroyBoard(chtype**gameBoard){
    delete gameBoard;
}

Board_t getDataFromSeed(){
    ifstream seedFile("./seeds/default.txt");
    Board_t board;
    char seedIcon;

    if(!seedFile.is_open()){
        return board;
    }

    int boardHeight;
    int boardWidth;
    seedFile >> boardHeight >> boardWidth;

    chtype **gameBoard;
    gameBoard = new chtype*[boardHeight];

    for(int i = 0; i < boardHeight; i++){
        gameBoard[i] = new chtype[boardWidth];
        seedFile.get(seedIcon);
        for(int j = 0; j < boardWidth; j++){
            seedFile.get(seedIcon);
            switch(seedIcon){
                case SEEDROADICON:
                    seedIcon = ROADICON;
                    break;
                case SEEDGRASSICON:
                    seedIcon = GRASSICON;
                    break;
                case SEEDFROGICON:
                    seedIcon = GRASSICON;
                    board.frogInitX = j;
                    board.frogInitY = i;
                    break;
                default:
                    seedIcon = '?';
                    
            }
            gameBoard[i][j] = seedIcon;
            
        }
    }

    board.height = boardHeight;
    board.width = boardWidth;
    board.board = gameBoard;

    board.isGood = true;
    return board;


}

Board_t initializeBoard(int scaleY = 1,int scaleX = 1){
    Board_t board = getDataFromSeed();
    if(board.isGood == false){
        return board;
    }
    board.scaleY = scaleY;
    board.scaleX = scaleX;

    board.height *= scaleY;
    board.width *= scaleX;

    int xMax,yMax;
    getmaxyx(stdscr,yMax,xMax);
    board.startRow = ((yMax/2)-(board.height/2));
    board.startCol = ((xMax/2)-(board.width/2));

    board.board_win = newwin(board.height+2*OFFSET,board.width+2*OFFSET,board.startRow-1,board.startCol-1);

    return board;
}

void drawAt(WINDOW *window, int y, int x, chtype icon){
    mvwaddch(window,y+OFFSET,x+OFFSET,icon);
}

void drawScaleIcon(WINDOW *window,int row, int col, int scaleY, int scaleX, chtype icon){
    int actualX, actualY;
    for(int sy = 0; sy < scaleY; sy++){
        for(int sx = 0; sx < scaleX; sx++){
            actualY = (row * scaleY) + sy;
            actualX = (col * scaleX) + sx;
            drawAt(window,actualY,actualX,icon);
        }
    }
}

void drawEntity(WINDOW *window, MovingObject_t entity, int scaleY, int scaleX){
    for(int i = 0; i < entity.height; i++){
        for(int j = 0; j < entity.width; j++){
            drawScaleIcon(window,entity.position.y-i, entity.position.x+j,scaleY,scaleX,entity.icon);
        }
    }

}


void drawBoard(Board_t gameBoard){
    int normalHeight = gameBoard.height/gameBoard.scaleY;
    int normalWidth = gameBoard.width/gameBoard.scaleX;


    //drawing terrain
    for(int row = 0; row < normalHeight; row++){
        for(int col = 0; col < normalWidth; col++){
            drawScaleIcon(gameBoard.board_win,row,col,gameBoard.scaleY, gameBoard.scaleX, gameBoard.board[row][col]);
        }
    }
}

void drawGame(FrogGame_t frogGame){
    drawBoard(frogGame.gameBoard);

    //drawing entities
    drawEntity(frogGame.gameBoard.board_win, frogGame.frog, frogGame.gameBoard.scaleY, frogGame.gameBoard.scaleX);



}