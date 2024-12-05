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
    char levelsPath[][30]= {"./files/level1.txt\0","./files/level2.txt\0","./files/level3.txt\0"};
    int levelsNumber = 3;

    Ranking_t ranking;
    if(!initializeRankingFromFile(&ranking)){
        cout << "cannot initialize ranking..." << "\n";
        return 0;
    }

    Player_t player;
    player.levelNumber = 1;
    cout << "Podaj nick: ";
    cin >> player.nick;
    player.points = 1000;

    initializeGameWindow();
    srand(time(NULL));    

    for(int i = 0; i <levelsNumber; i++){
        FrogGame_t frogGame;
        initializeGame(&frogGame, levelsPath[i]);

        if(!frogGame.isSeedOkay){ 
            endwin();
            cout << "Something gone wrong with seed :(." << "\n";
            getch();
            return 0;
        }

        gameLoop(&frogGame, &player);
        strcpy(ranking.rankingRecords[ranking.numberOfRecords-1].name,player.nick);
        ranking.rankingRecords[ranking.numberOfRecords-1].score = player.points;
        

        if(frogGame.isGameEnded && frogGame.frog.isAlive == true){
            char message[] = "You passed the level\0";
            int textLength = sizeof(message)/sizeof(char);
            char option = endWindow(frogGame.gameBoard.board_win,frogGame.gameBoard.width, frogGame.gameBoard.height, message, textLength,levelsNumber-player.levelNumber,player.points);
            if(option == 'q'){
                destroyGame(&frogGame);
                ranking.rankingRecords[ranking.numberOfRecords-1].score = 0;
                break;
            }
        }else{
            char message[] = "You are dead\0";
            int textLength = sizeof(message)/sizeof(char);
            endWindow(frogGame.gameBoard.board_win,frogGame.gameBoard.width, frogGame.gameBoard.height, message, textLength,false,0);
            break;
        }
    }
    saveAndCloseRanking(&ranking);
    
    


    
   


    
    

    
    destroyGameWindow();
    return 0;
}   