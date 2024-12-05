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
#include "src/recorderFunctions.hpp"

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
    player.levelNumber = 0;
    cout << "Podaj nick: ";
    cin >> player.nick;
    player.points = 1234;

    initializeGameWindow();
    srand(time(NULL));    

    for(int i = 0; i <levelsNumber; i++){
        player.levelNumber++;
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
            }else if(option == 'r'){
                showRecording(frogGame.gameBoard.board_win,frogGame.framesNumber);
                wattron(frogGame.gameBoard.board_win,COLOR_PAIR(FROG_COLOR_NUMBER));
                mvwaddstr(frogGame.gameBoard.board_win,1,1,"press any key");
                mvwaddstr(frogGame.gameBoard.board_win,2,1,"to start new level!");
                wattroff(frogGame.gameBoard.board_win,COLOR_PAIR(FROG_COLOR_NUMBER));
                refreshWindow(frogGame.gameBoard.board_win);
                getch();
            }
            destroyGame(&frogGame);
        }else{
            char message[] = "You are dead\0";
            int textLength = sizeof(message)/sizeof(char);
            char option = endWindow(frogGame.gameBoard.board_win,frogGame.gameBoard.width, frogGame.gameBoard.height, message, textLength,false,0);
            if(option == 'r'){
                showRecording(frogGame.gameBoard.board_win,frogGame.framesNumber);
                wattron(frogGame.gameBoard.board_win,COLOR_PAIR(CAR_COLOR_NUMBER));
                mvwaddstr(frogGame.gameBoard.board_win,1,1,"press any key..");
                wattroff(frogGame.gameBoard.board_win,COLOR_PAIR(CAR_COLOR_NUMBER));
                refreshWindow(frogGame.gameBoard.board_win);
                getch();
            }
            destroyGame(&frogGame);
            break;
        }

        
    }
    saveAndCloseRanking(&ranking);
    destroyGameWindow();
    return 0;
}   