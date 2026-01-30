#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void checkWin(Game *g);
static void checkDraw(Game *g);
static void PlayAgain(Game *g);

void bufferClear()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void clear_table(Game *g)
{
    for(int i = 0; i < 9 ; i++)
    {
        g->table[i] = ' '; 
    }
}

void start(Game *g)
{
    printf("-------------------------------");
    printf("\n      TIC TAC TOE GAME       ");
    printf("\n\n1 - MultiPlayer");
    printf("\n2 - SinglePlayer");
    printf("\n\n->");

    do
    {

        scanf("%d", &g->multiplayer);
        bufferClear();

        if(g->multiplayer < 1 || g->multiplayer > 2)
        {
            printf("Error, please insert a expected number\n\n");
            printf("->");
        }

    }while(g->multiplayer < 1 || g->multiplayer > 2);

    printf("\n-------------------------------\n\n");
}

void get_user_name(Game *g)
{
    printf("Please, insert P1 name: ");
    fgets(g->player_name, 20, stdin);
    g->player_name[strcspn(g->player_name, "\n")] = '\0';
        
    printf("Please, insert P2 name: ");
    fgets(g->player2_name, 20, stdin);
    g->player2_name[strcspn(g->player2_name, "\n")] = '\0';
}

void sort_first_player(Game *g)
{
    int num_rand;

    srand(time(NULL));

    num_rand = rand();

    if(num_rand % 2 == 0)
    {
        g->turn = 0;
    }
    else
    {
        g->turn = 1;
    }
}

void show_player_turn(Game *g)
{
    if(g->turn == 0)
    {
        printf("\n%s turn!\n\n", g->player_name);
    }
    else
    {
        printf("\n%s turn!\n\n", g->player2_name);
    }
}

void show_table(Game *g)
{
    printf("\n");

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(j != 2)
            {
                printf("  %c  |", g->table[(i * 3) + j]);
            }
            else
            {
                printf("  %c", g->table[(i * 3) + j]);
            }
        }
        if(i != 2)
        {
            printf("\n-----------------\n");
        }
        else
        {
            printf("\n\n");
        }
    }
}

void tutorial()
{
    printf("\nTo select a place to place X or O, you will have to choose between 1-9.\nHere's every position with it's number to help you!\n\n");

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
                printf("  %d", (i * 3) + j + 1);
            }
        }
        if(i != 2)
        {
            printf("\n-----------------\n");
        }
        else
        {
            printf("\n\n");
        }
    }
}

void tictactoe(Game *g)
{
    tutorial();

    printf("\n-------------------------------\n\n");

    printf("Lets get started:\n");

    insertPlay(g);

}

void static checkWin(Game *g)
{
    char *t = g->table;

    
    if ((t[0] != ' ' && t[0] == t[1] && t[1] == t[2]) ||
        (t[3] != ' ' && t[3] == t[4] && t[4] == t[5]) ||
        (t[6] != ' ' && t[6] == t[7] && t[7] == t[8]) ||
    
        (t[0] != ' ' && t[0] == t[3] && t[3] == t[6]) ||
        (t[1] != ' ' && t[1] == t[4] && t[4] == t[7]) ||
        (t[2] != ' ' && t[2] == t[5] && t[5] == t[8]) ||
    
        (t[0] != ' ' && t[0] == t[4] && t[4] == t[8]) ||
        (t[2] != ' ' && t[2] == t[4] && t[4] == t[6]))
    {
        g->gamestate = 1;

        char winner[21];

        if(!(g->turn) == 0)
        {
            strcpy(winner, g->player_name);
        }
        else
        {
            strcpy(winner, g->player2_name);
        }

        show_table(g);

        printf("\n\nTHE PLAYER %s WON!! CONGRATULATIONS!\n\n", winner);

        PlayAgain(g);
    }
    
    

}

void static checkDraw(Game *g)
{
    if(g->n_plays == 9 && g->gamestate != 1)
    {
        g->gamestate = 1;

        show_table(g);

        printf("\n\nWE HAVE A DRAW!! NOBODY WON...\n\n");

        PlayAgain(g);
    }
}

void static PlayAgain(Game *g)
{
    int op;

    printf("-------------------------------\n");

    do
    {
        printf("\nWanna Play Again? \n1 - Yes\n2 - No\n");
        
        scanf("%d", &op);
        bufferClear();

    }while(op < 1 || op > 2);

    if(op == 1)
    {
        g->endGame = 0;
    }
    else
    {
        g->endGame = 1;
    }
}

void reset_game(Game *g) {
    clear_table(g);
    g->gamestate = 0;
    g->n_plays = 0;
    g->endGame = 0;
}

void insertPlay(Game *g)
{
    do
    {
        show_table(g);
        show_player_turn(g);
        
        printf("Please, insert a number from 1-9: ");

        scanf("%d", &g->play);

        g->n_plays += 1;

        while(g->table[g->play - 1] != ' ')
        {
            printf("\nThe place you selected is already used, choose another number!\n\n");

            printf("Please, insert a number from 1-9: ");
            
            scanf("%d", &g->play);
        }


        if(g->turn == 0)
        {
            g->table[g->play - 1] = 'X';
        }
        else
        {
            g->table[g->play - 1] = 'O';
        }

        g->turn = !(g->turn);

        checkDraw(g);

        checkWin(g);

    } while(g->gamestate != 1);
}

