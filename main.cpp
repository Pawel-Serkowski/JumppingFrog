#include <iostream>
#include <ncurses.h>

#include "src/board.hpp"

using namespace std;



int main(){
    initscr();
    refresh();

    noecho(); 
    curs_set(0);
    
    FrogGame_t frogGame;
    frogGame.gameBoard = initializeBoard(3,3);
    frogGame.frog.position.y = frogGame.gameBoard.frogInitY;
    frogGame.frog.position.x = frogGame.gameBoard.frogInitX;
    frogGame.frog.icon = FROGICON;
    frogGame.frog.height = 1;
    frogGame.frog.width = 1;
    if(frogGame.gameBoard.isGood == false){ 
        endwin();
        cout << "We can't get seed." << "\n";
        return 0;
    }

    keypad(frogGame.gameBoard.board_win,true);
    
    drawGame(frogGame);
    addBorder(frogGame.gameBoard.board_win);
    refreshWindow(frogGame.gameBoard.board_win);
    getch();
    endwin();
    return 0;
}   