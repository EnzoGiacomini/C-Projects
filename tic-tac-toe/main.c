#include "common.h"
#include "multiplayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main ()
{
    int *decision = (int *)calloc(1, sizeof(int));
    Data *game = (Data *)calloc(1, sizeof(Data));
    srand(time(NULL));

    do
    {
        startUi();
        *decision = getOp();

        switchMode(decision, game);

    } while(*decision != 4);

    free(game);
    free(decision);

    return 0;
}