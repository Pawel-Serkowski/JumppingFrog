#pragma once

#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "customTypes.hpp"
#include "CONFIG.hpp"

bool initializeRankingFromFile(Ranking_t * ranking){
    FILE* rankingFile =fopen("./files/ranking.txt","r");
    if(rankingFile == NULL){
        return false;
    }
    fscanf(rankingFile,"%i",&ranking->numberOfRecords);
    ranking->rankingRecords = new RankingRecord_t[ranking->numberOfRecords+1];
    
    ranking->numberOfRecords += 1;
    for(int i = 0; i < ranking->numberOfRecords-1; i++){
        fseek(rankingFile,SEEK_CUR,1);
        fscanf(rankingFile,"%s %i",ranking->rankingRecords[i].name,&ranking->rankingRecords[i].score);
        
    }

    fclose(rankingFile);
    return true;
}


void saveAndCloseRanking( Ranking_t * ranking){
    FILE* rankingFile = fopen("./files/ranking.txt","w");

    for(int i = 0; i < ranking->numberOfRecords;i++){
        for(int j = i; j < ranking->numberOfRecords; j++){
            RankingRecord_t tempRank;
            if(ranking->rankingRecords[i].score < ranking->rankingRecords[j].score){
                tempRank = ranking->rankingRecords[j];
                ranking->rankingRecords[j] = ranking->rankingRecords[i];
                ranking->rankingRecords[i] = tempRank;

            }
        }
    }

    fprintf(rankingFile,"%d",ranking->numberOfRecords);
    for(int i = 0; i < ranking->numberOfRecords;i++){
        fprintf(rankingFile,"\n%s %i",ranking->rankingRecords[i].name,ranking->rankingRecords[i].score);
    }
    delete ranking->rankingRecords;

    fclose(rankingFile);
}
