#include <iostream>
#include <ncurses.h>

#include "src/gameSetup.hpp"
#include "src/drawGame.hpp"
#include "src/customTypes.hpp"
#include "src/windowFunctions.hpp"

using namespace std;

int main(){
    initscr();
    refresh();

    noecho(); 
    curs_set(0);
    start_color();
    use_default_colors();
    initColors();

    
    
    FrogGame_t frogGame;
    FrogGame_t *frogGamePointer = &frogGame;
    initializeGame(frogGamePointer);

    if(!frogGame.isSeedOkay){ 
        endwin();
        cout << "Something gone wrong with seed :(." << "\n";
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