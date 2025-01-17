#include "deck.h"
#include "constants.h"
#include "player.h"

const int getCardScore(int card) {

	if (card == ACE) {

		return 11;

	}
	else if (card == SEVEN) {

		return 7;

	}
	else if (card == EIGHT) {

		return 8;

	}
	else if (card == NINE) {

		return 9;

	}
	else if (card >= TEN && card <= KING) {

		return 10;

	}

		return 0;

}

int getHighCard(int cardType[3]) {

	int scoreOne = getCardScore(cardType[0]);
	int scoreTwo = getCardScore(cardType[1]);
	int scoreThree = getCardScore(cardType[2]);
	int temp = scoreOne > scoreTwo ? scoreOne : scoreTwo;
	return temp > scoreThree ? temp : scoreThree;

}

int calculateScore(int hand[3]) {

	int cardType[3] = { getCardType(hand[0]), getCardType(hand[1]), getCardType(hand[2]) };
	int cardColour[3] = { getCardColour(hand[0]), getCardColour(hand[1]), getCardColour(hand[2]) };
	if (cardType[0] == cardType[1] && cardType[1] == cardType[2] && cardType[0] != SEVEN) {
		return getCardScore(cardType[0]) * 3;
	}else if (cardType[0] == cardType[1] && cardType[1] == cardType[2] && cardType[0] == SEVEN) {
		return 34;
	}
	else if (cardColour[0] == cardColour[1] && cardColour[1] == cardColour[2]) {
		return getCardScore(cardType[0]) + getCardScore(cardType[1]) + getCardScore(cardType[2]);
	}
	else if (
		(cardType[0] == cardType[1] && cardType[2] == SEVEN && cardColour[2] == CLUB)
		|| (cardType[0] == cardType[2] && cardType[1] == SEVEN && cardType[1] == CLUB)
		|| (cardType[1] == cardType[2] && cardType[0] == SEVEN && cardType[0] == CLUB)
		) {
		return 11 + 2 * (cardType[0] == SEVEN ? cardType[1] : cardType[0]);
	}
	else if (
		(cardColour[0] == cardColour[1] && cardType[2] == SEVEN && cardColour[2] == CLUB)
		|| (cardColour[0] == cardColour[2] && cardType[1] == SEVEN && cardColour[1] == CLUB)
		|| (cardColour[1] == cardColour[2] && cardType[0] == SEVEN && cardColour[0] == CLUB)
		) {
		return getCardScore(cardType[0]) + getCardScore(cardType[1]) + getCardScore(cardType[2]) + 4;
	}
	else if (
		(cardType[0] == SEVEN && cardColour[0] == CLUB)
		|| (cardType[1] == SEVEN && cardColour[1] == CLUB)
		|| (cardType[2] == SEVEN && cardColour[2] == CLUB)
		) {
		return getHighCard(cardType) + 11;
	}
	else {
		getHighCard(cardType);
	}

}

bool* getPlayersWithHighestScore(player* players, bool* activePlayers, int totalPlayers) {

	int highestScore = 0;
	bool* highestScorePlayers = new bool[totalPlayers];
	for (int i = 0; i < totalPlayers; i++) {

		highestScorePlayers[i] = false;

		if (players[i].score >= highestScore && activePlayers[i]) {

			highestScore = players[i].score;

		}

	}

	for (int i = 0; i < totalPlayers; i++) {

		if (players[i].score == highestScore && activePlayers[i]) {

			highestScorePlayers[i] = true;

		}

	}

	return highestScorePlayers;

}

int getNumberOfHighestScoringPlayers(player* players, bool* activePlayers, int totalPlayers) {

	int count = 0;
	bool* highestScorePlayers = getPlayersWithHighestScore(players, activePlayers, totalPlayers);

	for (int i = 0; i < totalPlayers; i++) {

		if (highestScorePlayers[i]) {

			count++;

		}

	}

	return count;

}

int getHighestScoringPlayer(player* players, bool* activePlayers, int totalPlayers) {

	int highestScore = 0, highestScoringPlayer = 0;
	for (int i = 0; i < totalPlayers; i++) {

		if (players[i].score > highestScore && activePlayers[i]) {

			highestScore = players[i].score;
			highestScoringPlayer = i;

		}

	}

	return highestScoringPlayer;

}