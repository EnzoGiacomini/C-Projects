#include "common.h"
#include "multiplayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void lineUi()
{
    printf("\n\n-----------------------------------\n\n");
}

void startUi()
{
    lineUi();
    printf("\tTicTacToe Game!");
    lineUi();

    printf("Options:\n\n");
    printf("(Local Multiplayer - 1)\n");
    printf("(Singleplayer - 2)\n");
    printf("(How to play? - 3)\n");
    printf("(Exit - 4)");

    printf("\n\n-> ");
}

void switchMode(int *op, Data *g)
{
    switch (*op)
    {
    case 1:
        multi(g);
        break;
    case 2:
        //single();
        break;
    case 3:
        tutorial(g);
        break;
    case 4:
        //Do nothing
        break;
    default:
        printf("\nError, invalid option!\nPlease try again... \n-> ");
        *op = getOp();
        switchMode(op, g);
        break;
    }
}

int getOp()
{
    char *buffer = (char *)malloc(sizeof(char) * 5);
    int op;

    fgets(buffer, 5, stdin);
    op = strtol(buffer, NULL, 10);

    free(buffer);

    return op;
}

void showTable(int isTutorial, Data *g)
{
    if(isTutorial == 0)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(j != 2)
                {
                    printf("  %d  |", g->table[i][j]);
                }
                else
                {
                    printf("  %d  ", g->table[i][j]);
                }
            }
            if(i != 2)
            {
                printf("\n-----+-----+-----\n");
            }
            else
            {
                printf("\n\n");
            }
        }
    }
    else
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(j != 2)
                {
                    printf("  %d  |", (i * 3) + j + 1);
                }
                else
                {
                    printf("  %d  ", (i * 3) + j + 1);
                }
            }
            if(i != 2)
            {
                printf("\n-----+-----+-----\n");
            }
            else
            {
                printf("\n\n");
            }
            
        }
    }
}

void tutorial(Data *g)
{   
    char c;

    lineUi();
    printf("\tHow to play:");
    lineUi();

    showTable(1, g);

    lineUi();
    printf("When started your turn, you must input a number from 1-9, like the table show above.\nMake sure that your input isn't already marked!\n\n");
    printf("Press ENTER to get back to menu...");
    while((c = getchar()) != '\n');

}