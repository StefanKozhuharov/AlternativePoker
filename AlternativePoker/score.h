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
* This file is made to merge functions needed in other files from score.cpp
*
*/
#ifndef SCORE_H
#define SCORE_H

int calculateScore(int hand[3]);
bool* getPlayersWithHighestScore(player* players, bool* activePlayers, int totalPlayers);
int getNumberOfHighestScoringPlayers(player* players, bool* activePlayers, int totalPlayers);
int getHighestScoringPlayer(player* players, bool* activePlayers, int totalPlayers);

#endif