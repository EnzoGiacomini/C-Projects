#include "singleplayer.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void single(Data *g)
{
    int gameResult = -1;
    int iaLevel;

    g->numPlays = 0;

    g->gameMode = 1;

    lineUi();
    printf("\tSINGLEPLAYER");
    lineUi();

    getUserNames(g, 0);

    sortPlayer(g);

    chooseDifficult(&iaLevel);

    do
    {
        playSingle(g, &gameResult, iaLevel);
    } while(g->gameMode != 0);

    endGame(gameResult, g);
}

void playSingle(Data *g, int *r, int ia)
{
    int move;

    printf("PLAYER: %s TURN!\n\n", g->nameTurn);

    if(g->turn == 0)
    {
        showTable(0, g);

        printf("Move position (1-9): ");

        move = getOp();
    
        decoderInputPlayer(move, g);
    }
    else
    {
        switch (ia)
        {
        case 1:
            iaEasy(g);
            break;
        case 2:
            iaNormal(g);
            break;
        case 3: 
            //iaHard();
            break;
        default:
            printf("\nSOMETHING WENT WRONG, PLEASE CHECK playSingle()!\n");
            break;
        }

        showTable(0, g);
    }

    g->numPlays++;

    lineUi();

    checkGame(g, r);

    if(*r != 1 && *r != 0)
    {
        switchTurn(g);
    }
}

void iaNormal(Data *g)
{   
    int move = 1;

    while(testPlace(g, move) == 0 && move <= 9)
    {
        move++;
    }

    if(move == 10)
    {
        if(canPlace(1, 1, g) == 1)
        {
            g->table[1][1] = g->turn;
        }
        else if(canPlace(0,0,g) == 1)
        {
            g->table[0][0] = g->turn;
        }
        else if(canPlace(0,2,g) == 1)
        {
            g->table[0][2] = g->turn;
        }
        else if(canPlace(2,0,g) == 1)
        {
            g->table[2][0] = g->turn;
        }
        else if(canPlace(2,2,g) == 1)
        {
            g->table[2][2] = g->turn;
        }
        else if(g->numPlays != 9)
        {
            iaEasy(g);
        }
    }
    else
    {
        //Play where bot can win or player can win
        decoderInputBOT(move, g);
    }
    
}

int testPlace(Data *g, int m)
{   
    int i = (m - 1) / 3;
    int j = (m - 1) % 3;


    //Test if BOT can win
    if(canPlace(i, j, g) == 0)
    {
        return 0;
    }

    int testResult, tempTable[3][3];
    copyTable(g, tempTable);

    tempTable[i][j] = g->turn;
    testResult = testGame(tempTable, g->turn);

    if(testResult != 0) 
    {
        return testResult;
    }

    copyTable(g, tempTable);
    tempTable[i][j] = !(g->turn);
    testResult = testGame(tempTable, !(g->turn));

    return  testResult;
    
}

int testGame(int tempTable[3][3], int turn)
{
    //Testa linha
    for(int i = 0; i < 3; i++)
    {
        if(tempTable[i][0] == tempTable[i][1] && tempTable[i][1] == tempTable[i][2] && tempTable[i][0] != -1)
        {   
            if(turn == 1)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
    }
    //Testa coluna
    for(int j = 0; j < 3; j++)
    {
        if(tempTable[0][j] == tempTable[1][j] && tempTable[1][j] == tempTable[2][j] && tempTable[0][j] != -1)
        {
            if(turn == 1)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
    }
    //Teste diagonal principal
    if(tempTable[0][0] == tempTable[1][1] && tempTable[1][1] == tempTable[2][2] && tempTable[0][0] != -1)
    {
        if(turn == 1)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    //Teste diagonal secundária
    if(tempTable[0][2] == tempTable[1][1] && tempTable[1][1] == tempTable[2][0] && tempTable[0][2] != -1)
    {
        if(turn == 1)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    
    return 0;
}

void iaEasy(Data *g)
{
    int randomPlace = (rand() % 9) + 1;

    int i = (randomPlace - 1) / 3;
    int j = (randomPlace - 1) % 3;

    while(canPlace(i, j, g) != 1)
    {
        randomPlace = (rand() % 9) + 1;

        i = (randomPlace - 1) / 3;
        j = (randomPlace - 1) % 3;
    }

    g->table[i][j] = g->turn;
}

void decoderInputBOT(int m, Data *g)
{
    int i = (m - 1) / 3;
    int j = (m - 1) % 3;

    g->table[i][j] = g->turn;
}

void copyTable(Data *g, int copyTable[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            copyTable[i][j] = g->table[i][j];
        }
    }
}

void chooseDifficult(int *ia)
{
    lineUi();
    printf("Please select the IA difficult: \n1 - Easy\n2 - Normal\n3 - Hard\n\n-> ");

    do
    {
        *ia = getOp();

        if(*ia > 3 || *ia < 0)
        {
            printf("ERROR, PLEASE ENTER A NUMBER BETWEEN 1 AND 3\n\n-> ");
        }
    } while(*ia > 3 || *ia < 0);

    lineUi();
}