#include "structures.h"
#ifndef PLAYER_H
#define PLAYER_H

player* initializePlayers(int totalPlayers);
int setPlayerCount();
int getNumberOfActivePlayers(bool* activePlayers, int totalPlayers);

#endif