#include <iostream>
#include <ncurses.h>

#include "src/gameSetup.hpp"
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

    gameLoop(&frogGame);
    
    destroyGameWindow();
    return 0;
}   