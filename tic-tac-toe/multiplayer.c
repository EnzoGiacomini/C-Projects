#include "common.h"
#include "multiplayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void multi(Data *g)
{
    int gameResult = -1;

    g->numPlays = 0;

    g->gameMode = 1;

    lineUi();
    printf("\tMULTIPLAYER!");
    lineUi();

    getUserNames(g, 1);  
    
    sortPlayer(g);

    do
    {
        playMulti(g, &gameResult);
    } while(g->gameMode != 0);

    endGame(gameResult, g);

}

void playMulti(Data *g, int *r)
{
    int move;

    printf("PLAYER: %s TURN!\n\n", g->nameTurn);

    showTable(0, g);

    printf("Move position (1-9): ");

    move = getOp();
    
    decoderInputPlayer(move, g);

    lineUi();

    checkGame(g, r);

    if(*r != 1 && *r != 0)
    {
        switchTurn(g);
    }

    g->numPlays++;

}
