#include "common.h"
#include "multiplayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void multi(Data *g)
{
    lineUi();
    printf("\tMULTIPLAYER!");
    lineUi();

    getUserNames(g);  
    
    sortPlayer(g);

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

void sortPlayer(Data *g)
{
    int randomNumber = rand() % 2;

    if(randomNumber = 0)
    {
        g->turn = 0;
    }
    else
    {
        g->turn = 1;
    }
}