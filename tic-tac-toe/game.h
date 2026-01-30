#ifndef GAME_H
#define GAME_H

typedef struct {
    char table[9];
    char player_name[21];
    int multiplayer;
    char player2_name[21];
    int turn;
    int play;
    int gamestate;
    int n_plays;
    int endGame;
} Game;

void bufferClear();
void clear_table(Game *g);
void start(Game *g);
void get_user_name(Game *g);
void sort_first_player(Game *g);
void show_player_turn(Game *g);
void tictactoe(Game *g);
void show_table(Game *g);
void tutorial();
void insertPlay(Game *g);
void reset_game(Game *g);

#endif