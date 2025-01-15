#include <iostream>
#include "deck.h"
#include "constants.h"
using namespace std;

struct player {

	int hand[3];
	int balance = CHIP_VALUE * 100;
	int current_bid;
	int score;

};

int setPlayerCount() {

	int totalPlayers = 1;

	while (totalPlayers < 2 || totalPlayers > 9) {

		cout << "How many players are going to play (2-9)?" << endl;
		cin >> totalPlayers;

	}

	return totalPlayers;

}

int totalPlayers = setPlayerCount();
player* players;

void setHand() {

	int* deck = shuffleDeck(cards);

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < totalPlayers; j++) {

			players[j].hand[i] = deck[j+i*totalPlayers];

		}

	}

	delete[] deck;

}
