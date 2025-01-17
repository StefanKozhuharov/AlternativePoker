#ifndef SCORE_H
#define SCORE_H

int calculateScore(int hand[3]);
bool* getPlayersWithHighestScore(player* players, bool* activePlayers, int totalPlayers);
int getNumberOfHighestScoringPlayers(player* players, bool* activePlayers, int totalPlayers);
int getHighestScoringPlayer(player* players, bool* activePlayers, int totalPlayers);

#endif