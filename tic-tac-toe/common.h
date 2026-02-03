#ifndef COMMON_H
#define COMMON_H

typedef struct {
    int table[3][3];
    int gameMode;
    char p1Name[31];
    char p2Name[31];
    int turn;
} Data;

void lineUi();
void startUi();
int getOp();
void switchMode(int *op, Data *g);
void tutorial(Data *g);
void showTable(int isTutorial, Data *g);

#endif