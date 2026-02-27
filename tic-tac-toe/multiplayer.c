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

    getUserNames(g);  
    
    sortPlayer(g);

    do
    {
        play(g, &gameResult);
    } while(g->gameMode != 0);

    endGame(gameResult, g);

}

void endGame(int result, Data *g)
{
    if(result == 1)
    {
        printf("END GAME, WE HAVE A WINNER!\nCONGRATULATIONS %s", g->nameTurn);
        lineUi();
    }
    else
    {
        printf("OH WE HAVE A DRAWN!\nUNFORTNALY NOBODY WON...");
        lineUi();
    }
}

void checkGame(Data *g, int *r)
{
    //Testa linha
    for(int i = 0; i < 3; i++)
    {
        if(g->table[i][0] == g->table[i][1] && g->table[i][1] == g->table[i][2] && g->table[i][0] != -1)
        {
            g->gameMode = 0;
            
            *r = 1;
        }
    }
    //Testa coluna
    for(int j = 0; j < 3; j++)
    {
        if(g->table[0][j] == g->table[1][j] && g->table[1][j] == g->table[2][j] && g->table[0][j] != -1)
        {
            g->gameMode = 0;
            
            *r = 1;
        }
    }
    //Teste diagonal principal
    if(g->table[0][0] == g->table[1][1] && g->table[1][1] == g->table[2][2] && g->table[0][0] != -1)
    {
        g->gameMode = 0;

        *r = 1;
    }
    //Teste diagonal secundária
    if(g->table[0][2] == g->table[1][1] && g->table[1][1] == g->table[2][0] && g->table[0][2] != -1)
    {
        g->gameMode = 0;

        *r = 1;
    }
    //Teste empate
    if(g->numPlays == 8 && *r != 1)
    {
        g->gameMode = 0;

        *r = 0;
    }
}

void play(Data *g, int *r)
{
    int move;

    printf("PLAYER: %s TURN!\n\n", g->nameTurn);

    showTable(0, g);

    printf("Move position (1-9): ");

    move = getOp();
    
    decoderInput(move, g);

    lineUi();

    checkGame(g, r);

    if(*r != 1 && *r != 0)
    {
        switchTurn(g);
    }

    g->numPlays++;

}

void decoderInput(int m, Data *g)
{
    
    if (m < 1 || m > 9) {
        int new_m;

        printf("\n\nERROR, INVALID INPUT!\nTRY AGAIN\n\n");

        new_m = getOp();
        
        decoderInput(new_m, g);

        return; 
    }

    int i = (m - 1) / 3;
    int j = (m - 1) % 3;

    if(canPlace(i, j, g) == 1)
    {
        g->table[i][j] = g->turn;
    }
    else
    {
        int new_m;

        printf("\n\nERROR, NUMBER ALREADY CHOOSED!\nTRY AGAIN\n\n");

        new_m = getOp();

        decoderInput(new_m, g);
    }
    
}

int canPlace(int i, int j, Data *g)
{
    if(g->table[i][j] != -1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void getUserNames(Data *g)
{
    printf("Please enter player 1 nickname: ");
    fgets(g->p1Name, 30, stdin);
    printf("Now, enter player 2 nickname: ");
    fgets(g->p2Name, 30, stdin);

    g->p1Name[strcspn(g->p1Name, "\n")] = '\0';
    g->p2Name[strcspn(g->p2Name, "\n")] = '\0';

    printf("\nDone!");
    lineUi();
}

void switchTurn(Data *g)
{
    g->turn = !(g->turn);

    if(g->turn == 0)
    {
        strcpy(g->nameTurn, g->p1Name);
    }
    else
    {
        strcpy(g->nameTurn, g->p2Name);
    }
}

void sortPlayer(Data *g)
{
    int randomNumber = rand() % 2;

    if(randomNumber == 0)
    {
        g->turn = 0;
        strcpy(g->nameTurn, g->p1Name);
    }
    else
    {
        g->turn = 1;
        strcpy(g->nameTurn, g->p2Name);
    }
}