#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "CONFIG.hpp"
#include "customTypes.hpp"
#include "windowFunctions.hpp"

void initializeRecorder(int boardHeight, int boardWidth){
    FILE * recorderFile = fopen("./files/recording.txt","w");
    fprintf(recorderFile,"%d %d",boardHeight,boardWidth);
    fclose(recorderFile);
}

void recordToFile(WINDOW * win, int boardHeight, int boardWidth){
    FILE * recorderFile = fopen("./files/recording.txt","a");
    for(int i = 0; i < boardHeight; i++){
        fprintf(recorderFile,"%c",'\n');
        for(int j = 0; j < boardWidth; j++){
            chtype c = mvwinch(win, i+OFFSET, j+OFFSET);
            char c1 = c;
            fprintf(recorderFile,"%c",c1);
        }
        
        
    }
    fclose(recorderFile);
}


void showRecording(WINDOW * win, int framesNumber){
    int width, height;
    FILE * recorderFile = fopen("./files/recording.txt","r");
    fscanf(recorderFile,"%d %d",&height,&width);

    wclear(win);
    addBorder(win);
    refreshWindow(win);

    for(int f = 0; f < framesNumber; f++){
        for(int h = 0; h < height; h++){
            fseek(recorderFile,SEEK_CUR, 1);
            for(int w = 0; w < width; w++){
                chtype c = fgetc(recorderFile);
                char c1 = c;
                mvwaddch(win,h+OFFSET,w+OFFSET,c1);
            }
        }
        refreshWindow(win);
        usleep(10000);
    }
    fclose(recorderFile);

}