#include "game.h"
#include <stdlib.h>

int main() {

    Game *game = (Game *)calloc(1,sizeof(Game));
    if (!game) return 1;

    do
    {

        reset_game(game);

        start(game);
        
        if(game->multiplayer == 1) {
            get_user_name(game);
            sort_first_player(game);
            tictactoe(game);
        }
        else
        {

        }

    } while(game->endGame == 0);

    free(game);

    return 0;
}