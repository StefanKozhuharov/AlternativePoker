#include <iostream>
#include "player.h"
#include "deck.h"
#include "score.h"
#include "constants.h"
#include "structures.h"
using namespace std;

int cards[32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };

void startGame(int totalPlayers, player* players, int& pot) {

	shuffleDeck(cards);

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < totalPlayers; j++) {

			players[j].hand[i] = cards[j + i * totalPlayers];

		}

	}


	for (int i = 0; i < totalPlayers; i++) {

		players[i].balance -= CHIP_VALUE;
		players[i].currentBid = CHIP_VALUE;
		players[i].score = calculateScore(players[i].hand);

	}

	pot = totalPlayers * CHIP_VALUE;

	for (int i = 0; i < totalPlayers; i++) {

		cout << "Player" << i+1 << ": " << players[i].balance;
		cout << endl;

	}

	cout << "Pot: " << pot << endl;

	int i = 0;


}

int getHighestBid(player* players, int totalPlayers) {

	int highestBid = players[0].currentBid;
	for (int i = 1; i < totalPlayers; i++) {

		if (players[i].currentBid > highestBid) {

			highestBid = players[i].currentBid;

		}

	}

	return highestBid;

}

int getLowestBalance(player* players, int totalPlayers) {

	int lowestBalance = players[0].balance;
	for (int i = 1; i < totalPlayers; i++) {

		if (players[i].balance < lowestBalance) {

			lowestBalance = players[i].balance;

		}

	}

	return lowestBalance;

}

void raise(player& currentPlayer, int totalPlayers, int& pot, int highestBid, int lowestBalance) {

	int ammount = -1;
	while (
		currentPlayer.currentBid + ammount < highestBid
		|| ammount > lowestBalance
		|| ammount % CHIP_VALUE != 0
		|| ammount > currentPlayer.balance
		) {

		cout << "Enter an ammount to raise: (ammount needs to be divisible by the value of a single chip)" << endl;
		cin >> ammount;

	}

	pot += ammount;
	currentPlayer.balance -= ammount;
	currentPlayer.currentBid += ammount;

}

int main() {

	int totalPlayers = setPlayerCount();
	player* players = initializePlayers(totalPlayers);
	int pot = 0;

	while (true) {

		startGame(totalPlayers, players, pot);
		int i = 0;

		while (true) {

			player currentPlayer = players[i];
			vizualizePlayerHand(currentPlayer.hand, i + 1);

			char command = ' ';
			while (command != 'r' && command != 'R' && command != 'f' && command != 'F' && command != 'c' && command != 'C') {

				cout << endl << "Enter a command: (r - raise; f - fold; c - call)" << endl;
				cin >> command;

			}

			if (command == 'r' || command == 'R') {

				int highestBid = getHighestBid(players, totalPlayers);
				int lowestBalance = getLowestBalance(players, totalPlayers);
				raise(currentPlayer, totalPlayers, pot, highestBid, lowestBalance);

			}

			i++;
			if (i == totalPlayers) {

				i = 0;

			}

		}

	}

}