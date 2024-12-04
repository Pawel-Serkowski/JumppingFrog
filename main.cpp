#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "src/gameSetup.hpp"
#include "src/customTypes.hpp"
#include "src/windowFunctions.hpp"
#include "src/game.hpp"

using namespace std;

int main(){

    initializeGameWindow();
    srand(time(NULL));    

    Player_t player;
    player.levelNumber = 1;
    player.nick = "SerekJunior";
    
    FrogGame_t frogGame;
    initializeGame(&frogGame);

    if(!frogGame.isSeedOkay){ 
        endwin();
        cout << "Something gone wrong with seed :(." << "\n";
        getch();
        return 0;
    }
    player.points = 1000;
    gameLoop(&frogGame, &player);

    if(frogGame.isGameEnded && frogGame.frog.isAlive == true){
        char message[] = "You passed the level\0";
        int textLength = sizeof(message)/sizeof(char);
        endWindow(frogGame.gameBoard.board_win,frogGame.gameBoard.width, frogGame.gameBoard.height, message, textLength);
    }else{
        char message[] = "You are dead xD\0";
        int textLength = sizeof(message)/sizeof(char);
        endWindow(frogGame.gameBoard.board_win,frogGame.gameBoard.width, frogGame.gameBoard.height, message, textLength);
    }
    
    
    destroyGameWindow();
    return 0;
}   