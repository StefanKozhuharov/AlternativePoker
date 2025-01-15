#include <iostream>
#include "deck.h"
using namespace std;

int const CHIP_VALUE = 10;

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
