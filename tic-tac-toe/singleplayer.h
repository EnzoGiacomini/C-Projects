#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "common.h"

void single(Data *g);
void playSingle(Data *g, int *r, int ia);
void iaEasy(Data *g);
void iaNormal(Data *g);
int testPlace(Data *g, int m);
int testGame(int tempTable[3][3], int turn);
void copyTable(Data *g, int copyTable[3][3]);
void decoderInputBOT(int m, Data *g);
void chooseDifficult(int *ia);


#endif