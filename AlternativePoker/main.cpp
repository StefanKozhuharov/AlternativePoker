#include <iostream>
#include <fstream>
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

void dealCards(player* players, int totalPlayers, bool* activePlayers) {

	shuffleDeck(cards);

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < totalPlayers; j++) {

			if (activePlayers[j]) {

				players[j].hand[i] = cards[j + i * totalPlayers];

			}

		}

	}

}

void vizualizeBalances(player* players, int totalPlayers) {

	for (int i = 0; i < totalPlayers; i++) {

		cout << "Player" << i + 1 << ": " << players[i].balance;
		cout << endl;
	}

	cout << endl;

}

void joinDrawOrNot(player* players, bool* activePlayers, int totalPlayers, int& pot, bool* winningPlayers, int& bid) {

	char decision = ' ';

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

}

void startGame(int totalPlayers, player* players, int& pot, bool* activePlayers) {

	dealCards(players, totalPlayers, activePlayers);

	for (int i = 0; i < totalPlayers; i++) {

		players[i].balance -= CHIP_VALUE;
		players[i].currentBid = CHIP_VALUE;
		players[i].score = calculateScore(players[i].hand);

	}

	pot = totalPlayers * CHIP_VALUE;

	vizualizeBalances(players, totalPlayers);

}

void draw(int totalPlayers, player* players, int& pot, bool* activePlayers) {

	bool* winningPlayers = getPlayersWithHighestScore(players, activePlayers, totalPlayers);
	int bid = 0;

	joinDrawOrNot(players, activePlayers, totalPlayers, pot, winningPlayers, bid);

	dealCards(players, totalPlayers, activePlayers);

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

	vizualizeBalances(players, totalPlayers);

	delete[] winningPlayers;

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

void endGame(player& currentPlayer, int currentPlayerIndex, player* players, bool* activePlayers, int pot, int& totalPlayers, int TOTAL_PLAYERS) {

	currentPlayer.balance += pot;

	for (int i = 0; i < totalPlayers; i++) {

		if (players[i].balance == 0) {

			bustPlayerOut(players, totalPlayers, i);

		}

	}

	if (TOTAL_PLAYERS - getNumberOfBustedOutPlayers(players, TOTAL_PLAYERS) == 1) {

		cout << "Player" << currentPlayerIndex << " wins!";
		delete[] players;
		delete[] activePlayers;
		remove("save.txt");
		exit(0);

	}

	char decision = ' ';

	while (decision != 'y' && decision != 'Y' && decision != 'n' && decision != 'N') {

		cout << "Would you like to play again?" << endl;
		cin >> decision;

	}

	if (decision == 'n' || decision == 'N') {

		ofstream save("save.txt");
		save << TOTAL_PLAYERS << "\n" << totalPlayers << '\n';
		for (int i = 0; i < TOTAL_PLAYERS; i++) {

			save << players[i].balance << "\n";

		}
		save.close();

		delete[] players;
		delete[] activePlayers;
		exit(0);

	}

}

bool isEmpty(ifstream& pFile)
{
	return pFile.peek() == ifstream::traits_type::eof();
}

int getFileSize() {

	ifstream file("save.txt");

	if (!file.is_open()) {

		cout << "Error";

	}

	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	file.getline(line, MAX_SIZE_CHAR_ARRAY, '\0');

	while (line[index] != '\0') {
		
		index++;

	}

	file.close();
	return index+1;
}

int getRowCount() {

	ifstream file("save.txt");

	if (!file.is_open()) {

		cout << "Error";

	}

	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	int counterNewLine = 0;

	file.getline(line, MAX_SIZE_CHAR_ARRAY, '\0');

	while (line[index] != '\0') {

		if (line[index] == '\n') {

			counterNewLine++;

		}

		index++;

	}

	file.close();
	counterNewLine++;
	return counterNewLine;
}

void continueGame(int& TOTAL_PLAYERS, int& totalPlayers, player*& players) {

	ifstream save("save.txt");
	int length = getFileSize();
	char* text = new char[length];
	save.getline(text, length, '\0');
	int rowCount = getRowCount();
	int currentRow = 1;

	while (*text != '\0' && currentRow != rowCount+1) {

		int num = 0;
		while (*text >= '0' && *text <= '9') {

			num = num * 10 + (*text - '0');
			text++;

		}

		text++;
		if (currentRow == 1) {

			TOTAL_PLAYERS = num;
			players = initializePlayers(TOTAL_PLAYERS);

		}
		else if (currentRow == 2) {

			totalPlayers = num;

		}
		else {

			players[currentRow - 3].balance = num;

		}

		currentRow++;

	}

	save.close();

}

void vizualizeHUD(player* players, int totalPlayers, bool* activePlayers, int pot, int i, int turnsWithoutRaise) {

	int highestBid = getHighestBid(players, totalPlayers, activePlayers);

	cout << "Pot: " << pot << endl;
	cout << "Highest bid: " << highestBid << endl;
	cout << endl << "Player" << i + 1 << "'s turn" << endl;
	cout << "Your bid: " << players[i].currentBid << endl;
	cout << "Your balance: " << players[i].balance << endl;
	vizualizePlayerHand(players[i].hand, i + 1);
	char command = selectCommand(players[i], highestBid);
	handleCommand(command, players, totalPlayers, activePlayers, pot, highestBid, turnsWithoutRaise, i);

}

void onePlaythrough(bool* activePlayers, player* players, int& totalPlayers, int TOTAL_PLAYERS, int& pot, bool& isDraw) {

	int i = 0;
	int turnsWithoutRaise = 0;

	while (true) {

		if (!activePlayers[i]) {

			turnsWithoutRaise++;
			i = ++i % totalPlayers;
			continue;

		}

		if (getNumberOfActivePlayers(activePlayers, totalPlayers) == 1) {

			endGame(players[i], i, players, activePlayers, pot, totalPlayers, TOTAL_PLAYERS);
			break;

		}

		if (turnsWithoutRaise == totalPlayers - 1) {

			if (getNumberOfHighestScoringPlayers(players, activePlayers, totalPlayers) == 1) {

				endGame(players[getHighestScoringPlayer(players, activePlayers, totalPlayers)], i, players, activePlayers, pot, totalPlayers, TOTAL_PLAYERS);

			}
			else {

				cout << "It's a draw!" << endl;
				isDraw = true;

			}

		}

		vizualizeHUD(players, totalPlayers, activePlayers, pot, i, turnsWithoutRaise);

		i = ++i % totalPlayers;

	}

}

void continueGameOrNot(bool& continuedGame, int& TOTAL_PLAYERS, int& totalPlayers, player*& players) {

	char decision = ' ';

	while (decision != 'y' && decision != 'Y' && decision != 'n' && decision != 'N') {

		cout << "Would you like to continue your previous game?" << endl;
		cin >> decision;

	}

	if (decision == 'y' || decision == 'Y') {

		continuedGame = true;
		continueGame(TOTAL_PLAYERS, totalPlayers, players);

	}

}

int main() {

	ifstream save("save.txt");
	bool continuedGame = false;
	int TOTAL_PLAYERS = 0, totalPlayers = 0;
	player* players = nullptr;

	if (!isEmpty(save)) {

		continueGameOrNot(continuedGame, TOTAL_PLAYERS, totalPlayers, players);

	}

	save.close();
	if (!continuedGame) {

		ofstream save("save.txt");
		save << ' ';
		totalPlayers = setPlayerCount();
		TOTAL_PLAYERS = totalPlayers;
		players = initializePlayers(TOTAL_PLAYERS);
		save.close();

	}

	bool* activePlayers = new bool[TOTAL_PLAYERS];
	int pot = 0;
	bool isDraw = false;

	if (players == nullptr) {

		return 0;

	}

	while (true) {

		if (!isDraw) {

			for (int i = 0; i < totalPlayers; i++) {

				activePlayers[i] = true;

			}
			startGame(totalPlayers, players, pot, activePlayers);

		}
		else {

			draw(totalPlayers, players, pot, activePlayers);
			isDraw = false;

		}

		onePlaythrough(activePlayers, players, totalPlayers, TOTAL_PLAYERS, pot, isDraw);

	}

}