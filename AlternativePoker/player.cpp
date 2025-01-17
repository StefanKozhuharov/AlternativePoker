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
* This file is made to run functions related to the players
*
*/
#include <iostream>
#include "constants.h"
#include "structures.h"
using namespace std;
//sets the ammount of players our game will have depending on what our players decide
int setPlayerCount() {

	int totalPlayers = 1;

	while (totalPlayers < 2 || totalPlayers > 9) {

		cout << "How many players are going to play (2-9)?" << endl;
		cin >> totalPlayers;

	}

	return totalPlayers;

}

//initializes the starting values of our players at the start of a fresh game
player* initializePlayers(int totalPlayers) {

	player* players = new player[totalPlayers];

	for (int i = 0; i < totalPlayers; i++) {

		players[i].hand[0] = NULL;
		players[i].hand[1] = NULL;
		players[i].hand[2] = NULL;
		players[i].balance = CHIP_VALUE * 100;
		players[i].currentBid = NULL;
		players[i].score = NULL;

	}

	return players;

}
//returns the number of players who have not folded yet
int getNumberOfActivePlayers(bool* activePlayers, int totalPlayers) {

	int count = 0;
	for (int i = 0; i < totalPlayers; i++) {

		if (activePlayers[i]) {

			count++;

		}

	}

	return count;

}
//allows us to remove players who have been busted out by moving them to the end of the players array and decreasing the totalPlayers left who have not been busted out by 1
void bustPlayerOut(player* players, int& totalPlayers, int bustedPlayer) {

	for (int i = bustedPlayer; i < totalPlayers - 1; i++) {

		player temp = players[i];
		players[i] = players[i + 1];
		players[i + 1] = temp;

	}

	totalPlayers--;

}
//returns the number of busted out players, which is used to see when we have ourselves a winner of the game
int getNumberOfBustedOutPlayers(player* players, int TOTAL_PLAYERS) {

	int count = 0;

	for (int i = 0; i < TOTAL_PLAYERS; i++) {

		if (players[i].balance == 0) {

			count++;

		}

	}

	return count;

}