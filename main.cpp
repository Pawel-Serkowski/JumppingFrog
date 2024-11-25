#include <iostream>
#include <ncurses.h>

#include "src/gameSetup.hpp"
#include "src/drawGame.hpp"
#include "src/customTypes.hpp"
#include "src/windowFunctions.hpp"
#include "src/game.hpp"

using namespace std;

int main(){

    initializeGameWindow();    
    
    FrogGame_t frogGame;
    initializeGame(&frogGame);

    if(!frogGame.isSeedOkay){ 
        endwin();
        cout << "Something gone wrong with seed :(." << "\n";
        return 0;
    }

    drawGame(frogGame);
    while(true){
        processInput(frogGame.gameBoard.board_win, &(frogGame.frogDirection));
        doLogic(&frogGame);

        drawGame(frogGame);
        refreshWindow(frogGame.gameBoard.board_win);
    }
    
    destroyGameWindow();
    return 0;
}   