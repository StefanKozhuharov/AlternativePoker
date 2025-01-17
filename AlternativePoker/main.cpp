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

	cout << endl;

}

int getHighestBid(player* players, int totalPlayers, bool* activePlayers) {

	int highestBid = players[0].currentBid;
	for (int i = 1; i < totalPlayers; i++) {

		if (players[i].currentBid > highestBid && activePlayers[i]) {

			highestBid = players[i].currentBid;

		}

	}

	return highestBid;

}

int getLowestBalance(player* players, int totalPlayers, bool* activePlayers) {

	int highestBid = getHighestBid(players, totalPlayers, activePlayers);
	int lowestBalance = players[0].currentBid - highestBid + players[0].balance;
	for (int i = 1; i < totalPlayers; i++) {

		int currentPlayerBalance = players[i].currentBid - highestBid + players[i].balance;

		if (currentPlayerBalance < lowestBalance && activePlayers[i]) {

			lowestBalance = currentPlayerBalance;

		}

	}

	return lowestBalance;

}

void raise(player& currentPlayer, int& pot, int highestBid, int lowestBalance) {

	int ammount = -1;
	while (
		currentPlayer.currentBid + ammount < highestBid
		|| ammount > lowestBalance
		|| ammount % CHIP_VALUE != 0
		|| ammount > currentPlayer.balance - highestBid + currentPlayer.currentBid
		|| ammount < highestBid - currentPlayer.currentBid + CHIP_VALUE
		) {

		cout << "Enter an ammount to raise: (ammount needs to be divisible by the value of a single chip)" << endl;
		cin >> ammount;

	}

	int addedChips = ammount + highestBid - currentPlayer.currentBid;
	pot += addedChips;
	currentPlayer.balance -= addedChips;
	currentPlayer.currentBid += addedChips;

}

void fold(bool* activePlayers, int playerIndex) {

	activePlayers[playerIndex] = false;

}

void call(player& currentPlayer, int& pot, int highestBid) {

	currentPlayer.balance -= highestBid - currentPlayer.currentBid;
	pot += highestBid - currentPlayer.currentBid;
	currentPlayer.currentBid = highestBid;

}

int main() {

	int totalPlayers = setPlayerCount();
	player* players = initializePlayers(totalPlayers);
	bool* activePlayers = new bool[totalPlayers];
	int pot = 0;

	while (true) {

		startGame(totalPlayers, players, pot);

		for (int i = 0; i < totalPlayers; i++) {

			activePlayers[i] = true;

		}

		int i = 0;
		int turnsWithoutRaise = 0;

		while (true) {

			if (!activePlayers[i]) {

				turnsWithoutRaise++;
				i = ++i % totalPlayers;
				continue;

			}

			if (turnsWithoutRaise == totalPlayers - 1) {



			}

			int highestBid = getHighestBid(players, totalPlayers, activePlayers);

			cout << "Pot: " << pot << endl;
			cout << "Highest bid: " << highestBid << endl;
			cout << endl << "Player" << i + 1 << "'s turn" << endl;
			cout << "Your bid: " << players[i].currentBid << endl;
			cout << "Your balance: " << players[i].balance << endl;
			vizualizePlayerHand(players[i].hand, i + 1);

			char command = ' ';
			
			if (players[i].balance - highestBid + players[i].currentBid == 0) {

				while (command != 'f' && command != 'F' && command != 'c' && command != 'C') {

					cout << endl << "Enter a command: (f - fold; c - call)" << endl;
					cin >> command;

				}

			}
			else if (players[i].currentBid == highestBid) {

				while (command != 'r' && command != 'R' && command != 'f' && command != 'F') {

					cout << endl << "Enter a command: (r - raise; f - fold)" << endl;
					cin >> command;

				}

			}
			else {

				while (command != 'r' && command != 'R' && command != 'f' && command != 'F' && command != 'c' && command != 'C') {

					cout << endl << "Enter a command: (r - raise; f - fold; c - call)" << endl;
					cin >> command;

				}

			}

			if (command == 'r' || command == 'R') {

				int lowestBalance = getLowestBalance(players, totalPlayers, activePlayers);
				raise(players[i], pot, highestBid, lowestBalance);
				turnsWithoutRaise = 0;

			}
			else if (command == 'f' || command == 'F') {

				fold(activePlayers, i);
				turnsWithoutRaise++;

			}
			else if (command == 'c' || command == 'C') {

				call(players[i], pot, highestBid);
				turnsWithoutRaise++;

			}

			i = ++i % totalPlayers;

		}

	}

}