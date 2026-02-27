#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

void multi(Data *g);
void getUserNames(Data *g);
void sortPlayer(Data *g);
void switchTurn(Data *g);
void decoderInput(int m, Data *g);
void play(Data *g, int *r);
int canPlace(int i, int j, Data *g);
void checkGame(Data *g, int *r);
void endGame(int result, Data *g);



#endif