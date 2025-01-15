#include "deck.h"
#include "constants.h"

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
