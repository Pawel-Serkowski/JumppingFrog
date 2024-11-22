#include <iostream>
#include <ncurses.h>

#include "src/board.hpp"

using namespace std;



int main(){
    initscr();
    refresh();

    noecho(); 
    curs_set(0);
    
    Board_t gameBoard = initializeBoard(1,2);
    if(gameBoard.isGood == false){ 
        endwin();
        cout << "We can't get seed." << "\n";
        return 0;
    }

    keypad(gameBoard.board_win,true);
    
    drawGame(gameBoard);
    addBorder(gameBoard.board_win);
    refreshWindow(gameBoard.board_win);
    getch();
    endwin();
    return 0;
}   