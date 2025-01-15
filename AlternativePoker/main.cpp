#include <iostream>
#include "player.h"
#include "deck.h"
#include "score.h"
#include "constants.h"
#include "structures.h"
using namespace std;

int cards[32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };

void startGame(int totalPlayers, player* players) {

	shuffleDeck(cards);

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < totalPlayers; j++) {

			players[j].hand[i] = cards[j + i * totalPlayers];

		}

	}


	for (int i = 0; i < totalPlayers; i++) {

		players[i].balance -= CHIP_VALUE;
		players[i].current_bid = CHIP_VALUE;
		players[i].score = calculateScore(players[i].hand);

	}


}

int main() {

	int totalPlayers = setPlayerCount();
	player* players = initializePlayers(totalPlayers);
	startGame(totalPlayers, players);

}