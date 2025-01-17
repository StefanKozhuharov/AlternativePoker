#include <iostream>
#include "player.h"
#include "deck.h"
#include "score.h"
#include "constants.h"
#include "structures.h"
using namespace std;

int cards[32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };

int getHighestBid(player* players, int totalPlayers, bool* activePlayers) {

	int highestBid = players[0].currentBid;
	for (int i = 1; i < totalPlayers; i++) {

		if (players[i].currentBid > highestBid && activePlayers[i]) {

			highestBid = players[i].currentBid;

		}

	}

	return highestBid;

}

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

void draw(int totalPlayers, player* players, int& pot, bool* activePlayers) {

	char decision = ' ';
	bool* winningPlayers = getPlayersWithHighestScore(players, activePlayers, totalPlayers);

	int bid;
	if ((pot / 2) % CHIP_VALUE == 0) {

		bid = pot / 2;

	}
	else {

		bid = pot / 2 + CHIP_VALUE / 2;

	}

	for (int i = 0; i < totalPlayers; i++) {

		while (decision != 'y' && decision != 'Y' && decision != 'n' && decision != 'N' && !winningPlayers[i] && players[i].balance - bid >= 0) {

			cout << "Player" << i << " would you like to join the tie?(y/n)" << endl;
			cin >> decision;

		}

		if (decision == 'n' || decision == 'N') {

			activePlayers[i] = false;

		}

	}

	shuffleDeck(cards);

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < totalPlayers; j++) {

			if (activePlayers[j]) {

				players[j].hand[i] = cards[j + i * totalPlayers];

			}

		}

	}

	for (int i = 0; i < totalPlayers; i++) {

		if (activePlayers[i] && winningPlayers[i]) {

			players[i].score = calculateScore(players[i].hand);

		}
		else if (activePlayers[i] && !winningPlayers[i]) {

			players[i].balance -= bid;
			players[i].currentBid += bid;
			players[i].score = calculateScore(players[i].hand);
			pot += bid;

		}

	}

	int highestBid = getHighestBid(players, totalPlayers, activePlayers);

	for (int i = 0; i < totalPlayers; i++) {

		if (players[i].balance - highestBid + players[i].currentBid < 0 && activePlayers[i]) {

			players[i].balance = 0;
			pot += highestBid - players[i].currentBid;
			players[i].currentBid = highestBid;

		}
		if (players[i].balance == 0 && activePlayers[i]) {

			players[i].balance += 50;

		}

	}

	for (int i = 0; i < totalPlayers; i++) {

		cout << "Player" << i + 1 << ": " << players[i].balance;
		cout << endl;
	}

	cout << endl;

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

char selectCommand(player currentPlayer, int highestBid) {

	char command = ' ';

	if (currentPlayer.balance - highestBid + currentPlayer.currentBid == 0) {

		while (command != 'f' && command != 'F' && command != 'c' && command != 'C') {

			cout << endl << "Enter a command: (f - fold; c - call)" << endl;
			cin >> command;

		}

	}
	else if (currentPlayer.currentBid == highestBid) {

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

	return command;

}

void handleCommand(char command, player* players, int totalPlayers, bool* activePlayers, int& pot, int& highestBid, int& turnsWithoutRaise, int playerIndex) {

	if (command == 'r' || command == 'R') {

		int lowestBalance = getLowestBalance(players, totalPlayers, activePlayers);
		raise(players[playerIndex], pot, highestBid, lowestBalance);
		turnsWithoutRaise = 0;

	}
	else if (command == 'f' || command == 'F') {

		fold(activePlayers, playerIndex);
		turnsWithoutRaise++;

	}
	else if (command == 'c' || command == 'C') {

		call(players[playerIndex], pot, highestBid);
		turnsWithoutRaise++;

	}

}

void endGame(player currentPlayer, int pot) {

	currentPlayer.balance += pot;

}

int main() {

	int totalPlayers = setPlayerCount();
	player* players = initializePlayers(totalPlayers);
	bool* activePlayers = new bool[totalPlayers];
	int pot = 0;
	bool isDraw = false;

	while (true) {

		if (!isDraw) {

			startGame(totalPlayers, players, pot);

		}
		else {

			draw(totalPlayers, players, pot, activePlayers);
			isDraw = false;

		}

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

			if (getNumberOfActivePlayers(activePlayers, totalPlayers) == 1) {

				endGame(players[i], pot);
				break;

			}

			if (turnsWithoutRaise == totalPlayers - 1) {

				if (getNumberOfHighestScoringPlayers(players, activePlayers, totalPlayers) == 1) {

					endGame(players[getHighestScoringPlayer(players, activePlayers, totalPlayers)], pot);

				}
				else {

					cout << "It's a draw!" << endl;
					isDraw = true;

				}

			}

			int highestBid = getHighestBid(players, totalPlayers, activePlayers);

			cout << "Pot: " << pot << endl;
			cout << "Highest bid: " << highestBid << endl;
			cout << endl << "Player" << i + 1 << "'s turn" << endl;
			cout << "Your bid: " << players[i].currentBid << endl;
			cout << "Your balance: " << players[i].balance << endl;
			vizualizePlayerHand(players[i].hand, i + 1);
			char command = selectCommand(players[i], highestBid);			
			handleCommand(command, players, totalPlayers, activePlayers, pot, highestBid, turnsWithoutRaise, i);

			i = ++i % totalPlayers;

		}

	}

}