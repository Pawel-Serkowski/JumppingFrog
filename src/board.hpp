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
    char temp_ch; //char to przerzucania char'a z pliku do board (bo typy są rozne)

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
        seedFile.get(temp_ch);
        for(int j = 0; j < boardWidth; j++){
            seedFile.get(temp_ch);
            if(temp_ch == ROADICON){
                for(int t = 0; t < boardWidth; t++){
                    gameBoard[i][j+t] = ' ';
                }
                break;
            }
            gameBoard[i][j] = temp_ch;
            
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

    board.board_win = newwin(board.height+2,board.width+2,board.startRow-1,board.startCol-1);

    return board;
}

void drawAt(WINDOW *board_win, int y, int x, chtype icon){
    mvwaddch(board_win,y+1,x+1,icon);
}

void drawGame(Board_t gameBoard){
    int normalHeight = gameBoard.height/gameBoard.scaleY;
    int normalWidth = gameBoard.width/gameBoard.scaleX;
    int actualX, actualY;

    for(int row = 0; row < normalHeight; row++){
        for(int col = 0; col < normalWidth; col++){
            // drawAt(gameBoard.board_win,i,j,gameBoard.board[i][j]);
            for(int sy = 0; sy < gameBoard.scaleY; sy++){
                for(int sx = 0; sx < gameBoard.scaleX; sx++){
                    actualY = (row * gameBoard.scaleY) + sy;
                    actualX = (col * gameBoard.scaleX) + sx;
                    drawAt(gameBoard.board_win,actualY,actualX,gameBoard.board[row][col]);
                }
            }
        }
    }
}