/**
*
* Solution to course project #10
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Stefan Kozhuharov
* @idnumber 9MI0600529
* @compiler VC
*
* This file is made to merge functions needed in other files from player.cpp
*
*/
#include "structures.h"
#ifndef PLAYER_H
#define PLAYER_H

player* initializePlayers(int totalPlayers);
int setPlayerCount();
int getNumberOfActivePlayers(bool* activePlayers, int totalPlayers);
void bustPlayerOut(player* players, int& totalPlayers, int bustedPlayer);
int getNumberOfBustedOutPlayers(player* players, int TOTAL_PLAYERS);

#endif