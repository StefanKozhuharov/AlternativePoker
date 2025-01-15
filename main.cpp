#include <iostream>
#include "player.h"
#include "deck.h"
#include "score.h"
#include "constants.h"
#include "structures.h"
using namespace std;

void startGame(int totalPlayers, player* players) {

	int* deck = shuffleDeck(cards);

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < totalPlayers; j++) {

			players[j].hand[i] = deck[j + i * totalPlayers];

		}

	}

	for (int i = 0; i < totalPlayers; i++) {

		players[i].balance -= CHIP_VALUE;
		players[i].current_bid = CHIP_VALUE;
		players[i].score = calculateScore(players[i].hand);

	}

	delete[] deck;

}

int main() {

	int totalPlayers = setPlayerCount();

}
