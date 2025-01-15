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
