#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include "string.h"


#include "src/gameSetup.hpp"
#include "src/gameEnd.hpp"
#include "src/customTypes.hpp"
#include "src/windowFunctions.hpp"
#include "src/rankingFunctions.hpp"
#include "src/game.hpp"

using namespace std;

int main(){
    Ranking_t ranking;
    if(!initializeRankingFromFile(&ranking)){
        cout << "cannot initialize ranking..." << "\n";
        return 0;
    }
    

    initializeGameWindow();
    srand(time(NULL));    

    Player_t player;
    player.levelNumber = 1;
    strcpy(player.nick,"SerekJunior");
    
    FrogGame_t frogGame;
    initializeGame(&frogGame);

    if(!frogGame.isSeedOkay){ 
        endwin();
        cout << "Something gone wrong with seed :(." << "\n";
        getch();
        return 0;
    }
    player.points = 50*(frogGame.gameBoard.height/SCALE_Y);
    gameLoop(&frogGame, &player);


    strcpy(ranking.rankingRecords[ranking.numberOfRecords-1].name,player.nick);
    ranking.rankingRecords[ranking.numberOfRecords-1].score = player.points;
    saveAndCloseRanking(&ranking);

    if(frogGame.isGameEnded && frogGame.frog.isAlive == true){
        char message[] = "You passed the level\0";
        int textLength = sizeof(message)/sizeof(char);
        endWindow(frogGame.gameBoard.board_win,frogGame.gameBoard.width, frogGame.gameBoard.height, message, textLength);
    }else{
        char message[] = "You are dead xD\0";
        int textLength = sizeof(message)/sizeof(char);
        endWindow(frogGame.gameBoard.board_win,frogGame.gameBoard.width, frogGame.gameBoard.height, message, textLength);
    }

    destroyGame(&frogGame);
    destroyGameWindow();
    return 0;
}   