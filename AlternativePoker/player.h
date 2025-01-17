#include "structures.h"
#ifndef PLAYER_H
#define PLAYER_H

player* initializePlayers(int totalPlayers);
int setPlayerCount();
int getNumberOfActivePlayers(bool* activePlayers, int totalPlayers);
void bustPlayerOut(player* players, int& totalPlayers, int bustedPlayer);
int getNumberOfBustedOutPlayers(player* players, int TOTAL_PLAYERS);

#endif