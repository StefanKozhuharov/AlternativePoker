#include <iostream>
#include "constants.h"
#include "structures.h"
using namespace std;

int setPlayerCount() {

	int totalPlayers = 1;

	while (totalPlayers < 2 || totalPlayers > 9) {

		cout << "How many players are going to play (2-9)?" << endl;
		cin >> totalPlayers;

	}

	return totalPlayers;

}


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

int getNumberOfActivePlayers(bool* activePlayers, int totalPlayers) {

	int count = 0;
	for (int i = 0; i < totalPlayers; i++) {

		if (activePlayers[i]) {

			count++;

		}

	}

	return count;

}

void bustPlayerOut(player* players, int& totalPlayers, int bustedPlayer) {

	for (int i = bustedPlayer; i < totalPlayers - 1; i++) {

		player temp = players[i];
		players[i] = players[i + 1];
		players[i + 1] = temp;

	}

	totalPlayers--;

}

int getNumberOfBustedOutPlayers(player* players, int TOTAL_PLAYERS) {

	int count = 0;

	for (int i = 0; i < TOTAL_PLAYERS; i++) {

		if (players[i].balance == 0) {

			count++;

		}

	}

	return count;

}